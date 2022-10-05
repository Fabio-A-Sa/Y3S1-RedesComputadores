# Physical Layer

São os canais reais usados na rede para transmitir e receber dados digitais. O sinal de transmissão de input pode ser modificado até ao receptor, com uma frequência que varia entre zero e o valor máximo BH. Um sinal também é composto por um número variado de ondas harmónicas. 

## Reconstrução do sinal no receptor

Nyquist provou que é possível reconstruir totalmente um sinal no receptor desde que exista uma banda BH e amostrado na taxa de 2B por segundo. Amostragem em taxa mais alta não fornece informações adicionais. A fórmula a reter é bitrate C = 2BH * log (M)

### Exemplo:

Uma onda quadrada tem diferença de potencial que varia entre 5v e -5v (M = 2). A frequência do canal é de BH = 3kHz. Então deverá receber 2BH símbolos por segundo, ou seja, 6k, com cada símbolo a ser um bit de informação. 

Se M = 4, ou seja, há 4 níveis de diferença de potencial para enviar a informação, então o bitrate é 6k * log (4) = 12 kbits/s.

### Bandas

1. **Baseband**: O sinal tem uma frequência de zero até a um limite BH. É comum para fios;
2. **Passband**: O sinal usa uma banda de frequências em torno de uma frequência fixa FC. Comum para canais sem fio e óticos.

## Transmissão em BaseBand

1. **NRZ-L, Non Return to Zero Level**, há dois níveis, o mais baixo representa o 1;
2. **NRZ-I, Non Return to Zero Inverted**, há também dois níveis, mas a mudança de nível representa um 1;
3. **Manchester**, a transmissão é no meio do bit. Se descer é um 1, se subir é um 0. É muito usada na Ethernet. 

### Clock Recovery

Para descodificar os símbolos, o sinal precisa ter transições suficientes. Então é usada uma codificação Manchester que, por cada 4 bits de dados, manda também uma codificação de 5 bits respectivamente. 