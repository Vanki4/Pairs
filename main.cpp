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
    int cntTurns = 0;
    sf::Font font("Assets/font.ttf");
    sf::Text turnsText(font);
    sf::Text finalScore(font);
    turnsText.setCharacterSize(30);
    turnsText.setFillColor(sf::Color::White);
    turnsText.setPosition({950.f, 100.f});
    finalScore.setCharacterSize(30);
    finalScore.setFillColor(sf::Color::White);
    finalScore.setPosition({300.f, 300.f});
    bool waiting = false;
    int firstCard = -1;
    int firstId = -1;
    int secondId = -1;
    bool win = false;
    bool gameStart = false;
    int cntWins = 0;
    int bestResult = 0;
    sf::ConvexShape playIcon;
    playIcon.setPointCount(3);
    playIcon.setPoint(0, {0.f, 0.f});
    playIcon.setPoint(1, {0.f, 40.f});
    playIcon.setPoint(2, {35.f, 20.f});
    playIcon.setFillColor(sf::Color::White);
    playIcon.setPosition({565.f, 365.f});
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
        if (!gameStart)
        {
            while (const std::optional event = window.pollEvent())
            {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseButtonPressed->position);
                    if (playIcon.getGlobalBounds().contains(mousePos))
                        gameStart = true;
                }
            }
            }
            window.clear();
            window.draw(playIcon);
            finalScore.setString("Best result: " + std::to_string(bestResult));
            window.draw(finalScore);
            window.display();
            continue;
        }
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
        turnsText.setString("Turns: " + std::to_string(cntTurns));
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
                    cntTurns++;
                    cntWins++;
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
                    cntTurns++;
                }
            }

        }
        window.clear();
        for (int i = 0;i<mainVec.size();i++)
        {
                mainVec[i].draw(window);
        }
        window.draw(turnsText);
        window.display();
        if (cntWins==8) {
            gameStart = false;
            cntWins = 0;
            if (bestResult==0 || cntTurns < bestResult)
                bestResult = cntTurns;
            cntTurns = 0;
            mainVec.clear();
            fillVector(mainVec,textures,backside);
            shuffleVector(mainVec);
            cardsToPositions(mainVec);
        }
    }
	return 0;
}
