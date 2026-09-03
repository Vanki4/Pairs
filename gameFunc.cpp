#include "gameFunc.h"

void fillVector(std::vector<Card>& vec,const std::vector<sf::Texture>& Textures,const sf::Texture& backside) {
    for (int i = 0;i<Textures.size();i++)
    {
        Card temp1(Textures[i],backside,i);
        Card temp2(Textures[i],backside,i);
        vec.emplace_back(temp1);
        vec.emplace_back(temp2);
    }
}

void shuffleVector(std::vector<Card>& vec) {
    for (int i = vec.size()-1;i>0;--i)
    {
        int RandomNum = rand()%(i+1);
        std::swap(vec[i],vec[RandomNum]);
    }
}

bool equalCards(const Card& first,const Card& second) {
    return first.getId() == second.getId();
}

void cardsToPositions(std::vector<Card>& vec) {
    vec[0].setPosition({150.f, 50.f});
    vec[1].setPosition({350.f, 50.f});
    vec[2].setPosition({550.f, 50.f});
    vec[3].setPosition({750.f, 50.f});

    vec[4].setPosition({150.f, 230.f});
    vec[5].setPosition({350.f, 230.f});
    vec[6].setPosition({550.f, 230.f});
    vec[7].setPosition({750.f, 230.f});

    vec[8].setPosition({150.f, 410.f});
    vec[9].setPosition({350.f, 410.f});
    vec[10].setPosition({550.f, 410.f});
    vec[11].setPosition({750.f, 410.f});

    vec[12].setPosition({150.f, 590.f});
    vec[13].setPosition({350.f, 590.f});
    vec[14].setPosition({550.f, 590.f});
    vec[15].setPosition({750.f, 590.f});
}