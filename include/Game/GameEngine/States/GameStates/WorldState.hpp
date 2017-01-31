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
 * \file WorldState.hpp
 * \brief Class to define the world state of the game.
 * \author Anthony Acroute
 * \version 0.6
 * \date 2016-2017
 *
 */

#ifndef WORLDSTATE_HPP__
#define WORLDSTATE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../State.hpp"
#include <Game/includes.hpp>
#include <Game/GameObjects/WorldState/GOWorldView.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the world state of the game.
/// This state contain the world, objets, creatures, etc...
/// It's here that the player plays in the 3D world.
///
////////////////////////////////////////////////////////////
class WorldState : public State {

  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint            m_uiRenderList2D_ID;
    GameObjects::ID   m_uiTerrain;
    GameObjects::ID   m_uiPlayer;
    sf::Sprite        m_sfMainBoard[3];
    // Food inventory
    sf::Sprite        m_sfInventory;
    GLuint*           m_uiInventory;
    drimi::Gui::Container m_oInventoryContainer;
    GLboolean         m_bFoodCollecting;
    GLint             m_iScoreWonTime;
    drimi::BmpText    m_oScoreWon;

    GLuint            m_uiLevel_ID;
    GLuint            m_uiScoreTexts_ID;
    GLuint            m_uiTotalScore_ID;
    GLuint            m_uiCurrentScore_ID;
    sf::View          m_sfMainView;
    GOWorldView       m_oGOWorldView;
    GLboolean         m_bScrolling;
    GLboolean         m_bGameOver;
    GLboolean         m_bEndGame;
    GLboolean         m_bNDA_Increment;     ///< Variable to in/decrement the color of the screen
    sf::Uint8         m_uiRedAlert;         ///< background during the near death alert.

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a world state.
    ///
    ////////////////////////////////////////////////////////////
    WorldState ( StateStack& oStack, ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~WorldState ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the state.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Upgrade all the composants of the state when
    /// the render target view is resized.
    ///
    ////////////////////////////////////////////////////////////
    virtual void ResizeView ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Draw ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Call all the update of the components of the state.
    ///
    /// \return True to permit the other states to be updated, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Update ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the state.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode );

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the state.
    ///
    /// \return True to permit the inputs of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void );

    ////////////////////////////////////////////////////////////
    /// \brief What do we do when the player eat a food ?
    ///
    ////////////////////////////////////////////////////////////
    void FoodEating ( void );

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the main render window of the game.
    ///
    /// \return The main render window of the game
    ///
    ////////////////////////////////////////////////////////////
    gm::RenderWindow& GetMainWindow ( void );
};

#endif // WORLDSTATE_HPP__
