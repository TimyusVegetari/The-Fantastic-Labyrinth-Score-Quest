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

#include <Game/GameEngine/GraphicsEngine/Renderer2D/AnimatedSprite.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
AnimatedSprite::AnimatedSprite ( void ) :
  m_iCurrentFrameLine (0),
  m_iCurrentFrame     (0),
  m_bIsPaused         (GL_FALSE),
  m_bIsLooped         (GL_TRUE),
  m_vFrames           (),
  m_sfTexture         (NULL)
{
}

////////////////////////////////////////////////////////////
AnimatedSprite::~AnimatedSprite ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void AnimatedSprite::AddFrame ( std::size_t iFrameLine, sf::IntRect sfRect ) {
  if (iFrameLine == m_vFrames.size ()) {
    m_vFrames.push_back (std::vector<sf::IntRect> ());
  }
  m_vFrames[iFrameLine].push_back (sfRect);
}

////////////////////////////////////////////////////////////
void AnimatedSprite::Update ( void ) {
  // If animation is playing.
  if (!m_bIsPaused) {
    // Get next Frame index
    if (m_iCurrentFrame+1 < m_vFrames[m_iCurrentFrameLine].size ())
      m_iCurrentFrame++;
    else {
      // animation has ended, reset to start.
      m_iCurrentFrame = 0;
      if (!m_bIsLooped)
        m_bIsPaused = GL_TRUE;
    }
    // Set the current frame.
    SetFrame (m_iCurrentFrame);
  }
}

////////////////////////////////////////////////////////////
void AnimatedSprite::Play ( void ) {
  m_bIsPaused = GL_FALSE;
}

////////////////////////////////////////////////////////////
void AnimatedSprite::Pause ( void ) {
  m_bIsPaused = GL_TRUE;
}

////////////////////////////////////////////////////////////
void AnimatedSprite::Stop ( void ) {
  m_bIsPaused = GL_TRUE;
  m_iCurrentFrame = 0;
  SetFrame (m_iCurrentFrame);
}

void AnimatedSprite::draw (sf::RenderTarget& target, sf::RenderStates states) const {
  if (m_sfTexture) {
    states.transform *= getTransform ();
    states.texture = m_sfTexture;
    target.draw (m_sfVertices, 4, sf::Quads, states);
  }
}

////////////////////////////////////////////////////////////
void AnimatedSprite::SetFrame ( std::size_t iNewFrame ) {
  // Calculate new vertex positions and texture coordinates
  sf::IntRect sfRect = m_vFrames[m_iCurrentFrameLine][iNewFrame];

  m_sfVertices[0].position = sf::Vector2f (0.f, 0.f);
  m_sfVertices[1].position = sf::Vector2f (0.f, static_cast<GLfloat> (sfRect.height));
  m_sfVertices[2].position = sf::Vector2f (static_cast<GLfloat> (sfRect.width), static_cast<GLfloat> (sfRect.height));
  m_sfVertices[3].position = sf::Vector2f (static_cast<GLfloat> (sfRect.width), 0.f);

  GLfloat fLeft = static_cast<GLfloat> (sfRect.left) + 0.0001f;
  GLfloat fRight = fLeft + static_cast<GLfloat> (sfRect.width);
  GLfloat fTop = static_cast<GLfloat> (sfRect.top);
  GLfloat fBottom = fTop + static_cast<GLfloat> (sfRect.height);

  m_sfVertices[0].texCoords = sf::Vector2f (fLeft, fTop);
  m_sfVertices[1].texCoords = sf::Vector2f (fLeft, fBottom);
  m_sfVertices[2].texCoords = sf::Vector2f (fRight, fBottom);
  m_sfVertices[3].texCoords = sf::Vector2f (fRight, fTop);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void AnimatedSprite::SetSpriteSheet ( const sf::Texture& sfTexture ) {
  m_sfTexture = &sfTexture;
}

////////////////////////////////////////////////////////////
void AnimatedSprite::SetLooped ( GLboolean bLooped ) {
  m_bIsLooped = bLooped;
}

////////////////////////////////////////////////////////////
sf::FloatRect AnimatedSprite::GetLocalBounds ( void ) const {
  sf::IntRect sfRect = m_vFrames[m_iCurrentFrameLine][m_iCurrentFrame];

  GLfloat fWidth  = static_cast<float> (std::abs (sfRect.width));
  GLfloat fHeight = static_cast<float> (std::abs (sfRect.height));

  return sf::FloatRect (0.f, 0.f, fWidth, fHeight);
}

////////////////////////////////////////////////////////////
sf::FloatRect AnimatedSprite::GetGlobalBounds ( void ) const {
  return getTransform ().transformRect (GetLocalBounds ());
}

////////////////////////////////////////////////////////////
GLboolean AnimatedSprite::IsLooped ( void ) const {
  return m_bIsLooped;
}

////////////////////////////////////////////////////////////
GLboolean AnimatedSprite::IsPlaying ( void ) const {
  return !m_bIsPaused;
}

////////////////////////////////////////////////////////////
void AnimatedSprite::SetFrameLine ( std::size_t iNewFrameLine ) {
  if (iNewFrameLine < m_vFrames.size ())
    m_iCurrentFrameLine = iNewFrameLine;
  else
    std::cout << "Error in a animated sprite : frame lines size overflow !" << std::endl;
}
