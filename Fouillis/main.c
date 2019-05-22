#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct VignetteDuMot {
    char direction;
    int x,y;
};
typedef struct VignetteDuMot VignetteDuMot;

int n=0,m=0,nmots=0,motsRestant=0;
char grille[100][100];
char cgrille[100][100];
char listeDesMots[200][100];
char clisteDesMots[200];

void IntroduireLaGrille() {
	printf(" Donner les dimentions de la grille (sous forme: nlinges nclones): ");
	scanf("%d %d", &n, &m); getchar();
	printf(" Introduire la grille ligne par ligne (c1 c2 ...):\n\n");
	int i = 0, j;
	for (;i<n;i++) {
		printf("ligne %d: ", i+1);
		for (j=0;j<m;j++) {
			scanf("%c",&grille[i][j]);
			cgrille[i][j]=1;
			if(grille[i][j]==' '||grille[i][j]=='\n') j--;
		}
	} getchar();
}

void IntroduireLaListeDesMots() {
	printf(" Donner le nombre de mots: ");
	scanf("%d", &nmots);
	motsRestant=nmots;
	int i = 0;
	for (i = 0; i < nmots; i++) {
        printf(" Donner le %d mot: ",i+1);
        scanf("%s",listeDesMots[i]);
        clisteDesMots[i]=1;
	}
}

void AfficherLaGrille() {
    printf("  ");
    int i=0,j;
    for(i=0;i<m;i++) printf("%d ",i+1);
    printf("\n");
    for(i=0;i<n;i++) {
        printf("%d ",i+1);
        for(j=0;j<m;j++) {
            printf("%c ",grille[i][j]);
        }
        printf("\n");
    }
}

void AfficherLaListeDesMots() {
    printf("  Mot\n");
    int i=0;
    for(;i<nmots;i++)
        printf("%d %s\n",i+1,listeDesMots[i]);
    printf("\n");
    getch();
}

void AffcherLesLettresNonCoche() {
    int i=0,j;
    for(;i<n;i++) for(j=0;j<m;j++) if(cgrille[i][j]) printf("%c",grille[i][j]);
}

void TrouverUnMot() {
    char mot[100];
    printf("Donner un mot à chercher: ");
    scanf("%s",mot);
    VignetteDuMot vignette;
    vignette.direction=0;
    int i=0,j,k,l,taille=strlen(mot);
    int x[]={0,-1, 0,1};
    int y[]={1, 0,-1,0};
    for(;i<n;i++) {
        for(j=0;j<m;j++) {
            if(mot[0]!=grille[i][j]) continue;
            else
                if(taille==1) {
                    vignette.direction=1;
                    vignette.x=i;
                    vignette.y=j;
                    for(l=0;l<nmots;l++)
                        if(!strcmp(listeDesMots[l],mot)){
                            cgrille[i][j]=0;
                            clisteDesMots[i]=0;
                            motsRestant--;
                        }
                    break;
                }

            for(k=0;k<4;k++) {
                if(i+taille*x[k]<=n&&0<=x+taille*x[k]&&j+taille*y[k]<=m&&0<=j+taille*y[k])
                for(l=1;l<taille;l++) {
                    if(mot[l]!=grille[i+l*x[k]][j+l*y[k]]) break;
                    if(l==taille-1) {
                        vignette.direction=k+1;
                        vignette.x=i;
                        vignette.y=j;
                    }
                }
                if(vignette.direction) {
                    for(l=0;l<nmots;l++)
                        if(!strcmp(listeDesMots[l],mot)){
                            clisteDesMots[i]=0;
                            motsRestant--;
                            int m=0;
                            for(;m<taille;m++)
                                cgrille[i+m*x[k]][j+m*y[k]]=0;
                        }
                    break;
                }
            }
            if(vignette.direction) break;
        }
        if(vignette.direction) break;
    }
    if(vignette.direction) {
        printf("\n Le mot %s est trouve a (%d,%d)",mot,vignette.x+1,vignette.y+1);
        if(taille>1)
            switch(vignette.direction) {
                case 1:
                    printf("direction vers la droite");
                    break;
                case 2:
                    printf("direction vers le haut");
                    break;
                case 3:
                    printf("direction vers la gauche");
                    break;
                case 4:
                    printf("direction vers le bas");
                    break;
            }
        printf("\n");
    }
    else {
        printf("Desole mot non trouve\n");
    }
    if(motsRestant==0) {
        printf("Felicitation mot resultant: ");
        AffcherLesLettresNonCoche();
        printf("\n");
    }
    getch();
}

void printMenu() {
    system("cls");
	printf(" ###########################################\n");
	printf(" #                                         #\n");
	printf(" #  1- Introduire la grille                #\n");
	printf(" #  2- Introduire la liste des mots        #\n");
	printf(" #  3- Afficher la grille                  #\n");
	printf(" #  4- Afficher la liste des mots          #\n");
	printf(" #  5- Rechercher un mot dans la grille    #\n");
	printf(" #  6- Lettres non coche                   #\n");
	printf(" #  7- Quitter                             #\n");
	printf(" #                                         #\n");
	printf(" ###########################################\n");
	printf("\n  Choisir le numéro coresspondant: ");
	switch (getchar()) {
	case '1':
	    getchar();
		system("cls");
        IntroduireLaGrille();
		break;

	case '2':
	    getchar();
		system("cls");
        IntroduireLaListeDesMots();
		break;

	case '3':
	    getchar();
		system("cls");
        AfficherLaGrille();
        getch();
		break;

	case '4':
	    getchar();
		system("cls");
        AfficherLaListeDesMots();
		break;

	case '5':
	    getchar();
		system("cls");
        TrouverUnMot();
		break;

	case '6':
	    getchar();
		system("cls");
		printf("Les lettres non coche sont: ");
        AffcherLesLettresNonCoche();
        printf("\n");
		break;
	case '7':
        exit(0);
		break;
	}
}

int main(int argc, char** argv) {
    while(1) {
        printMenu();
    }
    return 0;
}

