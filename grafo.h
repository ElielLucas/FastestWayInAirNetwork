#ifndef GRAFO_H
#define GRAFO_H
#include<vector>
#include <algorithm>
#include<queue>
#include"voo.h"
using namespace std;

const float INF = 1000000009;
typedef pair<float, int> ii;
typedef pair<int, float> obj;
typedef vector<obj> Vec;
class Grafo
{
    int N;
    Vec* V;

public:
    Grafo(){};
    ~Grafo();

    void setG(int N);
    void insereAresta(int u, int v, float w);
    void excluiAresta(int u, int v);
    bool temAresta(int u, int v);

    void dijkstra(int s, float* d, int* p);

    int grau(int u);
    int popular();
};
Grafo::~Grafo()
{
    delete[]V;
}
void Grafo::setG(int N)
{
    this->N=N;
    V=new Vec[N];
}
void Grafo::insereAresta(int u, int v, float w)
{
    bool ok = true;
    for (int i = 0; i < (int)V[u].size(); i++)
    {
        if (V[u][i].first == v)
            ok = false;
    }
    if (ok)V[u].push_back({v, w});
}
void Grafo::excluiAresta(int u, int v)
{
    Vec aux;
    for (int i = 0; i < (int)V[u].size(); i++)
    {
        if (V[u][i].first != v)
            aux.push_back(V[u][i]);
    }
    V[u].clear();
    V[u] = aux;
}
bool Grafo::temAresta(int u, int v)
{
    for (int i = 0; i < (int)V[u].size(); i++)
    {
        if (V[u][i].first == v)
            return true;
    }
    return false;
}
int Grafo::grau(int u)
{
    return V[u].size();
}

void Grafo::dijkstra(int s, float* d, int* p)
{
    priority_queue <ii,
        vector<ii>, greater<ii>>Q;

    //initialize_single_source
    for (int i = 0; i < N; i++)
    {
        d[i] = INF;
        p[i] = -1;
    }
    d[s] = 0;

    Q.push({ d[s], s });
    while (!Q.empty())
    {
        int u = Q.top().second;
        Q.pop();
        for (int IT = 0; IT < (int)V[u].size(); IT++)
        {
            int v = V[u][IT].first;
            float w = V[u][IT].second;

            if (d[v] > d[u] + w) //relaxamento
            {
                d[v] = d[u] + w;
                p[v]=u;
                Q.push({ d[v],v });
            }
        }
    }   
}


#endif // GRAFOL_H
