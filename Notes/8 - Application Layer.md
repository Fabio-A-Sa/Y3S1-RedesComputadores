# 8 - Application Layer

Esta camada define os tipos de mensagens trocadas, a sintaxe e semântica delas e as regras de envio e resposta por parte dos processos. Enquanto que os protocolos TCP e UDP não oferecem segurança, o TLS (*Transport Layer Security*) encripta todas as mensagens enviadas e torna a ligação ponta-a-ponta usando certificados como autenticadores.

## HTTP - Hypertext Transfer Protocol

É um protocolo que não tem estado, na medida em que o servidor não armazena informação de sessões ou pedidos anteriores. Os pedidos têm um cabeçalho, que evidencia o tipo de pedido (GET, POST, PUT, DELETE), e as respostas também podem conter corpo com o payload solicitado.<br>

O estado pode ser conhecido através de *cookies* e o sistema pode ser mais rápido com *proxy servers* que guardam as respostas HTTP anteriores em cache.

### HTTP Não persistente

Permite o envio e recepção de no máximo um objecto por conexão TCP. Sendo RTT o tempo para um pacote viajar do cliente para o servidor e voltar, então o tempo total para uma resposta é dado por:

> response_time = 2 * RTT + transfer_time <br>
> inicialização de uma conexão TCP (RTT) <br>
> pedido do ficheiro (RTT) <br>
> trasferência do ficheiro (transfer_time)  <br>

### HTTP Persistente

Permite troca de vários objectos numa única conexão TCP, ou seja, o servidor deixa a conexão aberta após mandar a resposta. Assim as mensagens seguintes entre o mesmo par cliente-servidor deixam de iniciar uma nova ligação TCP, poupando tempo. A persistência pode ser:
- `sem pipelining`, quando o cliente manda um request apenas quando recebe a resposta anterior, utilizando um RTT para cada novo pedido;
- `com pipelining`, quando o cliente manda vários requests sem esperar pela resposta, utilizando um RTT para todas as requests que enviar;

## Eletronic Mail

O serviço de email é constituido por três grandes pilares: os utilizadores, os servidores de email e o protocolo de transporte SMTP (*Simple Mail Transfer Protocol*). As mensagens enviadas ficam numa fila de espera para serem enviadas entre servidores antes de seguirem para o destino final. Usam conexões persistentes e as mensagens trocadas (cabeça e corpo) têm de ser codificadas em ASCII de 7 bits.

Usam-se ainda os protocolos:
- IMAP (*Internet Mail Access Protocol*), para manipulação das mensagens existentes no servidor. Guarda o estado entre sessões;
- POP3 (*Post Office Protocol*), para autorização de conexão entre o cliente e o servidor e para downloads de mensagens entre serviços. Não guarda o estado entre sessões;

## DNS - Domain Name System

É uma base de dados distribuída implementada com hierarquia que é capaz de traduzir os nomes dos servidores nos respectivos endereços IP. É descentralizada para não haver o ponto único de falha, por distribuição de tráfego e manutenção. Os servidores TLD (*Top Level Domain*) são responsáveis pelas terminações mais comuns de sites, enquanto os *Authoritative* são responsáveis por tradução de IPs de organizações de Web e Mail. Cada ISP contém um `Local Name Server`, que é o default.