#include "ObjFactory.h"

ObjFactory::ObjFactory(ColorFactory* colorFactory)
{
	this->colorFactory = colorFactory;
	this->modelFactory = new ModelFactory();
	this->textureFactory = new TextureFactory();
}

ObjFactory::~ObjFactory()
{
	delete this->colorFactory;
	delete this->modelFactory;
	delete this->textureFactory;
}

ObjectAssimp* ObjFactory::getProduct(MODEL model, TEXTURE texture, COLOR color)
{
	Mesh* object_model = this->modelFactory->getProduct(model);
	Texture* object_texture = this->textureFactory->getProduct(texture);
	glm::vec4 object_color = glm::vec4(this->colorFactory->getProduct(color), 1);

	return new ObjectAssimp(object_model, object_texture, object_color);
}
