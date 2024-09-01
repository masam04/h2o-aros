#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define MOLEKULI 10

int kiseonik=0;
int vodonik=0;
int spremniZaVezu = 0;

sem_t mutex;
sem_t kiseonikSemafor;
sem_t vodonikSemafor;

int ulazakUHemijskuVezu() {

    spremniZaVezu++;

    if(spremniZaVezu % 3 == 0) {
        printf("Molekul H2O je formiran 🌊\n");
        spremniZaVezu = 0;
    }

    sleep(2);
    return 0;

}

void* funkcijaKiseonika() {

        int sekundiCekanja = rand() % 15;
        sleep(sekundiCekanja);

        printf("Kiseonik se pojavljuje! 🧪\n");

        sem_wait(&mutex);
        kiseonik+=1;

        if(vodonik>=2) {
            sem_post(&vodonikSemafor);
            sem_post(&vodonikSemafor);
            vodonik-=2;
            sem_post(&kiseonikSemafor);
            kiseonik-=1;
        }
        else {
            sem_post(&mutex);
        }
        
        sem_wait(&kiseonikSemafor);
        printf("Kiseonik je stigao u molekulnu vezu!\n");

        ulazakUHemijskuVezu();
        sem_post(&mutex);

}

void* funkcijaVodonika() {

        int sekundiCekanja = rand() % 15;
        sleep(sekundiCekanja);

        printf("Vodonik se pojavljuje! 🧪\n");

        sem_wait(&mutex);
        vodonik+=1;

        if(vodonik>=2 && kiseonik>=1) {
            sem_post(&vodonikSemafor);
            sem_post(&vodonikSemafor);
            vodonik-=2;
            sem_post(&kiseonikSemafor);
            kiseonik-=1;
        }
        else {
            sem_post(&mutex);
        }

        sem_wait(&vodonikSemafor);
        printf("Vodonik je stigao u molekulnu vezu!\n");
        ulazakUHemijskuVezu();

}

int main(void) {

    printf("Početak H2O projekta! 🧪\n");
    
    sem_init(&mutex,0,1);
    sem_init(&kiseonikSemafor,0,0);
    sem_init(&vodonikSemafor,0,0);
    
    pthread_t kiseonici[MOLEKULI];
    pthread_t vodonici[2*MOLEKULI];

    for (int i=0; i<MOLEKULI; i++) {
        pthread_create(&kiseonici[i], NULL, funkcijaKiseonika, NULL);
    }

    for (int i=0; i<2*MOLEKULI; i++) {
        pthread_create(&vodonici[i], NULL, funkcijaVodonika, NULL);
    }
 
    for(int i = 0; i < MOLEKULI; i++) {
        pthread_join(kiseonici[i], NULL);
    }

    for(int i = 0; i < 2*MOLEKULI; i++) {
        pthread_join(vodonici[i], NULL);
    }

    printf("\n\nUkupno je kreirano %d molekula! ⚛️",MOLEKULI);
    return 0;
}