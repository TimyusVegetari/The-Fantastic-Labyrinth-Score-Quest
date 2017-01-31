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
#include <Game/GameEngine/States/StateStack.hpp>

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::ST_Context::ST_Context ( const GLuint& uiElapsedTime,
                                     RenderTargetsManager& oRenderTargetsManager,
                                     drimi::BmpFont& oBmpFont,
                                     GraphicsEngine& oGraphicsEngine,
                                     StateStack& oStateStack,
                                     GameObjectsManager& oGameObjectsManager,
                                     LevelsManager& oLevelsManager,
                                     TilesManager& oTilesManager,
                                     ScoreBoard& oScoreBoard,
                                     FoodsManager& oFoodsManager ) :
  m_uiElapsedTime           (uiElapsedTime),
  m_oRenderTargetsManager   (oRenderTargetsManager),
  m_oBmpFont                (oBmpFont),
  m_oGraphicsEngine         (oGraphicsEngine),
  m_oStateStack             (oStateStack),
  m_oGameObjectsManager     (oGameObjectsManager),
  m_oLevelsManager          (oLevelsManager),
  m_oTilesManager           (oTilesManager),
  m_oScoreBoard             (oScoreBoard),
  m_oFoodsManager           (oFoodsManager)
{
}

////////////////////////////////////////////////////////////
const GLuint& GameObject::ST_Context::GetElapsedTime ( void ) {
  return m_uiElapsedTime;
}

////////////////////////////////////////////////////////////
RenderList2D& GameObject::ST_Context::GetRenderList2D ( GLuint uiRenderList2D_ID ) {
  return m_oGraphicsEngine.GetRenderer2D ().GetRenderList (uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
StateStack& GameObject::ST_Context::GetStateStack ( void ) {
  return m_oStateStack;
}

////////////////////////////////////////////////////////////
GameObjectsManager& GameObject::ST_Context::GetGameObjectsManager ( void ) {
  return m_oGameObjectsManager;
}

////////////////////////////////////////////////////////////
LevelsManager& GameObject::ST_Context::GetLevelsManager ( void ) {
  return m_oLevelsManager;
}

////////////////////////////////////////////////////////////
TilesManager& GameObject::ST_Context::GetTilesManager ( void ) {
  return m_oTilesManager;
}

////////////////////////////////////////////////////////////
ScoreBoard& GameObject::ST_Context::GetScoreBoard ( void ) {
  return m_oScoreBoard;
}

////////////////////////////////////////////////////////////
FoodsManager& GameObject::ST_Context::GetFoodsManager ( void ) {
  return m_oFoodsManager;
}

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::GameObject ( ST_Context& stContext ) :
  m_stContext       (stContext)
{
}

////////////////////////////////////////////////////////////
GameObject::~GameObject ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GameObject::RequestStackPush ( States::ID eStateID ) {
  m_stContext.GetStateStack ().PushState (eStateID);
}

////////////////////////////////////////////////////////////
void GameObject::RequestStackPop ( void ) {
	m_stContext.GetStateStack ().PopState ();
}

////////////////////////////////////////////////////////////
void GameObject::RequestStackReplace ( States::ID eStateID ) {
  m_stContext.GetStateStack ().ReplaceState (eStateID);
}

////////////////////////////////////////////////////////////
void GameObject::RequestStateClear ( void ) {
	m_stContext.GetStateStack ().ClearStates ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GameObject::ST_Context& GameObject::GetContext ( void ) const {
	return m_stContext;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
OGLManager& GameObject::GetOGLManager ( void ) {
  return m_stContext.m_oGraphicsEngine.GetOGLManager ();
}
