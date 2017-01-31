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
#include <Game/GameEngine/Tiles/Shadow.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Shadow::Shadow ( GameObject::ST_Context& stContext ) :
  m_stContext   (stContext)
{
}

////////////////////////////////////////////////////////////
Shadow::~Shadow ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Shadow::Initialize ( GLuint uiShadowTexID, GLuint uiTorchTexID ) {
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Tile of the shadow.
  const sf::Texture& sfTexShadow = oTextures2DManager.GetSFMLTexture (uiShadowTexID);
  const sf::Texture& sfTexTorch = oTextures2DManager.GetSFMLTexture (uiTorchTexID);
  for (GLuint uiShadowType = 0 ; uiShadowType < Tiles::ShadowType::ST_Count ; uiShadowType++) {
    m_sfShadow[uiShadowType].setTexture (sfTexShadow);
    m_sfShadow[uiShadowType].setOrigin  (11.f, 11.f);
    m_sfTorch[uiShadowType].setTexture (sfTexTorch);
    m_sfTorch[uiShadowType].setOrigin  (11.f, 11.f);
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void Shadow::Draw ( Tiles::ShadowType eShadowType, GLuint uiAlpha, GLfloat fX, GLfloat fY, GLfloat fScale ) {
  // Getting of the needed systems.
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  m_sfShadow[eShadowType].setPosition (fX, fY);
  m_sfShadow[eShadowType].setScale (fScale, fScale);
  m_sfShadow[eShadowType].setColor (sf::Color (255, 255, 255, uiAlpha));
  gmMainWindow.Draw (m_sfShadow[eShadowType]);
  if (uiAlpha == 0) {
    m_sfTorch[eShadowType].setPosition (fX, fY);
    m_sfTorch[eShadowType].setScale (fScale, fScale);
    gmMainWindow.Draw (m_sfTorch[eShadowType]);
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Shadow::SetTexCoords ( sf::IntRect sfTexRect ) {
  for (GLuint uiShadowType = 0 ; uiShadowType < Tiles::ShadowType::ST_Count ; uiShadowType++) {
    m_sfShadow[uiShadowType].setTextureRect (sfTexRect);
    m_sfTorch[uiShadowType].setTextureRect (sfTexRect);
    sfTexRect.left += sfTexRect.width;
  }
}
