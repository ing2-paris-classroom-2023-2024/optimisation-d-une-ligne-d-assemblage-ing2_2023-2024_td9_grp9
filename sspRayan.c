#include <stdio.h>
/*
void countTasksAndTotalTime(const char* fileName, int* totalTasks, double* totalTime) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        *totalTasks = -1;
        *totalTime = 0.0;
        return;
    }

    int task;
    double time;
    *totalTasks = 0;
    *totalTime = 0.0;

    while (fscanf(file, "%d %lf", &task, &time) == 2) {
        (*totalTasks)++;
        *totalTime += time;
    }

    fclose(file);
}

double findTaskTime(const char* fileName, int taskNumber) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1.0;
    }

    int task;
    double time;

    while (fscanf(file, "%d %lf", &task, &time) == 2) {
        if (task == taskNumber) {
            fclose(file);
            return time;
        }
    }

    fclose(file);
    return -1.0;
}

int MONmain() {
    const char* fileName = "operations.txt";
    int totalTasks;
    double totalTime;

    countTasksAndTotalTime(fileName, &totalTasks, &totalTime);

    if (totalTasks >= 0) {
        printf("Nombre total de taches : %d\n", totalTasks);
        printf("Temps total : %.2f secondes\n", totalTime);
    }

    printf("Entrez le nombre de taches a consulter : ");
    int numTasks;
    scanf("%d", &numTasks);

    double totalTaskTime = 0.0;
    int taskNumber;

    for (int i = 0; i < numTasks; i++) {
        printf("Entrez le numero de la tache %d : ", i + 1);
        scanf("%d", &taskNumber);
        double taskTime = findTaskTime(fileName, taskNumber);
        if (taskTime >= 0) {
            totalTaskTime += taskTime;
        } else {
            printf("Tache %d non trouvee.\n", taskNumber);
        }
    }

    printf("Temps total pour les taches specifiees : %.2f secondes\n", totalTaskTime);

    return 0;
}
 */