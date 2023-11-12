/* functii-Arb.c */

#include "structs.h"

ArbFisier ConstrArbFis(char *nume, ArbDirector parinte)
{
    ArbFisier aux = (ArbFisier)malloc(sizeof(fisier));
    if(!aux)
    return NULL;
    aux->nume = malloc(MAX_caracters);
    if(!aux->nume)
    return NULL;
    strcpy(aux->nume, nume);
    aux->parinte = parinte;
    aux->st = NULL;
    aux->dr = NULL;
    return aux;
}

ArbDirector ConstrArbDir(char *nume, ArbDirector parinte)
{
    ArbDirector aux = (ArbDirector)malloc(sizeof(director));
    if(!aux)
    return NULL;
    aux->nume = malloc(MAX_caracters);
    if(!aux->nume)
    return NULL;
    strcpy(aux->nume, nume);
    aux->parinte = parinte;
    aux->st = NULL;
    aux->dr = NULL;
    aux->directories = NULL;
    aux->files = NULL;
    return aux;
}

int InserareFisier(ArbDirector parinte, ArbFisier files, char *nume, int file)
{
    ArbFisier f = files, p;
    while(f != NULL)
    {
    p = f;
    if(strcmp(f->nume,nume) == 0)
    return 0;
    if(strcmp(f->nume,nume) > 0)
    f = f->st;
    else
    f = f->dr;
    }
    if(file == 1)
    {
    ArbFisier aux =  ConstrArbFis(nume, parinte);
    if(!aux)
    return -1;
    if(strcmp(nume,p->nume) < 0)
    p->st = aux;
    else
    p->dr = aux;
    }
    return 1;
}

int InserareDirector(ArbDirector parinte, ArbDirector directories,
    char *nume, int directory)
{
    ArbDirector d = directories, p;
    while(d != NULL)
    {
    p = d;
    if(strcmp(d->nume,nume) == 0)
    return 0;
    if(strcmp(d->nume,nume) > 0)
    d = d->st;
    else
    d = d->dr;
    }
    if(directory == 1)
    {
    ArbDirector aux =  ConstrArbDir(nume, parinte);
    if(!aux)
    return -1;
    if(strcmp(nume,p->nume) < 0)
    p->st = aux;
    else
    p->dr = aux;
    }
    return 1;
}

void SRDFisier(ArbFisier f)
{
	if(!f)
    return;
	if(!f->st && !f->dr) 
    {
        printf("%s ", f->nume);
        return;
    }
	SRDFisier(f->st);
	printf("%s ", f->nume);
	SRDFisier(f->dr);
}

void SRDDirector(ArbDirector d)
{
	if(!d)
    return;
	if(!d->st && !d->dr) 
    {
        printf("%s ", d->nume);
        return;
    }
	SRDDirector(d->st);
	printf("%s ", d->nume);
	SRDDirector(d->dr);
}

void Ls(ArbDirector DirectorCurent)
{
    SRDDirector(DirectorCurent->directories);
    SRDFisier(DirectorCurent->files);
    printf("\n");
}

//  Functie auxiliara pentru a distruge arborele de fisiere dintr-un director.
void DistrugeArbFiles(ArbFisier files)
{
    if(!files)
    return;
    DistrugeArbFiles(files->st);
    DistrugeArbFiles(files->dr);
    free(files->nume);
    free(files);
}

void DistrugeArbore(ArbDirector root)
{
    if(!root)
    return;
    DistrugeArbFiles(root->files);
    DistrugeArbore(root->directories);
    DistrugeArbore(root->st);
    DistrugeArbore(root->dr);
    free(root->nume);
    free(root);
}

//  Funcitie care returneaza valoarea minima dintr-un subarbore de fisiere
//  cu radacina "file".
ArbFisier MinFisier(ArbFisier file)
{
    ArbFisier min = file;
    while(min != NULL && min->st != NULL)
    min = min->st;
    return min;
}

ArbFisier Rm(ArbFisier files, char *nume)
{
    if(files == NULL)
    return NULL;
    //  Cautam fisierul ce trebuie eliminat.
    if(strcmp(files->nume, nume) > 0)
    files->st = Rm(files->st, nume);
    else if(strcmp(files->nume, nume) < 0)
    files->dr = Rm(files->dr, nume);
    else
    {
    //  Am gasit fisierul pe care vrem sa il eliminam, verificam tipul sau.
    if(files->st == NULL && files->dr == NULL)
    {
        //  Cazul in care este frunza, stergem nodul.
        free(files->nume);
        free(files);
        files = NULL;
    }
    else if(files->dr == NULL)
    {
        //  Cazul in care are doar fiu stanga, il inlocuim cu fiu stanaga.
        ArbFisier aux = files;
        files = files->st;
        free(aux->nume);
        free(aux);
        aux = NULL;
    }
     else if(files->dr == NULL)
    {
        //  Cazul in care are doar fiu dreapta, il inlocuim cu fiu dreapta.
        ArbFisier aux = files;
        files = files->dr;
        free(aux->nume);
        free(aux);
        aux = NULL;
    }
    else
    {
        //  Cazul in care este are doi fii, inlocuim cu min subarborelui drept.
        ArbFisier aux = MinFisier(files->dr);
        strcpy(files->nume,aux->nume);
        files->dr = Rm(files->dr,aux->nume);
    }
    }
    return files;
}

//  Funcitie care returneaza adresa minimului dintr-un subarbore de directoare
//  cu radacina "dir".
ArbDirector MinDirector(ArbDirector dir)
{
    ArbDirector min = dir;
    while(min != NULL && min->st != NULL)
    min = min->st;
    return min;
}

ArbDirector Rmdir(ArbDirector directories, char *nume)
{
    if(directories == NULL)
    return NULL;
    //  Cautam directorul ce trebuie eliminat.
    if(strcmp(directories->nume, nume) > 0)
    directories->st = Rmdir(directories->st, nume);
    else if(strcmp(directories->nume, nume) < 0)
    directories->dr = Rmdir(directories->dr, nume);
    else
    {
    //  Am gasit directorul pe care vrem sa il eliminam, verificam tipul sau.
    if(directories->st == NULL && directories->dr == NULL)
    {
        //  Cazul in care este frunza, stergem nodul.
        free(directories->nume);
        DistrugeArbFiles(directories->files);
        free(directories);
        directories = NULL;
    }
    else if(directories->dr == NULL)
    {
        //  Cazul in care are doar fiu stanga, il inlocuim cu fiu stanaga.
        ArbDirector aux = directories;
        directories = directories->st;
        free(aux->nume);
        DistrugeArbFiles(aux->files);
        free(aux);
        aux = NULL;
    }
     else if(directories->dr == NULL)
    {
         //  Cazul in care are doar fiu stanga, il inlocuim cu fiu dreapta.
        ArbDirector aux = directories;
        directories = directories->dr;
        free(aux->nume);
        DistrugeArbFiles(aux->files);
        free(aux);
        aux = NULL;
    }
    else
    {
        //  Cazul in care este are doi fii, inlocuim cu min subarborelui drept.
        ArbDirector aux = MinDirector(directories->dr);
        strcpy(directories->nume, aux->nume);
        DistrugeArbFiles(directories->files);
        directories->files = aux->files;
        directories->dr = Rmdir(directories->dr,aux->nume);
    }
    }
    return directories;
}

ArbDirector Cd(ArbDirector DirectorCurent, char *nume)
{
    //  Parcurem arborele utilizand directorul auxiliar d.
    ArbDirector d = DirectorCurent->directories;
    while(d != NULL)
    {
    if(strcmp(d->nume,nume) == 0)
    return d;
    //  Daca se gaseste directorul cautat acesta este intors.
    if(strcmp(d->nume,nume) > 0)
    d = d->st;
    else
    d = d->dr;
    }
    //  Daca in urma parcurgeri nu s-a gasit directorul cautat se printeaza
    //  mesajul corespunzator si se intoarce directorul initial.
    printf("Directory not found!\n");
    return DirectorCurent;
}

void Pwd(ArbDirector DirectorCurent)
{
    if(strcmp(DirectorCurent->nume,"root") == 0)
    {
    printf("/root");
    return;
    }
    Pwd(DirectorCurent->parinte);
    printf("/%s",DirectorCurent->nume);
}

int FindFileAux(ArbFisier files, char *nume)
{
    if(!files)
    return 0;
    if(strcmp(files->nume,nume) == 0)
    {
        return 1;
    }
    else
    return FindFileAux(files->st, nume) + FindFileAux(files->dr, nume);
}

int FindFile(ArbDirector root, char *nume)
{
    if(!root)
    return 0;
    FindFileAux(root->files, nume);
    if(FindFileAux(root->files, nume))
    {
        printf("File %s found!\n", nume);
        Pwd(root);
        printf("\n");
        return 1;
    }
    else
    return FindFile(root->directories, nume) + FindFile(root->st, nume)
    + FindFile(root->dr, nume);
}

int FindDir(ArbDirector root, char *nume)
{
    if(!root)
    return 0;
    if(strcmp(root->nume,nume) == 0)
    {
        printf("Directory %s found!\n", nume);
        Pwd(root);
        printf("\n");
        return 1;
    }
    else
    return FindDir(root->directories, nume) + FindDir(root->st, nume)
    + FindDir(root->dr, nume);
}