#ifndef VERTICE_H
#define VERTICE_H
#include"voo.h"
using namespace std;

class Vertice
{
private:
    int position;
    string nome;
    Voo viajem;

public:
    Vertice();
    Vertice(int position, string nome);
    Vertice(int position, string nome, Voo viajem);

    string getNome()const      { return nome; }
    void setPosition(int num)  { position = num; }
    int getPosition()const     { return position; }
    void setViajem(Voo viajem) { this->viajem = viajem;}
    Voo getViajem()const       { return viajem; }
    string getID()const;

    void setAll(int position, string nome, Voo viajem);
    void setAll(int position, string nome);


    string printOrigem()const;
    string printDestino()const;
};
Vertice::Vertice()
{
    nome = "";
    position = 0;
}

Vertice::Vertice(int position, string nome, Voo viajem)
{
    this->position = position;
    this->nome = nome;
    this->viajem = viajem;
}
Vertice::Vertice(int position, string nome)
{
    this->position = position;
    this->nome = nome;
}

void Vertice::setAll(int position, string nome, Voo viajem)
{
    this->position = position;
    this->nome = nome;
    this->viajem = viajem;
}
void Vertice::setAll(int position, string nome)
{
    this->position = position;
    this->nome = nome;
}

string Vertice::getID()const
{
    string saida;
    saida = viajem.getCodigo() + nome + "_" + viajem.getStatus() +"_"+ to_string(position);
    return saida;
}

string Vertice::printOrigem()const
{
    string saida="";
    saida+= viajem.getCodigo() +" " + nome + " " + viajem.getHorarioSaida();
    return saida;
}
string Vertice::printDestino()const
{
    string saida="";
    saida+=" "+nome + " " +  viajem.getHorarioChegada();
    return saida;
}

#endif // VERTICE_H
