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
 * \file GameObject.hpp
 * \brief Class for the game objects.
 * \author Anthony Acroute
 * \version 0.4
 * \date 2016
 *
 */

#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <Game/GameEngine/RenderTargets/RenderTargetsManager.hpp>
#include <Game/GameEngine/GraphicsEngine/GraphicsEngine.hpp>
#include <DRIMI/Utils/EventTypes.hpp>
#include "GameObjectIdentifiers.hpp"
#include <Game/GameEngine/LevelsManager.hpp>
#include <Game/GameEngine/ScoreBoard.hpp>
#include <Game/GameEngine/States/GameStates/StateIdentifiers.hpp>

class StateStack;
class GameObjectsManager;
class TilesManager;
class FoodsManager;

////////////////////////////////////////////////////////////
/// \brief Class to create game objects like as players,
/// creatures, equipments, vehicules, etc...
///
////////////////////////////////////////////////////////////
class GameObject {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<GameObject> Ptr;  ///< Unique pointer of game object.

    ////////////////////////////////////////////////////////////
    /// \brief Structure defining a unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    struct ST_Context {
      const GLuint&         m_uiElapsedTime;          ///< Reference of the absolute elapsed time of the game.
			RenderTargetsManager&	m_oRenderTargetsManager;  ///< Reference of the render targets manager of the game.
			drimi::BmpFont&       m_oBmpFont;               ///< Reference of the bitmap font of the game.
      GraphicsEngine&       m_oGraphicsEngine;        ///< Reference of the graphics engine of the game.
      StateStack&           m_oStateStack;            ///< Reference of the state stack.
			GameObjectsManager&   m_oGameObjectsManager;    ///< Reference of the game objects manager.
			LevelsManager&        m_oLevelsManager;         ///< Reference of the game levels manager.
      TilesManager&         m_oTilesManager;          ///< Reference of the game tiles manager.
      ScoreBoard&           m_oScoreBoard;            ///< Reference of the game score board.
      FoodsManager&         m_oFoodsManager;          ///< Reference of the game foods manager.

			ST_Context  ( const GLuint& uiElapsedTime,
                    RenderTargetsManager&	oRenderTargetsManager,
                    drimi::BmpFont& oBmpFont,
                    GraphicsEngine& oGraphicsEngine,
                    StateStack& oStateStack,
                    GameObjectsManager& oGameObjectsManager,
                    LevelsManager& oLevelsManager,
                    TilesManager& oTilesManager,
                    ScoreBoard& oScoreBoard,
                    FoodsManager& oFoodsManager );
      const GLuint& GetElapsedTime ( void );
      RenderList2D& GetRenderList2D ( GLuint uiRenderList2D_ID );
      StateStack& GetStateStack ( void );
      GameObjectsManager& GetGameObjectsManager ( void );
      LevelsManager& GetLevelsManager ( void );
      TilesManager& GetTilesManager ( void );
      ScoreBoard& GetScoreBoard ( void );
      FoodsManager& GetFoodsManager ( void );
    };

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ST_Context&       m_stContext;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a game object.
    ///
    ////////////////////////////////////////////////////////////
    GameObject ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GameObject ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the game object.
    ///
    /// \return True if the initialization is not finish, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean Initialize ( void ) {return GL_TRUE;};

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for all the components of the game object.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {return GL_TRUE;};

    ////////////////////////////////////////////////////////////
    /// \brief Transmit a unicode text to the game object.
    ///
    /// \param cUnicode   The current text unicode.
    ///
    /// \return True to permit the text unicode transmission of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleTextUnicode ( const char cUnicode ) {return GL_TRUE;};

    ////////////////////////////////////////////////////////////
    /// \brief Check the inputs for all the components of the game object.
    ///
    /// \return True to permit the inputs of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleInput ( void ) {return GL_TRUE;};

  protected :
    ////////////////////////////////////////////////////////////
    /// \brief Add a state on the top of the state stack.
    ///
    /// \param sStateID   Value to identify a specific state.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStackPush ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Remove a state of the state stack.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStackPop ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Replace a state on the top of the state stack by a new state.
    ///
    /// \param sStateID   Value to identify the new state.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStackReplace ( States::ID eStateID );

    ////////////////////////////////////////////////////////////
    /// \brief Call the method to clean the state stack.
    ///
    ////////////////////////////////////////////////////////////
    void RequestStateClear ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the unique ressources context of the game
    ///
    /// \return The unique ressources context
    ///
    ////////////////////////////////////////////////////////////
    ST_Context& GetContext ( void ) const;

    ////////////////////////////////////////////////////////////
    // Internal methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the OpenGL manager.
    ///
    /// \return The OpenGL manager.
    ///
    ////////////////////////////////////////////////////////////
    OGLManager& GetOGLManager ( void );
};

#endif // GAMEOBJECT_HPP__
