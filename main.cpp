#include <iostream>
#include "card.h"
#include "gameFunc.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

int main() {
    srand(time(NULL));
    sf::Clock clickDelay;
    bool waiting = false;
    int firstCard = -1;
    int firstId = -1;
    int secondId = -1;
    bool win = false;
    std::vector<Card> mainVec;
    std::vector<sf::Texture> textures;
    const sf::Texture backside("Textures/backside.png");
    for (int i = 1;i<9;i++)
    {
        std::string tmp = std::to_string(i);
        tmp = "Textures/"+tmp+".png";
        textures.emplace_back(tmp);
    }
    fillVector(mainVec,textures,backside);
    shuffleVector(mainVec);
    cardsToPositions(mainVec);
	sf::RenderWindow window(sf::VideoMode({1200,800}),"Pair game");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    if (waiting)
                        continue;
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseButtonPressed->position);
                    for (int i = 0;i<mainVec.size();i++)
                    {
                        if (mainVec[i].contains(mousePos) && !mainVec[i].isfliped()) {
                            if (firstCard==-1)
                            {
                                mainVec[i].flip();
                                firstCard = mainVec[i].getId();
                                firstId = i;
                            }
                            else if (firstCard!=mainVec[i].getId())
                            {
                                waiting = true;
                                clickDelay.restart();
                                mainVec[i].flip();
                                secondId = i;
                            }
                            else 
                            {
                                waiting = true;
                                clickDelay.restart();
                                win = true;
                                mainVec[i].flip();
                                secondId = i;
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (waiting)
        {
            if (win)
            {
                if (clickDelay.getElapsedTime().asSeconds() >= 0.5f)
                {
                    mainVec[firstId].flip();
                    mainVec[firstId].setMatched();
                    mainVec[secondId].flip();
                    mainVec[secondId].setMatched();
                    win = false;
                    firstCard = -1;
                    firstId = -1;
                    secondId = -1;
                    waiting = false;
                }
            }
            else
            {
                if (clickDelay.getElapsedTime().asSeconds() >= 1.5f)
                {
                    mainVec[firstId].flip();
                    mainVec[secondId].flip();
                    firstCard = -1;
                    firstId = -1;
                    secondId = -1;
                    waiting = false;
                }
            }

        }
        window.clear();
        for (int i = 0;i<mainVec.size();i++)
        {
                mainVec[i].draw(window);
        }
        window.display();
    }
	return 0;
}
