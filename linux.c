/* Mitulescu Ilie 314 CB */
#include "structs.h"


int main ()
{
char *comanda = (char*)malloc(zece);
char *nume = (char*)malloc(MAX_caracters);
if(!comanda || !nume)
return 1;
ArbDirector root = ConstrArbDir("root", NULL);
if(!root)
return 1;
ArbDirector DirectorCurent = root;
//  Cu ajutorul DirectorCurent putem parcurge arborele de directoare.
//  Acesta este initializat cu directorul root.

while(1)
{
scanf("%s", comanda);
if(strcmp(comanda, "touch") == 0)
{
	scanf("%s", nume);
	//  Verificam daca exista un director cu acest nume.
	if(InserareDirector(DirectorCurent,
	DirectorCurent->directories, nume, 0) == 0)
		printf("Directory %s already exists!\n", nume);
	else
	{
	//  Verificam daca este exista alte fisiere in director.
	if(DirectorCurent->files == NULL)
	{
		//  Daca nu, noul fisier este radacina arborelui de fisiere.
		ArbFisier f = ConstrArbFis (nume, DirectorCurent);
		if(!f)
		return 1;
		else
		DirectorCurent->files = f;
	}
	else
	{
		//  Daca da, introducem noul fisier in arborele de fisiere.
		//  Verificam introducerea corecta si daca numele este unic.
		int exista;
		exista = InserareFisier(DirectorCurent, DirectorCurent->files,nume, 1);
		if(exista == -1)
		printf("error\n");
		else if (exista == 0)
		printf("File %s already exists!\n", nume);
	}
	}
}
else if(strcmp(comanda, "mkdir") == 0)
{
	scanf("%s", nume);
	//  Verificam daca exista un fisier cu acest nume.
	if(InserareFisier(DirectorCurent, DirectorCurent->files, nume, 0) == 0)
	printf("File %s already exists!\n", nume);
	else
	{
	//  Verificam daca este exista alte directoare in director.
	//  Similar cu introducerea la fisiere.
	if(DirectorCurent->directories == NULL)
	{
		ArbDirector d = ConstrArbDir (nume, DirectorCurent);
		if(!d)
		return 1;
		else
		DirectorCurent->directories = d;
	}
	else
	{
		int exista;
		exista = InserareDirector(DirectorCurent,
		DirectorCurent->directories, nume, 1);
		if(exista == -1)
		printf("error\n");
		else if (exista == 0)
		printf("Directory %s already exists!\n", nume);
	}
	}
}
else if(strcmp(comanda, "ls") == 0)
{
	Ls(DirectorCurent);
}
else if(strcmp(comanda, "rm") == 0)
{
	scanf("%s", nume);
	//  Verificam daca exista un fisier cu acest nume.
	if(InserareFisier(DirectorCurent, DirectorCurent->files, nume, 0) == 1)
	printf("File %s doesn't exist!\n", nume);
	else
	DirectorCurent->files = Rm(DirectorCurent->files, nume);
}
else if(strcmp(comanda, "rmdir") == 0)
{
	scanf("%s", nume);
	//  Verificam daca exista un director cu acest nume.
	if(InserareDirector(DirectorCurent, DirectorCurent->directories, nume, 0) == 1)
	printf("Directory %s doesn't exist!\n", nume);
	else
	DirectorCurent->directories = Rmdir(DirectorCurent->directories, nume);
}
else if(strcmp(comanda, "cd") == 0)
{
	scanf("%s", nume);
	if(strcmp(nume,"..") == 0)
	{
		//  Directorul root nu are parinte, asa ca ramane neschimbat.
		if(strcmp(DirectorCurent->nume,"root") != 0)
		DirectorCurent = DirectorCurent -> parinte;
	}
	else
	{
		DirectorCurent = Cd(DirectorCurent, nume);
	}
}
else if(strcmp(comanda, "pwd") == 0)
{
	Pwd(DirectorCurent);
	printf("\n");
}
else if(strcmp(comanda, "find") == 0)
{
	//  Cu variabila found verificam daca fisierul/directorul exista.
	int found = 0;
	scanf("%s", comanda);
	if(strcmp(comanda, "-f") == 0)
	{
		scanf("%s", nume);
		found = FindFile(root,nume);
		if(found == 0)
		printf("File %s not found!\n", nume);
	}
	else if(strcmp(comanda, "-d") == 0)
	{
		scanf("%s", nume);
		found = FindDir(root,nume);
		if(found == 0)
		printf("Directory %s not found!\n", nume);
	}
}
else if(strcmp(comanda, "quit") == 0)
{
	//  Eliberam memoria si iesim din while.
	free(comanda);
	free(nume);
	DistrugeArbore(root);
	break;
}
}
return 0;
}