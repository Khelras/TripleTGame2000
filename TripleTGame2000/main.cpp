#include <SFML/Graphics.hpp>
#include "CUIManager.h"
#include "CInputHandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Triple T Game");

    CUIManager* ui = CUIManager::getInstance();
    ui->LoadFont("font.otf");
    ui->SetupUI(window.getSize());

    CInputHandler* input = CInputHandler::getInstance();
    input->SetWindow(&window);

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Must run once per frame, before anything reads input
        input->UpdateInput();
        input->UpdateMousePos(window);

        ui->HandleEvent(window);
        ui->Update(dt);

        if (ui->WantsToQuit())
            window.close();

        window.clear();

        // Game drawing goes here for when the UI is in the GAME state
        if (ui->GetCurrentState() == GAME)
        {
            // Each player reads their own movement, using their own keys
            sf::Vector2f p1Move = input->InputVector(PLAYER_ONE);
            sf::Vector2f p2Move = input->InputVector(PLAYER_TWO);

            // e.g. Levels->Draw(window, ui->GetSelectedLevel());
        }

        ui->Draw(window);
        window.display();
    }

    return 0;
}
