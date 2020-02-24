#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "src/Tilemap.hh"
#include "src/Animation.hh"
#include "src/AnimatedSprite.hh"
#include "src/Worm.hh"
#include "src/Platform.hh"
#include "src/Constant.hh"
#include "src/Game.hh"
#include "src/Monster/MonsterFactory.hh"
#include "src/Monster/GroundMonster.hh"
#include "src/InitBoomer.hh"


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
    srand (time(NULL));
    platforms.reserve(3);
    platforms.emplace_back(sf::Vector2f(3000.f, 50.f), sf::Vector2f(1000.f, 850.f), false, true);
    platforms.emplace_back(sf::Vector2f(300.f, 50.f), sf::Vector2f(600.f, 600.f), true, false);
    platforms.emplace_back(sf::Vector2f(300.f, 50.f), sf::Vector2f(1000.f, 500.f), false, false);

    std::vector<Monster*> listMonsters;
    InitBoomer initboomer = InitBoomer();

    while (window.isOpen()) {

        frameTime = frameClock.restart();
        // fix a bug that when you shake the window you fall through the floor because the game is paused but not frameTime. So you move by a lot in one frame.
        if (frameTime.asSeconds() > 1.0f / 60.0f) {
            frameTime = sf::seconds(1.0f / 60.0f);
        }

        worm.update(frameTime);

        Collider playerCollider = worm.getCollider();

        sf::Vector2f direction;
        listMonsters = {};

        for (Platform &platform: platforms) {
            platform.update(frameTime);
            if (worm.hasshot) {
                Collider bullet = worm.getBullet().getCollider();
                if (platform.getCollider().checkCollision(bullet, direction, 1.0f)) {
                   Boom boom =  initboomer.createBoom(worm.getBullet().getposition());
                   boom.draw(window);
                   boom.update(frameTime);
//                    worm.hasshot = false;
//                    worm.getBullet().onCollision(direction);

                }
            }
            if (platform.getCollider().checkCollision(playerCollider, direction, 1.0f)) {
                worm.onCollision(direction);
                platform.onCollision(direction, true);
            }

            for (Monster* m : platform.getSpawner().getListMonsters()) {
                listMonsters.push_back(m);
            }

        }

        for (Monster* m: listMonsters) {
            Collider monsterCollider = m->getCollider();
            sf::Vector2f monsterDirection;
            for (Platform &p: platforms) {
                if (p.getCollider().checkCollision(monsterCollider, monsterDirection, 1.0f)) {
                    m->onCollision(direction);
                }
                if (worm.getCollider().checkCollision(monsterCollider, monsterDirection, 1.0f)) {
                    m->onCollision(direction);
                }
            }
        }

        view.setCenter(worm.getPosition());


        // draw
        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        for (Platform &platform: platforms) {
            platform.draw(window);
            platform.getSpawner().draw(window); // draw monsters
        }

        worm.draw(window);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.type == sf::Event::Resized)
                resizeView(window, view);
        }
    }

    return 0;
}