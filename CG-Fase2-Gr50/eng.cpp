#include "tinyxml2.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "draw.h"



std::vector<Pontos> guardaPontos(std::string ficheiro) {

    std::vector<Pontos> pontos;

    std::ifstream file;
    std::string s = "./";
    s.append(ficheiro.c_str());
    file.open(s.c_str());
    float a,b,c;
    while(file >> a >> b >> c) {
        Pontos aux;
        aux.a = a;
        aux.b = b;
        aux.c = c;
        pontos.push_back(aux);
    }
    return pontos;
}

std::vector<std::vector<Pontos>> doModels(tinyxml2::XMLElement* models) {
    std::vector<std::vector<Pontos>> pPontos;
    tinyxml2::XMLElement* novo = models->FirstChildElement();
    for(novo; novo != NULL; novo = novo->NextSiblingElement()) {
        const char * file;
        file = novo->Attribute("file");
        pPontos.push_back(guardaPontos(file));
    }
    return pPontos;
}

array<float,3> doTranslate(tinyxml2::XMLElement* translate) {

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

    return trans;
}

array<float,4> doRotate(tinyxml2::XMLElement* rotate) {

    array<float,4> rot;

    const char * x;
    const char * y;
    const char * z;
    const char * ang;
    x = rotate->Attribute("x");
    y = rotate->Attribute("y");
    z = rotate->Attribute("z");
    ang = rotate->Attribute("angle");

    ang == nullptr ? rot[0] = 0 : rot[0] = atof(ang);
    x == nullptr ? rot[1] = 0 : rot[1] = atof(x);
    y == nullptr ? rot[2] = 0 : rot[2] = atof(y);
    z == nullptr ? rot[3] = 0 : rot[3] = atof(z);

    return rot;
}

array<float,3> doScale(tinyxml2::XMLElement* scale) {

    array<float,3> sca;

    const char * x;
    const char * y;
    const char * z;

    x = scale->Attribute("x");
    y = scale->Attribute("y");
    z = scale->Attribute("z");

    x == nullptr ? sca[0] = 1 : sca[0] = atof(x);
    y == nullptr ? sca[1] = 1 : sca[1] = atof(y);
    z == nullptr ? sca[2] = 1 : sca[2] = atof(z);

    return sca;
}

array<float,3> doCor(tinyxml2::XMLElement* cor) {

    array<float, 3> c;

    const char * r;
    const char * g;
    const char * b;
    r = cor->Attribute("R");
    g = cor->Attribute("G");
    b = cor->Attribute("B");

    r == nullptr ? c[0] = 0 : c[0] = atof(r);
    g == nullptr ? c[1] = 0 : c[1] = atof(g);
    b == nullptr ? c[2] = 0 : c[2] = atof(b);

    return c;
}

SceneGraph doGroup(tinyxml2::XMLElement* group) {
    SceneGraph sg;
    tinyxml2::XMLElement* novo = group->FirstChildElement();
    for(novo; novo != NULL; novo = novo->NextSiblingElement()) {
        if(!strcmp(novo->Name(), "group")) {
            sg.addFilho(doGroup(novo));
        } else if(!strcmp(novo->Name(), "models")) {
            sg.setModelo(doModels(novo));
        } else if(!strcmp(novo->Name(), "translate")) {
            sg.setTrans(doTranslate(novo));
        } else if(!strcmp(novo->Name(), "rotate")) {
            sg.setRot(doRotate(novo));
        } else if(!strcmp(novo->Name(), "scale")) {
            sg.setScale(doScale(novo));
        } else if(!strcmp(novo->Name(), "cor")) {
            sg.setCor(doCor(novo));
        } else {
            perror("Formato XML Incorreto.\n");
        }
    }
    return sg;
}