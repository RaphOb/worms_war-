#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "src/Tilemap.hh"
#include "src/Animation.hh"
#include "src/AnimatedSprite.hh"
#include "src/Worm.hh"

int main() {
    int height = 8;
    int width = 16;
    int tileWidth = 32;
    int tileHeight = 32;

    sf::Vector2i screenDimensions(1600, 900);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    const int level[] =
            {
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 1, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
            };

    Tilemap map;

    if (!map.load("../resources/tilemap.png", sf::Vector2u(tileWidth, tileHeight), level, width, height))
        return -1;


    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("../resources/worms_character2.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        return -1;
    }

    std::vector<sf::IntRect> left = {
            sf::IntRect(0, 0, 32, 34),
            sf::IntRect(32, 0, 32, 34),
            sf::IntRect(64, 0, 32, 34)
    };

    std::vector<sf::IntRect> right = {
            sf::IntRect(0, 34, 32, 34),
            sf::IntRect(32, 34, 32, 34),
            sf::IntRect(64, 34, 32, 34)
    };

    Animation walkingAnimationLeft = Animation(left, texture);
    Animation walkingAnimationRight = Animation(right, texture);
    Animation *currentAnimation = &walkingAnimationLeft;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, true);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
    animatedSprite.setScale(3.0f, 3.0f);

    Worm worm;

    sf::Clock frameClock;
    bool noKeyWasPressed = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();
        worm.resetMovement();
        // if a key was pressed set the correct animation and move correctly
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            currentAnimation = &walkingAnimationLeft;
            worm.move(LEFT);
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            currentAnimation = &walkingAnimationRight;
            worm.move(RIGHT);
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            worm.jump();
            noKeyWasPressed = false;
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(worm.getMovement() * frameTime.asSeconds());
        std::cout << worm.getMovement().x << ", " << worm.getMovement().y << std::endl;

        // if no key was pressed stop the animation
        if (noKeyWasPressed) {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear(sf::Color(255, 255, 255));
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}