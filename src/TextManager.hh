//
// Created by oraph on 06/03/2020.
//

#ifndef LITTLEBIGGAME_TEXTMANAGER_HH
#define LITTLEBIGGAME_TEXTMANAGER_HH


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum class TypeText {MONSTER, SCORES,LASTSCORE};
class TextManager {
private:
    sf::Text textNbMonster;
    sf::Text nbScores;
    sf::Text lastScores;
    std::string lastScoresStr;
    int nbScoresInt;
public:
    void setText(const std::string&, TypeText type);
    TextManager();
    void draw(sf::RenderWindow&);
    void loadFileScore();
    void saveScore();
    void setNbScores(int);

};


#endif //LITTLEBIGGAME_TEXTMANAGER_HH
