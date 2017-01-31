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
// along with The Fanstastic Labyrinth.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/GameObjects/WorldState/GOPlayer.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOPlayer::GOPlayer ( ST_Context& stContext ) :
  GameObject          (stContext),
  GameObject2D        (),
  m_uiCharacter_ID    (0),
  m_oCharacterWalking (),
  m_oCharacterRunning (),
  m_uiX               (0),
  m_uiY               (0),
  m_bMoved            (GL_FALSE),
  m_bRunning          (GL_TRUE),
  m_bDrawWalking      (GL_FALSE),
  m_bDrawRunning      (GL_FALSE),
  m_iMoveX            (0),
  m_iMoveY            (0),
  m_fMoveX            (0.f),
  m_fMoveY            (0.f)
{
  // Loading of the texture 2D
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  GLuint  uiCharacterWalkingTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/player/player_walking", "png");
  GLuint  uiCharacterRunningTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/player/player_running", "png");

  // Tile of the walking player.
  m_oCharacterWalking.SetLooped (GL_FALSE);
  m_oCharacterWalking.Pause ();
  m_oCharacterWalking.SetSpriteSheet (oTextures2DManager.GetSFMLTexture (uiCharacterWalkingTexID));
  // Down direction
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 64, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 32, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 0, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 32, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 64, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 96, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 128, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 160, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 128, 32, 32));
  m_oCharacterWalking.AddFrame (0, sf::IntRect (0, 96, 32, 32));
  // Right direction
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 64, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 32, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 0, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 32, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 64, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 96, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 128, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 160, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 128, 32, 32));
  m_oCharacterWalking.AddFrame (1, sf::IntRect (32, 96, 32, 32));
  // Up direction
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 64, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 32, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 0, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 32, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 64, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 96, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 128, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 160, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 128, 32, 32));
  m_oCharacterWalking.AddFrame (2, sf::IntRect (64, 96, 32, 32));
  // Left direction
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 64, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 32, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 0, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 32, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 64, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 96, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 128, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 160, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 128, 32, 32));
  m_oCharacterWalking.AddFrame (3, sf::IntRect (96, 96, 32, 32));
  m_oCharacterWalking.SetFrame (0);

  // Tile of the running player.
  m_oCharacterRunning.SetLooped (GL_FALSE);
  m_oCharacterRunning.Pause ();
  m_oCharacterRunning.SetSpriteSheet (oTextures2DManager.GetSFMLTexture (uiCharacterRunningTexID));
  // Down direction
  m_oCharacterRunning.AddFrame (0, sf::IntRect (0, 0, 32, 32));
  m_oCharacterRunning.AddFrame (0, sf::IntRect (0, 32, 32, 32));
  m_oCharacterRunning.AddFrame (0, sf::IntRect (0, 64, 32, 32));
  m_oCharacterRunning.AddFrame (0, sf::IntRect (0, 96, 32, 32));
  m_oCharacterRunning.AddFrame (0, sf::IntRect (0, 128, 32, 32));
  // Right direction
  m_oCharacterRunning.AddFrame (1, sf::IntRect (32, 0, 32, 32));
  m_oCharacterRunning.AddFrame (1, sf::IntRect (32, 32, 32, 32));
  m_oCharacterRunning.AddFrame (1, sf::IntRect (32, 64, 32, 32));
  m_oCharacterRunning.AddFrame (1, sf::IntRect (32, 96, 32, 32));
  m_oCharacterRunning.AddFrame (1, sf::IntRect (32, 128, 32, 32));
  // Up direction
  m_oCharacterRunning.AddFrame (2, sf::IntRect (64, 0, 32, 32));
  m_oCharacterRunning.AddFrame (2, sf::IntRect (64, 32, 32, 32));
  m_oCharacterRunning.AddFrame (2, sf::IntRect (64, 64, 32, 32));
  m_oCharacterRunning.AddFrame (2, sf::IntRect (64, 96, 32, 32));
  m_oCharacterRunning.AddFrame (2, sf::IntRect (64, 128, 32, 32));
  // Left direction
  m_oCharacterRunning.AddFrame (3, sf::IntRect (96, 0, 32, 32));
  m_oCharacterRunning.AddFrame (3, sf::IntRect (96, 32, 32, 32));
  m_oCharacterRunning.AddFrame (3, sf::IntRect (96, 64, 32, 32));
  m_oCharacterRunning.AddFrame (3, sf::IntRect (96, 96, 32, 32));
  m_oCharacterRunning.AddFrame (3, sf::IntRect (96, 128, 32, 32));
  m_oCharacterRunning.SetFrame (0);
}

////////////////////////////////////////////////////////////
GOPlayer::~GOPlayer ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOPlayer::Initialize ( void ) {
  std::cout << " >> GOPlayer initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  // Loading of the texture 2D
  GLuint  uiCharacterTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/player/player", "png");

  // Tile of the player.
  m_uiCharacter_ID = oRenderList2D.PushBack<sf::Sprite> ();
  sf::Sprite& sfCharacter = oRenderList2D.GetDrawable<sf::Sprite> (m_uiCharacter_ID);
  sfCharacter.setTexture (oTextures2DManager.GetSFMLTexture (uiCharacterTexID));
  sfCharacter.setTextureRect (sf::IntRect (0, 0, 32, 32));

  // Tile of the walking and running player.
  m_oCharacterWalking.Stop ();
  m_oCharacterRunning.Stop ();

  m_uiX           = 0;
  m_uiY           = 0;
  m_bMoved        = GL_FALSE;
  m_bRunning      = GL_FALSE;
  m_bDrawWalking  = GL_FALSE;
  m_bDrawRunning  = GL_FALSE;
  m_iMoveX        = 0;
  m_iMoveY        = 0;
  m_fMoveX        = 0.f;
  m_fMoveY        = 0.f;

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean GOPlayer::Update ( void ) {
  // Update the player movement
  if (m_bMoved) {
    GLfloat fDistance;
    if (m_bRunning) {
      if (!m_oCharacterRunning.IsPlaying ()) {
        // Update the player sprite
        RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
        sf::Sprite& sfCharacter = oRenderList2D.GetDrawable<sf::Sprite> (m_uiCharacter_ID);
        if (m_iMoveY > 0) {
          m_oCharacterRunning.SetFrameLine (0);
          sfCharacter.setTextureRect (sf::IntRect (0, 0, 32, 32));
        } else if (m_iMoveX > 0) {
          m_oCharacterRunning.SetFrameLine (1);
          sfCharacter.setTextureRect (sf::IntRect (32, 0, 32, 32));
        } else if (m_iMoveY < 0) {
          m_oCharacterRunning.SetFrameLine (2);
          sfCharacter.setTextureRect (sf::IntRect (64, 0, 32, 32));
        } else if (m_iMoveX < 0) {
          m_oCharacterRunning.SetFrameLine (3);
          sfCharacter.setTextureRect (sf::IntRect (96, 0, 32, 32));
        }
        m_oCharacterRunning.Play ();
        m_bDrawRunning = GL_TRUE;
      }
      fDistance = 6.4f;
    } else {
      if (!m_oCharacterWalking.IsPlaying ()) {
        // Update the player sprite
        RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
        sf::Sprite& sfCharacter = oRenderList2D.GetDrawable<sf::Sprite> (m_uiCharacter_ID);
        if (m_iMoveY > 0) {
          m_oCharacterWalking.SetFrameLine (0);
          sfCharacter.setTextureRect (sf::IntRect (0, 0, 32, 32));
        } else if (m_iMoveX > 0) {
          m_oCharacterWalking.SetFrameLine (1);
          sfCharacter.setTextureRect (sf::IntRect (32, 0, 32, 32));
        } else if (m_iMoveY < 0) {
          m_oCharacterWalking.SetFrameLine (2);
          sfCharacter.setTextureRect (sf::IntRect (64, 0, 32, 32));
        } else if (m_iMoveX < 0) {
          m_oCharacterWalking.SetFrameLine (3);
          sfCharacter.setTextureRect (sf::IntRect (96, 0, 32, 32));
        }
        m_oCharacterWalking.Play ();
        m_bDrawWalking = GL_TRUE;
      }
      fDistance = 3.2f;
    }
    if (m_iMoveX > 0)
      m_fMoveX += fDistance;
    else if (m_iMoveX < 0)
      m_fMoveX -= fDistance;
    if (m_iMoveY > 0)
      m_fMoveY += fDistance;
    else if (m_iMoveY < 0)
      m_fMoveY -= fDistance;
    GLboolean bAnimationIsPlaying;
    if (m_bRunning) {
      m_oCharacterRunning.Update ();
      bAnimationIsPlaying = m_oCharacterRunning.IsPlaying ();
    } else {
      m_oCharacterWalking.Update ();
      bAnimationIsPlaying = m_oCharacterWalking.IsPlaying ();
    }
    if (!bAnimationIsPlaying) {
      m_uiX += m_iMoveX;
      m_uiY += m_iMoveY;
      ClearMove ();
    }
  }

	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean GOPlayer::HandleInput ( void ) {
  // Enable the player running
  // Move the player
  if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up)) {
    if (!m_bMoved) {
      m_iMoveY--;
      m_bMoved = GL_TRUE;
      if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::LShift)) {
        m_bRunning = GL_TRUE;
      }
    }
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down)) {
    if (!m_bMoved) {
      m_iMoveY++;
      m_bMoved = GL_TRUE;
      if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::LShift)) {
        m_bRunning = GL_TRUE;
      }
    }
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right)) {
    if (!m_bMoved) {
      m_iMoveX++;
      m_bMoved = GL_TRUE;
      if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::LShift)) {
        m_bRunning = GL_TRUE;
      }
    }
  } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left)) {
    if (!m_bMoved) {
      m_iMoveX--;
      m_bMoved = GL_TRUE;
      if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::LShift)) {
        m_bRunning = GL_TRUE;
      }
    }
  } else if (!m_bMoved) {
    if (!m_bRunning) {
      m_bDrawRunning = GL_FALSE;
    }
    m_bDrawWalking = GL_FALSE;
  }

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOPlayer::Draw ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Draw the player
  if (m_bDrawRunning) {
    m_oCharacterRunning.setPosition (static_cast<GLfloat>(32*m_uiX)+m_fMoveX, static_cast<GLfloat>(32*m_uiY)+m_fMoveY);
    gmMainWindow.Draw (m_oCharacterRunning);
  } else if (m_bDrawWalking) {
    m_oCharacterWalking.setPosition (static_cast<GLfloat>(32*m_uiX)+m_fMoveX, static_cast<GLfloat>(32*m_uiY)+m_fMoveY);
    gmMainWindow.Draw (m_oCharacterWalking);
  } else {
    RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

    sf::Sprite& sfCharacter = oRenderList2D.GetDrawable<sf::Sprite> (m_uiCharacter_ID);
    sfCharacter.setPosition (static_cast<GLfloat>(32*m_uiX), static_cast<GLfloat>(32*m_uiY));
    gmMainWindow.Draw (sfCharacter);
  }
}

////////////////////////////////////////////////////////////
void GOPlayer::ClearMove ( void ) {
  m_iMoveX = 0;
  m_iMoveY = 0;
  m_fMoveX = 0.f;
  m_fMoveY = 0.f;
  m_bMoved = GL_FALSE;
  m_bRunning = GL_FALSE;
  m_bDrawWalking = GL_FALSE;
  m_bDrawRunning = GL_FALSE;
  m_oCharacterWalking.Stop ();
  m_oCharacterRunning.Stop ();
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOPlayer::SetPosition ( GLuint uiX, GLuint uiY ) {
  m_uiX = uiX;
  m_uiY = uiY;
  ClearMove ();
}

////////////////////////////////////////////////////////////
void GOPlayer::GetPosition ( GLuint& uiX, GLuint& uiY ) {
  uiX = m_uiX;
  uiY = m_uiY;
}

////////////////////////////////////////////////////////////
GLboolean GOPlayer::GetMovePosition ( GLuint& uiX, GLuint& uiY ) {
  if (m_iMoveX == 0 && m_iMoveY == 0)
    return GL_FALSE;
  uiX = m_uiX+m_iMoveX;
  uiY = m_uiY+m_iMoveY;
  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOPlayer::GetCenterInPixels ( GLfloat& fX, GLfloat& fY ) {
  fX = static_cast<GLfloat>(16+m_uiX*32)+m_fMoveX;
  fY = static_cast<GLfloat>(16+m_uiY*32)+m_fMoveY;
}

////////////////////////////////////////////////////////////
GLboolean GOPlayer::IsMoving ( void ) {
  return m_bMoved;
}
