#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>


#include "animation.h"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
    explicit AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);

    void update(sf::Time deltaTime);//updates according to time
    void setAnimation(const Animation& animation);//sets the animation
    void setFrameTime(sf::Time time);//sets the frame rate
    void play();//plays animation
    void play(const Animation& animation);//also plays animation
    void pause();//pauses the animation
    void stop();//stops the animation
    void setLooped(bool looped);//sets if it has looped
    void setColor(const sf::Color& color);//sets the color
    const Animation* getAnimation() const;//gets the animation
    sf::FloatRect getLocalBounds() const;//gets the local bound of sprite
    sf::FloatRect getGlobalBounds() const;//gets the global bound of the sprite
    bool isLooped() const;//if the loop is playing
    bool isPlaying() const;//if the animation is playing
    sf::Time getFrameTime() const;//gets frame time
    void setFrame(std::size_t newFrame, bool resetTime = true);//sets the frame time


private:
    const Animation* m_animation;
    sf::Time m_frameTime;
    sf::Time m_currentTime;
    std::size_t m_currentFrame;
    bool m_isPaused;
    bool m_isLooped;
    const sf::Texture* m_texture;
    sf::Vertex m_vertices[4];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif // ANIMATEDSPRITE_H
