#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class vectory         //klasa z wektorem klasy dla sekwencji
{
    public:
    string nazwa;
    vector <char> sekwencja;
    vector <int> wartosc;
    vector <int> pozycja;

    vectory(string n)  //konstruktor wektora z przypisaniem nazwy sekwencji
    {
        nazwa = n;
    }
    void v_sekwencja(char s)  //wpisanie sekwencji
    {
        sekwencja.push_back(s);
    }
    void v_wartosc(int w)
    {
        wartosc.push_back(w); //wpisanie wartosci
    }
    void v_pozycja(int p)
    {
        pozycja.push_back(p);  // wpisanie pozycji
    }
};
vector <vectory> vectoryyy;

class wierzcholki          //klasa z wektorem klasy dla wierzcholkow
{
public:
    wierzcholki(){}        // konstruktor klasy (dzieki niemu tworzy sie obiekt)
    vector <char> podciag;
    vector <int> lista_nastepnikow;

    string nazwa_sek;
    int numer_sek;
    int numer_podc;
    int id;

    void w_podciag(char p)       //SPISANIE SEQ. PODCIAGU DO VEKTORA
    {
        podciag.push_back(p);
    }
    void w_numer_sek(int n)    //PRZYPISANIE Z KTOREJ SEKWENCJI POCHODZI PODCIAG
    {
        numer_sek = n;
    }
    void w_numer_podc(int u)   //PRZYPISANIE POZYCJI PIERWSZEGO NT W PODCIAGU
    {
        numer_podc = u;
    }
    void w_lista_nastepnikow(int l)        //DODANIE DO LISTY NASTEPNIKOW DLA DANEGO WIERZCHOLKA
    {
        lista_nastepnikow.push_back(l);
    }
    void dodaj_id(int d)       //NUMER WIERZCHOLKA
    {
        id = d;
    }
    void w_nazwa_sek(string seq)
    {
        nazwa_sek = seq;
    }

};
vector <wierzcholki> wierzcholkiii;

class klikii      // klasa z wektorem klasy dla kliki
{
    public:
    klikii(){}
    vector <char> sekw_kliki;   //zapamietanie sekwencji kliki
    vector <int> element_kliki;     //zapamietanie elementow kliki (nr. wierzcholkow nalezacych do kliki)
    int id_kliki;               //zapamietanie id/numeru kliki
    vector <int> podc_kliki;    //zapamietanie nr podciagu elementu z kliki
    vector <string> nazwa_sekw_kliki;     //nazwy sekwencji z ktorych pochodza elementy kliki

    void K_sekw(char c)
    {
        sekw_kliki.push_back(c);
    }
    void K_element(int n)
    {
        element_kliki.push_back(n);
    }
    void K_id(int id)
    {
        id_kliki = id;
    }
    void K_podciag(int cp)        //wepchniecie nr podciagu z sekwencji oryginalnej
    {
        podc_kliki.push_back(cp);
    }
    void K_nazwa(string cs)         //wepchniecie nazwy sekwencji z jakiej pochodzi podc
    {
        nazwa_sekw_kliki.push_back(cs);
    }
};
vector <klikii> klikaa;

void wyswietl()     // wyswietlanie sekwencji i ich wiarygodnosci
{
    cout <<"WCZYTANIE PLIKOW:"<< endl;
    for(int i = 0; i < vectoryyy.size(); i++)
   {
       cout << "Sekwencja: " << vectoryyy[i].nazwa << endl;
       for(int j = 0; j < vectoryyy[i].sekwencja.size(); j++)
       {
           cout << vectoryyy[i].sekwencja[j] << " ";

       }
       cout << endl;
       cout << "Wiarygodnosc: " <<endl;
       for(int k = 0; k < vectoryyy[i].wartosc.size(); k++)
       {
           cout << vectoryyy[i].wartosc[k] << " ";
       }
       cout << "" << endl;
       cout <<"-------------------------"<<endl;

    }
}


void wczytaj(string fasta,string qual)   // wczytywanie plikow
{
   fstream file1;
   string f1 = fasta + ".txt";

    //wczytanie pierwszego plik
   file1.open(f1, ios::in);

   if(file1.good() == false)
   {
       cout << "Brak pliku do odczytu." << endl;
   }

    string line;
    char nukleotyd;


   while(file1.good()== true)
   {
       int poz = 1;    //pozycja nukleotydu

        getline(file1, line);    //bierze pierwsza linie z pliku
        vectory *temp = new vectory(line);    //tworzy nowy obiekt vectorow

        file1 >> nukleotyd;                                     //odczytuje znak po znaku plik,
        if(nukleotyd == '|')
        {
            file1.close();
            break;
            cout << "Wczytano plik fasta." << endl;
        }

        while(nukleotyd != '>')                              //jesli pierwszy znak w linii jest != od > to rozpoczyna sie wczytywanie sekwencji
        {
            temp->v_sekwencja(nukleotyd);
            temp->v_pozycja(poz);
            poz++;
            file1 >> nukleotyd;
            if(nukleotyd == '>' || nukleotyd == '|')
                break;
        }

        vectoryyy.push_back(*temp);                          //przeslanie utworzonego wektora do vektorow

        if(nukleotyd == '|')
        {
            file1.close();
        }
    }


    //wczytanie drugiego pliku
    fstream file2;
    string f2 = qual + ".txt";

    file2.open(f2,ios::in);

    int i = 0;  //do wczytania sekwencji do odpowiedniego vektora
    int val;

    if(file2.good() == false)
    {
        cout << "Brak pliku do odczytu" << endl;
    }


    while(file2.good() == true)
    {
        getline(file2, line);       //bierze pierwsza linie z pliku tekstowego

        file2 >> val;

        while(val != 0)
        {
            vectoryyy[i].v_wartosc(val);
            file2 >> val;
            if(val == 0)
            {
                i++;
                break;
            }

        }
        if( val == '|')
        {
            file2.close();
        }
        getline(file2, line);

    }


    for(int i = 1; i < vectoryyy.size(); i++)    //dodawanie >
    {
        vectoryyy[i].nazwa = ">"+vectoryyy[i].nazwa;
    }


   return;
}


void usuwanie_pozycji(int wiarygodnosc)   // usuwanie nukleotydow o wartosci < wiarygodnosci
{
    for(int i = 0; i < vectoryyy.size(); i++)
    {
        for(int j = 0; j < vectoryyy[i].wartosc.size(); j++)  // przechodzimy po indeksach wartosci sekwencji
        {
            if(vectoryyy[i].wartosc[j] < wiarygodnosc)
            {
                vectoryyy[i].wartosc.erase(vectoryyy[i].wartosc.begin() + j);
                vectoryyy[i].sekwencja.erase(vectoryyy[i].sekwencja.begin() + j);
                vectoryyy[i].pozycja.erase(vectoryyy[i].pozycja.begin() +j);
                j = 0;                                 // j zerujemy, bo inaczej przeskakuje nam jeden nukleotyd i nie sprawdza ( ewentualnie j--;)
            }
        }
    }
    return;
}


void graf_wierzcholki(int podciag)  // tworzenie wierzcholkow podciagow
{
    int id = 0;
    for(int i = 0; i < vectoryyy.size(); i++)
    {
        for(int j = 0; j < vectoryyy[i].sekwencja.size() - podciag; j++) // przechodzimy po rozmiarach sekwencji - podciag
        {
            wierzcholki *temp = new wierzcholki;       // nowy obiekt wierzcholkow
            for(int k = 0; k < podciag; k++)           // spisywanie podciagow
            {
                temp->w_podciag(vectoryyy[i].sekwencja[j+k]);

            }
            temp->w_numer_sek(i);                           //sekwencja podciagu
            temp->w_numer_podc(vectoryyy[i].pozycja[j]);    //pierwszy nukleotyd w sekwencji podciagu
            temp->dodaj_id(id);                            //id wierzcholka
            temp->w_nazwa_sek(vectoryyy[i].nazwa);         //nazwa sekwencji,z ktorej jest wierzcholek

            wierzcholkiii.push_back(*temp);        // dodajemy obiekt do wierzcholkow
            id++;
        }
    }
    return;
}


void polacz_wierzcholki()   // laczenie wierzcholkow
{
    int rozmiar = wierzcholkiii.size();
    for(int i = 0; i < wierzcholkiii.size(); i++)     //
    {

        for(int j = 0; j < wierzcholkiii.size(); j++)    //
        {
            int dopasowanie = 0;

            if(i != j)                               //
            {
                for(int k = 0; k < wierzcholkiii[i].podciag.size(); k++)   //
                {
                    if(wierzcholkiii[i].podciag[k] == wierzcholkiii[j].podciag[k])    //
                    {
                        dopasowanie++;

                    }
                }
                if(dopasowanie == wierzcholkiii[i].podciag.size())  //
                        wierzcholkiii[i].w_lista_nastepnikow(j);
            }
        }
    }
    return;
}


void klika()   // szukanie / tworzenie kliki
{
    bool sekwencje[5];
    bool ok = true;
    int id = 1;

    for(int i = 0; i < wierzcholkiii.size(); i++)
    {
        klikii *temp = new klikii;
        for(int b = 0; b < 5; b++)
        {
            sekwencje[b] = false;
        }

        if(wierzcholkiii[i].lista_nastepnikow.size() >= 4)
        {
            for(int j = 0; j < wierzcholkiii[i].lista_nastepnikow.size(); j++)
            {
                if(wierzcholkiii[i].numer_sek == 0 )
                {
                    sekwencje[0] = true;
                }
                for(int d =1; d < 5; d++)
                {
                    if(wierzcholkiii[wierzcholkiii[i].lista_nastepnikow[j]].numer_sek == d)
                    {
                        sekwencje[d] = true;
                    }
                }
            }

            for(int k = 0; k < 5; k++)
            {
                if(sekwencje[k] == false)
                {
                    ok = false;
                }

            }
            if(ok == true)
            {
                temp->sekw_kliki = wierzcholkiii[i].podciag;
                temp->K_element(wierzcholkiii[i].id);

                temp->K_id(id);
                id++;
                for(int g = 0; g < wierzcholkiii[i].lista_nastepnikow.size(); g++)
                {
                    temp->K_element(wierzcholkiii[i].lista_nastepnikow[g]);
                }

                klikaa.push_back(*temp);
            }

        }
    }


    for(int i = 0; i < klikaa.size(); i++)
    {
        for(int j = 0; j < klikaa[i].element_kliki.size() ; j++)
        {
            for(int k = 0; k < wierzcholkiii.size(); k++)
            {
                if(klikaa[i].element_kliki[j] == wierzcholkiii[k].id)
                {
                        klikaa[i].K_nazwa(wierzcholkiii[k].nazwa_sek);
                        klikaa[i].K_podciag(wierzcholkiii[k].numer_podc);
                }
            }
        }
    }


    return;
}


void wyswietl_klike()  // wyswietlanie klik
{
     cout << klikaa.size() << " klik:" << endl;
     for(int i = 0; i < klikaa.size(); i++)
    {
            cout << "Klika nr: " << klikaa[i].id_kliki << " | Sekwencja kliki: ";
            for(int j = 0; j < klikaa[i].sekw_kliki.size(); j++)
            {
                cout << klikaa[i].sekw_kliki[j] << " " ;
            }
            cout << endl;
            cout << "Elementy kliki:" << endl ;
            cout << "   Sekwencja     ----- Nr poz. " << endl;
            for(int k = 0; k < klikaa[i].element_kliki.size(); k++)
            {
                cout << klikaa[i].nazwa_sekw_kliki[k] << "  -----  " << klikaa[i].podc_kliki[k] << endl;

            }
            cout << "" << endl;
            cout << ""<<endl;

    }
}


int main()
{
    int wiarygodnosc;    //wartosc wiarygodnosci do usuniecia nukleotydow
    int podciag;         //jaka dlugosc ma miec tworzony podciag
    string file1;
    string file2;


    cout << "Podaj nazwe pliku z sekwencjami do odczytu: ";
    cin >> file1;
    cout << "Podaj nazwe pliku z ocenami jakosci nukleotydow do odczytu: ";
    cin >> file2;

    wczytaj(file1, file2);
    cout << "Podaj wartosc wiarygodnosci: " << endl;
    cin >> wiarygodnosc;
    usuwanie_pozycji(wiarygodnosc);

    cout << "Podaj dlugosc podciagow w zakresie od 4 do 9: " << endl;
    cin >> podciag;
    while(podciag < 4 || podciag > 9)
    {
        cout << "Podaj wartosc podciagow w zakresie od 4 do 9." << endl;
        cin >> podciag;
    }
    graf_wierzcholki(podciag);
    polacz_wierzcholki();
    klika();
    wyswietl_klike();

    return 0;
}
