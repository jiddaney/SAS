#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TACHES 100

// Structure de la tâche
typedef struct {
    char titre[100];
    char description[255];
    char date_echeance[11];  // Format: "YYYY-MM-DD"
    char priorite[10];        // "High" ou "Low"
    char statut[20];          // "Complète" ou "Incomplète"
} Tache;

// Afficher le menu des opérations
void afficherMenu() {
    printf("===== Gestion des Tâches =====\n");
    printf("1. Ajouter une Tâche\n");
    printf("2. Afficher la Liste des Tâches\n");
    printf("3. Modifier une Tâche\n");
    printf("4. Supprimer une Tâche\n");
    printf("5. Filtrer par Priorité\n");
    printf("6. Filtrer par Statut\n");
    printf("7. Trier les Tâches\n");
    printf("8. Quitter\n");
    printf("=============================\n");
    printf("Choix: ");
}

// Ajouter une nouvelle tâche
void ajouterTache(Tache taches[MAX_TACHES], int nbTaches) {
    Tache nouvelleTache;
    printf("Titre de la tâche: ");
    fgets(nouvelleTache.titre, 100, stdin);
    nouvelleTache.titre[strcspn(nouvelleTache.titre, "\n")] = '\0'; 

    printf("Description de la tâche: ");
    fgets(nouvelleTache.description, 255, stdin);
    nouvelleTache.description[strcspn(nouvelleTache.description, "\n")] = '\0';

    printf("Date d'échéance (YYYY-MM-DD): ");
    fgets(nouvelleTache.date_echeance, 11, stdin);
    nouvelleTache.date_echeance[strcspn(nouvelleTache.date_echeance, "\n")] = '\0';

    printf("Priorité (High/Low): ");
    fgets(nouvelleTache.priorite, 10, stdin);
    nouvelleTache.priorite[strcspn(nouvelleTache.priorite, "\n")] = '\0';

    printf("Statut (Complète/Incomplète): ");
    fgets(nouvelleTache.statut, 20, stdin);
    nouvelleTache.statut[strcspn(nouvelleTache.statut, "\n")] = '\0';

    // Ajouter la tâche à la liste
    taches[nbTaches] = nouvelleTache;
}

// Afficher la liste des tâches
void afficherTaches(Tache taches[MAX_TACHES], int nbTaches) {
    if (nbTaches == 0) {
        printf("Aucune tâche à afficher.\n");
        return;
    }
    for (int i = 0; i < nbTaches; i++) {
        printf("\nTâche %d:\n", i + 1);
        printf("Titre: %s\n", taches[i].titre);
        printf("Description: %s\n", taches[i].description);
        printf("Date d'échéance: %s\n", taches[i].date_echeance);
        printf("Priorité: %s\n", taches[i].priorite);
        printf("Statut: %s\n", taches[i].statut);
    }
}

// Modifier une tâche
void modifierTache(Tache taches[MAX_TACHES], int nbTaches) {
    int id;
    printf("Entrez l'ID de la tâche à modifier (1-%d): ", nbTaches);
    scanf("%d", &id);
    id--; // Ajuster pour que l'index commence à 0

    if (id < 0 || id >= nbTaches) {
        printf("Tâche non valide.\n");
        return;
    }

    // Modifier la tâche
    printf("Nouveau titre: ");
    getchar();
    fgets(taches[id].titre, 100, stdin);
    taches[id].titre[strcspn(taches[id].titre, "\n")] = '\0';

    printf("Nouvelle description: ");
    fgets(taches[id].description, 255, stdin);
    taches[id].description[strcspn(taches[id].description, "\n")] = '\0';

    printf("Nouvelle date d'échéance (YYYY-MM-DD): ");
    fgets(taches[id].date_echeance, 11, stdin);
    taches[id].date_echeance[strcspn(taches[id].date_echeance, "\n")] = '\0';

    printf("Nouvelle priorité (High/Low): ");
    fgets(taches[id].priorite, 10, stdin);
    taches[id].priorite[strcspn(taches[id].priorite, "\n")] = '\0';

    printf("Nouveau statut (Complète/Incomplète): ");
    fgets(taches[id].statut, 20, stdin);
    taches[id].statut[strcspn(taches[id].statut, "\n")] = '\0';
}

void supprimerTache(Tache taches[MAX_TACHES], int nbtaches) {
    int id;
    printf("entrez l'id de la tache a supprimer (1-%d): ", nbtaches);
    scanf("%d, &id");
    id--;
    if (id < 0 || id >= nbtaches) {
        printf("Tache non valide.\n");
        return;
    }
    for (int i = id; i < nbtaches - 1; i++) {
        taches[i] = taches[i + 1];
    }
    (nbtaches)--;
    printf("tache suprimee.\n");
}

void filtrerParPriorite(Tache taches[MAX_TACHES], int nbtaches, char priorite[10]) {
for (int i = 0; i < nbtaches; i++){
    if (strcmp(taches[i].priorite, priorite) == 0) {
        printf("\ntache %d:\n", i + 1);
        printf("titre: %s\n",taches[i].titre);
        printf("description: %s\n", taches[i].description);
        printf("date d'echeance: %s\n", taches[i].date_echeance);
        printf("priorite: %s\n", taches[i].priorite);
        printf("statut: %s\n", taches[i].statut);
    }
  }
}

void filtrerParStatut(Tache taches[MAX_TACHES], int nbtaches, char statut[20]) {
    for (int i = 0; i < nbtaches; i++) {
        if (strcmp(taches[i].statut, statut) == 0) {
            printf("\nTache %d:\n", i + 1);
            printf("titre: %s\n",taches[i].titre);
            printf("description: %s\n", taches[i].description);
            printf("date d'echeance: %s\n", taches[i].date_echeance);
            printf("priorite;%s\n", taches[i].priorite);
            printf("statut:%s\n", taches[i].statut);
            
        }
    }
}

int comparerDates(Tache tacheA, Tache tacheB) {
     return strcmp(tacheA.date_echeance, tacheB.date_echeance);
}

void trierTaches(Tache taches[MAX_TACHES], int nbtaches) {
    Tache temp;
    for (int i = 0 ;i < nbtaches - 1; i++) {
        for (int j = 0; j < nbtaches - i - 1; i++) {
            if (comparerDates(taches[j], taches[j + i]) > 0) {
                temp = taches[j];
                taches[j] = taches[j + i];
                taches[j + 1] = temp;
            }
        }
    }
}

void sauvegarderTaches(Tache taches[MAX_TACHES], int nbtaches) {
    FILE *fichier = fopen("tasks.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nbtaches; i++) {
        fprintf(fichier, "%s\n%s\n%s\n%s\n%s\n",
        taches[i].titre,
        taches[i].description,
        taches[i].date_echeance,
        taches[i].priorite,
        taches[i].statut);
    }
    fclose(fichier);
}

int main() {
    Tache taches[MAX_TACHES];
    int nbtaches = 0;
    int choix;

      do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
              ajouterTache(taches, nbtaches);
              nbtaches++;
              break;
            case 2:
               afficherTaches(taches, nbtaches);
               break;
            case 3:
                modifierTache(taches, nbtaches);
                break;
            case 4:
                 supprimerTache(taches, nbtaches);
                 break;
            case 5:
                 {
                    char prioritie[20];
                    printf("priorite a filtrer (high/low):");
                    scanf("%s", prioritie);
                    filtrerParPriorite(taches, nbtaches, prioritie);
                 }   
                  break;
            case 6:
            {
                char statut[20];
                    printf("statut a filtrer (complete/incomplete):");
                    scanf("%s", statut);
                    filtrerParPriorite(taches, nbtaches, statut);
            }
                   break;
            case 7:
                 trierTaches(taches, nbtaches);
                 printf("Tache triees par date.\n");
                 break;
            case 8:
                 sauvegarderTaches(taches, nbtaches);
                 printf("au revoir!!\n");
                 break;
            default:
                printf("choix invalide.\n");     
        }
      } while (choix != 8);
      
        return 0;
        
      }
      
