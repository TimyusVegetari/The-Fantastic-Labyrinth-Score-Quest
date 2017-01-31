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
#include <Game/GameObjects/TitleState/GOMainMenu.hpp>
#include <Game/GameEngine/States/GameStates/StateIdentifiers.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GOMainMenu::GOMainMenu ( ST_Context& stContext ) :
  GameObject          (stContext),
  GameObject2D        ()
{
}

////////////////////////////////////////////////////////////
GOMainMenu::~GOMainMenu ( void ) {
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean GOMainMenu::Initialize ( void ) {
  std::cout << " >> GOMainMenu initializing..." << std::endl;
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();

  // Positioning the menu
  m_oMenuContainer.SetPosition (m_sfPosition.x, m_sfPosition.y);

  // Loading of the textures 2D
  GLuint  uiButtonTexID = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gui/button", "png");

	// Game menu : Play button
	drimi::Gui::Button::Ptr poButtonPlay = std::make_shared<drimi::Gui::Button> ();
	poButtonPlay->SetBackgroundTextures (oTextures2DManager.GetSFMLTexture (uiButtonTexID), 198, 32);
	poButtonPlay->SetText ("Play", m_stContext.m_oBmpFont, sf::Color::Yellow);
	poButtonPlay->SetOrigin (99.f, 16.f);
	poButtonPlay->SetPosition (0.f, 0.f);
	poButtonPlay->SetCallback ([this] () {
                              RequestStackReplace (States::ID::World);
                            });
	m_oMenuContainer.Pack (poButtonPlay);
	// Game menu : Highscore button
	drimi::Gui::Button::Ptr poButtonHighscore = std::make_shared<drimi::Gui::Button> ();
	poButtonHighscore->SetBackgroundTextures (oTextures2DManager.GetSFMLTexture (uiButtonTexID), 198, 32);
	poButtonHighscore->SetText ("Highscore", m_stContext.m_oBmpFont, sf::Color::Yellow);
	poButtonHighscore->SetOrigin (99.f, 16.f);
	poButtonHighscore->SetPosition (0.f, 34.f);
	poButtonHighscore->SetCallback ([this] () {
                              RequestStackReplace (States::ID::HighScore);
                            });
	m_oMenuContainer.Pack (poButtonHighscore);
	// Game menu : Quit button
	drimi::Gui::Button::Ptr poButtonQuit = std::make_shared<drimi::Gui::Button> ();
	poButtonQuit->SetBackgroundTextures (oTextures2DManager.GetSFMLTexture (uiButtonTexID), 198, 32);
	poButtonQuit->SetText ("Quit", m_stContext.m_oBmpFont, sf::Color::Yellow);
	poButtonQuit->SetOrigin (99.f, 16.f);
	poButtonQuit->SetPosition (0.f, 68.f);
	poButtonQuit->SetCallback ([this] () {
                              gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
                              gmMainWindow.Close ();
                            });
	m_oMenuContainer.Pack (poButtonQuit);

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void GOMainMenu::ResizeView ( void ) {
  // Positioning the menu
  m_oMenuContainer.SetPosition (m_sfPosition.x, m_sfPosition.y);
}

////////////////////////////////////////////////////////////
GLboolean GOMainMenu::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  // Event of the menu and its components
  m_oMenuContainer.HandleEvent (eEventType, sfKeyCode);

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean GOMainMenu::HandleTextUnicode ( const char cUnicode ) {
  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void GOMainMenu::Draw ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = m_stContext.m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);

  // Draw the menu and its components
  m_oMenuContainer.Update ();
  gmMainWindow.Draw (m_oMenuContainer);
}

////////////////////////////////////////////////////////////
// Accessor methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void GOMainMenu::SetPosition ( GLfloat fX, GLfloat fY ) {
  m_sfPosition = sf::Vector2f (fX, fY);
}

////////////////////////////////////////////////////////////
drimi::Gui::Container& GOMainMenu::GetMenuContainer ( void ) {
  return m_oMenuContainer;
}
