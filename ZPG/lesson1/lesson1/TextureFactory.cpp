#include "TextureFactory.h"

Texture* TextureFactory::getProduct(TEXTURE type)
{
	if (type == TEXTURE::NONE) {
		return nullptr;
	}
	return this->textures[type];
}

TextureFactory::TextureFactory()
{
	this->createTextures();
}

void TextureFactory::createTextures()
{
	this->textures.insert({ TEXTURE::BARN, new Texture("./textures/barn.png") });
	this->textures.insert({ TEXTURE::HOUSE, new Texture("./textures/house.png") });
	this->textures.insert({ TEXTURE::LOG, new Texture("./textures/log.png") });
	this->textures.insert({ TEXTURE::MONKEY, new Texture("./textures/monkey.png") });
	this->textures.insert({ TEXTURE::LAMP, new Texture("./textures/lamp.png") });
	this->textures.insert({ TEXTURE::PIG, new Texture("./textures/pig.png") });
}
