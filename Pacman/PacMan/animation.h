#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
    Animation();

    void addFrame(sf::IntRect rect);//add frames
    void setSpriteSheet(const sf::Texture& texture);//sets the texture, sprite sheet
    const sf::Texture* getSpriteSheet() const;//gets the texture, sprite sheet
    std::size_t getSize() const;//sets the size of frames
    const sf::IntRect& getFrame(std::size_t n) const;//gets the frames

private:
    std::vector<sf::IntRect> m_frames;//vector of frames
    const sf::Texture* m_texture;//the texture
};

#endif // ANIMATION_H
