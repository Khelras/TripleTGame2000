#include "cProjectManager.h"
#include "CUIManager.h"
#include "CInputHandler.h"


cProjectManager::cProjectManager()
{
    // ~~~ Create the Windows ~~~ //
    m_Window.create(sf::VideoMode({ m_WindowWidth, m_WindowHeight }), "Axis Bound", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    sf::VideoMode Desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u WindowSize = m_Window.getSize();
    m_Window.setPosition(sf::Vector2i((Desktop.size.x - WindowSize.x - 100), (Desktop.size.y - WindowSize.y) / 2));



    m_DeltaTime = 0.0f;
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
    m_DeltaTime = fmin(m_DeltaTime, 1.0f / FPSCap);  // Caps to FPSCap
    m_Clock.restart();



    PollWindow();
    WindowDraw();
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

    // Game drawing goes here for when the UI is in the GAME state
    if (UIManager->GetCurrentState() == GAME)
    {
        // Each player reads their own movement, using their own keys
        sf::Vector2f p1Move = InputHandler->InputVector(PLAYER_ONE);
        sf::Vector2f p2Move = InputHandler->InputVector(PLAYER_TWO);

        // e.g. Levels->Draw(window, ui->GetSelectedLevel());
    }

    UIManager->Draw(m_Window);
    m_Window.display();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
