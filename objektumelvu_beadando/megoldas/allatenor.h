#pragma once
#include <vector>
#include "allat.h"

class AllatEnor
{
private:
    bool _end;
    std::vector<Allat*>::iterator _i;
    std::vector<Allat*> *_p;
public:
    AllatEnor(std::vector<Allat*> *p) : _p(p) {}
    AllatEnor() {}
    void first();
    void next();
    Allat *current() {return *_i;}
    bool end() {return _end;}
    std::vector<Allat*>::iterator getI() {return _i;}

};



