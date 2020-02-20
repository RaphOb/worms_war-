#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "src/Tilemap.hh"
#include "src/Animation.hh"
#include "src/AnimatedSprite.hh"
#include "src/Worm.hh"
#include "src/Platform.hh"
#include "src/Constant.hh"
#include "src/Game.hh"


void resizeView(const sf::RenderWindow &window, sf::View &view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(Constant::VIEW_WIDTH * aspectRatio, Constant::VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(int(Constant::VIEW_WIDTH), int(Constant::VIEW_HEIGHT)), "Animations!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), Constant::SCREEN_DIMENSIONS);
    window.setFramerateLimit(60);

    Game game;
    Worm worm = game.initWorm();


    // load walkingTexture (spritesheet)
//    sf::Texture walkingTexture;
//    if (!walkingTexture.loadFromFile("../resources/worms_character2.png")) {
//        std::cout << "Failed to load worms spritesheet!" << std::endl;
//        return -1;
//    }
//
//    sf::Texture jumpingTexture;
//    if (!jumpingTexture.loadFromFile("../resources/worms_jump.png")) {
//        std::cout << "Failed to load worms jumps" << std::endl;
//        return -1;
//    }
//
//    std::vector<sf::IntRect> left = {
//            sf::IntRect(0, 0, 32, 34),
//            sf::IntRect(32, 0, 32, 34),
//            sf::IntRect(64, 0, 32, 34)
//    };
//
//    std::vector<sf::IntRect> right = {
//            sf::IntRect(0, 34, 32, 34),
//            sf::IntRect(32, 34, 32, 34),
//            sf::IntRect(64, 34, 32, 34)
//    };
//
//    std::vector<sf::IntRect> jumpLeft = {
//            sf::IntRect(0, 0, 28, 52),
//            sf::IntRect(28, 0, 28, 52),
//            sf::IntRect(56, 0, 28, 52),
//            sf::IntRect(84, 0, 28, 52)
//    };
//
//    std::vector<sf::IntRect> jumpRight = {
//            sf::IntRect(0, 52, 28, 52),
//            sf::IntRect(28, 52, 28, 52),
//            sf::IntRect(56, 52, 28, 52),
//            sf::IntRect(84, 52, 28, 52)
//    };
//
//    Animation walkingAnimationLeft = Animation(left, walkingTexture);
//    Animation walkingAnimationRight = Animation(right, walkingTexture);
//    Animation jumpingAnimationLeft = Animation(jumpLeft, jumpingTexture);
//    Animation jumpingAnimationRight = Animation(jumpRight, jumpingTexture);
//
//    // set up AnimatedSprite
//    sf::RectangleShape shape;
//    AnimatedSprite animatedSprite(shape, sf::seconds(0.1), true, true);
////    animatedSprite.getBody().setPosition(Constant::SCREEN_DIMENSIONS / 2.f);
//
////    animatedSprite.getBody().setScale(3.0f, 3.0f);
////    std::cout << animatedSprite.getBody().getPosition().x << animatedSprite.getBody().getPosition().y << std::endl;
//    Worm worm(animatedSprite,
//              {walkingAnimationRight, walkingAnimationLeft, jumpingAnimationLeft, jumpingAnimationRight});



    // TODO replace this by the time manager did in the steps ?
    sf::Clock frameClock;
    sf::Time frameTime;
    std::vector<Platform> platforms;
    platforms.reserve(2);
    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(300.f, 600.f));
    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(600.f, 400.f));

    while (window.isOpen()) {

//        shape = sf::RectangleShape();

        frameTime = frameClock.restart();
        // fix a bug that when you shake the window you fall through the floor because the game is paused but not frameTime. So you move by a lot in one frame.
        if (frameTime.asSeconds() > 1.0f / 60.0f) {
            frameTime = sf::seconds(1.0f / 60.0f);
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.type == sf::Event::Resized)
                resizeView(window, view);
        }

        worm.update(frameTime);
        Collider playerCollider = worm.getCollider();
        sf::Vector2f direction;

        for (Platform &platform: platforms) {
            if (platform.getCollider().checkCollision(playerCollider, direction, 1.0f)) {
                worm.onCollision(direction);
            }
        }

        view.setCenter(worm.getPosition());


        // draw
        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        worm.draw(window);
        for (Platform &platform: platforms) {
            platform.draw(window);
        }
        window.display();
    }

    return 0;
}