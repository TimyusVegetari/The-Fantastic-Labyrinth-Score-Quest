////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2016-2017 Acroute Anthony (ant110283@hotmail.fr)
//
// Demiurge is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Demiurge is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Demiurge.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/LevelsManager.hpp>
#include <DRIMI/Mathematics/Methods/ToString.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
LevelsManager::LevelsManager ( void ) {
}

////////////////////////////////////////////////////////////
LevelsManager::~LevelsManager ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void LevelsManager::Initialize ( void ) {
  m_eState = LevelsManager::State::START;
  m_uiLevelsCount = 0;
  m_uiStepsCount = 0;
  m_iSubLevelsCount = -1;
}

////////////////////////////////////////////////////////////
void LevelsManager::IncrementLevel ( void ) {
  m_uiLevelsCount++;
  if (m_iSubLevelsCount == 4) {
    m_uiStepsCount++;
    m_iSubLevelsCount = 0;
  } else
    m_iSubLevelsCount++;
}

////////////////////////////////////////////////////////////
std::string LevelsManager::ToString ( void ) {
	return "Level "+drimi::ToString (m_uiLevelsCount);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void LevelsManager::SetState ( LevelsManager::State eState ) {
  m_eState = eState;
}

////////////////////////////////////////////////////////////
LevelsManager::State LevelsManager::GetState ( void ) {
  return m_eState;
}

////////////////////////////////////////////////////////////
GLuint LevelsManager::GetStepsCount ( void ) {
  return m_uiStepsCount;
}

////////////////////////////////////////////////////////////
GLint LevelsManager::GetSubLevelsCount ( void ) {
  return m_iSubLevelsCount;
}
