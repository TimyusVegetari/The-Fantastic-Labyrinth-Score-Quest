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
#include <Game/GameEngine/Tiles/TilesManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
TilesManager::TilesManager ( void ) :
  m_vDecorations  (),
  m_poShadows     (nullptr)
{
}

////////////////////////////////////////////////////////////
TilesManager::~TilesManager ( void ) {
  if (m_vDecorations.size () > 0) {
    for (GLuint uiTheme = 0 ; uiTheme < Tiles::Theme::Th_Count ; uiTheme++) {
      if (m_vDecorations[uiTheme] != nullptr)
        delete[] m_vDecorations[uiTheme];
    }
  }
  if (m_poShadows != nullptr)
    delete m_poShadows;
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void TilesManager::Initialize ( GameObject::ST_Context& stContext ) {
  // Getting of the needed systems
  Textures2DManager& oTextures2DManager = stContext.m_oGraphicsEngine.GetTextures2DManager ();
  // Loading of the texture 2D
  GLuint uiGroundTexID  = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/tiles/grounds", "png");
  GLuint uiWallTexID    = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/tiles/walls", "png");
  GLuint uiShadowTexID  = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/tiles/shadows", "png");
  GLuint uiTorchTexID   = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/tiles/torches", "png");

  // Creating the tile types.
  m_vDecorations.assign (Tiles::Theme::Th_Count, nullptr);
  std::cout << "Tiles of the grounds, walls, etc... registering : ";
  GLint iLeft = 1, iTopGround = 1, iTopWall = 1;
  for (GLuint uiTheme = 0 ; uiTheme < Tiles::Theme::Th_Count ; uiTheme++) {
    m_vDecorations[uiTheme] = new Decoration[5] {{stContext},{stContext},{stContext},{stContext},{stContext}};
    // Tile of the ground.
    m_vDecorations[uiTheme][0].SetGroundTexCoords (iLeft, iTopGround, TILE_WIDTH, TILE_HEIGHT);
    iLeft += TILE_WIDTH;
    m_vDecorations[uiTheme][1].SetGroundTexCoords (iLeft, iTopGround, TILE_WIDTH, TILE_HEIGHT);
    iLeft += TILE_WIDTH;
    m_vDecorations[uiTheme][2].SetGroundTexCoords (iLeft, iTopGround, TILE_WIDTH, TILE_HEIGHT);
    iLeft += TILE_WIDTH;
    m_vDecorations[uiTheme][3].SetGroundTexCoords (iLeft, iTopGround, TILE_WIDTH, TILE_HEIGHT);
    iLeft += TILE_WIDTH;
    m_vDecorations[uiTheme][4].SetGroundTexCoords (iLeft, iTopGround, TILE_WIDTH, TILE_HEIGHT);
    iLeft = 1;
    iTopGround += TILE_HEIGHT+1;
    // Tile of the oriented walls.
    m_vDecorations[uiTheme][0].SetWallTexCoords (1, iTopWall, TILE_WIDTH, TILE_HEIGHT);
    iTopWall += TILE_HEIGHT;
    m_vDecorations[uiTheme][1].SetWallTexCoords (1, iTopWall, TILE_WIDTH, TILE_HEIGHT);
    iTopWall += TILE_HEIGHT;
    m_vDecorations[uiTheme][2].SetWallTexCoords (1, iTopWall, TILE_WIDTH, TILE_HEIGHT);
    iTopWall += TILE_HEIGHT;
    m_vDecorations[uiTheme][3].SetWallTexCoords (1, iTopWall, TILE_WIDTH, TILE_HEIGHT);
    iTopWall += TILE_HEIGHT;
    m_vDecorations[uiTheme][4].SetWallTexCoords (1, iTopWall, TILE_WIDTH, TILE_HEIGHT);
    iTopWall += TILE_HEIGHT+1;
    // Initialisation of the decorations.
    m_vDecorations[uiTheme][0].Initialize (uiGroundTexID, uiWallTexID);
    m_vDecorations[uiTheme][1].Initialize (uiGroundTexID, uiWallTexID);
    m_vDecorations[uiTheme][2].Initialize (uiGroundTexID, uiWallTexID);
    m_vDecorations[uiTheme][3].Initialize (uiGroundTexID, uiWallTexID);
    m_vDecorations[uiTheme][4].Initialize (uiGroundTexID, uiWallTexID);

    // Initialisation of the shadows.
    m_poShadows = new Shadow (stContext);
    m_poShadows->SetTexCoords (sf::IntRect (0, 0, 54, 54));
    m_poShadows->Initialize (uiShadowTexID, uiTorchTexID);
  }
  std::cout << "Succeed" << std::endl;
}

////////////////////////////////////////////////////////////
void TilesManager::DrawGround ( GLuint uiStep, GLuint uiSubLevel, GLfloat fX, GLfloat fY, GLfloat fScale ) {
  m_vDecorations[uiStep][uiSubLevel].GetGround ().Draw (fX, fY, fScale);
}

////////////////////////////////////////////////////////////
void TilesManager::DrawWall ( GLuint uiStep, GLuint uiSubLevel, Tiles::WallType eWallType, GLfloat fX, GLfloat fY, GLfloat fScale ) {
  m_vDecorations[uiStep][uiSubLevel].GetWall ().Draw (eWallType, fX, fY, fScale);
}

////////////////////////////////////////////////////////////
void TilesManager::DrawShadow ( Tiles::ShadowType eShadowType, GLuint uiAlpha, GLfloat fX, GLfloat fY, GLfloat fScale ) {
  m_poShadows->Draw (eShadowType, uiAlpha, fX, fY, fScale);
}
