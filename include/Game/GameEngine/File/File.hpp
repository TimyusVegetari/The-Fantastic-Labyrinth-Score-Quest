////////////////////////////////////////////////////////////
//
// This file is part of Demiurge.
// Copyright (C) 2015 Acroute Anthony (ant110283@hotmail.fr)
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
// Description for Doxygen
////////////////////////////////////////////////////////////
/**
 * \file File.hpp
 * \brief Class to define a file.
 * \author Anthony Acroute
 * \version 0.1
 * \date 2013
 *
 */

#ifndef FILE_HPP__
#define FILE_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>

////////////////////////////////////////////////////////////
/// \brief Class to load and store the datas of a file.
///
////////////////////////////////////////////////////////////
class File {

  private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::fstream  m_fsFileStream;
    std::string   m_szBuffer;

  public:
    ////////////////////////////////////////////////////////////
    // Constructor(s)/Destructor
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// This constructor defines a file.
    ///
    ////////////////////////////////////////////////////////////
    File ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Cleans up all the internal resources used by the file class.
    ///
    ////////////////////////////////////////////////////////////
    ~File ( void );

    ////////////////////////////////////////////////////////////
    // General methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Open a file.
    ///
    /// \param szFileName   The adress of the file to open.
    ///
    /// \return True if the file have been open, false else.
    ///
    ////////////////////////////////////////////////////////////
    GLboolean Open ( const std::string szFileName );

    ////////////////////////////////////////////////////////////
    /// \brief Read the file and store datas in the buffer.
    ///
    ////////////////////////////////////////////////////////////
    void Read ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Close the file and delete datas of the buffer.
    ///
    ////////////////////////////////////////////////////////////
    void Close ( void );

    ////////////////////////////////////////////////////////////
    // Accessor methods
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// \brief Get the datas buffer.
    ///
    /// \return An instance of the datas buffer.
    ///
    ////////////////////////////////////////////////////////////
    std::string& GetBuffer ( void );

    ////////////////////////////////////////////////////////////
    /// \brief Get the datas buffer size.
    ///
    /// \return The size of the datas buffer.
    ///
    ////////////////////////////////////////////////////////////
    GLuint GetBufferSize ( void );
};

#endif // FILE_HPP__
