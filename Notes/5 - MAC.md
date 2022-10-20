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



### Taking turns

