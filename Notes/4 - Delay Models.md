# Delay Models

## Multiplexing

Multiplexar: técnicas para transmitir pacotes de vários tipos num mesmo cabo. Existem três tipos de estratégias

### Statistical Multiplexing

Todos os pacotes de várias proveniências são colocados numa fila de espera. O tempo necessário para transferir os frames é igual ao comprimento dos pacotes / capacidade do canal.

### FDM - Frequency Division Multiplexing

São usadas nas comunicações de rádio. A capacidade do meio é dividida em m subcanais, cada um com a sua frequência. A capacidade de cada canal é C/m e o tempo necessário para transferir os frames é igual a Lm/C.

### TDM - Time Division Multiplexing

O tempo é dividido em m slots com comprimento fixo. Cada pacote é transmitido no seu respectivo tempo, sendo a capacidade do canal a utilizar = C = C/m. Da mesma forma, o tempo necessário para transferir os frames é igual a Lm/C.

# Queue models

O delay é um importante indicador de performence nas redes de comunicação. É computado usando modelos de filas de espera, que:

- Quantificam o número de pacotes na rede;
- Calcula o tempo médio de espera por pacote;

Quando as filas (nos routers, switches...) estão cheios, há pacotes que se perdem.

## Poisson Processes

Calculam a probabilidade de eventos discretos e independentes: a chegada de x pacotes num intervalo de tempo. <br>
Exemplo: sabe-se que numa rede existe capacidade de transporte de m pacotes por minuto. Calcule a probabilidade de ocorrer transporte de x pacotes nesse mesmo muito. Usando a distribuição de Poisson:

> P(x) = (m^x * e^(-m)) / x! <br>
> A variância e o valor esperado é sempre igual ao valor médio: m <br>

Probabilidade do tempo de chegada entre cada pacote ser menor ou igual a A:

> P(A <=T) = 1 - P(A > T) = 1 - e ^ (-lambda * t) <br>

Cálculo do tempo médio entre chegadas de pacotes (derivada da fórmula anterior):

> P() = lambda * e ^ (-lambda * t) <br>

### Propriedades do Processo de Poisson

#### 1. Merging

O resultado da soma de processos de Poisson continua a ser um processo de Poisson. Exemplo: num local onde chegam 3 pacotes/segundo e 5 pacotes/segundo, origina um fluxo de 8 pacotes/segundo.

#### 2. Splitting

O resultado da divisão de processos de Poisson continua a ser um processo de Poisson. Exemplo: num local onde chegam 5 pacotes/segundo, se houver divisão num ramo do fluxo em x pacotes/segundo, o outro ramo terá (5-x) pacotes/segundo.

## Caracterização do modelo de filas

`lambda`: número médio de pacotes enviados por segundo <br>
`pico`: número médio de pacotes processados por segundo <br>
`ró`: lambda / pico, intensidade do tráfico (ocupação do servidor).

### Notação de Kendall

A/S/s/K, onde:

- A: processo de chegada de pacotes (Poisson, por exemplo)
- S: processo de processamento de pacotes (Poisson, por exemplo)
- s: número de servidores
- K: capacidade do sistema em número de buffers (assumir infinito quando for omido)

## Little's Law

O número médio de pacotes que estão dentro do sistema (N) é igual ao tempo médio em que cada pacote passa no sistema (T) multiplicado pela taxa de chegada de pacotes ao sistema (lambda).

> N = T * lambda <br>

Num sistema estável (as filas de espera não crescem infinitamente), o tempo médio de espera não depende da taxa do serviço mas apenas do número de clientes à espera e da taxa de chegada. 

## Modelo de Markov Chain M/M/1/Inf

Na Cadeia de Markov, os estados estão numerados de acordo com o número de clientes dentro do sistema. Há uma transição para cada intervalo de tempo delta, em que há possibilidade de avançar no estado (chegou mais um pacote) ou retornar ao estado anterio (o pacote foi processado e saiu do sistema). Assim:

> P(0, 0), probabilidade de não haver alteração de estado = 1 - lambda*delta - pico*delta <br>
> P(i, i-1), probabilidade do pacote ser processado = pico*delta <br>
> P(i i+1), probabilidade de ter mais um pacote em espera = lambda*delta <br>
> P(0), probabilidade do sistema não ter ninguém = 1 - ró = 1 - probabilidade do sistema estar a processar algo <br>
> P(n), probabilidade do sistema ter X pacotes = ró^n * (1-ró) <br>

### Modelos Discretos vs. Modelos Contínuos

1. Nos modelos de Poisson de chegada de pacotes, uma taxa de serviço alta não é sinónimo de um número pequeno de pacotes à espera (porque os pacotes tendem a chegar todos juntos);

2. Nos modelos discretos de chegada de pacotes (D/D/1), não vai haver espera, considerando um sistema estável (a taxa de chegada <= taxa de processamento);

### Modelo M/M/1/B

Modelo de filas de comprimento finito (B buffers). Neste caso os pacotes podem ser perdidos se os buffers estiverem todos cheios:

> P(B), probabilidade de perder pelo menos um pacote = ró^B * P(0)

### Modelo M/D/1

Tem um modelo de chegada de pacotes de Poisson, enquanto o tempo de serviço segue uma qualquer distribuição D em que se conheça E[X] e E[X^2]. Assim, segundo a fórmula de Pollaczek-Khinchin (P-K), tem-se que:

> Tw = lambda * E[X^2] / (2*(1-ró)), com ró = labda / pico = lambda * E[X]

## Redes de filas de espera

Numa rede de X filas de espera, a fila X não poderá ter uma taxa de Poisson chegada de pacotes, uma vez que está limitada à taxa de processamento/serviço da fila X-1. Há, no entanto, duas soluções:

### 1. Kleinrock Independence Approximation

A ideia é acoplar vários envios de pacotes numa mesma linha de transmissão. Assim há reestabelecimento da independência dos tempos segundo os tamanhos dos pacotes. O modelo M/M/1 pode ser usado para modelar cada canal de comunicação. <br>

- Os sistemas envolvendo Poisson estão nas portas de entrada;
- Os tamanhos dos pacotes são dados por distribuições exponenciais;
- São redes densamente conectadas;
- Moderam a carga de tráfego pesado;

### 2. Jakson Networks

