//
//  class.h
//  negozio
//
//  Created by Alessandro masone on 06/03/22.
//

#ifndef class_h
#define class_h

using namespace std;


/// Serve per rimappare i mutex per ottenere un allocazione dinamica
struct mutex_wrapper : std::mutex
{
  mutex_wrapper() = default;
  mutex_wrapper(mutex_wrapper const&) noexcept : std::mutex() {}
  bool operator==(mutex_wrapper const&other) noexcept { return this==&other; }
};

/// pass all'interno del negozio con riferimento anche all'identificativo dell'utente
struct passaport {
    int utente;
    mutex_wrapper pass;
};

/// Classe dei punti all'interno della localizzazione delle entita
class Coordinate {
private:
    int x;
    int y;
public:
    void assegnax(int valore_x);
    void assegnay(int valore_y);
    int dammix();
    int dammiy();
    void incrementax();
    void decrementax();
    void incrementay();
    void decrementay();
};
/// Assegna un valore alla X
/// @param valore_x valore da ssegnare alla X
void Coordinate::assegnax(int valore_x) {
    x = valore_x;
}
/// Assegna un valore alla Y
/// @param valore_y valore da ssegnare alla Y
void Coordinate::assegnay(int valore_y) {
    y = valore_y;
}
/// Ritorna la coordinata X
int Coordinate::dammix() {
    return x;
}
/// Ritorna la coordinata Y
int Coordinate::dammiy() {
    return y;
}
/// Incrementa il valore X
void Coordinate::incrementax() {
    x++;
}
/// Decrementa il valore X
void Coordinate::decrementax() {
    x--;
}
/// Incrementa il valore Y
void Coordinate::incrementay() {
    y++;
}
/// Decrementa il valore Y
void Coordinate::decrementay() {
    y--;
}

/// Singola piastrella del negozio
class Mattonella {
private:
    int tipo;
    int utente;
    mutex_wrapper dispobile;
public:
    void assegnavuoto();
    void assegnaentrata();
    void assegnauscita();
    void assegnapersona();
    void rimuoviutente();
    void assegnautente(int valore);
    int dammitipo();
    int dammiutente();
    void bloccamattonella();
    void sbloccamattonella();
    bool provabloccamattonella();
};
/// Assegna il tipo vuoto alla mattonella
void Mattonella::assegnavuoto() {
    tipo = VUOTO;
}
/// Assegna il tipo entrata alla mattonella
void Mattonella::assegnaentrata() {
    tipo = ENTRATA;
}
/// Assegna il tipo uscita alla mattonella
void Mattonella::assegnauscita() {
    tipo = USCITA;
}
/// Assegna il tipo persone alla mattonella
void Mattonella::assegnapersona() {
    tipo = PERSONA;
}
/// Rimuove il valore dell'indetificativo dalla piastrella
void Mattonella::rimuoviutente() {
    utente = -1;
}
/// Assegnazione di un identificativo utente
/// @param valore identificativo della persone
void Mattonella::assegnautente(int valore) {
    utente = valore;
}
/// Ritorna il tipo di mattonella
int Mattonella::dammitipo() {
    return tipo;
}
/// Ritorna la presenza di un utente con il suo identificativo
int Mattonella::dammiutente() {
    return utente;
}
/// Richiama lock del mutex
void Mattonella::bloccamattonella() {
    dispobile.lock();
}
/// Richiamata unlock del mutex
void Mattonella::sbloccamattonella() {
    dispobile.unlock();
}
/// RIchiamata try_lock del mutex
bool Mattonella::provabloccamattonella() {
    return dispobile.try_lock();
}

/// Coda di persone
class Coda {
private:
    int identificativo;
    Coordinate entrata;
    vector<mutex_wrapper> posto;
    vector<int> identificativo_utente;
public:
    void assegnaidentificativo(int valore);
    void assegnaidentificativoutente(int valore, int posizione);
    void assegnacoordinateentrata(int x, int y);
    void assegnaposti(int valore);
    void bloccaposto(int valore);
    void sbloccaposto(int valore);
    bool provabloccare(int valore);
    int dammiidentificatoreutente(int posizione);
    int dammicoordinateentrata(char v);
};
/// Assegnazione di un identificativo alla coda
/// @param valore valore da associare all'identificativo
void Coda::assegnaidentificativo(int valore) {
    identificativo = valore;
}
/// assegnazione dell'identificativo utente nella posizione
/// @param valore identificativo
/// @param posizione posizione dove scrivere
void Coda::assegnaidentificativoutente(int valore, int posizione) {
    identificativo_utente[posizione] = valore;
}
/// Associa alla coda un entrata
/// @param x valore X entrata
/// @param y valore Y entrata
void Coda::assegnacoordinateentrata(int x, int y) {
    entrata.assegnax(x);
    entrata.assegnay(y);
}
/// Allocazione dinamica della coda
/// @param valore valore della lunghezza della coda
void Coda::assegnaposti(int valore) {
    posto.resize(valore);
    identificativo_utente.resize(valore);
}
/// Richiamo funzione lock
/// @param valore posto da bloccare
void Coda::bloccaposto(int valore) {
    posto[valore].lock();
}
/// Richiamo funzione unlock
/// @param valore valore posto da sbloccare
void Coda::sbloccaposto(int valore) {
    posto[valore].unlock();
}
/// RIchiamo funzione try_lock
/// @param valore valore posto da provare a sbloccare
bool Coda::provabloccare(int valore) {
    return posto[valore].try_lock();
}
/// ritorno identificativo dell'utente
/// @param posizione posizione dell'identificativo che si vuole come ritorno
int Coda::dammiidentificatoreutente(int posizione) {
    return identificativo_utente[posizione];
}
/// Ritorno coordinate entrata della coda
/// @param v carattere 'x' o 'y'
int Coda::dammicoordinateentrata(char v) {
    if (v == 'x') {
        return entrata.dammix();
    }
    else if (v == 'y') {
        return entrata.dammiy();
    }
    return 0;
}

class Persona {
    int identificativo;
    int coda;
    int velocita;
    Coordinate uscita;
    Coordinate entrata;
    int direzione;
    Coordinate posizione;
    int pass;
    int spostamenti;
public:
    thread threadw;
    void assegnavelocita(int valore);
    int dammivelocita();
    void inizializzaspostamenti();
    void incrementaspostamenti();
    void assegnaidentificativo(int valore);
    void assegnacoda(int valore);
    void assegnaentrata(int x, int y);
    void assegnauscita(int x, int y);
    void movimentosopra();
    void movimentosotto();
    void movimentodestra();
    void movimentosinistra();
    void movimentofermo();
    void assegnaposizione(int x, int y);
    void assegnapass(int valore);
    int dammiidentificativo();
    int dammicoordinate(char v);
    int dammiuscita(char v);
    void incrementax();
    void decrementax();
    void incrementay();
    void decrementay();
};
/// Assegnazione della velocita di movimento
/// @param valore valore da assegnare
void Persona::assegnavelocita(int valore) {
    velocita = valore;
}
/// ritorno della velocità
int Persona::dammivelocita() {
    return velocita;
}
/// Imposta a 0 gli spostamenti della persone
void Persona::inizializzaspostamenti() {
    spostamenti = 0;
}
/// Incrementazione degli spostamenti della persona
void Persona::incrementaspostamenti() {
    spostamenti++;
}
/// Assegnazione dell'identificativo alla persona
/// @param valore valore
void Persona::assegnaidentificativo(int valore) {
    identificativo = valore;
}
/// Assegnazione di una coda
/// @param valore valore identificativo della coda
void Persona::assegnacoda(int valore) {
    coda = valore;
}
/// Assegnazione coordinate di entrata alla persona
/// @param x valore X dell'entrata
/// @param y valore Y dell'entrata
void Persona::assegnaentrata(int x, int y) {
    entrata.assegnax(x);
    entrata.assegnay(y);
}
/// Assegnazione coordinate di uscita alla persona
/// @param x valore X dell'uscita
/// @param y valore Y dell'uscita
void Persona::assegnauscita(int x, int y) {
    uscita.assegnax(x);
    uscita.assegnay(y);
}
/// modifica direzione della persona
void Persona::movimentosopra() {
    direzione = SOPRA;
}
/// modifica direzione della persona
void Persona::movimentosotto() {
    direzione = SOTTO;
}
/// modifica direzione della persona
void Persona::movimentodestra() {
    direzione= DESTRA;
}
/// modifica direzione della persona
void Persona::movimentosinistra() {
    direzione = SINISTRA;
}
/// modifica direzione della persona
void Persona::movimentofermo() {
    direzione = FERMO;
}
/// Assegnazione della posizione dell'utente
/// @param x valore X della posizione
/// @param y valore Y della posizione
void Persona::assegnaposizione(int x, int y) {
    posizione.assegnax(x);
    posizione.assegnay(y);
}
/// Assegnazione pass alla persona
/// @param valore identificativo del pass
void Persona::assegnapass(int valore) {
    pass = valore;
}
/// Ritorno dell'identificativo
int Persona::dammiidentificativo() {
    return identificativo;
}
/// Ritorno della cordinata scelta della posizione
/// @param v carattere 'x' o 'y'
int Persona::dammicoordinate(char v) {
    if (v == 'x') {
        return posizione.dammix();
    }
    else if (v == 'y') {
        return posizione.dammiy();
    }
    return 0;
}
/// Ritorno della cordinata scelta dell'uscita
/// @param v carattere 'x' o 'y'
int Persona::dammiuscita(char v) {
    if (v == 'x') {
        return uscita.dammix();
    }
    else if (v == 'y') {
        return uscita.dammiy();
    }
    return 0;
}
/// Incrmento x posizione
void Persona::incrementax() {
    posizione.incrementax();
}
/// Decremento x posizione
void Persona::decrementax() {
    posizione.decrementax();
}
/// Incremento y posizione
void Persona::incrementay() {
    posizione.incrementay();
}
/// Decremento y posizione
void Persona::decrementay() {
    posizione.decrementay();
}

#endif /* class_h */
