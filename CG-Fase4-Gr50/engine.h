#include "draw.h"
#include "tinyxml2.h"
#include "pointLight.h"
#include "spotLight.h"
#include "directionLight.h"

int loadTexture(std::string s);

GLenum pickLight();

void guardaPontos(std::string ficheiro, std::vector<float> &vertices, std::vector<float> &normais, std::vector<float> &coordstext);


std::vector<ModTex> doModels(tinyxml2::XMLElement* models);

TranslacaoV doTranslate(tinyxml2::XMLElement* translate);

RotacaoV doRotate(tinyxml2::XMLElement* rotate);

TranslacaoT doTimeTranslate(tinyxml2::XMLElement* translate);

RotacaoT doTimeRotate(tinyxml2::XMLElement* rotate);

Scale doScale(tinyxml2::XMLElement* scale);

std::vector<std::shared_ptr<Luz> > doLights(tinyxml2::XMLElement* lights);

SceneGraph doGroup(tinyxml2::XMLElement* group);

