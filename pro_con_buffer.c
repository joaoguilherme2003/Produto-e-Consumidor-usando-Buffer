#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void produzir(int i);
void consumir(int i);
int isEmpty();
int isFull();
int dado = 0, indice = 0, num_produtores = 0, num_consumidores = 0, limite = 0, tam_buffer = 0;
int buffer[2048];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int index_consumidor = 0, index_produtor = 0;
int j_prod = 0, l_con = 0;

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
    return 0;
}
void produzir(int i)
{
    pthread_mutex_lock(&mutex);
    if (indice == limite) {
        indice = 0;
    }
    dado = 2 * indice + 1;

    if (isFull() == 0) {
      while (1) {
          if (j_prod == tam_buffer) {
              j_prod = 0;
          }
          if (buffer[j_prod] == NULL) {
              printf("Produtor %d produzindo %d na posição %d\n", i, dado, j_prod);
              buffer[j_prod] = dado;
              j_prod++;
              break;
          }
          j_prod++;
      }
    }
    indice++;
    pthread_mutex_unlock(&mutex);
}
void consumir(int i)
{
    pthread_mutex_lock(&mutex);
    if(isEmpty() == 0){
          while (1) {
              if (l_con == tam_buffer) {
                  l_con = 0;
              }
              if (buffer[l_con] != NULL) {
                  printf("Consumidor %d consumindo %d na posição %d\n", i, buffer[l_con], l_con);
                  buffer[l_con] = NULL;
                  l_con++;
                  break;
              }
             l_con++;
        }
    }
    pthread_mutex_unlock(&mutex);
}
int isEmpty()
{
    for (int i = 0; i < tam_buffer; i++) {
        if (buffer[i] != NULL) {
            return 0;
        }
    }
    return  1;
}
int isFull()
{
    for (int i = 0; i < tam_buffer; i++) {
        if (buffer[i] == NULL) {
            return 0;
        }
    }
    return  1;
}
