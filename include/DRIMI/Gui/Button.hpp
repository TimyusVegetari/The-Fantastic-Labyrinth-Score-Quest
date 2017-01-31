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
 * \file Button.hpp
 * \brief Class for the button of the gui.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef BUTTON_HPP__
#define BUTTON_HPP__

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
/// \brief Class to define a button of the gui.
///
////////////////////////////////////////////////////////////
namespace drimi {
namespace Gui {

class Button : public Component {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::shared_ptr<Button>   Ptr;      ///< Unique pointer of button.
    typedef std::function<void ()>	  Callback; ///< Callback function.

    enum State {
      Normal,
      Selected,
      Pressed
    }; ///< List of possible States of the button.

  private :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    State           m_eState;
    Callback		    m_funcCallback;
    sf::Sprite	    m_sfNormalSprite,
                    m_sfSelectedSprite,
                    m_sfPressedSprite;
    drimi::BmpText  m_oBmpText;
    GLboolean		    m_bIsToggle;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a button.
    ///
    ////////////////////////////////////////////////////////////
    Button ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the button.
    ///
    ////////////////////////////////////////////////////////////
    ~Button ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Select the button.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Select ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Deselect the button.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Deselect ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Activate the button.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Activate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Deactivate the button.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Deactivate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Check the events for the container.
    ///
    /// \param eEventType   The current event type.
    ///        sfKeyCode    The current keyboard key code.
    ///
    /// \return True to permit the events of the other components to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode );

    ////////////////////////////////////////////////////////////
    /// \brief Transmit a unicode text to the container.
    ///
    /// \param cUnicode   The current text unicode.
    ///
    /// \return True to permit the text unicode transmission of the other components to be checked, false else.
    ///
    ////////////////////////////////////////////////////////////
    virtual GLboolean HandleTextUnicode ( const char cUnicode );

    ////////////////////////////////////////////////////////////
    /// \brief Draw all the composants of the container.
    ///
    /// \param sfTarget   The render target to draw.
    ///        sfStates   The current render states.
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw ( sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void Draw ( sf::RenderTarget& sfTarget, sf::RenderStates sfStates = sf::RenderStates::Default );

  public :
    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the origin of the button.
    ///
    /// \param uiX  The X value of the origin.
    ///        uiY  The Y value of the origin.
    ///
    ////////////////////////////////////////////////////////////
    void SetOrigin ( GLfloat fX, GLfloat fY );

    ////////////////////////////////////////////////////////////
    /// \brief Set the position of the button.
    ///
    /// \param uiX  The X value of the position.
    ///        uiY  The Y value of the position.
    ///
    ////////////////////////////////////////////////////////////
    void SetPosition ( GLfloat fX, GLfloat fY );

    ////////////////////////////////////////////////////////////
    /// \brief Set the background textures.
    ///
    /// \param sfTextures   The textures of the background.
    ///        uiWidth      The width of each texture.
    ///        uiHeight     The height of each texture.
    ///
    ////////////////////////////////////////////////////////////
    void SetBackgroundTextures ( const sf::Texture& sfTextures, GLuint uiWidth, GLuint uiHeight );

    ////////////////////////////////////////////////////////////
    /// \brief Set the callback function.
    ///
    /// \param funcCallback   The callback function.
    ///
    ////////////////////////////////////////////////////////////
    void SetCallback ( Callback funcCallback );

    ////////////////////////////////////////////////////////////
    /// \brief Set the text of the button.
    ///
    /// \param szText       The text of the button.
    ///        oBmpFont     The bitmap font of the text.
    ///        sfTextColor  The color of the text.
    ///
    ////////////////////////////////////////////////////////////
    void SetText ( const std::string& szText, drimi::BmpFont& oBmpFont, sf::Color sfTextColor );

    ////////////////////////////////////////////////////////////
    /// \brief Set the toggle of the button.
    ///
    /// \param bFlag  The flag to define the toggle.
    ///
    ////////////////////////////////////////////////////////////
    void SetToggle ( GLboolean bFlag );

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

#endif // BUTTON_HPP__
