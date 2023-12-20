//
//  main.cpp
//  negozio
//
//  Created by Alessandro masone on 06/03/22.
//

#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <unistd.h>
#include <random>
#include <vector>
#include <string.h>
#include <ncurses.h>
#include "define.h"
#include "class.h"
#include "funzioni.h"

int main(int argc, const char * argv[]) {

    bool fuori = false;
    int vettore[11] = {};
    thread stampanegozio;
    Funzione funzione;
    vector<vector<Mattonella>> mattonella;
    vector<Coda> coda;
    vector<Persona> persona;
    
    funzione.inputdati(vettore);
    
    if(vettore[0] < 5) {
        printf("Lato X troppo piccolo");
        return 1;
    }
    if(vettore[1] < 5) {
        printf("Lato Y troppo piccolo");
        return 2;
    }
    if(vettore[2] < 1) {
        printf("Numero di entrate non valido");
        return 3;
    }
    if(vettore[3] < 1) {
        printf("Numero di uscite non valido");
        return 4;
    }
    if(vettore[4] < 1) {
        printf("Numero di clienti non valido");
        return 5;
    }
    if(vettore[5] < 5) {
        printf("Tempo di arrivo non valido");
        return 6;
    }
    if(vettore[6] < 100000) {
        printf("Tempo di movimento minimo non valido");
        return 7;
    }
    if(vettore[7] < vettore[6]) {
        printf("Tempo di movimento massimo non valido");
        return 8;
    }
    if(vettore[8] < 1) {
        printf("Numero di clienti massimo non valido");
        return 9;
    }
    if(vettore[10] < 0 || vettore[10] > 2) {
        printf("Valore Degub non valido non valido");
        return 10;
    }
    if ((vettore[0]*vettore[1]) < vettore[8]) {
        printf("Numero di clienti massimo non valido");
        return 11;
    }
    if (((vettore[0]-1)+(vettore[1]-1)+(vettore[0]-1)+(vettore[1]-1)) < vettore[2]+vettore[3]) {
        printf("Numero entrate + uscite non valido");
        return 12;
    }
    
    funzione.assegnadimensioni(vettore[0], vettore[1]);
    funzione.assegnanumeroentrate(vettore[2]);
    funzione.assegnanumerouscite(vettore[3]);
    funzione.assegnanumeroclienti(vettore[4]);
    funzione.assegnatempoarrivo(vettore[5]);
    funzione.assegnarangetempo(vettore[6], vettore[7]);
    funzione.assegnadecisioneuscita(vettore[8]);
    funzione.inizializzapass(vettore[9]);
    
    funzione.inizializzadimensioninegozio(mattonella);
    funzione.assegnaentrate(mattonella);
    funzione.assegnauscite(mattonella);
    funzione.inizializzacoda(coda, mattonella, funzione.damminumeroclienti());
    funzione.inizializzaclienti(persona);
    
    stampanegozio = thread(&negoziostart, ref(mattonella), funzione.dammipassaporto(), ref(fuori), vettore[10]);
    funzione.generaclienti(mattonella, coda, persona, vettore[10]);
    funzione.uscitaclienti(persona);
    fuori = true;
    stampanegozio.join();
    
    return 0;
}
