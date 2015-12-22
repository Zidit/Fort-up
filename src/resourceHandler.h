#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <map>

typedef std::shared_ptr<sf::Image> imagePtr;
typedef std::shared_ptr<sf::Texture> texturePtr;

class resourceHandler
{
    public:
        resourceHandler();
        virtual ~resourceHandler();

        imagePtr getImage(std::string const &fileName);
        texturePtr getTexture(std::string const &fileName);

    protected:
    private:
        std::map<std::string, imagePtr> images;
        std::map<std::string, texturePtr> textures;
};

extern resourceHandler resources;

#endif // RESOURCEHANDLER_H
