//
// Created by lafay on 08/03/2020.
//

#include <iostream>
#include <cmath>
#include "Pathfinding.hh"
#include "../Map.hh"

Pathfinding::Pathfinding(){}

Pathfinding::Pathfinding(Map *context, Worm *target) : m_map(context), m_target(target) {}

Map *Pathfinding::getMap() { return m_map; }

void Pathfinding::setMap(Map* map) {
    m_map = map;
}

void Pathfinding::setTarget(Worm *worm) {
    m_target = worm;
}

std::vector<Direction> Pathfinding::getDirection(Node *origin) {
    std::vector<Node>* nodeGrid = getMap()->getNodeGrid();
    Node *targetNode = getMap()->getNodeByPos(std::floor(m_target->getPosition().y/Constant::BLOCK_SIZE), std::floor(m_target->getPosition().x/Constant::BLOCK_SIZE));
    for (auto &node : *nodeGrid) {
        node.resetNode();
        node.setCostByNode(targetNode, origin);
    }
    origin->getRect()->setFillColor(sf::Color(255, 255, 255, 150));
    targetNode->getRect()->setFillColor(sf::Color(255, 255, 255, 150));

    // Algo de PATHFINDING :D --- https://www.youtube.com/watch?v=-L-WgKMFuhE
    std::vector<const Node*> open;
    open.reserve(nodeGrid->size());
    std::vector<const Node*> close;
    close.reserve(nodeGrid->size());

    Node *current;
    int index;

    open.push_back(origin);

    while (true) {
        index = getNodeWithLowestFCost(open);
        current = const_cast<Node *>(open.at(index));
        open.erase(open.begin()+index);
        close.push_back(current);

        if (current==targetNode) {
            Node *displayNode = targetNode;
            while (displayNode->getParent()!= nullptr) {
                displayNode->getParent()->getRect()->setFillColor(sf::Color(255, 0, 0, 150));
                displayNode = displayNode->getParent();
            }
            displayNode->getRect()->setFillColor(sf::Color(0, 255, 0, 150));
            std::vector<Direction> resDir;
            if (origin->getX()<displayNode->getX()) resDir.push_back(RIGHT);
            if (origin->getX()>displayNode->getX()) resDir.push_back(LEFT);
            if (origin->getY()<displayNode->getY()) resDir.push_back(DOWN);
            if (origin->getY()>displayNode->getY()) resDir.push_back(UP);
            return resDir;
        }

        vector<Node *> neighbours = getNeighbourNodes(current);
        for (Node *neighbour : neighbours) {
            if (neighbour == nullptr)
                continue;
            if (neighbour->getStatus()==1 || std::find(close.begin(), close.end(), neighbour) != close.end())
                continue;
            if (awayFromOrigin(neighbour)<awayFromOrigin(current) || !(std::find(open.begin(), open.end(), neighbour) != open.end())) {
                neighbour->setCostByNode(targetNode, current);
                if (current!=origin) neighbour->setParent(current);
                if (!(std::find(open.begin(), open.end(), neighbour) != open.end()))
                    open.push_back(neighbour);

            }
        }
    }
}

int Pathfinding::getNodeWithLowestFCost(std::vector<const Node*> nodeGrid) {
    Node *res = (Node *) nodeGrid.front();
    int index = 0;
    for (unsigned i=0; i<nodeGrid.size(); i++) {
        if (nodeGrid[i]->getFCost() < res->getFCost()) {
            res= const_cast<Node *>(nodeGrid[i]);
            index = (int) i;
        }
    }
    return index;
}

std::vector<Node*> Pathfinding::getNeighbourNodes(Node *current) {
    std::vector<Node*> neighbours;
    int currentX = current->getX();
    int currentY = current->getY();

    if (currentY-1>=0 && currentY-1<getMap()->getRows() && currentX-1>=0 && currentX-1<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY-1, currentX-1)); // top left
    if (currentY-1>=0 && currentY-1<getMap()->getRows() && currentX>=0 && currentX<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY-1, currentX)); // top
    if (currentY-1>=0 && currentY-1<getMap()->getRows() && currentX+1>=0 && currentX+1<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY-1, currentX+1)); // top right
    if (currentY>=0 && currentY<getMap()->getRows() && currentX+1>=0 && currentX+1<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY, currentX+1)); // right
    if (currentY+1>=0 && currentY+1<getMap()->getRows() && currentX+1>=0 && currentX+1<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY+1, currentX+1)); // bottom right
    if (currentY+1>=0 && currentY+1<getMap()->getRows() && currentX>=0 && currentX<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY+1, currentX)); // bottom
    if (currentY+1>=0 && currentY+1<getMap()->getRows() && currentX-1>=0 && currentX-1<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY+1, currentX-1)); // bottom left
    if (currentY>=0 && currentY<getMap()->getRows() && currentX-1>=0 && currentX-1<getMap()->getCols())
        neighbours.push_back(getMap()->getNodeByPos(currentY, currentX-1)); // left

    return neighbours;
}

int Pathfinding::awayFromOrigin(Node *node) {
    int res = 0;
    while (node->getParent()!= nullptr){
        node=node->getParent();
        res++;
    }
    return res;
}
