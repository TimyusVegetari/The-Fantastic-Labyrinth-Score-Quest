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
 * \file TilesManager.hpp
 * \brief Class to manage the tiles.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2016-2017
 *
 */

#ifndef TILESMANAGER_HPP__
#define TILESMANAGER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Decoration.hpp"
#include "Shadow.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to store and manage the tiles.
///
////////////////////////////////////////////////////////////
class TilesManager : private sf::NonCopyable {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<Decoration*>  m_vDecorations;   ///< Vector of decorations.
    Shadow*                   m_poShadows;      ///< Shadows of the labyrinth.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a tiles manager.
    ///
    ////////////////////////////////////////////////////////////
    explicit TilesManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the tiles manager.
    ///
    ////////////////////////////////////////////////////////////
    ~TilesManager ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the tiles.
    ///
    /// \param stContext    Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    void Initialize ( GameObject::ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Draw a ground tile.
    ///
    /// \param uiStep     Number of the current levels step.
    ///        uiSubLevel Number of the current level in the step.
    ///        fX         X coordinate of the tile.
    ///        fY         Y coordinate of the tile.
    ///        fScale     Scale value of the tile (1.f by default).
    ///
    ////////////////////////////////////////////////////////////
    void DrawGround ( GLuint uiStep, GLuint uiSubLevel, GLfloat fX, GLfloat fY, GLfloat fScale = 1.f );

    ////////////////////////////////////////////////////////////
    /// \brief Draw a wall tile.
    ///
    /// \param uiStep     Number of the current levels step.
    ///        uiSubLevel Number of the current level in the step.
    ///        eWallType  Type of the wall to draw.
    ///        fX         X coordinate of the tile.
    ///        fY         Y coordinate of the tile.
    ///        fScale     Scale value of the tile (1.f by default).
    ///
    ////////////////////////////////////////////////////////////
    void DrawWall ( GLuint uiStep, GLuint uiSubLevel, Tiles::WallType eWallType, GLfloat fX, GLfloat fY, GLfloat fScale = 1.f );

    ////////////////////////////////////////////////////////////
    /// \brief Draw a shadow tile.
    ///
    /// \param eShadowType  Type of the shadow to draw.
    ///        uiAlpha      Alpha of the tile for transparence.
    ///        fX           X coordinate of the tile.
    ///        fY           Y coordinate of the tile.
    ///        fScale       Scale value of the tile (1.f by default).
    ///
    ////////////////////////////////////////////////////////////
    void DrawShadow ( Tiles::ShadowType eShadowType, GLuint uiAlpha, GLfloat fX, GLfloat fY, GLfloat fScale = 1.f );
};

#endif // TILESMANAGER_HPP__
