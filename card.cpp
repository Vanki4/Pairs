#include "card.h"
#include <SFML/Graphics.hpp>

Card::Card(const sf::Texture& front,const sf::Texture& back,int id) :
    frontTexture(&front), backTexture(&back), sprite(back), id(id)
    {
    }

void Card::draw(sf::RenderWindow& win) {
    if (!matched)
        win.draw(sprite);
}

bool Card::isfliped() const {
    return fliped;
}

void Card::flip() {
    if (!matched) {
    if (!fliped) {
        sprite.setTexture(*frontTexture);
        fliped = true;
    }
    else {
        sprite.setTexture(*backTexture);
        fliped = false;
    }
    }
}

bool Card::contains(sf::Vector2f& mousePos) const {
    if (sprite.getGlobalBounds().contains(mousePos))
        return true;
    return false;
}

void Card::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

bool Card::isMatched() const {
    return matched;
}

void Card::setMatched() {
    matched=true;
}

int Card::getId() const {
    return id;
}