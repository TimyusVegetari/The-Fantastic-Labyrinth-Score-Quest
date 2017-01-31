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
 * \file Decoration.hpp
 * \brief Class for the decoration objects.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2017
 *
 */

#ifndef DECORATION_HPP__
#define DECORATION_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include "Ground.hpp"
#include "Wall.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to create decoration object like as a oak garden,
/// a blue castle room, etc...
///
////////////////////////////////////////////////////////////
class Decoration {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<Decoration>  Ptr; ///< Unique pointer of decoration.

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GameObject::ST_Context& m_stContext;
    Ground                  m_oGround;
    Wall                    m_oWall;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a decoration.
    ///
    /// \param stContext  Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    Decoration ( GameObject::ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the decoration.
    ///
    ////////////////////////////////////////////////////////////
    ~Decoration ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the decoration.
    ///
    /// \param uiGroundTexID  Value to identify the texture of the ground.
    ///        uiWallTexID    Value to identify the texture of the wall.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( GLuint uiGroundTexID, GLuint uiWallTexID );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the textures coords of the ground, wall, etc...
    ///
    /// \param iLeft    Left of the texture.
    ///        iTop     Top of the texture.
    ///        iWidth   Width of the texture.
    ///        iHeight  Height of the texture.
    ///
    ////////////////////////////////////////////////////////////
    void SetGroundTexCoords ( GLint iLeft, GLint iTop, GLint iWidth, GLint iHeight );
    void SetWallTexCoords ( GLint iLeft, GLint iTop, GLint iWidth, GLint iHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Get the textures coords of the ground, wall, etc...
    ///
    /// \return The coords of the texture.
    ///
    ////////////////////////////////////////////////////////////
    Ground& GetGround ( void );
    Wall& GetWall ( void );
};

#endif // DECORATION_HPP__
