//
// Created by geoff on 24/02/2020.
//

#ifndef LITTLEBIGGAME_RESOURCELOADER_HH
#define LITTLEBIGGAME_RESOURCELOADER_HH


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

enum TextureName {
    WORM_WALKING_TEXTURE,
    WORM_JUMPING_TEXTURE,
    MONSTER_WALKING_TEXTURE,
    PLATFORM_DEFAULT_TEXTURE,
    PLATFORM_CURSED_TEXTURE,
    PLATFORM_SPAWNER_TEXTURE,
    BAZOOKA_TEXTURE,
    BULLET_TEXTURE
};

class ResourceLoader {
private:
    ResourceLoader();
    std::vector<sf::Texture> m_textures;

    sf::Font m_font;
    sf::Music background_music;
public:
    static ResourceLoader& getInstance() {
        static ResourceLoader singleton;
        return singleton;
    }


    bool loadResources();
    sf::Texture& getTexture(TextureName textureName);
    sf::Font& getFont();
    sf::Music& getMusic();

private:
    ResourceLoader(const ResourceLoader &old);
    ResourceLoader &operator=(const ResourceLoader &old);

    bool loadTextures();
    bool loadFont();
    bool loadWormTexture();
    bool loadMonsterTexture();
    bool loadPlatformTexture();
    bool loadWeaponTexture();
    bool openMusicFile();
};


#endif //LITTLEBIGGAME_RESOURCELOADER_HH
