#include <fstream>
#include <iostream>
#include "eng.h"

std::vector<float> guardaPontos(std::string ficheiro) {

    std::vector<float> pontos;

    std::ifstream file;
    std::string s = "./";
    s.append(ficheiro.c_str());
    file.open(s.c_str());
    float a,b,c;
    while(file >> a >> b >> c) {
        pontos.push_back(a);
        pontos.push_back(b);
        pontos.push_back(c);
    }
    return pontos;
}

std::vector<float> doModels(tinyxml2::XMLElement* models) {
    std::vector<float> pPontos;
    std::vector<float> savedPoints;

    tinyxml2::XMLElement* novo = models->FirstChildElement();
    for(novo; novo != NULL; novo = novo->NextSiblingElement()) {
        const char * file;
        file = novo->Attribute("file");
        savedPoints = guardaPontos(file);
        pPontos.insert(pPontos.begin(), savedPoints.begin(), savedPoints.end());
    }
    return pPontos;
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

    x == nullptr ? trans[0] = 0 : trans[0] = atoi(x);
    y == nullptr ? trans[1] = 0 : trans[1] = atoi(y);
    z == nullptr ? trans[2] = 0 : trans[2] = atoi(z);

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

Translacao doTimeTranslate(tinyxml2::XMLElement* translate) {

    Translacao t;

    int tempo;
    tempo = atoi(translate->Attribute("time"));

    std::vector<Pontos> pontos;

    tinyxml2::XMLElement* point = translate->FirstChildElement();
    for(point; point != NULL; point = point->NextSiblingElement()) {
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

Rotacao doTimeRotate(tinyxml2::XMLElement* rotate) {

    Rotacao rotation;

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

Cor doCor(tinyxml2::XMLElement* cor) {

    Cor cores;

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

    cores.setAxis(c);


    return cores;
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
            if(novo->Attribute("time") == nullptr) {
                sg.setTrans(doTranslate(novo));
            } else {
                sg.setCurva(doTimeTranslate(novo));
            }
        } else if(!strcmp(novo->Name(), "rotate")) {
            if(novo->Attribute("time") == nullptr) {
                sg.setRot(doRotate(novo));
            } else {
                sg.setEixo(doTimeRotate(novo));
            }
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
