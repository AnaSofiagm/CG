#include <fstream>
#include <iostream>
#include <stdio.h>
#include "engine.h"
#include "il.h"

//GL_LIGHT i, where i ranges from 0 to the value of GL_MAX_LIGHTS - 1. 
int nLights = -1;

int loadTexture(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}

GLenum pickLight() {
  nLights += 1;
  GLenum res;
  switch (nLights) {
    case 0: res = GL_LIGHT0; break;
    case 1: res = GL_LIGHT1; break;
    case 2: res = GL_LIGHT2; break;
    case 3: res = GL_LIGHT3; break;
    case 4: res = GL_LIGHT4; break;
    case 5: res = GL_LIGHT5; break;
    case 6: res = GL_LIGHT6; break;
    case 7: res = GL_LIGHT7; break;
    default: perror("Numero possivel de luzes excedido."); break;
  }
  return res;
}

void guardaPontos(std::string ficheiro, std::vector<float> &vertices, std::vector<float> &normais, std::vector<float> &coordstext) {

    std::ifstream file;
    std::string s = "./";
    s.append(ficheiro.c_str());
    file.open(s.c_str());

    //guardar o nr de vertices e de normais
    int size;
    file >> size;

    float p;
    int i;
    for(i = 0; i < size; i++) {
        file >> p;
        vertices.push_back(p);
    }
    for(i = 0; i < size; i++) {
        file >> p;
        normais.push_back(p);
    }
    while(file >> p) {
        coordstext.push_back(p);
    }
}

std::vector<ModTex> doModels(tinyxml2::XMLElement* models) {

    std::vector<ModTex> res;
    const char * type;
    std::vector<float> vertices;
    std::vector<float> normais;
    std::vector<float> coordstext;
    tinyxml2::XMLElement* novo; 
    for(novo = models->FirstChildElement(); novo != NULL; novo = novo->NextSiblingElement()) {
        ModTex tmp;
        std::array<float, 4> ambiente;
        std::array<float, 4> especular;
        std::array<float, 4> emissiva;
        std::array<float, 4> difusa;
        type = novo->Attribute("texture");
        if(type != nullptr) {
            std::string texture;
            texture = novo->Attribute("texture");
            tmp.setTexID(loadTexture(texture));
        }

        const char * R;
        const char * G;
        const char * B;

        const char * file;
        file = novo->Attribute("file");

        R = novo->Attribute("difR");
        G = novo->Attribute("difG");
        B = novo->Attribute("difB");

        R == nullptr ? difusa[0] = 0.0f : difusa[0] = atof(R);
        G == nullptr ? difusa[1] = 0.0f : difusa[1] = atof(G);
        B == nullptr ? difusa[2] = 0.0f : difusa[2] = atof(B);
        difusa[3] = 1.0f;

        R = novo->Attribute("ambR");
        G = novo->Attribute("ambG");
        B = novo->Attribute("ambB");

        R == nullptr ? ambiente[0] = 0.0f : ambiente[0] = atof(R);
        G == nullptr ? ambiente[1] = 0.0f : ambiente[1] = atof(G);
        B == nullptr ? ambiente[2] = 0.0f : ambiente[2] = atof(B);
        ambiente[3] = 1.0f;

        R = novo->Attribute("espR");
        G = novo->Attribute("espG");
        B = novo->Attribute("espB");

        R == nullptr ? especular[0] = 0.0f : especular[0] = atof(R);
        G == nullptr ? especular[1] = 0.0f : especular[1] = atof(G);
        B == nullptr ? especular[2] = 0.0f : especular[2] = atof(B);
        especular[3] = 1.0f;

        R = novo->Attribute("emiR");
        G = novo->Attribute("emiG");
        B = novo->Attribute("emiB");

        R == nullptr ? emissiva[0] = 0.0f : emissiva[0] = atof(R);
        G == nullptr ? emissiva[1] = 0.0f : emissiva[1] = atof(G);
        B == nullptr ? emissiva[2] = 0.0f : emissiva[2] = atof(B);
        emissiva[3] = 1.0f;

        guardaPontos(file, vertices, normais, coordstext);

        tmp.setPontos(vertices);
        tmp.setNormais(normais);
        tmp.setTexturas(coordstext);
        tmp.setAmbiente(ambiente);
        tmp.setSpecular(especular);
        tmp.setEmissive(emissiva);
        tmp.setDifusa(difusa);

        res.push_back(tmp);
        vertices.clear();
        normais.clear();
        coordstext.clear();

    }

    return res;
}

TranslacaoV doTranslate(tinyxml2::XMLElement* translate) {

    TranslacaoV transl;

    array<float, 3> trans;

    const char * x;
    const char * y;
    const char * z;
    x = translate->Attribute("x");
    y = translate->Attribute("y");
    z = translate->Attribute("z");

    x == nullptr ? trans[0] = 0 : trans[0] = atof(x);
    y == nullptr ? trans[1] = 0 : trans[1] = atof(y);
    z == nullptr ? trans[2] = 0 : trans[2] = atof(z);

    transl.setTrans(trans);

    return transl;
}

RotacaoV doRotate(tinyxml2::XMLElement* rotate) {

    RotacaoV rotation;

    array<float,4> rot;

    const char * x;
    const char * y;
    const char * z;
    const char * ang;
    x = rotate->Attribute("x");
    y = rotate->Attribute("y");
    z = rotate->Attribute("z");
    ang = rotate->Attribute("angle");

    ang == nullptr ? rot[0] = 0.0f : rot[0] = atoi(ang);
    x == nullptr ? rot[1] = 0.0f : rot[1] = atof(x);
    y == nullptr ? rot[2] = 0.0f : rot[2] = atof(y);
    z == nullptr ? rot[3] = 0.0f : rot[3] = atof(z);

    rotation.setRot(rot);

    return rotation;
}

Scale doScale(tinyxml2::XMLElement* scale) {

    Scale escala;

    array<float,3> sca;

    const char * x;
    const char * y;
    const char * z;

    x = scale->Attribute("x");
    y = scale->Attribute("y");
    z = scale->Attribute("z");

    x == nullptr ? sca[0] = 1.0f : sca[0] = atof(x);
    y == nullptr ? sca[1] = 1.0f : sca[1] = atof(y);
    z == nullptr ? sca[2] = 1.0f : sca[2] = atof(z);

    escala.setAxis(sca);

    return escala;

 }

TranslacaoT doTimeTranslate(tinyxml2::XMLElement* translate) {

    TranslacaoT t;

    int tempo;
    tempo = atoi(translate->Attribute("time"));

    std::vector<Pontos> pontos;

    tinyxml2::XMLElement* point;
    for(point = translate->FirstChildElement(); point != NULL; point = point->NextSiblingElement()) {
        Pontos aux;
        aux.a = atof(point->Attribute("x"));
        aux.b = atof(point->Attribute("y"));
        aux.c = atof(point->Attribute("z"));
        pontos.push_back(aux);
    }
    if(pontos.size() < 4) {
        perror("Sao necessarios no minimo 4 pontos");
    } else {
        t.setCurva(pontos, tempo);
    }
    return t;
}

RotacaoT doTimeRotate(tinyxml2::XMLElement* rotate) {

    RotacaoT rotation;

    std::array<float, 3> xyz;

    int tempo;

    xyz[0] = atof(rotate->Attribute("x"));
    xyz[1] = atof(rotate->Attribute("y"));
    xyz[2] = atof(rotate->Attribute("z"));

    tempo = atoi(rotate->Attribute("time"));

    rotation.setRot(xyz);
    rotation.setGraus(tempo);

    return rotation;
}

std::vector<std::shared_ptr<Luz> > doLights(tinyxml2::XMLElement* lights) {
  std::array<float, 3> pontos;
  std::array<float, 3> direction;
  float cutoff;
  const char * x;
  const char * y;
  const char * z;
  std::vector<std::shared_ptr<Luz> > res;
  //Sacar o First Element do bloco de luzes
  tinyxml2::XMLElement* light;
  // percorrer todos os elementos do bloco LIGHTS
  for(light = lights->FirstChildElement(); light != NULL; light = light->NextSiblingElement()) {
    // Verificar se o tipo de luz é POINT LIGHT
    if(!strcmp((light->Attribute("type")), "POINT")) {
      //DO POINT LIGHT
      x = light->Attribute("posX");
      y = light->Attribute("posY");
      z = light->Attribute("posZ");

      x == nullptr ? pontos[0] = 0.0f : pontos[0] = atof(x);
      y == nullptr ? pontos[1] = 0.0f : pontos[1] = atof(y);
      z == nullptr ? pontos[2] = 0.0f : pontos[2] = atof(z);

      std::shared_ptr<Luz> pL(new PLight(pontos, pickLight()));
      res.push_back(pL);
    // Verificar se o tipo de luz é DIRECTIONAL LIGHT
  } else if(!strcmp((light->Attribute("type")), "SPOT")) {
      //DO DIRECTIONAL LIGHT
      x = light->Attribute("posX");
      y = light->Attribute("posY");
      z = light->Attribute("posZ");

      x == nullptr ? pontos[0] = 0.0f : pontos[0] = atof(x);
      y == nullptr ? pontos[1] = 0.0f : pontos[1] = atof(y);
      z == nullptr ? pontos[2] = 0.0f : pontos[2] = atof(z);

      x = light->Attribute("dirX");
      y = light->Attribute("dirY");
      z = light->Attribute("dirZ");

      x == nullptr ? direction[0] = 0.0f : direction[0] = atof(x);
      y == nullptr ? direction[1] = 0.0f : direction[1] = atof(y);
      z == nullptr ? direction[2] = 0.0f : direction[2] = atof(z);


      x = light->Attribute("cutoff");

      x == nullptr ? cutoff = 0.0f : cutoff = atof(x);

      std::shared_ptr<Luz> sL(new SLight(pontos, direction, cutoff, pickLight()));

      res.push_back(sL);

    // Verificar se o tipo de luz é SPOT LIGHT
  } else if(!strcmp((light->Attribute("type")), "DIRECTIONAL")) {
      //DO SPOT LIGHT
      x = light->Attribute("dirX");
      y = light->Attribute("dirY");
      z = light->Attribute("dirZ");

      x == nullptr ? direction[0] = 0.0f : direction[0] = atof(x);
      y == nullptr ? direction[1] = 0.0f : direction[1] = atof(y);
      z == nullptr ? direction[2] = 0.0f : direction[2] = atof(z);

      std::shared_ptr<Luz> dL(new DLight(pontos, pickLight()));
      res.push_back(dL);
    }
  }
  return res;
}

SceneGraph doGroup(tinyxml2::XMLElement* group) {
    SceneGraph s_g;
    tinyxml2::XMLElement* novo;
    for(novo = group->FirstChildElement(); novo != NULL; novo = novo->NextSiblingElement()) {
        if(!strcmp(novo->Name(), "group")) {
            s_g.addFilho(doGroup(novo));
        } else if(!strcmp(novo->Name(), "models")) {
            s_g.setTexturas(doModels(novo));
        } else if(!strcmp(novo->Name(), "translate")) {
            if(novo->Attribute("time") == nullptr) {
                s_g.setTrans(doTranslate(novo));
            } else {
                s_g.setCurva(doTimeTranslate(novo));
            }
        } else if(!strcmp(novo->Name(), "rotate")) {
            if(novo->Attribute("time") == nullptr) {
                s_g.setRot(doRotate(novo));
            } else {
                s_g.setEixo(doTimeRotate(novo));
            }
        } else if(!strcmp(novo->Name(), "scale")) {
            s_g.setScale(doScale(novo));
        } else if(!strcmp(novo->Name(), "lights")) {
            s_g.setLuzes(doLights(novo));
        } else {
            perror("Formato XML Incorreto.\n");
        }
    }
    return s_g;
}
