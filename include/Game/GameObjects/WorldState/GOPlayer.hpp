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
 * \file GOPlayer.hpp
 * \brief Class for the player of the game.
 * \author Anthony Acroute
 * \version 0.3
 * \date 2016-2017
 *
 */

#ifndef GOPLAYER_HPP__
#define GOPLAYER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObject2D.hpp>
#include <Game/GameEngine/GraphicsEngine/Renderer2D/AnimatedSprite.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the player.
///
////////////////////////////////////////////////////////////
class GOPlayer : public GameObject, public GameObject2D {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint    m_uiCharacter_ID;
    AnimatedSprite  m_oCharacterWalking,
                    m_oCharacterRunning;
    GLuint    m_uiX, m_uiY;               ///< Position of the player in terrain coordinates.
    GLboolean m_bMoved,                   ///< Boolean to check if the player has moved.
              m_bRunning,                 ///< Boolean to check if the player is running.
              m_bDrawWalking,             ///< Boolean to check if the walking animation must be drawn.
              m_bDrawRunning;             ///< Boolean to check if the running animation must be drawn.
    GLint     m_iMoveX, m_iMoveY;         ///< Movement of the player in terrain coordinates.
    GLfloat   m_fMoveX, m_fMoveY;         ///< Movement of the player in pixels.


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
    GOPlayer ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GOPlayer ( void );

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
    /// \brief Call all the update of the components of the game object.
    ///
    /// \return True to permit the other game objects to be updated, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Update ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the game object.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other game objects to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) { return GL_FALSE; }

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the game object.
    ///
    /// \return True to permit the inputs of the other game objects to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the state.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Clear the movement.
    ///
    ////////////////////////////////////////////////////////////
    void ClearMove ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the position of the player.
    ///
    /// \param uiX  X value of the position of the player.
    ///        uiY  Y value of the position of the player.
    ///
    ////////////////////////////////////////////////////////////
    void SetPosition ( GLuint uiX, GLuint uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the player.
    ///
    /// \param uiX  Variable to get the X value of the position of the player.
    ///        uiY  Variable to get the Y value of the position of the player.
    ///
    ////////////////////////////////////////////////////////////
    void GetPosition ( GLuint& uiX, GLuint& uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Get the potential position of the player after movement.
    ///
    /// \param uiX  Variable to get the X value of the potential position of the player.
    ///        uiY  Variable to get the Y value of the potential position of the player.
    ///
    /// \return True there is a movement, or false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean GetMovePosition ( GLuint& uiX, GLuint& uiY );

    ////////////////////////////////////////////////////////////
    /// \brief Get the center of the player in pixels.
    ///
    /// \param fX   X of the center of the player in pixels.
    ///        fY   Y of the center of the player in pixels.
    ///
    ////////////////////////////////////////////////////////////
    void GetCenterInPixels ( GLfloat& fX, GLfloat& fY );

    ////////////////////////////////////////////////////////////
    /// \brief Check if the player is moving.
    ///
    /// \return True if the player is moving, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean IsMoving ( void );

};

#endif // GOPLAYER_HPP__
