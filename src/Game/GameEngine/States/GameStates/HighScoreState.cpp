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
#include <Game/GameEngine/States/GameStates/HighScoreState.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
HighScoreState::HighScoreState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID   (0),
  m_uiHighScore_ID      (0),
  m_uiPressEnter_ID     (0),
  m_uiPressEnterTimer   (0),
  m_uiHighScores        (0),
  m_sfMainView          ()
{
}

////////////////////////////////////////////////////////////
HighScoreState::~HighScoreState ( void ) {
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);

  // Delete the game objects
  m_stContext.m_oGameObjectsManager.DeleteGameObject (GameObjects::Type::HighScores, m_uiHighScores);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean HighScoreState::Initialize ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  // Creation of the initializer for this state.
  m_uiInitializer_ID = oGameObjectsManager.CreateInitializer ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();

  // Loading of the textures 2D
  GLuint m_uiHighScoreTex_ID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/highscore/highscore", "png");

  // Game high score
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  m_uiHighScore_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfHighScore = oRenderList2D.GetDrawable<sf::Sprite> (m_uiHighScore_ID);
  sfHighScore.setTexture  (oTextures2DManager.GetSFMLTexture (m_uiHighScoreTex_ID), true);
	sfHighScore.setOrigin   (sfHighScore.getLocalBounds ().width / 2.f, sfHighScore.getLocalBounds ().height / 2.f);
	sfHighScore.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 5.f));

  // Game high scores
  if (!oGameObjectsManager.AddToInitializer<GOHighScores> (m_uiInitializer_ID, GameObjects::Type::HighScores, m_uiHighScores)) {
    // Debug : It will be necessary to process the errors, in the future.
  }
  GOHighScores& oGOHighScores = oGameObjectsManager.GetGameObject<GOHighScores> (GameObjects::Type::HighScores, m_uiHighScores);
  oGOHighScores.SetRenderList2D_ID (m_uiRenderList2D_ID);
	oGOHighScores.SetSize (600.f, 0.f);
	oGOHighScores.SetPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 5.f)+64.f);

  // Game Press Enter
  m_uiPressEnter_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oPressEnter = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiPressEnter_ID);
  oPressEnter.SetFont      (m_stContext.m_oBmpFont);
  oPressEnter.SetString    ("- Press Enter to continue -");
  oPressEnter.SetColor     (sf::Color::Green);
	oPressEnter.SetOrigin    (oPressEnter.GetLocalBounds ().width / 2.f, oPressEnter.GetLocalBounds ().height / 2.f);
	oPressEnter.setPosition  (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 5.f)+330.f);

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void HighScoreState::ResizeView ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  // Update the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, static_cast<GLfloat> (gmMainWindow.GetWidth ()), static_cast<GLfloat> (gmMainWindow.GetHeight ())));

  // Game high score
  sf::Sprite& sfHighScore = oRenderList2D.GetDrawable<sf::Sprite> (m_uiHighScore_ID);
	sfHighScore.setPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 5.f));
  // Game high scores
  GOHighScores& oGOHighScores = oGameObjectsManager.GetGameObject<GOHighScores> (GameObjects::Type::HighScores, m_uiHighScores);
	oGOHighScores.SetPosition (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 5.f)+64.f);
  oGOHighScores.ResizeView ();

  // Game Press Enter
  drimi::BmpText& oPressEnter = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiPressEnter_ID);
	oPressEnter.setPosition  (gmMainWindow.GetView ().getCenter ().x, floorf (static_cast<GLfloat> (gmMainWindow.GetHeight ()) / 5.f)+330.f);
}

////////////////////////////////////////////////////////////
void HighScoreState::Draw ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

  gmMainWindow.EnableSFML ();

  // Activating of the main view
  gmMainWindow.setView (m_sfMainView);

  // Draw high score
  sf::Sprite& sfHighScore = oRenderList2D.GetDrawable<sf::Sprite> (m_uiHighScore_ID);
  gmMainWindow.Draw (sfHighScore);
  // Draw high scores
  GOHighScores& oGOHighScores = oGameObjectsManager.GetGameObject<GOHighScores> (GameObjects::Type::HighScores, m_uiHighScores);
	oGOHighScores.Draw ();
  // Draw Press Enter
  if (m_uiPressEnterTimer == 40) {
    m_uiPressEnterTimer = 0;
  } else {
    if (m_uiPressEnterTimer < 20) {
      drimi::BmpText& oPressEnter = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiPressEnter_ID);
      gmMainWindow.Draw (oPressEnter);
    }
    m_uiPressEnterTimer++;
  }

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean HighScoreState::Update ( void ) {
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean HighScoreState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  if (eEventType == drimi::Event::Type::Closed) {
    gmMainWindow.Close ();
	} else if (eEventType == drimi::Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      case sf::Keyboard::Key::Return :
        RequestStackReplace (States::ID::Title);
        break;
      default :
        break;
    }
	}

	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean HighScoreState::HandleInput ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& HighScoreState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
