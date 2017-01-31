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
// Headers
////////////////////////////////////////////////////////////
#include <DRIMI/Gui/Button.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
drimi::Gui::Button::Button ( void ) :
  drimi::Gui::Component (),
  m_eState              (drimi::Gui::Button::State::Normal),
  m_funcCallback        (),
  m_sfNormalSprite      (),
  m_sfSelectedSprite    (),
  m_sfPressedSprite     (),
  m_oBmpText            (),
  m_bIsToggle           (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
drimi::Gui::Button::~Button ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void drimi::Gui::Button::Select ( void ) {
  drimi::Gui::Component::Select ();
  m_eState = drimi::Gui::Button::State::Selected;
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::Deselect ( void ) {
  drimi::Gui::Component::Deselect ();
  m_eState = drimi::Gui::Button::State::Normal;
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::Activate ( void ) {
  drimi::Gui::Component::Activate ();
  // If we are toggle then we should show that the button is pressed and thus "toggled".
  if (m_bIsToggle)
    m_eState = drimi::Gui::Button::State::Pressed;
  if (m_funcCallback)
    m_funcCallback ();
  // If we are not a toggle then deactivate the button since we are just momentarily activated.
  if (!m_bIsToggle)
    Deactivate ();
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::Deactivate ( void ) {
  drimi::Gui::Component::Deactivate ();
  if (m_bIsToggle) {
    // Reset texture to right one depending on if we are selected or not.
    if (IsSelected ())
      m_eState = drimi::Gui::Button::State::Selected;
    else
      m_eState = drimi::Gui::Button::State::Normal;
  }
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Button::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  if (sfKeyCode == sf::Keyboard::Return) {
    if (!IsActive ())
      Activate ();
    else
      Deactivate ();
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Button::HandleTextUnicode ( const char cUnicode ) {
  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::draw ( sf::RenderTarget& target, sf::RenderStates states ) const {
  states.transform *= getTransform ();

	// Draw the background and the text.
	if (m_eState == drimi::Gui::Button::State::Selected)
    target.draw (m_sfSelectedSprite, states);
	else if (m_eState == drimi::Gui::Button::State::Pressed)
    target.draw (m_sfPressedSprite, states);
  else
    target.draw (m_sfNormalSprite, states);
	target.draw (m_oBmpText, states);
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::Draw ( sf::RenderTarget& sfTarget, sf::RenderStates sfStates ) {
  draw (sfTarget, sfStates);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void drimi::Gui::Button::SetOrigin ( GLfloat fX, GLfloat fY ) {
  m_sfNormalSprite.setOrigin    (sf::Vector2f (fX, fY));
  m_sfSelectedSprite.setOrigin  (sf::Vector2f (fX, fY));
  m_sfPressedSprite.setOrigin   (sf::Vector2f (fX, fY));
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::SetPosition ( GLfloat fX, GLfloat fY ) {
	m_sfNormalSprite.setPosition    (fX, fY);
	m_sfSelectedSprite.setPosition  (fX, fY);
	m_sfPressedSprite.setPosition   (fX, fY);

  m_oBmpText.SetOrigin(m_oBmpText.GetLocalBounds ().width / 2.f, m_oBmpText.GetLocalBounds ().height / 2.f);
	m_oBmpText.setPosition (fX, fY);
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::SetBackgroundTextures ( const sf::Texture& sfTextures, GLuint uiWidth, GLuint uiHeight ) {
  m_sfNormalSprite.setTexture (sfTextures);
  m_sfNormalSprite.setTextureRect (sf::IntRect (0, 0, uiWidth, uiHeight));
  m_sfSelectedSprite.setTexture (sfTextures);
  m_sfSelectedSprite.setTextureRect (sf::IntRect (0, uiHeight, uiWidth, uiHeight));
  m_sfPressedSprite.setTexture (sfTextures);
  m_sfPressedSprite.setTextureRect (sf::IntRect (0, 2*uiHeight, uiWidth, uiHeight));
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::SetCallback ( Callback funcCallback ) {
  m_funcCallback = funcCallback;
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::SetText ( const std::string& szText, drimi::BmpFont& oBmpFont, sf::Color sfTextColor ) {
  m_oBmpText.SetFont (oBmpFont);
  m_oBmpText.SetColor (sfTextColor);
  m_oBmpText.SetString (szText);
}

////////////////////////////////////////////////////////////
void drimi::Gui::Button::SetToggle ( GLboolean bFlag ) {
  m_bIsToggle = bFlag;
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Button::IsSelectable ( void ) const {
  return GL_TRUE;
}
