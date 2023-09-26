#include "allat.h"
#include "pisti.h"
#include <iostream>

using namespace std;

int Pisti::legszomorubb()
{
    _e.first();
    int min=_e.current()->getEletkedv();
    for (_e.next(); !_e.end(); _e.next())
    {
        if (_e.current()->getEletkedv()< min)
        {
            min=_e.current()->getEletkedv();
        }
    }
    return min;
}

void Pisti::gondoz()
{
    if (legszomorubb()>=5){
        if (_kedv==atlagos) _kedv=jo;
        if (_kedv==rossz) _kedv=atlagos;
    }
    _e.first();
    while (!_e.end())
    {
        _e.current()->eletkedvValtoztatas(_kedv);
        cout <<  _e.current()->getNev() << "\t" << _e.current()->getFaj() << "\t";
        if (_e.current()->getEletkedv()==0)
        {
            delete _e.current();
            _allatok.erase(_e.getI());
            cout << "elpusztult" << endl;
            if (_allatok.empty())
            {
                throw nincsAllat;
            }
            if (_allatok.end()==_e.getI())
            {
                _e.next();
            }
        }
        else
        {
            cout << _e.current()->getEletkedv() << endl;
            _e.next();
        }
    }
}



