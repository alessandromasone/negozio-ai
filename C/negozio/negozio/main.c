//
//  main.c
//  negozio
//
//  Created by Alessandro masone on 06/03/22.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ncurses.h>

#define DIMENSIONI_LATO_X 10
#define DIMENSIONI_LATO_Y 10
#define NUMERO_ENTRATE 3
#define NUMERO_USCITE 3
#define NUMERO_CLIENTI 10
#define TEMPO_DI_ARRIVO 5
#define MOVIMENTO_TEMPO_MINIMO 250000
#define MOVIMENTO_TEMPO_MASSIMO 500000
#define DECISIONE_USCITA 100
#define MASSIMO_CLIENTI 5
#define DEBUGS 0

#define NULLO -1
#define VUOTO 0
#define ENTRATA 1
#define USCITA 2
#define SCAFFALE 3
#define BAGNATO 4
#define PERSONA 5

#define FERMO 0
#define SOPRA 1
#define SOTTO 2
#define DESTRA 3
#define SINISTRA 4



typedef struct _Coordinate {
    int x;
    int y;
}Coordinate;

typedef struct _Passaport {
    int utente;
    pthread_mutex_t pass;
}Passaport;

typedef struct _Mattonella {
    int tipo;
    int utente;
    pthread_mutex_t disponibile;
}Mattonella;

typedef struct _Coda {
    int identificativo;
    int identificativo_utente[NUMERO_CLIENTI];
    Coordinate entrata;
    pthread_mutex_t posto[NUMERO_CLIENTI];
}Coda;

typedef struct _Persona {
    pthread_t thread;
    int identificativo;
    int coda;
    int velocita;
    Coordinate uscita;
    Coordinate entrata;
    int direzione;
    Coordinate posizione;
    int pass;
    int spostamenti;
}Persona;

bool fuori = false;
pthread_t stampanegozio;
Mattonella mattonella[DIMENSIONI_LATO_X][DIMENSIONI_LATO_Y];
Coda coda[NUMERO_ENTRATE];
Persona persona[NUMERO_CLIENTI];
Passaport semaforo[MASSIMO_CLIENTI];
int type = DEBUGS;
int contaclienti = 0;
pthread_mutex_t stampa, calc;

#include "funzioni.h"

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    pthread_mutex_init(&stampa, NULL);
    pthread_mutex_init(&calc, NULL);
    inizializzadimensioninegozio();
    assegnaentrate();
    assegnauscite();
    inizializzacoda();
    inizializzaclienti();
    inizializzapass();
    
    pthread_create(&stampanegozio, NULL, negoziostart, NULL);
    generaclienti();
    uscitaclienti();
    fuori = true;
    pthread_join(stampanegozio, NULL);
    
    return 0;
}
