#ifndef VOO_H
#define VOO_H
#include<iostream>
using namespace std;
class Voo
{
    string codigo;
    string status;
    string horarioSaida;
    string horarioChegada;


public:
    Voo();
    Voo(string codigo,
            string status,string horarioSaida,string horarioChegada);

    void setAll(string codigo,
                string status,string horarioSaida,string horarioChegada);

    string getCodigo()const         { return codigo; }
    string getStatus()const         { return status; }
    void getHorarioSaida(string horarioSaida)     { this->horarioSaida = horarioSaida; }
    string getHorarioSaida()const   { return horarioSaida; }
    void getHorarioChegada(string horarioChegada) { this->horarioChegada = horarioChegada; }
    string getHorarioChegada()const { return horarioChegada; }
};

Voo::Voo()
{
    codigo = "";
    status = "";
    horarioSaida = "";
    horarioChegada = "";
}

Voo::Voo(string codigo,string status,string horarioSaida,string horarioChegada)
{
    this->codigo = codigo;
    this->status = status;
    this->horarioSaida = horarioSaida;
    this->horarioChegada = horarioChegada;
}

void Voo::setAll(string codigo,string status,string horarioSaida,string horarioChegada)
{
    this->codigo = codigo;
    this->status = status;
    this->horarioSaida = horarioSaida;
    this->horarioChegada = horarioChegada;   
}

#endif // VOO_H
