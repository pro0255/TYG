#pragma once
#include "Texture.h"
#include <map>
enum class TEXTURE {
	barn,
	house,
	log,
	monkey,
	lamp,
	pig,
	none,
	terrain1
};

class TextureFactory
{
public:
	Texture* getProduct(TEXTURE type);
private:
	map<TEXTURE, Texture*> textures;
	void createTextures();
};

