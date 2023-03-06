#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Locuinta{

    string client;
    int suprafata;
    int pret;
    int discount;

public:

    Locuinta()
    {
        this-> client = "";
        this-> suprafata = 0;
        this-> pret = 0;
        this-> discount = 0;
    }

    Locuinta(string client, int suprafata, int pret, int discount)
    {
        this-> client = client;
        this-> suprafata = suprafata;
        this-> pret = pret;
        this-> discount = discount;
    }

    virtual ~Locuinta(){};

    int getpret()
    {
        return pret;
    }

    int getsuprafata()
    {
        return suprafata;
    }

    int getdiscount()
    {
        return discount;
    }

    virtual void citire()
    {
        cout<<"Nume client: ";
        cin>>client;

        cout<<"Suprafata utila: ";
        cin>>suprafata;

        cout<<"Pret pe metru patrat: ";
        cin>>pret;

        cout<<"Discount: ";

        try
        {
            cin>>discount;

            if(discount < 0 || discount > 0)
                throw(discount);
        }

        catch(int disc)
        {
            cout<<"Reintroduceti discountul: ";
            cin>>disc;
            discount = disc;
        }
    }

    virtual void afisare()
    {
        cout<<"Nume client: "<<client<<endl;

        cout<<"Suprafata utila: "<<suprafata<<endl;

        cout<<"Pret pe metru patrat: "<<pret<<endl;

        cout<<"Discount: "<<discount<<endl;
    }

};


class Apartament: public Locuinta{

    int etaj;

public:

    Apartament():Locuinta()
    {
        this-> etaj = 0;
    }

    Apartament(string client, int suprafata, int pret, int discount, int etaj): Locuinta(client, suprafata, pret, discount)
    {
        this-> etaj = etaj;
    }

    ~Apartament(){};

    void citire()
    {
        Locuinta::citire();

        cout<<"Etajul apartamentului: ";
        cin>>etaj;
    }

    void afisare()
    {
        Locuinta::afisare();

        cout<<"Etajul apartamentului: "<<etaj<<endl;
    }
};


class Casa: public Locuinta{

    int mpcurte;
    int nretaje;
    vector <int> s;

public:

    Casa():Locuinta()
    {
        this-> mpcurte = 0;
        this-> nretaje = 0;
        this-> s.clear();
    }

    Casa(string client, int suprafata, int pret, int discount, int mpcurte, int nretaje, vector <int> s): Locuinta(client, suprafata, pret, discount)
    {
        this-> mpcurte = mpcurte;
        this-> nretaje = nretaje;

//        for(int i = 0; i < nretaje; i++)
//        {
//            s.push_back(new int());
//        }
//
//        for(auto p = s.begin(); p != s.end(); p++)
//        {
//            (*p)->
//        }
    }

    ~Casa(){};

    vector <int> gets()
    {
        return s;
    }

    int getmpcurte()
    {
        return mpcurte;
    }

    void citire()
    {
        Locuinta::citire();

        cout<<"Numar metrii patrati ai curtii: ";
        cin>>mpcurte;

        cout<<"Numar etaje casa: ";
        cin>>nretaje;

        int suprafetaj;
        for(int i = 0; i < nretaje; i++)
        {
            cout<<"Etajul "<<i<<" are suprafata utila (metri patrati) de: ";
            cin>>suprafetaj;
            s.push_back(suprafetaj);
        }
    }

    void afisare()
    {
        Locuinta::afisare();

        cout<<"Numar metrii patrati ai curtii: "<<mpcurte<<endl;

        cout<<"Numar etaje casa: "<<nretaje<<endl;

        int i = 0;
        for(auto p = s.begin(); p != s.end(); p++, i++)
        {
            cout<<"Etajul "<<i<<" are suprafata utila (metri patrati) de: "<<*p<<endl;
        }
    }
};

void citireLoc(vector <Locuinta*> v)
{   int n;
    cout<<"Introduceti numarul de locuinte: ";
    cin>>n;
    int t[n+1];

    string tip;
    for(int i = 1; i <= n; i++)
    {
        cout << "Tipul locuintei ('c' pt casa/'a' pt apartament) cu numarul " << i << ": ";
        cin >> tip;

        if(tip == "a"){
            v.push_back(new Apartament());
            t[i] = 0;
        }

        if(tip == "c"){
            v.push_back(new Casa());
            t[i] = 1;
        }
    }

    int i = 0;
    for(auto p = v.begin(); p != v.end(); p++, i++)
    {
        cout << "Locuinta " << i+1 << ":" << endl;
        (*p) -> citire();
        cout << endl;
    }
    cout<<endl;
}

void afisareLoc(vector <Locuinta*> v)
{
    int i = 1;
    for(auto p = v.begin(); p != v.end(); p++, i++)
    {
        if(v[i] == 0)
            cout << "Locuinta " << i << "- apartament:" << endl;
        else
            cout << "Locuinta " << i << "- casa:" << endl;

        (*p) -> afisare();
        cout << endl;
    }
}

void cost(vector <Locuinta*> v)
{
    int i = 1, total = 0;
    for(auto p = v.begin(); p != v.end(); p++, i++)
    {
        if(v[i] == 0)
        {
            cout << "Locuinta " << i << "este apartament si are pretul de inchiriere/luna de:";
            total = (*dynamic_cast <Locuinta*> (*p)).getsuprafata();
        }
        else
        {
            cout << "Locuinta " << i << "este casa si are pretul de inchiriere/luna de:";
            vector <int> vect = (*dynamic_cast <Casa*> (*p)).gets();
            total = 0;
            for(auto x = vect.begin(); x != vect.end(); x++)
            {
                total += *x;
            }
            total += (*dynamic_cast <Casa*> (*p)).getmpcurte();
        }

    int d = (*dynamic_cast <Locuinta*> (*p)).getdiscount();
    int pr = (*dynamic_cast <Locuinta*> (*p)).getpret();

    float rez;

    rez = (total * pr * (100-d) / 100) + (total * pr * (100-d) % 100);

        cout << rez << endl;
    }
}

int meniu(){

    int tasta;

    cout<<endl<<"Apasati tasta corespunzatoare comenzii pe care doriti sa o executati:"<<endl<<endl;
    cout<<"1. Citirea locuintelor din dosar"<<endl;
    cout<<"2. Afisarea locuintelor din dosar"<<endl;
    cout<<"3. Afisarea costului de inchiriere al locuintelor din dosar"<<endl<<endl;
    cout<<"Pentru a parasi meniul apasati orice alta tasta."<<endl<<endl;

    cin>>tasta;

    cout<<endl;

    return tasta;

}


int main()
{   vector <Locuinta*> loc;
    int option;
    bool k = true;

    while(k)
        {

        option = meniu();

        switch(option)
        {

        case 1:
            {
                citireLoc(loc);
                break;
            }

        case 2:
            {
                afisareLoc(loc);
                break;
            }

        case 3:
            {
                cost(loc);
                break;
            }

        default:
            {
                cout << "La revedere!" << endl;
                k = false;
            }
        }
    }

    return 0;
}
