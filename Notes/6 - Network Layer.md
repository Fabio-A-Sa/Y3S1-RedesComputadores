# 6 - Network Layer

A camada de rede (a terceira camada) tem como funções principais:

- **transportar pacotes** desde a origem até ao destino;
- **cálculo dos caminhos** através de grafos, para mandar os pacotes a passar pelo mínimo número de componentes da rede possível;

## Virtual Circuits and Datagram Networks

### VC - Virtual Circuits

Criação do circuito virtual entre o primeiro router e o último router para transferência de dados. Para isso há estabelecimento de um conjunto de identificadores virtuais, presentes numa tabela. Só depois do caminho estabelecido é que há transferência contínua e sequencial de todos os pacotes e durante isso não há utilização do mesmo circuito por parte de outros pacotes. É, por isso, mais fácil de gerir.

### Datagrams Networks

Não é necessário estabelecer o caminho antes da transferência. Cada um dos pacotes vai ser encaminhado independentemente, possivelmente fora de ordem. Não há garantias da qualidade de serviço ou do controlo de congestionamento. 

## Internet Protocol (IP)

Na Network Layer temos três tipos de protocolos:

- IP Protocol, que garante as convenções de endereçamento, o formato das tramas e a recepção dos pacotes;
- ICMP protocol, que garante o report dos erros;
- Routing protocol, que garante a escolha do melhor caminho para enviar a informação entre os routers (RIP, OSPF, BGP);

### IP Datagram Format

Na trama de dados é indicada:
- a versão do protocolo;
- o tamanho do header;
- o tamanho da zona dos dados;
- tempo de vida, ou seja, o número máximo de routers a visitar. Isto permite descartar pacotes que estejam em ciclos infinitos na rede;
- checksum do header;
- endereço IP da origem e do destino, ambos com 32 bits;

### Fragmentação e Reassemblagem

Nas redes podem existir links que tenham MTU (maximum transfer size), o que impossibilita o envio de pacotes que excedam esse tamanho. Assim, é necessário fazer `fragmentação` do pacote em subpacotes. No destino, existe a `reassemblagem`, que constroi o pacote original.

Na fragmentação, todos os subpacotes excepto o último contêm uma flag de fragmento = 1. Têm também um offset, que é igual ao número de bytes de informação que ainda restam (número de bits / 8).

### Endereços IP

São endereços de 32, representados com 4 números em decimal (exemplo: 127.0.0.1). Cada mecanismo da rede tem o seu endereço IP único.

#### CIDR - Classless InterDomain Routing

Cada subrede tem o endereço de rede (os três primeiros números decimais, os 24 bits mais significativos) iguais. Assim, os 8 bits menos significativos são diferentes para cada computador. Computadores que estão na mesma subrede podem comunicar entre si sem necessário ter a interferência de um router a encaminhar os pacotes. 

127.34.19.0/23, significa que o IP da subrede é definido pelos 23 bits mais significativos. 

#### Endereços IP especiais

0.0.0.0 - o host
0.0.0.X - outro host
1..1 - para enviar o pacote a todos os membros da rede local (broadcast)
network.1..1 - para enviar o pacote a todos os membros da rede distante
127.X.X.X - para um computador enviar pacotes para ele mesmo