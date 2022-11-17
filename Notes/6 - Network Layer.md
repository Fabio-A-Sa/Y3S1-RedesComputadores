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

### Subnetting

Há possibilidade de definir uma subrede dentro de uma rede. Para isso utiliza-se uma máscara de X bits. Exemplo: subnetid de 3 bits e hostid de 5 bits numa rede 192.228.17.0/24. 

#### Endereços IP especiais

0.0.0.0 - o computador está a enviar o pacote para ele mesmo
0.0.0.X - o computador está a enviar o pacote para um computador X na mesma rede
255.255.255.255 - para enviar o pacote a todos os membros da rede local (broadcast)
network.255.255.255 - para enviar o pacote a todos os membros da rede destino
127.X.X.X - para um computador enviar pacotes para ele mesmo, loopback

##### Nota

Apesar de existirem X bits disponíveis para endereçar, há apenas 2^X-2 endereços disponíveis (não considerar tudo 0, subnet, ou tudo 1, broadcast).

### Encaminhamento de pacotes

Quando o router recebe um pacote na porta de entrada, consulta uma tabela "Forwarding table": cada destino está associado à interface/porta correspondente do router mais próximo na rede. 

Uma tabela que tenha o prefixo da network (123.234.122.201), a máscara (/24), o gateway (123.123.125.123) e a interface (ethX), então:
- Se o resultado da máscara & prefixo da network for igual, adicionar ao conjunto;
- Escolher do conjunto o que contém a maior máscara, ou seja, o que tem encaminhamento mais específico;
- Se a entrada selecionada tiver um gateway, então enviar para ele a partir da interface especificada;
- Caso contrário, enviar logo para o computador de destino final;

### Address Resolution Protocol ARP

Usado para obter o MAC address de algum computador na rede e associá-lo ao seu endereço IP. O IP e MAC do computador de origem é partilhado na rede por todos (broadcast) assim como o IP desconhecido. O computador que tiver o IP responderá com o seu endereço MAC e assim poderá haver conexão e transferência entre os dois. 

#### Funcionamento

Considerando:
- ID - ip de destino
- IO - ip de origem
- MD - mac address de destino
- MO - mac address de origem

A trama de informação entre um computador A, um router R e um computador B:
- Entre A e R terá ID = B, IO = A, MD = R, MO = A
- Entre R e B terá ID = B, IO = A, MD = B, MO = R

### Obtenção de endereços IP, protocolo DHCP

Através dos ISPs. Para servidores HTTP ou de email os IPs são fixos, para outros casos (máquinas pessoais) usa-se o protocolo DHCP (*Dynamic Host Configuration Protocol*). Funcionamento entre servidor-cliente (DORA):
- O computador que chega à rede manda um DHCP discover ao servidor;
- O servidor retorna um DHCP offer
- O computador responde com DHCP request;
- O servidor retorna um DHCP Ack;
Cada transação contém um ID, que é diferente para cada computador da rede.

### Network Address Translation (NAT)

Inicialmente o IPv4 continha apenas 32 bits, o que não foi suficiente para o crescimento da internet. Atualmente existe o IPv6. NAT veio como uma solução para a falta de endereços: existem endereços de formatos que não são usados na internet, não são alcançáveis, pois existe sobreposição. Todos os requests da rede local são enviados com o IP do router, que contém um endereço único. O router contém uma tabela NAT que associa o endereço de origem ao endereço de destino, podendo fazer a tradução quando a resposta chega. 

#### NAT Transversal

Um servidor na rede local (com IP que pode ser comum a muitas redes) pode-se ligar ao exterior através de uma porta fixa X. Assim, todos os requests que vêm para a rede local, o router encaminha diretamente para o servidor assinalado.

## Internet Control Message Protocol (ICMP)

Usada por routers e servidores host. Consistem em mensagens especiais para avisar de algum erro ou mensagens de controlo. Permitem inclusive fazer o **redirect** de pacotes quando um servidor/router X perceber que o percurso é mais curto de outro lado.

### Comandos

```bash
$ ping <IP>             # manda mensagens/pacotes para atribuir estatísticas ao servidor de destino
$ traceroute <MACHINE>  # manda mensagens com time = 1,2,3... de forma a traçar o percurso dos dados
$ netstat -nr           # permite ver a forwarding table, com destination, gateway, genmask...
$ ip rout show cache    # ver a cache do ip atual
```

## IPv6

- Os endereços são de 128 bits e normalmente representados em hexadecimal;
- Melhorias no suporte a multicast
- Configurações de host;
- Mais eficiente em routing
- #TODO

### Endereços

#### Link local

Usado para comunicar entre hosts dentro da mesma LAN. É criado automaticamente pelo MAC address. 

#### Global unicast

Pode ser gerado automaticamente pelo prefixo e o MAC address.

#### Anycast

#### Multicast
#TODO

### Protocol Neighbor Discovery (ND)

O IPv6 usa este protocolo para:
- descobrir os nós do mesmo LAN;
- descobrir os vizinhos de um MAC address a partir dos seus endereços IPv6;
- encontrar rotas na rede;
- manter a informação dos seus vizinhos;

#### Mensagens

- `Neighbor solicitation`, para obter o endereço MAC do vizinho ou saber se ele está presente;
- `Neighbor advertisement`, resposta à solicitação;
- `Router advertisement`, usado pelos routers para enviar informação sobre o prefixo da rede;
- `Router solicitation`, request de um router advertisement de um router no link;
- `Redirect`, para informar um host sobre a melhor rota a tomar;