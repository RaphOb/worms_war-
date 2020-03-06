//
// Created by oraph on 06/03/2020.
//

#include "TextManager.hh"
#include "Loader/ResourceLoader.hh"
#include "Constant.hh"
#include <fstream>
#include <iostream>

void TextManager::setText(const std::string &string, TypeText type) {
    if(type == TypeText::MONSTER) {
        textNbMonster.setString(string);
    } else if(type == TypeText::SCORES) {
        nbScores.setString(string);
    } else if (type == TypeText::LASTSCORE) {
        lastScores.setString(string);
    }
}

void TextManager::draw(sf::RenderWindow &window) {
    window.draw(textNbMonster);
    window.draw(nbScores);
    window.draw(lastScores);
}

TextManager::TextManager() {
    textNbMonster.setFont(ResourceLoader::getInstance().getFont());
    nbScores.setFont(ResourceLoader::getInstance().getFont());
    lastScores.setFont(ResourceLoader::getInstance().getFont());
    textNbMonster.setOutlineColor(sf::Color::Black);
    nbScores.setOutlineColor(sf::Color::Black);
    lastScores.setOutlineColor(sf::Color::Black);
    textNbMonster.setOutlineThickness(2.f);
    nbScores.setOutlineThickness(2.f);
    lastScores.setOutlineThickness(2.f);
    textNbMonster.setCharacterSize(20);
    nbScores.setCharacterSize(20);
    lastScores.setCharacterSize(20);
    textNbMonster.setPosition(Constant::VIEW_WIDTH - 50, 0.f);
    nbScores.setPosition(Constant::VIEW_WIDTH - 500, 0.f);
    lastScores.setPosition(Constant::VIEW_WIDTH - 1300, 0.f);
}

void TextManager::loadFileScore() {
    std::string line;
    std::ifstream myfile ("test.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            lastScores.setString(line);
        }
        myfile.close();
    }
}

void TextManager::saveScore() {
    std::ofstream ofs;
    ofs.open ("test.txt", std::ofstream::out | std::ofstream::trunc);
    std::string c  = nbScores.getString();
    ofs << c;

    ofs.close();
}
