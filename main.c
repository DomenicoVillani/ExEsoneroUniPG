#include <stdio.h>
#include <stdlib.h>

// Funzione per pulire il buffer di input in caso di errore
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funzione per leggere un numero intero con controllo dell'input
int readInt(const char* prompt) {
    int value;
    int result;
    
    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        
        if (result == 1) {  // Input valido
            clearInputBuffer(); // Pulisci il buffer per evitare problemi con scanf successivi
            return value;
        } else {
            printf("Input non valido. Inserisci un numero intero.\n");
            clearInputBuffer();  // Pulisci il buffer di input
        }
    }
}

// Funzione per leggere un valore intero positivo con controllo
int readPositiveInt(const char* prompt) {
    int value;
    
    while (1) {
        value = readInt(prompt);
        
        if (value > 0) {
            return value;
        } else {
            printf("Il numero deve essere maggiore di zero.\n");
        }
    }
}

int main(void) {
    int giorni = 0, k = 0;

    giorni = readPositiveInt("Inserisci numero giorni: ");
    k = readPositiveInt("Inserisci numero azioni da comprare: ");

    int valori[giorni];  // Array per i valori giornalieri

    // Inserimento dei valori giornalieri con controllo dell'input
    for (int i = 0; i < giorni; i++) {
        char prompt[50];
        sprintf(prompt, "Inserisci valore giornaliero per il giorno %d: ", i + 1);
        valori[i] = readInt(prompt);
    }

    int sumMax = 0;  // Per memorizzare il massimo guadagno
    int intervalli[giorni][2];  // Per memorizzare gli intervalli con guadagno massimo
    int intervalliCount = 0;  // Contatore degli intervalli

    // Variabili per il recap finale
    int costoIniziale = 0;
    int costoFinale = 0;
    int guadagnoTotale = 0;

    // Controllo di ogni possibile intervallo di acquisto e vendita
    for (int i = 0; i < giorni - 1; i++) {
        for (int j = i + 1; j < giorni; j++) {
            int guadagno = valori[j] - valori[i];  // Guadagno se compri al giorno i e vendi al giorno j
            if (guadagno > sumMax) {
                sumMax = guadagno;  // Aggiorna il massimo guadagno
                intervalliCount = 0;  // Resetta il contatore
                intervalli[intervalliCount][0] = i + 1;
                intervalli[intervalliCount][1] = j + 1;
                intervalliCount++;
            } else if (guadagno == sumMax) {
                intervalli[intervalliCount][0] = i + 1;
                intervalli[intervalliCount][1] = j + 1;
                intervalliCount++;
            }
        }
    }

    if (sumMax <= 0) {
        printf("Non comprare mai! Guadagno negativo o nullo.\n");
    } else {
        printf("Gli intervalli migliori per comprare e vendere sono:\n");
        for (int i = 0; i < intervalliCount; i++) {
            int indiceS = intervalli[i][0];
            int indiceD = intervalli[i][1];
            int guadagno = k * (valori[indiceD - 1] - valori[indiceS - 1]);

            // Aggiungi al costo iniziale e finale
            costoIniziale += k * valori[indiceS - 1];
            costoFinale += k * valori[indiceD - 1];

            // Aggiungi al guadagno totale
            guadagnoTotale += guadagno;

            printf("- Compra il giorno %d e vendi il giorno %d, guadagno %d\n", indiceS, indiceD, guadagno);
        }

        // Stampa il recap finale
        printf("\nRecap finale:\n");
        printf("Numero di azioni acquistate per intervallo: %d\n", k);
        printf("Costo totale iniziale: %d\n", costoIniziale);
        printf("Costo totale finale: %d\n", costoFinale);
        printf("Guadagno totale: %d\n", guadagnoTotale);
    }

    return 0;
}
