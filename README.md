ESERCIZIO<br>

Per consentire l’osservanza delle norme anti-assembramento ai tempi del COVID-19, un negozio
dispone di un software per il controllo degli accessi ai suoi clienti. In particolare, viene
consentito l’accesso automatico a pochi clienti per volta, in base alle caratteristiche dello
stabile e al rischio di contagio. Utilizzando le funzioni della programmazione multithreading del
linguaggio C, implementare un programma che dati N clienti che in momenti diversi intendono
entrare in negozio e M pass elettronici disponibili, venga monitorato l’accesso al negozio ad un
massimo di M clienti per volta, in modo tale che ciascuno degli altri N-M clienti in coda possa
accedere allo stabile soltanto quando uno degli M clienti abbia rilasciato il pass all’uscita dal
negozio.<br><br>

LIVELLO BASE<br>
Realizzare una soluzione del problema in linguaggio C mediante il ricorso ai thread e scrivere
una relazione che spieghi la strategia risolutiva e i dettagli progettuali e implementativi.<br><br>

LIVELLO AVANZATO<br>
Il titolare del negozio decide di ampliare il locale prevedendo di conseguenza una gestione di
più punti di accesso simultanei di entrata nel negozio. Prevedere una nuova gestione degli accessi
al negozio mediante NUM_PORTE_DI_ACCESSO > 1, ricorrendo ad una programmazione
multithreading sincronizzata. Scrivere in una relazione la strategia risolutiva e i dettagli
progettuali e implementativi di questa nuova soluzione.<br><br>

Per la versione in C Bisogna cambiare il valore delle define, mentre per il C++ basta aprire il file txt  e modificare i valori dopo i due punti (':'), di seguito riporto le varie indicazioni<br>

Dimensioni-X -> Dimensioni del lato X<br>
Dimensioni-Y -> Dimensioni del lato Y<br>
Numero-entrate -> Numero di entrate che si voglio avere nel negozio e sarà anche per il numero di code.<br>
Numero-uscite -> Relativo al numero di uscite che si voglio avere nel negozio<br>
Numero-clienti -> Numero di clienti che deve generare il programma (un numero troppo altro potrebbe causare delle instabilità del sistema)<br>
Tempo-massimo-arrivo -> Tempo del cliente di presa posizione dopo la sua nascita<br>
Tempo-minimo/massimo-movimento -> indicati i valori in microsecondi per gli spostamenti della persona<br>
Percentuale-decisione-uscita -> range per la percentuale di uscita (la percentuale che possa uscite 1)<br>
Clienti-massimo -> all'interno del negozio nello stesso momento<br>
Debug -> 0 = Normale | 1 = Senza grafica | 2 = debug console<br>


--------------------<br>
RETURN VALUE<br>
Return 1 -> Lato x troppo piccolo<br>
Return 2 -> Lato y troppo piccolo<br>
Return 3 -> Numero di entrate troppo piccolo<br>
Return 4 -> Numero di uscite troppo piccolo<br>
Return 5 -> Numero di clienti troppo piccolo<br>
Return 6 -> Tempo massimo di arrivo troppo piccolo<br>
Return 7 -> Tempo di movimento minimo < 200000<br>
Return 8 -> Tempo di movimento massimo troppo piccolo<br>
Return 9 -> Numero di clienti massimo troppo piccolo<br>
Return 10 -> Debug valore non impostato<br>
Return 11 -> Numero di clienti massimo non valido<br>
Return 12 -> Numero di entrate + uscite non valido<br>
