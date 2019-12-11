#include "TextureFactory.h"

Texture* TextureFactory::getProduct(TEXTURE type)
{
	if (this->textures.size() < 1)
	{
		this->createTextures();
	}

	if (type == TEXTURE::none) {
		return nullptr;
	}
	return this->textures[type];
}


void TextureFactory::createTextures()
{
	this->textures.insert({ TEXTURE::barn, new Texture("./textures/barn.png") });
	this->textures.insert({ TEXTURE::house, new Texture("./textures/house.png") });
	this->textures.insert({ TEXTURE::log, new Texture("./textures/log.png") });
	this->textures.insert({ TEXTURE::monkey, new Texture("./textures/monkey.png") });
	this->textures.insert({ TEXTURE::lamp, new Texture("./textures/lamp.png") });
	this->textures.insert({ TEXTURE::pig, new Texture("./textures/pig.png") });
	this->textures.insert({ TEXTURE::terrain1, new Texture("./textures/terrain1.png") });
	this->textures.insert({ TEXTURE::deer, new Texture("./textures/deer.png") });
	this->textures.insert({ TEXTURE::moose , new Texture("./textures/moose.png") });
	this->textures.insert({ TEXTURE::house2, new Texture("./textures/house2.png") });
}
