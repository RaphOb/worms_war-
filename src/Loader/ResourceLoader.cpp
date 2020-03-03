//
// Created by geoff on 24/02/2020.
//

#include <iostream>
#include "ResourceLoader.hh"

bool ResourceLoader::loadResources() {
    return loadTextures()
        && loadFont()
        && openMusicFile();
}

bool ResourceLoader::loadTextures() {
    return loadMonsterTexture()
           && loadPlatformTexture()
           && loadWormTexture()
           && loadWeaponTexture();
}

bool ResourceLoader::loadFont() {
    if (!m_font.loadFromFile("../resources/fonts/arial.ttf")) {
        std::cout << "Failed to load platform font!" << std::endl;
        return false;
    }
    return true;
}

bool ResourceLoader::loadWormTexture() {
    sf::Texture wormWalkingTexture;
    if (!wormWalkingTexture.loadFromFile("../resources/worms_character2.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        return false;
    }
    sf::Texture wormJumpingTexture;
    if (!wormJumpingTexture.loadFromFile("../resources/worms_jump.png")) {
        std::cout << "Failed to load worms jumps" << std::endl;
        return false;
    }
    m_textures[WORM_WALKING_TEXTURE] = wormWalkingTexture;
    m_textures[WORM_JUMPING_TEXTURE] = wormJumpingTexture;
    return true;
}

bool ResourceLoader::loadMonsterTexture() {
    sf::Texture monsterWalkingTexture;
    if (!monsterWalkingTexture.loadFromFile("../resources/ground_monster.png")) {
        std::cout << "Failed to load monsters spritesheet!" << std::endl;
        return false;
    }

    // TODO add jumping texture
//    if (!m_monsterJumpingTexture.loadFromFile("../resources/ground_monster.png")) {
//        std::cout << "Failed to load monster jumps" << std::endl;
//        return false;
//    }
    m_textures[MONSTER_WALKING_TEXTURE]= monsterWalkingTexture;
    return true;
}

bool ResourceLoader::loadPlatformTexture() {
    sf::Texture platformDefaultTexture;
    if (!platformDefaultTexture.loadFromFile("../resources/platforms/platformDefault.png")) {
        std::cout << "Failed to load platform spritesheet!" << std::endl;
        return false;
    }
    sf::Texture platformCursedTexture;
    if (!platformCursedTexture.loadFromFile("../resources/platforms/platformCursed.png")) {
        std::cout << "Failed to load platform spritesheet!" << std::endl;
        return false;
    }
    sf::Texture platformSpawnerTexture;
    if (!platformSpawnerTexture.loadFromFile("../resources/platforms/platformSpawner.png")) {
        std::cout << "Failed to load platform spritesheet!" << std::endl;
        return false;
    }
    m_textures[PLATFORM_DEFAULT_TEXTURE]    = platformDefaultTexture;
    m_textures[PLATFORM_CURSED_TEXTURE]     = platformCursedTexture;
    m_textures[PLATFORM_SPAWNER_TEXTURE]    = platformSpawnerTexture;
    m_textures[PLATFORM_DEFAULT_TEXTURE].setRepeated(true);
    m_textures[PLATFORM_CURSED_TEXTURE].setRepeated(true);
    m_textures[PLATFORM_SPAWNER_TEXTURE].setRepeated(true);
    return true;
}

bool ResourceLoader::loadWeaponTexture() {
    sf::Texture bazookaTexture;
    if (!bazookaTexture.loadFromFile("../resources/bazooka.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        return false;
    }

    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        return false;
    }

    m_textures[BAZOOKA_TEXTURE] = bazookaTexture;
    m_textures[BULLET_TEXTURE]  = bulletTexture;
    return true;
}

sf::Font& ResourceLoader::getFont() {
    return m_font;
}

sf::Texture& ResourceLoader::getTexture(TextureName textureName) {
    return m_textures[textureName];

}

ResourceLoader::ResourceLoader() {
    m_textures.reserve(8);
}

bool ResourceLoader::openMusicFile() {
    return background_music.openFromFile("../resources/sound/Waterflame - Glorious morning.wav");
}

sf::Music &ResourceLoader::getMusic() {
    return background_music;
}
