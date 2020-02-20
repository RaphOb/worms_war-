//
// Created by geoff on 13/02/2020.
//

#include <iostream>
#include "Collider.hh"

Collider::Collider(sf::RectangleShape* body) : body(body) {

}

sf::Vector2f Collider::getPosition() {
    return body->getPosition();
}

sf::Vector2f Collider::getHalfSize() {
    return body->getSize() / 2.0f;
}

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push) {
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition  = getPosition();
    sf::Vector2f thisHalfSize  = getHalfSize();

//    std::cout << "otherHalfsize: " << otherHalfSize.x << ", " << otherHalfSize.y << std::endl;
//    std::cout << "thisHalfsize: " << thisHalfSize.x << ", " << thisHalfSize.y << std::endl;
//    std::cout <<"otherPosition: " << otherPosition.x << ", " << otherPosition.y << std::endl;
//    std::cout << "thisPosition: " << thisPosition.x << ", " << thisPosition.y << std::endl;

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
//    std::cout << "deltaX: " << deltaX << std::endl;
//    std::cout << "deltaY: " << deltaY << std::endl;
    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
//    std::cout << "intersectX: " << intersectX << std::endl;
//    std::cout << "intersectY: " << intersectY << std::endl;


    if (intersectX < 0.0f && intersectY < 0.0f) {

        push = std::min(std::max(push, 0.0f), 1.0f);
        if (intersectX > intersectY) {
            // Push on the x abscissa
            if (deltaX > 0.0f) {
                std::cout << "pushing left" << std::endl;
                move(intersectX * (1.0f - push), 0.0f);
                other.move(-intersectX * push, 0.0f);
                direction.x = 1.0f;
                direction.y = 0.0f;
            } else {
                std::cout << "pushing right" << std::endl;
                move(-intersectX * (1.0f - push), 0.0f);
                other.move(intersectX * push, 0.0f);
                direction.x = -1.0f;
                direction.y = 0.0f;
            }
        } else {
            // Push on the Y abscissa
            if (deltaY > 0.0f) {
                move(0.0f, intersectY * (1.0f - push));
                other.move(0.0f, -intersectY * push);
                direction.x = 0.0f;
                direction.y = 1.0f;
            } else {
                move(0.0f, -intersectY * (1.0f - push));
                other.move(0.0f, intersectY * push);
                direction.x = 0.0f;
                direction.y = -1.0f;
            }
        }
        return true;
    }
    return false;
}

void Collider::move(float dx, float dy) {
    body->move(dx, dy);
}
