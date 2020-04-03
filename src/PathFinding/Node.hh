//
// Created by lafay on 26/02/2020.
//

#ifndef LITTLEBIGGAME_NODE_HH
#define LITTLEBIGGAME_NODE_HH

//https://www.youtube.com/watch?v=-L-WgKMFuhE

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Node {
private:
    int x;
    int y;
    int status;
    int gCost;
    int hCost;
    int fCost;
    sf::RectangleShape m_rect;
    sf::Text* m_textG;
    sf::Text* m_textH;
    sf::Text* m_textF;
    Node *m_parent;
public:
    Node(int y, int x);
    int getX() const;
    int getY() const;
    int getStatus() const;
    void setStatus(int);
    int getGCost() const;
    int setGCost(int);
    int getHCost() const;
    int setHCost(int);
    int getFCost() const;
    int setFCost(int);
    void initTextures();
    void draw(sf::RenderWindow& window);
    void resetNode();
    void setCostByNode(Node*, Node*);
    sf::RectangleShape* getRect();
    void setColorByStatus();
    void setParent(Node *);
    Node *getParent();
    bool isInDiagonale(Node *node);
};

#endif //LITTLEBIGGAME_NODE_HH
