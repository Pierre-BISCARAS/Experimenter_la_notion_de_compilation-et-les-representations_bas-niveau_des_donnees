// Pierre BISCARAS


#include <stdio.h> // inclusion de la bibliotheque d'entrees/sorties
#include <stdlib.h> // inclusion de la bibliotheque standard
#include <stdbool.h>


#define max_ligne 6
#define max_colonne 7

typedef char grille[max_ligne][max_colonne];



void initGrille(grille G) {
    int i,j;
    for (i =0;i<max_ligne; i++) {
        for (j=0;j<max_colonne; j++)
            G[i][j] = '_';
        
    }
    
}

void afficheGrille(grille G) {
    int i,j,k;
    printf("%s", "    1   2   3   4   5   6   7  ");
    printf("\n");

    k = 0;

    for (i =0; i<max_ligne; i++) { 
        printf("%i |",i+1 );
        for (j=0;j<max_colonne; j++) 
            printf(" %c |", G[i][j]);
        printf("\n");
    }

}


int grillepleine(grille G) {
    int i,j = -1;
    int ok = 1;
    for (i =0;i<max_ligne; i++) {
        for (j=0;j<max_colonne; j++)
            if (G[i][j] == '_'){
                ok = 0;
            }
    }
    return (ok);
}

int charger_partie(char nomfic[], grille g, int *joueur)
{
    FILE *f; /* fichier a lire */
    int i,j; // entiers utilises comme compteurs dans les boucles for

    if ((f=fopen(nomfic,"r"))==NULL)  // si fopen renvoie un resultat NULL alors echec de l'ouverture du fichier
    {
        return(0); // retourne 0 (faux) pour indiquer une erreur
    }
    else // sinon le fichier est ouvert et accessible en lecture (choix de "r" pour read lors de l'ouverture)
    {
        // on suppose dans la suite que le fichier est correct et ne necessite pas de verification des donnees
        printf("Ouverture du fichier %s reussie.\n",nomfic);
        // lecture du fichier a l'aide de fscanf dont chaque appel permet de lire tout en avancant dans le fichier
        fscanf(f,"%i",joueur); /* recuperation depuis le fichier f du nombre d'etudiants stocke dans la valeur pointee par ptr_nb_et */
        for (i = 0; i < 6; i++)
            for (j = 0; j < 7; j++)
            fscanf(f, " %c ", &g[i][j]);
                 // la note est un reel et doit etre passee par adresse pour etre lue

        
        fclose(f); // fermeture du fichier
        printf("Lecture des donnees terminee.\n\n");
        return(1); // retourne 1 (!=0 donc vrai) pour indiquer qu'il n'y a pas d'erreur
    }
        
}


void sauvegarder_fichier_notes(char nomfic[], grille g, int joueur)
{
    FILE *f; /* fichier a ecrire */
    int i,j; // entiers utilises comme compteurs dans les boucles for
    int ecrasement; /* pour choisir entre l'écrasement ou pas d'un fichier existant */
    char choix; /* choix de reponse saisi par l'utilisateur */

    ecrasement=1; // par defaut choisir d'ecraser le fichier existant
    if ((f=fopen(nomfic,"r"))!=NULL) // si l'ouverture en lecture "r" (read) fonctionne alors le fichier existe deja
    {
        fclose(f); // fermer le fichier
        do // demander a l'utilisateur si il veut ecraser le fichier
        {
            printf("Le fichier %s existe, voulez-vous l'ecraser ? (o/n) ",nomfic);
            scanf(" %c",&choix); /* Lecture du choix de l'utilisateur */
        }
        while (choix!='o' && choix!='n'); // tant que la reponse n'est ni 'o' ni 'n'
        if (choix=='n')
        {
            ecrasement=0; // si la reponse est 'n' alors annuler l'ecrasement du fichier
        }
    }
    if (ecrasement) // si ecrasement n'est pas 0 alors ecriture du fichier
    {
        if ((f=fopen(nomfic,"w"))==NULL) // ouverture du fichier en ecriture "w" (write) et teste si retour NULL alors probleme
            printf("Erreur lors de la creation du fichier %s\n",nomfic);
        else // ouverture en ecriture reussie
        {
            // ecriture du fichier a l'aide de fprintf dont chaque appel permet d'ecrire tout en avancant dans le fichier
            fprintf(f,"%d\n",joueur); /* ecriture du nombre d'etudiants */

            fprintf(f,"\n"); // retour a la ligne apres l'ecriture des coefficients
            for (i=0; i<max_ligne; i++) /* parcours de chaque ligne */
            {
                for (j=0; j<max_colonne; j++) /* ecriture de chaque note */
                    fprintf(f," %c ",g[i][j]);
                fprintf(f,"\n"); // retour a la ligne apres l'ecriture d'une ligne de notes
            }
            fclose(f);
        }
    }
}

void ajoutejeton(grille G, int j) {
    int colonne,ok;
    int i = 5;
    ok = 0;

    printf("Sur quelle colonne voulez vous placez votre piece entre 1-7(10 pour save)");
    scanf("%d", &colonne);

    colonne -= 1;
    while  (ok == 0) {


        if (colonne == 9) {
            sauvegarder_fichier_notes("save",G,j);
            ok = 0;
            break;
        }

        if (G[0][colonne] == '_' && colonne < 7) {

            do {
                
                if ( G[i][colonne] == '_'){
                    

                    if (j == 1) {
                        G[i][colonne] = 'X';
                        ok = 1;
                    }
                    if (j == 0) {
                        G[i][colonne] = 'O';
                        ok = 1;
                    }
                    
                }
                else {
                    i = i-1;
                }
                
            } while (i < 0 || ok == 0);

        
        }
        else {
            printf("\nLa colonne est pleine\n");
            printf("Sur quelle colonne voulez vous placez votre piece entre 1-7 (10 pour save)");
            scanf("%d", &colonne);
            colonne -= 1;

    } 
    }
}


int verifLigne(grille G, int joueur){
    int i, j;
    int compteur = 0;
    if (joueur == 1){
        for (i=0; i<=max_ligne;i++){
            for (j=0; j<=max_colonne;j++){
                if(G[i][j]=='X'){
                    compteur++;
                }
                if (G[i][j]!='X') {
                    compteur = 0;
                }

                if(compteur==4){
                    return 1;
                }
            }
            compteur=0;
        }
        return 0;
    }
    if (joueur == 0){
        for (i=0; i<=max_ligne;i++){
            for (j=0; j<=max_colonne;j++){
                if(G[i][j]=='O'){
                    compteur++;
                }
                if (G[i][j]!='O') {
                    compteur = 0;
                }
                if(compteur==4){
                    return 1;
                }
            }
            compteur=0;
        }
        return 0;
    }
}

int verifCol(grille G, int joueur){
    int i, j;
    int compteur = 0;
    if (joueur == 1){
        for (i=0; i<=max_colonne;i++){
            for (j=0; j<=max_ligne;j++){
                if(G[j][i]=='X'){
                    compteur++;
                }
                if(G[j][i]!='X') {
                    compteur=0;
                }
                if(compteur==4){
                    return 1;
                }
            }
            compteur=0;
        }
        return 0;
    }
    if (joueur == 0){
        for (i=0; i<=max_colonne;i++){
            for (j=0; j<=max_ligne;j++){
                if(G[j][i]=='O'){
                    compteur++;
                }
                if (G[j][i]!='O') {
                    compteur = 0;
                }
                if(compteur==4){
                    return 1;
                }
            }
            compteur=0;
        }
        return 0;
    }
}


int verifDiag(grille G, int joueur){
    int i,j;
    if(joueur==1){
        for (i=0; i<=max_ligne;i++){
            for (j=0; j<=max_colonne;j++){
                if(G[i][j]=='X' && G[i+1][j+1]=='X' && G[i+2][j+2]=='X' && G[i+3][j+3]=='X'){
                    return 1;
                } if(G[i][j]=='X' && G[i-1][j-1]=='X' && G[i-2][j-2]=='X' && G[i-3][j-3]=='X'){
                    return 1;
                } if(G[i][j]=='X' && G[i+1][j-1]=='X' && G[i+2][j-2]=='X'&& G[i+3][j-3]=='X'){
                    return 1;
                } if(G[i][j]=='X' && G[i-1][j+1]=='X' && G[i-2][j+2]=='X'&& G[i-3][j+3]=='X'){
                    return 1;
                }
            }
        }
        return 0;
    }
    if(joueur==0){
        for (i=0; i<=max_ligne;i++){
            for (j=0; j<=max_colonne;j++){
                if(G[i][j]=='O' && G[i+1][j+1]=='O' && G[i+2][j+2]=='O' && G[i+3][j+3]=='O'){
                    return 1;
                } if(G[i][j]=='O' && G[i-1][j-1]=='O' && G[i-2][j-2]=='O' && G[i-3][j-3]=='O'){
                    return 1;
                } if(G[i][j]=='O' && G[i+1][j-1]=='O' && G[i+2][j-2]=='O'&& G[i+3][j-3]=='O'){
                    return 1;
                } if(G[i][j]=='O' && G[i-1][j+1]=='O' && G[i-2][j+2]=='O'&& G[i-3][j+3]=='O'){
                    return 1;
                }
            }
        }
        return 0;
    }
}


int jeuFini(grille G,int j) {
    if (verifCol(G,j) == 1){
        printf("Le joueur %i a gagner la partie\n", j);
        return (1);
    }

    if (verifLigne(G,j) == 1) {
        printf("Le joueur %i a gagner la partie\n", j);
        return (1);
    }

    if (verifDiag(G,j) == 1) {
        printf("Le joueur %i a gagner la partie\n", j);
        return (1);
    }

    if (grillepleine(G) == 1) {
        printf("Egalité entre les deux joueurs\n");
        return (1);
    }
}



void main(){
    grille g;
    int ok,choix;
    int i = 1;
    initGrille(g); 
    
    
    do {
        printf("\n1. Nouvelle partie\n2. Charger partie\n3. Quittez\n -->");
        scanf(" %c",&choix); /* lecture du choix de l'utilisateur */
        if (choix== '1') {
            grille g;
            int ok,choix;
            int i = 1;
            initGrille(g); 
            do {
                i = i%2;
                afficheGrille(g);
                ajoutejeton(g,i);
                ok = jeuFini(g,i);
                
                i++;
            } while (ok == 0);
            afficheGrille(g);
        }
        
        if (choix== '2') {
            charger_partie("save",g,&i);
            do {
                i = i%2;
                afficheGrille(g);
                ajoutejeton(g,i);
                ok = jeuFini(g,i);
                i++;
            } while (ok == 0);
            afficheGrille(g);
            
        }
    } while (choix == '1' || choix =='2');
}
