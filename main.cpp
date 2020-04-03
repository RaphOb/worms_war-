#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <windef.h>
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
#include "src/Audio/AudioLoader.hh"
#include "src/Audio/AudioManager.hh"
#include "src/TextManager.hh"


void resizeView(const sf::RenderWindow &window, sf::View &view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(Constant::VIEW_WIDTH * aspectRatio, Constant::VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(int(Constant::VIEW_WIDTH), int(Constant::VIEW_HEIGHT)), "Animations!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), Constant::SCREEN_DIMENSIONS);
    window.setFramerateLimit(60);

    if (!ResourceLoader::getInstance().loadResources() || !AudioLoader::getInstance().loadAudio()) {
        exit(-1);
    }



    Game game;
    Worm worm = game.initWorm();
    game.setWorm(&worm);
    game.initPathfinding();
    Scenes scene;
//     TODO replace this by the time manager did in the steps ?
    sf::Clock frameClock;
    TextManager textManager;
    textManager.loadFileScore();
    sf::Time frameTime;
    srand (time(nullptr));


//    platforms.reserve(2);
//    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(500.f, 1000.f));
//    platforms.emplace_back(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(800.f, 800.f));

    std::vector<Monster*> listMonsters;
    InitBoomer initboomer = InitBoomer();

    AudioLoader::getInstance().getMusic().setLoop(true);
//    AudioLoader::getInstance().getMusic().play();


//
    AudioManager::getInstance().addSound(WORM_WALKING_BUFFER);
//    AudioManager::getInstance().playSounds();
//    sf::Sound sound;
//    sound.setBuffer(AudioLoader::getInstance().getBuffer(WORM_WALKING_BUFFER));
//    sound.setLoop(true);
//    sound.play();

    while (window.isOpen()) {
        frameTime = frameClock.restart();
        // fix a bug that when you shake the window you fall through the floor because the game is paused but not frameTime. So you move by a lot in one frame.
        game.setFPS(int(1 / frameTime.asSeconds()));
        if (frameTime.asSeconds() > 1.0f / 60.0f) {
            frameTime = sf::seconds(1.0f / 60.0f);
        }

        worm.update(frameTime);
        scene.update(frameTime);
        game.update(window); // have to be after setView

        textManager.setText(std::to_string(listMonsters.size()), TypeText::MONSTER);
        textManager.setText("SCORE : " + std::to_string(listMonsters.size()), TypeText::SCORES); //TODO le Nb de monstre tué
        AudioManager::getInstance().playSounds();

        Collider playerCollider = worm.getCollider();
        sf::Vector2f direction;
        listMonsters = {};

        for (auto &platform: game.getMap().getPlatforms()) {
            platform->update(frameTime);
            if (worm.hasshot) {
                Collider bullet = worm.getBullet().getCollider();
                if (platform->getCollider().checkCollision(bullet, direction, 1.0f)) {
                    scene.add(std::make_unique<Boom>(initboomer.createBoom(bullet.getPosition())));
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
                    m->onCollision(monsterDirection);
                }
                if (worm.getCollider().checkCollision(monsterCollider, monsterDirection, 1.0f)) {
                    m->onCollision(monsterDirection);
                }
            }
        }

        // draw
        window.clear(sf::Color(150, 150, 150));

        // c'est ça qui centre le vue sur le worm
//        view.setCenter(worm.getPosition());
//        window.setView(view);


        for (auto &platform:  game.getMap().getPlatforms()) {
            platform->draw(window);
            platform->getSpawner().draw(window); // draw monsters
        }

        textManager.draw(window);
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
    textManager.saveScore();
    return 0;
}