#ifndef PROJETO_H
#define PROJETO_H
#include<fstream>
#include<stack>
#include<sstream>
#include<string>
#include"grafo.h"
#include"vertice.h"
using namespace std;

struct Connection{
    string idOrigem;
    string idDestino;
};

class Projeto
{
    Grafo G;
    vector<Vertice> vert;
    vector<Connection> arestas;
    int posicaoOrigem;
    int posicaoDestino;

public:
    Projeto(string nomeArquivo, string AO, string AD);

    void initGraph(string nomeArquivo, string &AO, string &AD);            
    string insertVert(string name,Voo* viajem,int &numVert);
    void insertArest(string orig, string dest);

    void organizeData(vector<string>& w, int& numVert);
    void organizeEdges(string &AO, string &AD);
    string searchRoute();

    void separateWords(string x, vector<string>* w);
    float convertTemp(string saida, string chegada);    
    pair<string,string> concString(string x);
    void connectSymbolicVertices(string &AO, string &AD);
    float to_float(string t);
    int position(string v);

    string printVert();
    string printArestas();
};

Projeto::Projeto(string nomeArquivo, string AO, string AD)
{
    initGraph(nomeArquivo, AO, AD);
    G.setG(vert.size());
    organizeEdges(AO, AD);
}

void Projeto::initGraph(string nomeArquivo, string &AO, string &AD)
{
    fstream arquivo;
    int numVert = 0;

    arquivo.open(nomeArquivo.c_str(), std::ios::in);
    while (!arquivo.is_open()){
        printf("O arquivo de Voos nao foi aberto! Tente novamente\nNome do arquivo: \n");
        nomeArquivo = "";
        cin >> nomeArquivo;
        arquivo.open(nomeArquivo.c_str(), std::ios::in);
    }

    vector<string> w;
    string linha = "";
    getline(arquivo, linha);
    while (!arquivo.eof()){
        separateWords(linha, &w);   
        organizeData(w, numVert);
        getline(arquivo, linha);
    }

    //Insere os pontos, inicial e final
    Vertice org(numVert++, AO), dest(numVert++, AD);
    vert.push_back(org); vert.push_back(dest); 
    posicaoOrigem=vert.size()-2;
    posicaoDestino=vert.size()-1;
}

void  Projeto::organizeData(vector<string>& w, int& numVert)
{
    //Insere os vertices 2 primeiros vertices da linha
    string orig, dest;
    Voo viajemAux1(w[0],"P", w[2], w[4]);
    Voo viajemAux2(w[0],"C", w[2], w[4]);
    orig=insertVert(w[1],&viajemAux1, numVert);
    dest=insertVert(w[3],&viajemAux2, numVert);
    insertArest(orig, dest);

    //Insere os vertices que fazem parte de uma escala
    for (int i = 5; i < (int)w.size(); i++)
        if (w[i][0] >= 65 && w[i][0] <= 90)
        {
            viajemAux1.setAll(w[0],"P", w[i - 1], w[i+1]);
            viajemAux2.setAll(w[0],"C", w[i - 1], w[i+1]);
            orig=insertVert(w[i-3],&viajemAux1, numVert);    //aqui
            insertArest(dest, orig); //tempo de esperar na escala
            dest=insertVert(w[i],&viajemAux2, numVert);
            insertArest(orig, dest);
        }
    w.clear();
}

void Projeto::organizeEdges(string &AO, string &AD)
{
    //Arestas comuns, que conectam um aeroporto a outro
    for(int i=0; i<(int)arestas.size(); i++)
    {
        int u = position(arestas[i].idOrigem);
        int v = position(arestas[i].idDestino);

        G.insereAresta (u, v, convertTemp(vert[u].getViajem().getHorarioSaida(),vert[v].getViajem().getHorarioChegada()));
    }

    //Arestas que conectam todas chegadas a todas as partidas de um aeroporto
    for(int i=0; i<(int)vert.size()-2; i++)
    {
        for(int j=0; j<(int)vert.size()-2; j++)
        {
            if((vert[i].getNome() == vert[j].getNome()) && (vert[i].getViajem().getStatus()=="C" && vert[j].getViajem().getStatus()=="P"))
            {
                 float tempEspera=convertTemp(vert[i].getViajem().getHorarioChegada(),vert[j].getViajem().getHorarioSaida());
                 if(tempEspera < 30)
                    tempEspera += 1440; //soma 24 hrs

                 G.insereAresta (vert[i].getPosition(), vert[j].getPosition(), tempEspera);
            }
        }
    }

    //Arestas que conectam os vertices "simbólicos" de origem e destino
    connectSymbolicVertices(AO,AD);
}

void Projeto::connectSymbolicVertices(string &AO, string &AD)
{
    for(int i=0; i<(int)vert.size()-2; i++)
    {
        if(vert[i].getNome()==AO && vert[i].getViajem().getStatus()=="P")
            G.insereAresta (vert[posicaoOrigem].getPosition(), vert[i].getPosition(), 0);
        else if(vert[i].getNome()==AD && vert[i].getViajem().getStatus()=="C")
            G.insereAresta (vert[i].getPosition(), vert[posicaoDestino].getPosition(), 0);
    }
}

string Projeto::searchRoute()
{
    float dist[vert.size()];
    int pai[vert.size()];
    G.dijkstra(posicaoOrigem,dist, pai);

    stack<Vertice> route;
    string saida="";

    for(int i=posicaoDestino; i!=-1; i=pai[i])
        route.push(vert[i]);
    route.pop();

    while(route.size()>1)
    {
        if(route.top().getViajem().getStatus()=="P")
            saida+=route.top().printOrigem();
        else  saida+=route.top().printDestino()+"\n";
        route.pop();
    }

    return saida;
}

string Projeto::insertVert(string name,Voo* viajem, int &numVert)
{
    Vertice x;
    x.setAll(numVert,name, *viajem);

    numVert++;
    vert.push_back(x);
    return vert[vert.size()-1].getID();
}
void Projeto::insertArest(string orig, string dest)
{
    Connection c;
    c.idOrigem = orig;
    c.idDestino = dest;
    arestas.push_back(c);
}

void Projeto::separateWords(string x, vector<string>* w)
{
    if (x == "")return;
    string aux = "";
    int i;
    for (i = 0; i < (int)x.size() && x[i] != ' '; aux += x[i], i++);
    i++;

    w->push_back(aux);

    aux = "";
    for (; i < (int)x.size(); i++)
        aux += x[i];
    separateWords(aux, w);
}

float Projeto::convertTemp(string saida, string chegada)
{
    float tempIni, tempFin;
    string sH, sM, cH, cM;
    pair<string,string> aux;

    //separa o horário em duas strings, 'horas' e 'minutos'
    aux= concString(saida);
    sH = aux.first;
    sM = aux.second;
    tempIni=(to_float(sH)*60) + to_float(sM);  //converte horas para minutos e soma com os minutos restantes

    aux= concString(chegada);
    cH = aux.first;
    cM = aux.second;
    tempFin=(to_float(cH)*60) + to_float(cM);

    return (tempFin - tempIni);
}
pair<string,string> Projeto::concString(string x)
{
    pair<string,string> saida;

    //concatena a primeira parte do horário (horas)
    saida.first=x[0];
    saida.first+=x[1];

    //concatena a primeira parte do horário (minutos)
    saida.second=x[3];
    saida.second+=x[4];

    return saida;
}

int Projeto::position(string v)
{
    int i = 0;
    for (; i < (int)vert.size() && vert[i].getID()!= v; i++);
    if(i< (int)vert.size()) return vert[i].getPosition();
    return -1;
}

string Projeto::printVert()
{
    string saida = "";
    for (int i = 0; i < (int)vert.size(); i++)
        saida += to_string(vert[i].getPosition()) + " " + vert[i].getNome()+"   ";

    return saida;
}

float Projeto::to_float(string str)
{
   std::istringstream is(str);
   float result;
   result = ::strtod(str.c_str(), 0);
   is >> result;
   return result;
}

#endif // PROJETO_H
