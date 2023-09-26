#include <iostream>
#include <fstream>
#include "pisti.h"
#include "allat.h"
#include "allatenor.h"


#include "../gtlib/linsearch.hpp"
#include "../gtlib/maxsearch.hpp"
#include "../gtlib/seqinfileenumerator.hpp"

using namespace std;
#define NORMAL_MODE

class ParatlanKeres : public LinSearch<int, false>
{
protected:
    bool cond(const int& e) const override { return e % 2 == 1; }
};

class LegnagyobbMod3 : public MaxSearch<int, int, Greater<int>>
{
protected:
    int func(const int& e) const override { return e; }
    bool cond(const int& e) const override { return e % 3 == 0; }
    void first() override {}
};

void beolvas(string file, vector<Allat*> *allatok, ifstream *f)
{
    *f=ifstream(file);
    if(f->fail())
    {
        cout << "Rossz file nev!" << endl;
        exit(1);
    }
    unsigned int n;
    char c;
    string nev;
    int eletkedv;
    *f >> n;
    allatok->resize(n);
    for (unsigned int i=0; i<n; i++)
    {
        *f >> c >> nev >> eletkedv;
        if (eletkedv>0){
            switch (c)
            {
            case ('H'):
                (*allatok)[i] = new Hal(nev, eletkedv);
                break;
            case ('M'):
                (*allatok)[i] = new Madar(nev, eletkedv);
                break;
            case ('K'):
                (*allatok)[i] = new Kutya(nev, eletkedv);
                break;
            }
        }

    }
}

void napokFeldogozasa(Pisti *pisti, ifstream *f)
{
        string s;
    *f >> s;
    unsigned int m=s.size();
    try
    {
        for (unsigned int i=0; i<m; i++)
        {
            switch (s[i])
            {
            case('j'):
                pisti->setKedv(jo);
                break;

            case('a'):
                pisti->setKedv(atlagos);
                break;

            case('r'):
                pisti->setKedv(rossz);
                break;
            }

            pisti->gondoz();
            cout <<"-------------------------------------------"<<endl;
        }
    }
    catch (Error err)
    {
        cout << "\n\nAz osszes allat elpusztult.\n";
        #ifdef NORMAL_MODE
        exit(0);
        #endif // NORMAL_MODE
    }

}


void minKer (Pisti *pisti, vector<string> *v)
{
    AllatEnor *e=pisti->getEnor();
    int min=pisti->legszomorubb();
        for (e->first(); !e->end(); e->next()){
            if (e->current()->getEletkedv()==min)
            {
                v->push_back(e->current()->getNev());
            }
        }
}


//#define NORMAL_MODE
#ifdef NORMAL_MODE
int main()
{
    string file;
    cout << "A bemeneti file neve: ";
    cin >> file;
    vector<Allat*> allatok;
    ifstream f;
    beolvas (file, &allatok, &f);

    Pisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    vector<string> legszomorubbak;
    minKer(&pisti, &legszomorubbak);
    cout << "A legszomorubb meg elo allat(ok):"<<endl;
    for (size_t i=0; i<legszomorubbak.size(); i++)
    {
        cout << legszomorubbak[i] <<endl;
    }





    SeqInFileEnumerator<int> in("input.txt");

    ParatlanKeres keres;
    keres.addEnumerator(&in);
    keres.run();

    if (keres.found())
    {
        LegnagyobbMod3 legn;
        legn.addEnumerator(&in);
        legn.run();

        if (legn.found())
            cout << legn.optElem() << endl;
        else cout << "Nem volt harommal oszthato.";
    }
    else cout << "Nem volt paratlan szam." << endl;

    return 0;
}



#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ios>




class testPisti : public Pisti
{
public:
    vector<Allat*> getAllatok(){return _allatok;}
    testPisti(std::vector<Allat*> allatok) : Pisti(allatok) {_e=AllatEnor(&_allatok);}
};



TEST_CASE("beolvasas", "inp1.txt")
{
    string file="inp1.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);

    CHECK(pisti.getAllatok()[0]->getEletkedv()==4);
    CHECK(pisti.getAllatok()[0]->getNev()=="Sanyi");
    CHECK(pisti.getAllatok()[0]->getFaj()=="hal");
    CHECK(pisti.getAllatok()[1]->getEletkedv()==4);
    CHECK(pisti.getAllatok()[1]->getNev()=="Pityu");
    CHECK(pisti.getAllatok()[1]->getFaj()=="madar");
    CHECK(pisti.getAllatok()[2]->getEletkedv()==4);
    CHECK(pisti.getAllatok()[2]->getNev()=="Bodri");
    CHECK(pisti.getAllatok()[2]->getFaj()=="kutya");/**/
}

TEST_CASE("minden allat eletkedve kisebb mint 5", "inp1.txt")
{
    string file="inp1.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);

    CHECK(pisti.getAllatok()[0]->getEletkedv()==2);
    CHECK(pisti.getAllatok()[1]->getEletkedv()==5);
    CHECK(pisti.getAllatok()[2]->getEletkedv()==7);
}


TEST_CASE("van allat legalabb 5 eletkedvvel", "inp2.txt")
{
    string file="inp2.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);

    CHECK(pisti.getAllatok()[0]->getEletkedv()==2);
    CHECK(pisti.getAllatok()[1]->getEletkedv()==6);
    CHECK(pisti.getAllatok()[2]->getEletkedv()==7);
}


TEST_CASE("mindegyik allat legalabb 5 eletkedvvel rendelkezik", "inp3.txt")
{
    string file="inp3.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);

    CHECK(pisti.getAllatok()[0]->getEletkedv()==13);
    CHECK(pisti.getAllatok()[1]->getEletkedv()==16);
    CHECK(pisti.getAllatok()[2]->getEletkedv()==19);
}

TEST_CASE("egy allat elpusztul", "inp4.txt")
{
    string file="inp4.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    REQUIRE(pisti.getAllatok().size()==2);
    CHECK(pisti.getAllatok()[0]->getNev()=="Pityu");
    CHECK(pisti.getAllatok()[1]->getNev()=="Bodri");
}

TEST_CASE("tobb mint 1 allat elpusztul egy napon", "inp5.txt")
{
    string file="inp5.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    REQUIRE(pisti.getAllatok().size()==1);
    CHECK(pisti.getAllatok()[0]->getNev()=="Pityu");
}

TEST_CASE("minden allat elpusztul", "inp6.txt")
{
    string file="inp6.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    CHECK(pisti.getAllatok().size()==0);
}

TEST_CASE("egy legszomorubb", "inp7.txt")
{
    string file="inp7.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    vector<string> v;
    minKer(&pisti, &v);
    REQUIRE(v.size()==1);
    CHECK(v[0]=="Bodri");
}

TEST_CASE("tobb legszomorubb", "inp8.txt")
{
    string file="inp8.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    vector<string> v;
    minKer(&pisti, &v);
    REQUIRE(v.size()==2);
    CHECK(v[0]=="Pityu");
    CHECK(v[1]=="Bodri");
}


TEST_CASE("minden allat egyenlo eletkedvu", "inp9.txt")
{
    string file="inp9.txt";
    vector<Allat*> allatok;
    ifstream f;
    beolvas(file, &allatok, &f);
    testPisti pisti(allatok);
    napokFeldogozasa(&pisti, &f);
    vector<string> v;
    minKer(&pisti, &v);
    REQUIRE(v.size()==3);
    CHECK(v[0]=="Sanyi");
    CHECK(v[1]=="Pityu");
    CHECK(v[2]=="Bodri");
}





#endif // NORMAL_MODE
