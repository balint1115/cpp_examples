#pragma once
#include <string>
#include "enums.h"

class Allat
{
protected:
    std::string _nev;
    int _eletkedv;
    Allat(std::string nev, int eletkedv) : _nev(nev), _eletkedv(eletkedv) {if (_eletkedv>100) _eletkedv=100;}
public:
    virtual void eletkedvValtoztatas (Kedv kedv)=0;
    virtual std::string getFaj () const=0;
    int getEletkedv () const {return _eletkedv;}
    std::string getNev() const {return _nev;}
    Allat() {}
    virtual ~Allat() {}
};

class Hal : public Allat
{
public:
    void eletkedvValtoztatas (Kedv kedv) override;
    std::string getFaj () const override {return "hal";}
    Hal(std::string nev, int eletkedv) : Allat(nev, eletkedv) {}
};

class Madar : public Allat
{
public:
    void eletkedvValtoztatas (Kedv kedv) override;
    std::string getFaj () const override {return "madar";}
    Madar(std::string nev, int eletkedv) : Allat(nev, eletkedv) {}
};

class Kutya : public Allat
{
public:
    void eletkedvValtoztatas (Kedv kedv) override;
    std::string getFaj () const override { return "kutya";}
    Kutya(std::string nev, int eletkedv) : Allat(nev, eletkedv) {}
};
