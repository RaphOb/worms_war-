//
// Created by lafay on 26/02/2020.
//

#include <cmath>
#include "Node.hh"
#include "../Loader/ResourceLoader.hh"
#include "../Constant.hh"

Node::Node(int y, int x) : y(y), x(x) {
    status = 0;
    m_parent = nullptr;
    initTextures();
}

/**
 * top left Gcost
 * top right Hcost
 * middle Fcost
 */
void Node::initTextures() {
    m_rect.setSize({Constant::BLOCK_SIZE, Constant::BLOCK_SIZE});
    m_rect.setPosition({x*Constant::BLOCK_SIZE, y*Constant::BLOCK_SIZE});
    m_rect.setFillColor(sf::Color::Transparent);
    m_rect.setOutlineColor(sf::Color::Blue);
    m_rect.setOutlineThickness(1);

    m_textG = new sf::Text();
    m_textG->setString("99");
    m_textG->setPosition({x*Constant::BLOCK_SIZE, y*Constant::BLOCK_SIZE});
    m_textG->setFont(ResourceLoader::getInstance().getFont());
    m_textG->setCharacterSize(8);
    m_textG->setFillColor(sf::Color(0, 0, 0));

    m_textH = new sf::Text();
    m_textH->setString("99");
    m_textH->setPosition({x*Constant::BLOCK_SIZE+18, y*Constant::BLOCK_SIZE});
    m_textH->setFont(ResourceLoader::getInstance().getFont());
    m_textH->setCharacterSize(8);
    m_textH->setFillColor(sf::Color(0, 0, 0));

    m_textF = new sf::Text();
    m_textF->setString("99");
    m_textF->setPosition({x*Constant::BLOCK_SIZE+6, y*Constant::BLOCK_SIZE+10});
    m_textF->setFont(ResourceLoader::getInstance().getFont());
    m_textF->setCharacterSize(14);
    m_textF->setFillColor(sf::Color(0, 0, 0));
}

void Node::draw(sf::RenderWindow &window) {
    window.draw(m_rect);
    //window.draw(*m_textG);
    //window.draw(*m_textH);
    //window.draw(*m_textF);
    m_rect.setFillColor(sf::Color::Transparent);
}

int Node::getX() const { return x; }

int Node::getY() { return y; }

int Node::getStatus() { return status; }

void Node::setStatus(int s) {
    status = s;
}

int Node::setGCost(int c) {
    gCost = c;
    m_textG->setString(std::to_string(gCost));
}

int Node::getGCost() { return gCost; }

int Node::setHCost(int c) {
    hCost = c;
    m_textH->setString(std::to_string(hCost));
}

int Node::getHCost() { return hCost; }

int Node::setFCost(int c) {
    fCost = c;
    m_textF->setString(std::to_string(fCost));
}

int Node::getFCost() const { return fCost; }

void Node::resetNode() {
    m_parent = nullptr;
    setGCost(99);
    setHCost(99);
    setFCost(99);
}

void Node::setCostByNode(Node *targetNode, Node *originNode) {
    setColorByStatus();
    int c1GCost = std::pow(abs(originNode->getX()-this->getX()), 2);
    int c2GCost = std::pow(abs(originNode->getY()-this->getY()), 2);
    float c3GCost = std::sqrt(c1GCost+c2GCost);
    int GCost = floor(c3GCost*10);

    int c1HCost = std::pow(abs(targetNode->getX()-this->getX()), 2);
    int c2HCost = std::pow(abs(targetNode->getY()-this->getY()), 2);
    float c3HCost = std::sqrt(c1HCost+c2HCost);
    int HCost = floor(c3HCost*10);

    setGCost(GCost);
    setHCost(HCost);
    setFCost(GCost+HCost);
}

sf::RectangleShape *Node::getRect() {
    return &m_rect;
}

void Node::setColorByStatus() {
    if (status == 0) {
        m_rect.setOutlineColor(sf::Color::Blue);
    } else {
        m_rect.setOutlineColor(sf::Color::Magenta);
    }
}

void Node::setParent(Node *parent) {
    m_parent = parent;
}

Node *Node::getParent() {
    return m_parent;
}
