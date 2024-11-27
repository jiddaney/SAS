#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TACHES 100
#define TITRE_MAX 100
#define DESCRIPTION_MAX 256

typedef struct {
    int year;
    int month;
    int day;
} Date;


typedef struct {
    char titre[TITRE_MAX];
    char description[DESCRIPTION_MAX];
    Date dateEcheance;
    int priorite; // "High" ou "Low"
    int complete; // 0 pour incomplète, 1 pour complète
} Tache;

Tache taches[MAX_TACHES];
int nombreTaches = 0;

// add

void addDate(Tache* nouvelleTache) {
     int day, month, year;

    printf("Date d'échéance");
    do {
        printf("=> mois: ");
        scanf("%d", &month);
        if (month > 12 || month < 1){
            printf("Date invalide. Veuillez entrer une date au format correct: \n");
        }
    } while (month > 12 || month < 1);
    nouvelleTache->dateEcheance.month = month;
    do{
        printf("=> day: ");
        scanf("%d", &day);
          if (day > 31 || day < 1){
        printf("Date invalide. Veuillez entrer une date au format correct: \n");
        }
    }while (day > 31 || day < 1);
    nouvelleTache->dateEcheance.day = day;
   do {
    printf("=>year: ");
    scanf("%d", &year);
     if (year < 2024){
        printf("year invalid!! \n");
     }
      }while (year < 2024);
      nouvelleTache->dateEcheance.year = year;
}

void addTitre(Tache* nouvelleTache){
    printf("Titre: "); 
    fgets(nouvelleTache->titre, TITRE_MAX, stdin);
    nouvelleTache->titre[strcspn(nouvelleTache->titre, "\n")] = '\0';
}

void addDesc(Tache* nouvelleTache) {
    printf("Description: ");
    fgets(nouvelleTache->description, DESCRIPTION_MAX, stdin);
    nouvelleTache->description[strcspn(nouvelleTache->description, "\n")] = '\0';
}

void addpriorite(Tache* nouvelleTache){
    int preoritie;
    do
    {
        printf("entrez la preorite (0=LOW/1=HIGH)");
        scanf("%d", &preoritie);
        if (preoritie != 0 && preoritie != 1)printf("choix non valid!!");
    } while (preoritie != 0 && preoritie != 1);
    nouvelleTache->priorite = preoritie;
}

void addstatut(Tache* nouvelleTache){
    int statut;
    do
    {
       printf("entrez le statut : (INCOMPLETTE=0/COMPLETTE=1)");
       scanf("%d1",&statut);
       if (statut != 0 && statut != 1)printf("choix non valid!!");
       
    } while (statut != 0 && statut != 1);
    nouvelleTache->complete = statut;
    
}

// L'affichage menu
void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une tâcheuuuu\n");
    printf("2. Afficher les tâches\n");
    printf("3. Modifier une tâche\n");
    printf("4. Supprimer une tâche\n");
    printf("5. Filtrer les tâches\n");
    printf("6. Sauvegarder les tâches\n");
    printf("0. Quitter\n");
    printf("Veuillez entrer votre choix: ");
}

// L'addition des tâches
void ajouterTache() {
    if (nombreTaches >= MAX_TACHES) {
        printf("Limite de tâches atteinte.\n");
        return;
    }
    
    Tache nouvelleTache;

    addTitre(&nouvelleTache);

    addDesc(&nouvelleTache);

    addDate(&nouvelleTache);

    addpriorite(&nouvelleTache);

    addstatut(&nouvelleTache);

     
    taches[nombreTaches] = nouvelleTache;
    nombreTaches++;
    printf("l'ajoute de tache avec succes!!");
}

// Affichage des tâches
void afficherTaches() {

    if (nombreTaches == 0) {
        printf("Aucune tâche à afficher.\n");
        return;
    }

    printf("\n=== Liste des Tâches ===\n");
    for (int i = 0; i < nombreTaches; i++) {
        printf("Tâche %d:\n", i + 1);
        printf("  Titre: %s\n", taches[i].titre);
        printf("  Description: %s\n", taches[i].description);
        printf("  Date d'échéance :%d/%d/%d\n", taches[i].dateEcheance.day, taches[i].dateEcheance.month, taches[i].dateEcheance.year);
        printf("  Priorité: %s\n", taches[i].priorite ? "HIGH" : "LOW");
        printf("  Statut: %s\n", taches[i].complete ? "Complète" : "Incomplète");
        printf("\n");
    }
}

// Modification des tâches
void modifierTache() {
    int update_titre,update_descrip,update_date,update_priorite,update_satatut;

    int index;
    afficherTaches();
    printf("Entrez le numéro de la tâche à modifier: ");
    scanf("%d", &index);
    getchar(); // Pour consommer le retour à la ligne

    if (index < 1 || index > nombreTaches) {
        printf("Numéro de tâche invalide.\n");
        return;
    }

    Tache *tache = &taches[index - 1];

     do
     {
        printf("Modifier la titre (actuelle: %s) voulez vous modifier le titre ? (0=yes/1=no): ", tache->titre);
         scanf("%d", &update_titre);
        
          if(update_titre != 0 && update_titre != 1)printf("choix non valide!!");
        
     } while (update_titre != 0 && update_titre != 1);
     if (update_titre == 0){
        getchar();
        addTitre(tache);
     }
     
  do
   {
    printf("Modifier la description (actuelle: %s) voulez vous modifier la discreption ? (0=yes/1=no): ", tache->description);
    scanf("%d", &update_descrip);

        if (update_descrip != 0 && update_descrip != 1)printf("choix non valid!!");

   }while (update_descrip != 0 && update_descrip != 1);
        if (update_descrip == 0){
            getchar();
            addDesc(tache);   
        }

     do
     {
        printf("Modifier la date (actuelle: %d/%d/%d) voulez vous modifier la date ? (0=yes/1=no): ", tache->dateEcheance.day, tache->dateEcheance.month, tache->dateEcheance.year);
         scanf("%d",&update_date);
        
          if(update_date != 0 && update_date != 1)printf("choix non valide!!");
        
     } while (update_date != 0 && update_date != 1);
     if (update_date == 0)addDate(tache);
        
   do
     {
        printf("Modifier la preorite (actuelle: %s) voulez vous modifier la preorite ? (0=yes/1=no): ", tache->priorite ? "HIGH" : "LOW");
         scanf("%d", &update_priorite);
        
          if(update_priorite != 0 && update_priorite != 1)printf("choix non valide!!");
        
     } while (update_priorite != 0 && update_priorite != 1);
     if (update_priorite == 0)addpriorite(tache);
    
   do
     {
        printf("Modifier le statut (actuelle: %s) voulez vous modifier le statut ? (0=yes/1=no): ", tache->complete ? "Complete" : "Incomplete");
         scanf("%d", &update_satatut);
        
          if(update_satatut != 0 && update_satatut != 1)printf("choix non valide!!");
        
     } while (update_satatut != 0 && update_satatut != 1);
     if (update_satatut == 0)addstatut(tache);
    

    

    printf("Tâche modifiée avec succès.\n");
}

// Suppression des tâches
void supprimerTache() {
    int index;
    afficherTaches();
    printf("Entrez le numéro de la tâche à supprimer: ");
    scanf("%d", &index);
    getchar(); // Pour consommer le retour à la ligne

    if (index < 1 || index > nombreTaches) {
        printf("Numéro de tâche invalide.\n");
        return;
    }

    for (int i = index - 1; i < nombreTaches - 1; i++) {
        taches[i] = taches[i + 1];
    }
    nombreTaches--;
    printf("Tâche supprimée avec succès.\n");
}

// Filtration des tâches
void filtrerTaches() {
    int filter;
    
    do
    {
        printf("filtrer par (0 = low, 1 = high )");
        scanf("%d", &filter);
        if(filter != 0 && filter != 1) printf("choix invalid!!");
    } while (filter != 0 && filter != 1);
    

    printf("\n=== Tâches Filtrées ===\n");
    for (int i = 0; i < nombreTaches; i++) {
        if (taches[i].priorite == filter) {
            printf("Tâche %d:\n", i + 1);
            printf("  Titre: %s\n", taches[i].titre);
            printf("  Description: %s\n", taches[i].description);
            printf("  Date d'échéance :%d/%d/%d", taches[i].dateEcheance.day, taches[i].dateEcheance.month, taches[i].dateEcheance.year);
            printf("  Priorité: %s\n", taches[i].priorite ? "HIGH" : "LOW");
            printf("  Statut: %s\n", taches[i].complete ? "Complète" : "Incomplète");
            printf("\n");
        }
    }
}


// Sauvegarde des tâches
void sauvegarderTaches() {
    FILE *file = fopen("taches.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de la sauvegarde des tâches.\n");
        return;
    }

    for (int i = 0; i < nombreTaches; i++) {
        fprintf(file, "%s\n%s\n%d/%d/%d\n%s\n%d\n",
                taches[i].titre,
                taches[i].description,
                taches[i].dateEcheance.day, 
                taches[i].dateEcheance.month, 
                taches[i].dateEcheance.year, 
                taches[i].priorite? "HIGH" : "LOW",
                taches[i].complete? "Complète" : "Incomplète");
    }
    fclose(file);
    printf("Tâches sauvegardées avec succès.\n");
}


int main() {
    int choix;
    
    do {
        afficherMenu();
        scanf("%d", &choix);
        getchar(); // Pour consommer le retour à la ligne après scanf
        
        switch (choix) {
            case 1: ajouterTache(); break;
            case 2: afficherTaches(); break;
            case 3: modifierTache(); break;
            case 4: supprimerTache(); break;
            case 5: filtrerTaches(); break;
            case 6: sauvegarderTaches(); break;
            default: printf("Choix non valide, veuillez réessayer.\n");
        }
    } while (choix != 0);
    
    return 0;
}