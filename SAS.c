#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    char priorite[10]; // "High" ou "Low"
    int complete; // 0 pour incomplète, 1 pour complète
} Tache;

Tache taches[MAX_TACHES];
int nombreTaches = 0;

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

// L'affichage menu
void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une tâche\n");
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
   
    printf("Titre: ");
    getchar(); // pour consommer la retour à ligne
    fgets(nouvelleTache.titre, TITRE_MAX, stdin);
    nouvelleTache.titre[strcspn(nouvelleTache.titre, "\n")] = '\0';

    printf("Description: ");
    fgets(nouvelleTache.description, DESCRIPTION_MAX, stdin);
    nouvelleTache.description[strcspn(nouvelleTache.description, "\n")] = '\0';

    addDate(&nouvelleTache);
     
    printf("Priorité (High/Low): ");
    getchar();
    fgets(nouvelleTache.priorite, 10, stdin);
    nouvelleTache.priorite[strcspn(nouvelleTache.priorite, "\n")] = '\0';

    nouvelleTache.complete = 0; // Tâche est incomplète par défaut
    taches[nombreTaches++] = nouvelleTache;
    printf("Tâche ajoutée avec succès.\n");
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
        printf("  Date d'échéance :%d/%d/%d", taches[i].dateEcheance.day, taches[i].dateEcheance.month, taches[i].dateEcheance.year);
        printf("  Priorité: %s\n", taches[i].priorite);
        printf("  Statut: %s\n", taches[i].complete ? "Complète" : "Incomplète");
        printf("\n");
    }
}

// Modification des tâches
void modifierTache() {
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
     printf("Modifier la titre (actuelle: %s): ", tache->titre);
    getchar();
    fgets(tache->titre, TITRE_MAX, stdin);
    tache->titre[strcspn(tache->titre, "\n")] = '\0';

    printf("Modifier la description (actuelle: %s): ", tache->description);
    getchar();
    fgets(tache->description, DESCRIPTION_MAX, stdin);
    tache->description[strcspn(tache->description, "\n")] = '\0';

    addDate(tache);

    printf("Modifier la priorité (actuelle: %s): ", tache->priorite);
    getchar();
    fgets(tache->priorite, 10, stdin);
    tache->priorite[strcspn(tache->priorite, "\n")] = '\0';

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
    char priorite[10];
    printf("Entrez la priorité à filtrer (High/Low): ");
    fgets(priorite, 10, stdin);
    priorite[strcspn(priorite, "\n")] = '\0';

    printf("\n=== Tâches Filtrées ===\n");
    for (int i = 0; i < nombreTaches; i++) {
        if (strcmp(taches[i].priorite, priorite) == 0) {
            printf("Tâche %d:\n", i + 1);
            printf("  Titre: %s\n", taches[i].titre);
            printf("  Description: %s\n", taches[i].description);
            printf("  Date d'échéance :%d/%d/%d", taches[i].dateEcheance.day, taches[i].dateEcheance.month, taches[i].dateEcheance.year);
            printf("  Priorité: %s\n", taches[i].priorite);
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
        fprintf(file, "%s\n%s\n%s\n%s\n%d\n",
                taches[i].titre,
                taches[i].description,
                taches[i].dateEcheance,
                taches[i].priorite,
                taches[i].complete);
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