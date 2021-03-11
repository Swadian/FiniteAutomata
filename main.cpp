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
public:
    void setNum(int nr){this->num=nr;}
    int getNum(){return this->num;}
    state()
    {
        this->arce=new transition[n];
        this->trNumber=0;
    };
~state(){if(this->arce!=NULL)delete[] this->arce;}
void add_arc(transition t){this->arce[trNumber++]=t;}
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
    int k;
    for(int i=0;i<n;i++)
    {
        fin>>k;
        stari[i].setNum(k);
    }
    int m;
    fin>>m;
    int x,y;char l;
    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>l;
        for(int i=0;i<n;i++)
            {
                transition t(l,y);
                if(stari[i].getNum()==x)
                    stari[i].add_arc(t);
            }
    }
    return 0;
}
