# 8 - Routing

As redes de computadores podem ser vistas como um grafo, onde se constroi uma árvore de caminhos mínimos (*ShortestPath Tree*) usando os algoritmos de Dijkstra ou Bellman-Ford.

A escolha de um bom caminho (boa largura de banda, curta distância, baixa latência) é importante para garantir a eficiência da rede e limitar a quantidade de pacotes perdidos no processo.

## Routing in Layer 3 Networks

Cada router conhece a rede e contém uma Fowarding Table, construída com base nos destinos dos pacotes a transferir e na sua própria Spanning Tree. Escolhe sempre o caminho mais curto, se o custo de cada ligação for o mesmo, ou o caminho com menos custo total.

### Link-State Routing

#### Forma 1

Cada um dos routers emite periodicamente (tipicamente de meia em meia hora) uma mensagem em **broadcast** contendo a sua identificação, a identificação dos routers diretamente ligados e os custos associados. Assim conseguem manter o grafo da rede e a própria Fowarding Table atualizados. A mensagem pode ser imediatamente lançada quando algum router detecta uma nova ligação ou perda (através de mensagens *"hello"*). Por um lado as informações trocadas são mais localizadas e menores, mas por outro qualquer modificação na rede distante acaba por demorar muito tempo a chegar a todos os routers.

#### Forma 2

Através do Algoritmo de `Bellman-Ford` as mensagens são enriquecidas com o conhecimento cada vez mais vasto da rede: dos vizinhos, dos vizinhos dos vizinhos... através da troca das Fowarding Tables correspondentes. Aqui as mensagens são mais longas, pois acabam por conter a informação das tabelas todas, mas por outro lado as modificações são rapidamente transportadas para todos os routers.

### Routing Information Protocol (RIP)

É o protocolo que gere a distância entre routers. Os routers enviam a sua distância aos outros de 30 em 30 segundos ou quando um update causa uma modificação na rede em si.

## Routing in Layer 2 Networks

### Spanning Tree Protocol (STP)

Protocolo existente nas bridges presentes nos switches da rede. Aqui os routers não constroem as suas próprias Spanning Tree, existindo apenas uma árvore no sistema que é construída por mensagens trocadas entre switches. As mensagens são do tipo (Y, d, X):

> M (Y, d, X)
> Y <- Root da árvore atual
> d <- Distância de ligação
> X <- Origem

Inicialmente todos os switches assumem que eles próprios são a raiz da árvore. À medida que as mensagens são trocadas, os switches admitem sempre que a raiz da árvore é agora o switch que contém o menor número identificador. Os switches bloqueiam algumas portas para que não existam ciclos.

