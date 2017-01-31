////////////////////////////////////////////////////////////
//
// This file is part of The Fantastic Labyrinth.
// Copyright (C) 2016-2017 Acroute Anthony (ant110283@hotmail.fr)
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
#include <Game/GameEngine/Tiles/Ground.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Ground::Ground ( GameObject::ST_Context& stContext ) :
  m_stContext   (stContext)
{
}

////////////////////////////////////////////////////////////
Ground::~Ground ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Ground::Initialize ( GLuint uiGroundTexID ) {
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Tile of the wall.
  const sf::Texture& sfTexture = oTextures2DManager.GetSFMLTexture (uiGroundTexID);
  m_sfSprite.setTexture (sfTexture);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void Ground::Draw ( GLfloat fX, GLfloat fY, GLfloat fScale ) {
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
void Ground::SetTexCoords ( sf::IntRect sfTexRect ) {
  m_sfSprite.setTextureRect (sfTexRect);
}
