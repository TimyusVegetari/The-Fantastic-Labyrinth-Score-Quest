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
#include <DRIMI/Gui/TextLine.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
drimi::Gui::TextLine::TextLine ( void ) :
  drimi::Gui::Component (),
  m_sfBackground        (),
  m_oBmpText            (),
  m_szText              (""),
  m_uiMaxTextSize       (16),
  // Cursor of the text line
  m_oBmpCursor          (),
  m_cCursor             (L'_'),
  m_bCursor             (GL_FALSE),
  m_uiCursorIndex       (0),
  m_uiCursorTimer       (0),
  m_bCursorDisplay      (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
drimi::Gui::TextLine::~TextLine ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::Select ( void ) {
  drimi::Gui::Component::Select ();
  m_bCursor = GL_TRUE;
  // Update the cursor appearence
  UpdateCursor ();
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::Deselect ( void ) {
  drimi::Gui::Component::Deselect ();
  m_bCursor = GL_FALSE;
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::Activate ( void ) {
  drimi::Gui::Component::Activate ();
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::Deactivate ( void ) {
  drimi::Gui::Component::Deactivate ();
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::TextLine::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  if (eEventType == drimi::Event::Type::KeyPressed) {
    if (sfKeyCode == sf::Keyboard::Left)
      MoveCursorLeft ();
		else if (sfKeyCode == sf::Keyboard::Right)
      MoveCursorRight ();
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::TextLine::HandleTextUnicode ( const char cUnicode ) {
  if (cUnicode >= 32 && m_szText.size () < m_uiMaxTextSize) {
    m_szText.insert (m_uiCursorIndex, 1, cUnicode);
    m_oBmpText.SetString (m_szText);
    m_oBmpText.SetOrigin (0.f, m_oBmpText.GetLocalBounds ().height / 2.f);
    m_oBmpText.SetOrigin (m_oBmpText.GetLocalBounds ().width / 2.f, m_oBmpText.GetLocalBounds ().height / 2.f);
    // Update the cursor
    m_uiCursorIndex++;
  } else if (cUnicode == 8) { // backspace
    if (m_szText.size () > 0 && m_uiCursorIndex > 0) {
      m_szText.erase (m_uiCursorIndex-1, 1);
      m_oBmpText.SetString (m_szText);
      m_oBmpText.SetOrigin (0.f, m_oBmpText.GetLocalBounds ().height / 2.f);
      m_oBmpText.SetOrigin (m_oBmpText.GetLocalBounds ().width / 2.f, m_oBmpText.GetLocalBounds ().height / 2.f);
      // Update the cursor
      m_uiCursorIndex--;
    }
  }
  // Update the cursor appearence
  UpdateCursor ();

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::Update ( void ) {
	if (m_bCursor)
    AnimateCursor ();
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::draw ( sf::RenderTarget& target, sf::RenderStates states ) const {
  states.transform *= getTransform ();

	// Draw the background and the text.
	target.draw (m_sfBackground, states);
	target.draw (m_oBmpText, states);
	if (m_bCursor && m_bCursorDisplay)
    target.draw (m_oBmpCursor, states);
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::Draw ( sf::RenderTarget& sfTarget, sf::RenderStates sfStates ) {
  draw (sfTarget, sfStates);
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::UpdateCursor ( void ) {
  // If edition is now impossible
  if (m_szText.size () == m_uiMaxTextSize) {
    if (m_cCursor == L'_')
      m_cCursor = L'|';
  // If edition is now possible
  } else if (m_cCursor == L'|')
    m_cCursor = L'_';
  m_oBmpCursor.SetString (m_cCursor);
  if (m_szText.size () == 0)
    m_oBmpCursor.SetOrigin (m_oBmpCursor.GetLocalBounds ().width / 2.f, m_oBmpCursor.GetLocalBounds ().height / 2.f);
  else
    m_oBmpCursor.SetOrigin (0.f, 0.f);
  sf::Vector2f sfCursorPos = m_oBmpText.FindCharacterPos (m_uiCursorIndex);
  m_oBmpCursor.setPosition (sfCursorPos);
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::MoveCursorLeft ( void ) {
  // If the cursor isn't totaly to the left, update it
  if (m_uiCursorIndex > 0) {
    m_uiCursorIndex--;
    // Update the cursor appearence
    UpdateCursor ();
  }
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::MoveCursorRight ( void ) {
  // If the cursor isn't totaly to the right, update it
  if (m_uiCursorIndex < m_szText.size ()) {
    m_uiCursorIndex++;
    // Update the cursor appearence
    UpdateCursor ();
  }
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::AnimateCursor ( void ) {
  if (m_uiCursorTimer == 30) {
    m_bCursorDisplay = GL_FALSE;
    m_uiCursorTimer = 0;
  } else {
    if (m_uiCursorTimer == 15)
      m_bCursorDisplay = GL_TRUE;
    m_uiCursorTimer++;
  }
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::SetPosition ( GLfloat fX, GLfloat fY ) {
	sf::FloatRect sfBounds = m_sfBackground.getLocalBounds ();
  m_sfBackground.setOrigin (sf::Vector2f (sfBounds.width / 2.f, sfBounds.height / 2.f));
	m_sfBackground.setPosition (fX, fY);

  m_oBmpText.SetOrigin (m_oBmpText.GetLocalBounds ().width / 2.f, m_oBmpText.GetLocalBounds ().height / 2.f);
	m_oBmpText.setPosition (fX, fY);
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::SetBackgroundTexture ( const sf::Texture& sfTexture, GLuint uiWidth, GLuint uiHeight ) {
  m_sfBackground.setTexture (sfTexture);
  m_sfBackground.setTextureRect (sf::IntRect (0, 0, uiWidth, uiHeight));
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::SetColor ( sf::Color sfTextColor ) {
  m_oBmpText.SetColor (sfTextColor);
  m_oBmpCursor.SetColor (sfTextColor);
}

////////////////////////////////////////////////////////////
void drimi::Gui::TextLine::SetText ( const std::string& szText, drimi::BmpFont& oBmpFont ) {
  m_szText                = szText;
  m_oBmpText.SetFont      (oBmpFont);
  m_oBmpText.SetString    (szText);
  m_oBmpCursor.SetFont    (oBmpFont);
  m_oBmpCursor.SetStyle   (sf::Text::Style::Bold);
}

////////////////////////////////////////////////////////////
std::string drimi::Gui::TextLine::GetText ( void ) {
  return m_szText;
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::TextLine::IsSelectable ( void ) const {
  return GL_TRUE;
}
