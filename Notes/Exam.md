# Preparação para o Exame

## Tópicos

0. Introduction
1. Physical Layer
    - 1.1 Shannon's Law
    - 1.2 Meios de Propagação
2. DataLink Layer
    - 2.1 Error detection
    - 2.2 Automatic Repeat Request
3. Network Layer
    - 3.1 DHCP
    - 3.2 NAT
    - 3.3 ICMP
    - 3.4 IPv6
    - 3.5 DN
4. Transport Layer
    - 4.1 UDP
    - 4.2 TCP
    - 4.3 Routing
5. Application Layer

## 0 - Introduction

As redes podem ser classificadas de acordo com a sua extensão (PAN, LAN, MAN, WAN, Internet, PLMWI) e são baseadas numa stack de camadas onde são passados os pacotes de informação (PDNTA):

1. Physical Layer - Passagem dos bits dos pacotes de dados por canais físicos;
2. DataLink Layer - Passagem de pacotes entre elementos das redes;
3. Network Layer - Roteamento dos pacotes de um lado para outro;
4. Transport Layer - Com os protocolos TCP ou UDP;
5. Application Layer - Suporta a aplicação, como o FTP, SMTP e HTTP;

A passagem de pacotes pode ser por dois métodos:

- `Circuit Switching`, só quando a ligação é estabelecida é que os pacotes são enviados;
- `Packet Switching`, passagem de pacotes pelos intermediários e segundo a ordem na fila;

## 1 - Physical Layer

No meio físico, de acordo com Nyquist, um sinal de frequência X Hz pode ser reconstruído se se capturar 2X símbolos / segundo. A capacidade de um canal com M níveis é definido como C = 2B*Log(M) símbolos ou bits / segundo. A transmissão pode ser:

- *Baseband* - de 0 até um valor de frequência máximo BH. É característico dos fios;
- *Passband or BandPass* - em torno de uma frequência FC. É característico de wireless e optical channels;

De qualquer das formas, os bits da transmissão podem ser descodificados de algumas formas:

- NRZ-L (Non Return to Zero - Level), um nível superior representa 0 e o inferior representa 1;
- NRZ-I (Non Return to Zero - Inverted), a mudança de nível representa 1;
- Manchester, uma descida é 1, a subida é 0, usada na Ethernet;

Para descodificar os símbolos é necessário ter suficientes transições, pelo que é normal misturar ciclos de relógio com cada símbolo transmitido. Para sinais contínuos, podemos usar modulações binárias, de mudança de amplitude, frequência e fase.

### 1.1 - Shannon's Law

Na realidade a capacidade teórica de um canal é dada em função do ruído captado do receptor, logo M = 1 + SNR (Signal to Noise Ratio). Assim é proporcional à largura de banda e como um sinal muito superior ao nível de ruído é proporcional ao logaritmo de SNR.

### 1.2 - Meios de Propagação

- Coaxial Cable, grande imunidade a ruído e com baixa atenuação, usado para grandes larguras de banda;
- Unshielded twisted pair;
- Fiber optic, para grandes larguras de banda e com muito pouca atenuação, embora tenha alguma perda devido à reflexão total;

Para transmissões wireless em antenas a razão entre a potência emitida e recebida é igual a (4 * pi * frequência * distância / c) ^ 2

## 2 - DataLink Layer

Camada que regula a transmissão, retransmissão, integridade e gestão de erros provenientes da transmissão da informação de forma física pela Physical Layer. Para o envio da informação (cadeias de bits) é necessário recorrer a *framming*, através:
- da contagem de bits, cada frame é constuído pela quantidade de dados seguida desses mesmos dados;
- da existência de um bit de término com *stuffing*;
- da existência de flags de início e término, também com *stuffing*;

### 2.1 - Error detection

Os erros podem ser simples (independentes de erros anteriores) ou em *bursts*, conjuntos dependentes. Para determinar probabilidades usa-se o FER (*Frame Error Ratio*) e o BER (*Bit Error Ratio*). Para deteção de erros usa-se um bit de paridade (onde o bit é 1 quando existe um número ímpar/par de 1s na trama), uma paridade bidimensional (com d = 4).

#### CRC - Cyclic redundancy check

Dado um polinómio M(x) derivado dos bits a transmitir, e r bits de redundância, faz-se R(x) = M(x) * x^r / (x^r + 1). Envia-se M(x) * x^r + R(x). Do lado do receptor é só fazer a divisão inteira de T(x) por G(x) e o resultado tem de ser zero. Detecta 1,2 ou 3 bits com erro.

### 2.2 - Automatic Repeat Request (ARQ)

Para pacotes perdidos ou com erros, o receptor retransmite a informação. Para isso há três métodos:

#### Stop and Wait

O transmissor envia e fica à espera por timeout da resposta (ACK). Se a resposta não for afirmativa ou não vier em tempo útil, reenvia a informação. Os frames são numerados, assim como as respostas e são descartados duplicados para não haver sobreposição. A eficiência é dada por 1 / (1 + 2 * x), com x sendo a relação entre o tempo de propagação (depende da distância percorrida) e o tempo de transferência da trama (depende do tamanho da trama). A eficiência é muito baixa quando o valor de x (ou a distância percorrida) é grande, ou seja, quando a trama tem tamanho muito inferior à distância percorrida.

#### Go-Back N / Sliding Window Protocol

Uma janela de ordem K permite o envio de até K frames antes de esperar pelas respostas, para aumento da eficiência do Stop and Wait. O receptor rejeita frames fora da sequência e a resposta ACK(i) permite identificar que todos os pacotes de ordem até i-1 foram enviados correctamente. O número máximo de K é 2^M-1, com M = número de bits necessários para codificar o índice das respostas e correspondentes frames. Neste caso a eficiência é W / (1 + 2 * x).

#### Selective Repeat

Parecido com o anterior mas aceita tramas fora de ordem. Usado para casos em que x ou W são muito elevados. O receptor sinaliza a falta/erro da trama I com REJ(I) e o transmissor reenvia apenas o que é pedido pelo receptor. O tamanho da janela é agora W = M / 2 = 2^(k-1), com k igual ao número de bits suficientes para codificar o índex da trama. O transmissor envia no máximo meia janela antes de receber um ACK para não ocorrer sobreposição das suas tramas na janela. A nível de eficiência é dado por expressões semelhantes às anteriores.

#### Link-to-Link ARQ

Os erros ou perdas são detectados entre cada par de links e não nas pontas da transmissão. Necessita que a rede lembre o estado, o que provoca um maior processamento interno e memória usada.

#### End-to-End ARQ

Só nas pontas é que são detectados os erros ou perdas. A complexidade intermédia é baixa mas não é usada para sistemas com grande distância ou com grande percentagem de erros.

### 2.3 - Delay Models

#### Multiplexing

Usar o mesmo canal de capacidade C para enviar diferentes tipos de pacotes. Pode ser numa única fila, em M filas fixas pelo tempo (*Time Division Multiplexing*) e em M filas fixas pela frequência (*Frequency Division Multiplexing*). Nestes dois últimos casos o delay provocado é diretamente proporcional a M e a capacidade de cada canal inversamente proporcional a M.

#### Poisson Processes

Seja Lambda o número de chegadas de pacotes por segundo e T o número de segundos:
- Probabilidade de chegar X pacotes é ((Lambda * T)^x * e^(-Labda * T)) / (X!);
- Probabilidade do tempo de chegada ser menor que A é (1 - e^(Lambda * T));
- O tempo médio é dado por Lambda * e^(-Lambda * T)

- Lambda -> O número de pacotes que chegam por unidade de tempo
- Miu -> O número de pacotes servidor por unidade de tempo
- Ró -> Relação entre Lambda e Miu, dá a intensidade de tráfego e a ocupação do servidor

#### Kendalls Notation A/S/s/K

A -> Processo de chegada de pacotes
S -> Processo de serviço dos pacotes
s -> Número de servidores
K -> Capacidade do sistema, normalmente infinito para sistemas estáveis

A Little's Law indica que N = Lambda * T, com N a representar o número de clientes do sistema (os que vão chegando e os que estão a ser tratados no momento). O número de clientes no sistema não dependem de Miu, a taxa de serviço.

#### Cadeia de Markov

Usada para sistemas M/M/1/Inf estáveis. A probabilidade de chegar um novo pacote à fila num tempo Sigma é Lambda * Sigma e a probabilidade de um pacote ser atendido é Miu * Sigma. A probabilidade de estar num estado N é Ró ^ N * (1 - Ró).

- Nos modelos de Poisson de chegada de pacotes, uma taxa de serviço alta não é sinónimo de um número pequeno de pacotes à espera (porque os pacotes tendem a chegar todos juntos);

- Nos modelos discretos de chegada de pacotes (D/D/1), não vai haver espera, considerando um sistema estável (a taxa de chegada <= taxa de processamento);

#### Redes de filas de espera

Não se pode admitir uma cadeia linear com base na cadência de Poisson. No entanto dá para aproximar, tornando-se uma cadeia subdividida (Kleinrock Independence Approximation) através do modelo M/M/1 ou em redes de Jackson.

### 2.4 - MAC Sublayer

A DataLink Layer subdivide-se nas camadas LLC (Logical Link Layer), responsável por fluxo de dados e detecção de erros, e MAC (Medium Access Control), responsável por controlo de acesso, recepção e retransmissão da informação. Numa situação normal, vários são os computadores que usam o mesmo canal para comunicar. Para M computadores, cada computador tem direito a C/M da capacidade total do canal se forem todos tentar comunicar entre si, ou C se cada um esperar por sua vez.

#### Channel Partitioning Protocols

Time Division Multiple Access ou Frequency Division Multiple Access. Custará na eficiência de cada chamada pois agora cada emissor tem que partilhar o meio (ou por slots de tempo ou por frequência).

#### Random Access Protocols

Acontecem quando numa rede todos os emissores têm a mesma prioridade:

- ALOHA: envia o pacote para a rede esperando K tempo para a resposta, com K random. Usado para sistemas de baixa frequência de utilização;
- CSMA (Carrier Sense Multiple Access): se ninguém estiver a transmitir, lança o pacote na rede. Pode ser persistente, transmite quando o canal estiver desocupado tentando sempre ver de está livre, ou não persistente, quando ainda espera um tempo random R antes de cada tentativa de ver se está livre e só depois é que transmite, ou P-Persistente, quando transmite de um modo ou outro com probabilidade P. De qualquer modo espera sempre por ACK;
- CSMA/CD: Com deteção de colisões, e nesse caso aborta. Transmite novamente mas após esperar um tempo exponencial (Binary Exponential Backoff). Tramas curtas podem impedir a deteção de colisões sob o ponto de vista do emissor. O tempo de transmissão da trama deve ser maior do que duas vezes o tempo de ida e volta (tempo de propagação). Não dá para ser usada em sistemas sem fios devido às distorções causadas pelo meio, iria "detectar" colisões não tendo nenhuma ou não conseguiria ouvir a frequência do outro emissor pois as distâncias são elevadas.
- CSMA/CA: Evita erros, esperando ainda um tempo exponencial depois que descobrir que o canal está livre. É necessário voltar a haver ACK e é característica das redes sem fios.

#### Taking Turns Protocols

- Polling: quando existe um computador Master na rede que dá autorização para as outras transferirem pacotes. Se os tempos forem bem implementados não há colisões mas perde-se algum tempo em espera ou na transmissão dos pedidos;
- Token Passing: só há transmissão de pacotes por parte dos edges que têm o token. Há latência pois tem de haver passagem do token;

### 2.5 - Evolução da internet na Link Layer

- Bus - com cabo coaxial, os computadores ligavam-se através de um cabo onde podia haver colisões e múltiplos transmissores e receptores.
- Active Hub - existem repetidores que enviam os bits recebidos para todos as outras portas. Existe deteção de colisão, mas só numa única porta de cada vez.
- Bridge - Separa os domínios de colisão e vários frames podem ser transmitidos simultaneamente.
- Full Duplex Ethernet - o CSMA/CD não é usado praticamente, pois não existem colisões. Os cabos UTP são usados (Unshielded Twisted Pair), que são mais baratos e fáceis de instalar, embora não suportem bem múltiplas transmissões ou receptores;
- Ethernet de hoje em dia - UTP para distâncias curtas, fibras óticas para longas, suporta redundância para minimizar erros;

## 3 - Network Layer

Transporta os pacotes de dados da origem ao destino e calcula caminhos através de grafos. O encaminhamento de pacotes pode ser por **Virtual Circuits** (todos os pacotes são enviados sequencialmente se houver um caminho estável entre o primeiro e último routers) ou por **Datagrams Networks**, quando os pacotes são enviados sem um caminho definido, o que é mais difícil de gerir e podem vir fora de ordem.

### 3.1 - DHCP - Dynamic Host Configuration Protocol

Para obtenção de IP por parte de um HOST a partir do server da rede. Segue respostas DORA (Discovery, Offer, Request, Ack), em que as três últimas já vêm com o IP único para aquela subrede.

### 3.2 - NAT - Network Address Translation

Network Address Translation. Por motivos de IPv4 usado internamente não há IPs suficientes, pelo que a Internet contacta com um único router de casa, que fica encarregue de traduzir os endereços e redirecionar os pacotes. Em casos excepcionais, existe a NAT transversal, que permite contacto directo com um host privado a partir de uma entrada específica na tabela.

### 3.3 - ICMP - Internet Control Message Protocol

Serve para descobrir rotas e fazer redirects para caminhos mais curtos / com menos custo

### 3.4 - IPv6 Addresses

- Unicast: um sender e um receiver;
- Multicast: um sender e vários receivers;
- Anycast: proporciona iguais IDs para vários receivers;
- Link-local: para redes privadas;

### 3.5 - ND - Neighbor Discovery Protocol

Usa mensagens ICMPv6 com Link Local Addresses para descobrir novos nós da mesma LAN, descobrir os routers da rede e manter atualizados as características dos nós vizinhos. As mensagens trocadas podem ser as seguintes:

- Neighbor solicitation/advertisement, para obter o endereço MAC do vizinho ou saber se ele está presente;
- Router solicitation/advertisement, usado pelos routers para enviar informação sobre o prefixo da rede;
- Redirect, para informar um host sobre a melhor rota a tomar;

## 4 - Transport Layer

### 4.1 - User Datagram Protocol (UDP)

Não tem um mecanismo de controlo de erros mas como é mais simples permite contacto direto com o IP de destino sem muito overhead, enviando diretamente os dados. Só tem um checksum que é opcional.

### 4.2 - Transmission Control Protocol (TCP)

Orientado às comunicações, com base em ACK e NACK, e incorpora o controlo de fluxo e controlo de congestionamento. Os números de sequência correspondem ao primeiro byte transferido naquela trama, para depois poder ser ordenado e descarta duplicados. Por um lado há **controlo de fluxo** pois há o parâmetro Advertise Window que indica a quantidade de espaço que ainda tem disponível. O tempo de retransmissão é feito iterativamente usando uma *Adaptative Retransmission*, em que há retransmissão apenas dos blocos selecionados. Por outro lado há **controlo de congestionamento**, com *additive increase* e *multiplicative decrease* da CongestionWindow:
- Sempre que leva time-out, baixa, vai até metade em slow start e depois additive increase;
- Sempre que levar 3 ACKs repetidos, baixa, e depois additive increase;

### 4.3 - Routing

A escolha de um bom caminho (boa largura de banda, curta distância, baixa latência) é importante para garantir a eficiência da rede e limitar a quantidade de pacotes perdidos no processo. A Spanning Tree pode ser realizada por:
- Algoritmo de Dijkstra, onde as mensagens trocadas são mais localizadas (partilha informação do nó N e nós adjacentes a N apenas), o que provoca um delay grande se a rede for considerável;
- Algoritmo de Bellman-Ford, onde trocam-se as Fowarding Tables em vez de mensagens soltas, as mensagens são mais longas mas as modificações perpetuam-se na rede mais rapidamente;

#### RIP - Routing Information Protocol

Protocolo que gere a distância entre os routers. Os routers enviam a sua distância aos outros de 30 em 30 segundos ou quando um update causa uma modificação na rede em si. Está limitado a pequenas redes.

### STP - Spanning Tree Protocol

Protocolo existente nas bridges presentes nos switches da rede. Aqui os routers não constroem as suas próprias Spanning Tree, existindo apenas uma árvore no sistema que é construída por mensagens trocadas entre switches. As mensagens são do tipo (root da árvore atual, distância de ligação, origem). Inicialmente todos os switches assumem que eles próprios são a raiz da árvore. À medida que as mensagens são trocadas, os switches admitem sempre que a raiz da árvore é agora o switch que contém o menor número identificador. Os switches bloqueiam algumas portas para que não existam ciclos.

## 5 - Application Layer

Esta camada define os tipos de mensagens trocadas, a sintaxe e semântica delas e as regras de envio e resposta por parte dos processos. Por exemplo o protocolo HTTP(S), que pode ser não-persistente (um recurso por conexão TCP, 2 * RTT + FileTransferTime) ou persistente (vários recursos numa mesma conexão TCP). Esta última pode ser com *pipelining*, para vários requests sem esperar pela resposta (um RTT para tudo), ou sem *pipelining*, quando novos requests são feitos só depois de receber a resposta ao anterior (cada request tem direito ao seu RTT). O IMAP permite manipular mensagens existentes no servidor e guarda o estado entre sessões. O POP3 serve para autorização de conexão entre o servidor e para download de mensagens entre serviços, mas não guarda o estado entre sessões.