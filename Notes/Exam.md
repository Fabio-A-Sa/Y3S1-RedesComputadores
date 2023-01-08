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