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
 * \file Shadow.hpp
 * \brief Class for the shadow objects.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2017
 *
 */

#ifndef SHADOW_HPP__
#define SHADOW_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include "TileTypes.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to create shadow object for the light in the labyrinth.
///
////////////////////////////////////////////////////////////
class Shadow {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<Shadow>  Ptr; ///< Unique pointer of shadow.

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GameObject::ST_Context&   m_stContext;
    sf::Sprite                m_sfShadow[Tiles::ShadowType::ST_Count];
    sf::Sprite                m_sfTorch[Tiles::ShadowType::ST_Count];

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a shadow.
    ///
    /// \param stContext  Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    Shadow ( GameObject::ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the shadow.
    ///
    ////////////////////////////////////////////////////////////
    ~Shadow ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the shadow.
    ///
    /// \param uiShadowTexID  Value to identify the texture of the shadows.
    ///        uiTorchTexID   Value to identify the texture of the torches.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( GLuint uiShadowTexID, GLuint uiTorchTexID );

    ////////////////////////////////////////////////////////////
    /// \brief Draw a shadow and a torch.
    ///
    /// \param eShadowType  Type of the shadow to draw.
    ///        uiAlpha      Alpha of the tile for transparence.
    ///        fX           X coordinate of the tile.
    ///        fY           Y coordinate of the tile.
    ///        fScale       Scale value of the tile (1.f by default).
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( Tiles::ShadowType eShadowType, GLuint uiAlpha, GLfloat fX, GLfloat fY, GLfloat fScale = 1.f );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the textures coords of the shadow.
    ///
    /// \param sfTexRect  Position and size the subtexture.
    ///
    ////////////////////////////////////////////////////////////
    void SetTexCoords ( sf::IntRect sfTexRect );
};

#endif // SHADOW_HPP__
