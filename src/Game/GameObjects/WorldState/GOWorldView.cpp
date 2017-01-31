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
// along with The Fanstastic Labyrinth.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameObjects/WorldState/GOWorldView.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOWorldView::GOWorldView ( ST_Context& stContext ) :
  GameObject            (stContext),
  GameObject2D          (),
  sf::View              (),
  m_sfViewportRect      (0.f, 0.f, 10.f, 10.f),
  m_sfScale             (1.f, 1.f),
  m_sfRenderTargetSize  (10.f, 10.f)
{
}

////////////////////////////////////////////////////////////
GOWorldView::~GOWorldView ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOWorldView::Initialize ( void ) {
  std::cout << " >> GOWorldView initializing..." << std::endl;
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Loading of the texture 2D
  GLuint  uiBordersTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gui/world_background", "png");

  // Tile of the player.
  m_sfBorders[0].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[0].setTextureRect (sf::IntRect (0, 0, 10, 10));
  m_sfBorders[1].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[1].setTextureRect (sf::IntRect (11, 0, 1, 10));
  m_sfBorders[2].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[2].setTextureRect (sf::IntRect (13, 0, 10, 10));
  m_sfBorders[3].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[3].setTextureRect (sf::IntRect (0, 11, 10, 1));
  m_sfBorders[4].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[4].setTextureRect (sf::IntRect (13, 11, 10, 1));
  m_sfBorders[5].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[5].setTextureRect (sf::IntRect (0, 13, 10, 10));
  m_sfBorders[6].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[6].setTextureRect (sf::IntRect (11, 13, 1, 10));
  m_sfBorders[7].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[7].setTextureRect (sf::IntRect (13, 13, 10, 10));
  m_sfBorders[8].setTexture (oTextures2DManager.GetSFMLTexture (uiBordersTexID));
  m_sfBorders[8].setTextureRect (sf::IntRect (11, 11, 1, 1));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOWorldView::Scrolling ( GLfloat fX, GLfloat fY, GLfloat fWidth, GLfloat fHeight ) {
  // Update the scrolling for X
  GLfloat fCenter1X = m_sfViewportRect.width/2.f;
  if (fWidth > m_sfViewportRect.width) {
    if (fX < fCenter1X)
      fX = fCenter1X;
    else {
      GLfloat fCenter2X = fCenter1X+(fWidth-m_sfViewportRect.width);
      if (fX > fCenter2X)
        fX = fCenter2X;
    }
  } else
    fX = fCenter1X;
  // Update the scrolling for Y
  GLfloat fCenter1Y = m_sfViewportRect.height/2.f;
  if (fHeight > m_sfViewportRect.height) {
    if (fY < fCenter1Y)
      fY = fCenter1Y;
    else {
      GLfloat fCenter2Y = fCenter1Y+(fHeight-m_sfViewportRect.height);
      if (fY > fCenter2Y)
        fY = fCenter2Y;
    }
  } else
    fY = fCenter1Y;
  // Update of the view center
  setCenter (fX, fY);
}

////////////////////////////////////////////////////////////
void GOWorldView::Draw ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Draw the world borders
  for (GLuint uiWB = 0 ; uiWB < 9 ; uiWB++)
    gmMainWindow.Draw (m_sfBorders[uiWB]);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOWorldView::SetScale ( GLfloat fScaleX, GLfloat fScaleY ) {
  m_sfScale.x = fScaleX;
  m_sfScale.y = fScaleY;
}

////////////////////////////////////////////////////////////
void GOWorldView::SetRenderTargetSize ( GLfloat fWidth, GLfloat fHeight ) {
  m_sfRenderTargetSize.x = fWidth*m_sfScale.x;
  m_sfRenderTargetSize.y = fHeight*m_sfScale.y;
}

////////////////////////////////////////////////////////////
void GOWorldView::SetViewport ( GLfloat fLeft, GLfloat fTop, GLfloat fWidth, GLfloat fHeight ) {
  // Positionate the world borders.
  m_sfBorders[0].setPosition (fLeft, fTop);
  m_sfBorders[1].setPosition (fLeft+10.f, fTop);
  m_sfBorders[1].setScale (fWidth-20.f, 1.f);
  m_sfBorders[2].setPosition (fWidth-10.f, fTop);
  m_sfBorders[3].setPosition (fLeft, fTop+10.f);
  m_sfBorders[3].setScale (1.f, fHeight-20.f);
  m_sfBorders[4].setPosition (fWidth-10.f, fTop+10.f);
  m_sfBorders[4].setScale (1.f, fHeight-20.f);
  m_sfBorders[5].setPosition (fLeft, fTop+fHeight-10.f);
  m_sfBorders[6].setPosition (fLeft+10.f, fTop+fHeight-10.f);
  m_sfBorders[6].setScale (fWidth-20.f, 1.f);
  m_sfBorders[7].setPosition (fWidth-10.f, fTop+fHeight-10.f);
  m_sfBorders[8].setPosition (fLeft+10.f, fTop+10.f);
  m_sfBorders[8].setScale (fWidth-20.f, fHeight-20.f);

  // Configurate the viewport.
  fLeft += 10.f;
  fTop += 10.f;
  fWidth -= 20.f;
  fHeight -= 20.f;
  m_sfViewportRect.left   = fLeft*m_sfScale.x;
  m_sfViewportRect.top    = fTop*m_sfScale.y;
  m_sfViewportRect.width  = fWidth*m_sfScale.x;
  m_sfViewportRect.height = fHeight*m_sfScale.y;
  setViewport (sf::FloatRect (m_sfViewportRect.left/m_sfRenderTargetSize.x, m_sfViewportRect.top/m_sfRenderTargetSize.y, m_sfViewportRect.width/m_sfRenderTargetSize.x, m_sfViewportRect.height/m_sfRenderTargetSize.y));
}
