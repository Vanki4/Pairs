#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({800,600}),"SFML window");
	const sf::Texture texture("test.png");
    const sf::Texture texture2("test2.png");
    sf::Sprite sprite(texture);
	sprite.setPosition({100.f,100.f});
	while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseButtonPressed->position);
                    if (sprite.getGlobalBounds().contains(mousePos)) {
                        if (&sprite.getTexture() == &texture)
                            sprite.setTexture(texture2);
                        else
                            sprite.setTexture(texture);
                    }
                }
            }
	    }

        // Clear screen
        window.clear();
	window.draw(sprite);
        // Update the window
        window.display();
    }
	return 0;
}
