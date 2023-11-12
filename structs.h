/* structs.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_caracters 51
//  nr maxim de caractere al numelui unui director/fisier
#define zece 10
//  nr maxim de caractere al unei comenzi

typedef struct Director
{
    char *nume;
    struct Director *parinte, *directories, *st, *dr;
    struct Fisier *files;
} *ArbDirector, director;

typedef struct Fisier
{
    char *nume;
    struct Director *parinte;
    struct Fisier *st, *dr;
} *ArbFisier, fisier;

//  Operatii cu arbori de fisiere si directoare

ArbDirector ConstrArbDir(char *nume, ArbDirector parinte);
//  intoarce adresa directorului cu informatiile date
//  sau NULL daca nu s-a putut face alocarea memoriei

ArbFisier ConstrArbFis(char *nume, ArbDirector parinte);
//  intoarce adresa fisierului cu informatiile date
//  sau NULL daca nu s-a putut face alocarea memoriei

int InserareFisier(ArbDirector parinte, ArbFisier files, char *nume, int file);
//  inserare in arborele files, aceasta functie are si rolul de a cauta daca
//  exista un fisier cu numele dat, cand se doreste doar cautarea fisierului
//  functia este apelata cu file = 0, altfel cu file = 1

int InserareDirector(ArbDirector parinte,
    ArbDirector directories, char *nume, int directory);
//  inserare in arborele directories, similara cu InserareFisier
//  cand se doreste doar cautarea directorului functia este apelata
//  cu directory = 0, altfel cu directory = 1

void Ls(ArbDirector Director_Curent);
//  parcurgerile SRD ale arborelui directories si ale arborelui de fisiere
//  (folosind doua functii auxiliare pentru cele doua tipuri de arbori)
//  si printarea elementelor cu " " intre ele

void DistrugeArbore(ArbDirector root);
//  functie recursiva de eliberare a memoriei
//  foloseste functia auxiliara DistrugeArbFiles

ArbFisier Rm(ArbFisier files, char *nume);
//  functia gaseste fisierul cautat in arborele files si in functie
//  de tipul nodului face eliminarea

ArbDirector Rmdir(ArbDirector directories, char *nume);
//  similar cu Rm, elimina si arborele de fisiere din directorul
//  eliminat

void Pwd(ArbDirector DirectorCurent);
//  funcite recursiva care merge din parinte in parinte pana ajunge la
//  root de unde incepe sa printeze directoarele pana la directorul curent

ArbDirector Cd(ArbDirector DirectorCurent, char *nume);
//  parcurge arborele directories pana gaseste directorul nume si intoarce
//  adresa acestuia, daca nu il gaseste printeaza un mesaj si intoarce adresa
//  directorului initial

int FindFile(ArbDirector root, char *nume);

int FindDir(ArbDirector root, char *nume);

