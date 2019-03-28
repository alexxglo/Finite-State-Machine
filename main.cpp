#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream f("nods.txt");

struct automat
{
    int drumuri_posibile[100];
    char alfabet[100][100];
    int vecini;
    int nr_litere_per_vecin[100];
    bool nod_terminal;
    bool nod_inceput;

} nod[100];
int parcurgere_cuvant(int x,char cuvant[20],int pozitie)
{
    int i;
    /// Verific pentru fiecare vecin de-al nodului x literele pentru a vedea daca poate fi acceptat vecinul
    char litera_cuvant;
    litera_cuvant=cuvant[pozitie]; /// gasim litera la care am ajuns
    if(pozitie==0&&strcmp(cuvant,"l4")==0&&nod[x].nod_terminal==1)return 1; /// daca cuvantul este lambda si nodul este terminal => cuvant acceptat
    if(pozitie==strlen(cuvant)&&nod[x].nod_terminal==1)return 1; /// daca pozitia = lungimea cuv inseamna ca nu mai avem litere si daca avem nod terminal =>  cuvant acceptat
    for(i=0; i<nod[x].vecini; i++) /// verific fiecare vecin pentru eventuale posibilitati de gasire a literelor
    {
        for(int j=0; j<nod[x].nr_litere_per_vecin[i]; j++)      /// verific fiecare litera acceptata de muchia vecinului
            if(nod[x].alfabet[i][j]==litera_cuvant)            /// daca se gaseste muchie cu litera cautata, se reapeleaza functia
                if(parcurgere_cuvant(nod[x].drumuri_posibile[i],cuvant,pozitie+1)==1)return 1;    /// la reapelare, schimb nodul in vecinul gasit si cresc pozitia cu 1
    }
    return 0;
}
/// DATE DE INTRARE:
/// NUMAR NODURI
/// FIECARE NOD ESTE CONTINE URMATOARELE:
/// 1. NUMAR VECINI
/// 2. NR. LITERE CARE SUNT ADMISE + LITERELE ADMISE
/// 3. STARE NOD / DACA E DE INCEPUT SAU NU
/// 4. STARE NOD TERMINAL/NETERMINAL
/// 5. CUVANTUL DE VERIFICAT

int main()
{
    int numar_noduri=0,i=0,x=0,j=0,k=0,vecin=0,q=0,nr_litere_admise=0;
    char cuvant[20]; /// cuvantul testat de AFN
    char litera;
    char stringg[20];
    char verif[20]="nod_incepere"; /// verif si veriff determina starea terminala/neterminala si starea de incepere a nodurilor
    char veriff[20]="nod_terminal";
    f>>numar_noduri;
    cout<<"Numarul de noduri este: ";
    cout<<numar_noduri; /// citesc nr total de noduri
    cout<<endl<<endl;
    for(i=0; i<numar_noduri; i++)
    {
        cout<<"Nodul curent este: "<<i<<endl;

        f >> x;
        cout<<"Numarul total de vecini al nodului "<<i<<" este: "<<x;
        cout<<endl;
        cout<<"Vecinii nodului "<<i<<" sunt: ";
        nod[i].vecini = x; /// x= nr de vecini ai nodului
        for (j = 0; j < nod[i].vecini; j++)
        {
            f >> vecin;  /// citesc fiecare vecin
            cout<<vecin<<" ";
            nod[i].drumuri_posibile[j] = vecin; ///retin vecinul ca un drum posibil
            f >> nr_litere_admise; /// citesc nr de litere permise ale muchiei dintre nodul curent si vecin
            nod[i].nr_litere_per_vecin[j]=nr_litere_admise;
            for (q = 0; q <nod[i].nr_litere_per_vecin[j]; q++)   /// i = parcurgere noduri j= parcurgere vecini q= parcurgere litere admise ale unui vecin
            {
                f >> litera;
                nod[i].alfabet[j][q] = litera; /// citesc litera si o adaug in alfabetul relatiei nod-vecin
            }
        }
        cout<<endl;
        f >> stringg;
        if (strcmp(stringg, verif) == 0)
        {
            nod[i].nod_inceput = 1;
            cout<<"Starea nodului este: nod de inceput "<<endl;        /// verific daca nodurile sunt de inceput sau terminale/neterminale
        }
        else
        {
            nod[i].nod_inceput = 0;
            cout<<"Starea nodului este: nod normal "<<endl;
        }
        f >> stringg;
        if (strcmp(stringg, veriff) == 0)
        {
            nod[i].nod_terminal = 1;
            cout<<"Starea nodului este: nod terminal "<<endl;
        }
        else
        {
            nod[i].nod_terminal = 0;
            cout<<"Starea nodului este: nod neterminal "<<endl;
        }
        cout<<endl;
    } /// constructia nodurilor
    cout<<"Cuvantul este: ";
    f>>cuvant;
    if(strcmp(cuvant,"l4")==0)cout<<"lambda"; /// cuvantul l4 in fisier text este reprezentativ pentru lambda
    else cout<<cuvant;
    for(i=0; i<numar_noduri; i++)if(nod[i].nod_inceput==1)x=i;  /// caut nodul de inceput pentru a apela functia mea recursiva din acel punct
    int raspuns=0;
    cout<<endl<<endl;
    raspuns=parcurgere_cuvant(x,cuvant,0); /// apelez nodul, cuvantul intreg si pozitia literei pe care o verific(initial, desigur, 0)
    if(raspuns==1)cout<<"Cuvant acceptat"<<endl;
    else cout<<"Cuvantul nu este acceptat"<<endl;
    return 0;
}








/*
exemplul1
5
3
1 5 a b c d e
2 2 a b
3 1 c
nod_incepere
nod_netermin
2
0 3 a b c
3 2 b c
nod_neincepr
nod terminal
4
0 2 a d
1 1 b
3 4 c d e f
4 2 d f
nod_neincepr
nod terminal
1
2 1 a
nod_neincepr
nod_netermin
3
0 2 a b
1 3 b d f
2 2 c e
nod_neincepr
nod_terminal

abc
*/


/*
exemplul2
3
1
1 2 a c
nod_incepere
nod_netermin
2
0 2 a b
2 2 b d
nod_neincepr
nod_netermin
0
nod_neincepr
nod_terminal
abcd







exemplul3

5
3
1 5 a b c d e
2 2 a b
3 1 c
nod_incepere
nod_netermin
2
0 3 a b c
3 2 b c
nod_neincepr
nod_terminal
4
0 2 a d
1 1 a
3 4 c d e f
4 2 d f
nod_neincepr
nod_terminal
1
2 1 a
nod_neincepr
nod_netermin
3
0 2 a b
1 3 b d f
2 2 c e
nod_neincepr
nod_terminal

aa





exemplul1 drive


4
2
0 1 b
1 1 a
nod_incepere
nod_netermin
2
1 1 a
2 1 b
nod_neincepr
nod_netermin
2
0 1 b
3 1 a
nod_neincepr
nod_netermin
1
3 2 a b
nod_neincepr
nod_terminal
bbbabb



exemplul2 drive

3
2
0 1 b
1 1 a
nod_incepere
nod_terminal
2
0 1 b
2 1 a
nod_neincepr
nod_terminal
1
2 2 a b
nod_neincepr
nod_netermin
bbababbba



*/
