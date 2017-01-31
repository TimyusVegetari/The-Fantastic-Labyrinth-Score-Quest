////////////////////////////////////////////////////////////
//
// This file is part of DRIMI::Gui.
// Copyright (C) 2013-2016 Acroute Anthony (ant110283@hotmail.fr)
//
// DRIMI::Gui is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// DRIMI::Gui is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DRIMI::Gui.  If not, see <http://www.gnu.org/licenses/>.
//
// A part of the code in this file is inspired by the book
// "SFML Game Development".
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file TextLine.hpp
 * \brief Class for the text line of the gui.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef TEXTLINE_HPP__
#define TEXTLINE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <DRIMI/Gui/Component.hpp>
#include <DRIMI/BitmapFont/BmpFont.hpp>
#include <DRIMI/BitmapFont/BmpText.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

////////////////////////////////////////////////////////////
/// \brief Class to define a text line of the gui.
///
////////////////////////////////////////////////////////////
namespace drimi {
namespace Gui {

class TextLine : public Component {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::shared_ptr<TextLine> Ptr;      ///< Unique pointer of text line.

    enum State {
      Normal,
      Selected,
      Pressed
    }; ///< List of possible States of the text line.

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite	    m_sfBackground;
    drimi::BmpText  m_oBmpText;
    std::string     m_szText;
    GLuint          m_uiMaxTextSize;
    // Cursor of the text line
    drimi::BmpText  m_oBmpCursor;
    char            m_cCursor;
    GLboolean       m_bCursor;
    GLuint          m_uiCursorIndex;
    GLuint          m_uiCursorTimer;
    GLboolean       m_bCursorDisplay;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a text line.
    ///
    ////////////////////////////////////////////////////////////
    TextLine ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the text line.
    ///
    ////////////////////////////////////////////////////////////
    ~TextLine ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Select the text line.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Select ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Deselect the text line.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Deselect ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Activate the text line.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Activate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Deactivate the text line.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Deactivate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for the text line.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other components to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode );

    ////////////////////////////////////////////////////////////
    /// \brief Transmit a unicode text to the text line.
    ///
    /// \param cUnicode   The current text unicode.
    ///
    /// \return True to permit the text unicode transmission of the other states to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleTextUnicode ( const char cUnicode );

    ////////////////////////////////////////////////////////////
    /// \brief Update the text line.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Update ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the text line.
    ///
    /// \param sfTarget   The render target to draw.
    ///        sfStates   The current render states.
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;
    virtual void Draw ( sf::RenderTarget& sfTarget, sf::RenderStates sfStates = sf::RenderStates::Default );

  private :
    ////////////////////////////////////////////////////////////
    /// \brief Update the cursor.
    ///
    ////////////////////////////////////////////////////////////
    void UpdateCursor ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Move the cursor to the left.
    ///
    ////////////////////////////////////////////////////////////
    void MoveCursorLeft ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Move the cursor to the right.
    ///
    ////////////////////////////////////////////////////////////
    void MoveCursorRight ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Animate the cursor to make an effect of blinking.
    ///
    ////////////////////////////////////////////////////////////
    void AnimateCursor ( void );

  public :
    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the position of the text line.
    ///
    /// \param uiX  The X value of the position.
    ///        uiY  The Y value of the position.
    ///
    ////////////////////////////////////////////////////////////
    void SetPosition ( GLfloat fX, GLfloat fY );

    ////////////////////////////////////////////////////////////
    /// \brief Set the background texture.
    ///
    /// \param sfTexture    The texture of the background.
    ///        uiWidth      The width of each texture.
    ///        uiHeight     The height of each texture.
    ///
    ////////////////////////////////////////////////////////////
    void SetBackgroundTexture ( const sf::Texture& sfTexture, GLuint uiWidth, GLuint uiHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Set the color of the text line.
    ///
    /// \param sfTextColor  The color of the text.
    ///
    ////////////////////////////////////////////////////////////
    void SetColor ( sf::Color sfTextColor );

    ////////////////////////////////////////////////////////////
    /// \brief Set the text of the text line.
    ///
    /// \param szText       The text of the text line.
    ///        oBmpFont     The bitmap font of the text.
    ///
    ////////////////////////////////////////////////////////////
    void SetText ( const std::string& szText, drimi::BmpFont& oBmpFont );

    ////////////////////////////////////////////////////////////
    /// \brief Get the text of the text line.
    ///
    /// \return The text of the text line.
    ///
    ////////////////////////////////////////////////////////////
    std::string GetText ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get if the container is selectable or not.
    ///
    /// \return True to if the container is selectable, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean IsSelectable ( void ) const;
};

} // namespace Gui
} // namespace drimi

#endif // TEXTLINE_HPP__
