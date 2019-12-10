#include "ObjFactory.h"


TextureFactory* ObjFactory::textureFactory = new TextureFactory();
ModelFactory* ObjFactory::modelFactory = new ModelFactory();


auto ObjFactory::getProduct(MODEL model, TEXTURE texture, COLOR color) -> ObjectAssimp* { return new ObjectAssimp(modelFactory->getProduct(model), textureFactory->getProduct(texture), glm::vec4(ColorFactory::getProduct(color), 1)); }
