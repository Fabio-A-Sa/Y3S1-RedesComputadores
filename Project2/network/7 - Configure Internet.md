# 2.7 Configure Internet

## Steps

1. Conectar 5.1 com o E0 do Tux53;
2. Em Tux53 executar os seguintes comandos:

    ```bash
    $ ifconfig eth0 172.16.1.53/24
    $ route add default gw 172.16.1.254
    ```