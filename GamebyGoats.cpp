#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

const int lygiu_kiekis = 3;

string SUNKUMAS;

clock_t start, finish;

struct Priesas
{
    int lygis;
    int health_min;
    int health_max;
    int chance;
};

struct Regionai
{
    bool Buvo;
    bool Terai;
};

struct Shop
{
    int Maistas;
    int Sarvai[lygiu_kiekis];
    int Sarvu_kainos[lygiu_kiekis];
    int Sarvu_patvarumas;
    int Ginklai[lygiu_kiekis];
    int Ginklu_kainos[lygiu_kiekis];
    int Soviniai;
    int Kompanijonai;
}P;

struct Zaidimo_lvl
{
    int Regionu_kiekis;
    struct Regionai* regionas;
    int Teru_kiekis;
    int Auksas_min;
    int Auksas_max;
    int Stovyklu_kiekis;
    bool Stovykla;
    struct Priesas Priesas;
};

struct Inventorius
{
    int Kompanijonai;
    int Maistas;
    int Auksas;
    int Sarvai;
    int Sarvu_patvarumas;
    int ginklas;
    int Soviniai;
};

struct Zaidejas
{
    string Vardas;
    int dabartinis_lygis;
    double laikas;
    Inventorius inv;
    int rastas_Auksas;
    int iveikti_priesai;
    int Teru_liko;
    int ejimai;
};

struct Top
{
    string Vardas;
    double laikas;
    int ejimai;
    int rastas_Auksas;
    int iveikti_priesai;
};

void pagrindinis_meniu(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
void naujas_zaidimas(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
int zaidimo_sunkumas();
void testi_zaidima(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
void zaidimo_meniu(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
void Keliauti_i_Regionas(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z);
void Priesas(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z, int pasirinkimas);
void Terai_regione(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z, int pasirinkimas);
void Priesasin(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z, int pasirinkimas);
void Keliauti_i_Stovykla(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z);
void resursu_pirkimas(int& Auksas, int& resursas, string pav1, string pav2, string pav3, int kaina);
void Sarvu_ginklo_pirkimas(int& Auksas, int& resursas, string pav1, string pav2, string pav3, int pirkinys[], int kaina[]);
void issaugoti_zaidima(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
void zaidimas_pralaimetas(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
void zaidimas_pereitas(struct Zaidimo_lvl Lygis[], struct Zaidejas Z);
void taisykles();


int main()
{
    struct Zaidimo_lvl Lygis[lygiu_kiekis];
    struct Zaidejas Z;
    pagrindinis_meniu(Lygis, Z);
    return 0;
}

void pagrindinis_meniu(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    system("CLS");
    string pasirinkimas;
    while (1)
    {
        cout << "***********************************************" << endl;
        cout << "************* PANDOROS BEIESKANT *****************" << endl;
        cout << "************* PANDOROS BEIESKANT *****************" << endl;
        cout << "************* PANDOROS BEIESKANT *****************" << endl;
        cout << "************* PANDOROS BEIESKANT *****************" << endl;
        cout << "************* PANDOROS BEIESKANT *****************" << endl;
        cout << "***********************************************" << endl;
        cout << "---------------PAGRINDINIS MENIU---------------" << endl;
        cout << "             [1] Pradeti nauja zaidima" << endl;
        cout << "             [2] Testi zaidima" << endl;
        cout << "             [4] Zaidimo taisykles" << endl;
        cout << "             [5] Iseiti is zaidimo" << endl;
        cout << endl;
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;
        if (pasirinkimas == "1")
        {
            naujas_zaidimas(Lygis, Z);
            system("CLS");
        }
        else if (pasirinkimas == "2")
        {
            testi_zaidima(Lygis, Z);
            system("CLS");
        }
        else if (pasirinkimas == "3")
        {
            taisykles();
            system("CLS");
        }
        else if (pasirinkimas == "4")
        {
            exit(0);
        }
        else
        {
            system("CLS");
        }
    }
}

void naujas_zaidimas(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    system("CLS");
    cout << "Iveskite zaidejo varda: ";
    cin >> Z.Vardas;
    Z.laikas = 0;
    Z.Teru_liko = 0;
    Z.ejimai = 0;
    int sunkumas = zaidimo_sunkumas();
    int lobiu_skaicius, Regionai_indeksas;
    // Lengvas sunkumas
    if (sunkumas == 1)
    {
        // Sugeneruojami zaidimo lygiai (Regionu kiekis, Stovykla, teru kiekis, kuriose Regionuose terai
        //, sansas sutikti priesus
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            Lygis[i].Regionu_kiekis = i + 3;
            Lygis[i].Teru_kiekis = i + 2;
            Lygis[i].Auksas_min = (i + 1) * 50;
            Lygis[i].Auksas_max = (i + 2) * 50;
            Lygis[i].Stovykla = false;
            Lygis[i].Priesas.lygis = i + 2;
            Lygis[i].Priesas.health_min = i + 1;
            Lygis[i].Priesas.health_max = i + 2;
            Lygis[i].Priesas.chance = (i + 2) * 10; ///20% 30% 40%
            //////////////////////////////////////////////////////
            Lygis[i].regionas = (Regionai*)malloc(Lygis[i].Regionu_kiekis);
            for (int j = 0; j < Lygis[i].Regionu_kiekis; j++)
            {
                Lygis[i].regionas[j].Buvo = false;
                Lygis[i].regionas[j].Terai = false;
            }
            // Paskirstomi lobiai i regionus
            //srand(time(NULL));
            lobiu_skaicius = Lygis[i].Teru_kiekis;
            while (lobiu_skaicius != 0)
            {
                Regionai_indeksas = rand() % Lygis[i].Regionu_kiekis + 1;
                if (Lygis[i].regionas[Regionai_indeksas - 1].Terai == false)
                {
                    Lygis[i].regionas[Regionai_indeksas - 1].Terai = true;
                    lobiu_skaicius--;
                }
            }
            Z.Teru_liko += Lygis[i].Teru_kiekis;
        }
        // Sugeneruoja parduotuves daiktus ir kainas
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            P.Sarvai[i] = i + 2;
            P.Sarvu_kainos[i] = (i + 1) * 100;
            P.Ginklai[i] = i + 2;
            P.Ginklu_kainos[i] = (i + 1) * 50;
        }
        P.Maistas = 50;
        P.Sarvu_patvarumas = 20;
        P.Soviniai = 20;
        P.Kompanijonai = 100;
    }
    // Vidutinis sunkumas
    if (sunkumas == 2)
    {
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            Lygis[i].Regionu_kiekis = (i * 2) + 4;
            Lygis[i].Teru_kiekis = Lygis[i].Regionu_kiekis * 0.5;
            Lygis[i].Auksas_min = (i + 1) * 70;
            Lygis[i].Auksas_max = (i + 2) * 70;
            Lygis[i].Stovykla = false;
            Lygis[i].Priesas.lygis = i + 2;
            Lygis[i].Priesas.health_min = i + 2;
            Lygis[i].Priesas.health_max = i + 3;
            Lygis[i].Priesas.chance = (i + 3) * 10; ///30% 40% 50%
            Lygis[i].Priesas.lygis = i + 1;
            Lygis[i].Priesas.health_min = i + 2;
            Lygis[i].Priesas.health_max = i + 3;
            Lygis[i].Priesas.chance = (i + 3) * 10; ///30% 40% 50%
            //////////////////////////////////////////////////////
            Lygis[i].regionas = (Regionai*)malloc(Lygis[i].Regionu_kiekis);
            for (int j = 0; j < Lygis[i].Regionu_kiekis; j++)
            {
                Lygis[i].regionas[j].Buvo = false;
                Lygis[i].regionas[j].Terai = false;
            }
            // Paskirstomi terai regiuonose
            srand(time(NULL));
            lobiu_skaicius = Lygis[i].Teru_kiekis;
            while (lobiu_skaicius != 0)
            {
                Regionai_indeksas = rand() % Lygis[i].Regionu_kiekis + 1;
                if (Lygis[i].regionas[Regionai_indeksas - 1].Terai == false)
                {
                    Lygis[i].regionas[Regionai_indeksas - 1].Terai = true;
                    lobiu_skaicius--;
                }
            }
            Z.Teru_liko += Lygis[i].Teru_kiekis;
        }
        // Sugeneruoja parduotuves daiktus ir kainas
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            P.Sarvai[i] = i + 2;
            P.Sarvu_kainos[i] = (i + 1) * 125;
            P.Ginklai[i] = i + 2;
            P.Ginklu_kainos[i] = (i + 1) * 75;
        }
        P.Maistas = 50;
        P.Sarvu_patvarumas = 20;
        P.Soviniai = 20;
        P.Kompanijonai = 100;
    }
    // Sunkus sunkumas
    if (sunkumas == 3)
    {
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            Lygis[i].Regionu_kiekis = (i * 3) + 5;
            Lygis[i].Teru_kiekis = Lygis[i].Regionu_kiekis * 0.7;
            Lygis[i].Auksas_min = (i + 1) * 90;
            Lygis[i].Auksas_max = (i + 2) * 90;
            Lygis[i].Stovykla = false;
            Lygis[i].Priesas.lygis = i + 1;
            Lygis[i].Priesas.health_min = i + 3;
            Lygis[i].Priesas.health_max = i + 4;
            Lygis[i].Priesas.chance = (i + 4) * 10; ///40% 50% 60%
            Lygis[i].Priesas.lygis = i + 1;
            Lygis[i].Priesas.health_min = i + 3;
            Lygis[i].Priesas.health_max = i + 4;
            Lygis[i].Priesas.chance = (i + 4) * 10; ///40% 50% 60%
            //////////////////////////////////////////////////////
            Lygis[i].regionas = (Regionai*)malloc(Lygis[i].Regionu_kiekis);
            for (int j = 0; j < Lygis[i].Regionu_kiekis; j++)
            {
                Lygis[i].regionas[j].Buvo = false;
                Lygis[i].regionas[j].Terai = false;
            }
            // Paskirstomi terai i regionus//
            srand(time(NULL));
            lobiu_skaicius = Lygis[i].Teru_kiekis;
            while (lobiu_skaicius != 0)
            {
                Regionai_indeksas = rand() % Lygis[i].Regionu_kiekis + 1;
                if (Lygis[i].regionas[Regionai_indeksas - 1].Terai == false)
                {
                    Lygis[i].regionas[Regionai_indeksas - 1].Terai = true;
                    lobiu_skaicius--;
                }
            }
            Z.Teru_liko += Lygis[i].Teru_kiekis;
        }
        // Sugeneruoja parduotuves daiktus ir kainas
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            P.Sarvai[i] = i + 2;
            P.Sarvu_kainos[i] = (i + 1) * 150;
            P.Ginklai[i] = i + 2;
            P.Ginklu_kainos[i] = (i + 1) * 100;
        }
        P.Maistas = 50;
        P.Sarvu_patvarumas = 20;
        P.Soviniai = 20;
        P.Kompanijonai = 100;
    }
    // Sugeneruojamas zaidejo inventorius
    Z.inv.Kompanijonai = 5;
    Z.inv.Maistas = 300;
    Z.inv.Auksas = 500;
    Z.inv.Sarvai = 20;
    Z.inv.Sarvu_patvarumas = 1;
    if (Z.inv.Sarvu_patvarumas == 0) {
        zaidimas_pralaimetas(Lygis, Z);
    }
    Z.inv.ginklas = 1;
    Z.inv.Soviniai = 500;
    /////
    Z.rastas_Auksas = 0;
    Z.iveikti_priesai = 0;
    /////
    Z.dabartinis_lygis = 1;
    /////
    zaidimo_meniu(Lygis, Z);
}

int zaidimo_sunkumas()
{
    system("CLS");
    string pasirinkimas;
    while (1)
    {
        cout << "----------PAGRINDINIS MENIU----------" << endl;
        cout << "     Pasirinkite zaidimo sunkuma:" << endl;
        cout << "           [1] Lengvas" << endl;
        cout << "          [2] Vidutinis" << endl;
        cout << "            [3] Sunkus" << endl;
        cout << endl;
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;
        if (pasirinkimas == "1")
        {
            SUNKUMAS = "Lengvas";
            return 1;
        }
        else if (pasirinkimas == "2")
        {
            SUNKUMAS = "Vidutinis";
            return 2;
        }
        else if (pasirinkimas == "3")
        {
            SUNKUMAS = "Sunkus";
            return 3;
        }
        else
        {
            system("CLS");
        }
    }
}

void testi_zaidima(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    ifstream file;
    file.open("save.txt");
    if (file.is_open())
    {
        file.seekg(0, ios::end);
        size_t failo_dydis = file.tellg();
        file.close();
        file.open("save.txt");
        if (failo_dydis == 0)
        {
            system("CLS");
            cout << "Issaugoto zaidimo nera." << endl;
            cout << "Norint grizti atgal i meniu, spauskite ENTER..." << endl;
            _getch();
        }
        else
        {
            file >> Z.Vardas;
            file >> SUNKUMAS;
            file >> Z.dabartinis_lygis;
            file >> Z.laikas;
            file >> Z.ejimai;
            file >> Z.Teru_liko;
            for (int i = Z.dabartinis_lygis - 1; i < lygiu_kiekis; i++)
            {
                file >> Lygis[i].Regionu_kiekis;
                file >> Lygis[i].Teru_kiekis;
                file >> Lygis[i].Auksas_min;
                file >> Lygis[i].Auksas_max;
                file >> Lygis[i].Priesas.lygis;
                file >> Lygis[i].Priesas.health_min;
                file >> Lygis[i].Priesas.health_max;
                file >> Lygis[i].Priesas.chance;
                file >> Lygis[i].Priesas.lygis;
                file >> Lygis[i].Priesas.health_min;
                file >> Lygis[i].Priesas.health_max;
                file >> Lygis[i].Priesas.chance;
                Lygis[i].regionas = (Regionai*)malloc(Lygis[i].Regionu_kiekis);
                for (int j = 0; j < Lygis[i].Regionu_kiekis; j++)
                {
                    file >> Lygis[i].regionas[j].Buvo;
                    file >> Lygis[i].regionas[j].Terai;
                }
                file >> Lygis[i].Stovykla;
            }
            file >> Z.inv.Kompanijonai;
            file >> Z.inv.Maistas;
            file >> Z.inv.Auksas;
            file >> Z.inv.Sarvai;
            file >> Z.inv.Sarvu_patvarumas;
            file >> Z.inv.ginklas;
            file >> Z.inv.Soviniai;
            file >> Z.rastas_Auksas;
            file >> Z.iveikti_priesai;
            file >> Z.Teru_liko;

            file >> P.Maistas;
            file >> P.Sarvu_patvarumas;
            file >> P.Soviniai;
            file >> P.Kompanijonai;
            for (int i = 0; i < lygiu_kiekis; i++)
            {
                file >> P.Sarvai[i];
                file >> P.Sarvu_kainos[i];
                file >> P.Ginklai[i];
                file >> P.Ginklu_kainos[i];
            }
            file.close();
            zaidimo_meniu(Lygis, Z);
        }
    }
    file.close();
}

void zaidimo_meniu(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    start = clock();
    system("CLS");
    string pasirinkimas;
    while (1)
    {
        cout << "-----------[ " << Z.dabartinis_lygis << " Lygis ]-----------" << endl;
        cout << "----------ZAIDIMO MENIU----------" << endl;
        cout << "      [1] Keliauti i regiona" << endl;
        cout << "     [2] Keliauti i stovykla" << endl;
        cout << " [3] Iseiti i pagrindini meniu" << endl;
        cout << "---------------------------------" << endl;
        cout << "REGIONAI: " << Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis << endl;
        cout << "TERAI: " << Lygis[Z.dabartinis_lygis - 1].Teru_kiekis << endl;
        cout << "---------------------------------" << endl;
        cout << "|           Inventorius         |" << endl;
        cout << "---------------------------------" << endl;
        cout << "|    Sarvai     |    Ginklas    |" << endl;

        cout << "| LVL " << Z.inv.Sarvai << "   DMG " << Z.inv.Sarvai << " | LVL " << Z.inv.ginklas << "   DMG " << Z.inv.ginklas << " |" << endl;
        cout << "---------------------------------" << endl;
        cout << "| Kompanijonai: " << Z.inv.Kompanijonai << endl;
        cout << "| Auksas: " << Z.inv.Auksas << endl;
        cout << "| Maistas: " << Z.inv.Maistas << endl;
        cout << "| Patvarumas: " << Z.inv.Sarvu_patvarumas << endl;
        cout << "| Soviniai: " << Z.inv.Soviniai << endl;
        cout << "---------------------------------" << endl;
        cout << endl;
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;
        if (pasirinkimas == "1")
        {
            if (Lygis[Z.dabartinis_lygis - 1].Stovykla == true)
            {
                Lygis[Z.dabartinis_lygis - 1].Stovykla = false;
            }
            Z.ejimai++;
            Keliauti_i_Regionas(Lygis, Z);
            system("CLS");
        }
        else if (pasirinkimas == "2")
        {
            if (Lygis[Z.dabartinis_lygis - 1].Stovykla == false)
            {
                Lygis[Z.dabartinis_lygis - 1].Stovykla = true;
                Z.ejimai++;
                Keliauti_i_Stovykla(Lygis, Z);
                system("CLS");
            }
            else
            {
                system("CLS");
                cout << "Jus jau esate stovykloje." << endl;
                cout << "Jei norite grizti, spauskite ENTER..." << endl;
                _getch();
                system("CLS");
            }

        }
        else if (pasirinkimas == "3")
        {
            issaugoti_zaidima(Lygis, Z);
            break;
        }
        else
        {
            system("CLS");
        }
    }
}

void Keliauti_i_Regionas(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z)
{
    system("CLS");
    int pasirinkimas, temp;
    srand(time(NULL));
    cout << "Pasirinkite regiona (nuo 1 iki " << Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis << "): ";
    cin >> pasirinkimas;
    while (1)
    {
        system("CLS");
        if ((pasirinkimas >= 1 && pasirinkimas <= Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis) && Lygis[Z.dabartinis_lygis - 1].regionas[pasirinkimas - 1].Buvo == true)
        {
            cout << "Siame regione jau esate." << endl;
        }
        else if (pasirinkimas < 1 || pasirinkimas > Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis)
        {
            cout << "Neteisingas pasirinkimas." << endl;
        }
        else
        {
            break;
        }
        cout << "Pasirinkite regiona (nuo 1 iki " << Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis << "): ";
        cin >> pasirinkimas;
    }
    // Visi Regionai yra false (nei vienoje is ju siuo metu nesi), 
    //kad nuimt nuo vieno Regionai true (kad esi tame regione siuo metu), kai is jo iskeliauji
    for (int i = 0; i < Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis; i++)
    {
        Lygis[Z.dabartinis_lygis - 1].regionas[i].Buvo = false;
    }
    // Atimami resursai uz keliavima
    if (Z.inv.Maistas > 0)
    {
        Z.inv.Maistas--;
    }
    else if (Z.inv.Kompanijonai > 0)
    {
        Z.inv.Kompanijonai--;
    }
    else
    {
        zaidimas_pralaimetas(Lygis, Z);
    }
    // Jei pakeliui i regiona sutinkami priesai
    temp = rand() % 100 + 1;
    if (temp >= 1 && temp <= Lygis[Z.dabartinis_lygis - 1].Priesas.chance)
    {
        Priesas(Lygis, Z, pasirinkimas);
    }
    Lygis[Z.dabartinis_lygis - 1].regionas[pasirinkimas - 1].Buvo = true;
    // Jei regione yra Terai
    if (Lygis[Z.dabartinis_lygis - 1].regionas[pasirinkimas - 1].Terai == true)
    {
        Terai_regione(Lygis, Z, pasirinkimas);
    }
    // Jei lobio saloje nera
    else
    {
        system("CLS");
        cout << "[ " << pasirinkimas << " regionas ]" << endl;
        cout << "Regione Teru nera." << endl;
        cout << "Norint testi, spauskite ENTER..." << endl;
        _getch();
    }
}

void Priesas(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z, int pasirinkimas)
{
    system("CLS");
    cout << "Keliaujantiant i " << pasirinkimas << " regionas sutikote priesus." << endl;
    int prieso_hp;
    srand(time(NULL));
    prieso_hp = rand() % (Lygis[Z.dabartinis_lygis - 1].Priesas.health_max - Lygis[Z.dabartinis_lygis - 1].Priesas.health_min + 1) + Lygis[Z.dabartinis_lygis - 1].Priesas.health_min;
    
    while (Z.inv.Kompanijonai > 0 && prieso_hp > 0)
    {
        if (Z.inv.Sarvu_patvarumas > 0)
        {
            prieso_hp -= Z.inv.Sarvai;
            Z.inv.Sarvu_patvarumas--;
        }
        if (prieso_hp > 0)
        {
            Z.inv.Kompanijonai -= Lygis[Z.dabartinis_lygis - 1].Priesas.lygis;
        }
    }
    // Jei Priesas iveikiamas
    if (prieso_hp < 1)
    {
        Z.iveikti_priesai++;
        cout << "Priesas nugaletas." << endl;
        cout << "Norint testi, spauskite ENTER..." << endl;
        _getch();
    }
    // Jei pralaimima (zaidejo Kompanijonai zuna)
    else
    {
        zaidimas_pralaimetas(Lygis, Z);
    }
}

void Terai_regione(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z, int pasirinkimas)
{
    system("CLS");
    int temp, Teru_drop;
    srand(time(NULL));
    cout << "[ " << pasirinkimas << " regionas ]" << endl;
    cout << "Regione radote Teru." << endl;
    temp = rand() % 100 + 1;
    // Jei saloje sutinkami priesai
    if (temp >= 1 && temp <= Lygis[Z.dabartinis_lygis - 1].Priesas.chance)
    {
        Priesas(Lygis, Z, pasirinkimas);
    }
    // Paskaiciuoja random aukso kieki gauta su Terais, nuo galimo gauti aukso minimumo iki maximumo
    Teru_drop = rand() % (Lygis[Z.dabartinis_lygis - 1].Auksas_max - Lygis[Z.dabartinis_lygis - 1].Auksas_min + 1) + Lygis[Z.dabartinis_lygis - 1].Auksas_min;
    Z.inv.Auksas += (Teru_drop / 10 * 10);
    Z.rastas_Auksas += (Teru_drop / 10 * 10);
    Lygis[Z.dabartinis_lygis - 1].regionas[pasirinkimas - 1].Terai = false;
    Lygis[Z.dabartinis_lygis - 1].Teru_kiekis--;
    Z.Teru_liko--;
    cout << "Terai sekmingai surinkti." << endl;
    cout << "Norint testi, spauskite ENTER..." << endl;
    _getch();
    if (Lygis[Z.dabartinis_lygis - 1].Teru_kiekis == 0)
    {
        if (Z.Teru_liko != 0)
        {
            system("CLS");
            cout << "Visi " << Z.dabartinis_lygis << " Lygi esantis Terai surinkti." << endl;
            Z.dabartinis_lygis++;
            cout << "Pereinama i " << Z.dabartinis_lygis << " lygi." << endl;
            cout << "Norint testi, spauskite ENTER..." << endl;
            _getch();
        }
        else
        {
            zaidimas_pereitas(Lygis, Z);
        }
    }
}

void Priesasin(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z, int pasirinkimas)
{
    cout << "Regione susidurete su priesais." << endl;
    int prieso_hp;
    srand(time(NULL));
    prieso_hp = rand() % (Lygis[Z.dabartinis_lygis - 1].Priesas.health_max - Lygis[Z.dabartinis_lygis - 1].Priesas.health_min + 1) + Lygis[Z.dabartinis_lygis - 1].Priesas.health_min;
    // Kova su priesu sausumoje
    while (Z.inv.Kompanijonai > 0 && prieso_hp > 0)
    {
        if (Z.inv.Soviniai > 0)
        {
            prieso_hp -= Z.inv.ginklas;
            Z.inv.Soviniai--;
        }

        if (prieso_hp > 0)
        {
            Z.inv.Kompanijonai -= Lygis[Z.dabartinis_lygis - 1].Priesas.lygis;
        }
    }
    // Jei Priesas iveikiamas
    if (prieso_hp < 1)
    {
        Z.iveikti_priesai++;
        cout << "Priesas nugaletas." << endl;
    }
    // Jei pralaimima (zaidejo Kompanijonai zuna)
    else
    {
        zaidimas_pralaimetas(Lygis, Z);
    }
}

void Keliauti_i_Stovykla
(struct Zaidimo_lvl Lygis[], struct Zaidejas& Z)
{
    system("CLS");
    string pasirinkimas;
    if (Z.inv.Maistas > 0)
    {
        Z.inv.Maistas--;
    }
    else if (Z.inv.Kompanijonai > 0)
    {
        Z.inv.Kompanijonai--;
    }
    else
    {
        zaidimas_pralaimetas(Lygis, Z);
    }
    while (1)
    {
        system("CLS");
        cout << "-----------[ " << Z.dabartinis_lygis << " Lygis ]-----------" << endl;
        cout << "----------PARDUOTUVE----------" << endl;
        cout << "------------------------------" << endl;
        cout << "[1] Pirkti Maista" << endl;
        cout << "[2] Pirkti Sarvu patvaruma" << endl;
        cout << "[3] Pirkti Saovinius" << endl;
        cout << "[4] Pirkti Sarvus" << endl;
        cout << "[5] Pirkti Ginkla" << endl;
        cout << "[6] Samdyti Kompanijonus" << endl;
        cout << "[7] Iseiti is parduotuves" << endl;
        cout << "---------------------------------" << endl;
        cout << "Regionai: " << Lygis[Z.dabartinis_lygis - 1].Regionu_kiekis << endl;
        cout << "Terai: " << Lygis[Z.dabartinis_lygis - 1].Teru_kiekis << endl;
        cout << "---------------------------------" << endl;
        cout << "|           Inventorius         |" << endl;
        cout << "---------------------------------" << endl;
        cout << "|    Sarvai     |    Ginklas    |" << endl;
        cout << "| LVL " << Z.inv.Sarvai << "   DMG " << Z.inv.Sarvai << " | LVL " << Z.inv.ginklas << "   DMG " << Z.inv.ginklas << " |" << endl;
        cout << "---------------------------------" << endl;
        cout << "| Kompanijonai: " << Z.inv.Kompanijonai << endl;
        cout << "| Auksas: " << Z.inv.Auksas << endl;
        cout << "| Maistas: " << Z.inv.Maistas << endl;
        cout << "| Patvarumas: " << Z.inv.Sarvu_patvarumas << endl;
        cout << "| Soviniai: " << Z.inv.Soviniai << endl;
        cout << "---------------------------------" << endl;
        cout << endl;
        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;
        if (pasirinkimas == "1")
        {
            resursu_pirkimas(Z.inv.Auksas, Z.inv.Maistas, "Maisto", "Maisto", "Maistas", P.Maistas);
        }
        else if (pasirinkimas == "2")
        {
            resursu_pirkimas(Z.inv.Auksas, Z.inv.Sarvu_patvarumas, "Patvarumo", "Patvarumo", "Patvarumas", P.Sarvu_patvarumas);
        }
        else if (pasirinkimas == "3")
        {
            resursu_pirkimas(Z.inv.Auksas, Z.inv.Soviniai, "Soviniai", "Soviniu", "Soviniai", P.Soviniai);
        }
        else if (pasirinkimas == "4")
        {
            Sarvu_ginklo_pirkimas(Z.inv.Auksas, Z.inv.Sarvai, "Sarvai", "Sarvu", "Sarvai", P.Sarvai, P.Sarvu_kainos);
        }
        else if (pasirinkimas == "5")
        {
            Sarvu_ginklo_pirkimas(Z.inv.Auksas, Z.inv.ginklas, "Ginklai", "Ginkla", "Ginklas", P.Ginklai, P.Ginklu_kainos);
        }
        else if (pasirinkimas == "6")
        {
            resursu_pirkimas(Z.inv.Auksas, Z.inv.Kompanijonai, "Vieno zmogaus", "Zmoniu", "Kopanijonai", P.Kompanijonai);
        }
        else if (pasirinkimas == "7")
        {
            break;
        }
        else
        {
            system("CLS");
        }
    }
}

void resursu_pirkimas(int& Auksas, int& resursas, string pav1, string pav2, string pav3, int kaina)
{
    string pasirinkimas;
    int kiekis = 0;
    while (1)
    {
        system("CLS");
        cout << "----------PARDUOTUVE----------" << endl;
        cout << "------------------------------" << endl;
        cout << "Auksas: " << Auksas << endl;
        cout << pav3 << ": " << resursas << endl;
        cout << "------------------------------" << endl;
        cout << pav1 << " kaina: " << kaina << endl;
        cout << "[1] Ivesti kieki" << endl;
        cout << "[2] Grizti atgal i parduotuves meniu" << endl;
        cout << endl;
        cout << "pasirinkimas: ";
        cin >> pasirinkimas;
        if (pasirinkimas == "1")
        {
            system("CLS");
            cout << "----------PARDUOTUVE----------" << endl;
            cout << "------------------------------" << endl;
            cout << "Auksas: " << Auksas << endl;
            cout << pav3 << ": " << resursas << endl;
            cout << "------------------------------" << endl;
            cout << pav1 << " kaina: " << kaina << endl;
            cout << endl;
            cout << "Iveskite kieki: ";
            cin >> kiekis;
            if (kiekis * kaina > Auksas)
            {
                kiekis = 0;
                cout << endl;
                cout << "Nepakanka aukso." << endl;
                cout << "Norint testi, spauskite ENTER..." << endl;
                _getch();
            }
            else
            {
                Auksas -= kiekis * kaina;
                resursas += kiekis;
                cout << endl;
                cout << "Sekmingai nusipirkote " << pav2 << "." << endl;
                cout << "Norint testi, spauskite ENTER..." << endl;
                _getch();
                break;
            }
        }
        if (pasirinkimas == "2")
        {
            break;
        }
    }
}

void Sarvu_ginklo_pirkimas(int& Auksas, int& resursas, string pav1, string pav2, string pav3, int pirkinys[], int kaina[])
{
    int pasirinkimas;
    while (1)
    {
        system("CLS");
        cout << "----------PARDUOTUVE----------" << endl;
        cout << "------------------------------" << endl;
        cout << "Auksas: " << Auksas << endl;
        cout << pav3 << ": LVL " << resursas << "   DMG " << resursas << endl;
        cout << "------------------------------" << endl;
        cout << "***" << pav1 << "***" << endl;
        cout << "   LVL/DMG | Kaina" << endl;
        for (int i = 0; i < lygiu_kiekis; i++)
        {
            cout << "[" << i + 1 << "]   " << pirkinys[i] << "     " << kaina[i] << endl;
        }
        cout << "------------------------------" << endl;
        cout << "(Pasirinkite 0, kad atsaukti pirkima)" << endl;
        cout << "Pasirinkite " << pav2 << "." << endl;
        cout << endl;
        cout << "pasirinkimas: ";
        cin >> pasirinkimas;
        if (pasirinkimas == 0)
        {
            break;
        }
        if (pasirinkimas > 0 && pasirinkimas <= lygiu_kiekis)
        {
            if (kaina[pasirinkimas - 1] > Auksas)
            {
                pasirinkimas = 0;
                cout << endl;
                cout << "Nepakanka aukso." << endl;
                cout << "Norint testi, spauskite ENTER..." << endl;
                _getch();
            }
            else
            {
                Auksas -= kaina[pasirinkimas - 1];
                resursas = pirkinys[pasirinkimas - 1];
                cout << endl;
                cout << "Sekmingai nusipirkote " << pav2 << "." << endl;
                cout << "Norint testi, spauskite ENTER..." << endl;
                _getch();
                break;
            }
        }
    }
}

void issaugoti_zaidima(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    finish = clock();
    Z.laikas += (double)(finish - start) / CLOCKS_PER_SEC;
    ofstream file;
    file.open("save.txt", ios::trunc);
    file << Z.Vardas << endl;
    file << SUNKUMAS << endl;
    file << Z.dabartinis_lygis << endl;
    file << Z.laikas << endl;
    file << Z.ejimai << endl;
    file << Z.Teru_liko << endl;
    for (int i = Z.dabartinis_lygis - 1; i < lygiu_kiekis; i++)
    {
        file << Lygis[i].Regionu_kiekis << endl;
        file << Lygis[i].Teru_kiekis << endl;
        file << Lygis[i].Auksas_min << endl;
        file << Lygis[i].Auksas_max << endl;
        file << Lygis[i].Priesas.lygis << endl;
        file << Lygis[i].Priesas.health_min << endl;
        file << Lygis[i].Priesas.health_max << endl;
        file << Lygis[i].Priesas.chance << endl;
        file << Lygis[i].Priesas.lygis << endl;
        file << Lygis[i].Priesas.health_min << endl;
        file << Lygis[i].Priesas.health_max << endl;
        file << Lygis[i].Priesas.chance << endl;
        for (int j = 0; j < Lygis[i].Regionu_kiekis; j++)
        {
            file << Lygis[i].regionas[j].Buvo << " " << Lygis[i].regionas[j].Terai << endl;
        }
        file << Lygis[i].Stovykla << endl;
    }
    file << Z.inv.Kompanijonai << endl;
    file << Z.inv.Maistas << endl;
    file << Z.inv.Auksas << endl;
    file << Z.inv.Sarvai << endl;
    file << Z.inv.Sarvu_patvarumas << endl;
    file << Z.inv.ginklas << endl;
    file << Z.inv.Soviniai << endl;
    file << Z.rastas_Auksas << endl;
    file << Z.iveikti_priesai << endl;
    file << Z.Teru_liko << endl;

    file << P.Maistas << endl;
    file << P.Sarvu_patvarumas << endl;
    file << P.Soviniai << endl;
    file << P.Kompanijonai << endl;
    for (int i = 0; i < lygiu_kiekis; i++)
    {
        file << P.Sarvai[i] << endl;
        file << P.Sarvu_kainos[i] << endl;
        file << P.Ginklai[i] << endl;
        file << P.Ginklu_kainos[i] << endl;
    }
    file.close();
}

void zaidimas_pralaimetas(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    ofstream file;
    file.open("save.txt", ios::trunc);
    file.close();
    if (Z.inv.Kompanijonai == 0) {
        cout << "Jusu visi Kompanijonai buvo nugaleti, zaidimas pralaimetas." << endl;
        cout << "Norint testi, spauskite ENTER..." << endl;
    }
    else
        cout << "Jusu sarvai buvo sulauzyti, zaidimas pralaimetas." << endl;
    cout << "Norint testi, spauskite ENTER..." << endl;
    _getch();
    pagrindinis_meniu(Lygis, Z);
}

void zaidimas_pereitas(struct Zaidimo_lvl Lygis[], struct Zaidejas Z)
{
    finish = clock();
    Z.laikas += (double)(finish - start) / CLOCKS_PER_SEC;
    system("CLS");
    ofstream file;
    file.open("save.txt", ios::trunc);
    file.close();
    cout << "*********************************" << endl;
    cout << "* Sveikiname, zaidimas pereitas, jus igelbejote pasauli nuo prazuties *" << endl;
    cout << "*********************************" << endl;
    cout << "Norint testi, spauskite ENTER..." << endl;
    _getch();
    // issaugoti_top(Z);
    pagrindinis_meniu(Lygis, Z);
}


void taisykles()
{
    system("CLS");
    cout << "*************PIRATU LOBIS************" << endl;
    cout << "----------ZAIDIMO TAISYKLES----------" << endl;
    cout << endl;
    cout << "-----ZAIDIMO ESME IR TIKSLAS-----" << endl;
    cout << "Zaidejas zaidzia uz pagrindini veikeja bandanti sustapdyti apokalipse." << endl;
    cout << "Yra 3 lygiai." << endl;
    cout << "Zaidejas privalo kiekviename lygyje rasti visus Terus,"
        "kuriuos surinkus bus galima uzdaryti pandoros skrynia ir sustabdyti apokalipse." << endl;
    cout << "Kiekviename lygyje yra tam tikras skaicius regionu, kuriuos zaidejas turi aplankyti." << endl;
    cout << "Kai kuriuose regionuose galima rast Teru, kai kuriuose ten ju nera." << endl;
    cout << "Uz rastus Terus taip pat gaunamas tam tikra kiekis aukso." << endl;
    cout << "Kiekviename lygyje yra Stovykla, kurioje uz auksa galima pirkti resursus ar geresnius sarvus/ginkla." << endl;
    cout << endl;
    cout << "-----Resursai-----" << endl;
    cout << "Kompanijonai" << endl;
    cout << "Auksas" << endl;
    cout << "Maistas" << endl;
    cout << "Sarvu_patvarumas" << endl;
    cout << "Soviniai" << endl;
    cout << "Sarvai" << endl;
    cout << "Ginklas" << endl;
    cout << "Kelione i regiona ar i stovykla kainuoja 1 maisto resursa." << endl;
    cout << "Neturint maisto, uz kelione prarandama po viena kompanijona." << endl;
    cout << endl;
    cout << "Keliaujant i regiona, yra galimybe pakeliui sutikti priesu." << endl;
    cout << " sutikti priesai iveikiami naudojant sviedinius." << endl;
    cout << " sutiktiems piratams daroma zala atitinka zaidejo laivo lygi." << endl;
    cout << " sutiktu piratu daroma zala taip pat atitinka ju lygi." << endl;
    cout << endl;
    cout << "Atvykus i regiona, kuriame yra Terai, yra taip pat galimybe sutikti priesus." << endl;
    cout << "Regione sutikti suteikti priesai iveikiami naudojant sovinius." << endl;
    cout << "Regione sutiktiems priesams daroma zala atitinka zaidejo ginklo lygi." << endl;
    cout << "Regione sutiktu priesu daroma zala taip pat atitinka ju lygi." << endl;
    cout << endl;
    cout << "Radus visus Terus kiekviename lygyje, zaidimas pereinamas." << endl;
    cout << "Praradus visus kompanijonus, zaidimas pralaimimas." << endl;
    cout << "-------------------------------------" << endl;
    cout << "Norint testi, spauskite ENTER..." << endl;
    _getch();
}
