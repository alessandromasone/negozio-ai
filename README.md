Per la versione in C Bisogna cambiare il valore delle define, mentre per il C++ basta aprire il file txt  e modificare i valori dopo i due punti (':'), di seguito riporto le varie indicazioni

Dimensioni-X -> Dimensioni del lato X
Dimensioni-Y -> Dimensioni del lato Y
Numero-entrate -> Numero di entrate che si voglio avere nel negozio e sarà anche per il numero di code.
Numero-uscite -> Relativo al numero di uscite che si voglio avere nel negozio
Numero-clienti -> Numero di clienti che deve generare il programma (un numero troppo altro potrebbe causare delle instabilità del sistema)
Tempo-massimo-arrivo -> Tempo del cliente di presa posizione dopo la sua nascita
Tempo-minimo/massimo-movimento -> indicati i valori in microsecondi per gli spostamenti della persona
Percentuale-decisione-uscita -> range per la percentuale di uscita (la percentuale che possa uscite 1)
Clienti-massimo -> all'interno del negozio nello stesso momento
Debug -> 0 = Normale | 1 = Senza grafica | 2 = debug console


--------------------
RETURN VALUE
Return 1 -> Lato x troppo piccolo
Return 2 -> Lato y troppo piccolo
Return 3 -> Numero di entrate troppo piccolo
Return 4 -> Numero di uscite troppo piccolo
Return 5 -> Numero di clienti troppo piccolo
Return 6 -> Tempo massimo di arrivo troppo piccolo
Return 7 -> Tempo di movimento minimo < 200000
Return 8 -> Tempo di movimento massimo troppo piccolo
Return 9 -> Numero di clienti massimo troppo piccolo
Return 10 -> Debug valore non impostato
Return 11 -> Numero di clienti massimo non valido
Return 12 -> Numero di entrate + uscite non valido