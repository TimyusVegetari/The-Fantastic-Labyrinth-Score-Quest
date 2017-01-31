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
#include <Game/GameObjects/TitleState/GOTitle.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOTitle::GOTitle ( ST_Context& stContext ) :
  GameObject        (stContext),
  GameObject2D      (),
  m_sfPosition      (),
  m_uiTitleBG_ID    (0),
  m_uiTitle_ID      (0),
  m_uiSubTitle_ID   (0)
{
}

////////////////////////////////////////////////////////////
GOTitle::~GOTitle ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOTitle::Initialize ( void ) {
  std::cout << " >> GOTitle initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  // Loading of the textures 2D
  GLuint  uiTitleBgTexID  = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/title/titlebg", "png"),
          uiTitleTexID    = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/title/title", "png"),
          uiSubTitleTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/title/subtitle", "png");

  // Game title background
  m_uiTitleBG_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitleBG = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitleBG_ID);
  sfTitleBG.setTexture  (oTextures2DManager.GetSFMLTexture (uiTitleBgTexID), true);
	sfTitleBG.setOrigin   (sfTitleBG.getLocalBounds ().width / 2.f, sfTitleBG.getLocalBounds ().height / 2.f);
	sfTitleBG.setPosition (m_sfPosition.x, m_sfPosition.y);
  // Game title
  m_uiTitle_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitle_ID);
  sfTitle.setTexture      (oTextures2DManager.GetSFMLTexture (uiTitleTexID), true);
	sfTitle.setOrigin       (sfTitle.getLocalBounds ().width / 2.f, sfTitle.getLocalBounds ().height / 2.f);
	sfTitle.setPosition     (m_sfPosition.x, m_sfPosition.y);
  // Game subtitle
  m_uiSubTitle_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfSubTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiSubTitle_ID);
  sfSubTitle.setTexture      (oTextures2DManager.GetSFMLTexture (uiSubTitleTexID), true);
	sfSubTitle.setOrigin       (sfSubTitle.getLocalBounds ().width / 2.f, sfSubTitle.getLocalBounds ().height / 2.f);
	sfSubTitle.setPosition     (m_sfPosition.x+154.f, m_sfPosition.y+84.f);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOTitle::ResizeView ( void ) {
  // Get the render list 2D
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  // Game title background
  sf::Sprite& sfTitleBG = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitleBG_ID);
	sfTitleBG.setPosition (m_sfPosition.x, m_sfPosition.y);
  // Game title
  sf::Sprite& sfTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTitle_ID);
	sfTitle.setPosition (m_sfPosition.x, m_sfPosition.y);
  // Game title
  sf::Sprite& sfSubTitle = oRenderList2D.GetDrawable<sf::Sprite> (m_uiSubTitle_ID);
	sfSubTitle.setPosition (m_sfPosition.x+154.f, m_sfPosition.y+84.f);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOTitle::SetPosition ( GLfloat fX, GLfloat fY ) {
  m_sfPosition = sf::Vector2f (fX, fY);
}

////////////////////////////////////////////////////////////
const sf::Vector2f& GOTitle::GetPosition ( void ) {
  return m_sfPosition;
}
