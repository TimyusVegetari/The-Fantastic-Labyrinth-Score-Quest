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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file GOLicense.hpp
 * \brief Class for the title of the game.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef GOLICENSE_HPP__
#define GOLICENSE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObject2D.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the license informations for the title of the game.
///
////////////////////////////////////////////////////////////
class GOLicense : public GameObject, public GameObject2D {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint    m_uiVersion_ID,
              m_uiLicense_ID;

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
    GOLicense ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GOLicense ( void );

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
};

#endif // GOLICENSE_HPP__
