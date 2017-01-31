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
// along with The Fantastic Labyrinth.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file GameOverState.hpp
 * \brief Class to define the game over state of the game.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef GAMEOVERSTATE_HPP__
#define GAMEOVERSTATE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../State.hpp"
#include <Game/includes.hpp>
#include <DRIMI/Gui/Container.hpp>
#include <DRIMI/Gui/TextLine.hpp>

////////////////////////////////////////////////////////////
/// \brief Class to create the game over state of the game.
/// This state contain the game over message and the final score.
///
////////////////////////////////////////////////////////////
class GameOverState : public State {

  public :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint        m_uiRenderList2D_ID;
    sf::View      m_sfMainView;
    GLuint        m_uiBackGround_ID,
                  m_uiGameOver_ID,
                  m_uiTotalScore_ID,
                  m_uiEndMessage_ID;
    drimi::Gui::Container m_oScoreContainer;
    drimi::Gui::TextLine::Ptr m_poTextLine;
    GLboolean     m_bSaveScore;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a title state.
    ///
    ////////////////////////////////////////////////////////////
    GameOverState ( StateStack& oStack, ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the state.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GameOverState ( void );

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
    /// \brief Transmit a unicode text to the state.
    ///
    /// \param cUnicode   The current text unicode.
    ///
    /// \return True to permit the text unicode transmission of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleTextUnicode ( const GLchar cUnicode );

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the state.
    ///
    /// \return True to permit the inputs of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void );

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

#endif // GAMEOVERSTATE_HPP__
