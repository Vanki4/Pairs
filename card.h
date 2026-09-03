#pragma once

#include <SFML/Graphics.hpp>

class Card {
    private:
    const sf::Texture* frontTexture;
    const sf::Texture* backTexture;
    sf::Sprite sprite;
    bool fliped = false;
    bool matched = false;
    int id;
    public:
    Card(const Card& other) = default;
    Card& operator=(const Card& other) = default;
    Card(Card&& other) = default;
    Card& operator=(Card&& other) = default;
    Card(const sf::Texture& front,const sf::Texture& back,int id);
    void draw(sf::RenderWindow& win);
    bool isfliped() const;
    void flip();
    bool contains(sf::Vector2f& mousePos) const;
    void setPosition(sf::Vector2f pos);
    bool isMatched() const;
    void setMatched();
    int getId() const;
};