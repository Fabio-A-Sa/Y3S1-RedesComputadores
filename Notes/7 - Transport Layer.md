# 7 - Transport Layer

Nesta camada existem dois tipos de protocolos principais:

## User Datagram Protocol (UDP)

Permite que uma aplicação envie diretamente dados, que serão colocados dentro de pacotes na rede com o mínimo overhead possível. Não é aconselhado pois apesar de conseguir detectar erros, não consegue revertê-los (por exemplo em falhas no payload, erros de envio/recepção). O Header do protocolo contém o número a porta que identifica os processos de origem e destino, o tamanho da trama e um checksum. 

## Transmission Control Protocol (TCP)

É orientado às comunicações, full-duplex (permite transferência nos dois sentidos) e incorpora dois mecanismos de controlo: o Controlo de Fluxo, que permite ao receptor controlar o fluxo de emissão de pacotes, e o Controlo de congestionamento, onde os emissores de dados não geram mais tráfego do que é possível transportar na rede. <br>

Do lado do **emissor**, a informação será partida em fragmentos, e a cada segmento enviado espera por ACK. Sempre que atinge o timeout ou a resposta for NACK, reenvia o mesmo fragmento. Do lado do **receptor**, os erros serão detectados através do checksum, os segmentos serão ordenados e os duplicados descartados.

### Cabeçalho do TCP

- Número de portas, que são semelhantes ao UDP mas a transferência só começa a acontecer quando há comunicação estável estabelecida;
- Os números de sequência (*SeqNumber*) são números de 32 bits que identificam a ordem do primeiro byte a ser enviado na zona de tramas de informação. É no *handshake* que os números iniciais das sequence numbers são trocados;
- O *AckNumber* serve para indicar ao receptor qual é o próximo byte de resposta que está à espera (normalmente um byte a indicar um ACK) e garante a recepção correcta de todos os bytes de ordem inferior;
- Window size;
- Checksum, que cobre toda a trama (header e dados);

### Controlo de Fluxo

Os buffers do lado do receptor e do transmissor são finitos, pelo que não podem receber mais do que a sua capacidade porque senão há perda de pacotes. Sempre que o receptor recebe um pacote, verifica se tem espaço e lança na resposta um parâmetro, `Advertise Window`, indicando a quantidade de espaço em bytes que ainda tem disponível. O transmissor faz então resize da próxima payload enviada, considerando o valor dado pela resposta e os bytes já enviados e cuja resposta ainda não foi recebida. 

### Timeout

Quando as redes são extensas e desconhecidas, é difícil prever o timeout adequado de espera por uma resposta. Usa-se o mecanismo **Addaptative Retransmission**, que é um algoritmo iterativo:

> Com alpha = 0.125 <br>
> Tempo de espera i = (1-alpha) * (tempo de espera i - 1) + alpha * (tempo de espera da resposta recebida em i) <br>
> Timeout i = Tempo de espera i <br>

No entanto este mecanismo ainda não é suficiente, pois a variância pode fazer esperar mais do que necessário. Assim é também necessário calculá-la e ajustar o tempo de timeout:

> Com beta = 0.25 <br>
> Variância em i = (1-beta) * (variância em i - 1) + beta * (variância calculada em i - tempo de espera da resposta recebida em i) <br>
> Timeout i = Tempo de espera i + 4 * Variância em i <br>

Estes cálculos não são efetuados quando há retransmissão de segmentos para evitar ambiguidade (há casos onde não dá para saber qual é a trama a que se refere a resposta).

### Selective ACK

Há adição de uma bit mask dos pacotes recebidos, de forma a que a resposta contenha um identificador de qual trama se refere. Assim há retransmissão apenas dos pacotes selecionados e não todos.

### Controlo de Congestionamento

Cada emissor determina a capacidade da comunicação para poder enviar mais ou menos pacotes. Para isso há mais um parâmetro na conexão (*CongestionWindow*):

> MaxWin = MIN(CongestionWindow, AdvertisedWindow) <br>
> EffWin = MaxWin - (LastByteSent - LastByteAcked) <br>
> Bitrate = CongestionWindow / Round Trip Time <br>

Assim, se o nível de congestionamento da rede aumenta a CongestionWindow diminui e vice-versa.

#### Como verificar a existência de congestionamento ?

Uma rede diz-se congestionada a partir do momento que se perdem pacotes. É necessário o envio de vários pacotes de uma vez (*Additive Increase*) até que tal aconteça. Usa-se `slow start` quando em vez de adicionar uma unidade à CongestionWindow em cada transmissão, usa-se o mesmo método mas em modo exponencial na base dois. A perda do pacote pode ser dada:

- Por `timeout`. Ocorre um *Multiplicative Decrease*, passando a Congestion Window a 1 e aumentando novamente até metade do valor obtido por mecanismo de slow start. A partir de metade o *Additive Increase* passa a ser incremental de uma unidade;
- Por `3 ACKs seguidos`. Ocorre um *Multiplicative Decrease*, passando a Congestion Window a metade e *Additive Increase* passa a ser incremental de uma unidade;