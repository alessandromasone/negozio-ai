# Negozio AI

Questo progetto offre una soluzione di programmazione multithreading in linguaggio C per il controllo degli accessi al negozio, consentendo il rispetto delle norme anti-assembramento durante la pandemia di COVID-19.

## Descrizione

Il software sviluppato per questo progetto permette di gestire l'accesso dei clienti al negozio in modo automatico, consentendo l'accesso a un numero limitato di clienti alla volta, in base alle caratteristiche dello stabile e al rischio di contagio.

Il progetto è suddiviso in due livelli di complessità:

- **Livello Base**: Implementazione di una soluzione con un singolo punto di accesso.
- **Livello Avanzato**: Implementazione di una soluzione con più punti di accesso simultanei.

## Livello Base

La soluzione di base prevede l'utilizzo di thread in linguaggio C per controllare gli accessi al negozio. Viene gestito un singolo punto di accesso, e il programma monitora il numero di clienti presenti nel negozio, consentendo l'accesso solo a un numero massimo di clienti contemporaneamente. Per maggiori dettagli sulla soluzione implementata, consulta la relazione nel file [relazione_base.md](./relazione_base.md).

## Livello Avanzato

La soluzione avanzata prevede una gestione di più punti di accesso simultanei al negozio. In questo modo, il programma può consentire l'accesso a un maggior numero di clienti contemporaneamente, riducendo gli assembramenti alle entrate. Per maggiori dettagli sulla soluzione implementata, consulta la relazione nel file [relazione_avanzata.md](./relazione_avanzata.md).

## Relazioni

- [Relazione Livello Base](./relazione_base.md): Descrizione dettagliata della strategia risolutiva e dei dettagli progettuali e implementativi per il livello base.
- [Relazione Livello Avanzato](./relazione_avanzata.md): Descrizione dettagliata della strategia risolutiva e dei dettagli progettuali e implementativi per il livello avanzato.

## Istruzioni per l'esecuzione

1. Assicurarsi di avere un compilatore C installato sul proprio sistema.
2. Clonare il repository Negozio-AI.
3. Compilare il programma utilizzando il comando:
   ```
   gcc -pthread main.c -o negozio
   ```
4. Eseguire il programma con il comando:
   ```
   ./negozio
   ```
   Seguire le istruzioni sullo schermo per interagire con il programma.


Certamente! Di seguito troverai le istruzioni per la modifica dei valori di configurazione sia per la versione in C che per la versione in C++. Queste istruzioni possono essere incluse nel file README.md del tuo progetto utilizzando la sintassi del linguaggio Markdown.

## Modifica dei valori di configurazione

Per personalizzare il comportamento del programma, puoi modificare i valori di configurazione nel codice sorgente o nel file di testo fornito, a seconda della versione del linguaggio che stai utilizzando.

### Versione in C

Per la versione in C, è possibile modificare direttamente le definizioni dei valori di configurazione nel codice sorgente. Apri il file sorgente `main.c` e cerca le seguenti definizioni:

```c
#define Numero-clienti 100
#define Tempo-massimo-arrivo 500000
#define Tempo-minimo-movimento 200000
#define Tempo-massimo-movimento 500000
#define Percentuale-decisione-uscita 0.5
#define Clienti-massimo 10
#define Debug 0
```

Modifica i valori secondo le tue preferenze. Ad esempio:

```c
#define Numero-clienti 50
#define Tempo-massimo-arrivo 300000
#define Tempo-minimo-movimento 100000
#define Tempo-massimo-movimento 400000
#define Percentuale-decisione-uscita 0.3
#define Clienti-massimo 5
#define Debug 1
```

Salva le modifiche e riavvia il programma.

### Versione in C++

Per la versione in C++, puoi modificare i valori di configurazione nel file di testo fornito. Apri il file `dati.txt` e trova le seguenti linee:

```
Numero-clienti: 100
Tempo-massimo-arrivo: 500000
Tempo-minimo-movimento: 200000
Tempo-massimo-movimento: 500000
Percentuale-decisione-uscita: 0.5
Clienti-massimo: 10
Debug: 0
```

Modifica i valori dopo i due punti (':') secondo le tue preferenze. Ad esempio:

```
Numero-clienti: 50
Tempo-massimo-arrivo: 300000
Tempo-minimo-movimento: 100000
Tempo-massimo-movimento: 400000
Percentuale-decisione-uscita: 0.3
Clienti-massimo: 5
Debug: 1
```

Salva le modifiche e riavvia il programma.

## Contributi

Sono benvenuti contributi e miglioramenti a questo progetto! Se desideri contribuire, segui le seguenti istruzioni:

1. Forka il repository.
2. Crea un nuovo branch per le tue modifiche:
   ```
   git checkout -b miglioramenti
   ```
3. Effettua le modifiche e commita i tuoi cambiamenti:
   ```
   git commit -m "Aggiunti miglioramenti al thread di controllo"
   ```
4. Pusha il tuo branch:
   ```
   git push origin miglioramenti
   ```
5. Apri una Pull Request nel repository originale.

## Licenza

Questo progetto è distribuito con la licenza MIT.
