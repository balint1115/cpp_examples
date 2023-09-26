#pragma once
#include <vector>
#include "allat.h"
#include "enums.h"
#include "allatenor.h"

class Pisti
{
protected:
    std::vector <Allat*> _allatok;
    Kedv _kedv;
    AllatEnor _e;

public:
    Pisti () {}
    Pisti(std::vector<Allat*> allatok) : _allatok(allatok) {_e=AllatEnor(&_allatok);}
    int legszomorubb();
    void gondoz();
    void setKedv(Kedv k){_kedv=k;}
    AllatEnor *getEnor (){return &_e;}
};


