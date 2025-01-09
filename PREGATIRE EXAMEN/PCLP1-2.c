#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char *nume;
    int an;
    struct TActor *distributie[100];
    int nrCrtD;
} TFilm;
typedef struct
{
    char *nume;
    int nrCrtFilme;
    TFilm *filme[100];
} TActor;
typedef struct
{
    int nrCrtFilme, nrMaxFilme, nrCrtActori, nrMaxActori;
    TActor *actori;
    TFilm *filme;
    TActor **idxActori;
    TFilm **idxFilme;
} TIMDB;
TIMDB *allocTIMDB(int nrMaxFilme, int nrMaxActori)
{
    TIMDB *t = malloc(sizeof(TIMDB));
    if (t == NULL)
    {
        return NULL;
    }
    t->actori = malloc(nrMaxActori * sizeof(TActor));
    if (t->actori == NULL)
    {
        free(t);
        return NULL;
    }
    t->filme = malloc(nrMaxFilme * sizeof(TFilm));
    if (t->filme == NULL)
    {
        free(t->actori);
        free(t);
        return NULL;
    }
    t->idxActori = malloc(nrMaxActori * sizeof(TActor *));
    if (t->idxActori == NULL)
    {
        free(t->actori);
        free(t->filme);
        free(t);
        return NULL;
    }
    t->idxFilme = malloc(nrMaxFilme * sizeof(TFilm *));
    if (t->idxFilme == NULL)
    {
        free(t->actori);
        free(t->filme);
        free(t->idxActori);
        free(t);
        return NULL;
    }
    t->nrCrtActori = 0;
    t->nrMaxActori = nrMaxActori;
    t->nrCrtFilme = 0;
    t->nrMaxFilme = nrMaxFilme;
    return t;
}
void adaugaActor(TIMDB *imdb, char *nume)
{
    if (imdb->nrCrtActori >= imdb->nrMaxActori)
    {
        imdb->actori = realloc(imdb->actori, (imdb->nrMaxActori * 2) * sizeof(TActor));
        if (imdb->actori == NULL)
        {
            // Handle realloc failure
            fprintf(stderr, "Error: Unable to allocate memory for actors.\n");
            exit(EXIT_FAILURE);
        }
        imdb->idxActori = realloc(imdb->idxActori, (imdb->nrMaxActori * 2) * sizeof(TActor *));
        if (imdb->idxActori == NULL)
        {
            // Handle realloc failure
            fprintf(stderr, "Error: Unable to allocate memory for actor index.\n");
            exit(EXIT_FAILURE);
        }
        imdb->nrMaxActori *= 2;
    }

    imdb->actori[imdb->nrCrtActori].nume = strdup(nume);
    if (imdb->actori[imdb->nrCrtActori].nume == NULL)
    {
        // Handle strdup failure
        fprintf(stderr, "Error: Unable to allocate memory for actor name.\n");
        exit(EXIT_FAILURE);
    }

    imdb->idxActori[imdb->nrCrtActori] = &imdb->actori[imdb->nrCrtActori];
    imdb->nrCrtActori++;
}
void adaugaFilmIMDB(TIMDB *imdb, char *nume)
{
    if (imdb->nrCrtFilme >= imdb->nrMaxFilme)
    {
        imdb->filme = realloc(imdb->filme, (imdb->nrMaxFilme * 2) * sizeof(TFilm));
        if (imdb->filme == NULL)
        {
            // Handle realloc failure
            fprintf(stderr, "Error: Unable to allocate memory for films.\n");
            exit(EXIT_FAILURE);
        }
        imdb->idxFilme = realloc(imdb->idxFilme, (imdb->nrMaxFilme * 2) * sizeof(TFilm *));
        if (imdb->idxFilme == NULL)
        {
            // Handle realloc failure
            fprintf(stderr, "Error: Unable to allocate memory for film index.\n");
            exit(EXIT_FAILURE);
        }
        imdb->nrMaxFilme *= 2;
    }

    imdb->filme[imdb->nrCrtFilme].nume = strdup(nume);
    if (imdb->filme[imdb->nrCrtFilme].nume == NULL)
    {
        // Handle strdup failure
        fprintf(stderr, "Error: Unable to allocate memory for film name.\n");
        exit(EXIT_FAILURE);
    }

    imdb->idxFilme[imdb->nrCrtFilme] = &imdb->filme[imdb->nrCrtFilme];
    imdb->nrCrtFilme++;
}
//DE LA CHAT GPT

// Function to compare two actors by name for qsort
int compareActors(const void *a, const void *b)
{
    return strcmp((*(TActor **)a)->nume, (*(TActor **)b)->nume);
}

// Function to compare two films by name for qsort
int compareFilms(const void *a, const void *b)
{
    return strcmp((*(TFilm **)a)->nume, (*(TFilm **)b)->nume);
}

// Function to create and sort idxActori
void createAndSortIdxActori(TIMDB *imdb)
{
    imdb->idxActori = malloc(imdb->nrCrtActori * sizeof(TActor *));
    if (imdb->idxActori == NULL)
    {
        // Handle malloc failure
        fprintf(stderr, "Error: Unable to allocate memory for actor index.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < imdb->nrCrtActori; i++)
    {
        imdb->idxActori[i] = &imdb->actori[i];
    }

    qsort(imdb->idxActori, imdb->nrCrtActori, sizeof(TActor *), compareActors);
}

// Function to create and sort idxFilme
void createAndSortIdxFilme(TIMDB *imdb)
{
    imdb->idxFilme = malloc(imdb->nrCrtFilme * sizeof(TFilm *));
    if (imdb->idxFilme == NULL)
    {
        // Handle malloc failure
        fprintf(stderr, "Error: Unable to allocate memory for film index.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < imdb->nrCrtFilme; i++)
    {
        imdb->idxFilme[i] = &imdb->filme[i];
    }

    qsort(imdb->idxFilme, imdb->nrCrtFilme, sizeof(TFilm *), compareFilms);
}
//END DE LA CHAT GPT
TFilm *getFilm(TIMDB *t, char *nume)
{
    for (int i = 0; i < t->nrCrtFilme; i++)
    {
        if (strcmp(t->filme[i].nume,nume) == 0)
        {
            return t->filme + i;
        }
    }
    return NULL;
}
TActor *getActor(TIMDB *t, char *nume)
{
    for (int i = 0; i < t->nrCrtActori; i++)
    {
        if (strcmp(t->actori[i].nume,nume) == 0)
        {
            return t->actori + i;
        }
    }
    return NULL;
}
TActor * adaugaActorFilm(TIMDB * imdb, char * numeActor,char * numeFilm) {
    TActor* actor = getActor(imdb,numeActor);
    TFilm* film = getFilm(imdb,numeFilm);
    if(film->nrCrtD >= 100 || actor->nrCrtFilme >= 100) {
        return NULL;
    }
    film->distributie[film->nrCrtD++] = (struct TActor *)actor;
    actor->filme[actor->nrCrtFilme++] = film;
    return actor;
}
TFilm *adaugaFilm(TIMDB* imdb,char * nume){
    TFilm film;
    film.nume = malloc(strlen(nume));
    if(film.nume == NULL) {
        return NULL;
    }
    strcpy(film.nume, nume);
    if(imdb->nrCrtFilme >= imdb->nrMaxActori) {
        imdb->filme = realloc(imdb->filme,(++imdb->nrMaxFilme) * sizeof(TFilm));
        if(imdb->filme == NULL) {
            return NULL;
        }
        imdb->idxFilme = realloc(imdb->idxFilme,(++imdb->nrMaxActori) * sizeof(TActor *));
        if(imdb->idxFilme == NULL) {
            return NULL;
        }
    }
    imdb->filme[imdb->nrCrtFilme++] = film;
    // resortam
    for (int i = 0; i < imdb->nrCrtFilme; i++)
    {
        if (strcmp(imdb->idxFilme[i]->nume,nume) < 0)
        {
            for (int j = i + 1; i < imdb->nrCrtFilme; j++)
            {
                imdb->idxFilme[j + 1] = imdb->idxFilme[j];
            }
            imdb->idxFilme[i + 1] = imdb->filme + (imdb->nrCrtFilme - 1);
        }
    }
    return imdb->filme + (imdb->nrCrtFilme - 1);
}
void freeTot(TIMDB * imdb) {
    free(imdb->idxActori);
    free(imdb->idxFilme);
    free(imdb->actori);
    free(imdb->filme);
    free(imdb);
}
//TOT DE LA CHATGPT
void printActorsInFilm(TIMDB *imdb, char *filmName)
{
    printf("\nActors in %s: ", filmName);
    TFilm *film = getFilm(imdb, filmName);
    if (film != NULL)
    {
        for (int i = 0; i < film->nrCrtD; i++)
        {
            TFilm *film =  (TFilm *)film->distributie[i];
            printf("%s ", film->nume);
        }
    }
    printf("\n");
}

void printFilmsOfActor(TIMDB *imdb, char *actorName)
{
    printf("Films of %s: ", actorName);
    TActor *actor = getActor(imdb, actorName);
    if (actor != NULL)
    {
        for (int i = 0; i < actor->nrCrtFilme; i++)
        {
            printf("%s ", actor->filme[i]->nume);
        }
    }
    printf("\n");
}

void printSortedActors(TIMDB *imdb)
{
    printf("Sorted Actors:\n");
    for (int i = 0; i < imdb->nrCrtActori; i++)
    {
        printf("%s\n", imdb->idxActori[i]->nume);
    }
}

void printSortedFilms(TIMDB *imdb)
{
    printf("Sorted Films:\n");
    for (int i = 0; i < imdb->nrCrtFilme; i++)
    {
        printf("%s\n", imdb->idxFilme[i]->nume);
    }
}

int main()
{
    TIMDB *imdb = allocTIMDB(10, 10);

    // Adding actors and films
    adaugaActor(imdb, "Actor3");
    adaugaActor(imdb, "Actor1");
    adaugaActor(imdb, "Actor2");

    adaugaFilmIMDB(imdb, "Film2");
    adaugaFilmIMDB(imdb, "Film1");

    // Creating and sorting index vectors
    createAndSortIdxActori(imdb);
    createAndSortIdxFilme(imdb);

    //adaugaFilm(imdb, "Film2");
    //adaugaFilm(imdb, "Film1");

    // Displaying information using IMDb
    printSortedActors(imdb);
    printSortedFilms(imdb);
    printActorsInFilm(imdb, "Film1");
    printFilmsOfActor(imdb, "Actor1");

    // Adding actors to films
    adaugaActorFilm(imdb, "Actor1", "Film1");
    adaugaActorFilm(imdb, "Actor2", "Film1");
    adaugaActorFilm(imdb, "Actor3", "Film2");

    // Freeing allocated memory
    freeTot(imdb);

    return 0;
}