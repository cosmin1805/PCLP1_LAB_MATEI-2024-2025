#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int timestampToDay(int timestamp) {
    // Convert Unix timestamp to struct tm
    struct tm *timeInfo = gmtime(&timestamp);

    // Extracting the day part
    int day = timeInfo->tm_mday;

    return day;
}

typedef struct {
    char src[25];
    char dest[25];
    int timestamp;
    double suma;
}TTranzactie;
typedef struct {
    char* nume;
    char CNP[14];
    char conturi[50][25];
    int nrCrtConturi;
}TPers;
typedef struct {
    int nrCrtTranzactii, nrMaxTranzactii, nrMaxPers, nrCrtPers;
    TPers *pers;
    TTranzactie * tranz;
    TTranzactie **tranzIdx;
    TTranzactie **idxData[366];
}TColectie;

TColectie *allocTColectie(int nrMaxTranzactii, int maxPers) {
    TColectie *colectie = (TColectie *)malloc(sizeof(TColectie));
    if (colectie == NULL)
    {
        return NULL;
    }
    colectie->tranz = (TTranzactie *)malloc(nrMaxTranzactii * sizeof(TTranzactie));
    if (colectie->tranz == NULL)
    {
        free(colectie);
        return NULL;
    }
    colectie->tranzIdx = (TTranzactie **)malloc(nrMaxTranzactii * sizeof(TTranzactie *));
    if(colectie->tranzIdx == NULL) {
        free(colectie->tranzIdx);
        free(colectie);
        return NULL;
    }
    colectie->pers = malloc(maxPers * sizeof(TPers));
    if (colectie->pers == NULL)
    {
        free(colectie->tranzIdx);
        free(colectie->tranzIdx);
        free(colectie);
        return NULL;
    }
    colectie->nrMaxTranzactii = nrMaxTranzactii;
    colectie->nrCrtTranzactii = 0;
    return colectie;
}
TColectie *sortareTranzIdx(TColectie *colectie){
    for (int i = 0; i < colectie->nrCrtTranzactii; i++)
    {
        colectie->tranzIdx[i] = colectie->tranz + i;
    }
    for (int i = 0; i < colectie->nrCrtTranzactii - 1; i++)
    {
        for (int j = i + 1; j < colectie->nrCrtTranzactii; j++)
        {
            if (colectie->tranzIdx[i]->timestamp > colectie->tranzIdx[j]->timestamp)
            {
                TTranzactie *temp = colectie->tranzIdx[i];
                colectie->tranzIdx[i] = colectie->tranzIdx[j];
                colectie->tranzIdx[j] = temp;
            }
        }
    }
    return colectie;
}
TColectie *completeIdxData(TColectie *colectie){
    sortareTranzIdx(colectie);
    colectie->idxData[timestampToDay(colectie->tranzIdx[0]->timestamp)] = colectie->tranzIdx;
    for (int i = 1; i < colectie->nrCrtTranzactii; i++)
    {
        if (colectie->tranzIdx[i] != colectie->tranzIdx[i - 1])
        {
            colectie->idxData[timestampToDay(colectie->tranzIdx[i]->timestamp)] = colectie->tranzIdx + i;
        }
    }
    return colectie;
}
int moreThenOneBank(TColectie *colectie) {
    int persCuMaiMulteConturi = 0;
    for (int i = 0; i < colectie->nrCrtPers; i++)
    {
        int conturiLaMaiMulteBanci = 0;
        for (int j = 0; j < colectie->pers[i].nrCrtConturi; j++)
        {
            for (int k = j + 1; k < colectie->pers[i].nrCrtConturi; k++)
            {
                if (strncmp(colectie->pers[i].conturi[j] + 3,colectie->pers[i].conturi[k] + 3, 4) != 0)
                {
                    conturiLaMaiMulteBanci = 1;
                    break;
                }
            }
        }
        if (conturiLaMaiMulteBanci)
        {
            persCuMaiMulteConturi++;
        }
    }
    return persCuMaiMulteConturi;
}
int apartineCont(TPers *p, char* iban){
    for (int i = 0; i < p->nrCrtConturi; i++)
    {
        if (strcmp(iban,p->conturi[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
double calcSuma(TColectie *col, char* cnp, int zi) {
    double suma = 0;
    TPers* persoana;
    for (int i = 0; i < col->nrCrtPers; i++)
    {
        if (strcmp(cnp,col->pers[i].CNP) == 0)
        {
            persoana = persoana + i;
            break;
        }
    }
    for (TTranzactie * i = col->idxData[zi]; i != NULL && (i+1) != NULL && (* i).timestamp == (*(i + 1)).timestamp; i = i + 1)
    {
        if (apartineCont(persoana,i->dest));
        {
            suma += i->suma;
        }
    }
    return suma;
}
int main() {
    TColectie *colectie = allocTColectie(100, 10); // Adjust the values based on your requirements

    // Populating sample data
    // For simplicity, I'll provide a basic example. You should adapt it to your actual use case.

    // Adding a person
    colectie->pers[0].nume = "John Doe";
    strcpy(colectie->pers[0].CNP, "12345678901234");
    colectie->pers[0].nrCrtConturi = 2;
    strcpy(colectie->pers[0].conturi[0], "RO0123456789012345678901");
    strcpy(colectie->pers[0].conturi[1], "RO9876543210987654321098");

    // Adding transactions
    colectie->tranz[0].timestamp = 20220101;
    strcpy(colectie->tranz[0].src, "RO0123456789012345678901");
    strcpy(colectie->tranz[0].dest, "RO9876543210987654321098");
    colectie->tranz[0].suma = 100.0;

    colectie->tranz[1].timestamp = 20220101;
    strcpy(colectie->tranz[1].src, "RO0123456789012345678901");
    strcpy(colectie->tranz[1].dest, "RO9876543210987654321098");
    colectie->tranz[1].suma = 150.0;

    // Setting the number of current transactions and persons
    colectie->nrCrtTranzactii = 2;
    colectie->nrCrtPers = 1;

    // Testing the calcSuma function
    double totalSum = calcSuma(colectie, "12345678901234", 20220101);

    printf("Total sum for CNP 12345678901234 on 20220101: %.2f\n", totalSum);

    // Testing moreThanOneBank function
    int result = moreThenOneBank(colectie);
    printf("Number of persons with accounts in more than one bank: %d\n", result);

    // Freeing allocated memory
    free(colectie->pers);
    free(colectie->tranz);
    free(colectie->tranzIdx);
    free(colectie);

    return 0;
}
