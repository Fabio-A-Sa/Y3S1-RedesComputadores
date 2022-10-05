# Data Link layer

É a camada que permite a comunicação entre máquinas adjacentes. O seu objectivo é reduzir e eliminar os erros de transmissão que podem ocorrer na physical layer e regular o fluxo de dados.

## Framing

Os dados enviados devem ser separados em frames / pacotes para regular o fluxo de dados e reduzir a possibilidade de erros, com posterior retransmissão caso ocorram. Para isso há três técnicas que são usadas:

### 1 - Character byte count

