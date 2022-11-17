# 7 - Transport Layer

Nesta camada existem dois tipos de protocolos principais:

## User Datagram Protocol (UDP)

Permite que uma aplicação envie diretamente dados, que serão colocados dentro de pacotes na rede com o mínimo overhead possível. Não é aconselhado pois apesar de conseguir detectar erros, não consegue revertê-los (por exemplo em falhas no payload, erros de envio/recepção). O Header do protocolo contém o número a porta que identifica os processos de origem e destino, o tamanho da trama e um checksum. 

### Transmission Control Protocol (TCP)

É orientado às comunicações, full-duplex (permite transferência nos dois sentidos) e incorpora dois mecanismos de controlo: o Controlo de Fluxo, que permite ao receptor controlar o fluxo de emissão de pacotes, e o Controlo de congestionamento, onde os emissores de dados não geram mais tráfego do que é possível transportar na rede. <br>

Do lado do **emissor**, a informação será partida em fragmentos, e a cada segmento enviado espera por ACK. Sempre que atinge o timeout ou a resposta for NACK, reenvia o mesmo fragmento. Do lado do **receptor**, os erros serão detectados através do checksum, os segmentos serão ordenados e os duplicados descartados.

## Cabeçalho do TCP

- Número de portas, que são semelhantes ao UDP;
- Os números de sequência (*SeqNumber*) são números de 32 bits que identificam os dados contidos no segmento;
- O *AckNumber* serve para indicar ao receptor qual é o próximo byte de respota que está à espera (normalmente um byte a indicar um ACK);
- Window size;
- Checksum;