//display individual student record
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  // For usleep function on UNIX systems

struct Student{
    char studId[10];
    char name[50];
    char icNum[20];
    char address[100];
    char phone[20];
    char email[50];
};

struct StudentIntake{
    char studId[10];
    char intake[10];
};

struct StudentActivity{
    char studId[10];
    char activityId[10];
};

struct Core{
    char id[10];
    char intake[10];
    char name[100];
    char day[10];
    char stime[10];
    char etime[10];
    char venue[50];
};

struct Elective{
    char id[10];
    char intake[10];
    char name[100];
    char day[10];
    char stime[10];
    char etime[10];
    char venue[50];
    int credithour;
};

struct Club{
    char id[10];
    char name[100];
};

struct ClubRole{
    char studId[10];
    char clubId[10];
    char role[20];
};

struct Workshop{
    char id[10];
    char name[100];
    char date[20];
    char stime[10];
    char etime[10];
    char venue[50];
};

struct Competitions{
    char id[10];
    char name[100];
    char date[20];
    char venue[50];
};

void display_core(){
    char **list = NULL;
    int lineCount = 0;
    FILE *file;
    
    file = fopen("core.txt", "r");

    if (file == NULL){
        printf("Error reading file\n");
    }
    else{
        printf("\nCore Course List:\n");
        printf("\n%-20s%-40s%-20s\n","Module Code:","Module Name:","Module Credit Hours:");

        while (!feof(file)){
            char ch = fgetc(file);
            if (ch == '\n'){
                lineCount++;
            }
        }

        //Reset the file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);

        list = (char **)malloc(lineCount * sizeof(char *));
        for (int i=0; i<lineCount; i++){
            list[i] = (char *)malloc(100 * sizeof(char));
        }

        int currentLine = 0;
        while (fgets(list[currentLine], 100, file) != NULL){
            currentLine++;
        }

        for (int i=0; i<lineCount; i++){
            char *token = strtok(list[i], ",");
            int columnCount = 0;

            while (token != NULL){
                if (columnCount == 0){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-20s", token);
                } else if (columnCount == 2){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-40s", token);
                }

                token = strtok(NULL, ",");
                columnCount++;
            }
            printf("%-20d",3);
            printf("\n");    
        }
    }

    for (int i=0; i<lineCount; i++){
        free(list[i]);
    }
    free(list);
    fclose(file);
}

void display_elective(){
    char **list = NULL;
    int lineCount = 0;
    FILE *file;
    
    file = fopen("elective.txt", "r");

    if (file == NULL){
        printf("Error reading file\n");
    }
    else{
        printf("\nElective Course List:\n");
        printf("\n%-20s%-40s%-20s\n","Module Code:","Module Name:","Module Credit Hours:");

        while (!feof(file)){
            char ch = fgetc(file);
            if (ch == '\n'){
                lineCount++;
            }
        }

        //Reset the file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);

        list = (char **)malloc(lineCount * sizeof(char *));
        for (int i=0; i<lineCount; i++){
            list[i] = (char *)malloc(100 * sizeof(char));
        }

        int currentLine = 0;
        while (fgets(list[currentLine], 100, file) != NULL){
            currentLine++;
        }

        for (int i=0; i<lineCount; i++){
            char *token = strtok(list[i], ",");
            int columnCount = 0;

            while (token != NULL){
                if (columnCount == 0){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-20s", token);
                } else if (columnCount == 2){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-40s", token);
                } else if (columnCount == 7){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-20s",token);
                }

                token = strtok(NULL, ",");
                columnCount++;
            }
            printf("\n");    
        }
    }

    for (int i=0; i<lineCount; i++){
        free(list[i]);
    }
    free(list);
    fclose(file);
}

void display_club(){
    char **list = NULL;
    int lineCount = 0;
    FILE *file;
    
    file = fopen("club.txt", "r");

    if (file == NULL){
        printf("Error reading file\n");
    }
    else{
        printf("\nClub & Society List:\n");
        printf("\n%-20s%-40s%-20s\n","Club Code:","Club Name:","Club Credit Hours:");

        while (!feof(file)){
            char ch = fgetc(file);
            if (ch == '\n'){
                lineCount++;
            }
        }

        //Reset the file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);

        list = (char **)malloc(lineCount * sizeof(char *));
        for (int i=0; i<lineCount; i++){
            list[i] = (char *)malloc(100 * sizeof(char));
        }

        int currentLine = 0;
        while (fgets(list[currentLine], 100, file) != NULL){
            currentLine++;
        }

        for (int i=0; i<lineCount; i++){
            char *token = strtok(list[i], ",");
            int columnCount = 0;

            while (token != NULL){
                if (columnCount == 0){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-20s", token);
                } else if (columnCount == 1){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-40s", token);
                }

                token = strtok(NULL, ",");
                columnCount++;
            }
            printf("%-20s", "Role-dependent (5-15)");
            printf("\n");    
        }
    }

    for (int i=0; i<lineCount; i++){
        free(list[i]);
    }
    free(list);
    fclose(file);
}

void display_workshop(){
    char **list = NULL;
    int lineCount = 0;
    FILE *file;
    
    file = fopen("workshop.txt", "r");

    if (file == NULL){
        printf("Error reading file\n");
    }
    else{
        printf("\nTalk & Workshop List:\n");
        printf("\n%-20s%-40s%-20s\n","Workshop Code:","Workshop Name:","Workshop Credit Hours:");

        while (!feof(file)){
            char ch = fgetc(file);
            if (ch == '\n'){
                lineCount++;
            }
        }

        //Reset the file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);

        list = (char **)malloc(lineCount * sizeof(char *));
        for (int i=0; i<lineCount; i++){
            list[i] = (char *)malloc(100 * sizeof(char));
        }

        int currentLine = 0;
        while (fgets(list[currentLine], 100, file) != NULL){
            currentLine++;
        }

        for (int i=0; i<lineCount; i++){
            char *token = strtok(list[i], ",");
            int columnCount = 0;

            while (token != NULL){
                if (columnCount == 0){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-20s", token);
                } else if (columnCount == 1){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-40s", token);
                }

                token = strtok(NULL, ",");
                columnCount++;
            }
            printf("%-20s", "0.1");
            printf("\n");    
        }
    }

    for (int i=0; i<lineCount; i++){
        free(list[i]);
    }
    free(list);
    fclose(file);
}

void display_competition(){
    char **list = NULL;
    int lineCount = 0;
    FILE *file;
    
    file = fopen("competition.txt", "r");

    if (file == NULL){
        printf("Error reading file\n");
    }
    else{
        printf("\nCompetition List:\n");
        printf("\n%-20s%-40s%-20s\n","Competition Code:","Competition Name:","Competition Credit Hours:");

        while (!feof(file)){
            char ch = fgetc(file);
            if (ch == '\n'){
                lineCount++;
            }
        }

        //Reset the file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);

        list = (char **)malloc(lineCount * sizeof(char *));
        for (int i=0; i<lineCount; i++){
            list[i] = (char *)malloc(100 * sizeof(char));
        }

        int currentLine = 0;
        while (fgets(list[currentLine], 100, file) != NULL){
            currentLine++;
        }

        for (int i=0; i<lineCount; i++){
            char *token = strtok(list[i], ",");
            int columnCount = 0;

            while (token != NULL){
                if (columnCount == 0){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-20s", token);
                } else if (columnCount == 1){
                    token[strcspn(token, "\n")] = '\0';
                    printf("%-40s", token);
                }

                token = strtok(NULL, ",");
                columnCount++;
            }
            printf("%-20s", "1");
            printf("\n");    
        }
    }

    for (int i=0; i<lineCount; i++){
        free(list[i]);
    }
    free(list);
    fclose(file);
}

void processStudent(FILE *stfile, struct Student *stud, const char *studID){
    while (fscanf(stfile, "%10[^,],%50[^,],%*d,%*[^,],%20[^,],%100[^,],%*c,%20[^,],%50[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,\n]\n",
        stud->studId, stud->name, stud->icNum, stud->address, stud->phone, stud->email) != EOF) {
            if (strcmp(stud->studId, studID) == 0){
                // Student ID found
                return;
            }
    }
}

void processStudentList(FILE *sfile, struct StudentIntake *studList, const char *studID, int *found){
    while (fscanf(sfile, "%10[^,],%10[^,\n]\n", studList->studId, studList->intake) != EOF) {
        if (strcmp(studList->studId, studID) == 0){
            // Student ID found
            *found = 1;
            return;
        }
    }
    if (*found == 0){
        printf("Student ID not found\n");
    }
}

void processCore(FILE *rfile, FILE *file, const char *intake, float *totalcredits){
    struct Core c;
    
    printf("\nCore Module List:\n");
    printf("\n%-20s%-40s%-20s\n","Module Code:","Module Name:","Module Credit Hours:");
    fprintf(rfile, "\nCore Module List:\n");
    fprintf(rfile, "\n%-20s%-40s%-20s\n","Module Code:","Module Name:","Module Credit Hours:");
    
    while (fscanf(file, "%10[^,],%10[^,],%100[^,],%10[^,],%10[^,],%10[^,],%50[^,\n]\n", c.id, c.intake, c.name, c.day, c.stime, c.etime, c.venue) != EOF) {
        if (strcmp(c.intake, intake) == 0){
            // Intake found
            printf("%-20s%-40s%-20d\n", c.id, c.name, 3);
            fprintf(rfile, "%-20s%-40s%-20d\n", c.id, c.name, 3);
        }
    }
    *totalcredits += 12;
    printf("Total Core Module Credit Hours: 12\n");
    fprintf(rfile, "Total Core Module Credit Hours: 12\n");
}

void processElective(FILE *rfile, FILE *afile, FILE *file, struct StudentActivity *studAct, const char *studID, float *totalcredits){
    struct Elective e;
    int electivecredits = 0;

    printf("\nElective Module List:\n");
    printf("\n%-20s%-40s%-20s\n","Module Code:","Module Name:","Module Credit Hours:");
    fprintf(rfile, "\nElective Module List:\n");
    fprintf(rfile, "\n%-20s%-40s%-20s\n","Module Code:","Module Name:","Module Credit Hours:");
    
    rewind(afile);
    while (fscanf(afile, "%10[^,],%10[^,\n]\n", studAct->studId, studAct->activityId) != EOF) {
        if (strcmp(studAct->studId, studID) == 0){
            // Student ID found
            while (fscanf(file, "%10[^,],%10[^,],%100[^,],%10[^,],%10[^,],%10[^,],%50[^,],%d\n", e.id, e.intake, e.name, e.day, e.stime, e.etime, e.venue, &e.credithour) != EOF) {
                if (strcmp(e.id, studAct->activityId) == 0){
                    // Intake found
                    printf("%-20s%-40s%-20d\n", e.id, e.name, e.credithour);
                    fprintf(rfile, "%-20s%-40s%-20d\n", e.id, e.name, e.credithour);
                    electivecredits += e.credithour;
                }
            }
            rewind(file);
        }
    }
    *totalcredits += electivecredits;
    printf("Total Elective Module Credit Hours: %d\n", electivecredits);
    fprintf(rfile, "Total Elective Module Credit Hours: %d\n", electivecredits);
}

void processClub(FILE *rfile, FILE *afile, FILE *cfile, FILE *file, struct StudentActivity *studAct, const char *studID, float *totalcredits){
    struct ClubRole cr;
    struct Club c;
    float creditHour = 0;
    float clubcredits = 0;

    printf("\nClub List:\n");
    printf("\n%-20s%-40s%-20s%-20s\n","Club Code:","Club Name:","Club Role:", "Club Credit Hours:");
    fprintf(rfile, "\nClub List:\n");
    fprintf(rfile, "\n%-20s%-40s%-20s%-20s\n","Club Code:","Club Name:","Club Role:", "Club Credit Hours:");
    
    rewind(afile);
    while (fscanf(afile, "%10[^,],%10[^,\n]\n", studAct->studId, studAct->activityId) != EOF) {
        if (strcmp(studAct->studId, studID) == 0){
            // Student ID found
            while (fscanf(cfile, "%10[^,],%100[^,\n]\n", c.id, c.name) != EOF) {
                if (strcmp(c.id, studAct->activityId) == 0){
                    // Activity ID found
                    while (fscanf(file, "%10[^,],%10[^,],%20[^,\n]\n", cr.studId, cr.clubId, cr.role) != EOF) {
                        if (strcmp(cr.clubId, c.id) == 0 && strcmp(cr.studId, studID) == 0){
                            // Club ID found
                            if (strcmp(cr.role, "President") == 0)
                                creditHour = 1.5;
                            else if (strcmp(cr.role, "Vice President") == 0)
                                creditHour = 1.4;
                            else if (strcmp(cr.role, "Secretary") == 0)
                                creditHour = 1.3;
                            else if (strcmp(cr.role, "Treasurer") == 0)
                                creditHour = 1.2;
                            else if (strcmp(cr.role, "Committee Member") == 0)
                                creditHour = 1.1;
                            else if (strcmp(cr.role, "Member") == 0)
                                creditHour = 0.5;
                            printf("%-20s%-40s%-20s%-20.1f\n", c.id, c.name, cr.role, creditHour);
                            fprintf(rfile, "%-20s%-40s%-20s%-20.1f\n", c.id, c.name, cr.role, creditHour);
                            clubcredits += creditHour;
                        }
                    }
                    rewind(file);
                }
            }
            rewind(cfile);
        }
    }
    *totalcredits += clubcredits;
    printf("Total Club Credit Hours: %.1f\n", clubcredits);
    fprintf(rfile, "Total Club Credit Hours: %.1f\n", clubcredits);
}

void processWorkshop(FILE *rfile, FILE *afile, FILE *file, struct StudentActivity *studAct, const char *studID, float *totalcredits){
    struct Workshop w;
    float workshopcredits = 0;

    printf("\nTalk & Workshop List:\n");
    printf("\n%-20s%-40s%-20s\n","Workshop Code:","Workshop Name:","Workshop Credit Hours:");
    fprintf(rfile, "\nTalk & Workshop List:\n");
    fprintf(rfile, "\n%-20s%-40s%-20s\n","Workshop Code:","Workshop Name:","Workshop Credit Hours:");
    
    rewind(afile);
    while (fscanf(afile, "%10[^,],%10[^,\n]\n", studAct->studId, studAct->activityId) != EOF) {
        if (strcmp(studAct->studId, studID) == 0){
            // Student ID found
            while (fscanf(file, "%10[^,],%100[^,],%20[^,],%10[^,],%10[^,],%50[^,\n]\n", w.id, w.name, w.date, w.stime, w.etime, w.venue) != EOF) {
                if (strcmp(w.id, studAct->activityId) == 0){
                    // Intake found
                    printf("%-20s%-40s%-20s\n", w.id, w.name, "0.1");
                    fprintf(rfile, "%-20s%-40s%-20s\n", w.id, w.name, "0.1");
                    workshopcredits += 0.1;
                }
            }
            rewind(file);
        }
    }
    *totalcredits += workshopcredits;
    printf("Total Talk & Workshop Credit Hours: %.1f\n", workshopcredits);
    fprintf(rfile, "Total Talk & Workshop Credit Hours: %.1f\n", workshopcredits);
}

void processCompetition(FILE *rfile, FILE *afile, FILE *file, struct StudentActivity *studAct, const char *studID, float *totalcredits){
    struct Competitions c;
    int competitioncredits = 0;

    printf("\nCompetition List:\n");
    printf("\n%-20s%-40s%-20s\n","Competition Code:","Competition Name:","Competition Credit Hours:");
    fprintf(rfile, "\nCompetition List:\n");
    fprintf(rfile, "\n%-20s%-40s%-20s\n","Competition Code:","Competition Name:","Competition Credit Hours:");
    
    rewind(afile);
    while (fscanf(afile, "%10[^,],%10[^,\n]\n", studAct->studId, studAct->activityId) != EOF) {
        if (strcmp(studAct->studId, studID) == 0){
            // Student ID found
            while (fscanf(file, "%10[^,],%100[^,],%20[^,],%50[^,\n]\n", c.id, c.name, c.date, c.venue) != EOF) {
                if (strcmp(c.id, studAct->activityId) == 0){
                    // Intake found
                    printf("%-20s%-40s%-20d\n", c.id, c.name, 1);
                    fprintf(rfile, "%-20s%-40s%-20d\n", c.id, c.name, 1);
                    competitioncredits += 1;
                }
            }
            rewind(file);
        }
    }
    totalcredits += competitioncredits;
    printf("Total Competition Credit Hours: %d\n", competitioncredits);
    fprintf(rfile, "Total Competition Credit Hours: %d\n", competitioncredits);
}

void processCredits(FILE *file, float *totalcredits){
    if (*totalcredits >= 20){
        *totalcredits = 20;
        printf("\nTotal Credit Hours: %.1f\n", *totalcredits);
        fprintf(file, "\nTotal Credit Hours: %.1f\n", *totalcredits);
    }
    else if (*totalcredits < 16){
        printf("\nTotal Credit Hours: %.1f\n", *totalcredits);
        printf("*Remarks: Student has not met the minimum credit hours required");
        fprintf(file, "\nTotal Credit Hours: %.1f\n", *totalcredits);
        fprintf(file, "*Remarks: Student has not met the minimum credit hours required");
    }
    else{
        printf("\nTotal Credit Hours: %.1f\n", *totalcredits);
        fprintf(file, "\nTotal Credit Hours: %.1f\n", *totalcredits);
    }
}

void report(char *fName){
    struct Student stud;
    struct StudentIntake studList;
    struct StudentActivity studAct;
    char studID[10],
         intake[10];
    int found = 0;
    float totalcredits = 0;
    FILE *stfile, *sfile, *afile, *cfile, *efile, *clfile, *crfile, *wfile, *cofile, *rfile;

    stfile = fopen("student.txt", "r");
    sfile = fopen("studentList.txt", "r");
    afile = fopen("studentActivity.txt", "r");
    cfile = fopen("core.txt", "r");
    efile = fopen("elective.txt", "r");
    clfile = fopen("club.txt", "r");
    crfile = fopen("clubRole.txt", "r");
    wfile = fopen("workshop.txt", "r");
    cofile = fopen("competition.txt", "r");

    if (stfile == NULL || sfile == NULL || afile == NULL || cfile == NULL || efile == NULL || efile == NULL || clfile == NULL || crfile == NULL || wfile == NULL || cofile == NULL){
        printf("Error reading file\n");
    }
    else{
        do{
            printf("\nStudent ID: ");
            fflush(stdin);
            fgets(studID, sizeof(studID), stdin);
            studID[strcspn(studID, "\n")] = '\0';
        
            processStudentList(sfile, &studList, studID, &found);
            fseek(sfile, 0, SEEK_SET);
        } while (found == 0);

        processStudent(stfile, &stud, studID);

        char reportName[20];
        sprintf(reportName, "%s.txt", studID);
        strcpy(fName, reportName);
        rfile = fopen(reportName, "w");
        fprintf(rfile, "Student ID: %s\n", studList.studId);
        fprintf(rfile, "Name: %s\n", stud.name);
        fprintf(rfile, "Identification Number: %s\n", stud.icNum);
        fprintf(rfile, "Address: %s\n", stud.address);
        fprintf(rfile, "Phone Number: %s\n", stud.phone);
        fprintf(rfile, "Email: %s\n", stud.email);
        fprintf(rfile, "\nIntake: %s\n", studList.intake);
        fclose(rfile);

        printf("Name: %s\n", stud.name);
        printf("Identification Number: %s\n", stud.icNum);
        printf("Address: %s\n", stud.address);
        printf("Phone Number: %s\n", stud.phone);
        printf("Email: %s\n", stud.email);
        printf("\nIntake: %s\n", studList.intake);

        rfile = fopen(reportName, "a");
        processCore(rfile, cfile, studList.intake, &totalcredits);
        processElective(rfile, afile, efile, &studAct, studID, &totalcredits);
        processClub(rfile, afile, clfile, crfile, &studAct, studID, &totalcredits);
        processWorkshop(rfile, afile, wfile, &studAct, studID, &totalcredits);
        processCompetition(rfile, afile, cofile, &studAct, studID, &totalcredits);
        
        processCredits(rfile, &totalcredits);
    }
    fclose(sfile);
    fclose(afile);
    fclose(cfile);
    fclose(efile);
    fclose(clfile);
    fclose(wfile);
    fclose(cofile);
    fclose(rfile);
}

void menu1(int *option){
    printf("\nDisplay Options:\n");
    printf("    1. Module List\n");
    printf("    2. Activity List\n");
    printf("    3. Individual Student Report\n");
    printf("    4. Exit\n");
    printf("Enter an option: ");
    scanf("%d", & *option);
    fflush(stdin);
}

void moduleMenu(int *option){
    printf("\nModule List:\n");
    printf("    1. Core Module\n");
    printf("    2. Elective Module\n");
    printf("    3. Back\n");
    printf("Enter an option: ");
    scanf("%d", & *option);
    fflush(stdin);
}

void activityMenu(int *option){
    printf("\nActivity List:\n");
    printf("    1. Club\n");
    printf("    2. Workshop\n");
    printf("    3. Competition\n");
    printf("    4. Back\n");
    printf("Enter an option: ");
    scanf("%d", & *option);
    fflush(stdin);
}

void reportMenu(int *option){
    printf("\nWould you like to generate a report text file?:\n");
    printf("    1. Yes\n");
    printf("    2. No\n");
    printf("Enter an option: ");
    scanf("%d", & *option);
    fflush(stdin);
}

void loadingBar(){
    int duration = 100000;
    int steps = 20;
    int i, j;
    for (i = 0; i < steps; ++i) {
        printf("Generating...[");
        for (j = 0; j < i; ++j) {
            printf("|");
        }
        for (j = i; j < steps - 1; ++j) {
            printf(" ");
        }
        printf("] %d%%\r", (i + 1) * 100 / steps);
        fflush(stdout);
        usleep(duration);
    }
    printf("\n");
}

void programLeaderMain(){
    int option,
        loop = 0;
    char fileName[20];

    do{
        menu1(&option);
        switch (option){
            case 1:
                moduleMenu(&option);
                switch (option){
                    case 1:
                        display_core();
                        break;
                    case 2:
                        display_elective();
                        break;
                    case 3:
                        break;
                    default:
                        printf("Invalid option\n");
                }
                break;
            case 2:
                activityMenu(&option);
                switch (option){
                    case 1:
                        display_club();
                        break;
                    case 2:
                        display_workshop();
                        break;
                    case 3:
                        display_competition();
                        break;
                    case 4:
                        break;
                    default:
                        printf("Invalid option\n");
                }
                break;
            case 3:
                report(fileName);
                reportMenu(&option);

                switch (option){
                    case 1:
                        loadingBar();
                        printf("Report generated\n");
                        system(fileName);
                        remove(fileName);
                        exit(0);
                    case 2:
                        remove(fileName);
                        exit(0);
                    default:
                        printf("Invalid option\n");
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid option\n");
        }
    } while(loop == 0);
}

// int main(){
//     programLeaderMain();
//     return 0;
// }