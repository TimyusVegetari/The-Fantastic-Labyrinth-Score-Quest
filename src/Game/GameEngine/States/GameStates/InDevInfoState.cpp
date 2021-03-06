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
#include <Game/GameEngine/States/GameStates/InDevInfoState.hpp>
#include <Game/gamedev_info.hpp>

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
InDevInfoState::InDevInfoState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID (0),
  m_uiTitle_ID        (0),
  m_uiContent_ID      (0),
  m_uiTickTrigger     (500),
  m_uiElapsedTicks    (0),
  m_bIsQuiting        (GL_FALSE)
{
}

////////////////////////////////////////////////////////////
InDevInfoState::~InDevInfoState ( void ) {
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean InDevInfoState::Initialize ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

	// In development information title
  m_uiTitle_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oTitle  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTitle_ID);
  oTitle.SetFont        (m_stContext.m_oBmpFont);
  oTitle.SetString      (std::string ("Please note this is a b�ta version of ")
                        +std::string (THEFANTASTICLABYRINTH_NAME)
                        +std::string ("."));
  oTitle.SetStyle       (sf::Text::Style::Bold);
  oTitle.SetColor       (sf::Color::Yellow);
	oTitle.SetOrigin      (oTitle.GetLocalBounds ().width / 2.f, 0.f);
	oTitle.setPosition    (gmMainWindow.GetView ().getCenter ().x, 100.f);
	// In development information contant
  m_uiContent_ID            = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oContent  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiContent_ID);
  oContent.SetFont          (m_stContext.m_oBmpFont);
  oContent.SetString        (std::string ("It has only a fraction of the planned features\n")
                            +std::string ("and may contain bugs and be missing anims,\n")
                            +std::string ("sounds and other features.\n\n")
                            +std::string ("This does not reflect the quality, wealth or\n")
                            +std::string ("feature set of the imagined project.\n")
                            +std::string ("It is the beginning of a long-term work, intended to\n")
                            +std::string ("evolve during the years.\n\n")
                            +std::string ("Thank you for your understanding and good game !"));
  oContent.SetColor         (sf::Color::Green);
	oContent.SetOrigin        (oContent.GetLocalBounds ().width / 2.f, 0.f);
	oContent.setPosition      (gmMainWindow.GetView ().getCenter ().x, 130.f);

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, gmMainWindow.GetWidth ()*1.f, gmMainWindow.GetHeight ()*1.f));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void InDevInfoState::ResizeView ( void ) {
  // Getting of the main window
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Update the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, gmMainWindow.GetWidth ()*1.f, gmMainWindow.GetHeight ()*1.f));

  // Get the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  RenderList2D& oRenderList2D = oRenderer2D.GetRenderList (m_uiRenderList2D_ID);

	// In development information title
  drimi::BmpText& oTitle  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTitle_ID);
	oTitle.setPosition    (gmMainWindow.GetView ().getCenter ().x, 100.f);
	// In development information contant
  drimi::BmpText& oContent  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiContent_ID);
	oContent.setPosition      (gmMainWindow.GetView ().getCenter ().x, 130.f);
}

////////////////////////////////////////////////////////////
void InDevInfoState::Draw ( void ) {
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  gmMainWindow.EnableSFML ();

  // Activating of the main view
  gmMainWindow.setView (m_sfMainView);

  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Render (m_uiRenderList2D_ID, gmMainWindow);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean InDevInfoState::Update ( void ) {
  if (!m_bIsQuiting) {    ///< While the state is not quiting.
    // After a laps of time the game go to the title state
    if (m_uiElapsedTicks >= m_uiTickTrigger) {
      RequestStackReplace (States::ID::Title);
      m_bIsQuiting = GL_TRUE;

      return GL_TRUE;
    } else
      m_uiElapsedTicks++; // Else, time goes by
  }

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean InDevInfoState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
	if (eEventType == drimi::Event::Type::KeyPressed) {
    if (!m_bIsQuiting) {  ///< While the state is not quiting.
      if (sfKeyCode == sf::Keyboard::Key::Return) {
        RequestStackReplace (States::ID::Title);
        m_bIsQuiting = GL_TRUE;
      }
    }
	}
	return GL_TRUE;
}

////////////////////////////////////////////////////////////
GLboolean InDevInfoState::HandleInput ( void ) {

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& InDevInfoState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
