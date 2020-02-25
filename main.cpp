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
#include "src/Scenes.hh"
#include "src/Map.hh"
#include "src/Loader/ResourceLoader.hh"
#include "src/InitBoomer.hh"


void resizeView(const sf::RenderWindow &window, sf::View &view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(Constant::VIEW_WIDTH * aspectRatio, Constant::VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(int(Constant::VIEW_WIDTH), int(Constant::VIEW_HEIGHT)), "Animations!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), Constant::SCREEN_DIMENSIONS);
    window.setFramerateLimit(60);

    if (!ResourceLoader::getInstance().loadResources()) {
        exit(-1);
    }

    Game game;
    Worm worm = game.initWorm();
    auto scene = Scenes{};
//     TODO replace this by the time manager did in the steps ?
    sf::Clock frameClock;
    sf::Time frameTime;
    srand (time(nullptr));


//    platforms.reserve(2);
//    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(500.f, 1000.f));
//    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(800.f, 800.f));

    std::vector<Monster*> listMonsters;
    InitBoomer initboomer = InitBoomer();
    Boom boom =  initboomer.createBoom(sf::Vector2f(0.f,0));
    while (window.isOpen()) {
        window.clear(sf::Color(150, 150, 150));

        frameTime = frameClock.restart();
        // fix a bug that when you shake the window you fall through the floor because the game is paused but not frameTime. So you move by a lot in one frame.
        if (frameTime.asSeconds() > 1.0f / 60.0f) {
            frameTime = sf::seconds(1.0f / 60.0f);
        }

        worm.update(frameTime);

        scene.update(frameTime);

        Collider playerCollider = worm.getCollider();

        sf::Vector2f direction;
        listMonsters = {};

        for (auto &platform: game.getMap().getPlatforms()) {
            platform->update(frameTime);
            if (worm.hasshot) {
                Collider bullet = worm.getBullet().getCollider();
                if (platform->getCollider().checkCollision(bullet, direction, 1.0f)) {
                    boom.setPosition(bullet.getPosition().x,bullet.getPosition().y);
                    std::cout<< "la pos de la bullet au momentde boom x : "<<bullet.getPosition().x << std::endl;
                    std::cout<< "la pos de la bullet au momentde boom y : "<<bullet.getPosition().y << std::endl;
                    std::cout<< "la pos de la bullet au momentde boom worm y : "<<worm.getPosition().y << std::endl;
                    scene.add(std::make_unique<Boom>(boom));
                    worm.hasshot = false;
                    worm.getBullet().onCollision(direction);

                }
            }
            if (platform->getCollider().checkCollision(playerCollider, direction, 1.0f)) {
                worm.onCollision(direction);
                platform->onCollision(direction);
            }

            for (Monster* m : platform->getSpawner().getListMonsters()) {
                listMonsters.push_back(m);
            }

        }

        for (Monster* m: listMonsters) {
            Collider monsterCollider = m->getCollider();
            sf::Vector2f monsterDirection;
            for (auto &p: game.getMap().getPlatforms()) {
                if (p->getCollider().checkCollision(monsterCollider, monsterDirection, 1.0f)) {
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
        game.update(window); // have to be after setView

        window.setView(view);
        for (auto &platform:  game.getMap().getPlatforms()) {
            platform->draw(window);
            platform->getSpawner().draw(window); // draw monsters
        }

        scene.draw(window);
        worm.draw(window);
        game.draw(window);
        window.display();
        scene.clean();

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