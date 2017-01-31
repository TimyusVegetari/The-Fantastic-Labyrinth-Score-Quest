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
#include <Game/GameEngine/Food/Food.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Food::Food ( GameObject::ST_Context& stContext ) :
  m_stContext   (stContext),
  m_sfSprite    (),
  m_iScore      (0)
{
}

////////////////////////////////////////////////////////////
Food::~Food ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Food::Initialize ( GLuint uiFoodTexID, sf::IntRect sfTexRect, GLint iScore ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  std::string szFoodType = "";
  if (iScore == 300)
    szFoodType = "Fruit";
  else if (iScore == 600)
    szFoodType = "Bread";
  else if (iScore == 900)
    szFoodType = "Vegetable soup";
  else
    szFoodType = "None";
  std::cout << " >> Food [" << szFoodType << "] initializing..." << std::endl;

  // Tile of the food.
  m_sfSprite.setTexture (oTextures2DManager.GetSFMLTexture (uiFoodTexID));
  m_sfSprite.setTextureRect (sfTexRect);
  // Score of the food.
  m_iScore = iScore;

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void Food::Draw ( GLfloat fX, GLfloat fY, GLfloat fScale ) {
  // Getting of the needed systems.
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  m_sfSprite.setPosition (fX, fY);
  m_sfSprite.setScale (fScale, fScale);
  gmMainWindow.Draw (m_sfSprite);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLint Food::GetScore ( void ) {
  return m_iScore;
}
