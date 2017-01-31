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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file GOTerrain.hpp
 * \brief Class for the terrain of the game.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2016-2017
 *
 */

#ifndef GOTERRAIN_HPP__
#define GOTERRAIN_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObject2D.hpp>
#include <Game/GameEngine/Food/FoodsManager.hpp>
#include <Game/GameEngine/Tiles/TilesManager.hpp>

#define GRAPHSIZE_X   16
#define GRAPHSIZE_Y   12
#define TILES_GRID_X  33  // GRAPHSIZE_X*2+1
#define TILES_GRID_Y  25  // GRAPHSIZE_Y*2+1

////////////////////////////////////////////////////////////
/// \brief Class to create the terrain.
///
////////////////////////////////////////////////////////////
class GOTerrain : public GameObject, public GameObject2D {

  public :
    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a tile of the terrain.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_Tile {
      GLuint              m_uiIdentifier;       ///< Identifier of the tile.
      Tiles::Type         m_eTileType;          ///< Identifier of the type on the tile.
      union SubType {
        Tiles::GroundType eGroundType;
        Tiles::WallType   eWallType;
      }                   m_eSubType;           ///< Identifier of the type on the ground or wall.
      Foods::Type         m_eFoodType;          ///< Identifier of the food on the tile.
      Tiles::ShadowType   m_eShadowType;        ///< Identifier of the shadow on the tile.
      GLuint              m_uiLightValue;       ///< Value of the light on the tile.

			ST_Tile ( void );
      void SetIdentifier ( GLuint uiIdentifier );
      void SetTileType ( Tiles::GroundType eGroundType );
      void SetTileType ( Tiles::WallType eWallType );
      void SetFoodType ( Foods::Type eFoodType );
      void SetShadowType ( Tiles::ShadowType eShadowType );
      void SetLight ( GLuint uiLightValue );
      GLuint GetIdentifier ( void );
      GLboolean IsFoodExist ( void );
      Tiles::Type GetTileType ( void );
      Tiles::GroundType GetGroundType ( void );
      Tiles::WallType GetWallType ( void );
      Foods::Type GetFoodType ( void );
      Tiles::ShadowType GetShadowType ( void );
      GLuint GetLight ( void );
      void ToEmpty ( void );
    };

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint        m_uiTileGround_ID,
                  m_uiTileWall_ID,
                  m_uiTileStart_ID,
                  m_uiTileGoal_ID;
    GLint         m_iStartNodeX, m_iStartNodeY;
    GLint         m_iGoalNodeX, m_iGoalNodeY;
    GLuint        m_uiTileStartX, m_uiTileStartY;
    GLuint        m_uiTileGoalX, m_uiTileGoalY;
    GLuint        m_uiLongestPath;
    GLuint        m_uiAfterLastTorch;
    sf::Vector2u  m_v2uTorches[50];                 /// Nombre arbitraire de torches, à calculer plus tard.
    GLuint        m_uiTorchesCount;                 //< Number of placed torches.
    GLuint        m_uiFoodPlacementTrigger,
                  m_uiFoodPlacementCounter;
    GLboolean     m_bIsMapRevealed;
    GLboolean     m_bGraph[GRAPHSIZE_X][GRAPHSIZE_Y];
    ST_Tile       m_stTilesGrid[TILES_GRID_X][TILES_GRID_Y];
    GLboolean     m_bVisibilityGrid[TILES_GRID_X][TILES_GRID_Y];
    sf::Vector2u  m_sfFrustumCullingFirst, m_sfFrustumCullingSecond;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the game object.
    ///
    ////////////////////////////////////////////////////////////
    GOTerrain ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GOTerrain ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the game object.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Upgrade all the composants of the game object when
    /// the render target view is resized.
    ///
    ////////////////////////////////////////////////////////////
    void ResizeView ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the state.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) { return GL_FALSE; }

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the game object.
    ///
    /// \return True to permit the inputs of the other game objects to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void ) { return GL_FALSE; }

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the state.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( void );
    void DrawShadows ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Positionnate the start node in the graph.
    ///
    ////////////////////////////////////////////////////////////
    void PositionateStartNode ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Selectionate the neighbor node in the graph.
    ///
    /// \param iXIn   Input X value of the node position.
    ///        iYIn   Input Y value of the node position.
    ///        iXOut  Output X value of the neighbor position.
    ///        iYOut  Output Y value of the neighbor position.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean RandNodeSelector ( GLint iXIn, GLint iYIn, GLint& iXOut, GLint& iYOut );

    ////////////////////////////////////////////////////////////
    /// \brief Generate the walls of the labyrinth.
    ///
    /// \param uiX  X value of the case position.
    ///        uiY  Y value of the case position.
    ///
    ////////////////////////////////////////////////////////////
    void GenerateWalls ( GLuint uiX, GLuint uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Generate the shadows of the labyrinth.
    ///
    /// \param uiX  X value of the case position.
    ///        uiY  Y value of the case position.
    ///
    ////////////////////////////////////////////////////////////
    void GenerateShadows ( GLuint uiX, GLuint uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Generate the labyrinth and the goal point. (Recursive function)
    ///
    /// \param iX  X value of the first position.
    ///        iY  Y value of the first position.
    ///        uiCurrentPath  Current path value.
    ///
    ////////////////////////////////////////////////////////////
    void GenerateMazePath ( GLint iX, GLint iY, GLuint uiCurrentPath );

    ////////////////////////////////////////////////////////////
    void GenerateLight ( GLint iX, GLint iY, GLint iDirection );

    ////////////////////////////////////////////////////////////
    /// \brief Final generator of the labyrinth.
    ///
    ////////////////////////////////////////////////////////////
    void GenerateLabyrinth ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Update the visibility of the terrain.
    ///
    /// \param uiX  X value of the position of the player.
    ///        uiY  Y value of the position of the player.
    ///
    ////////////////////////////////////////////////////////////
    void UpdateVisibility ( GLuint uiX, GLuint uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Reset the terrain.
    ///
    ////////////////////////////////////////////////////////////
    void Reset ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Reset the visibility of the terrain to true.
    ///
    ////////////////////////////////////////////////////////////
    void RevealTerrain ( void );

    ////////////////////////////////////////////////////////////
    /// \brief compute the tiles in the screen.
    ///
    /// \param sfViewCenter   Center of the view to display the terrain.
    ///        sfViewSize     Size of the view to display the terrain.
    ///
    ////////////////////////////////////////////////////////////
    void FrustumCulling ( sf::Vector2f sfViewCenter, sf::Vector2f sfViewSize );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the start tile.
    ///
    /// \param uiX  Variable to get the X value of the position of the tile.
    ///        uiY  Variable to get the Y value of the position of the tile.
    ///
    ////////////////////////////////////////////////////////////
    void GetStartPosition ( GLuint& uiX, GLuint& uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the goal tile.
    ///
    /// \param uiX  Variable to get the X value of the position of the tile.
    ///        uiY  Variable to get the Y value of the position of the tile.
    ///
    ////////////////////////////////////////////////////////////
    void GetGoalPosition ( GLuint& uiX, GLuint& uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Check if the tile is an obstacle.
    ///
    /// \param uiX  X value of the position of the tile.
    ///        uiY  Y value of the position of the tile.
    ///
    /// \return True if the tile is an obstacle, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsObstacle ( GLuint uiX, GLuint uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the terrain in pixels.
    ///
    /// \param fWidth   Width of the size of the terrain in pixels.
    ///        fHeight  Height of the size of the terrain in pixels.
    ///
    ////////////////////////////////////////////////////////////
    void GetSizeInPixels ( GLfloat& fWidth, GLfloat& fHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Set the food on the tile.
    ///
    /// \param eFoodType  Type of the food on the tile.
    ///        uiX        X value of the position of the tile.
    ///        uiY        Y value of the position of the tile.
    ///
    ////////////////////////////////////////////////////////////
    void SetFood ( Foods::Type eFoodType, GLuint uiX, GLuint uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Get the food on the tile.
    ///
    /// \param uiX  X value of the position of the tile.
    ///        uiY  Y value of the position of the tile.
    ///
    /// \return Food Type on the tile.
    ///
    ////////////////////////////////////////////////////////////
    Foods::Type GetFood ( GLuint uiX, GLuint uiY );
};

#endif // GOTERRAIN_HPP__
