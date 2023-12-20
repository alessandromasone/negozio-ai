//
//  funzioni.h
//  negozio
//
//  Created by Alessandro masone on 06/03/22.
//

#ifndef funzioni_h
#define funzioni_h

/// Assegna i valori predefiniti alle mattonelle del negozio
void inizializzadimensioninegozio(void) {
    for (int x = 0; x < DIMENSIONI_LATO_X; x++) {
        for (int y = 0; y < DIMENSIONI_LATO_Y; y++) {
            mattonella[x][y].utente = -1;
            pthread_mutex_init(&mattonella[x][y].disponibile, NULL);
            mattonella[x][y].tipo = VUOTO;
        }
    }
}
/// Randomiza un vettore di tutti numeri casuali
/// @param a vettore da randomizzare
/// @param max valore massimo
/// @param size dimensione del vettore
void randomizzavettore(int a[], int max, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = rand() % max;
        for (int j = 0; j < i; j++) {
            if (a[i] == a[j]) {
                i--;
                break;
            }
        }
    }
}
/// Perimetro del negozio
int calcolaperimentro(void) {
    return ((DIMENSIONI_LATO_X-1)+(DIMENSIONI_LATO_Y-1)+(DIMENSIONI_LATO_X-1)+(DIMENSIONI_LATO_Y-1));
}
/// Assegnazione delle entrate sul perimetro
void assegnaentrate(void) {
    int lunghezzabordi = calcolaperimentro();
    int a[NUMERO_ENTRATE];
    randomizzavettore(a, lunghezzabordi, NUMERO_ENTRATE);
    int numeroassegnamento = 0;
    lunghezzabordi = 0;
    for (int x = 0; x < DIMENSIONI_LATO_X; x++) {
        for (int y = 0; y < DIMENSIONI_LATO_Y; y++) {
            if (x == 0 || x == DIMENSIONI_LATO_X-1) {
                if (mattonella[x][y].tipo == 0) {
                    for (int z = 0; z < NUMERO_ENTRATE; z++) {
                        if (lunghezzabordi == a[z]) {
                            mattonella[x][y].tipo = ENTRATA;
                            numeroassegnamento++;
                        }
                    }
                    lunghezzabordi++;
                }
            }
            else if (y == 0 || y == DIMENSIONI_LATO_Y-1) {
                if (mattonella[x][y].tipo == 0) {
                    for (int z = 0; z < NUMERO_ENTRATE; z++) {
                        if (lunghezzabordi == a[z]) {
                            mattonella[x][y].tipo = ENTRATA;
                            numeroassegnamento++;
                        }
                    }
                    lunghezzabordi++;
                }
            }
        }
    }
}
/// Assegnazione delle uscite sul perimetro
void assegnauscite(void) {
    int lunghezzabordi = calcolaperimentro();
    int a[NUMERO_USCITE];
    randomizzavettore(a, lunghezzabordi, NUMERO_USCITE);
    int numeroassegnamento = 0;
    lunghezzabordi = 0;
    for (int x = 0; x < DIMENSIONI_LATO_X; x++) {
        for (int y = 0; y < DIMENSIONI_LATO_Y; y++) {
            if (x == 0 || x == DIMENSIONI_LATO_X-1) {
                if (mattonella[x][y].tipo == 0) {
                    for (int z = 0; z < NUMERO_USCITE; z++) {
                        if (lunghezzabordi == a[z]) {
                            mattonella[x][y].tipo = USCITA;
                            numeroassegnamento++;
                        }
                    }
                    lunghezzabordi++;
                }
            }
            else if (y == 0 || y == DIMENSIONI_LATO_Y-1) {
                if (mattonella[x][y].tipo == 0) {
                    for (int z = 0; z < NUMERO_USCITE; z++) {
                        if (lunghezzabordi == a[z]) {
                            mattonella[x][y].tipo = USCITA;
                            numeroassegnamento++;
                        }
                    }
                    lunghezzabordi++;
                }
            }
        }
    }
}
/// Inizializzazione della coda con i valori nulli e tutti i posti liberi
void inizializzacoda(void) {
    for (int i = 0; i < NUMERO_ENTRATE; i++) {
        coda[i].identificativo = i;
        for (int j = 0; j < NUMERO_CLIENTI; j++) {
            coda[i].identificativo_utente[j] = -1;
            pthread_mutex_init(&coda[i].posto[j], NULL);
        }
    }
    int z = 0;
    for (int x = 0; x < DIMENSIONI_LATO_X; x++) {
        for (int y = 0; y < DIMENSIONI_LATO_Y; y++) {
            if (mattonella[x][y].tipo == ENTRATA) {
                coda[z].entrata.x = x;
                coda[z].entrata.y = y;
                z++;
            }
        }
    }
}
/// Valori predefiniti per i clienti
void inizializzaclienti(void) {
    for (int i = 0; i < NUMERO_CLIENTI; i++) {
        persona[i].identificativo = i;
        persona[i].direzione = FERMO;
        persona[i].spostamenti = 0;
        persona[i].velocita = rand() % MOVIMENTO_TEMPO_MASSIMO + MOVIMENTO_TEMPO_MINIMO;
    }
}
/// Valori per i pass
void inizializzapass(void) {
    for (int i = 0; i < MASSIMO_CLIENTI; i++) {
        semaforo[i].utente = -1;
        pthread_mutex_init(&semaforo[i].pass, NULL);
    }
}
/// Azioni del clienti
/// @param identificativo numero cliente
void *azionicliente(int identificativo) {
    ///Attesa arrivo cliente al negozio
    int e = rand() % TEMPO_DI_ARRIVO +1;
    if (type == 2) {
        pthread_mutex_lock(&stampa);
        printf("%i: Tempo di attesa per l'arrivo %i\n", identificativo, e);
        pthread_mutex_unlock(&stampa);
    }
    ///Calcolo lunghezza delle varie code
    sleep(e);
    if (type == 2) {
        pthread_mutex_lock(&stampa);
        printf("%i: Calcolo lunghezze code\n", identificativo);
        pthread_mutex_unlock(&stampa);
    }
    int lunghezzacoda[NUMERO_ENTRATE];
    for (int i = 0; i < NUMERO_ENTRATE; i++) {
        lunghezzacoda[i] = 0;
        for (int j = 0; j < NUMERO_CLIENTI; j++) {
            if (coda[i].identificativo_utente[j] != -1) {
                lunghezzacoda[i]++;
            }
        }
    }
    ///Sort per la coda più piccola
    int codaminore = 0;
    for (int i = 1; i < NUMERO_ENTRATE; i++) {
        if (lunghezzacoda[i] < lunghezzacoda[codaminore]) {
            codaminore = i;
        }
    }
    if (type == 2) {
        pthread_mutex_lock(&stampa);
        printf("%i: Coda minore %i\n", identificativo, codaminore);
        pthread_mutex_unlock(&stampa);
    }
    persona[identificativo].coda = codaminore;
    ///Presa di posizione all'interno della coda minore
    int posizionecoda;
    for (int j = 0; ; j++) {
        if (pthread_mutex_trylock(&coda[codaminore].posto[j]) == 0) {
            posizionecoda = j;
            coda[codaminore].identificativo_utente[j] = identificativo;
            if (type == 2) {
                pthread_mutex_lock(&stampa);
                printf("%i: Posizione nella coda %i\n", identificativo, j);
                pthread_mutex_unlock(&stampa);
            }
            break;
        }
    }
    ///Scala di posto fino all'arrivo del prima posto utile per acceidere al pass/entrata negozio
    while (true) {
        if (posizionecoda > 0) {
            if (pthread_mutex_trylock(&coda[codaminore].posto[posizionecoda-1]) == 0) {
                if (type == 2) {
                    pthread_mutex_lock(&stampa);
                    printf("%i: Posizione nella coda %i\n", identificativo, posizionecoda);
                    pthread_mutex_unlock(&stampa);
                }
                coda[codaminore].identificativo_utente[posizionecoda] = -1;
                pthread_mutex_unlock(&coda[codaminore].posto[posizionecoda]);
                posizionecoda--;
                coda[codaminore].identificativo_utente[posizionecoda] = identificativo;
            }
        }
        else {
            break;
        }
    }
    ///Presa del pass per il cliente
    int pass = -1;
    while (true) {
        for (int i = 0; i < MASSIMO_CLIENTI; i++) {
            if (pthread_mutex_trylock(&semaforo[i].pass) == 0) {
                pass = i;
                semaforo[pass].utente = identificativo;
                pthread_mutex_unlock(&coda[codaminore].posto[posizionecoda]);
                pthread_mutex_lock(&mattonella[coda[codaminore].entrata.x][coda[codaminore].entrata.y].disponibile);
                mattonella[coda[codaminore].entrata.x][coda[codaminore].entrata.y].utente = identificativo;
                persona[identificativo].entrata.x = coda[codaminore].entrata.x;
                persona[identificativo].entrata.y = coda[codaminore].entrata.y;
                persona[identificativo].posizione.x = coda[codaminore].entrata.x;
                persona[identificativo].posizione.y = coda[codaminore].entrata.y;
                pthread_mutex_lock(&calc);
                contaclienti++;
                pthread_mutex_unlock(&calc);
                if (type == 2) {
                    pthread_mutex_lock(&stampa);
                    printf("%i: Presa del pass numero %i\n", identificativo, pass);
                    pthread_mutex_unlock(&stampa);
                    pthread_mutex_lock(&stampa);
                    printf("Clienti dentro %i\n", contaclienti);
                    pthread_mutex_unlock(&stampa);
                }
                break;
            }
        }
        if (pass != -1) {
            break;
        }
    }
    ///Movimento e decisione di uscite del cliente
    while (true) {
        int decisione = 0;
        int direzione = FERMO;
        direzione = rand() % 4 + 1;
        if (type == 2) {
            pthread_mutex_lock(&stampa);
            printf("%i: Posizione attuale %i.%i\n", identificativo, persona[identificativo].posizione.x, persona[identificativo].posizione.y);
            pthread_mutex_unlock(&stampa);
        }
        switch (direzione) {
            case SOPRA:
                if (persona[identificativo].posizione.y +1 > DIMENSIONI_LATO_Y-1) {
                }
                else {
                    if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y+1].disponibile) == 0) {
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                        pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                        persona[identificativo].posizione.y++;
                        persona[identificativo].spostamenti++;
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                    }
                }
                break;
            case SOTTO:
                if (persona[identificativo].posizione.y -1 < 0) {
                }
                else {
                    if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y-1].disponibile) == 0) {
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                        pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                        persona[identificativo].posizione.y--;
                        persona[identificativo].spostamenti++;
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                    }
                }
                break;
            case DESTRA:
                if (persona[identificativo].posizione.x +1 > DIMENSIONI_LATO_X-1) {
                }
                else {
                    if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x+1][persona[identificativo].posizione.y].disponibile) == 0) {
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                        pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                        persona[identificativo].posizione.x++;
                        persona[identificativo].spostamenti++;
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                    }
                }
                break;
            case SINISTRA:
                if (persona[identificativo].posizione.x -1 < 0) {
                }
                else {
                    if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x-1][persona[identificativo].posizione.y].disponibile) == 0) {
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                        pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                        persona[identificativo].posizione.x--;
                        persona[identificativo].spostamenti++;
                        mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                    }
                }
                break;
            default:
                break;
        }
        usleep(persona[identificativo].velocita);
        decisione = rand() % DECISIONE_USCITA;
        if (decisione == 1) {
            Coordinate vecchie;
            vecchie.x = persona[identificativo].posizione.x;
            vecchie.y = persona[identificativo].posizione.y;
            if (type == 2) {
                pthread_mutex_lock(&stampa);
                printf("%i: Decisione uscite\n", identificativo);
                pthread_mutex_unlock(&stampa);
            }
            int decisione_uscita = 0;
            int temp = 0;
            decisione_uscita = rand() % NUMERO_USCITE;
            for (int x = 0; x < DIMENSIONI_LATO_X; x++) {
                for (int y = 0; y < DIMENSIONI_LATO_Y; y++) {
                    if (mattonella[x][y].tipo == USCITA) {
                        if (decisione_uscita == temp) {
                            persona[identificativo].uscita.x = x;
                            persona[identificativo].uscita.y = y;
                        }
                        temp++;
                    }
                }
            }
            int temp2 = 0;
            int temp3 = 0;
            int fermo = 0;
            while (true) {
                if (type == 2) {
                    pthread_mutex_lock(&stampa);
                    printf("%i: Posizione attuale %i.%i\n", identificativo, persona[identificativo].posizione.x, persona[identificativo].posizione.y);
                    pthread_mutex_unlock(&stampa);
                }
                if (fermo == 1) {
                    direzione = rand() % 4 + 1;
                    if (temp3 > 2) {
                        fermo = 0;
                        temp3 = 0;
                    }
                    else {
                        temp3++;
                    }
                }
                else {
                    e = rand() % 2;
                    if (e == 0) {
                        if (persona[identificativo].uscita.x > persona[identificativo].posizione.x) {
                            direzione = DESTRA;
                        }
                        else if (persona[identificativo].uscita.x < persona[identificativo].posizione.x) {
                            direzione = SINISTRA;
                        }
                        else {
                            direzione = FERMO;
                        }
                    }
                    else {
                        if (persona[identificativo].uscita.y > persona[identificativo].posizione.y) {
                            direzione = SOPRA;
                        }
                        else if (persona[identificativo].uscita.y < persona[identificativo].posizione.y) {
                            direzione = SOTTO;
                        }
                        else {
                            direzione = FERMO;
                        }
                    }
                }
                switch (direzione) {
                    case SOPRA:
                        if (persona[identificativo].posizione.y +1 > DIMENSIONI_LATO_Y-1) {
                        }
                        else {
                            if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y+1].disponibile) == 0) {
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                                pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                                persona[identificativo].posizione.y++;
                                persona[identificativo].spostamenti++;
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                            }
                        }
                        break;
                    case SOTTO:
                        if (persona[identificativo].posizione.y -1 < 0) {
                        }
                        else {
                            if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y-1].disponibile) == 0) {
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                                pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                                persona[identificativo].posizione.y--;
                                persona[identificativo].spostamenti++;
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                            }
                        }
                        break;
                    case DESTRA:
                        if (persona[identificativo].posizione.x +1 > DIMENSIONI_LATO_X-1) {
                        }
                        else {
                            if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x+1][persona[identificativo].posizione.y].disponibile) == 0) {
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                                pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                                persona[identificativo].posizione.x++;
                                persona[identificativo].spostamenti++;
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                            }
                        }
                        break;
                    case SINISTRA:
                        if (persona[identificativo].posizione.x -1 < 0) {
                        }
                        else {
                            if (pthread_mutex_trylock(&mattonella[persona[identificativo].posizione.x-1][persona[identificativo].posizione.y].disponibile) == 0) {
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                                pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                                persona[identificativo].posizione.x--;
                                persona[identificativo].spostamenti++;
                                mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = identificativo;
                            }
                        }
                        break;
                    default:
                        break;
                }
                if (persona[identificativo].uscita.x == persona[identificativo].posizione.x && persona[identificativo].uscita.y == persona[identificativo].posizione.y) {
                    mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].utente = -1;
                    pthread_mutex_unlock(&mattonella[persona[identificativo].posizione.x][persona[identificativo].posizione.y].disponibile);
                    if (type == 2) {
                        pthread_mutex_lock(&stampa);
                        printf("%i: Uscite presa\n", identificativo);
                        pthread_mutex_unlock(&stampa);
                    }
                    break;
                }
                if (persona[identificativo].posizione.x == vecchie.x && persona[identificativo].posizione.y == vecchie.y) {
                    temp2++;
                    if (temp2 > 2) {
                        
                        fermo = 1;
                    }
                    else {
                        fermo = 0;
                        }
                }
                else {
                    vecchie.x = persona[identificativo].posizione.x;
                    vecchie.y = persona[identificativo].posizione.y;
                }
                usleep(persona[identificativo].velocita);
            }
            break;
        }
    }
    ///Rilascio risorse utili
    if (type == 2) {
        pthread_mutex_lock(&stampa);
        printf("%i: Rilascio del pass %i\n", identificativo, pass);
        pthread_mutex_unlock(&stampa);
    }
    semaforo[pass].utente = -1;
    pthread_mutex_unlock(&semaforo[pass].pass);
    pthread_mutex_lock(&calc);
    contaclienti--;
    if (type == 2) {
        pthread_mutex_lock(&stampa);
        printf("Clienti dentro %i\n", contaclienti);
        pthread_mutex_unlock(&stampa);
    }
    pthread_mutex_unlock(&calc);
    pthread_exit(NULL);
}

/// Generazione dei clienti
void generaclienti(void) {
    for (int i = 0; i < NUMERO_CLIENTI; i++) {
        pthread_create(&persona[i].thread, NULL, &azionicliente, i);
    }
}

/// Attesa clienti
void uscitaclienti(void) {
    for (int i = 0; i < NUMERO_CLIENTI; i++) {
        pthread_join(persona[i].thread, NULL);
    }
}


/// Stampa del negozio
void negoziostart(void) {
    if (type == 1) {
        while (1) {
            initscr();
            refresh();
            move(0,0);
            for (int i = 0; i < DIMENSIONI_LATO_X; i++) {
                for (int j = 0; j < DIMENSIONI_LATO_Y; j++) {
                    if (mattonella[i][j].tipo == ENTRATA) {
                        if (mattonella[i][j].tipo != -1) {
                            for (int k = 0; k < MASSIMO_CLIENTI; k++) {
                                if (mattonella[i][j].utente == semaforo[k].utente) {
                                    printw("[%i]", k+1);
                                }
                            }
                        }
                        else {
                            printw("[E]");
                        }
                    }
                    else if (mattonella[i][j].tipo == USCITA) {
                        if (mattonella[i][j].tipo != -1) {
                            for (int k = 0; k < MASSIMO_CLIENTI; k++) {
                                if (mattonella[i][j].utente == semaforo[k].utente) {
                                    printw("[%i]", k+1);
                                }
                            }
                        }
                        else {
                            printw("[U]");
                        }
                    }
                    else {
                        if (mattonella[i][j].tipo == -1) {
                            printw("[ ]");
                        }
                        else {
                            for (int k = 0; k < MASSIMO_CLIENTI; k++) {
                                if (mattonella[i][j].utente == semaforo[k].utente) {
                                    printw("[%i]", k+1);
                                }
                            }
                        }
                    }
                }
                printw("\n");
            }
            for (int f = 0; f < MASSIMO_CLIENTI; f++) {
                if (semaforo[f].utente == -1) {
                    printw("PASS %i NON ASSEGNATO\n", f+1);
                }
                else {
                    printw("PASS %i IN MANO AL CLIENTE %i\n", f+1, semaforo[f].utente);
                }
            }
            if (fuori) {
                break;
            }
        }
        endwin();
    }
    if (type == 0){

        while (1) {
            initscr();
            refresh();
            start_color();
            init_pair(1, COLOR_RED, COLOR_WHITE); //persona
            init_pair(2, COLOR_GREEN, COLOR_WHITE); //entrata
            init_pair(3, COLOR_BLUE, COLOR_WHITE); //uscita
            init_pair(4, COLOR_WHITE, COLOR_WHITE); //vuoto
            move(0,0);
            for (int i = 0; i < DIMENSIONI_LATO_X; i++) {
                for (int j = 0; j < DIMENSIONI_LATO_Y; j++) {
                    if (mattonella[i][j].tipo == ENTRATA) {
                        if (mattonella[i][j].utente != -1) {
                            attron(COLOR_PAIR(1));
                            for (int k = 0; k < MASSIMO_CLIENTI; k++) {
                                if (mattonella[i][j].utente == semaforo[k].utente) {
                                    printw(" %i ", k+1);
                                }
                            }
                            attroff(COLOR_PAIR(1));
                            
                        }
                        else {
                            attron(COLOR_PAIR(2));
                            printw(" E ");
                            attroff(COLOR_PAIR(2));
                        }
                    }
                    else if (mattonella[i][j].tipo == USCITA) {
                        if (mattonella[i][j].utente != -1) {
                            attron(COLOR_PAIR(1));
                            for (int k = 0; k < MASSIMO_CLIENTI; k++) {
                                if (mattonella[i][j].utente == semaforo[k].utente) {
                                    printw(" %i ", k+1);
                                }
                            }
                            attroff(COLOR_PAIR(1));
                        }
                        else {
                            attron(COLOR_PAIR(3));
                            printw(" U ");
                            attroff(COLOR_PAIR(3));
                        }
                    }
                    else {
                        if (mattonella[i][j].utente == -1) {
                            attron(COLOR_PAIR(4));
                            printw("[ ]");
                            attroff(COLOR_PAIR(4));
                        }
                        else {
                            attron(COLOR_PAIR(1));
                            for (int k = 0; k < MASSIMO_CLIENTI; k++) {
                                if (mattonella[i][j].utente == semaforo[k].utente) {
                                    printw(" %i ", k+1);
                                }
                            }
                            attroff(COLOR_PAIR(1));
                        }
                    }
                }
                printw("\n");
            }
            for (int f = 0; f < MASSIMO_CLIENTI; f++) {
                if (semaforo[f].utente == -1) {
                    printw("PASS %i NON ASSEGNATO\n", f+1);
                }
                else {
                    printw("PASS %i IN MANO AL CLIENTE %i\n", f+1, semaforo[f].utente);
                }
            }
            
            if (fuori) {
                break;
            }
        }
        endwin();
    }
}

#endif /* funzioni_h */
