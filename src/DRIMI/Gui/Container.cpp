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
#include <DRIMI/Gui/Container.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
drimi::Gui::Container::Container ( void ) :
  drimi::Gui::Component (),
  m_oChildren           (),
  m_iSelectedChild      (-1)
{
}

////////////////////////////////////////////////////////////
drimi::Gui::Container::~Container ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void drimi::Gui::Container::Select ( void ) {
  drimi::Gui::Component::Select ();
	if (HasSelection () && m_oChildren[m_iSelectedChild]->IsSelectable ()) {
    // Select the new component.
		m_oChildren[m_iSelectedChild]->Select ();
	}
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::Deselect ( void ) {
  drimi::Gui::Component::Deselect ();
	if (HasSelection () && m_oChildren[m_iSelectedChild]->IsSelectable ()) {
    // Deselect the current selected component.
		m_oChildren[m_iSelectedChild]->Deselect ();
	}
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::Pack ( Component::Ptr pComponent ) {
  m_oChildren.push_back (pComponent);

  // If container has no selection and the component
  // is selectable then select it.
  if (!HasSelection () && pComponent->IsSelectable ())
    Select (m_oChildren.size ()-1);
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Container::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  // If a child is selected then give it events.
  if (HasSelection ()) {
    m_oChildren[m_iSelectedChild]->HandleEvent (eEventType, sfKeyCode);
  }
  if (eEventType == drimi::Event::Type::KeyPressed) {
    if (sfKeyCode == sf::Keyboard::Up)
			SelectPrevious ();
		else if (sfKeyCode == sf::Keyboard::Down)
			SelectNext ();
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Container::HandleTextUnicode ( const char cUnicode ) {
  // If a child is selected then give it text unicode.
  if (HasSelection () && m_oChildren[m_iSelectedChild]->IsActive ()) {
    m_oChildren[m_iSelectedChild]->HandleTextUnicode (cUnicode);
  }

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::Update ( void ) {
  // If a child is selected then update it.
  if (HasSelection () && m_oChildren[m_iSelectedChild]->IsActive ()) {
    m_oChildren[m_iSelectedChild]->Update ();
  }
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::draw ( sf::RenderTarget& target, sf::RenderStates states ) const {
  states.transform *= getTransform ();

	// Draw all the components from bottom to top
	for (auto it = m_oChildren.begin () ; it != m_oChildren.end () ; ++it) {
    target.draw ((*(*it)), states);
  }
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::Draw ( sf::RenderTarget& sfTarget, sf::RenderStates sfStates ) {
  draw (sfTarget, sfStates);
}

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Container::HasSelection ( void ) const {
	return m_iSelectedChild >= 0;
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::Select ( std::size_t iIndex ) {
	if (m_oChildren[iIndex]->IsSelectable ()) {
    // Deselect the current selected component.
		if (HasSelection ())
			m_oChildren[m_iSelectedChild]->Deselect ();
    // Select the new component.
		m_oChildren[iIndex]->Select ();
		m_iSelectedChild = iIndex;
	}
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::SelectNext ( void ) {
  // If container has no selection, break.
	if (!HasSelection ())
		return;

	// Search next component that is selectable, wrap around if necessary.
	GLint iNext = m_iSelectedChild;
	do {
		iNext = (iNext+1) % m_oChildren.size ();
	} while (!m_oChildren[iNext]->IsSelectable());

	// Select that component.
	Select (iNext);
}

////////////////////////////////////////////////////////////
void drimi::Gui::Container::SelectPrevious ( void ) {
  // If container has no selection, break.
	if (!HasSelection ())
		return;

	// Search previous component that is selectable, wrap around if necessary.
	GLint iPrevious = m_iSelectedChild;
	do {
		iPrevious = (iPrevious+m_oChildren.size ()-1) % m_oChildren.size ();
	} while (!m_oChildren[iPrevious]->IsSelectable());

	// Select that component.
	Select (iPrevious);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean drimi::Gui::Container::IsSelectable ( void ) const {
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLint drimi::Gui::Container::GetSelection ( void ) {
  return m_iSelectedChild;
}
