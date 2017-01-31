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
// along with The Fanstastic Labyrinth.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameObjects/WorldState/GOTerrain.hpp>

#include <cstdlib>
#include <ctime>

// Random function
GLint Rand ( GLint iStart, GLint iMax ) {
  return rand ()%(iMax-iStart)+iStart;
}

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOTerrain::ST_Tile::ST_Tile ( void ) :
  m_uiIdentifier          (0),
  m_eTileType             (Tiles::Type::T_Count),
  m_eFoodType             (Foods::Type::Count),
  m_eShadowType           (Tiles::ShadowType::ST_Count),
  m_uiLightValue          (128)
{
  m_eSubType.eGroundType = Tiles::GroundType::GT_Count;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::SetIdentifier ( GLuint uiIdentifier ) {
  m_uiIdentifier = uiIdentifier;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::SetTileType ( Tiles::GroundType eGroundType ) {
  m_eTileType = Tiles::Type::Ground;
  m_eSubType.eGroundType = eGroundType;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::SetTileType ( Tiles::WallType eWallType ) {
  m_eTileType = Tiles::Type::Wall;
  m_eSubType.eWallType = eWallType;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::SetFoodType ( Foods::Type eFoodType ) {
  m_eFoodType = eFoodType;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::SetShadowType ( Tiles::ShadowType eShadowType ) {
  m_eShadowType = eShadowType;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::SetLight ( GLuint uiLightValue ) {
  m_uiLightValue = uiLightValue;
}

////////////////////////////////////////////////////////////
GLuint GOTerrain::ST_Tile::GetIdentifier ( void ) {
  return m_uiIdentifier;
}

////////////////////////////////////////////////////////////
GLboolean GOTerrain::ST_Tile::IsFoodExist ( void ) {
  return m_eFoodType != Foods::Type::Count;
}

////////////////////////////////////////////////////////////
Tiles::Type GOTerrain::ST_Tile::GetTileType ( void ) {
  return m_eTileType;
}

////////////////////////////////////////////////////////////
Tiles::GroundType GOTerrain::ST_Tile::GetGroundType ( void ) {
  return m_eSubType.eGroundType;
}

////////////////////////////////////////////////////////////
Tiles::WallType GOTerrain::ST_Tile::GetWallType ( void ) {
  return m_eSubType.eWallType;
}

////////////////////////////////////////////////////////////
Foods::Type GOTerrain::ST_Tile::GetFoodType ( void ) {
  return m_eFoodType;
}

////////////////////////////////////////////////////////////
Tiles::ShadowType GOTerrain::ST_Tile::GetShadowType ( void ) {
  return m_eShadowType;
}

////////////////////////////////////////////////////////////
GLuint GOTerrain::ST_Tile::GetLight ( void ) {
  return m_uiLightValue;
}

////////////////////////////////////////////////////////////
void GOTerrain::ST_Tile::ToEmpty ( void ) {
  m_eFoodType = Foods::Type::Count;
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOTerrain::GOTerrain ( ST_Context& stContext ) :
  GameObject                (stContext),
  GameObject2D              (),
  m_uiTileGround_ID         (0),
  m_uiTileWall_ID           (0),
  m_uiTileStart_ID          (0),
  m_uiTileGoal_ID           (0),
  m_iStartNodeX             (-1),
  m_iStartNodeY             (-1),
  m_iGoalNodeX              (-1),
  m_iGoalNodeY              (-1),
  m_uiTileStartX            (0),
  m_uiTileStartY            (0),
  m_uiTileGoalX             (0),
  m_uiTileGoalY             (0),
  m_uiLongestPath           (0),
  m_uiAfterLastTorch        (0),
  m_uiTorchesCount          (0),
  m_uiFoodPlacementTrigger  (0),
  m_uiFoodPlacementCounter  (0),
  m_bIsMapRevealed          (GL_FALSE),
  m_sfFrustumCullingFirst   (0, 0),
  m_sfFrustumCullingSecond  (0, 0)
{
}

////////////////////////////////////////////////////////////
GOTerrain::~GOTerrain ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOTerrain::Initialize ( void ) {
  std::cout << " >> GOTerrain initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  /// Loading of the tiles
  // Loading of the textures 2D
  GLuint  uiTileStartGoalTexID  = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/tiles/start_goal", "png");

  // Tile of the start
  m_uiTileStart_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTileStart = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTileStart_ID);
  sfTileStart.setTexture      (oTextures2DManager.GetSFMLTexture (uiTileStartGoalTexID));
  sfTileStart.setTextureRect  (sf::IntRect (0, 0, 32, 32));
  // Tile of the start
  m_uiTileGoal_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfTileGoal = oRenderList2D.GetDrawable<sf::Sprite> (m_uiTileGoal_ID);
  sfTileGoal.setTexture     (oTextures2DManager.GetSFMLTexture (uiTileStartGoalTexID));
  sfTileGoal.setTextureRect (sf::IntRect (32, 0, 32, 32));

  m_iStartNodeX             = -1;
  m_iStartNodeY             = -1;
  m_iGoalNodeX              = -1;
  m_iGoalNodeY              = -1;
  m_uiTileStartX            = 0;
  m_uiTileStartY            = 0;
  m_uiTileGoalX             = 0;
  m_uiTileGoalY             = 0;
  m_uiLongestPath           = 0;
  m_uiAfterLastTorch        = 0;
  m_uiTorchesCount          = 0;
  m_bIsMapRevealed          = GL_FALSE;
  m_sfFrustumCullingFirst   = sf::Vector2u (0, 0);
  m_sfFrustumCullingSecond  = sf::Vector2u (0, 0);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOTerrain::ResizeView ( void ) {
}

////////////////////////////////////////////////////////////
void GOTerrain::Draw ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D   = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  FoodsManager& oFoodsManager   = m_stContext.GetFoodsManager ();
  TilesManager& oTilesManager   = m_stContext.GetTilesManager ();
  LevelsManager& oLevelsManager = m_stContext.GetLevelsManager ();

  GLfloat fX = 0.f, fY = 0.f;
  for (GLuint uiY = m_sfFrustumCullingFirst.y ; uiY < m_sfFrustumCullingSecond.y ; uiY++) {
    for (GLuint uiX = m_sfFrustumCullingFirst.x ; uiX < m_sfFrustumCullingSecond.x ; uiX++) {
      if (m_bVisibilityGrid[uiX][uiY]) {
        GLfloat fX = static_cast<GLfloat> (32*uiX), fY = static_cast<GLfloat> (32*uiY);
        if (m_stTilesGrid[uiX][uiY].GetTileType () == Tiles::Type::Ground) {
          oTilesManager.DrawGround (oLevelsManager.GetStepsCount (), oLevelsManager.GetSubLevelsCount (), fX, fY);
        } if (m_stTilesGrid[uiX][uiY].GetTileType () == Tiles::Type::Wall) {
          oTilesManager.DrawWall (oLevelsManager.GetStepsCount (), oLevelsManager.GetSubLevelsCount (), m_stTilesGrid[uiX][uiY].GetWallType (), fX, fY);
        } else {
          sf::Sprite& sfTile = oRenderList2D.GetDrawable<sf::Sprite> (m_stTilesGrid[uiX][uiY].GetIdentifier ());
          sfTile.setPosition (fX, fY);
          gmMainWindow.Draw (sfTile);
        }
        // Draw the food
        if (m_stTilesGrid[uiX][uiY].IsFoodExist ())
          oFoodsManager.Draw (m_stTilesGrid[uiX][uiY].GetFoodType (), 8.f+fX, 8.f+fY);
      }
    }
  }
}

////////////////////////////////////////////////////////////
void GOTerrain::DrawShadows ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D   = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  TilesManager& oTilesManager   = m_stContext.GetTilesManager ();

  GLfloat fX = 0.f, fY = 0.f;
  for (GLuint uiY = m_sfFrustumCullingFirst.y ; uiY < m_sfFrustumCullingSecond.y ; uiY++) {
    for (GLuint uiX = m_sfFrustumCullingFirst.x ; uiX < m_sfFrustumCullingSecond.x ; uiX++) {
      if (m_bVisibilityGrid[uiX][uiY]) {
        GLfloat fX = static_cast<GLfloat> (32*uiX), fY = static_cast<GLfloat> (32*uiY);
        // Draw the shadow
        if (m_stTilesGrid[uiX][uiY].GetTileType () == Tiles::Type::Ground) {
          oTilesManager.DrawShadow (m_stTilesGrid[uiX][uiY].GetShadowType (), m_stTilesGrid[uiX][uiY].GetLight (), fX, fY);
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////
void GOTerrain::PositionateStartNode ( void ) {
  srand (time (NULL)); // random initialising

  m_iStartNodeX = Rand (1, GRAPHSIZE_X-1);
  m_iStartNodeY = Rand (1, GRAPHSIZE_Y-1);
}

////////////////////////////////////////////////////////////
GLboolean GOTerrain::RandNodeSelector ( GLint iXIn, GLint iYIn, GLint& iXOut, GLint& iYOut ) {
  GLint iIndex_X[4], iIndex_Y[4];
  GLint iMax = 0;

  if (iYIn > 0 && !m_bGraph[iXIn][iYIn-1]) {
    iIndex_X[iMax] = 0;
    iIndex_Y[iMax] = -1;
    iMax++;
  }
  if (iXIn < GRAPHSIZE_X-1 && !m_bGraph[iXIn+1][iYIn]) {
    iIndex_X[iMax] = 1;
    iIndex_Y[iMax] = 0;
    iMax++;
  }
  if (iYIn < GRAPHSIZE_Y-1 && !m_bGraph[iXIn][iYIn+1]) {
    iIndex_X[iMax] = 0;
    iIndex_Y[iMax] = 1;
    iMax++;
  }
  if (iXIn > 0 && !m_bGraph[iXIn-1][iYIn]) {
    iIndex_X[iMax] = -1;
    iIndex_Y[iMax] = 0;
    iMax++;
  }

  if (iMax != 0) {
    GLint iRand = Rand (0, iMax);
    iXOut = iIndex_X[iRand];
    iYOut = iIndex_Y[iRand];
    return GL_TRUE;
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void GOTerrain::GenerateWalls ( GLuint uiX, GLuint uiY ) {
  // Case at the top
  if (m_stTilesGrid[uiX  ][uiY-1].GetTileType () == Tiles::Type::Wall) {
    if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::Cross)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::T_Top);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::T_Right)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::L_Top);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::T_Down)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::Horizontal);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::T_Left)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::L_Left);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::L_Right)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::I_Right);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::L_Down)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::I_Left);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::Vertical)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::I_Top);
    else if (m_stTilesGrid[uiX  ][uiY-1].GetWallType () == Tiles::WallType::I_Down)
      m_stTilesGrid[uiX  ][uiY-1].SetTileType (Tiles::WallType::Point);
  }
  // Case at the right
  if (m_stTilesGrid[uiX+1][uiY  ].GetTileType () == Tiles::Type::Wall) {
    if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::Cross)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::T_Right);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::T_Top)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::L_Top);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::T_Down)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::L_Right);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::T_Left)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::Vertical);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::L_Down)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::I_Down);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::L_Left)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::I_Top);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::Horizontal)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::I_Right);
    else if (m_stTilesGrid[uiX+1][uiY  ].GetWallType () == Tiles::WallType::I_Left)
      m_stTilesGrid[uiX+1][uiY  ].SetTileType (Tiles::WallType::Point);
  }
  // Case at the down
  if (m_stTilesGrid[uiX  ][uiY+1].GetTileType () == Tiles::Type::Wall) {
    if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::Cross)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::T_Down);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::T_Top)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::Horizontal);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::T_Right)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::L_Right);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::T_Left)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::L_Down);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::L_Top)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::I_Right);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::L_Left)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::I_Left);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::Vertical)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::I_Down);
    else if (m_stTilesGrid[uiX  ][uiY+1].GetWallType () == Tiles::WallType::I_Top)
      m_stTilesGrid[uiX  ][uiY+1].SetTileType (Tiles::WallType::Point);
  }
  // Case at the left
  if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) {
    if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::Cross)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::T_Left);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::T_Top)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::L_Left);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::T_Right)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::Vertical);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::T_Down)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::L_Down);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::L_Top)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::I_Top);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::L_Right)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::I_Down);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::Horizontal)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::I_Left);
    else if (m_stTilesGrid[uiX-1][uiY  ].GetWallType () == Tiles::WallType::I_Right)
      m_stTilesGrid[uiX-1][uiY  ].SetTileType (Tiles::WallType::Point);
  }
}

////////////////////////////////////////////////////////////
void GOTerrain::GenerateShadows ( GLuint uiX, GLuint uiY ) {
  if (m_stTilesGrid[uiX  ][uiY-1].GetTileType () == Tiles::Type::Wall) {            // Wall at the Top
    if (m_stTilesGrid[uiX+1][uiY  ].GetTileType () == Tiles::Type::Wall) {          // Wall at the Top_Right
      if (m_stTilesGrid[uiX  ][uiY+1].GetTileType () == Tiles::Type::Wall) {        // Wall at the Top_Right_Down
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top_Right_Down);
      } else if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) { // Wall at the Top_Right_Left
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top_Right_Left);
      } else {                                                                      // Wall at the Top_Right
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top_Right);
      }
    } else if (m_stTilesGrid[uiX  ][uiY+1].GetTileType () == Tiles::Type::Wall) {   // Wall at the Top_Down
      if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) {        // Wall at the Top_Down_Left
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top_Down_Left);
      } else {                                                                      // Wall at the Top_Down
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top_Down);
      }
    } else if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) {   // Wall at the Top_Left
      m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top_Left);
    } else {                                                                        // Wall at the Top
      m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Top);
    }
  } else {
    if (m_stTilesGrid[uiX+1][uiY  ].GetTileType () == Tiles::Type::Wall) {          // Wall at the Right
      if (m_stTilesGrid[uiX  ][uiY+1].GetTileType () == Tiles::Type::Wall) {        // Wall at the Right_Down
        if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) {      // Wall at the Right_Down_Left
          m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Right_Down_Left);
        } else {                                                                    // Wall at the Right_Down
          m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Right_Down);
        }
      } else if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) { // Wall at the Right_Left
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Right_Left);
      } else {                                                                      // Wall at the Right
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Right);
      }
    } else if (m_stTilesGrid[uiX  ][uiY+1].GetTileType () == Tiles::Type::Wall) {   // Wall at the Down
      if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) {        // Wall at the Down_Left
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Down_Left);
      } else {                                                                      // Wall at the Down
        m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Down);
      }
    } else if (m_stTilesGrid[uiX-1][uiY  ].GetTileType () == Tiles::Type::Wall) {   // Wall at the Left
      m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Left);
    } else {                                                                        // No walls
      m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Cross);
    }
  }
}

////////////////////////////////////////////////////////////
void GOTerrain::GenerateMazePath ( GLint iX, GLint iY, GLuint uiCurrentPath ) {
  GLint iNeighbour_X, iNeighbour_Y;
  GLint iCurrent_X, iCurrent_Y;
  GLint iCase_X, iCase_Y;

  uiCurrentPath++;
  while (RandNodeSelector (iX, iY, iNeighbour_X, iNeighbour_Y)) {
    m_bGraph[iX+iNeighbour_X][iY+iNeighbour_Y] = GL_TRUE;
    iCurrent_X = iX*2+1;
    iCurrent_Y = iY*2+1;
    iCase_X = iCurrent_X+iNeighbour_X;
    iCase_Y = iCurrent_Y+iNeighbour_Y;
    m_stTilesGrid[iCase_X][iCase_Y].SetIdentifier (9);
    m_stTilesGrid[iCase_X][iCase_Y].SetTileType (Tiles::GroundType::GreenBrick);
    GenerateWalls (iCase_X, iCase_Y);

    iCase_X = iCurrent_X+iNeighbour_X*2;
    iCase_Y = iCurrent_Y+iNeighbour_Y*2;
    m_stTilesGrid[iCase_X][iCase_Y].SetIdentifier (9);
    m_stTilesGrid[iCase_X][iCase_Y].SetTileType (Tiles::GroundType::GreenBrick);
    // Placement of the torches.
    if (m_uiAfterLastTorch == 4) {
      if (Rand (0, 2) == 1) {
        m_stTilesGrid[iCase_X][iCase_Y].SetLight (0);
        m_v2uTorches[m_uiTorchesCount].x = iCase_X;
        m_v2uTorches[m_uiTorchesCount].y = iCase_Y;
        m_uiTorchesCount++;
        m_uiAfterLastTorch = 0;
      }
    } else
      m_uiAfterLastTorch++;
    GenerateWalls (iCase_X, iCase_Y);

    GenerateMazePath (iX+iNeighbour_X, iY+iNeighbour_Y, uiCurrentPath);
  }
  if (uiCurrentPath > m_uiLongestPath && iX != m_iStartNodeX && iY != m_iStartNodeY) {
    m_uiLongestPath = uiCurrentPath;
    m_iGoalNodeX = iX;
    m_iGoalNodeY = iY;
  }
  // Food placement update.
  if (m_uiFoodPlacementCounter == m_uiFoodPlacementTrigger) {
    m_uiFoodPlacementTrigger = static_cast<GLuint> (Rand (55, 65));
    m_uiFoodPlacementCounter = 0;
    m_stTilesGrid[iX*2+1][iY*2+1].SetFoodType (static_cast<Foods::Type> (Rand (0, 3)));
  } else
    m_uiFoodPlacementCounter++;
}

////////////////////////////////////////////////////////////
void GOTerrain::GenerateLight ( GLint iX, GLint iY, GLint iDirection ) {
  GLuint uiLightToApply = m_stTilesGrid[iX][iY].GetLight () + 32;
  if (iDirection != 3 && m_stTilesGrid[iX  ][iY-1].GetTileType () == Tiles::Type::Ground) {
    if (m_stTilesGrid[iX  ][iY-1].GetLight () > uiLightToApply) {
      m_stTilesGrid[iX  ][iY-1].SetLight (uiLightToApply);
    }
    if (uiLightToApply < 96)
      GenerateLight (iX  ,iY-1, 1);
  }
  if (iDirection != 4 && m_stTilesGrid[iX+1][iY  ].GetTileType () == Tiles::Type::Ground) {
    if (m_stTilesGrid[iX+1][iY  ].GetLight () > uiLightToApply) {
      m_stTilesGrid[iX+1][iY  ].SetLight (uiLightToApply);
    }
    if (uiLightToApply < 96)
      GenerateLight (iX+1,iY  , 2);
  }
  if (iDirection != 1 && m_stTilesGrid[iX  ][iY+1].GetTileType () == Tiles::Type::Ground) {
    if (m_stTilesGrid[iX  ][iY+1].GetLight () > uiLightToApply) {
      m_stTilesGrid[iX  ][iY+1].SetLight (uiLightToApply);
    }
    if (uiLightToApply < 96)
      GenerateLight (iX  ,iY+1, 3);
  }
  if (iDirection != 2 && m_stTilesGrid[iX-1][iY  ].GetTileType () == Tiles::Type::Ground) {
    if (m_stTilesGrid[iX-1][iY  ].GetLight () > uiLightToApply) {
      m_stTilesGrid[iX-1][iY  ].SetLight (uiLightToApply);
    }
    if (uiLightToApply < 96)
      GenerateLight (iX-1,iY  , 4);
  }
}

////////////////////////////////////////////////////////////
void GOTerrain::GenerateLabyrinth ( void ) {
  GLuint uiCurrentPath  = 0;
  m_uiLongestPath       = 0;
  // Torches placement initialisation.
  m_uiAfterLastTorch    = 0;
  m_uiTorchesCount      = 0;
  // Food placement initialisation.
  m_uiFoodPlacementTrigger = 0;
  m_uiFoodPlacementCounter = 0;
  // Generating of the maze path
  GenerateMazePath (m_iStartNodeX, m_iStartNodeY, uiCurrentPath);
  for (GLuint uiY = 0 ; uiY < TILES_GRID_Y ; uiY++)
    for (GLuint uiX = 0 ; uiX < TILES_GRID_X ; uiX++)
      if (m_stTilesGrid[uiX][uiY].GetTileType () == Tiles::Type::Ground)
        GenerateShadows (uiX, uiY);
  for (GLuint uiTorch = 0 ; uiTorch < m_uiTorchesCount ; uiTorch++) {
    if (m_stTilesGrid[m_v2uTorches[uiTorch].x][m_v2uTorches[uiTorch].y].GetShadowType () == Tiles::ShadowType::ST_Cross)
      m_stTilesGrid[m_v2uTorches[uiTorch].x][m_v2uTorches[uiTorch].y].SetLight (128);
    else
      GenerateLight (m_v2uTorches[uiTorch].x, m_v2uTorches[uiTorch].y, 0);
  }
  // Wall placement update.
  m_uiTileStartX  = static_cast<GLuint> (m_iStartNodeX*2+1);
  m_uiTileStartY  = static_cast<GLuint> (m_iStartNodeY*2+1);
  m_uiTileGoalX   = static_cast<GLuint> (m_iGoalNodeX*2+1);
  m_uiTileGoalY   = static_cast<GLuint> (m_iGoalNodeY*2+1);
  m_stTilesGrid[m_uiTileStartX][m_uiTileStartY].SetIdentifier (m_uiTileStart_ID);
  m_stTilesGrid[m_uiTileStartX][m_uiTileStartY].ToEmpty ();
  m_stTilesGrid[m_uiTileGoalX][m_uiTileGoalY].SetIdentifier (m_uiTileGoal_ID);
  m_stTilesGrid[m_uiTileGoalX][m_uiTileGoalY].ToEmpty ();
}

////////////////////////////////////////////////////////////
void GOTerrain::UpdateVisibility ( GLuint uiX, GLuint uiY ) {
  m_bVisibilityGrid[uiX-1][uiY-1] = GL_TRUE;
  m_bVisibilityGrid[uiX  ][uiY-1] = GL_TRUE;
  m_bVisibilityGrid[uiX+1][uiY-1] = GL_TRUE;
  m_bVisibilityGrid[uiX-1][uiY  ] = GL_TRUE;
  m_bVisibilityGrid[uiX  ][uiY  ] = GL_TRUE;
  m_bVisibilityGrid[uiX+1][uiY  ] = GL_TRUE;
  m_bVisibilityGrid[uiX-1][uiY+1] = GL_TRUE;
  m_bVisibilityGrid[uiX  ][uiY+1] = GL_TRUE;
  m_bVisibilityGrid[uiX+1][uiY+1] = GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOTerrain::Reset ( void ) {
  /// Resetting of the graph
  for (GLuint uiY = 0; uiY < GRAPHSIZE_Y; uiY++)
    for (GLuint uiX = 0; uiX < GRAPHSIZE_X; uiX++)
      m_bGraph[uiX][uiY] = GL_FALSE;

  /// Resetting of the tiles and visibility grids
  for (GLuint uiY = 0 ; uiY < TILES_GRID_Y ; uiY++) {
    for (GLuint uiX = 0 ; uiX < TILES_GRID_X ; uiX++) {
      m_stTilesGrid[uiX][uiY].SetIdentifier (10);
      m_stTilesGrid[uiX][uiY].SetShadowType (Tiles::ShadowType::ST_Cross);
      m_stTilesGrid[uiX][uiY].SetLight (128);
      // Wall placement update.
      if (uiY == 0) {
        if (uiX == 0)
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::L_Right);
        else if (uiX == TILES_GRID_X-1)
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::L_Down);
        else
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::T_Down);
      } else if (uiY == TILES_GRID_Y-1) {
        if (uiX == 0)
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::L_Top);
        else if (uiX == TILES_GRID_X-1)
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::L_Left);
        else
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::T_Top);
      } else {
        if (uiX == 0)
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::T_Right);
        else if (uiX == TILES_GRID_X-1)
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::T_Left);
        else
          m_stTilesGrid[uiX][uiY].SetTileType (Tiles::WallType::Cross);
      }
      m_bVisibilityGrid[uiX][uiY] = GL_FALSE;
    }
  }
  m_bIsMapRevealed = GL_FALSE;
}

////////////////////////////////////////////////////////////
void GOTerrain::RevealTerrain ( void ) {
  if (!m_bIsMapRevealed) {
    /// Resetting of the tiles and visibility grids
    for (GLuint uiY = 0 ; uiY < TILES_GRID_Y ; uiY++) {
      for (GLuint uiX = 0 ; uiX < TILES_GRID_X ; uiX++) {
        m_bVisibilityGrid[uiX][uiY] = GL_TRUE;
      }
    }
    m_bIsMapRevealed = GL_TRUE;
  }
}

////////////////////////////////////////////////////////////
void GOTerrain::FrustumCulling ( sf::Vector2f sfViewCenter, sf::Vector2f sfViewSize ) {
  m_sfFrustumCullingFirst.x   = static_cast<GLuint> (floorf ((sfViewCenter.x-sfViewSize.x/2.f)/32.f));
  m_sfFrustumCullingFirst.y   = static_cast<GLuint> (floorf ((sfViewCenter.y-sfViewSize.y/2.f)/32.f));
  m_sfFrustumCullingSecond.x  = static_cast<GLuint> (ceilf ((sfViewCenter.x+sfViewSize.x/2.f)/32.f));
  m_sfFrustumCullingSecond.y  = static_cast<GLuint> (ceilf ((sfViewCenter.y+sfViewSize.y/2.f)/32.f));
  if (m_sfFrustumCullingSecond.x > TILES_GRID_X)
    m_sfFrustumCullingSecond.x  = TILES_GRID_X;
  if (m_sfFrustumCullingSecond.y > TILES_GRID_Y)
    m_sfFrustumCullingSecond.y  = TILES_GRID_Y;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOTerrain::GetStartPosition ( GLuint& uiX, GLuint& uiY ) {
  uiX = m_uiTileStartX;
  uiY = m_uiTileStartY;
}

////////////////////////////////////////////////////////////
void GOTerrain::GetGoalPosition ( GLuint& uiX, GLuint& uiY ) {
  uiX = m_uiTileGoalX;
  uiY = m_uiTileGoalY;
}

////////////////////////////////////////////////////////////
GLboolean GOTerrain::IsObstacle ( GLuint uiX, GLuint uiY ) {
  return m_stTilesGrid[uiX][uiY].GetTileType () == Tiles::Type::Wall;
}

////////////////////////////////////////////////////////////
void GOTerrain::GetSizeInPixels ( GLfloat& fWidth, GLfloat& fHeight ) {
  fWidth = TILES_GRID_X*32.f;
  fHeight = TILES_GRID_Y*32.f;
}

////////////////////////////////////////////////////////////
void GOTerrain::SetFood ( Foods::Type eFoodType, GLuint uiX, GLuint uiY ) {
  m_stTilesGrid[uiX][uiY].SetFoodType (eFoodType);
}

////////////////////////////////////////////////////////////
Foods::Type GOTerrain::GetFood ( GLuint uiX, GLuint uiY ) {
  return m_stTilesGrid[uiX][uiY].GetFoodType ();
}
