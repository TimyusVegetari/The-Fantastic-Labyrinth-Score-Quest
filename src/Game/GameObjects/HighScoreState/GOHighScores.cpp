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
#include <Game/GameObjects/HighScoreState/GOHighScores.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOHighScores::GOHighScores ( ST_Context& stContext ) :
  GameObject          (stContext),
  GameObject2D        (),
  m_uiRank_ID         (0),
  m_uiName_ID         (0),
  m_uiScore_ID        (0)
{
}

////////////////////////////////////////////////////////////
GOHighScores::~GOHighScores ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOHighScores::Initialize ( void ) {
  std::cout << " >> GOHighScore initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

	// Game rank
  m_uiRankLabel_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oRankLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiRankLabel_ID);
  oRankLabel.SetFont      (m_stContext.m_oBmpFont);
  oRankLabel.SetString    ("Rank");
  oRankLabel.SetStyle     (sf::Text::Style::Bold);
  oRankLabel.SetColor     (sf::Color::Yellow);
	oRankLabel.SetOrigin    (oRankLabel.GetLocalBounds ().width/2.f, oRankLabel.GetLocalBounds ().height/2.f);
	oRankLabel.setPosition  (m_sfPosition.x-m_sfSize.x/2.f, m_sfPosition.y);
  m_uiRank_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oRank = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiRank_ID);
  oRank.SetFont      (m_stContext.m_oBmpFont);
  oRank.SetString    ("");
  oRank.SetStyle     (sf::Text::Style::Regular);
  oRank.SetColor     (sf::Color::White);

	// Game name
  m_uiNameLabel_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oNameLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiNameLabel_ID);
  oNameLabel.SetFont      (m_stContext.m_oBmpFont);
  oNameLabel.SetString    ("Name");
  oNameLabel.SetStyle     (sf::Text::Style::Bold);
  oNameLabel.SetColor     (sf::Color::Yellow);
	oNameLabel.SetOrigin    (oNameLabel.GetLocalBounds ().width/2.f, oNameLabel.GetLocalBounds ().height/2.f);
	oNameLabel.setPosition  ((m_sfPosition.x-m_sfSize.x/2.f)+300.f, m_sfPosition.y);
  m_uiName_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oName = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiName_ID);
  oName.SetFont      (m_stContext.m_oBmpFont);
  oName.SetString    ("");
  oName.SetStyle     (sf::Text::Style::Regular);
  oName.SetColor     (sf::Color::White);

	// Game score
  m_uiScoreLabel_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oScoreLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScoreLabel_ID);
  oScoreLabel.SetFont      (m_stContext.m_oBmpFont);
  oScoreLabel.SetString    ("Score");
  oScoreLabel.SetStyle     (sf::Text::Style::Bold);
  oScoreLabel.SetColor     (sf::Color::Yellow);
	oScoreLabel.SetOrigin    (oScoreLabel.GetLocalBounds ().width/2.f, oScoreLabel.GetLocalBounds ().height/2.f);
	oScoreLabel.setPosition  ((m_sfPosition.x-m_sfSize.x/2.f)+600.f, m_sfPosition.y);
  m_uiScore_ID = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScore_ID);
  oScore.SetFont      (m_stContext.m_oBmpFont);
  oScore.SetString    ("");
  oScore.SetStyle     (sf::Text::Style::Regular);
  oScore.SetColor     (sf::Color::White);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOHighScores::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Get the render list 2D
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  // Game rank
  drimi::BmpText& oRankLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiRankLabel_ID);
	oRankLabel.setPosition  (m_sfPosition.x-m_sfSize.x/2.f, m_sfPosition.y);
	// Game name
  drimi::BmpText& oNameLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiNameLabel_ID);
	oNameLabel.setPosition  ((m_sfPosition.x-m_sfSize.x/2.f)+300.f, m_sfPosition.y);
	// Game score
  drimi::BmpText& oScoreLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScoreLabel_ID);
	oScoreLabel.setPosition  ((m_sfPosition.x-m_sfSize.x/2.f)+600.f, m_sfPosition.y);
}

////////////////////////////////////////////////////////////
void GOHighScores::Draw ( void ) {
  // Getting of the main window
  ScoreBoard& oScoreBoard = m_stContext.GetScoreBoard ();
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  // Draw the labels
  drimi::BmpText& oRankLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiRankLabel_ID);
  gmMainWindow.Draw (oRankLabel);
  drimi::BmpText& oNameLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiNameLabel_ID);
  gmMainWindow.Draw (oNameLabel);
  drimi::BmpText& oScoreLabel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScoreLabel_ID);
  gmMainWindow.Draw (oScoreLabel);

  // Draw the datas
  GLfloat fPositionY = oRankLabel.getPosition ().y+20.f;
  oScoreBoard.ResetHighScoresIter ();
  for (GLuint uiRank = 1; uiRank <= 10; uiRank++) {
    ScoreBoard::ST_HighScoreLine& stHighScoreLine = oScoreBoard.GetHighScoresLine ();

    drimi::BmpText& oRank = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiRank_ID);
    oRank.SetString   (drimi::ToString (uiRank));
    oRank.SetOrigin   (oRank.GetLocalBounds ().width/2.f, oRank.GetLocalBounds ().height/2.f);
    oRank.setPosition (oRankLabel.getPosition ().x, fPositionY);

    drimi::BmpText& oName = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiName_ID);
    oName.SetString   (stHighScoreLine.GetName ());
    oName.SetOrigin   (oName.GetLocalBounds ().width/2.f, oName.GetLocalBounds ().height/2.f);
    oName.setPosition (oNameLabel.getPosition ().x, fPositionY);

    drimi::BmpText& oScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScore_ID);
    oScore.SetString    (drimi::ToString (stHighScoreLine.GetScore ()));
    oScore.SetOrigin    (oScore.GetLocalBounds ().width/2.f, oScore.GetLocalBounds ().height/2.f);
    oScore.setPosition  (oScoreLabel.getPosition ().x, fPositionY);

    if (uiRank == oScoreBoard.GetLastRank ()) {
      oRank.SetColor (sf::Color::Green);
      gmMainWindow.Draw (oRank);
      oRank.SetColor (sf::Color::White);
      oName.SetColor (sf::Color::Green);
      gmMainWindow.Draw (oName);
      oName.SetColor (sf::Color::White);
      oScore.SetColor (sf::Color::Green);
      gmMainWindow.Draw (oScore);
      oScore.SetColor (sf::Color::White);
    } else {
      gmMainWindow.Draw (oRank);
      gmMainWindow.Draw (oName);
      gmMainWindow.Draw (oScore);
    }

    oScoreBoard.NextHighScoresIter ();
    fPositionY += 20.f;
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOHighScores::SetPosition ( GLfloat fX, GLfloat fY ) {
  m_sfPosition = sf::Vector2f (fX, fY);
}

////////////////////////////////////////////////////////////
void GOHighScores::SetSize ( GLfloat fWidth, GLfloat fHeight ) {
  m_sfSize = sf::Vector2f (fWidth, fHeight);
}
