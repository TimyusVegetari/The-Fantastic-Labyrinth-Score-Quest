////////////////////////////////////////////////////////////
//
// This file is part of The Fantastic Labyrinth.
// Copyright (C) 2016 Acroute Anthony (ant110283@hotmail.fr)
//
// The Fantastic Labyrinth is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// The Fantastic Labyrinth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with The Fantastic Labyrinth.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/States/GameStates/GameOverState.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameOverState::GameOverState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID   (0),
  m_sfMainView          (),
  m_uiBackGround_ID     (0),
	m_uiGameOver_ID       (0),
  m_uiTotalScore_ID     (0),
  m_uiEndMessage_ID     (0),
  m_oScoreContainer     (),
  m_bSaveScore          (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
GameOverState::~GameOverState ( void ) {
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GameOverState::Initialize ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  ScoreBoard& oScoreBoard = m_stContext.GetScoreBoard ();

  // Creation of the initializer for this state.
  m_uiInitializer_ID = oGameObjectsManager.CreateInitializer ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();

  // Loading of the textures 2D
  GLuint m_uiGameOverTex_ID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gameover/gameover", "png");

	// GameOver and final score
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  m_uiBackGround_ID           = oRenderList2D.PushBack<sf::RectangleShape> ();
  sf::RectangleShape& sfBackGround = oRenderList2D.GetDrawable<sf::RectangleShape> (m_uiBackGround_ID);
  sfBackGround.setFillColor    (sf::Color (0, 0, 0, 160));
	sfBackGround.setPosition     (0.f, 0.f);
	sfBackGround.setSize         (sf::Vector2f (static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));

  m_uiGameOver_ID       = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfGameOver = oRenderList2D.GetDrawable<sf::Sprite> (m_uiGameOver_ID);
	sfGameOver.setTexture  (oTextures2DManager.GetSFMLTexture (m_uiGameOverTex_ID), true);
	sfGameOver.setOrigin   (sfGameOver.getLocalBounds ().width/2.f, sfGameOver.getLocalBounds ().height/2.f);
	sfGameOver.setPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f-20.f);

  m_uiTotalScore_ID       = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);
  oTotalScore.SetFont     (m_stContext.m_oBmpFont);
  oTotalScore.SetStyle    (sf::Text::Style::Bold);
  oTotalScore.SetColor    (sf::Color::Yellow);
	oTotalScore.SetString   ("Score : "+oScoreBoard.ToStringTotal ());
	oTotalScore.SetOrigin   (oTotalScore.GetLocalBounds ().width/2.f, oTotalScore.GetLocalBounds ().height/2.f);
	oTotalScore.setPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f+12.f);

  m_uiEndMessage_ID       = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oEndMessage = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiEndMessage_ID);
  oEndMessage.SetFont     (m_stContext.m_oBmpFont);
  oEndMessage.SetStyle    (sf::Text::Style::Bold);
  oEndMessage.SetColor    (sf::Color::Yellow);

	// If the current score is not at zero, this is the end of the game.
  if (oScoreBoard.GetCurrentScore () > 0) {
    oEndMessage.SetString   ("For now, this game contain only 15 levels.\nThe final version will contain 40 levels or more ;)");
    oEndMessage.SetOrigin   (oEndMessage.GetLocalBounds ().width/2.f, oEndMessage.GetLocalBounds ().height/2.f);
    oEndMessage.setPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f+80.f);
	}

  // If the total score is eligible
  if (oScoreBoard.IsTotalScoreEligible ()) {
    m_bSaveScore = GL_TRUE;

    // Positioning the container of the text line for the final score
    m_oScoreContainer.SetPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f+40.f);

    // Loading of the textures 2D
    GLuint  uiTextLineTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gui/button", "png");

    // Game menu : Text line
    m_poTextLine = std::make_shared<drimi::Gui::TextLine> ();
    m_poTextLine->SetBackgroundTexture (oTextures2DManager.GetSFMLTexture (uiTextLineTexID), 198, 32);
    m_poTextLine->SetText ("", m_stContext.m_oBmpFont);
    m_poTextLine->SetColor (sf::Color::Yellow);
    m_poTextLine->SetPosition (0.f, 0.f);
    m_poTextLine->Activate ();
    m_oScoreContainer.Pack (m_poTextLine);
	}

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GameOverState::ResizeView ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  // Update the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));

	// Update main board and scores
  sf::RectangleShape& sfBackGround = oRenderList2D.GetDrawable<sf::RectangleShape> (m_uiBackGround_ID);
	sfBackGround.setSize (sf::Vector2f (static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));

  sf::Sprite& sfGameOver = oRenderList2D.GetDrawable<sf::Sprite> (m_uiGameOver_ID);
	sfGameOver.setPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f-20.f);

  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);
	oTotalScore.setPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f+12.f);

  if (m_bSaveScore) {
    // Positioning the text line for the final score
    m_oScoreContainer.SetPosition (static_cast<GLfloat> (gmMainWindow.GetWidth ())/2.f, static_cast<GLfloat> (gmMainWindow.GetHeight())/2.f+28.f);
  }
}

////////////////////////////////////////////////////////////
void GameOverState::Draw ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  ScoreBoard& oScoreBoard = m_stContext.GetScoreBoard ();

  gmMainWindow.EnableSFML ();

  // Activating of the main view
  gmMainWindow.setView (m_sfMainView);

  // Draw the GameOver and the score
  sf::RectangleShape& sfBackGround = oRenderList2D.GetDrawable<sf::RectangleShape> (m_uiBackGround_ID);
  gmMainWindow.Draw (sfBackGround);
  sf::Sprite& sfGameOver = oRenderList2D.GetDrawable<sf::Sprite> (m_uiGameOver_ID);
  gmMainWindow.Draw (sfGameOver);
  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);
  gmMainWindow.Draw (oTotalScore);

  if (m_bSaveScore) {
    // Draw the text line for the final score
    m_oScoreContainer.Update ();
    gmMainWindow.Draw (m_oScoreContainer);
  }
	// This is the end of the game.
  if (oScoreBoard.GetCurrentScore () > 0) {
    drimi::BmpText& oEndMessage = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiEndMessage_ID);
    gmMainWindow.Draw (oEndMessage);
  }

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean GameOverState::Update ( void ) {
	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean GameOverState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  if (eEventType == drimi::Event::Type::Closed) {
    gmMainWindow.Close ();
	} else if (eEventType == drimi::Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      case sf::Keyboard::Key::Escape :
        gmMainWindow.Close ();
        break;
      case sf::Keyboard::Key::Return :
        RequestStackPop ();
        if (!m_bSaveScore) {
          RequestStackReplace (States::ID::Title);
        } else {
          // Saving of the score
          ScoreBoard& oScoreBoard = m_stContext.GetScoreBoard ();
          oScoreBoard.SaveHighScores (m_poTextLine->GetText ());

          RequestStackReplace (States::ID::HighScore);
        }
        break;
      default :
        break;
    }
	}
  if (m_bSaveScore) {
    // Event of text line for the final score
    m_oScoreContainer.HandleEvent (eEventType, sfKeyCode);
  }

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean GameOverState::HandleTextUnicode ( const char cUnicode ) {
  if (m_bSaveScore) {
    // Text unicode of text line for the final score
    m_oScoreContainer.HandleTextUnicode (cUnicode);
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean GameOverState::HandleInput ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& GameOverState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
