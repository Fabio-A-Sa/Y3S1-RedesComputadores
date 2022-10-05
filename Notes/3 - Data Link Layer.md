# Data Link layer

É a camada que permite a comunicação entre máquinas adjacentes. O seu objectivo é reduzir e eliminar os erros de transmissão que podem ocorrer na physical layer e regular o fluxo de dados.

## Framing

Os dados enviados devem ser separados em frames / pacotes para regular o fluxo de dados e reduzir a possibilidade de erros, com posterior retransmissão caso ocorram. Para isso há três técnicas que são usadas:

### 1 - Character byte count

O primeiro byte do frame indica quantos bytes o frame possui. No entanto, quando ocorre um erro torna-se impossível resolver a situação e a partir daí todos os dados são corrompidos. Não é uma técnica usada atualmente.

### 2 - Flag bytes with byte stuffing

O frame é delimitado por bytes de flag. Como o código desses bytes pode aparecer no meio dos dados, ocorrendo assim o possível corte da frame e consequente perda de dados, então há o **byte stuffing**: antes de cada flag que apareça nos dados, colocar um byte de escape ESC, até mesmo para o próprio byte de ESC. O receptor, antes de qualquer análise aos dados do frame, deverá fazer destuffing. É esta técnica a adoptar no caso do trabalho prático.

### 3 - Start and End flags with bit stuffing

Em vez de criar um byte, coloca-se um bit para travar qualquer interpretação errada. Por exemplo: se a flag for 0b01111110, então nos dados depois de cada 011111 colocar um 0 para evitar sequências iguais. De forma semelhante, o receptor só deverá interpretar os dados quando ocorrer destuffing.

## Error detection

Pode haver erros de um bit transmitido (*simple error*) ou de um grupo de bits transmitidos (*errors in bursts*). Estes últimos não são independentes e afetam os bits vizinhos.

### Probabilidades

- A probabilidade de um frame não conter erros, FER (Frame Error Ratio), é dado por FER = (1-BER)^n, com BER igual à probabilidade de um bit ter erros de transmissão (Bit Error Ratio) e n o comprimento do frame enviado. 

- A probabilidade de i bits conterem erros é igual à quantidade de escolhas possíveis nos n bits da trama vezes a probabilidade de n-i bits serem transmitidos bem e i bits serem transmitidos erradamente, com i <= n.

## Error technics

Nestes casos seguintes:
- `d`, significa o número de bits mínimo para que um erro não seja detectado num conjunto de dados transmitido;
- `D`, significa o número máximo de erros detectados num conjunto de bits;

### Redundância

Em vez de enviar um frame de k bits, envia um frame de k+r bits, com r a servir de redundância. Assim, do lado do receptor, pode haver um reconhecimento de um erro ocorrido num ou mais dos k bits de dados. 

#### Simple Parity Check

- Paridade par: verifica se o número de bits a 1 é par;
- Paridade ímpar: verifica se o número de bits a 1 é ímpar;

Nesta situação, apenas detecta erros simples ou erros derivados de um número ímpar de erros de transmissão. É muito usado em protocolos orientados a caracteres. 

#### Bi-dimensional Parity Check

Parecido com a situação anterior, mas a paridade é calculada por bloco, em linhas verticais e horizontais. Neste caso, qualquer erro numa configuração rectangular é indetectável, ou seja, d = 4. 

#### Cyclic Redundancy Check

A string de bits é representada por um polinómio M(x). Quando o número de bits em redundância é r, escolhemos uma string G(x) = x^r + 1 (r=3, s=1001), e fazemos uma divisão inteira de M(x) * x^r pelo polinómio G(x), que dará um polinómio R(x). O transmitido deverá ser M(x)*x^r + R(x). <br>
No lado do receptor, é só fazer a divisão inteira de T(x) por G(x). Se R(x) for diferente de zero, então algum erro ocorreu. 

É uma técnica muito usada, principalmente por ser facilmente implementada em software. Consegue detectar qualquer conjunto de 1,2 ou 3 erros (d > 3), todos os conjuntos com r ou menos bits e todos os erros que consistem num número ímpar de bits invertidos.

## Automatic Repeat Request (ARQ)

