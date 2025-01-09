#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char intensitate, rosu, verde, albastru;
    int id;
} TBec;
typedef struct
{
    char *nume;
    int nrCrtBecuri;
    TBec **becuri;
} TCamera;
typedef struct
{
    int nrCrtBecuri, nrMaxBecuri;
    TBec *becuri;
    int nrCrtCamere, nrMaxCamere;
    TCamera *camere;
} TCasa;
TCasa *alocaCasa(int nrMaxBecuri, int nrMaxCamere)
{
    TCasa *casa = malloc(sizeof(TCasa));
    if (casa == NULL)
    {
        return NULL;
    }
    casa->becuri = malloc(nrMaxBecuri * sizeof(TBec));
    if (casa->becuri == NULL)
    {
        free(casa);
        return NULL;
    }
    casa->camere = malloc(nrMaxCamere * sizeof(TCamera));
    for (int i = 0; i < nrMaxCamere; i++)
    {
        casa->camere[i].becuri = (TBec **)malloc(nrMaxBecuri * sizeof(TBec *));
        casa->camere[i].nume= malloc(30);
        casa->camere[i].nrCrtBecuri = 0;
    }
    if (casa->camere == NULL)
    {
        free(casa->becuri);
        free(casa);
        return NULL;
    }
    casa->nrCrtBecuri = 0;
    casa->nrMaxBecuri = nrMaxBecuri;
    casa->nrCrtCamere = 0;
    casa->nrMaxCamere = nrMaxCamere;
    return casa;
}
TBec *adaugaBec(TCasa *casa, char intensitate, char rosu, char verde, char albastru, char *numeCamera)
{
    for (int i = 0; i < casa->nrCrtCamere; i++)
    {
        if (strcmp(casa->camere[i].nume, numeCamera) == 0)
        {
            casa->becuri[casa->nrCrtBecuri].intensitate = intensitate;
            casa->becuri[casa->nrCrtBecuri].rosu = rosu;
            casa->becuri[casa->nrCrtBecuri].verde = verde;
            casa->becuri[casa->nrCrtBecuri++].albastru = albastru;
            casa->camere[i].becuri[casa->camere[i].nrCrtBecuri++] = casa->becuri + (casa->nrCrtBecuri - 1);
            return casa->becuri + (casa->nrCrtBecuri - 1);
        }
    }
    return NULL;
}
TCasa *readFromFile(FILE *f)
{
    int nrMaxCamere = 0;
    fscanf(f, "%d", &nrMaxCamere);
    TCasa *casa = alocaCasa(20, nrMaxCamere);
    if (casa == NULL)
    {
        return NULL;
    }
    for (; casa->nrCrtCamere < nrMaxCamere; casa->nrCrtCamere++)
    {
        int nrBecuriCamera = 0;
        fscanf(f, "%s %d", casa->camere[casa->nrCrtCamere].nume, &nrBecuriCamera);
        casa->nrMaxBecuri = casa->nrCrtBecuri + nrBecuriCamera;
        for (; casa->nrCrtBecuri < casa->nrMaxBecuri; casa->nrCrtBecuri++)
        {
            fscanf(f, "%hhd", &casa->becuri[casa->nrCrtBecuri].intensitate);
            fscanf(f, "%hhd", &casa->becuri[casa->nrCrtBecuri].rosu);
            fscanf(f, "%hhd", &casa->becuri[casa->nrCrtBecuri].verde);
            fscanf(f, "%hhd", &casa->becuri[casa->nrCrtBecuri].albastru);
            casa->camere[casa->nrCrtCamere].becuri[casa->camere[casa->nrCrtCamere].nrCrtBecuri++] = casa->becuri + casa->nrCrtBecuri;
        }
    }
    return casa;
}
// de la chat gpt
void adaugaCamera(TCasa *casa, const char *numeCamera)
{
    if (casa->nrCrtCamere < casa->nrMaxCamere)
    {
        casa->camere[casa->nrCrtCamere].nume = strdup(numeCamera);
        casa->camere[casa->nrCrtCamere].nrCrtBecuri = 0;
        casa->nrCrtCamere++;
    }
    else
    {
        printf("Nu se mai pot adauga camere. Limita a fost atinsa.\n");
    }
}
int main()
{
    // Test the allocation function
    TCasa *casa = alocaCasa(10, 5);
    if (casa == NULL)
    {
        printf("Failed to allocate house.\n");
        return 1;
    }

    adaugaCamera(casa, "Living Room");
    adaugaCamera(casa, "Bedroom");
    adaugaCamera(casa, "Kitchen");
    // Test adding bulbs to the house
    adaugaBec(casa, 50, 255, 0, 0, "Living Room");
    adaugaBec(casa, 75, 0, 255, 0, "Bedroom");
    adaugaBec(casa, 100, 0, 0, 255, "Kitchen");

    // Test reading from a file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return 1;
    }

    TCasa *casa2 = readFromFile(file);
    if (casa == NULL)
    {
        printf("Failed to read from file.\n");
        fclose(file);
        return 1;
    }
    printf("House2 Information:\n");
    for (int i = 0; i < casa2->nrCrtCamere; i++)
    {
        printf("Room: %s\n", casa2->camere[i].nume);
        for (int j = 0; j < casa2->camere[i].nrCrtBecuri; j++)
        {
            TBec *bulb = casa2->camere[i].becuri[j];
            printf("  Bulb %d - Intensity: %d, Red: %d, Green: %d, Blue: %d\n", j + 1, bulb->intensitate, bulb->rosu, bulb->verde, bulb->albastru);
        }
    }
    fclose(file);

    // Display information about the house
    printf("House Information:\n");
    for (int i = 0; i < casa->nrCrtCamere; i++)
    {
        printf("Room: %s\n", casa->camere[i].nume);
        for (int j = 0; j < casa->camere[i].nrCrtBecuri; j++)
        {
            TBec *bulb = casa->camere[i].becuri[j];
            printf("  Bulb %d - Intensity: %d, Red: %d, Green: %d, Blue: %d\n", j + 1, bulb->intensitate, bulb->rosu, bulb->verde, bulb->albastru);
        }
    }

    // Clean up allocated memory
    // ...

    return 0;
}