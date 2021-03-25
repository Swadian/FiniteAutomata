#include <fstream>

using namespace std;
class state;
    int n;

class transition
{
    char c;
    int to;
    public:
        int getTo(){return this->to;}
        char getChr(){return this->c;}
    transition(char c, int to) {this->c=c;this->to=to;}
    transition(){};
};
class state{
int num;
int trNumber;
transition *arce;
bool finala;
public:
    bool getFinality(){return this->finala;}
    void setNum(int nr){this->num=nr;}
    int getNum(){return this->num;}
    state()
    {
        this->arce=new transition[n];
        this->trNumber=0;
        this->finala=false;
    };
~state(){if(this->arce!=NULL)delete[] this->arce;}
void add_arc(transition t){this->arce[trNumber++]=t;}
void setFinality(bool f){this->finala=f;}
int moveto(char c)
{
    for(int i=0;i<trNumber;i++)
        if (arce[i].getChr()==c)
            return arce[i].getTo();
    return -1;
};

};

int main()
{
    ifstream fin("date.in");
    ofstream fout("rez.txt");
    fin>>n;
    state *stari= new state[n];
    int kk;
    for(int i=0;i<n;i++)
    {
        fin>>kk;
        stari[i].setNum(kk);
    }
    //adaugarea numerelor starilor
    int m;
    fin>>m;
    int x,y;char l;
    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>l;
        transition t(l,y);
        for(int i=0;i<n;i++)
            {
                if(stari[i].getNum()==x)
                    {stari[i].add_arc(t);i=n+1;}
            }
    }
    //adaugarea arcelor fiecarei stari
    int s;
    fin>>s;//starea initiala
    int ss=s;//backup pt starea initiala
    int nrF;
    fin>>nrF;//numarul de stari finale
    int st;
    for(int i=0;i<nrF;i++)
    {
        fin>>st;
        for(int i=0;i<n;i++)
            if(stari[i].getNum()==st)
                stari[i].setFinality(true);
    }
    //seteaza finalitatea starilor
    int nrCuv;
    fin>>nrCuv;
    string cuv;
    bool done;
    for(int i=0;i<nrCuv;i++)//procesarea pe toate cuvintele
    {
        s=ss;//restore initial state
        fin>>cuv;
        done=false;
        while(!done)//procesarea pe cuvant
        {
            for(int j=0;j<int(cuv.length())&&!done;j++)//procesarea pe litere
            {
                for(int k=0;k<n;k++)//cautarea starii in lista
                    if(stari[k].getNum()==s)//gasesti starea
                {
                    s=stari[k].moveto(cuv[j]);
                    if(s==-1)//daca nu are tranzitie cu caracterul respectiv
                    {
                        fout<<"NU\n";
                        done=true;
                    }
                    break;//odata procesata starea, iesi din cautare
                }
            }
            for(int k=0;k<n;k++)//cautarea starii in care a ajuns la final
                if(stari[k].getNum()==s)
                    {
                        if(stari[k].getFinality()==true)//daca a ajuns intr-o stare finala
                        {fout<<"DA\n";done=true;}
                        break;
                    }

            if(!done)fout<<"NU\n";//daca nu a ajuns in o stare finala
            done=true;
        }
    }


    delete[] stari;
    return 0;
}
