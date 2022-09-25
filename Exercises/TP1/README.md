# Aula TP1 2022/09/19

## Funcionamento da serial port no laboratório

No nosso caso, zona de computadores 5 da sala I320, no switch devemos escolher o computador 3. A transmissão de mensagens de um computador para outro deu-se pelo modo não canónico, executando os seguintes comandos:

```bash
# No computador emissor:
$ gcc -Wall write_noncanonical.c -o writer
$ ./writer /dev/ttyS0

# No computador receptor:
$ gcc -Wall read_noncanonical.c -o reader
$ ./reader /dev/ttyS0
```

## Funcionamento da serial port nos nossos computadores

Convém ter a dependência `socat` instalada no Linux:

```bash
$ sudo apt-get install socat
```

O programa em C `cable` trata de construir uma porta série virtual. Para isso:

```bash
$ gcc -Wall cable.c -o cable
$ /cable
```

Depois é só abrir mais dois terminais (um emissor e outro receptor) e executar o seguinte código:

```bash
# Emissor
gcc -Wall write_noncanonical.c -o writer && ./writer /dev/ttyS10

# Receptor
$ gcc -Wall read_noncanonical.c -o reader && ./reader /dev/ttyS11
```

É suposto escrever no emissor uma mensagem de no máximo X caracteres e essa mensagem aparecer. Depois essa mensagem.