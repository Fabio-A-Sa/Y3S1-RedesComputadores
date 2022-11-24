# 8 - Routing

As redes de computadores podem ser vistas como um grafo, onde se constroi uma árvore de caminhos mínimos (*ShortestPath Tree*) usando os algoritmos de Dijkstra ou Bellman-Ford.

A escolha de um bom caminho (boa largura de banda, curta distância, baixa latência) é importante para garantir a eficiência da rede e limitar a quantidade de pacotes perdidos no processo.

## Routing in Layer 3 Networks

Cada router conhece a rede e contém uma Fowarding Table, construída com base nos destinos dos pacotes a transferir e na sua própria Spanning Tree. Escolhe sempre o caminho mais curto, se o custo de cada ligação for o mesmo, ou o caminho com menos custo total.

### Link-State Routing

Cada um dos routers emite periodicamente uma mensagem em **broadcast** contendo a sua identificação, a identificação dos routers diretamente ligados a ele e os custos associados. Assim conseguem manter o grafo da rede e a própria Fowarding Table atualizados. 

