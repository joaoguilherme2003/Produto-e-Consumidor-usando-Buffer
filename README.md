# Produto-e-Consumidor-usando-Buffer

Este algoritmo executa um sistema de produtores e consumidores.
Primeiramente o usuario insere parâmetro o número de produtores , o número de
consumidores , um limite , e B que representa o tamanho do buffer.
Os produtores inserem no buffer os dados, e os consumidores retiram do buffer os dados.
Cada produtor e consumidor é uma thread diferente.
Os dados inseridos são calculados por meio da função f(x) = 2x + 1, em que x é incrementado e zerado quando chega no valor inserido pelo usuario.
O codigo roda de uma forma infinita e as threads de produção e consumo estão sempre rodando em ordem aleatoria.

## Funções de bibliotecas de threads

Foram usadas para organizar as threads, impedindo delas executem ao mesmo tempo:
```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&mutex);

pthread_mutex_unlock(&mutex);
```
Foram usadas para criar e encerrar as threads:
```c
pthread_create()
pthread_join();
```

## makefile

Make = Cria o aplicativo binario do codigo.

Make run = Executa o aplicativo.

Make clean = Apaga o aplicativo binario.

### Compile
```c
$ make
```
### Run
```c
$ make run
```
### Clean
```c
$ make clean
```
