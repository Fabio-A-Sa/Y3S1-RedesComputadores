# 5 - Medium Access Control

A Data Link Layer subdivide-se em duas camadas: a LLC (Logical Link Control) e MAC (Medium Access Control).

- `LLC` é faz a interface entre a Network Layer e é responsável pelo fluxo de dados e deteção de erros;
- `MAC` é responsável pelo controlo de acesso, recepção e retransmissão de erros, endereços e deteção de erros. 

## Tipos de meios de comunicação

- `Point-to-Point`, entre o Switch da internet e o host;
- `Broadcast`, entre meios partilhados, como ligações por cabo em redes, satélite e wifi;

## Coordenação de estações com broadcast e meio partilhado

Numa situação normal, vários são os computadores que comunicam usando o mesmo canal. Existindo m estações e o canal com capacidade R bits/s:

> numa situação em que só um comunica e todos lêm a velocidade é R bits/s, <br>
> numa situação em que vários tentam comunicar, em média a velocidade é R/m bits/s <br>

## Classes de protocolos MAC

### Channel Partitioning

- `TDMA Time Division Multiple Access`, o tempo é dividido em m porções;
- `FDMA Frequency Division Multiple Access`, a frequência é dividida em m porções;

### Random Access Protocols

Assumindo que não há coordenação entre estações e o canal disponível transmite R bits/s. Se duas ou mais transmitem no canal ao mesmo tempo, existe uma **colisão**: a mensagem perde-se pelo ruído causado (os receptores só têm acesso ao somatório das frequências transmitidas) e tem de haver retransmissão de cada uma.

- Quando a transmissão pode ocorrer?
- Como detectar colisões (na parte do receptor e transmissor);
- Se houver colisões, como recuperar os dados?

#### ALOHA

##### Funcionamento

Implementação simples e descentralizada em cada estação. Sempre que uma estação tem um pacote para enviar, envia imediatamente e fica em espera da confirmação até receber uma confirmação. Se não receber confirmação, parte do princípio que houve colisão e nesse caso espera um tempo aleatório K até à próxima retransmissão. O tempo aleatório K é importante porque se houve realmente colisão e houver uma retransmissão imediata, há muita probabilidade de ocorrer novamente. 

##### Eficiência

A implementação desta técnica com slots de tempo é mais eficiente (36.8% contra 18.4%, considerando a probabilidade de uma estação gerar um pacote = 100%).

Quando o tráfego é residual, a técnica ALOHA é bastante requisitada, pois em média há espera de 0.5 slots de tempo. Quando o tráfego é intenso, o tempo de espera aumenta exponencialmente, pois a probabilidade de colisão é elevada e aumenta o número de retransmissões.

#### CSMA Carrier Sense Multiple Access

##### Funcionamento

Cada estação não interrompe a transmissão de outras. No entanto as colisões ainda podem ocorrer devido aos tempos de propagação pelo canal, causando perda integral do pacote transmitido. 

##### Eficiência

É uma técnica usada para valores de `a` bastante baixo, ou seja, a probabilidade de haver colisões é também baixa.

> a = Tempo de propagação / Tempo de transmissão do pacote

##### Persistent CSMA

A estação transmite quando o canal estiver disponível. Quando o canal não estiver livre, então espera até que esteja. É o subtipo mais utilizado.

##### Non-Persistent CSMA

A estação transmite quando o canal estiver disponível. Quando o canal não estiver livre, então espera um tempo random e retransmite. É menos eficiente.

##### P-Persistent CSMA

É um intermédio entre os dois tipos anteriores. A estação transmite pacotes com probabilidade p. É considerado colisão quando a transmissão não ocorreu bem no slot anterior, caso contrário a estação espera até que a estação esteja livre e aí repete o algoritmo.

#### CSMA/CD Carrier Sense Multiple Access Collision Detection

##### Funcionamento

Semelhante à técnica de CSMA. Enquanto uma estação transmite, fica à escuta. Se ouvir algo diferente do que transmite, então existe colisão e aborta imediatamente a operação. Assim não é necessário haver resposta para transmissões bem sucedidas (ACK).

Para uma retransmissão, determina um atraso aleatório usando um algoritmo chamado "Binary Exponential Backoff". Para a retransmissão i, espera-se um número de slots aleatórios na gama [0, 2^i-1].

Tramas curtas podem impedir a deteção de colisões sob o ponto de vista do emissor. O tempo de transmissão da trama deve ser maior do que duas vezes o tempo de ida e volta (tempo de propagação). 

##### Eficiência

> a = Tempo de propagação máximo / Tempo de transmissão da trama <br>
> S = eficiência = 1 / (1 + 2ea) = 1 / (1 + 5.44a) <br>

Esta técnica é bastante eficiente (S aproximado a 1) quando:

- o cabo é pequeno;
- comprimento das tramas é grande

Na prática por causa de FER (*Frame Error Ratio*) a trama não pode ser muito grande. Não pode ser usado em meios sem fios uma vez que a atenuação é elevada: neste caso o transmissor ouve aquilo que fiz com uma potência elevada, a potência do outro transmissor é ouvida numa percentagem muito baixa e assim pode não haver deteção de colisões.

#### CSMA/CA Carrier Sense Multiple Access Collision Avoidance

##### Funcionamento

Semelhante à técnica de CSMA. Antes de transmitir, a estação fica à escuta DIFS tempo e se o meio ainda estiver livre ao fim desse tempo, transmite o pacote. Senão, espera até à transmissão da estação e volta a esperar DIFS tempo mais um tempo aleatório com Backoff até tentar novamente. Para evitar colisões é necessário voltar a existir pacotes de confirmação (ACK).

É um protocolo usado nas redes sem fios.

##### CSMA/CA RTS-CTS

Como as colisões não são detectadas e frames abortados, então há pequenos frames reservados usados para requests:

- RTS: Request to Send, como pedido
- CTS: Clear to Send, como resposta, é ouvida por todas as estações para evitar colisões.

### Taking turns

#### Polling

A estação principal dá autorização a outras estações para transmitir no seu tempo. Se os tempos forem bem implementados, não há colisões mas há algum tempo perdido em espera e na transmissão dos pedidos.

#### Token passing

Só há transmissão de dados nas estações que têm token. Pelo lado negativo há latência pois embora haja estações em que não têm nada a transmitir na sua vez, têm de passar o token pela rede e isso demora tempo.

## Ethernet Topology

1. `Bus` - com cabo coaxial, os computadores ligavam-se através de um cabo onde podia haver colisões e múltiplos transmissores e receptores. 
2. `Active Hub` - existem repetidores que enviam os bits recebidos para todos as outras portas. Existe deteção de colisão, mas só numa única porta de cada vez. 
3. `Bridge` - Separa os domínios de colisão e vários frames podem ser transmitidos simultaneamente.
4. `Full Duplex Ethernet` - o CSMA/CD não é usado praticamente, pois não existem colisões. Os cabos UTP são usados (Unshielded Twisted Pair), que são mais baratos e fáceis de instalar, embora não suportem bem múltiplas transmissões ou receptores;
5. `Ethernet de hoje em dia` - UTP para distâncias curtas, fibras óticas para longas, suporta redundância para minimizar erros. 

### Switch Self-Learning

As tramas que vão chegando ao switch, tem endereço de origem e destino. À medida que transmite e recebe, vai preenchendo as tabelas que relacionam os computadores às portas (se o computador A mandou informação na porta 1, então para comunicar com A é necessário enviar tramas na porta 1). As tabelas são temporárias e se o switch não souber para onde enviar, envia para todas as portas excepto ao transmissor. 

### Virtual LANs

Quando uma bridge ou switch tem simultaneamente várias redes, vários domínios de colisão. Podem ser extendidas com interfaces/cabos de fibra ótica *trunk link*.