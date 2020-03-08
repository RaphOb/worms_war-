//
// Created by lafay on 26/02/2020.
//

#include "Node.hh"
#include "../Loader/ResourceLoader.hh"
#include "../Constant.hh"

Node::Node(int y, int x) : y(y), x(x) {
    status = 0;

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
    m_textG->setString("34");
    m_textG->setPosition({x*Constant::BLOCK_SIZE, y*Constant::BLOCK_SIZE});
    m_textG->setFont(ResourceLoader::getInstance().getFont());
    m_textG->setCharacterSize(10);
    m_textG->setFillColor(sf::Color(0, 0, 0));

    m_textH = new sf::Text();
    m_textH->setString("34");
    m_textH->setPosition({x*Constant::BLOCK_SIZE+18, y*Constant::BLOCK_SIZE});
    m_textH->setFont(ResourceLoader::getInstance().getFont());
    m_textH->setCharacterSize(10);
    m_textH->setFillColor(sf::Color(0, 0, 0));

    m_textF = new sf::Text();
    m_textF->setString("34");
    m_textF->setPosition({x*Constant::BLOCK_SIZE+6, y*Constant::BLOCK_SIZE+10});
    m_textF->setFont(ResourceLoader::getInstance().getFont());
    m_textF->setCharacterSize(14);
    m_textF->setFillColor(sf::Color(0, 0, 0));
}

void Node::draw(sf::RenderWindow &window) {
    window.draw(*m_textG);
    window.draw(*m_textH);
    window.draw(*m_textF);
    window.draw(m_rect);
}

int Node::getX() { return x; }

int Node::getY() { return y; }

int Node::getStatus() { return status; }

void Node::setStatus(int s) { status = s; }

int Node::setGCost(int c) { gCost = c; }

int Node::getGCost() { return gCost; }

int Node::setHCost(int c) { hCost = c; }

int Node::getHCost() { return hCost; }

int Node::setFCost(int c) { fCost = c; }

int Node::getFCost() { return fCost; }