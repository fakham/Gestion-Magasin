#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct produit {
	char Ref[10];
	char Nom[50];
	float Prix;
	int Nbre;
};

typedef struct produit Produit;

struct Cellule {
	Produit info;
};

typedef struct Cellule *Liste;

void AugmenterNombreExemplaires(Liste Ps, char *Ref, int Nb) {
	
	int i, size = sizeof(Ps) / sizeof(Ps[0]);
	
	for (i = 0; i < size; i++) {
		
		if (strcmp(Ps[i].info.Ref, Ref) == 0) {
			
			Ps[i].info.Nbre += Nb;
			break;
			
		}
		
	}
	
}

void AjoutProduit(Produit P, Liste *Ps) {
	
	int i, pos = 0, size = sizeof(Ps) / sizeof(Ps[0]);
	
	printf("size : %d\n", size);
	
	for (i = 0; i < size; i++) {
			
		if (Ps[i]->info.Prix > P.Prix) {
			
			pos = i;
			break;
			
		}
		
	}
	
	for (i = size - 1; i > pos; i--)
		Ps[i] = Ps[i - 1];
	
	Ps[0]->info = P;
}

Liste lectureProduit(char *nomfichier) {
	
	FILE *f = fopen(nomfichier, "r");
	
	if (f == NULL)
		return NULL;
		
	int size;
	
	printf("Veuillez saisir le nombre de produits : ");
	scanf("%d", &size);
		
	Liste produits = malloc(sizeof(Liste) * size);
	Produit p;
	
	int i;
	for (i = 0; i < size; i++) {
		
		fscanf(f, "%s\t%s\t%f\t%d\n", &p.Ref, &p.Nom, &p.Prix, &p.Nbre);
			
		AjoutProduit(p, produits);
		
	}
	
	fclose(f);
	
	return produits;
}

Produit CommanderProduit(Liste Ps, char *Ref, int qtecommande) {
	
	int i, size = sizeof(Ps) / sizeof(Ps[0]);
	Produit p;
	
	for (i = 0; i < size; i++) {
		
		if (strcmp(Ps[i].info.Ref, Ref) == 0) {
			
			Ps[i].info.Nbre -= qtecommande;
			
			p = Ps[i].info;
			
		}
		
	}
	
	return p;
}

void CommandeClient(Liste Ps, char nomFichier[30]) {
	
	FILE *f = fopen(nomFichier, "w");
	
	if (f == NULL)
		return;
		
	int i, size = sizeof(Ps) / sizeof(Ps[0]);
	
	for (i = 0; i < size; i++) {
		
		fprintf(f, "%s\t%s\t%f\t%d\n", Ps[i].info.Ref, Ps[i].info.Nom, 
									   Ps[i].info.Prix, Ps[i].info.Nbre);
									   
		CommanderProduit(Ps, Ps[i].info.Ref, 1);
		
	}
	
	fclose(f);
	
}

void EtablirFacture(char nomFichier[30]) {
	
	FILE *f = fopen(nomFichier, "r");
	
	if (!f)	return;
	
	float total = 0;
	Produit p;
	
	printf("%20s\t%20s\t%20s\t%20s\t%20s\n","Reference", "Nom", "PrixUnitaire", "Qtecommandé", "PrixTotal");
	
	while( fscanf(f, "%s\t%s\t%f\t%d\n", &p.Ref, &p.Nom, &p.Prix, &p.Nbre) != EOF) {
		
		printf("%20s\t%20s\t%20f\t%20d\t%20f\n", 
			   p.Ref, p.Nom, p.Prix, p.Nbre, p.Nbre * p.Prix);
			   
		total += p.Nbre * p.Prix;
		
	}
	
	printf("\n\n\t\tTOTAL : %20f", total);
	
	fclose(f);
	
}

void Afficher(Liste Ps) {
	
	int i, size = sizeof(Liste) / sizeof(Ps[0]);
	Produit p;
	printf("size : %d\n", size);
	for (i = 0; i < size; i++) {
		
		p = Ps[i].info;
		
		printf("%20s\t%20s\t%20f\t%20d\t%20f\n", p.Ref, p.Nom, p.Prix, p.Nbre);
		
	}
	
}

int main(int argc, char *argv[]) {
	Liste Ps = malloc(sizeof(Liste) * 3);
	
	Produit p1;
	strcpy(p1.Ref, "R001");
	strcpy(p1.Nom, "Stylo");
	p1.Prix = 12;
	p1.Nbre = 7;
	
	Produit p2;
	strcpy(p2.Ref, "R002");
	strcpy(p2.Nom, "Stylo");
	p2.Prix = 17;
	p2.Nbre = 7;
	
	Produit p3;
	strcpy(p3.Ref, "R003");
	strcpy(p3.Nom, "Stylo");
	p3.Prix = 19;
	p3.Nbre = 7;
	
	AjoutProduit(p1, &Ps);
	AjoutProduit(p2, &Ps);
	AjoutProduit(p3, &Ps);
	Afficher(Ps);
	
//	CommandeClient(*Ps, "produits2.txt");
//	
//	EtablirFacture("produits2.txt");
	
	return 0;
}




















