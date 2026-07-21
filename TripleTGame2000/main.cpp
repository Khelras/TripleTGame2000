#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML works!");

    // Create a Graphical Circle to Fill
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 300.f, 200.f });

    // Start the Game Loop
    while (window.isOpen())
    {
        // Process Events
        while (const std::optional event = window.pollEvent())
        {
            // Close Window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear Screen
        window.clear();

        // Draw the shape
        window.draw(shape);

        // Update the window
        window.display();
    }

    return 0;
}