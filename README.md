Per la versione in C Bisogna cambiare il valore delle define, mentre per il C++ basta aprire il file txt  e modificare i valori dopo i due punti (':'), di seguito riporto le varie indicazioni

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