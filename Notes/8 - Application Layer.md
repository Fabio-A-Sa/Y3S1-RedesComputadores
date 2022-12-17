# 8 - Application Layer

Esta camada define os tipos de mensagens trocadas, a sintaxe e semântica delas e as regras de envio e resposta por parte dos processos. Enquanto que os protocolos TCP e UDP não oferecem segurança, o TLS (*Transport Layer Security*) encripta todas as mensagens enviadas e torna a ligação ponta-a-ponta usando certificados como autenticadores.

## HTTP - Hypertext Transfer Protocol

É um protocolo que não tem estado, na medida em que o servidor não armazena informação de sessões ou pedidos anteriores. 

### HTTP Não persistente

Permite o envio e recepção de no máximo um objecto por conexão TCP. Sendo RTT o tempo para um pacote viajar do cliente para o servidor e voltar, então o tempo total para uma resposta é dado por:

> response_time = 2 * RTT + transfer_time <br>
> inicialização de uma conexão TCP (RTT) <br>
> pedido do ficheiro (RTT) <br>
> trasferência do ficheiro (transfer_time)  <br>

### HTTP Persistente

Permite troca de vários objectos numa única conexão TCP.