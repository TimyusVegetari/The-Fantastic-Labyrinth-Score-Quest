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
 * \file FoodTypes.hpp
 * \brief Enumeration of IDs for the food types.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef FOODTYPES_HPP__
#define FOODTYPES_HPP__

////////////////////////////////////////////////////////////
/// \brief Enumeration of identifiers for the food types.
///
////////////////////////////////////////////////////////////
namespace Foods {

enum Type {
  Fruit,
  Bread,
  VegetableSoup,
  Count
};

}

#endif // FOODTYPES_HPP__
