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
 * \file Food.hpp
 * \brief Class for the food objects.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2016
 *
 */

#ifndef FOOD_HPP__
#define FOOD_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GameObjects/GameObject.hpp>
#include "FoodTypes.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to create food object like as a fruit,
/// a bread, a vegetable soup, etc...
///
////////////////////////////////////////////////////////////
class Food {

  public :
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::unique_ptr<Food>  Ptr; ///< Unique pointer of food.

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GameObject::ST_Context&   m_stContext;
    sf::Sprite                m_sfSprite;
    GLint                     m_iScore;

  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a food.
    ///
    /// \param stContext  Unique ressources context.
    ///
    ////////////////////////////////////////////////////////////
    Food ( GameObject::ST_Context& stContext );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the food.
    ///
    ////////////////////////////////////////////////////////////
    ~Food ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the the food.
    ///
    /// \param uiFoodTexID  Value to identify the texture of the foods.
    ///        sfTexRect    Position and size of the subtexture of the food.
    ///        iScore       Value of the score provided by the food.
    ///
    /// \return True if the initialization is succeed, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( GLuint uiFoodTexID, sf::IntRect sfTexRect, GLint iScore );

    ////////////////////////////////////////////////////////////
    /// \brief Draw a food.
    ///
    /// \param fX       X coordinate of the food.
    ///        fY       Y coordinate of the food.
    ///        fScale   Scale value of the food (1.f by default).
    ///
    ////////////////////////////////////////////////////////////
    void Draw ( GLfloat fX, GLfloat fY, GLfloat fScale = 1.f );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the score provided by the food.
    ///
    ////////////////////////////////////////////////////////////
    GLint GetScore ( void );
};

#endif // FOOD_HPP__
