#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void produzir(int i);
void consumir(int i);
int dado = 0, indice = 0;
int num_produtores = 0, num_consumidores = 0, limite = 0, tam_buffer = 0;
int buffer[1024];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int index_consumidor = 0, index_produtor = 0;

int main ()
{
    scanf("%d %d %d %d", &num_produtores, &num_consumidores, &limite, &tam_buffer);
    
    pthread_t produtor_t[num_produtores];
    pthread_t consumidor_t[num_consumidores];

    while (1) {
      for (int i = 0; i < num_produtores; i++) {
          pthread_create(&(produtor_t[i]), NULL, produzir, i);
      }
      for (int i = 0; i < num_consumidores; i++) {
          pthread_create(&(consumidor_t[i]), NULL, consumir, i);
      }
      for (int i = 0; i < num_produtores; i++) {
          pthread_join(produtor_t[i], NULL);
      }
      for (int i = 0; i < num_consumidores; i++) {
          pthread_join(consumidor_t[i], NULL);
      }
    }
}
void produzir(int i)
{
    pthread_mutex_lock(&mutex);
    if (indice == limite) {
        indice = 0;
    }
    dado = 2 * indice + 1;
    for (int j = 0; j < tam_buffer; j++) {
        if (buffer[j] == NULL) {
            printf("Produtor %d produzindo %d na posição %d\n", i, dado, j);
            buffer[j] = dado;
            break;
        }
    }
    indice++;
    pthread_mutex_unlock(&mutex);
}
void consumir(int i)
{
    pthread_mutex_lock(&mutex);
    for (int l = 0; l < tam_buffer; l++) {
        if (buffer[l] != NULL) {
            printf("Consumidor %d consumindo %d na posição %d\n", i, buffer[l], l);
            buffer[l] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}