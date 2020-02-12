
#ifndef LITTLEBIGGAME_ANIMATION_HH
#define LITTLEBIGGAME_ANIMATION_HH


#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

class Animation {
public:
    Animation();

    explicit Animation(std::vector<sf::IntRect> frames);

    Animation(std::vector<sf::IntRect> frames, sf::Texture &texture);

    void addFrame(sf::IntRect rect);

    void setSpriteSheet(const sf::Texture &texture);

    const sf::Texture *getSpriteSheet() const;

    std::size_t getSize() const;

    const sf::IntRect &getFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture *m_texture;
};


#endif //LITTLEBIGGAME_ANIMATION_HH
