#include <string>
#include "game.h"

Game::Game() : 
    window(sf::VideoMode({1280,800}),"Pair game"),
    backside("Textures/backside.png"),
    font("Assets/font.ttf"),
    turnsText(font),
    finalScore(font),
    startScreenBackGround("Textures/background1.jpeg"),
    gameBackGround("Textures/background2.jpeg"),
    backGround(startScreenBackGround)
{
    srand(time(NULL));
    turnsText.setCharacterSize(30);
    turnsText.setFillColor(sf::Color::White);
    turnsText.setPosition({950.f, 100.f});
    finalScore.setCharacterSize(60);
    finalScore.setFillColor(sf::Color::White);
    finalScore.setPosition({50.f, 700.f});
    playIcon.setPointCount(3);
    playIcon.setPoint(0, {0.f, 0.f});
    playIcon.setPoint(1, {0.f, 40.f});
    playIcon.setPoint(2, {35.f, 20.f});
    playIcon.setFillColor(sf::Color::White);
    playIcon.setPosition({596.f, 365.f});

    loadTextures();
    createCards();
}

void Game::loadTextures() {
    for (int i = 1;i<9;i++)
    {
        std::string tmp = std::to_string(i);
        tmp = "Textures/"+tmp+".png";
        textures.emplace_back(tmp);
    }
}

void Game::createCards() {
    cards.clear();
    fillVector(cards,textures,backside);
    shuffleVector(cards);
    cardsToPositions(cards);
}

void Game::run() {
    while (window.isOpen())
    {
        processEvents();
        update();
        draw();
    }
}

void Game::processEvents() {
    if (!gameStart)
        processStartScreenEvents();
    else
        processGameEvents();
}

void Game::processStartScreenEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseButtonPressed->position);
                    if (playIcon.getGlobalBounds().contains(mousePos))
                    {
                        gameStart = true;
                        backGround.setTexture(gameBackGround);
                    }
            }
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::KeyPressed>())
        {
            gameStart = true;
            backGround.setTexture(gameBackGround);
        }
    }
}

void Game::processGameEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButton->button == sf::Mouse::Button::Left)
            {
                if (waiting)
                    continue;
                sf::Vector2f mousePos = window.mapPixelToCoords(mouseButton->position);
                handleCardClick(mousePos);
            }
        }
    }
}

void Game::handleCardClick(sf::Vector2f mousePos) {
    for (int i = 0;i<cards.size();i++)
    {
        if (cards[i].contains(mousePos) && !cards[i].isfliped()) {
            if (firstCard==-1)
            {
                cards[i].flip();
                firstCard = cards[i].getId();
                firstId = i;
            }
            else if (firstCard!=cards[i].getId())
            {
                waiting = true;
                clickDelay.restart();
                cards[i].flip();
                secondId = i;
            }
            else 
            {
                waiting = true;
                clickDelay.restart();
                win = true;
                cards[i].flip();
                secondId = i;
            }
            break;
        }
    }
}

void Game::update() {
    if (!gameStart)
        return;
    turnsText.setString("Turns: " + std::to_string(cntTurns));
    updateWaitingCards();
    if (cntWins == 8)
    {
        finishGame();
        backGround.setTexture(startScreenBackGround);
    }
}

void Game::updateWaitingCards() {
    if (waiting)
    {
        if (win)
        {
            if (clickDelay.getElapsedTime().asSeconds() >= 0.5f)
            {
                cards[firstId].flip();
                cards[firstId].setMatched();
                cards[secondId].flip();
                cards[secondId].setMatched();
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
                cards[firstId].flip();
                cards[secondId].flip();
                firstCard = -1;
                firstId = -1;
                secondId = -1;
                waiting = false;
                cntTurns++;
            }
        }
    }
}

void Game::finishGame() {
    if (bestResult==0 || cntTurns < bestResult)
            bestResult = cntTurns;
    gameStart = false;
    restartGame();
}

void Game::restartGame() {
    cntTurns = 0;
    cntWins = 0;
    firstCard = -1;
    firstId = -1;
    secondId = -1;
    waiting = false;
    win = false;
    createCards();
}

void Game::draw() {
    window.clear();
    window.draw(backGround);
    if (gameStart)
        drawGame();
    else
        drawStartScreen();
    window.display();
}

void Game::drawStartScreen() {
    window.draw(playIcon);
    finalScore.setString("Best result: " + std::to_string(bestResult));
    window.draw(finalScore);
}

void Game::drawGame() {
    for (int i = 0;i<cards.size();i++)
    {
                cards[i].draw(window);
    }
    window.draw(turnsText);
}