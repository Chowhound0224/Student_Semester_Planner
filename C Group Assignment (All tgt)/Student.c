#include <stdio.h>
#include <string.h>
#include <unistd.h> // Library for adding delay function

#define studentListTxt "studentList.txt"
#define studentActivityTxt "studentActivity.txt"
#define coreTxt "core.txt"
#define electiveTxt "elective.txt"
#define clubTxt "club.txt"
#define clubRoleTxt "clubRole.txt"
#define workshopTxt "workshop.txt"
#define competitionTxt "competition.txt"

struct CoreModule{
    char moduleCode[10];
    char intakeCode[10];
    char moduleName[100];
    char day[10];
    char startTime[10];
    char endTime[10];
    char venue[100];
};

struct StudentActivityList{
    char studentID[10];
    char moduleCode[10];
};

struct StudentList{
    char studentID[10];
    char intakeCode[10];
};

struct ElectiveorSpecialiseModule{
    char moduleCode[10];
    char intakeCode[10];
    char moduleName[100];
    char day[10];
    char startTime[10];
    char endTime[10];
    char venue [100];
    int creditHour;
};

struct TalkorWorkshop {
    char moduleCode[10];
    char moduleName[100];
    char date[10];
    char startTime[10];
    char endTime[10];
    char venue[100];
};

struct CluborSociety {
    char moduleCode[10];
    char moduleName[10];
};

struct CluborSocietyRoles {
    char roles[100];
    char studentID[10];
    char moduleCode[10];
    int maxstudIDLimit;
};

struct Competition {
    char moduleCode[10];
    char moduleName[100];
    char date[10];
    char venue[100];
};

void regClubRole(const char *studID, char moduleCode[10], char role[20], struct CluborSocietyRoles clubRoles[], int roleChoice);
void ActivityRegister(const char *studID);
void UnregisterActivity(const char *studid);
void Profile(const char *studid);
void Logout();
void studentMain(const char *studentID);

// int main(){
//     studentMain();
//     return 0;
// }

void studentMain(const char *studentID) {
    int student_option;
    char studID[10];

    strcpy(studID, studentID);
    
    printf("*\t*\t*\t*\n");
    printf("1. Register Activities\n");
    printf("2. Unregister Activities\n");
    printf("3. View / Track Activities\n");
    printf("4. Logout\n");
    printf("*\t*\t*\t*\t\n");

    printf("Select 1 of the options given above: ");
    scanf("%d", &student_option);

    switch (student_option) {
        case 1:
            ActivityRegister(studID);
            break;

        case 2:
            UnregisterActivity(studID);
            break;

        case 3:
            Profile(studID);
            break;
        
        case 4:
            Logout();
            break;

        default:
            printf("Invalid option! Please try again.\n");
    }
}

void ActivityRegister(const char *studID) {
    int register_options;
    char confirmline;
    char line[100], moduleCode[100];

    // Declaring Struct for Clubs
    struct CluborSocietyRoles clubRoles[] = {
        {"President", "", "", 1},
        {"Vice President", "", "", 1},
        {"Secretary", "", "", 1},
        {"Treasurer", "", "", 1},
        {"Commitee Member", "", "", 2},
        {"Member", "", "", 4}
    };

    FILE *em = fopen(electiveTxt, "r"); // Open Elective Module text file in read mode
    FILE *tw = fopen(workshopTxt,"r"); // Open Talk / Workshop text file in read mode
    FILE *cs = fopen(clubTxt,"r"); // Open Club / Society text file in read mode
    FILE *comp = fopen(competitionTxt,"r"); // Open Competition text file in read mode

    if(em == NULL || tw == NULL || cs == NULL || comp == NULL) {
        printf("Error opening file! Please try again!\n");
        return;
    }

    printf("1. Elective / Specialise Module\n");
    printf("2. Talk / Workshop\n");
    printf("3. Competition\n");
    printf("4. Club / Society\n");

    printf("Select 1 of the options given above to register: ");
    scanf("%d",&register_options);

    if (register_options == 1) {

        if (em == NULL) {
            printf("Error opening file! Please try again!\n");
            return;
        }

        printf("Here are the list for Elective / Specialise modules:\n");

        while (fgets(line, 100, em)) {
            printf("%s", line);
        }

        fclose(em); // Closing the ElectiveModule.txt file after reading

        printf("\nEnter the module code you want to register: ");
        scanf(" %s", moduleCode);

        printf("Confirm registering this Module? (Y/N): ");
        scanf(" %c", &confirmline);

        if (confirmline == 'Y' || confirmline == 'y') {
            FILE *stu = fopen(studentActivityTxt, "a"); // Open in append mode

            if (stu == NULL) {
                printf("Error opening file! Please try again!\n");
                return;
            }

            fprintf(stu, "%s,%s\n", studID, moduleCode);    // Append the module code to StudentModule.txt
            fclose(stu);

            printf("Successfully registered!\n");

        } else if (confirmline == 'N' || confirmline == 'n') {
            printf("Cancelled!\n");
        } else {
            printf("Invalid option! Please try again!\n");
        }
    }

    else if (register_options == 2) {
        if (tw == NULL) {
            printf("Error opening file! Please try again!\n");
            return;
        }

        printf("Here are the list for Talk / Workshop:\n");

        while (fgets(line, 100, tw)) {
            printf("%s", line);
        }

        fclose(tw); // Closing the TalkWorkshop.txt file after reading

        printf("\nEnter the module code you want to register: ");
        scanf(" %s", moduleCode);

        printf("Confirm registering this Module? (Y/N): ");
        scanf(" %c", &confirmline);

        if (confirmline == 'Y' || confirmline == 'y') {
            FILE *stu = fopen(studentActivityTxt, "a"); // Open in append mode

            if (stu == NULL) {
                printf("Error opening file! Please try again!\n");
                return;
            }

            fprintf(stu, "%s,%s\n", studID, moduleCode);    // Append the module code to StudentModule.txt
            fclose(stu);

            printf("Successfully registered!\n");

            } else if (confirmline == 'N' || confirmline == 'n') {
                printf("Cancelled!\n");
            } else {
                printf("Invalid option! Please try again!\n");
            }
    }

    else if (register_options == 3) {
        if (comp == NULL) {
            printf("Error opening file! Please try again!\n");
            return;
        }

        printf("Here are the list for Club / Society modules:\n");

        while (fgets(line, 100, comp)) {
            printf("%s", line);
        }

        fclose(comp); // Closing the ClubSociety.txt file after reading

        printf("\nEnter the module code you want to register: ");
        scanf(" %s", moduleCode);

        printf("Confirm registering this Module? (Y/N): ");
        scanf(" %c", &confirmline);

        if (confirmline == 'Y' || confirmline == 'y') {
            FILE *stu = fopen(studentActivityTxt, "a"); // Open in append mode

            if (stu == NULL) {
                printf("Error opening file! Please try again!\n");
                return;
            }

            fprintf(stu, "%s,%s\n", studID, moduleCode);    // Append the module code to StudentModule.txt
            fclose(stu);

            printf("Successfully registered!\n");

        } else if (confirmline == 'N' || confirmline == 'n') {
            printf("Cancelled!\n");
        } else {
            printf("Invalid option! Please try again!\n");
        }
    }
    else if (register_options == 4) {
            if (cs == NULL) {
            printf("Error opening file! Please try again!\n");
            return;
        }

        printf("Here are the list for Club / Society modules:\n");

        while (fgets(line, 100, cs)) {
            printf("%s", line);
        }

        fclose(cs); // Closing the ClubSociety.txt file after reading
    
        printf("\nEnter the module code you want to register: ");
        scanf(" %s", moduleCode);

        printf("Confirm registering this Module? (Y/N): ");
        scanf(" %c", &confirmline);

        if (confirmline == 'Y' || confirmline == 'y') {
            printf("Here are the roles available:\n");
            int numRoles = sizeof(clubRoles) / sizeof(clubRoles[0]);

            for (int i = 0; i < numRoles; i++) {
                printf("%d, %s\n", i + 1, clubRoles[i].roles);
            }

            int roleChoice;
            printf("Enter the Role you want to register based on the numbers shown above (1-%d): ", numRoles);
            scanf("%d", &roleChoice);

            if (roleChoice < 1 || roleChoice > numRoles) {
                printf("Invalid role choice. Please try again!");
                return;
            }

            char role[20];
            strcpy(role, clubRoles[roleChoice - 1].roles);
            regClubRole(studID, moduleCode, role, clubRoles, roleChoice);
        }
        else if (confirmline == 'N' || confirmline == 'n') {
            printf("Cancelled!\n");
        } else {
            printf("Invalid option! Please try again!\n");
        }
    }

    else {
        printf("Invalid Option! Terminating!\n");
        return;
    }
}

void regClubRole(const char *studID, char moduleCode[10], char role[20], struct CluborSocietyRoles clubRoles[], int roleChoice) {
    char line[100];
    FILE *studcs = fopen(clubRoleTxt, "r"); // Opening student club list in append mode

    if (studcs == NULL) {
        printf("Error opening file! Please try again!\n");
        return;
    }

    // Validation for students not registering for any other roles in the same club
    char tempstudID[10], tempmoduleCode[10], temprole[20];

    while (fgets(line, sizeof(line), studcs) != NULL) {
        if (sscanf(line, "%9[^,],%9[^,],%19s", tempstudID, tempmoduleCode, temprole) == 3) {
            if (strcmp(tempstudID, studID) == 0 && strcmp(tempmoduleCode, moduleCode) == 0) {
                printf("Oops! You've already registered in this specific club / Society!\n");
                fclose(studcs); // Close file after found
                return;
            }
        }
    }

    fclose(studcs);

    // Validation for students not repeating the same role in the same club
    studcs = fopen(clubRoleTxt, "r"); // Opening student club list in append mode

    if (studcs == NULL) {
        printf("Error opening file! Please try again!\n");
        return;
    }
    
    while (fgets(line, sizeof(line), studcs) != NULL) {
        if (sscanf(line, "%9[^,],%9[^,],%19\n", tempstudID, tempmoduleCode, temprole) == 3) {
            if (strcmp(tempstudID, studID) == 0 && strcmp(temprole, role) == 0) {
                fclose(studcs); // Close file after found 
                printf("You have already registered as %s for this club! Please try again!\n");
                return;
            }
        }
    }

    fclose(studcs);

    //Validation to check roles limit
    int rolecount = 0;
    studcs = fopen(clubRoleTxt, "r"); // Opening student club list in read mode

    if (studcs == NULL) {
        printf("Error opening file! Please try again!");
        return;
    }

    while (fscanf(studcs, "%9[^,],%9[^,],%19[^\n]", tempstudID, tempmoduleCode, temprole) == 3) {
        if (strcmp(tempmoduleCode, moduleCode) == 0 && strcmp(temprole, role) == 0) {
            rolecount++;
        }
    }

    fclose(studcs);

    // validation to check whether any student ID has clash in same role
    if (rolecount >= clubRoles[roleChoice - 1].maxstudIDLimit) {
        printf("Sorry, the role you have chosen has reached its maximum limit. Please try again!\n");
        return;
    }

    else {
        studcs = fopen(clubRoleTxt, "a"); // Opening student club list in append mode

        if (studcs == NULL) {
            printf("Error Opening file! Please try again!");
            return;
        }

        fprintf(studcs, "%s,%s,%s\n", studID, moduleCode, role); // appending student ID, module code and role to studentclublist.txt
        fclose(studcs);

        FILE *stu = fopen("studentActivityTxt", "a"); // Open in append mode

        if (stu == NULL) {
            printf("Error opening file! Please try again!\n");
            return;
        }

        fprintf(stu, "%s,%s\n", studID, moduleCode);
        fclose(stu);

        printf("Successfully Registered as %s!\n", role);

    }
}

void UnregisterActivity(const char *studid) {
    char studentID[10], moduleCode[10], roles[100];
    char unregister_option[10];
    char confirm_unregister;

    FILE *stu = fopen(studentActivityTxt, "r");
    FILE *core = fopen(coreTxt, "r");
    FILE *em = fopen(electiveTxt, "r");
    FILE *tw = fopen(workshopTxt, "r");
    FILE *cs = fopen(clubTxt, "r");
    FILE *studcs = fopen(clubRoleTxt, "r");
    FILE *comp = fopen(competitionTxt, "r");

    if (stu == NULL || em == NULL || tw == NULL || cs == NULL || comp == NULL) {
        printf("Error opening file(s)! Please try again!\n");
        return;
    }

    printf("Core Modules are listed here:\n");
    char line[100];
    while (fgets(line, sizeof(line), core)) {
        printf("%s", line);
    }

    int studidfound = 0;
    int activityfound = 0;

    struct StudentActivityList studentActivities[100];
    struct CoreModule coreModules[100];
    struct ElectiveorSpecialiseModule electiveModules[100];
    struct TalkorWorkshop talkWorkshops[100];
    struct CluborSocietyRoles clubRoles[100];
    struct CluborSociety CluborSociety[100];
    struct Competition competitions[100];

    int numStudentActivities = 0;
    while (fscanf(stu, "%9[^,],%9s\n", studentActivities[numStudentActivities].studentID, studentActivities[numStudentActivities].moduleCode) == 2) {
        numStudentActivities++;
    }

    int numCoreModules = 0;
    while (fscanf(core, "%9[^,],%9[^,],%99[^,],%9[^,],%9[^,],%9[^,],%99[^,\n]\n", coreModules[numCoreModules].moduleCode,
                   coreModules[numCoreModules].intakeCode, coreModules[numCoreModules].moduleName,
                   coreModules[numCoreModules].day, coreModules[numCoreModules].startTime,
                   coreModules[numCoreModules].endTime, coreModules[numCoreModules].venue) == 7) {
        numCoreModules++;
    }

    int numElectiveModules = 0;
    while (fscanf(em, "%9[^,],%9[^,],%99[^,],%9[^,],%9[^,],%9[^,],%99[^,],%d\n", electiveModules[numElectiveModules].moduleCode,
                   electiveModules[numElectiveModules].intakeCode, electiveModules[numElectiveModules].moduleName,
                   electiveModules[numElectiveModules].day, electiveModules[numElectiveModules].startTime,
                   electiveModules[numElectiveModules].endTime, electiveModules[numElectiveModules].venue, &electiveModules[numElectiveModules].creditHour) == 8) {
        numElectiveModules++;
    }

    int numTalkWorkshops = 0;
    while (fscanf(tw, "%9[^,],%99[^,],%9[^,],%9[^,],%9[^,],%99[^\n]\n", talkWorkshops[numTalkWorkshops].moduleCode,
                   talkWorkshops[numTalkWorkshops].moduleName, talkWorkshops[numTalkWorkshops].date,
                   talkWorkshops[numTalkWorkshops].startTime, talkWorkshops[numTalkWorkshops].endTime,
                   talkWorkshops[numTalkWorkshops].venue) == 6) {
        numTalkWorkshops++;
    }

    int numClubsorSociety = 0;
    while (fscanf(cs, "%9[^,],%19[^\n]", CluborSociety[numClubsorSociety].moduleCode, CluborSociety[numClubsorSociety].moduleName) == 2) {
        numClubsorSociety++;
    }

    int numClubRoles = 0;
    while (fgets(line, sizeof(line), studcs) != NULL) {
        if (sscanf(line, "%9[^,],%9[^,],%99[^\n]\n", clubRoles[numClubRoles].studentID, clubRoles[numClubRoles].moduleCode, clubRoles[numClubRoles].roles) == 3) {
            numClubRoles++;
        }
        else {
            printf("Error reading line!\n", line);
        }

    }

    int numCompetition = 0;
    while (fscanf(comp, "%9[^,],%99[^,],%9[^,],%99[^\n]\n", competitions[numCompetition].moduleCode,
                   competitions[numCompetition].moduleName, competitions[numCompetition].date,
                   competitions[numCompetition].venue) == 4) {
        numCompetition++;
    }

    for (int i = 0; i < numStudentActivities; i++) {
        if (strcmp(studid, studentActivities[i].studentID) == 0) {
            studidfound = 1;
            printf("Student ID: %s\nModule Code: %s\n", studentActivities[i].studentID, studentActivities[i].moduleCode);

            int coreModuleFound = 0;
            for (int j = 0; j < numCoreModules; j++) {
                if (strcmp(studentActivities[i].moduleCode, coreModules[j].moduleCode) == 0) {
                    printf("Information:\n Module Name: %s, Day: %s, Start Time: %s, End Time: %s, Venue: %s\n",
                            coreModules[j].moduleName, coreModules[j].day,
                            coreModules[j].startTime, coreModules[j].endTime,
                            coreModules[j].venue);
                    activityfound = 1;
                    coreModuleFound = 1;
                    break;
                }
            }

            for (int j = 0; j < numElectiveModules; j++) {
                if (strcmp(studentActivities[i].moduleCode, electiveModules[j].moduleCode) == 0) {
                    printf("Information:\n Module Name: %s, Day: %s, Start Time: %s, End Time: %s, Venue: %s\n",
                            electiveModules[j].moduleName, electiveModules[j].day,
                            electiveModules[j].startTime, electiveModules[j].endTime,
                            electiveModules[j].venue);
                    activityfound = 1;
                    break;
                }
            }

            for (int j = 0; j < numTalkWorkshops; j++) {
                if (strcmp(studentActivities[i].moduleCode, talkWorkshops[j].moduleCode) == 0) {
                    printf("Information:\n Module Name: %s, Date: %s, Start Time: %s, End Time: %s, Venue: %s\n",
                            talkWorkshops[j].moduleName, talkWorkshops[j].date,
                            talkWorkshops[j].startTime, talkWorkshops[j].endTime,
                            talkWorkshops[j].venue);
                    activityfound = 1;
                    break;
                }  
            }

            for (int j = 0; j < numClubsorSociety; j++) {
                if (strcmp(studentActivities[i].moduleCode, CluborSociety[j].moduleCode) == 0) {
                    printf("Information:\n Club Name: %s\n", CluborSociety[j].moduleName);
                    activityfound = 1;
                    break;
                }
            }

            for (int j = 0; j < numClubRoles; j++) {
                if (strcmp(studentActivities[i].studentID, clubRoles[j].studentID) == 0 &&
                    strcmp(studentActivities[i].moduleCode, clubRoles[j].moduleCode) == 0) {
                    printf("Role: %s\n", clubRoles[j].roles);
                    activityfound = 1;
                    break;
                }
            }

            for (int j = 0; j < numCompetition; j++) {
                if(strcmp(studentActivities[i].moduleCode, competitions[j].moduleCode) == 0) {

                    printf("Information:\n Module Name: %s, Date: %s, Venue: %s\n",
                            competitions[j].moduleName, competitions[j].date,
                            competitions[j].venue);
                    activityfound = 1;
                    break;
                }
            }
        }
    }

    printf("Enter a Module / Activity Code to unregister: ");
    scanf("%s", unregister_option);

    for (int i = 0; i < numStudentActivities; i++) {
        if (strcmp(studid, studentActivities[i].studentID) == 0) {
            if (strcmp(unregister_option, studentActivities[i].moduleCode) == 0) {
                printf("Are you sure you want to unregister this activity? (Y/N): ");
                scanf(" %c", &confirm_unregister);

                if (confirm_unregister == 'Y' || confirm_unregister == 'y') {
                    // Removing list from StudentModule.txt
                    FILE *temp = fopen("temp.txt", "w");

                    if (temp == NULL) {
                        printf("Error opening file(s)! Please try again!\n");
                        return;
                    }

                // Rewrite and update the temp file from StudentModule.txt
                fseek(stu, 0, SEEK_SET);
                char removeline[100];

                while (fgets(removeline, sizeof(removeline), stu) != NULL) {
                    if (sscanf(removeline, "%9[^,],%9s", studentID, moduleCode) == 2) {
                        if (strcmp(studentID, studid) == 0 && strcmp(moduleCode, unregister_option) == 0) {
                            continue; // Skip the line to be removed
                        }
                        fprintf(temp, "%s,%s\n", studentID, moduleCode); // Write the line to temp file
                    }
                }

                fclose(stu);
                fclose(temp);

                // Renaming the temp file to StudentModule.txt
                remove(studentActivityTxt);
                rename("temp.txt", studentActivityTxt);

                printf("Successfully Unregistered!\n");

                // If users want to unregister from clubs
                if (strncmp(unregister_option, "CL", 2) == 0) {
                    // removing list from studentclublist.txt
                    FILE *cstemp = fopen("tempforclubsociety.txt", "w");

                    if (cstemp == NULL) {
                        printf("Error opening file(s)! Please try again!\n");
                        return;
                    }

                    // Rewrite and update the temp file from studentclublist.txt
                    fseek(studcs, 0, SEEK_SET);
                    char clubremoveline[100];
                    
                    while (fgets(clubremoveline, sizeof(clubremoveline), studcs) != NULL) {
                        if (sscanf(clubremoveline, "%9[^,],%9[^,],%99[^\n]\n", studentID, moduleCode, roles) == 3) {
                            if (strcmp(studentID, studid) == 0 && strcmp(moduleCode, unregister_option) == 0) {
                                continue; // Skip the line to be removed
                            }
                            
                            fprintf(cstemp, "%s,%s,%s\n", studentID, moduleCode, roles); // Write the line to temp file
                        }
                    }

                    fclose(studcs);
                    fclose(cstemp);

                    // Renaming the temp file to studentclublist.txt
                    remove(clubRoleTxt);
                    rename("tempforclubsociety.txt", clubRoleTxt);
                }

                break;
            }
            
                else if (confirm_unregister == 'N' || confirm_unregister == 'n') {
                    printf("You have \x1b[31m cancelled \x1b[0m the unregister process!\n");
                    break;
                }
                else {
                    printf("Invalid option! Please try again!\n");
                    break;
                }
            }
        }
    }

    if (!studidfound) {
        printf("Student ID not found!\n");
    }

    if (studidfound && !activityfound) {
        printf("No activities found for this student!\n");
    }

    fseek(em, 0, SEEK_SET);
    fseek(tw, 0, SEEK_SET);
    fseek(cs, 0, SEEK_SET);
    fseek(comp, 0, SEEK_SET);
    fseek(core, 0, SEEK_SET);

    fclose(stu);
    fclose(em);
    fclose(tw);
    fclose(cs);
    fclose(comp);
}

void Profile(const char *studid) {
        char studentID[10];
        char intakeCode[10];
        float totalElectiveCreditHour = 0;
        float totalCoreCreditHour = 0;
        float totalcredits = 0;
        float clubcreditHour = 0;
        float competitioncreditHour = 0;
        float competitioncodeCount[100] = {0}; // Array to store the number of times a competition code appears
        float talkworkshopcreditHour = 0;
        float talkworkshopcodeCount[100] = {0}; // Array to store the number of times a talk/workshop code appears
        float coremodulescreditHour = 12;

        FILE *stu = fopen(studentActivityTxt, "r");
        FILE *core = fopen(coreTxt, "r");
        FILE *studlist = fopen(studentListTxt, "r");
        FILE *em = fopen(electiveTxt, "r");
        FILE *tw = fopen(workshopTxt, "r");
        FILE *cs = fopen(clubTxt, "r");
        FILE *studcs = fopen(clubRoleTxt, "r");
        FILE *comp = fopen(competitionTxt, "r");

        if (stu == NULL || em == NULL || tw == NULL || cs == NULL ||studcs == NULL || comp == NULL) {
            printf("Error opening file(s)! Please try again!\n");
            return;
        }

        int intakeCodeFound = 0;
        while (fscanf(studlist, "%9[^,],%9s\n", studentID, intakeCode) == 2) {
            if (strcmp(studid, studentID) == 0) {
                intakeCodeFound = 1;
                break;
            }
        }

        if (!intakeCodeFound) {
            printf("Student ID not found!\n");
            fclose(studlist);
            return;
        }

        printf("Core Modules for intake code %s are listed here:\n", intakeCode);
        char line[100];
        while (fgets(line, sizeof(line), core)) {
            if(strstr(line, intakeCode) != NULL) {
                printf("%s", line);
            }
        }

        int studidfound = 0;
        int activityfound = 0;

        struct StudentActivityList studentActivities[100];
        struct CoreModule coreModules[100];
        struct ElectiveorSpecialiseModule electiveModules[100];
        struct TalkorWorkshop talkWorkshops[100];
        struct CluborSocietyRoles clubRoles[100];
        struct CluborSociety CluborSociety[100];
        struct Competition competitions[100];

        int numStudentActivities = 0;
        while (fscanf(stu, "%9[^,],%9s\n", studentActivities[numStudentActivities].studentID, studentActivities[numStudentActivities].moduleCode) == 2) {
            numStudentActivities++;
        }

        int numCoreModules = 0;
        while (fscanf(core, "%9[^,],%9[^,],%99[^,],%9[^,],%9[^,],%9[^,],%99[^,\n]\n", coreModules[numCoreModules].moduleCode,
                    coreModules[numCoreModules].intakeCode, coreModules[numCoreModules].moduleName,
                    coreModules[numCoreModules].day, coreModules[numCoreModules].startTime,
                    coreModules[numCoreModules].endTime, coreModules[numCoreModules].venue) == 7) {
            numCoreModules++;
        }

        int numElectiveModules = 0;
        while (fscanf(em, "%9[^,],%9[^,],%99[^,],%9[^,],%9[^,],%9[^,],%99[^,],%d\n", electiveModules[numElectiveModules].moduleCode,
                    electiveModules[numElectiveModules].intakeCode, electiveModules[numElectiveModules].moduleName,
                    electiveModules[numElectiveModules].day, electiveModules[numElectiveModules].startTime,
                    electiveModules[numElectiveModules].endTime, electiveModules[numElectiveModules].venue, &electiveModules[numElectiveModules].creditHour) == 8) {
            numElectiveModules++;
        }

        int numTalkWorkshops = 0;
        while (fscanf(tw, "%9[^,],%99[^,],%9[^,],%9[^,],%9[^,],%99[^\n]\n", talkWorkshops[numTalkWorkshops].moduleCode,
                    talkWorkshops[numTalkWorkshops].moduleName, talkWorkshops[numTalkWorkshops].date,
                    talkWorkshops[numTalkWorkshops].startTime, talkWorkshops[numTalkWorkshops].endTime,
                    talkWorkshops[numTalkWorkshops].venue) == 6) {
            numTalkWorkshops++;
        }

        int numClubsorSociety = 0;
        while (fscanf(cs, "%9[^,],%19[^\n]", CluborSociety[numClubsorSociety].moduleCode, CluborSociety[numClubsorSociety].moduleName) == 2) {
            numClubsorSociety++;
        }

        int numClubRoles = 0;
        while (fgets(line, sizeof(line), studcs) != NULL) {
            if (sscanf(line, "%9[^,],%9[^,],%99[^\n]\n", clubRoles[numClubRoles].studentID, clubRoles[numClubRoles].moduleCode, clubRoles[numClubRoles].roles) == 3) {
                numClubRoles++;
            }
            else {
                printf("Error reading line!\n", line);
            }

        }

        int numCompetition = 0;
        while (fscanf(comp, "%9[^,],%99[^,],%9[^,],%99[^\n]\n", competitions[numCompetition].moduleCode,
                    competitions[numCompetition].moduleName, competitions[numCompetition].date,
                    competitions[numCompetition].venue) == 4) {
            numCompetition++;
        }

        printf("-----------------------------\n");
        for (int i = 0; i < numStudentActivities; i++) {
            if (strcmp(studid, studentActivities[i].studentID) == 0) {
                studidfound = 1;
                printf("Module Code: %s\n", studentActivities[i].moduleCode);

                int coreModuleFound = 0;
                for (int j = 0; j < numCoreModules; j++) {
                    if (strcmp(studentActivities[i].moduleCode, coreModules[j].moduleCode) == 0) {
                        printf("Information:\n Module Name: %s\n Day: %s\n Start Time: %s\n End Time: %s\n Venue: %s\n",
                                coreModules[j].moduleName, coreModules[j].day,
                                coreModules[j].startTime, coreModules[j].endTime,
                                coreModules[j].venue);
                        activityfound = 1;
                        coreModuleFound = 1;
                        totalcredits += 3;
                        break;
                    }
                }

                for (int j = 0; j < numElectiveModules; j++) {
                    if (strcmp(studentActivities[i].moduleCode, electiveModules[j].moduleCode) == 0) {
                        printf("Information:\n Module Name: %s\n Day: %s\n Start Time: %s\n End Time: %s\n Venue: %s\n",
                                electiveModules[j].moduleName, electiveModules[j].day,
                                electiveModules[j].startTime, electiveModules[j].endTime,
                                electiveModules[j].venue);
                        activityfound = 1;
                        totalcredits += electiveModules[j].creditHour;
                        totalElectiveCreditHour += electiveModules[j].creditHour; // increment elective credits
                        break;
                    }
                }

                for (int j = 0; j < numTalkWorkshops; j++) {
                    if (strcmp(studentActivities[i].moduleCode, talkWorkshops[j].moduleCode) == 0) {
                        printf("Information:\n Module Name: %s\n Date: %s\n Start Time: %s\n End Time: %s\n Venue: %s\n",
                                talkWorkshops[j].moduleName, talkWorkshops[j].date,
                                talkWorkshops[j].startTime, talkWorkshops[j].endTime,
                                talkWorkshops[j].venue);
                        activityfound = 1;

                        // Calculation for Talk/Workshop Credit Points
                        if (talkworkshopcodeCount[i] == 0) {
                            talkworkshopcreditHour++;
                            talkworkshopcodeCount[i]++;
                        }
                        break;
                    }
                }

                for (int j = 0; j < numClubsorSociety; j++) {
                    if (strcmp(studentActivities[i].moduleCode, CluborSociety[j].moduleCode) == 0) {
                        printf("Information:\n Club Name: %s\n", CluborSociety[j].moduleName);
                        activityfound = 1;
                        break;
                    }
                }

                for (int j = 0; j < numClubRoles; j++) {
                    if (strcmp(studentActivities[i].studentID, clubRoles[j].studentID) == 0 &&
                        strcmp(studentActivities[i].moduleCode, clubRoles[j]. moduleCode) == 0) {
                        printf("Role: %s\n", clubRoles[j].roles);

                        // Calculation for Club Credit Points
                        if (strcmp(clubRoles[j].roles, "President") == 0) {
                            clubcreditHour = 1.5;
                        }
                        else if (strcmp(clubRoles[j].roles, "Vice President") == 0) {
                            clubcreditHour = 1.4;
                        }
                        else if (strcmp(clubRoles[j].roles, "Secretary") == 0) {
                            clubcreditHour = 1.3;
                        }
                        else if (strcmp(clubRoles[j].roles, "Treasurer") == 0) {
                            clubcreditHour = 1.2;
                        }
                        else if (strcmp(clubRoles[j].roles, "Committee Member") == 0) {
                            clubcreditHour = 1.1;
                        }
                        else if (strcmp(clubRoles[j].roles, "Member") == 0) {
                            clubcreditHour = 0.5;
                        }
                        else {
                            clubcreditHour = 0;
                        }
                        break;
                    }
                }

                for (int j = 0; j < numCompetition; j++) {
                    if(strcmp(studentActivities[i].moduleCode, competitions[j].moduleCode) == 0) {
                        printf("Information:\n Module Name: %s\n Date: %s\n Venue: %s\n",
                                competitions[j].moduleName, competitions[j].date,
                                competitions[j].venue);
                        activityfound = 1;

                        // Calculation for Competition Credit Points
                        if (competitioncodeCount[i] == 0) {
                            competitioncreditHour++;
                            competitioncodeCount[i]++;
                        }
                        break;
                    }
                }
                printf("-----------------------------\n");
            }
        }

        if (!studidfound) {
            printf("Student ID not found!\n");
        }

        if (studidfound && !activityfound) {
            printf("No activities found for this student!\n");
        }

        totalcredits = coremodulescreditHour + totalElectiveCreditHour + talkworkshopcreditHour + clubcreditHour + competitioncreditHour;

        // Validation for totalcredits to stay at maximum of 20
        if (totalcredits >= 20) {
            totalcredits = 20;
        }
        
        // Displaying credit hours STUD prompt has earned:
        printf("\nCore Credits: %.2f\n", coremodulescreditHour);
        printf("Elective Credits: %.2f\n", totalElectiveCreditHour);
        printf("Talk / Workshop Credits: %.2f\n", talkworkshopcreditHour);
        printf("Club / Society Credits: %.2f\n", clubcreditHour);
        printf("Competition Credits: %.2f\n", competitioncreditHour);
        printf("Total Credits: %.2f\n", totalcredits);

        // Informing users that totalcredits will only be at maximum of 20
        if (totalcredits >= 20) {
            totalcredits = 20;
            printf("\nYour Total Credits has gone over 20, hence it will be capped at 20!\n");
        }
        

        fseek(em, 0, SEEK_SET);
        fseek(tw, 0, SEEK_SET);
        fseek(cs, 0, SEEK_SET);
        fseek(comp, 0, SEEK_SET);
        fseek(core, 0, SEEK_SET);

        fclose(stu);
        fclose(em);
        fclose(tw);
        fclose(cs);
        fclose(comp);
    }

void Logout() { // Logout function
    printf("Processing ");
    fflush(stdout); // Flushes off the standard output buffer

    printf(".");

    for (int i=0l;i<5;i++) { // For loop to add a delay of 3 seconds with loading animation
        printf(" ~ .");
        fflush(stdout);
        sleep(1); // Delay function with a total of 1 second delay added here
    }

    printf("\nYou have \x1b[32m successfully \x1b[0m logged out!\n"); // Adding colour to text
    sleep(1); // Delay of 1 second added here
    printf("Thank you!");
}