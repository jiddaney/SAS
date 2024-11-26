#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TACHES 100
#define TITRE_MAX 100
#define DESCRIPTION_MAX 256
#define DATE_MAX 11

typedef struct {
    char titre[TITRE_MAX];
    char description[DESCRIPTION_MAX];
    char dateEcheance[DATE_MAX];
    char priorite[10]; // "High" ou "Low"
    int complete; // 0 pour incomplète, 1 pour complète
} Tache;

Tache taches[MAX_TACHES];
int nombreTaches = 0;

// Fonction pour valider la date
bool estDateValide(const char *date) {
    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return false; // Format incorrect
    }

    if (month < 1 || month > 12) {
        return false; // Mois invalide
    }

    int joursDansMois[] = { 0, 31, 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if (day < 1 || day > joursDansMois[month]) {
        return false; // Jour invalide
    }

    return true; // Date valide
}

// L'affichage menu
void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une tâche\n");
    printf("2. Afficher les tâches\n");
    printf("3. Modifier une tâche\n");
    printf("4. Supprimer une tâche\n");
    printf("5. Filtrer les tâches\n");
    printf("6. Trier les tâches\n");
    printf("7. Sauvegarder les tâches\n");
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

    do {
        printf("Date d'échéance (YYYY-MM-DD): ");
        fgets(nouvelleTache.dateEcheance, DATE_MAX, stdin);
        nouvelleTache.dateEcheance[strcspn(nouvelleTache.dateEcheance, "\n")] = '\0';
        if (!estDateValide(nouvelleTache.dateEcheance)) {
            printf("Date invalide. Veuillez entrer une date au format YYYY-MM-DD.\n");
        }
    } while (!estDateValide(nouvelleTache.dateEcheance));

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
        printf("  Date d'échéance: %s\n", taches[i].dateEcheance);
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
    printf("Modifier la description (actuelle: %s): ", tache->description);
    fgets(tache->description, DESCRIPTION_MAX, stdin);
    tache->description[strcspn(tache->description, "\n")] = '\0';

    do {
        printf("Modifier la date d'échéance (actuelle: %s): ", tache->dateEcheance);
        fgets(tache->dateEcheance, DATE_MAX, stdin);
        tache->dateEcheance[strcspn(tache->dateEcheance, "\n")] = '\0';
        if (!estDateValide(tache->dateEcheance)) {
            printf("Date invalide. Veuillez entrer une date au format YYYY-MM-DD.\n");
        }
    } while (!estDateValide(tache->dateEcheance));

    printf("Modifier la priorité (actuelle: %s): ", tache->priorite);
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
            printf("  Date d'échéance: %s\n", taches[i].dateEcheance);
            printf("  Priorité: %s\n", taches[i].priorite);
            printf("  Statut: %s\n", taches[i].complete ? "Complète" : "Incomplète");
            printf("\n");
        }
    }
}

// Triage des tâches
void trierTaches() {
    for (int i = 0; i < nombreTaches - 1; i++) {
        for (int j = 0; j < nombreTaches - i - 1; j++) {
            if (strcmp(taches[j].dateEcheance, taches[j + 1].dateEcheance) > 0) {
                Tache temp = taches[j];
                taches[j] = taches[j + 1];
                taches[j + 1] = temp;
            }
        }
    }
    printf("Tâches triées par date d'échéance.\n");
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
            case 6: trierTaches(); break;
            case 7: sauvegarderTaches(); break;
            default: printf("Choix non valide, veuillez réessayer.\n");
        }
    } while (choix != 0);
    
    return 0;
}

