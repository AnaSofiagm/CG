#include "draw.h"
std::vector<Pontos> guardaPontos(std::string ficheiro);

std::vector<std::vector<Pontos>> doModels(tinyxml2::XMLElement* models);

array<float,3> doTranslate(tinyxml2::XMLElement* translate);

array<float,4> doRotate(tinyxml2::XMLElement* rotate);

array<float,3> doScale(tinyxml2::XMLElement* scale);

array<float,3> doCor(tinyxml2::XMLElement* cor);

SceneGraph doGroup(tinyxml2::XMLElement* group);