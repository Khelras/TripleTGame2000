#include "cProjectManager.h"
#include "CUIManager.h"
#include "CInputHandler.h"
#include "cCamera.h"

// Turns seconds into "1:05" for the timer label
static std::string FormatTime(float _seconds)
{
    if (_seconds < 0.0f) _seconds = 0.0f;

    int total = int(_seconds);
    int minutes = total / 60;
    int seconds = total % 60;

    return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
}

cProjectManager::cProjectManager()
{
    // ~~~ Create the Windows ~~~ //
    m_Window.create(sf::VideoMode({ m_WindowWidth, m_WindowHeight }), "Axis Bound", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    sf::VideoMode Desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u WindowSize = m_Window.getSize();
    m_Window.setPosition(sf::Vector2i((Desktop.size.x - WindowSize.x - 100), (Desktop.size.y - WindowSize.y) / 2));



    m_DeltaTime = 0.0f;
    m_LevelTime = m_LevelTimeLimit;

    m_MainCamera = new cCamera(sf::Vector2f(m_WindowWidth / 2, m_WindowHeight / 2), sf::Vector2f(m_WindowWidth, m_WindowHeight));



    // ~~~ Make the level and load the first level ~~~ //
    m_LevelManager = new cLevelManager(&m_GlobalAudioManager);
    m_LevelManager->LoadLevel(0);
}
cProjectManager::~cProjectManager()
{
}




// ~~~~~ -= LIFE CYCLE FUNCTIONS =- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cProjectManager::Start()
{
    // Setup UIManager Stuff
    CUIManager* UIManager = CUIManager::getInstance();
    UIManager->LoadFont("font.otf");
    UIManager->SetupUI(m_Window.getSize());

    // Setup InputHandler Stuff
    CInputHandler* InputHandler = CInputHandler::getInstance();
    InputHandler->SetWindow(&m_Window);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cProjectManager::RunProgram()
{
    Start();

    while (m_Window.isOpen())
    {
        Update();
    }
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cProjectManager::Update()
{
    // Calibrate DeltaTime
    float FPSCap = 60.0f;

    m_DeltaTime = m_Clock.getElapsedTime().asSeconds();
    m_DeltaTime = fmin(m_DeltaTime, 1.0f / FPSCap); // Caps to FPSCap
    m_Clock.restart();


    m_LevelManager->Update(m_DeltaTime);

    UpdateGame();
    PollWindow();
    WindowDraw();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //




// ~~~~~ -= GAME LOGIC =- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cProjectManager::UpdateGame()
{
    // ~~~ -= Singletons =- ~~~ //
    CUIManager* UIManager = CUIManager::getInstance();
    CInputHandler* InputHandler = CInputHandler::getInstance();
    // ~~~~~~~~~~~~~~~~~~~~~~~~ //

    EUIState CurrentState = UIManager->GetCurrentState();

    // Just walked into a level, so put the clock back
    if (CurrentState == GAME && m_LastUIState != GAME)
    {
        m_LevelTime = m_LevelTimeLimit;
    }
    m_LastUIState = CurrentState;

    // Everything past here is gameplay, so it pauses by itself in the menus
    if (CurrentState != GAME)
        return;

    // Each player reads their own movement, using their own keys
    sf::Vector2f p1Move = InputHandler->InputVector(PLAYER_ONE);
    sf::Vector2f p2Move = InputHandler->InputVector(PLAYER_TWO);

    // Tick the timer down and push it into the HUD label
    m_LevelTime -= m_DeltaTime;

    if (m_LevelTime <= 0.0f)
    {
        m_LevelTime = 0.0f;
        UIManager->SetState(LEVEL_COMPLETE); // out of time
    }

    UIManager->SetLabelText("timer", FormatTime(m_LevelTime));
    UIManager->SetLabelColor("timer", m_LevelTime <= 10.0f ? sf::Color::Red : sf::Color::White);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //










// ~~~~~ -= WINDOW EVENTS =- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cProjectManager::PollWindow()
{
    // ~~~ -= Singletons =- ~~~ //
    CUIManager* UIManager = CUIManager::getInstance();
    CInputHandler* InputHandler = CInputHandler::getInstance();
    // ~~~~~~~~~~~~~~~~~~~~~~~~ //


    while (const std::optional event = m_Window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_Window.close();
    }

    // Must run once per frame, before anything reads input
    InputHandler->UpdateInput();
    InputHandler->UpdateMousePos(m_Window);

    UIManager->HandleEvent(m_Window);
    UIManager->Update(m_DeltaTime);

    if (UIManager->WantsToQuit())
        m_Window.close();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cProjectManager::WindowDraw()
{
    // ~~~ -= Singletons =- ~~~ //
    CUIManager* UIManager = CUIManager::getInstance();
    CInputHandler* InputHandler = CInputHandler::getInstance();
    // ~~~~~~~~~~~~~~~~~~~~~~~~ //

    m_Window.clear();
    m_Window.setView(*m_MainCamera->m_CameraView);

    // Game drawing goes here for when the UI is in the GAME state
    if (UIManager->GetCurrentState() == GAME)
    {
        // Each player reads their own movement, using their own keys
        sf::Vector2f p1Move = InputHandler->InputVector(PLAYER_ONE);
        sf::Vector2f p2Move = InputHandler->InputVector(PLAYER_TWO);

        m_LevelManager->Draw(&m_Window);
    }

    // UI is screen space, so drop back to the default view or it scrolls with the camera
    m_Window.setView(m_Window.getDefaultView());

    UIManager->Draw(m_Window);
    m_Window.display();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
