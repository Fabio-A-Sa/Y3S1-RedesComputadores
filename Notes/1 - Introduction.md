# 1 - Introduction of Computer Networks

As redes de computadores são utilizadas por diversos fins no nosso quotidiano (email, web, remote login, games, vídeos, streaming). <br>
Há, para isso, duas arquiteturas de aplicações principais:

## Application Architectures

### 1 - Client-server

O cliente comunica diretamente com o servidor (um always-on computer) mas não com outros clientes. O servidor têm um IP permanente e um nome conhecido. Um exemplo é a comunicação entre browsers e servidores, através de HTTP requests.

### 2 - Peer-to-peer (P2P)

Não há um servidor always-on mas sim sistemas arbitrários para comunicar diretamente (tal como outros clientes). Um exemplo é a distribuição de ficheiros: há torrent, que é um grupo de pessoas que partilham partes de um ficheiro, e o servidor, que é um tracker que controla quem faz parte do torrent.

## Tipos de Redes

As redes podem ser classificadas de acordo com a área/extensão de atuação:

1. **PAN - Personal Area Network**, 1 metro, bluetooth entre dispositivos de uma secretária;
2. **LAN - Local Area Network**, 10 metros a 1 quilómetro, no quarto, construção ou campus. É exemplo a rede da FEUP, que tem switches, routers e access points;
3. **MAN - Metropolitan Area Network**, 10 quilómetros, onde pode conter uma antena e servidores;
4. **WAN - Wide Area Network**, engloba um continente;
5. **Internet - no Planeta**, é um conjunto de redes conectadas;