#include "allatenor.h"

using namespace std;


void AllatEnor::first()
{
    _end=_p->empty();
    if (!_end)
    {
        _i=_p->begin();
    }
}

void AllatEnor::next()
 {
    _i++;
    _end=_i>=_p->end();
 }
