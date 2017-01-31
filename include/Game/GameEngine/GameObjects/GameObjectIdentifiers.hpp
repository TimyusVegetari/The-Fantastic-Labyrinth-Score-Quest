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
 * \file GameObjectIdentifiers.hpp
 * \brief Enumeration of types of game objects.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef GAMEOBJECTIDENTIFIERS_HPP__
#define GAMEOBJECTIDENTIFIERS_HPP__

////////////////////////////////////////////////////////////
/// \brief Enumeration of identifiers for the game objects.
///
////////////////////////////////////////////////////////////
namespace GameObjects {

typedef GLuint  Initializer;  ///< Identifier of the initializer.
typedef GLuint  ID;           ///< Identifier of game object.

enum Type {
  None,
  // Game objects of the title state
  Title,
  MainMenu,
  License,
  // Game objects of the high score state
  HighScores,
  // Game objects of the world state
  Terrain,
  Player
};

}

#endif // GAMEOBJECTIDENTIFIERS_HPP__
