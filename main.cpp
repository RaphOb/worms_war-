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
#include "src/observable/EventObservable.hh"


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
    int score = 0;
    Worm worm = game.initWorm();
    EventObservable eventWatcher;
    eventWatcher.addObserver(&worm);
    Scenes scene;
    sf::Clock frameClock;
    TextManager textManager;
    textManager.loadFileScore();
    sf::Time frameTime;
    TimeManager timeManager;
    timeManager.SetFrequenceHit(300);
    srand(time(nullptr));


    std::vector<Monster *> listMonsters;
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
        if (worm.getLife() > 0) {
            std::cout << "en vie" << std::endl;
            frameTime = frameClock.restart();
            // fix a bug that when you shake the window you fall through the floor because the game is paused but not frameTime. So you move by a lot in one frame.
            game.setFPS(int(1 / frameTime.asSeconds()));
            game.setLife(worm.getLife());
            if (frameTime.asSeconds() > 1.0f / 60.0f) {
                frameTime = sf::seconds(1.0f / 60.0f);
            }

            eventWatcher.update();
            worm.update(frameTime);
            scene.update(frameTime);
            game.update(window); // have to be after setView

            textManager.setText(std::to_string(listMonsters.size()), TypeText::MONSTER);
            textManager.setNbScores(score);
            textManager.setText(std::to_string(score), TypeText::SCORES); //TODO le Nb de monstre tué
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

                for (Monster *m : platform->getSpawner().getListMonsters()) {
                    listMonsters.push_back(m);
                }

            }

            for (Monster *m: listMonsters) {
                Collider monsterCollider = m->getCollider();
                sf::Vector2f monsterDirection;
                for (auto &p: game.getMap().getPlatforms()) {
                    if (p->getCollider().checkCollision(monsterCollider, monsterDirection, 1.0f)) {
                        m->onCollision(monsterDirection);
                    }
                }

                if (worm.getCollider().checkCollision(monsterCollider, monsterDirection, 0.0f)) {
                    m->onCollision(monsterDirection);
                    if (timeManager.FrequenceHit()) {
                        worm.reduceLife();
                    }
                }

                if (worm.hasshot) {
                    Collider bullet = worm.getBullet().getCollider();
                    if (m->getCollider().checkCollision(bullet, monsterDirection, 0)) {
                        m->isDestroyed = true;
                        score +=1;
                        listMonsters.erase(std::remove(listMonsters.begin(), listMonsters.end(), m), listMonsters.end());
                    }
                }
            }

            // draw
            window.clear(sf::Color(150, 150, 150));

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
        } else {
            window.clear(sf::Color(255, 255, 255));
            game.drawGameOver(window);
            window.display();
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
    }
//    textManager.saveScore();
    return 0;
}