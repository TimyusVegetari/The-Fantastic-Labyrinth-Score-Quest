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
 * \file GOWorldView.hpp
 * \brief Class for the view of the world.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2016
 *
 */

#ifndef GOWORLDVIEW_HPP__
#define GOWORLDVIEW_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include <Game/GameEngine/GameObjects/GameObject2D.hpp>

////////////////////////////////////////////////////////////
/// \brief Class for the view of the world.
///
////////////////////////////////////////////////////////////
class GOWorldView : public GameObject, public GameObject2D, public sf::View {

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::FloatRect   m_sfViewportRect;     ///< Rectangle of the viewport.
    sf::Vector2f    m_sfScale;            ///< Vector of a render target scale.
    sf::Vector2f    m_sfRenderTargetSize; ///< Vector of a render target size.
    sf::Sprite      m_sfBorders[9];       ///< Sprites to draw the borders of the game area.

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
    GOWorldView ( ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the game object.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GOWorldView ( void );

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
    /// \brief Compute the center of the view in the world in function of view size.
    ///
    /// \param uiX  X value of the position of the player.
    ///        uiY  Y value of the position of the player.
    ///
    ////////////////////////////////////////////////////////////
    void Scrolling ( GLfloat fX, GLfloat fY, GLfloat fWidth, GLfloat fHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the object.
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the center of the view in the world.
    ///
    /// \param fX   X value of the center of the view in the world.
    ///        fY   Y value of the center of the view in the world.
    ///
    ////////////////////////////////////////////////////////////
    void SetCenter ( GLfloat fX, GLfloat fY ) { setCenter (fX, fY); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the scale of the view in the world.
    ///
    /// \param fScaleX  Scale value of the width of the view.
    ///        fScaleY  Scale value of the height of the view.
    ///
    ////////////////////////////////////////////////////////////
    void SetScale ( GLfloat fScaleX, GLfloat fScaleY );

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the view in the world.
    ///
    /// \param fWidth   Width value of the view in the world.
    ///        fHeight  Height value of the view in the world.
    ///
    ////////////////////////////////////////////////////////////
    void SetSize ( GLfloat fWidth, GLfloat fHeight ) { setSize ((fWidth-20.f)*m_sfScale.x, (fHeight-20.f)*m_sfScale.y); }

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of a render target.
    ///
    /// \param fWidth   Width value of the render target.
    ///        fHeight  Height value of the render target.
    ///
    ////////////////////////////////////////////////////////////
    void SetRenderTargetSize ( GLfloat fWidth, GLfloat fHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Set the viewport of the view.
    ///
    /// \param fLeft    Left value of the position of the viewport.
    ///        fTop     Top value of the position of the viewport.
    ///
    ////////////////////////////////////////////////////////////
    void SetViewport ( GLfloat fLeft, GLfloat fTop, GLfloat fWidth, GLfloat fHeight );

};

#endif // GOWORLDVIEW_HPP__
