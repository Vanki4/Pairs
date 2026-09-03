#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "card.h"

void fillVector(std::vector<Card>& vec,const std::vector<sf::Texture>& textures,const sf::Texture& backside);

void shuffleVector(std::vector<Card>& vec);

bool equalCards(const Card& first,const Card& second);

void cardsToPositions(std::vector<Card>& vec);