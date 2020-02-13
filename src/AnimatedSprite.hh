
#ifndef LITTLEBIGGAME_ANIMATEDSPRITE_HH
#define LITTLEBIGGAME_ANIMATEDSPRITE_HH


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Animation.hh"

class AnimatedSprite : public sf::Drawable
//        , public sf::Transformable
{
public:
    explicit AnimatedSprite(sf::RectangleShape& body, sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);

    void update(sf::Time deltaTime);
    void setAnimation(const Animation& animation);
    void setFrameTime(sf::Time time);
    void play();
    void play(const Animation& animation);
    void pause();
    void stop();
    void setLooped(bool looped);
    void setColor(const sf::Color& color);
    void setOrigin(float x, float y);
    const Animation* getAnimation() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    bool isLooped() const;
    bool isPlaying() const;
    sf::RectangleShape& getBody() const;
    sf::Time getFrameTime() const;
    void setFrame(std::size_t newFrame, bool resetTime = true);

private:
    const Animation* m_animation;
    /**
     * @var The time needed to do one frame of the animation. Higher the frame time is, longer the animation will take
     */
    sf::Time m_frameTime;
    /**
     * @var Variable to keep track of the current time to check if we need to change frame or not
     */
    sf::Time m_currentTime;
    /**
     * @var The current frame of the animation.
     */
    std::size_t m_currentFrame;
    /**
     * @var Boolean to pause the animation or not
     */
    bool m_isPaused;
    /**
     * @var Boolean to continuously loop the animation or not
     */
    bool m_isLooped;
    /**
     * @var The texture of the animation
     */
    const sf::Texture* m_texture;
    /**
     * @var oui
     */
    sf::Vertex m_vertices[4];

    sf::RectangleShape& m_body;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif //LITTLEBIGGAME_ANIMATEDSPRITE_HH
