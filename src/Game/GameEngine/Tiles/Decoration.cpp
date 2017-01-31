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
// along with The Fantastic Labyrinth.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/Tiles/Decoration.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Decoration::Decoration ( GameObject::ST_Context& stContext ) :
  m_stContext (stContext),
  m_oGround   (stContext),
  m_oWall     (stContext)
{
}

////////////////////////////////////////////////////////////
Decoration::~Decoration ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean Decoration::Initialize ( GLuint uiGroundTexID, GLuint uiWallTexID ) {
  m_oGround.Initialize (uiGroundTexID);
  m_oWall.Initialize (uiWallTexID);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void Decoration::SetGroundTexCoords ( GLint iLeft, GLint iTop, GLint iWidth, GLint iHeight ) {
  sf::IntRect sfTexRect;
  sfTexRect.width   = iWidth;
  sfTexRect.height  = iHeight;
  sfTexRect.left    = iLeft;
  sfTexRect.top     = iTop;
  m_oGround.SetTexCoords (sfTexRect);
}

////////////////////////////////////////////////////////////
void Decoration::SetWallTexCoords ( GLint iLeft, GLint iTop, GLint iWidth, GLint iHeight ) {
  sf::IntRect sfTexRect;
  sfTexRect.width   = iWidth;
  sfTexRect.height  = iHeight;
  sfTexRect.left    = iLeft;
  sfTexRect.top     = iTop;
  m_oWall.SetTexCoords (sfTexRect);
}

////////////////////////////////////////////////////////////
Ground& Decoration::GetGround ( void ) {
  return m_oGround;
}

////////////////////////////////////////////////////////////
Wall& Decoration::GetWall ( void ) {
  return m_oWall;
}
