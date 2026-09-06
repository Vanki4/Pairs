#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "card.h"
#include "gameFunc.h"
#include <ctime>
#include <cstdlib>

class Game {
    private:
    sf::RenderWindow window;
    std::vector<Card> cards;
    std::vector<sf::Texture> textures;
    sf::Texture backside;
    sf::Font font;
    sf::Text turnsText;
    sf::Text finalScore;
    sf::ConvexShape playIcon;
    sf::Clock clickDelay;

    int cntTurns = 0;
    int cntWins = 0;
    int bestResult = 0;
    int firstCard = -1;
    int firstId = -1;
    int secondId = -1;
    bool waiting = false;
    bool win = false;
    bool gameStart = false;
    
    void loadTextures();
    void createCards();
    void processEvents();
    void processStartScreenEvents();
    void processGameEvents();
    void update();
    void draw();
    void drawStartScreen();
    void drawGame();
    void handleCardClick(sf::Vector2f mousePos);
    void updateWaitingCards();
    void restartGame();
    void finishGame();

    public:
    Game();
    void run();
};