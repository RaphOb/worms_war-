#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "src/Tilemap.hh"
#include "src/Animation.hh"
#include "src/AnimatedSprite.hh"
#include "src/Worm.hh"
#include "src/Platform.hh"

static const float VIEW_HEIGHT = 800.f;
static const float VIEW_WIDTH = 800.f;

void resizeView(const sf::RenderWindow& window, sf::View &view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::Vector2i screenDimensions(VIEW_WIDTH, VIEW_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    window.setFramerateLimit(60);

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

    // set up AnimatedSprite
    sf::RectangleShape shape;
    AnimatedSprite animatedSprite(shape, sf::seconds(0.2), true, true);
    animatedSprite.getBody().setPosition(sf::Vector2f(screenDimensions / 2));

//    animatedSprite.setScale(3.0f, 3.0f);
    std::cout << animatedSprite.getBody().getPosition().x << animatedSprite.getBody().getPosition().y << std::endl;
    Worm worm(animatedSprite, {walkingAnimationRight, walkingAnimationLeft});

    // TODO replace this by the time manager did in the steps ?
    sf::Clock frameClock;


    Platform platformMiddle(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(600.f, 300.f));
    Platform platformTop(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(500.f, 0.f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.type == sf::Event::Resized)
                resizeView(window, view);
        }

        worm.update(frameClock.restart());
        Collider playerCollider = worm.getCollider();
//        std::cout << "platform 1" << std::endl;
        platformMiddle.getCollider().checkCollision(playerCollider, 1.0f);
        std::cout << "platform top" << std::endl;
//        Collider playerCollider2 = worm.getCollider();
//        platformTop.getCollider().checkCollision(playerCollider, 1.0f);

        view.setCenter(worm.getPosition());

//        worm.setYVelocity(worm.getVelocity().y + 981.0f);
//        std::cout << worm.getVelocity().x << ", " << worm.getVelocity().y << std::endl;

        // draw
        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        worm.draw(window);
        platformMiddle.draw(window);
        platformTop.draw(window);
        window.display();
    }

    return 0;
}