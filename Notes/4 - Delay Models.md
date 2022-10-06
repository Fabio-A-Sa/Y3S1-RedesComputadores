# Delay Models

## Multiplexing

Multiplexar: técnicas para transmitir pacotes de vários tipos num mesmo cabo. Existem três tipos de estratégias

### Statistical Multiplexing

Todos os pacotes de várias proveniências são colocados numa fila de espera. O tempo necessário para transferir os frames é igual ao comprimento dos pacotes / capacidade do canal.

### FDM - Frequency Division Multiplexing

São usadas nas comunicações de rádio. A capacidade do meio é dividida em m subcanais, cada um com a sua frequência. A capacidade de cada canal é C/m e o tempo necessário para transferir os frames é igual a Lm/C.

### TDM - Time Division Multiplexing

O tempo é dividido em m slots com comprimento fixo. Cada pacote é transmitido no seu respectivo tempo, sendo a capacidade do canal a utilizar = C = C/m. Da mesma forma, o tempo necessário para transferir os frames é igual a Lm/C.

## Queue models

O delay é um importante indicador de performence nas redes de comunicação. É computado usando modelos de filas de espera, que:

- Quantificam o número de pacotes na rede;
- Calcula o tempo médio de espera por pacote;

Quando as filas (nos routers, switches...) estão cheios, há pacotes que se perdem.