#include "resourcetexture.h"
#include <iostream>
#include <SFML/Graphics.hpp>

resourceTexture::resourceTexture(std::string const &filename) : loaded(0), instances(0)
{
    _filename = filename;
    load(filename);
}


resourceTexture::~resourceTexture()
{
    glDeleteTextures(1, &texture_handle);
}

void resourceTexture::reload()
{
    load(_filename);
}

void resourceTexture::release()
{
    return;
}

void resourceTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture_handle);
}

void resourceTexture::load(std::string const &filename)
{
    sf::Image img_data;
    if (!img_data.loadFromFile(filename))
    {
        return;
    }

    glGenTextures(1, &texture_handle);

    glBindTexture(GL_TEXTURE_2D, texture_handle);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        img_data.getSize().x, img_data.getSize().y,
        0,
        GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr()
    );


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    loaded = true;

}
