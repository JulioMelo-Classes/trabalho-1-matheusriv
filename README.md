# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Jogo Keno

**Keno** é um jogo de apostas muito popular parecido com loteria ou bingo.

Os jogadores apostam escolhendo entre 1 e 15 números únicos no intervalo [1, 80] e definem o número de rodadas e a quantidade de crédito inicial, que será dividido entre as rodadas. 

Quando o jogador escolhe seus números, o algoritmo gera vinte números aleatórios entre 1 e 80. Baseado na quantidade de números que o jogador acertou, e no valor que ele apostou, ele recebe um valor de volta. Dessa forma, o jogador pode ganhar cerca de 1000 vezes o valor apostado!

# Como jogar

Para jogar este jogo você só precisa carregar seu arquivo de aposta na pasta `data`, o arquivo precisa ter uma extensão de texto simples (` .dat`, `.txt`, `...`).

Logo abaixo é possível visualizar um exemplo válido de texto para um arquivo de apostas.

```
1500.0
3
21 12 64
```

As três linhas ilustradas para arquivo de apostas significam, em ordem:
* Número real representando a quantidade de crédito inicial do jogador;
* Número inteiro representando a quantidade de rodadas que serão executadas;
* Conjunto de até 15 números inteiros únicos em qualquer ordem separados por espaço.

Quando algum requisito não for satisfeito, a aposta será rejeitada e uma mensagem de erro correspondente deverá ser impressa.

Após carregar seu arquivo de aposta, você deverá compilar o programa e executar o executável .

Para compilar, você só precisa colocar isso no terminal:

1. Entre na pasta de arquivo, no caso `data`:
```
cd build
```
2. Execute os comandos do `cmake` para gerar os arquivos intermediários e o executável dentro de `build`.
```
cmake ..
cmake --build .
```
Isso criará um executável dentro de `build` chamado de `KenoRun`.

Logo após a compilação, para executar o programa gerado use os comandos:

No linux:
```
./KenoRun nome_do_arquivo.dat
```
No windows:
```
KenoRun nome_do_arquivo.dat
```

Por exemplo, se o nome do seu arquivo for "aposta":
```
./KenoRun aposta.dat
```

Se nenhum arquivo de aposta foi especificado, o programa será executado com um arquivo de aposta demo (localizado em `data / default_bet.dat`).
