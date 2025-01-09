#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nrMasina[9];
    int anFabr, nrAmenzi;
} TMasina;
typedef struct
{
    TMasina *masina;
    float voloare;
    short achitat;
    char *PV;
} TAmenda;
typedef struct
{
    int nrMaxAmenzi, nrCrtAmenzi, nrMaxMasini, nrCrtMasini;
    TMasina *masini;
    TAmenda *amenzi;
} TColectie;
TColectie *allocTColectie(int nrMaxMasini, int MaxAmenzi)
{
    TColectie *colectie = malloc(sizeof(TColectie));
    if (colectie == NULL)
    {
        return NULL;
    }
    colectie->masini = malloc(nrMaxMasini * sizeof(TMasina));
    if (colectie->masini == NULL)
    {
        free(colectie);
        return NULL;
    }
    colectie->amenzi = malloc(MaxAmenzi * sizeof(TAmenda));
    if (colectie->amenzi == NULL)
    {
        free(colectie->masini);
        free(colectie);
        return NULL;
    }
    colectie->nrCrtAmenzi = 0;
    colectie->nrMaxAmenzi = MaxAmenzi;
    colectie->nrCrtMasini = 0;
    colectie->nrMaxMasini = nrMaxMasini;
    return colectie;
}
TAmenda *adaugaAmenda(TColectie *c, char *nr, char *PV, float valoare)
{
    for (int i = 0; i < c->nrCrtMasini; i++)
    {
        if (strcmp(c->masini[i].nrMasina, nr) == 0)
        {
            if (c->nrCrtAmenzi == c->nrMaxAmenzi)
            {
                c->amenzi = realloc(c->amenzi, 2 * c->nrMaxAmenzi * sizeof(TAmenda));
                if (c->amenzi == NULL)
                {
                    return NULL;
                }
                c->nrMaxAmenzi *= 2;
            }
            c->amenzi[c->nrCrtAmenzi].masina = c->masini + i;
            c->amenzi[c->nrCrtAmenzi].PV = malloc(strlen(PV) + 1);
            if (c->amenzi[c->nrCrtAmenzi].PV == NULL)
            {
                return NULL;
            }
            strcpy(c->amenzi[c->nrCrtAmenzi].PV, PV);
            c->amenzi[c->nrCrtAmenzi].voloare = valoare;
            c->amenzi[c->nrCrtAmenzi++].achitat = 0;
            break;
        }
    }
}
int sortFct(const void *a,const void *b)
{
    TAmenda *amenda1 = (TAmenda *)a;
    TAmenda *amenda2 = (TAmenda *)b;
    if (atoi(amenda1->masina->nrMasina) < atoi(amenda2->masina->nrMasina))
    {
        return -1;
    }
    else if (atoi(amenda1->masina->nrMasina) > atoi(amenda2->masina->nrMasina))
    {
        return 1;
    }
    return (int)amenda2->voloare - (int)amenda1->voloare;
}
void sortareAmenzi(TColectie *colectie)
{
    qsort(colectie->amenzi, colectie->nrCrtAmenzi, sizeof(TAmenda), sortFct);
}
TMasina *masinaMaxSuma(TColectie *colectie)
{
    float suma = colectie->amenzi[0].voloare, valMax = 0;
    TMasina *masina = colectie->amenzi[0].masina;
    for (int i = 1; i < colectie->nrCrtAmenzi; i++)
    {
        if (strcmp(colectie->amenzi[i].masina->nrMasina, colectie->amenzi[i - 1].masina->nrMasina) != 0)
        {
            if (suma > valMax)
            {
                valMax = suma;
                masina = colectie->amenzi[i - 1].masina;
            }
            suma = 0;
            if (colectie->amenzi[i].achitat == 0)
            {
                suma += colectie->amenzi[i].voloare;
            }
        }
        else if (colectie->amenzi[i].achitat == 0)
        {
            suma += colectie->amenzi[i].voloare;
        }
    }
    if (suma > valMax)
    {
        valMax = suma;
        masina = colectie->amenzi[colectie->nrCrtAmenzi - 1].masina;
    }
    return masina;
}
void saveToFile(TColectie *colectie, FILE *f)
{
    sortareAmenzi(colectie);
    fprintf(f, "Masina 1:%s\n", colectie->amenzi[0].masina->nrMasina);
    fprintf(f, "%f-%s\n", colectie->amenzi[0].voloare, colectie->amenzi[0].PV);
    for (int i = 1; i < colectie->nrCrtAmenzi; i++)
    {
        if (strcmp(colectie->amenzi[i].masina->nrMasina, colectie->amenzi[i - 1].masina->nrMasina) == 0)
        {
            fprintf(f, "%f-%s\n", colectie->amenzi[i].voloare, colectie->amenzi[i].PV);
        }
        else
        {
            fprintf(f, "Masina %d:%s\n", i + 1, colectie->amenzi[i].masina->nrMasina);
            fprintf(f, "%f-%s\n", colectie->amenzi[0].voloare, colectie->amenzi[i].PV);
        }
    }
}
int main()
{
    TColectie *colectie = allocTColectie(10, 20); // Adjust the numbers as needed
    if (colectie == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for TColectie.\n");
        return 1;
    }

    // Add some cars and fines
    // For simplicity, let's add a few fines for the same car
    adaugaAmenda(colectie, "ABC123", "Parking Violation", 50.0);
    adaugaAmenda(colectie, "XYZ789", "Speeding", 100.0);
    adaugaAmenda(colectie, "ABC123", "Red Light Violation", 75.0);
    adaugaAmenda(colectie, "XYZ789", "Illegal Parking", 60.0);

    // Sort fines
    sortareAmenzi(colectie);

    // Find the car with the maximum fine amount
    TMasina *maxSumaMasina = masinaMaxSuma(colectie);
    if (maxSumaMasina != NULL)
    {
        printf("Car with maximum fine amount: %s\n", maxSumaMasina->nrMasina);
    }

    // Save fines to a file
    FILE *f = fopen("fines.txt", "w");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file for writing.\n");
        return 1;
    }

    saveToFile(colectie, f);

    fclose(f);

    // Free allocated memory
    free(colectie->masini);
    free(colectie->amenzi);
    free(colectie);

    return 0;
}
