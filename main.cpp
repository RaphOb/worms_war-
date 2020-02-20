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

//     TODO replace this by the time manager did in the steps ?
    sf::Clock frameClock;
    sf::Time frameTime;
    std::vector<Platform> platforms;
    platforms.reserve(2);
    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(300.f, 600.f));
    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(600.f, 400.f));

    while (window.isOpen()) {

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
            if (worm.hasshot) {
                Collider bullet = worm.getBullet().getCollider();
                platform.getCollider().checkCollision(bullet, direction, 1.0f);
            }
            if (platform.getCollider().checkCollision(playerCollider, direction, 1.0f)) {
                worm.onCollision(direction);
            }
        }

        view.setCenter(worm.getPosition());


        // draw
        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        for (Platform &platform: platforms) {
            platform.draw(window);
        }
        worm.draw(window);
        window.display();
    }

    return 0;
}