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
#include <Game/GameEngine/ScoreBoard.hpp>
#include <DRIMI/Mathematics/Methods/ToString.hpp>
#include <math.h> // floor

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
ScoreBoard::ST_HighScoreLine::ST_HighScoreLine ( std::string szName, GLint iScore ) :
  m_szName  (szName),
  m_iScore  (iScore)
{
}

////////////////////////////////////////////////////////////
std::string& ScoreBoard::ST_HighScoreLine::GetName ( void ) {
  return m_szName;
}

////////////////////////////////////////////////////////////
GLint ScoreBoard::ST_HighScoreLine::GetScore ( void ) {
  return m_iScore;
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
ScoreBoard::ScoreBoard ( void ) :
  m_lHighScores     (),
  m_lHighScoresIter ()
{
}

////////////////////////////////////////////////////////////
ScoreBoard::~ScoreBoard ( void ) {
  while (!m_lHighScores.empty ()) {
    delete (*m_lHighScores.begin ());
    m_lHighScores.erase (m_lHighScores.begin ());
  }
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void ScoreBoard::Initialize ( void ) {
  m_iTotalScore = 0;
  m_iCurrentScore = 0;
  m_uiLastRank = 0;
}

////////////////////////////////////////////////////////////
void ScoreBoard::AddInCurrentScore ( GLint iPoints ) {
  if (m_iCurrentScore > 0) {
    m_iCurrentScore += iPoints;
    if (m_iCurrentScore < 0) m_iCurrentScore = 0;
  }
}

////////////////////////////////////////////////////////////
void ScoreBoard::ComputeTotalScore ( void ) {
  m_iTotalScore += m_iCurrentScore;
}

////////////////////////////////////////////////////////////
GLboolean ScoreBoard::IsTotalScoreEligible ( void ) {
  return (m_iTotalScore > 0 && (m_lHighScores.size () < 10 || m_iTotalScore > (*m_lHighScores.back ()).GetScore ()));
}

////////////////////////////////////////////////////////////
GLboolean ScoreBoard::SaveHighScores ( const std::string& szName ) {
  std::string szHighScoresFileName = "datas/highscore/highscores.xml";
  std::string szError = "Error : Saving of the file \""+szHighScoresFileName+"\"";

  // Loading of the XML file of the high scores table
  tinyxml2::XMLDocument xmlDocument;
  if (xmlDocument.LoadFile (szHighScoresFileName.c_str ()) != tinyxml2::XML_NO_ERROR) {
    std::cerr << szError << std::endl;
    std::cerr << "  Error #" << xmlDocument.ErrorID () << " : " << xmlDocument.GetErrorStr1 () << std::endl;
    return GL_FALSE;
  }

  // Go on the first element of the document
  tinyxml2::XMLHandle xmlHandle (&xmlDocument);
  tinyxml2::XMLElement *xmlElement = xmlHandle.FirstChildElement ().FirstChildElement ().ToElement ();
  if (xmlElement == NULL) {
    std::cout << szError << std::endl;
    std::cerr << "  The current node doesn't exist !" << std::endl;
    return GL_FALSE;
  }

  // Searching of an emplacement to store the new score if it's necessary
  GLboolean bFound = GL_FALSE;
  GLuint uiRank = 1;
  for (auto it = m_lHighScores.begin () ; it != m_lHighScores.end () ; ++it) {
    // If the score is superior to minimum one of higher scores.
    if (m_iTotalScore > (*it)->GetScore ()) {
      m_lHighScores.insert (it, new ScoreBoard::ST_HighScoreLine (szName, m_iTotalScore));
      delete m_lHighScores.back ();
      m_lHighScores.pop_back ();
      m_uiLastRank = uiRank;
      bFound = GL_TRUE;
      break;
    }
    uiRank++;
  }
  // Else if there is a place to registered the score in the high scores table.
  if (!bFound && uiRank < 10) {
    m_lHighScores.push_back (new ScoreBoard::ST_HighScoreLine (szName, m_iTotalScore));
  }

  // Saving the datas in the XML file
  if (bFound) {
    for (auto it = m_lHighScores.begin () ; it != m_lHighScores.end () ; ++it) {
      xmlElement->SetAttribute ("name", (*it)->GetName ().c_str ());
      xmlElement->SetAttribute ("score", (*it)->GetScore ());
      xmlElement = xmlElement->NextSiblingElement ();
    }
    xmlDocument.SaveFile (szHighScoresFileName.c_str ());
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean ScoreBoard::LoadHighScores ( void ) {
  std::string szHighScoresFileName = "datas/highscore/highscores.xml";
  std::string szError = "Error : Loading of the file \""+szHighScoresFileName+"\"";

  // Loading of the XML file of the high scores table
  tinyxml2::XMLDocument xmlDocument;
  if (xmlDocument.LoadFile (szHighScoresFileName.c_str ()) != tinyxml2::XML_NO_ERROR) {
    std::cerr << szError << std::endl;
    std::cerr << "  Error #" << xmlDocument.ErrorID () << " : " << xmlDocument.GetErrorStr1 () << std::endl;
    return GL_FALSE;
  }

  // Go on the first element of the document
  tinyxml2::XMLHandle xmlHandle (&xmlDocument);
  tinyxml2::XMLElement *xmlElement = xmlHandle.FirstChildElement ().FirstChildElement ().ToElement ();
  if (xmlElement == NULL) {
    std::cout << szError << std::endl;
    std::cerr << "  The current node doesn't exist !" << std::endl;
    return GL_FALSE;
  }

  // Initialization of the high scores table
  GLint iScore;
  while (xmlElement != NULL) {
    xmlElement->QueryIntAttribute ("score", &iScore);
    m_lHighScores.push_back (new ScoreBoard::ST_HighScoreLine (xmlElement->Attribute ("name"), iScore));
    xmlElement = xmlElement->NextSiblingElement ();
  }
  std::cout << "Loading of the high scores : Succeed" << std::endl;

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void ScoreBoard::ResetHighScoresIter ( void ) {
  m_lHighScoresIter = m_lHighScores.begin ();
}

////////////////////////////////////////////////////////////
void ScoreBoard::NextHighScoresIter ( void ) {
  m_lHighScoresIter++;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
std::string ScoreBoard::ToStringTotal ( void ) {
  return drimi::ToString (m_iTotalScore);
}

////////////////////////////////////////////////////////////
std::string ScoreBoard::ToStringCurrent ( void ) {
  return drimi::ToString (m_iCurrentScore);
}

////////////////////////////////////////////////////////////
void ScoreBoard::SetCurrentScore ( GLint iPoints ) {
  m_iCurrentScore = iPoints;
}

////////////////////////////////////////////////////////////
GLint ScoreBoard::GetCurrentScore ( void ) {
  return m_iCurrentScore;
}

////////////////////////////////////////////////////////////
GLuint ScoreBoard::GetLastRank ( void ) {
  return m_uiLastRank;
}

////////////////////////////////////////////////////////////
ScoreBoard::ST_HighScoreLine& ScoreBoard::GetHighScoresLine ( void ) {
  return (*(*m_lHighScoresIter));
}
