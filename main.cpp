#include <iostream>
#include"projeto.h"
#include <sstream>
using namespace std;


int main()
{
    string nomeArquivo, aeroOrigem, aeroDestino, op="S";

    printf("Informe o nome do arquivo de especificacoes dos Voos + '.txt': ");
    cin >> nomeArquivo;
    while(op=="S")
    {
        system("cls");
        printf("Nome do Aeroporto Origem: ");
        cin >> aeroOrigem;
        printf("Nome do Aeroporto Destino: ");
        cin >> aeroDestino;
        Projeto P(nomeArquivo, aeroOrigem, aeroDestino);

        string saida = P.searchRoute();
        if(saida=="")cout<<"\nNao existe voo para essa origem e destino\n\n";
        else cout<<"\n\n"<<P.searchRoute()<<"\n";

        printf("Deseja Continuar?\nEscreva 'S', caso sim: ");
        cin>>op;
    }
}
