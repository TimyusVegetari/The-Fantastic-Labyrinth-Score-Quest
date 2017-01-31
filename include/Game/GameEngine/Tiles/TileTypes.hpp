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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file TileTypes.hpp
 * \brief Enumeration of IDs for the tile types.
 * \author Anthony Acroute
 * \version 0.2
 * \date 2016-2017
 *
 */

#ifndef TILETYPES_HPP__
#define TILETYPES_HPP__

#define TILE_WIDTH  32
#define TILE_HEIGHT 32

////////////////////////////////////////////////////////////
/// \brief Enumeration of identifiers for the tile types.
///
////////////////////////////////////////////////////////////
namespace Tiles {

enum Type {
  Ground,
  Wall,
  T_Count
};

enum WallType {
  Vertical,
  Horizontal,
  Cross,
  Point,
  T_Top,
  T_Right,
  T_Down,
  T_Left,
  L_Top,
  L_Right,
  L_Down,
  L_Left,
  I_Top,
  I_Right,
  I_Down,
  I_Left,
  WT_Count
};

enum GroundType {
  GreenBrick,
  GT_Count
};

enum Theme {
  Garden,
  Castle,
  Catacombs,
  Th_Count
};

/*enum Variant {
  Hedge_Oak,
  Hedge_Birch,
  Hedge_Maple,
  Hedge_Cherry
  Hedge_Spruce,
  StoneBrick_Gray,
  StoneBrick_Yellow,
  StoneBrick_Green,
  StoneBrick_Blue,
  StoneBrick_Red,
  V_Count
};*/

enum ShadowType {
  ST_Right_Left,
  ST_Top_Down,
  ST_Cross,
  ST_Down,
  ST_Left,
  ST_Top,
  ST_Right,
  ST_Down_Left,
  ST_Top_Left,
  ST_Top_Right,
  ST_Right_Down,
  ST_Right_Down_Left,
  ST_Top_Down_Left,
  ST_Top_Right_Left,
  ST_Top_Right_Down,
  ST_Count
};

}

#endif // TILETYPES_HPP__
