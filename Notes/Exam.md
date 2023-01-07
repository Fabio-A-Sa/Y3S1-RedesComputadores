# Preparação para o Exame

## Tópicos

0. Introduction
1. Physical Layer
2. DataLink Layer
3. Network Layer
4. Transport Layer
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

Para transmissões wireless, em antenas por exemplo, a razão entre a potência emitida e recebida é igual a (4 * pi * frequência * distância / c) ^ 2

## 2 - DataLink Layer

Camada que regula a transmissão, retransmissão, integridade e gestão de erros provenientes da transmissão da informação de forma física pela Physical Layer. Para o envio da informação (cadeias de bits) é necessário recorrer a *framming*, através:
- da contagem de bits, cada frame é constuído pela quantidade de dados seguida desses mesmos dados;
- da existência de um bit de término com *stuffing*;
- da existência de flags de início e término, também com *stuffing*;

### 2.1 - Error detection

