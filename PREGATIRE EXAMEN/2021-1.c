#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int ip, mask, gateway;
}TInfo;

typedef struct {
    char nume[256];
    char *descriere;
    TInfo info;
}TCalc;

typedef struct {
    unsigned int nrMaxCalc, nrCurentCalc;
    char *nume;
    TCalc* calculatoare;
}TRetea;

TRetea* allocTRetea (int nrMaxCalc) {
    TCalc* calculatoare = malloc(nrMaxCalc * sizeof(TCalc));
    if(calculatoare == NULL) {
        return NULL;
    }
    TRetea* retea = malloc(sizeof(TRetea));
    if(retea == NULL) {
        free(calculatoare);
        return NULL;
    }
    retea->calculatoare = calculatoare;
    retea->nrCurentCalc = 0;
    retea->nrMaxCalc = nrMaxCalc;
    retea->nume = NULL;
    return retea;
}
TCalc* adaugaCalc(TRetea* r, char* nume, char* descriere, TInfo info) {
    if(r->nrCurentCalc == r->nrMaxCalc) {
        r->nrMaxCalc++;
        r->calculatoare = realloc(r->calculatoare, r->nrMaxCalc * sizeof(TRetea));
    }
    strcpy(r->calculatoare[r->nrCurentCalc].nume, nume);
    r->calculatoare[r->nrCurentCalc].descriere = descriere;
    r->calculatoare[r->nrCurentCalc].info.ip = info.ip;
    r->calculatoare[r->nrCurentCalc].info.mask = info.mask;
    r->calculatoare[r->nrCurentCalc].info.gateway = info.gateway;
    r->nrCurentCalc++;
    return r->calculatoare;
}
int sortareCalculatoareFct(void* a, void* b) {
    const TCalc *calc1 = (const TCalc *)a;
    const TCalc *calc2 = (const TCalc *)b;
    if (calc1->info.mask < calc2->info.mask) {
        return -1;
    } else if(calc1->info.mask > calc2->info.mask) {
        return 1;
    }
    if (calc1->info.ip < calc2->info.ip) {
        return -1;
    } else if(calc1->info.mask > calc2->info.ip) {
        return 1;
    }
    return 0;
}

char * convert(unsigned int nr) {
    char* ip = calloc(4 , sizeof(char));
    if(ip == NULL) {
        return NULL;
    }
    unsigned char *octeti = (unsigned char*)&nr;
    // Construim adresa IP în format text
    sprintf(ip,"%u.%u.%u.%u", octeti[3], octeti[2], octeti[1], octeti[0]);
    return ip;
}

void sortareCalculatoare(TRetea *r) {
    qsort(r->calculatoare,r->nrCurentCalc,sizeof(TCalc), sortareCalculatoareFct);
}
void salvareInFisier (TRetea *r, FILE *file) {
    sortareCalculatoare(r);
    fprintf(file,"Subretea %s\n",convert(r->calculatoare[0].info.mask));
    fprintf(file,"%s %s %s\n",convert(r->calculatoare[0].info.ip),r->calculatoare[0].nume,r->calculatoare[0].descriere);
    for (int i = 1; i < r->nrCurentCalc; i++)
    {
        if (r->calculatoare[i].info.mask == r->calculatoare[i - 1].info.mask)
        {
            fprintf(file,"%s %s %s\n",convert(r->calculatoare[i].info.ip),r->calculatoare[i].nume,r->calculatoare[i].descriere);
        }
        else {
            fprintf(file,"Subretea %s\n",convert(r->calculatoare[i].info.mask));
            fprintf(file,"%s %s %s\n",convert(r->calculatoare[i].info.ip),r->calculatoare[i].nume,r->calculatoare[i].descriere);
        }
    }
}
int main() {
    // Test the code
    TRetea* retea = allocTRetea(8);

    TInfo info1 = {192 << 24 | 168 << 16 | 1 << 8 | 100, 255 << 24 | 255 << 16 | 240 << 8 | 0, 1};
    TInfo info2 = {10 << 24 | 0 << 16 | 0 << 8 | 1, 255 << 24 | 255 << 16 | 240 << 8 | 0, 2};
    TInfo info3 = {172 << 24 | 16 << 16 | 0 << 8 | 1, 255 << 24 | 255 << 16 | 240 << 8 | 0, 3};
    TInfo info4 = {192 << 24 | 168 << 16 | 2 << 8 | 200, 255 << 24 | 255 << 16 | 240 << 8 | 0, 4};
    TInfo info5 = {10 << 24 | 0 << 16 | 0 << 8 | 2, 255 << 24 | 255 << 16 | 240 << 8 | 0, 5};
    TInfo info6 = {172 << 24 | 16 << 16 | 0 << 8 | 2, 255 << 24 | 255 << 16 | 240 << 8 | 0, 6};
    TInfo info7 = {192 << 24 | 168 << 16 | 3 << 8 | 300, 255 << 24 | 255 << 16 | 248 << 8 | 0, 7};
    TInfo info8 = {10 << 24 | 0 << 16 | 0 << 8 | 3, 255 << 24 | 255 << 16 | 248 << 8 | 0, 8};

    adaugaCalc(retea, "Calc1", "Descriere1", info1);
    adaugaCalc(retea, "Calc2", "Descriere2", info2);
    adaugaCalc(retea, "Calc3", "Descriere3", info3);
    adaugaCalc(retea, "Calc4", "Descriere4", info4);
    adaugaCalc(retea, "Calc5", "Descriere5", info5);
    adaugaCalc(retea, "Calc6", "Descriere6", info6);
    adaugaCalc(retea, "Calc7", "Descriere7", info7);
    adaugaCalc(retea, "Calc8", "Descriere8", info8);
    printf("Convertit: %s\n",convert(2130706433));
    // Open a file for writing
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file for writing.\n");
        return 1;
    }

    // Save the network information to the file
    salvareInFisier(retea, file);
    // Close the file
    fclose(file);

    // Clean up allocated memory
    free(retea->calculatoare);
    free(retea);
    return 0;
}