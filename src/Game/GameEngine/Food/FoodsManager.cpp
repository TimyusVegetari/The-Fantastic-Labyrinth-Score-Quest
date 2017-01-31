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
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/Food/FoodsManager.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
FoodsManager::FoodsManager ( void ) :
  m_oFoodTypes    (nullptr)
{
}

////////////////////////////////////////////////////////////
FoodsManager::~FoodsManager ( void ) {
  if (m_oFoodTypes != nullptr)
    delete[] m_oFoodTypes;
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void FoodsManager::Initialize ( GameObject::ST_Context& stContext ) {
  // Creating the food types.
  m_oFoodTypes = new Food[Foods::Type::Count] {{stContext},{stContext},{stContext}};

  // Loading of the texture 2D
  GLuint  uiFoodTexID = stContext.m_oGraphicsEngine.GetTextures2DManager ().LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/items/food", "png");

  // Tile of the fruit, bread and vegetable soup.
  m_oFoodTypes[Foods::Type::Fruit].Initialize (uiFoodTexID, sf::IntRect (0, 0, 16, 16), 300);
  m_oFoodTypes[Foods::Type::Bread].Initialize (uiFoodTexID, sf::IntRect (16, 0, 16, 16), 600);
  m_oFoodTypes[Foods::Type::VegetableSoup].Initialize (uiFoodTexID, sf::IntRect (32, 0, 16, 16), 900);
  std::cout << "Foods registering : Succeed" << std::endl;
}

////////////////////////////////////////////////////////////
void FoodsManager::Draw ( Foods::Type eFoodType, GLfloat fX, GLfloat fY, GLfloat fScale ) {
  m_oFoodTypes[eFoodType].Draw (fX, fY, fScale);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLint FoodsManager::GetFoodScore ( Foods::Type eFoodType ) {
  return m_oFoodTypes[eFoodType].GetScore ();
}
