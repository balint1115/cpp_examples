#include "allat.h"
#include "pisti.h"

using namespace std;


void Hal::eletkedvValtoztatas (Kedv kedv)
{
    switch (kedv)
    {
    case (jo):
        _eletkedv+=1;
        break;
    case (atlagos):
        _eletkedv-=3;
        break;
    case (rossz):
        _eletkedv-=5;
        break;
    }
    if (_eletkedv < 0) _eletkedv=0;
    if (_eletkedv > 100) _eletkedv=100;

}


void Madar::eletkedvValtoztatas (Kedv kedv)
{
    switch (kedv)
    {
    case (jo):
        _eletkedv+=2;
        break;
    case (atlagos):
        _eletkedv-=1;
        break;
    case (rossz):
        _eletkedv-=3;
        break;
    }
    if (_eletkedv < 0) _eletkedv=0;
    if (_eletkedv > 100) _eletkedv=100;
}


void Kutya::eletkedvValtoztatas (Kedv kedv)
{
    switch (kedv)
    {
    case (jo):
        _eletkedv+=3;
        break;
    case (atlagos):
        break;
    case (rossz):
        _eletkedv-=10;
        break;
    }
    if (_eletkedv < 0) _eletkedv=0;
    if (_eletkedv > 100) _eletkedv=100;
}
