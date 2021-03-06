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
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameEngine/GraphicsEngine/GraphicsEngine.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GraphicsEngine::GraphicsEngine ( void ) :
  m_oOGLManager           (),
  m_oTextures2DManager    (),
  m_oRenderer2D           (),
  m_uiPrevElapsedTime     (0),
  m_uiFrameDelay          (0),
  m_fFrameDelayInSeconds  (0.f),
  m_uiFrameRate           (0),
  m_szFrameRate           (""),
  m_uiFrameTrigger        (0),
  m_uiElapsedFrames       (0),
  m_sfScreenColor         (0.f, 0.f, 0.f, 0.f)
{
}

////////////////////////////////////////////////////////////
GraphicsEngine::~GraphicsEngine ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GraphicsEngine::Configurate ( GLuint uiWidth, GLuint uiHeight, GLuint uiDepth ) {
  OGLManager::OGLConfig& stOGLConfig  = m_oOGLManager.GetConfig ();
  stOGLConfig.uiWidth   = uiWidth;
  stOGLConfig.uiHeight  = uiHeight;
  stOGLConfig.uiDepth   = uiDepth;
}

////////////////////////////////////////////////////////////
GLboolean GraphicsEngine::Initialize ( void ) {
  std::cout << "Graphics Engine : Initializing..." << std::endl;
  GLboolean bSuccess = GL_TRUE;

  // Create the OpenGL context with SFML
  m_oOGLManager.CreateOpenGLContext ();

  // Initialize OpenGL
  if (m_oOGLManager.InitializeGlew () && m_oOGLManager.CheckGLversion () && m_oOGLManager.InitializeGLExtensions ()) {
  }

  if (m_oOGLManager.GetErrorGLExt ()) {
    // Initialize the 2D and 3D renderers
    bSuccess = m_oRenderer2D.Initialize ();
  } else
    bSuccess = GL_FALSE;

  if (bSuccess)
    std::cout << "Graphics Engine : Initialization succeed" << std::endl;
  else
    std::cout << "Graphics Engine : Initialization failed" << std::endl;
  return bSuccess;
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GraphicsEngine::SetFrameRate ( GLuint uiFrameRate ) {
  m_uiFrameDelay = 1000 / uiFrameRate;
  m_fFrameDelayInSeconds = static_cast<GLfloat>(m_uiFrameDelay) / 1000.f;
  m_uiFrameTrigger = m_uiFrameDelay;
  std::cout << "Graphics Engine : Frame rate has changed to " << uiFrameRate << " fps" << std::endl;
}

////////////////////////////////////////////////////////////
GLuint GraphicsEngine::GetFrameDelay ( void ) {
  return m_uiFrameDelay;
}

////////////////////////////////////////////////////////////
GLfloat GraphicsEngine::GetFrameDelayInSeconds ( void ) {
  return m_fFrameDelayInSeconds;
}

////////////////////////////////////////////////////////////
void GraphicsEngine::ComputeFrameRate ( GLuint uiElapsedTime ) {
  if (uiElapsedTime - m_uiPrevElapsedTime >= 1000) {
    m_uiPrevElapsedTime = uiElapsedTime;
    m_szFrameRate = drimi::ToString (m_uiFrameRate);
    m_uiFrameRate = 0;
  } else {
    m_uiFrameRate++;
    m_uiElapsedFrames++;
  }
}

////////////////////////////////////////////////////////////
std::string GraphicsEngine::GetFrameRate ( void ) {
  return m_szFrameRate;
}

////////////////////////////////////////////////////////////
void GraphicsEngine::SetFrameTrigger ( GLuint uiElapsedTime ) {
  m_uiFrameTrigger = uiElapsedTime + m_uiFrameDelay;
}

////////////////////////////////////////////////////////////
GLuint GraphicsEngine::GetFrameTrigger ( void ) {
  return m_uiFrameTrigger;
}

////////////////////////////////////////////////////////////
GLuint GraphicsEngine::GetElapsedFrames ( void ) {
  return m_uiElapsedFrames;
}

////////////////////////////////////////////////////////////
void GraphicsEngine::SetScreenColor ( sf::Uint8 uiRed, sf::Uint8 uiGreen, sf::Uint8 uiBlue, sf::Uint8 uiAlpha ) {
  m_sfScreenColor.r = uiRed;
  m_sfScreenColor.g = uiGreen;
  m_sfScreenColor.b = uiBlue;
  m_sfScreenColor.a = uiAlpha;
}

////////////////////////////////////////////////////////////
const sf::Color& GraphicsEngine::GetScreenColor ( void ) {
  return m_sfScreenColor;
}

////////////////////////////////////////////////////////////
OGLManager& GraphicsEngine::GetOGLManager ( void ) {
  return m_oOGLManager;
}

////////////////////////////////////////////////////////////
Textures2DManager& GraphicsEngine::GetTextures2DManager ( void ) {
  return m_oTextures2DManager;
}

////////////////////////////////////////////////////////////
Renderer2D& GraphicsEngine::GetRenderer2D ( void ) {
  return m_oRenderer2D;
}
