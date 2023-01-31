#include "menu.h"

int menu(void){
    // afficher menu.tbob sur le terminal
    FILE * launcher = fopen("menu.mtbob", "r");
    char c;
    while((c = fgetc(launcher)) != EOF){
        printf("%c", c);
    }

    printf("\n");
    fclose(launcher);
    
    // si l'utilisateur appuie sur 1 -> lancer le jeu
    // si l'utilisateur appuie sur 2 -> fermer l'appli
    // si l'utilisateur appuie sur autre chose -> ne rien faire
    int choix = 0;
    // scanf("%d",&choix);
    while(choix != 1 && choix != 2){
        scanf("%d",&choix);
    }
    if(choix == 1){
        play();
    }else if(choix == 2){
        return 0;
    }
    return 0;
}