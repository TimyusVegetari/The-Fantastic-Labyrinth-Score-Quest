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
 * \file GraphicsEngine.hpp
 * \brief Class for the graphics engine of Demiurge.
 * \author Anthony Acroute
 * \version 0.5
 * \date 2013-2016
 *
 */

#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Game/includes.hpp>
#include <DRIMI/Mathematics/Config.hpp>
#include "OGLManager.hpp"
#include "Textures2D/Textures2DManager.hpp"
#include "Renderer2D/Renderer2D.hpp"

#include <string>

class GraphicsEngine;

////////////////////////////////////////////////////////////
/// \brief Class for initialising and manage the graphical objects and rendering.
///
////////////////////////////////////////////////////////////
class GraphicsEngine {

  protected :
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    OGLManager            m_oOGLManager;
    Textures2DManager     m_oTextures2DManager; ///< Textures 2D of the game.
    Renderer2D            m_oRenderer2D;

    // Time for the graphics mecanic
		GLuint                m_uiPrevElapsedTime;
		GLuint                m_uiFrameDelay;
    GLfloat               m_fFrameDelayInSeconds;
    GLuint                m_uiFrameRate;
    std::string           m_szFrameRate;
    GLuint                m_uiFrameTrigger;
    GLuint                m_uiElapsedFrames;

    sf::Color             m_sfScreenColor;
  public :
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines the graphics engine.
    ///
    ////////////////////////////////////////////////////////////
    GraphicsEngine          ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the graphics engine.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~GraphicsEngine ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Configurate OpenGL context of the graphics engine.
    ///
    /// \param fWidth   Width of the OpenGL context.
    ///        fHeight  Height of the OpenGL context.
    ///        uiDepth  Depth of the OpenGL context.
    ///
    ////////////////////////////////////////////////////////////
    void Configurate ( GLuint uiWidth, GLuint uiHeight, GLuint uiDepth );

    ////////////////////////////////////////////////////////////
    /// \brief Initialize all the composants of the graphics engine.
    ///
    /// \return True if initializing succeeded, false if it failed.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Initialize ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Set the frame delay for the graphics mecanic from the frame rate.
    ///
    /// \param uiFrameRate   Frame rate of the graphics mecanic, in frames.
    ///
    ////////////////////////////////////////////////////////////
    void SetFrameRate ( GLuint uiFrameRate );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame delay in frames.
    ///
    /// \return Frame delay value, in frames.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetFrameDelay ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame delay in seconds.
    ///
    /// \return Frame delay value, in seconds.
    ///
    ////////////////////////////////////////////////////////////
    GLfloat GetFrameDelayInSeconds ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Compute the frame rate of the time of graphics mecanic.
    ///
    /// \param uiElapsedTime  Elapsed time to compute the frame rate of the graphics mecanic.
    ///
    ////////////////////////////////////////////////////////////
    void ComputeFrameRate ( GLuint uiElapsedTime );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame rate of the time of graphics mecanic.
    ///
    /// \return Frame rate value.
    ///
    ////////////////////////////////////////////////////////////
    std::string GetFrameRate ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Set the frame trigger with the elapsed time.
    ///
    /// \param uiElapsedTime  Elapsed time to permit the update of the trigger.
    ///
    ////////////////////////////////////////////////////////////
    void SetFrameTrigger ( GLuint uiElapsedTime );

    ////////////////////////////////////////////////////////////
    /// \brief Get the frame trigger.
    ///
    /// \return Frame trigger value.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetFrameTrigger ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the elapsed frames.
    ///
    /// \return Elapsed frame value.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetElapsedFrames ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Set the screen color.
    ///
    /// \param uiRed    Red value of the screen color.
    ///        uiGreen  Green value of the screen color.
    ///        uiBlue   Blue value of the screen color.
    ///        uiAlpha  Alpha value of the screen color.
    ///
    ////////////////////////////////////////////////////////////
    void SetScreenColor ( sf::Uint8 uiRed, sf::Uint8 uiGreen, sf::Uint8 uiBlue, sf::Uint8 uiAlpha );

    ////////////////////////////////////////////////////////////
    /// \brief Get the screen color.
    ///
    /// \return Screen color.
    ///
    ////////////////////////////////////////////////////////////
    const sf::Color& GetScreenColor ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the OpenGL manager.
    ///
    /// \return Instance of the OpenGL manager.
    ///
    ////////////////////////////////////////////////////////////
    OGLManager& GetOGLManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the textures 2D manager.
    ///
    /// \return Instance of the textures 2D manager.
    ///
    ////////////////////////////////////////////////////////////
    Textures2DManager& GetTextures2DManager ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the renderer 2D.
    ///
    /// \return Instance of the renderer 2D.
    ///
    ////////////////////////////////////////////////////////////
    Renderer2D& GetRenderer2D ( void );
};

#endif // GRAPHICSENGINE_HPP
