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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file Wall.hpp
 * \brief Class for the wall objects.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2016-2017
 *
 */

#ifndef WALL_HPP__
#define WALL_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include "TileTypes.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to create wall object like as a stonebricks wall,
/// a bricks wall, a foliage wall, etc...
///
////////////////////////////////////////////////////////////
class Wall {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<Wall>  Ptr; ///< Unique pointer of wall.

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GameObject::ST_Context&   m_stContext;
    sf::Sprite                m_sfSprite[Tiles::WallType::WT_Count];

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a wall.
    ///
    /// \param stContext  Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    Wall ( GameObject::ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the wall.
    ///
    ////////////////////////////////////////////////////////////
    ~Wall ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the wall.
    ///
    /// \param uiWallTexID  Value to identify the texture of the walls.
    /*///        sfTexRect    Position and size of the subtexture of the wall.*/
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( GLuint uiWallTexID );

    ////////////////////////////////////////////////////////////
    /// \brief Draw a wall.
    ///
    /// \param eWallType  Orientation of the wall.
    ///        fX         X coordinate of the wall.
    ///        fY         Y coordinate of the wall.
    ///        fScale     Scale value of the wall (1.f by default).
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( Tiles::WallType eWallType, GLfloat fX, GLfloat fY, GLfloat fScale = 1.f );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the textures coords of the wall.
    ///
    /// \param sfTexRect  Position and size the subtexture.
    ///
    ////////////////////////////////////////////////////////////
    void SetTexCoords ( sf::IntRect sfTexRect );
};

#endif // WALL_HPP__
