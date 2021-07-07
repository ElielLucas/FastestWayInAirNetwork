<div align="center">
  <h1>FastestWayInAirNetwork<h1>
  <h2>Caminho mais rápido em transportes aéreos</h2><br>
</div>
<p align="justify">Pretende-se desenvolver um programa para ajudar a escolher o vôo ou vôos a tomar para viajar de um aeroporto de origem para um aeroporto de destino no menor tempo possível (desde a partida no aeroporto de origem até à chegada ao aeroporto de destino), sem restrição de hora de partida ou chegada.<br>
 Os vôos oferecidos pelas companhias aéreas estão especificados num arquivo de texto (a ler pelo programa), com uma linha para cada vôo, indicando o número do vôo (sigla da companhia aérea seguido de um número atribuído pela companhia), o nome do aeroporto de origem, a hora de partida do aeroporto de origem, o nome do aeroporto de destino e a hora de chegada ao aeroporto de destino. No caso de um vôo com escalas, são indicados os aeroportos intermediários, por ordem, entre os aeroportos de origem e de destino, com a hora de chegada e a hora de partida a seguir ao nome de cada aeroporto intermediário. Os nomes de aeroportos são escritos sem espaços. Todas as horas são em tempo GMT.<p>
<h4>Exemplo de um arquivo com especificação de vôos:</h4>
TP1982 Porto 09:00 Madrid 11:00<br>
IB8717 Madrid 12:00 LasPalmasGranCanaria 15:00 15:30 SantaCruzTenerife 16:20<br>
TP1985 Porto 09:30 Lisboa 10:30<br>
PGA102 Lisboa 12:40 SantaCruzTenerife 16:00 16:30 LasPalmasGranCanaria 17:20<br><br>
    
<p align="justify">Supõe-se que todos os vôos se realizam diariamente. Supõe-se que podem entrar e sair passageiros em todos os aeroportos intermediários em que um vôo faz escala. Supõe-se que, para poder mudar de vôo num aeroporto, um passageiro precisa pelo menos de 30 minutos (entre a chegada num vôo e a partida noutro vôo).<br>
O programa deve ter como parâmetros de chamada (passados na linha de comandos) o nome do arquivo com a especificação dos vôos, o nome do aeroporto de origem e o nome do aeroporto de destino. O programa deve escrever no standard output o vôo ou vôos a tomar. No caso de vários vôos, o programa deve escrever uma linha para cada vôo. Para cada vôo a tomar, o programa deve mostrar o número do vôo, o aeroporto em que se deve tomar esse vôo, a hora de saída do vôo, o aeroporto em que se deve deixar esse vôo e a hora de chegada do vôo.</p>
<h4>Por exemplo, para os vôos acima especificados, e para viajar do Porto para SantaCruzTenerife o programa deve produzir o seguinte resultado:</h4>
TP1985 Porto 09:30 Lisboa 10:30<br>
PGA102 Lisboa 12:40 SantaCruzTenerife 16:00<br><br>
<p align="justify">Conceitualmente, este problema pode ser resolvido aplicando os algoritmos de caminhos mais curtos em grafos (nomeadamente o algoritmo de Dijkstra), sobre um grafo modificado conforme indicado na figura seguinte (relativamente aos vôos acima exemplificados).
As letras "C" e "P" referem -se a chegadas e partidas, respectivamente. As ligações entre aeroportos são marcadas com o tempo de vôo correspondente. Em cada aeroporto, todas as chegadas são ligadas a todas as partidas, com o tempo de espera correspondente. O caminho mais curto entre Porto e SCT está indicado a traço mais forte.
O programa deve ter opções (na forma de parâmetros passados na linha de comandos) para, caso o usuário pretenda, restringir as horas de saída e as horas de chegada.</p>
   
<div align="center">
  <img src="/imagens/mapaDeGrafo.png"/ weight="500" height="500">
  <img src="/imagens/organizaçãoDeVertices.png"/ weight="500" height="800">
</div>
