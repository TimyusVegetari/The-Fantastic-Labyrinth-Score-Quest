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
#include <Game/GameEngine/States/GameStates/WorldState.hpp>
#include <Game/gamedev_info.hpp>
#include <glm/trigonometric.hpp> // glm::atan
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////
// Constructor(s)/Destructor
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
WorldState::WorldState ( StateStack& oStack, ST_Context& stContext ) :
  State ( oStack, stContext ),
  m_uiRenderList2D_ID (0),
  m_uiTerrain         (0),
  m_uiPlayer          (0),
  m_sfInventory       (),
  m_uiInventory       (NULL),
  m_bFoodCollecting   (GL_FALSE),
  m_iScoreWonTime     (-1),
  m_oScoreWon         (),
  m_uiLevel_ID        (0),
  m_uiScoreTexts_ID   (0),
  m_uiTotalScore_ID   (0),
  m_uiCurrentScore_ID (0),
  m_sfMainView        (),
  m_oGOWorldView      (stContext),
  m_bScrolling        (GL_FALSE),
  m_bGameOver         (GL_FALSE),
  m_bEndGame          (GL_FALSE),
  m_bNDA_Increment    (GL_FALSE),
  m_uiRedAlert        (0)
{
}

////////////////////////////////////////////////////////////
WorldState::~WorldState ( void ) {
  // Delete the render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  oRenderer2D.Erase (m_uiRenderList2D_ID);

  if (m_uiInventory != NULL)
    delete[] m_uiInventory;

  m_stContext.m_oGraphicsEngine.SetScreenColor (0, 0, 0, 255);
}

////////////////////////////////////////////////////////////
// General methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
GLboolean WorldState::Initialize ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  Textures2DManager& oTextures2DManager = m_stContext.m_oGraphicsEngine.GetTextures2DManager ();
  gm::RenderWindow& gmMainWindow = GetMainWindow ();

  // Initialize the levels manager and the score board
  m_stContext.GetLevelsManager ().Initialize ();
  m_stContext.GetScoreBoard ().Initialize ();

  // Creation of the initializer for this state.
  m_uiInitializer_ID = oGameObjectsManager.CreateInitializer ();

  // Create a render list 2D
  Renderer2D& oRenderer2D = m_stContext.m_oGraphicsEngine.GetRenderer2D ();
  m_uiRenderList2D_ID = oRenderer2D.CreateRenderList ();

  // Game Terrain
  /*if (!oGameObjectsManager.AddToInitializer<GOTerrain> (m_uiInitializer_ID, GameObjects::Type::Terrain, m_uiTerrain)) {
    // Debug : It will be necessary to process the errors, in the future.
  }*/
  oGameObjectsManager.AddGameObject<GOTerrain> (GameObjects::Type::Terrain, m_uiTerrain);
  GOTerrain& oGOTerrain = oGameObjectsManager.GetGameObject<GOTerrain> (GameObjects::Type::Terrain, m_uiTerrain);
  oGOTerrain.SetRenderList2D_ID (m_uiRenderList2D_ID);
  if (!oGOTerrain.Initialize ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  // Game Player
  /*if (!oGameObjectsManager.AddToInitializer<GOPlayer> (m_uiInitializer_ID, GameObjects::Type::Player, m_uiPlayer)) {
    // Debug : It will be necessary to process the errors, in the future.
  }*/
  oGameObjectsManager.AddGameObject<GOPlayer> (GameObjects::Type::Player, m_uiPlayer);
  GOPlayer& oGOPlayer = oGameObjectsManager.GetGameObject<GOPlayer> (GameObjects::Type::Player, m_uiPlayer);
  oGOPlayer.SetRenderList2D_ID (m_uiRenderList2D_ID);
  if (!oGOPlayer.Initialize ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  // Game View
  if (!m_oGOWorldView.Initialize ()) {
    // Debug : It will be necessary to process the errors, in the future.
  }

  gmMainWindow.EnableSFML ();

  GLfloat fScreenWidth = static_cast<GLfloat> (gmMainWindow.GetWidth ());
  GLfloat fScreenHeight = static_cast<GLfloat> (gmMainWindow.GetHeight ());

	// Loading of the textures 2D
  GLuint  uiMainBoardTexID  = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gui/world_topbar", "png"),
          uiInventoryTexID  = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gui/inventory", "png"),
          uiSlotTexID       = oTextures2DManager.LoadTexture (Textures2DManager::TexType::SFML_TEXTURE, "datas/gui/slot", "png");

	// Main board for levels and scores
	m_sfMainBoard[0].setTexture     (oTextures2DManager.GetSFMLTexture (uiMainBoardTexID));
  m_sfMainBoard[0].setTextureRect (sf::IntRect (0, 0, 6, 42));
	m_sfMainBoard[0].setPosition    (0.f, 0.f);
	m_sfMainBoard[1].setTexture     (oTextures2DManager.GetSFMLTexture (uiMainBoardTexID));
  m_sfMainBoard[1].setTextureRect (sf::IntRect (7, 0, 1, 42));
	m_sfMainBoard[1].setPosition    (6.f, 0.f);
	m_sfMainBoard[1].setScale       (sf::Vector2f (fScreenWidth-12.f, 1.f));
	m_sfMainBoard[2].setTexture     (oTextures2DManager.GetSFMLTexture (uiMainBoardTexID));
  m_sfMainBoard[2].setTextureRect (sf::IntRect (9, 0, 6, 42));
	m_sfMainBoard[2].setPosition    (fScreenWidth-6.f, 0.f);

	m_sfInventory.setTexture      (oTextures2DManager.GetSFMLTexture (uiInventoryTexID));
  m_sfInventory.setTextureRect  (sf::IntRect (0, 0, 122, 42));
  m_sfInventory.setPosition     (150.f, 0.f);

  m_uiInventory = new GLuint[Foods::Type::Count];
  for (GLuint uiSlot = 0 ; uiSlot < Foods::Type::Count ; uiSlot++)
    m_uiInventory[uiSlot] = 0;

  m_oInventoryContainer.SetPosition (150.f, 0.f);

  // Inventory : Fruit slot
	drimi::Gui::Button::Ptr poSlotFruit = std::make_shared<drimi::Gui::Button> ();
	poSlotFruit->SetBackgroundTextures (oTextures2DManager.GetSFMLTexture (uiSlotTexID), 34, 34);
	poSlotFruit->SetPosition (6.f, 4.f);
	poSlotFruit->SetCallback ([this] () { FoodEating (); });
	m_oInventoryContainer.Pack (poSlotFruit);
  // Inventory : Bread slot
	drimi::Gui::Button::Ptr poSlotBread = std::make_shared<drimi::Gui::Button> ();
	poSlotBread->SetBackgroundTextures (oTextures2DManager.GetSFMLTexture (uiSlotTexID), 34, 34);
	poSlotBread->SetPosition (44.f, 4.f);
	poSlotBread->SetCallback ([this] () { FoodEating (); });
	m_oInventoryContainer.Pack (poSlotBread);
  // Inventory : Vegetable soup slot
	drimi::Gui::Button::Ptr poSlotVegetableSoup = std::make_shared<drimi::Gui::Button> ();
	poSlotVegetableSoup->SetBackgroundTextures (oTextures2DManager.GetSFMLTexture (uiSlotTexID), 34, 34);
	poSlotVegetableSoup->SetPosition (82.f, 4.f);
	poSlotVegetableSoup->SetCallback ([this] () { FoodEating (); });
	m_oInventoryContainer.Pack (poSlotVegetableSoup);
  m_oInventoryContainer.Deselect ();
  m_bFoodCollecting = GL_FALSE;
  // Initialize the score won.
  m_iScoreWonTime = -1;
  m_oScoreWon.SetFont (m_stContext.m_oBmpFont);
  m_oScoreWon.SetString ("");
  m_oScoreWon.SetColor (sf::Color::Cyan);

  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  m_uiLevel_ID          = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oLevel  = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiLevel_ID);
  oLevel.SetFont        (m_stContext.m_oBmpFont);
  oLevel.SetStyle       (sf::Text::Style::Bold);
  oLevel.SetColor       (sf::Color::Yellow);
	oLevel.setPosition    (12.f, 12.f);

  m_uiScoreTexts_ID       = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oScoreTexts = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScoreTexts_ID);
  oScoreTexts.SetFont     (m_stContext.m_oBmpFont);
  oScoreTexts.SetStyle    (sf::Text::Style::Bold);
  oScoreTexts.SetColor    (sf::Color::Yellow);

  m_uiTotalScore_ID       = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);
  oTotalScore.SetFont     (m_stContext.m_oBmpFont);
  oTotalScore.SetStyle    (sf::Text::Style::Bold);
  oTotalScore.SetColor    (sf::Color::Yellow);
	oTotalScore.setPosition (fScreenWidth-12.f, 5.f);

  m_uiCurrentScore_ID       = oRenderList2D.PushBack<drimi::BmpText> ();
  drimi::BmpText& oCurrentScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiCurrentScore_ID);
  oCurrentScore.SetFont     (m_stContext.m_oBmpFont);
  oCurrentScore.SetStyle    (sf::Text::Style::Bold);
  oCurrentScore.SetColor    (sf::Color::Yellow);
	oCurrentScore.setPosition (fScreenWidth-12.f, 22.f);

	// Initialize the main view
	m_sfMainView.reset (sf::FloatRect(0.f, 0.f, fScreenWidth, fScreenHeight));
	m_sfMainView.setViewport (sf::FloatRect (0.f, 0.f, 1.f, 1.f));

	// Initialize the world view
  m_oGOWorldView.SetScale (0.5f, 0.5f);
	m_oGOWorldView.SetSize (fScreenWidth, fScreenHeight-42.f);
  m_oGOWorldView.SetRenderTargetSize (fScreenWidth, fScreenHeight);
	m_oGOWorldView.SetViewport (0.f, 42.f, fScreenWidth, fScreenHeight-42.f);

  gmMainWindow.DisableSFML ();

  m_bEndGame = GL_FALSE;

  return GL_TRUE;
}

////////////////////////////////////////////////////////////
void WorldState::ResizeView ( void ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);

  GLfloat fScreenWidth = static_cast<GLfloat> (gmMainWindow.GetWidth ());
  GLfloat fScreenHeight = static_cast<GLfloat> (gmMainWindow.GetHeight ());

  // Update the main view
	m_sfMainView.reset (sf::FloatRect (0.f, 0.f, fScreenWidth, fScreenHeight));

	// Update main board and scores
	m_sfMainBoard[1].setScale       (sf::Vector2f (fScreenWidth-12.f, 1.f));
	m_sfMainBoard[2].setPosition    (fScreenWidth-6.f, 0.f);

  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);
	oTotalScore.setPosition (fScreenWidth-12.f, 5.f);

  drimi::BmpText& oCurrentScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiCurrentScore_ID);
	oCurrentScore.setPosition (fScreenWidth-12.f, 22.f);

  // Update the world view
  m_oGOWorldView.SetScale (0.5f, 0.5f);
	m_oGOWorldView.SetSize (fScreenWidth, fScreenHeight-42.f);
  m_oGOWorldView.SetRenderTargetSize (fScreenWidth, fScreenHeight);
	m_oGOWorldView.SetViewport (0.f, 42.f, fScreenWidth, fScreenHeight-42.f);
	m_bScrolling = GL_TRUE;
}

////////////////////////////////////////////////////////////
void WorldState::Draw ( void ) {
  // Getting of the needed systems.
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  FoodsManager& oFoodsManager = m_stContext.GetFoodsManager ();

  gmMainWindow.EnableSFML ();

  // Activating of the main view.
  gmMainWindow.setView (m_sfMainView);

  // Draw the main board.
  for (GLuint uiI = 0 ; uiI < 3 ; uiI++)
    gmMainWindow.Draw (m_sfMainBoard[uiI]);
  drimi::BmpText& oLevel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiLevel_ID);
  gmMainWindow.Draw (oLevel);
  // Draw the inventory.
  gmMainWindow.Draw (m_sfInventory);

  // Draw the inventory and its components.
  m_oInventoryContainer.Update ();
  gmMainWindow.Draw (m_oInventoryContainer);

  drimi::BmpText oFoodCount;
  oFoodCount.SetFont      (m_stContext.m_oBmpFont);
  oFoodCount.SetColor     (sf::Color::Yellow);

  oFoodsManager.Draw      (Foods::Type::Fruit, 158.f, 6.f, 2.f);
  oFoodCount.SetString    (drimi::ToString (m_uiInventory[Foods::Type::Fruit]));
  oFoodCount.setPosition  (181.f, 25.f);
  gmMainWindow.Draw       (oFoodCount);

  oFoodsManager.Draw      (Foods::Type::Bread, 196.f, 6.f, 2.f);
  oFoodCount.SetString    (drimi::ToString (m_uiInventory[Foods::Type::Bread]));
  oFoodCount.setPosition  (219.f, 25.f);
  gmMainWindow.Draw       (oFoodCount);

  oFoodsManager.Draw      (Foods::Type::VegetableSoup, 234.f, 6.f, 2.f);
  oFoodCount.SetString    (drimi::ToString (m_uiInventory[Foods::Type::VegetableSoup]));
  oFoodCount.setPosition  (257.f, 25.f);
  gmMainWindow.Draw       (oFoodCount);

  drimi::BmpText& oScoreTexts = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiScoreTexts_ID);
	oScoreTexts.setPosition (static_cast<GLfloat>(gmMainWindow.GetWidth ()-300), 5.f);
  oScoreTexts.SetString ("Total score :");
  gmMainWindow.Draw (oScoreTexts);
  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);
  gmMainWindow.Draw (oTotalScore);

	oScoreTexts.setPosition (static_cast<GLfloat>(gmMainWindow.GetWidth ()-300), 22.f);
  oScoreTexts.SetString ("Current score :");
  gmMainWindow.Draw (oScoreTexts);
  drimi::BmpText& oCurrentScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiCurrentScore_ID);
  gmMainWindow.Draw (oCurrentScore);

  m_oGOWorldView.Draw ();

  // Activating of the world view.
  gmMainWindow.setView (m_oGOWorldView);

  // Draw the terrain and the player.
  GOTerrain& oGOTerrain = oGameObjectsManager.GetGameObject<GOTerrain> (GameObjects::Type::Terrain, m_uiTerrain);
  oGOTerrain.Draw ();
  GOPlayer& oGOPlayer = oGameObjectsManager.GetGameObject<GOPlayer> (GameObjects::Type::Player, m_uiPlayer);
  oGOPlayer.Draw ();
  oGOTerrain.DrawShadows ();

  // Draw the score won on the player.
  if (m_iScoreWonTime >= 0)
    gmMainWindow.Draw (m_oScoreWon);

  gmMainWindow.DisableSFML ();
}

////////////////////////////////////////////////////////////
GLboolean WorldState::Update ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  GOTerrain& oGOTerrain = oGameObjectsManager.GetGameObject<GOTerrain> (GameObjects::Type::Terrain, m_uiTerrain);
  GOPlayer& oGOPlayer = oGameObjectsManager.GetGameObject<GOPlayer> (GameObjects::Type::Player, m_uiPlayer);
  LevelsManager& oLevelsManager = m_stContext.GetLevelsManager ();
  ScoreBoard& oScoreBoard = m_stContext.GetScoreBoard ();
  RenderList2D& oRenderList2D = m_stContext.GetRenderList2D (m_uiRenderList2D_ID);
  drimi::BmpText& oLevel = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiLevel_ID);
  drimi::BmpText& oCurrentScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiCurrentScore_ID);
  drimi::BmpText& oTotalScore = oRenderList2D.GetDrawable<drimi::BmpText> (m_uiTotalScore_ID);

  // Manage the levels
  if (oLevelsManager.GetState () == LevelsManager::START) {
    // Generate the labyrinth
    oGOTerrain.Reset ();
    oGOTerrain.PositionateStartNode ();
    oGOTerrain.GenerateLabyrinth ();
    // Place the player.
    GLuint uiX, uiY;
    oGOTerrain.GetStartPosition (uiX, uiY);
    oGOPlayer.SetPosition (uiX, uiY);
    // Activate scrolling
    m_bScrolling = GL_TRUE;
    // Set current score
    oScoreBoard.SetCurrentScore (3000);
    oCurrentScore.SetColor (sf::Color::Yellow);
    // Set the level to running state
    oLevelsManager.IncrementLevel ();
    /*std::cout << "Current step : " << oLevelsManager.GetStepsCount () << std::endl;
    std::cout << "Current level in the step : " << oLevelsManager.GetSubLevelsCount () << std::endl;*/
    oLevelsManager.SetState (LevelsManager::RUNNING);
  } else if (oLevelsManager.GetState () == LevelsManager::FINISH) {
    if (!m_bEndGame) {
      if (oLevelsManager.GetStepsCount () == Tiles::Theme::Th_Count-1 && oLevelsManager.GetSubLevelsCount () == 4 && !m_bGameOver) {  // If this is the end of the game.
        oGOTerrain.RevealTerrain ();
        oScoreBoard.ComputeTotalScore ();
        RequestStackPush (States::ID::GameOver);
        m_bGameOver = GL_TRUE;
        m_bEndGame = GL_TRUE;
      } else {
        oScoreBoard.ComputeTotalScore ();
        oLevelsManager.SetState (LevelsManager::START);
      }
    }
  } else if (oLevelsManager.GetState () == LevelsManager::RUNNING) {
    // Manage the movement of the player
    GLuint uiPlayerX, uiPlayerY;
    GLuint uiPlayerNewX, uiPlayerNewY;
    if (oGOPlayer.GetMovePosition (uiPlayerNewX, uiPlayerNewY)) {
      if (oGOTerrain.IsObstacle (uiPlayerNewX, uiPlayerNewY)) {
        oGOPlayer.ClearMove ();
      } else {
        // Update of the player position
        oGOPlayer.Update ();
        if (!oGOPlayer.IsMoving ()) {
          // Substract 10 points at the current score
          GLuint uiStartX, uiStartY;
          GLuint uiGoalX, uiGoalY;
          oGOTerrain.GetStartPosition (uiStartX, uiStartY);
          oGOTerrain.GetGoalPosition (uiGoalX, uiGoalY);
          oGOPlayer.GetPosition (uiPlayerX, uiPlayerY);
          if (!(uiPlayerX == uiStartX && uiPlayerY == uiStartY) &&
              !(uiPlayerNewX == uiGoalX && uiPlayerNewY == uiGoalY)) {
            oScoreBoard.AddInCurrentScore (-10);
          }
        }
        // Activate scrolling
        m_bScrolling = GL_TRUE;
      }
    }
    if (oScoreBoard.GetCurrentScore () > 0) {
      oGOPlayer.GetPosition (uiPlayerX, uiPlayerY);
      oGOTerrain.UpdateVisibility (uiPlayerX, uiPlayerY);
      // The current score under 1000 is orange and the screen background is red.
      if (oScoreBoard.GetCurrentScore () < 1000) {
        oCurrentScore.SetColor (sf::Color (255, 128, 0));
        if (m_uiRedAlert == 248)
          m_bNDA_Increment = GL_FALSE;
        else if (m_uiRedAlert == 0)
          m_bNDA_Increment = GL_TRUE;
        if (m_bNDA_Increment)
          m_uiRedAlert += 8;
        else
          m_uiRedAlert -= 8;
        m_stContext.m_oGraphicsEngine.SetScreenColor (m_uiRedAlert, 0, 0, 255);
      } else {
        oCurrentScore.SetColor (sf::Color::Yellow);
        m_stContext.m_oGraphicsEngine.SetScreenColor (0, 0, 0, 255);
      }
    } else if (!m_bGameOver) {  // If the current score is null, the map is revealed.
      oGOTerrain.RevealTerrain ();
      oCurrentScore.SetColor (sf::Color::Red);
      RequestStackPush (States::ID::GameOver);
      m_bGameOver = GL_TRUE;
    }
    // If the player is on the goal tile.
    GLuint uiX, uiY;
    oGOPlayer.GetPosition (uiPlayerX, uiPlayerY);
    oGOTerrain.GetGoalPosition (uiX, uiY);
    if (uiPlayerX == uiX && uiPlayerY == uiY) {
      oLevelsManager.SetState (LevelsManager::FINISH);
    }
    // if the player try to collect the food from the ground.
    if (m_bFoodCollecting) {
      Foods::Type eFoodOnTheGround = oGOTerrain.GetFood (uiPlayerX, uiPlayerY);
      if (eFoodOnTheGround != Foods::Type::Count && m_uiInventory[eFoodOnTheGround] < 9) {
        oGOTerrain.SetFood (Foods::Type::Count, uiPlayerX, uiPlayerY);
        m_uiInventory[eFoodOnTheGround]++;
      }
      m_bFoodCollecting = GL_FALSE;
    }
    // Animation of the score won.
    if (m_iScoreWonTime >= 0) {
      if (m_iScoreWonTime < 20) {
        m_oScoreWon.setPosition (m_oScoreWon.getPosition ().x, m_oScoreWon.getPosition ().y-1.f);
        m_iScoreWonTime++;
      } else {
        m_iScoreWonTime = -1;
      }
    }
  }
  // Update the scrolling.
  if (m_bScrolling) {
    // Compute the scrolling.
    GLfloat fTerrainPixWidth, fTerrainPixHeight;
    GLfloat fPlayerPixX, fPlayerPixY;
    oGOTerrain.GetSizeInPixels (fTerrainPixWidth, fTerrainPixHeight);
    oGOPlayer.GetCenterInPixels (fPlayerPixX, fPlayerPixY);
    m_oGOWorldView.Scrolling (fPlayerPixX, fPlayerPixY, fTerrainPixWidth, fTerrainPixHeight);
    // Compute the frustumCulling.
    oGOTerrain.FrustumCulling (m_oGOWorldView.getCenter (), m_oGOWorldView.getSize ());
    // Disactivate scrolling.
    m_bScrolling = GL_FALSE;
  }

  // Update of the main board
  oLevel.SetString (oLevelsManager.ToString ());

  oTotalScore.SetString (oScoreBoard.ToStringTotal ());
  oTotalScore.SetOrigin (oTotalScore.GetLocalBounds ().width, 0.f);

  oCurrentScore.SetString (oScoreBoard.ToStringCurrent ());
  oCurrentScore.SetOrigin (oCurrentScore.GetLocalBounds ().width, 0.f);

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean WorldState::HandleEvent ( const drimi::Event::Type eEventType, const sf::Keyboard::Key sfKeyCode ) {
  // Getting of the needed systems
  gm::RenderWindow& gmMainWindow = GetMainWindow ();
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();

	if (eEventType == drimi::Event::Type::KeyPressed) {
    switch (sfKeyCode) {
      /*case sf::Keyboard::Key::Escape :
        gmMainWindow.Close ();
        break;*/
      case sf::Keyboard::Key::I :
        if (m_oInventoryContainer.IsSelected ()) {
          m_oInventoryContainer.Deselect ();
        } else {
          m_oInventoryContainer.Select ();
        }
        break;
      case sf::Keyboard::Key::C :
        m_bFoodCollecting = GL_TRUE;
        break;
      default :
        break;
    }
	}
  // Event of the inventory and its components
  if (m_oInventoryContainer.IsSelected ())
    m_oInventoryContainer.HandleEvent (eEventType, sfKeyCode);

	return GL_FALSE;
}

////////////////////////////////////////////////////////////
GLboolean WorldState::HandleInput ( void ) {
  // Getting of the needed systems
  GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
  GOPlayer& oGOPlayer = oGameObjectsManager.GetGameObject<GOPlayer> (GameObjects::Type::Player, m_uiPlayer);

  if (!m_oInventoryContainer.IsSelected ())
    oGOPlayer.HandleInput ();

  return GL_FALSE;
}

////////////////////////////////////////////////////////////
void WorldState::FoodEating ( void ) {
  Foods::Type eFoodType = static_cast<Foods::Type> (m_oInventoryContainer.GetSelection ());
  if (m_uiInventory[eFoodType] > 0) {
    // Getting of the needed systems.
    ScoreBoard& oScoreBoard     = m_stContext.GetScoreBoard ();
    FoodsManager& oFoodsManager = m_stContext.GetFoodsManager ();
    GameObjectsManager& oGameObjectsManager = m_stContext.GetGameObjectsManager ();
    GOPlayer& oGOPlayer = oGameObjectsManager.GetGameObject<GOPlayer> (GameObjects::Type::Player, m_uiPlayer);
    // Set the inventory and add a score won in the current score.
    m_uiInventory[eFoodType]--;
    GLint FoodScore = oFoodsManager.GetFoodScore (eFoodType);
    if (oScoreBoard.GetCurrentScore () + FoodScore > 3000)
      FoodScore = 3000 - oScoreBoard.GetCurrentScore ();
    oScoreBoard.AddInCurrentScore (FoodScore);
    m_iScoreWonTime = 0;
    // Create the score won rendering.
    GLfloat fPlayerX, fPlayerY;
    oGOPlayer.GetCenterInPixels (fPlayerX, fPlayerY);
    m_oScoreWon.SetString ("+"+drimi::ToString (FoodScore));
    m_oScoreWon.SetOrigin (m_oScoreWon.GetLocalBounds ().width/2.f, m_oScoreWon.GetLocalBounds ().height/2.f);
    m_oScoreWon.setPosition (fPlayerX, fPlayerY);
  }
}

////////////////////////////////////////////////////////////
// Internal methods
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
gm::RenderWindow& WorldState::GetMainWindow ( void ) {
  return GetContext ().m_oRenderTargetsManager.GetRenderTargetObject<gm::RenderWindow> (RenderTargets::ID::MainWindow);
}
