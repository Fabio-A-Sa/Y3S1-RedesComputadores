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

Sistema que pede retransmissões de pacotes em falta ou com erros detectados. Existem três técnicas principais:

### 1 - Stop and Wait

O transmissor lança uma frame I e espera até que exista confirmação (ACK) do lado do receptor. Quando o receptor recebe o frame I, se este tiver erros lança um NACK, senão lança um ACK. Do outro lado é necessário existir um timeout e um número de tentativas fixas para prevenir erros de transmissão de mensagens. Caso receba um NACK, volta a enviar o frame anterior. 

#### Problema

Necessita de um conjunto sequencial de frames numerados, caso contrário os timeouts de um lado e do outro acabam por baralhar a transmissão. Neste caso apenas existem ACK(i) e o NACK não é necessário.

#### Eficiência

##### Sem erros

A eficiência mede-se através da razão entre o tempo de manipulação do frame por parte do receptor, Tf, e a soma entre Tf e os tempos de propagação, Tp. Ou seja, segundo esta fórmula:

> S = Tf / (Tf + 2*Tp)

##### Com erros

Designando pe pela probabilidade de ocorrência de um erro no frame, então a eficiência é dada pela seguinte fórmula:

> S = (1 - pe) / (Tf + 2*Tp)

### 2 - Go Back N

O problema do protocolo Stop and Wait é que em para longas distâncias, o tempo de transmissão é cada vez maior e acaba por diminuir bastante a eficiência. A ideia agora é estudar os `sliding window protocols`: permitem a transmissão de vários frames antes de começar a receber as confirmações do seu envio.

#### Transmissor

Pode transmitir W frames (W = 2^k-1, com k a ser o número de bits usados para codificar as sequências) e tem de esperar por alguma confirmação antes de transmitir o W+1 frame. 
Se um timeout ocorrer, o transmissor envia uma mensagem RR() para que o receptor indique qual é o índice do frame a enviar de seguida.

#### Receptor

Rejeita qualquer frame fora da sequência, enviando somente ACK(i) para indicar que os frames i-1 foram enviados correctamente. i é sempre o número de sequência do próximo frame esperado.

##### Eficiência

> S = W / (1+2a), se W < (1 + 2a), número de tramas que simultaneamente estão no cabo é inferior ao número de tramas da janela
> S = 1, caso contrário

### Selective Repeat

Usa a técnica da janela mas aceita tramas fora de ordem, ao contrário  do Go Back N. Usada para casose em que `W` ou `a` são muito elevados. O receptor sinaliza a falta/erro no frame i, enviando SREJ(i) ao emissor e continuando a guardar no buffer as tramas seguintes. O emissor continua a enviar tramas e retransmite apenas o que é pedido pelo receptor.

O tamanho da janela é agora W = M / 2 = 2^(k-1). Ou seja, o emissor pode enviar no máximo M/2 tramas sem confirmação por parte do receptor.
#TODO: justificação do livro, relacionado com timeout e com o buffer.

#TODO: eficiência

## Deteção de erros nas redes

### Ethernet

Os frames são compostos por um **preamble** de 7 octetos, seguido de uma flag SFD, DA e SA, seguida do comprimento em bytes da informação enviada e posteriormente por uma redundância CRC.

### Point to Point Protocol

A trama é delimitada por FLAG = 0x7E, existe byte stuffing com o ESC = 0x7D, algum tipo de deteção de erros (redundância e checksum), e um byte para endereço e outro para controlo. Semelhante ao implementado nas aulas de laboratório.

### Wireless LAN

No início da trama tem um conjunto de bytes de sincronização. Normalmente usa um polinómio gerador de 16 bits e ARQ de Stop and Wait.

### High-level Data Link Control


