#pragma once
#include "ModelFactory.h"
#include "TextureFactory.h"
#include "ColorFactory.h"
#include "ObjectAssimp.h"
static class ObjFactory
{
public:
	static ObjectAssimp* getProduct(MODEL model, TEXTURE texture = TEXTURE::none, COLOR color = COLOR::white);
	static TextureFactory* textureFactory;
	static ModelFactory* modelFactory;
};

