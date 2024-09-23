#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define coreTxt "core.txt"
#define electiveTxt "elective.txt"
#define clubTxt "club.txt"
#define workshopTxt "workshop.txt"
#define competitionTxt "competition.txt"

// Define the structure for an activity
struct Activity {
    char code[30];
    char intakeCode[30];
    char name[100];
    char day[10];
    char startTime[10];
    char endTime[10];
    char venue[30];
    float credits;
    char date[20];
};

int convertToMinutes(char *time) {
    int hours, minutes;
    sscanf(time, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

// Function to validate time conflict
int hasTimeConflict(struct Activity existing, char *newStartTime, char *newEndTime) {
    int existingStart = convertToMinutes(existing.startTime);
    int existingEnd = convertToMinutes(existing.endTime);
    int newStart = convertToMinutes(newStartTime);
    int newEnd = convertToMinutes(newEndTime);

    if ((newStart >= existingStart && newStart < existingEnd) ||
        (newEnd > existingStart && newEnd <= existingEnd) ||
        (newStart <= existingStart && newEnd >= existingEnd)) {
        return 1; // Time conflict
    }

    return 0; // No time conflict
}

// Validation function
int validate(char intakeCode[], char day[], char startTime[], char endTime[]) {
    struct Activity activities[100];  // Adjust the size based on your needs
    int activityCount = 0;
    FILE *file = fopen(coreTxt, "r");
    while (fscanf(file, "%19[^,],%19[^,],%49[^,],%3[^,],%9[^,],%9[^,],%19[^\n]\n",
                  activities[activityCount].code,
                  activities[activityCount].intakeCode,
                  activities[activityCount].name,
                  activities[activityCount].day,
                  activities[activityCount].startTime,
                  activities[activityCount].endTime,
                  activities[activityCount].venue) == 7) {
        activityCount++;
    }
    fclose(file);
    FILE *electiveFile = fopen(electiveTxt, "r");
    if (electiveFile == NULL) {
        perror("Error opening file");
        return 1;
    }
    while(fscanf(electiveFile, "%19[^,],%19[^,],%49[^,],%3[^,],%9[^,],%9[^,],%19[^,],%f\n",
                    activities[activityCount].code,
                    activities[activityCount].intakeCode,
                    activities[activityCount].name,
                    activities[activityCount].day,
                    activities[activityCount].startTime,
                    activities[activityCount].endTime,
                    activities[activityCount].venue,
                    &activities[activityCount].credits) == 8) {
            activityCount++;
        }
    fclose(electiveFile);
    for (int i = 0; i < activityCount; i++) {
        if (strcmp(activities[i].intakeCode, intakeCode) == 0 && strcmp(activities[i].day, day) == 0) {
            if (hasTimeConflict(activities[i], startTime, endTime)==1) {
                printf("Time conflict with existing activity: %s\n", activities[i].name);
                return 0; // Validation failed
            }
        }
    }
    return 1; // Validation passed
}

void clearbuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int is_leap_year(int year) {
    if (year % 4 == 0 && year % 100 != 0){
        return 1;
    } else if (year % 400 == 0){
        return 1;
    } else {
        return 0;
    }
}

int is_valid_date(const char *date) {
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) == 3) {
        if (year >= 2023 && month >= 1 && month <= 12) {
            int max_days_in_month;
            if (month == 2) {
                if (is_leap_year(year)) {
                    max_days_in_month = 29;
                } else {
                    max_days_in_month = 28;
                }
            } else if (month == 4 || month == 6 || month == 9 || month == 11) {
                max_days_in_month = 30;
            } else {
                max_days_in_month = 31;
            }

            if (day >= 1 && day <= max_days_in_month) {
                return 1;
            }
        }
    }
    return 0;
}

int isValidTimeFormat(const char *timeStr) {
    int hours, minutes;
    if (sscanf(timeStr, "%d:%d", &hours, &minutes) == 2) {
        if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
            return 1; // Valid time format
        }
    }
    return 0; // Invalid time format
}
int isEndTimeGreaterThanStartTime(const char *startTime, const char *endTime) {
    int startHour, startMinute, endHour, endMinute;
    if (sscanf(startTime, "%d:%d", &startHour, &startMinute) == 2 && sscanf(endTime, "%d:%d", &endHour, &endMinute) == 2) {
        if (startHour < endHour || (startHour == endHour && startMinute < endMinute)) {
            return 1; // End time is greater than start time
        }
    }
    return 0; // End time is not greater than start time
}
int is_valid_day(const char* input) {
    const char* valid_days[] = { "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    int num_valid_days = sizeof(valid_days) / sizeof(valid_days[0]);

    for (int i = 0; i < num_valid_days; i++) {
        if (strcasecmp(input, valid_days[i]) == 0) {
            return 1; // Input matches a valid day
        }
    }

    return 0; // Input does not match any valid day
}
int is_id_exists(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // File doesn't exist or cannot be opened, so ID doesn't exist.
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        char stored_id[10];  // Include space for the null terminator
        if (sscanf(line, "%9s", stored_id) == 1) {
            if (strncasecmp(id, stored_id, 9) == 0) {  // Case-insensitive comparison
                fclose(file);
                return 1; // ID exists in the file.
            }
        }
    }

    fclose(file);
    return 0; // ID doesn't exist in the file.
}

char *generateUniqueID(const char *filename) {
    char num[6];
    char line[1000];
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        // Handle the case where the file doesn't exist or cannot be opened.
        return NULL;
    }

    int count = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
            count++;
        }
    fclose(file);

    while (1) {
        sprintf(num, "%05d", count);
        char result[20];

        if (strcmp(filename, coreTxt) == 0) {
            strcpy(result, "CORE");
        } else if (strcmp(filename, electiveTxt) == 0) {
            strcpy(result, "ELEC");
        } else if (strcmp(filename, clubTxt) == 0) {
            strcpy(result, "CLUB");
        } else if (strcmp(filename, competitionTxt) == 0) {
            strcpy(result, "COMP");
        } else if (strcmp(filename, workshopTxt) == 0) {
            strcpy(result, "TALK");
        }


        strcat(result, num);

        if (!is_id_exists(filename, result)) {
            char *uniqueID = strdup(result); // Allocate memory
            return uniqueID;
        }
        else{
            count++;
        }

    }
}



void defineCoreModule(){
    FILE *f, *p;
    int count = 0;
    f = fopen(coreTxt, "r");
    if (f == NULL) {
        perror("Error opening the file");
        return;
    }
    p = fopen(coreTxt, "a");
    struct Activity oldActivity, newActivity;
    printf("Enter the Intake of the module: ");
    fgets(newActivity.intakeCode, sizeof(newActivity.intakeCode), stdin);
    newActivity.intakeCode[strcspn(newActivity.intakeCode, "\n")] = '\0';

    
    while (fscanf(f, "%29[^,],%29[^,],%99[^,],%9[^,],%9[^,],%9[^,],%29[^,\n]\n",
            oldActivity.code,oldActivity.intakeCode, oldActivity.name, oldActivity.day,
            oldActivity.startTime, oldActivity.endTime, oldActivity.venue) == 7) {
                // Check if the comparison works
                if (strcmp(oldActivity.intakeCode, newActivity.intakeCode) == 0) {
                    count += 1;
                }
            }


    fclose(f);
    switch (count)
    {
    case 0:
        printf("This intake Code still have 4 core module to be added\n");
        break;
    case 1:
        printf("This intake Code still have 3 core module to be added\n");
        break;
    case 2:
        printf("This intake Code still have 2 core module to be added\n");
        break;
    case 3:
        printf("This intake Code still have 1 core module to be added\n");
        break;
    case 4:
        printf("This intake Code is unable to add Core module,Pls reinput.\n");
        break;
    default:
        break;
    }
    
    strcpy(newActivity.code,generateUniqueID(coreTxt));

    printf("Enter activity name: ");
    fgets(newActivity.name, sizeof(newActivity.name), stdin);
    newActivity.name[strcspn(newActivity.name, "\n")] = '\0';
    do{
    printf("Enter the day (e.g., Mon, Tues): ");
    fgets(newActivity.day, sizeof(newActivity.day), stdin);
    newActivity.day[strcspn(newActivity.day, "\n")] = '\0';
    for (int i = 0; newActivity.day[i]; i++) {
        newActivity.day[i] = toupper(newActivity.day[i]);
    }
    while (is_valid_day(newActivity.day)==0){
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.day, sizeof(newActivity.day), stdin);
        newActivity.day[strcspn(newActivity.day, "\n")] = '\0';
        for (int i = 0; newActivity.day[i]; i++) {
        newActivity.day[i] = toupper(newActivity.day[i]);
    }
    }

    printf("Enter the start time in 24-hour format for the activity (e.g., 12:00): ");
    fgets(newActivity.startTime, sizeof(newActivity.startTime), stdin);
    newActivity.startTime[strcspn(newActivity.startTime, "\n")] = '\0';

    while (!isValidTimeFormat(newActivity.startTime)) {
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.startTime, sizeof(newActivity.startTime), stdin);
        newActivity.startTime[strcspn(newActivity.startTime, "\n")] = '\0';
    }
    printf("Enter the end time in 24 hours for the activity (e.g., 12:00): ");
    fgets(newActivity.endTime, sizeof(newActivity.endTime), stdin);
    newActivity.endTime[strcspn(newActivity.endTime, "\n")] = '\0';
    while (!isValidTimeFormat(newActivity.endTime)|| !isEndTimeGreaterThanStartTime(newActivity.startTime,newActivity.endTime)){
        printf("Ur input in unvalid,Please type again");
        fgets(newActivity.endTime, sizeof(newActivity.endTime), stdin);
        newActivity.endTime[strcspn(newActivity.endTime, "\n")] = '\0';
    }
    }while(validate(newActivity.intakeCode,newActivity.day,newActivity.startTime,newActivity.endTime)==0);

    printf("Enter the venue for the activity: ");
    fgets(newActivity.venue, sizeof(newActivity.venue), stdin);
    newActivity.venue[strcspn(newActivity.venue, "\n")] = '\0';

    fprintf(p, "%s,%s,%s,%s,%s,%s,%s\n", newActivity.code, newActivity.intakeCode, newActivity.name, newActivity.day,
    newActivity.startTime, newActivity.endTime, newActivity.venue);
    printf("Activity added successfully.\n");
    fclose(p);
}

void addElective(){
    FILE *f; 
    f = fopen(electiveTxt, "a+");
    struct Activity newActivity;
    strcpy(newActivity.code,generateUniqueID(electiveTxt));

    printf("Enter activity name: ");
    fgets(newActivity.name, sizeof(newActivity.name), stdin);
    newActivity.name[strcspn(newActivity.name, "\n")] = '\0';

    printf("Enter the intake code: ");
    fgets(newActivity.intakeCode, sizeof(newActivity.intakeCode), stdin);
    newActivity.intakeCode[strcspn(newActivity.intakeCode, "\n")] = '\0';

    do{
    printf("Enter the day (e.g., Mon, Tues): ");
    fgets(newActivity.day, sizeof(newActivity.day), stdin);
    newActivity.day[strcspn(newActivity.day, "\n")] = '\0';
    for (int i = 0; newActivity.day[i]; i++) {
        newActivity.day[i] = toupper(newActivity.day[i]);
    }
    while (is_valid_day(newActivity.day)==0){
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.day, sizeof(newActivity.day), stdin);
        newActivity.day[strcspn(newActivity.day, "\n")] = '\0';
        for (int i = 0; newActivity.day[i]; i++) {
        newActivity.day[i] = toupper(newActivity.day[i]);
    }
    }

    printf("Enter the start time in 24-hour format for the activity (e.g., 12:00): ");
    fgets(newActivity.startTime, sizeof(newActivity.startTime), stdin);
    newActivity.startTime[strcspn(newActivity.startTime, "\n")] = '\0';

    while (!isValidTimeFormat(newActivity.startTime)) {
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.startTime, sizeof(newActivity.startTime), stdin);
        newActivity.startTime[strcspn(newActivity.startTime, "\n")] = '\0';
    }
    printf("Enter the end time in 24 hours for the activity (e.g., 12:00): ");
    fgets(newActivity.endTime, sizeof(newActivity.endTime), stdin);
    newActivity.endTime[strcspn(newActivity.endTime, "\n")] = '\0';
    while (!isValidTimeFormat(newActivity.endTime)|| !isEndTimeGreaterThanStartTime(newActivity.startTime,newActivity.endTime)){
        printf("Ur input in unvalid,Please type again");
        fgets(newActivity.endTime, sizeof(newActivity.endTime), stdin);
        newActivity.endTime[strcspn(newActivity.endTime, "\n")] = '\0';
    }
    }while(validate(newActivity.intakeCode,newActivity.day,newActivity.startTime,newActivity.endTime)==0);

    printf("Enter the venue for the activity: ");
    fgets(newActivity.venue, sizeof(newActivity.venue), stdin);
    newActivity.venue[strcspn(newActivity.venue, "\n")] = '\0';

    printf("Enter activity credits: ");
    scanf("%f", &newActivity.credits);

    fprintf(f, "%s,%s,%s,%s,%s,%s,%s,%.1f\n", newActivity.code,newActivity.intakeCode, newActivity.name, newActivity.day,
    newActivity.startTime, newActivity.endTime, newActivity.venue, newActivity.credits);
    printf("Activity added successfully.\n");
    fclose(f);

}

void addClub(){
    FILE *f;
    f = fopen(clubTxt, "a+");
    struct Activity newActivity,oldActivity;
    int found=0;
    strcpy(newActivity.code,generateUniqueID(clubTxt));
    printf("Enter activity name: ");
    fgets(newActivity.name, sizeof(newActivity.name), stdin);
    newActivity.name[strcspn(newActivity.name, "\n")] = '\0';
    while (fscanf(f, "%29[^,],%29[^,\n]\n", oldActivity.code,oldActivity.name) == 2) {
        if (strcmp(oldActivity.name, newActivity.name) == 0) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        printf("Activity with name %s already exists.\n", newActivity.name);
        return;
    }
    else{
    fprintf(f, "%s,%s\n", newActivity.code, newActivity.name);
    printf("Activity added successfully.");
    }
    fclose(f);
}

void addTalk(){
    FILE *f;
    f = fopen(workshopTxt, "a+");
    struct Activity newActivity;
    strcpy(newActivity.code,generateUniqueID(workshopTxt));
    printf("Enter activity name: ");
    fgets(newActivity.name, sizeof(newActivity.name), stdin);
    newActivity.name[strcspn(newActivity.name, "\n")] = '\0';
    printf("Enter the date (e.g., 2023-01-01): ");
    fgets(newActivity.date, sizeof(newActivity.date), stdin);
    newActivity.date[strcspn(newActivity.date, "\n")] = '\0';
    while (is_valid_date(newActivity.date)==0){
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.date, sizeof(newActivity.date), stdin);
        newActivity.date[strcspn(newActivity.date, "\n")] = '\0';
    }
    printf("Enter the start time in 24-hour format for the activity (e.g., 12:00): ");
    fgets(newActivity.startTime, sizeof(newActivity.startTime), stdin);
    newActivity.startTime[strcspn(newActivity.startTime, "\n")] = '\0';

    while (!isValidTimeFormat(newActivity.startTime)) {
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.startTime, sizeof(newActivity.startTime), stdin);
        newActivity.startTime[strcspn(newActivity.startTime, "\n")] = '\0';
    }
    printf("Enter the end time in 24 hours for the activity (e.g., 12:00): ");
    fgets(newActivity.endTime, sizeof(newActivity.endTime), stdin);
    newActivity.endTime[strcspn(newActivity.endTime, "\n")] = '\0';
    while (!isValidTimeFormat(newActivity.endTime)|| !isEndTimeGreaterThanStartTime(newActivity.startTime,newActivity.endTime)){
        printf("Ur input in unvalid,Please type again");
        fgets(newActivity.endTime, sizeof(newActivity.endTime), stdin);
        newActivity.endTime[strcspn(newActivity.endTime, "\n")] = '\0';
    }

    printf("Enter the venue for the activity: ");
    fgets(newActivity.venue, sizeof(newActivity.venue), stdin);
    newActivity.venue[strcspn(newActivity.venue, "\n")] = '\0';

    fprintf(f, "%s,%s,%s,%s,%s,%s\n", newActivity.code, newActivity.name, newActivity.date,
                newActivity.startTime, newActivity.endTime, newActivity.venue);
    printf("Activity added successfully.\n");
    fclose(f);
}

void addCompetition(){
    FILE *f;
    f = fopen(competitionTxt, "a+");
    struct Activity newActivity;
    strcpy(newActivity.code,generateUniqueID(competitionTxt));
    printf("Enter activity name: ");
    fgets(newActivity.name, sizeof(newActivity.name), stdin);
    newActivity.name[strcspn(newActivity.name, "\n")] = '\0';

    printf("Enter the date (e.g., 2023-01-01): ");
    fgets(newActivity.date, sizeof(newActivity.date), stdin);
    newActivity.date[strcspn(newActivity.date, "\n")] = '\0';
    while (is_valid_date(newActivity.date)==0){
        printf("Your input is invalid. Please type again: ");
        fgets(newActivity.date, sizeof(newActivity.date), stdin);
        newActivity.date[strcspn(newActivity.date, "\n")] = '\0';
    }
    printf("Enter the venue for the activity: ");
    fgets(newActivity.venue, sizeof(newActivity.venue), stdin);
    newActivity.venue[strcspn(newActivity.venue, "\n")] = '\0';

    fprintf(f, "%s,%s,%s,%s\n", newActivity.code, newActivity.name, newActivity.date,
                newActivity.venue);
    printf("Activity added successfully.\n");
    fclose(f);

}


void updateCoreModule(){
    FILE* file = fopen(coreTxt, "r+");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    struct Activity updatedActivity;
    char activityCode[30];
    char intakeCode[30];
    printf("Enter the code of the activity to update: ");
    scanf("%s", &activityCode);

    int found = 0;

    // Create a temporary file to store updated data
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }
    while (fscanf(file, "%29[^,],%29[^,],%99[^,],%9[^,],%9[^,],%9[^,],%29[^,\n]\n",
            updatedActivity.code,updatedActivity.intakeCode, updatedActivity.name, updatedActivity.day,
            updatedActivity.startTime, updatedActivity.endTime, updatedActivity.venue) == 7) {

        if (strcmp(updatedActivity.code, activityCode) == 0) {
            // Activity found, allow updates
            found = 1;

            printf("Update activity details:\n");
            printf("1. Activity name\n");
            printf("2. Day\n");
            printf("3. Start time\n");
            printf("4. End time\n");
            printf("5. Venue\n");
            printf("6. Exit\n");


            int choice;
            do {
                printf("Enter your choice: ");
                scanf("%d", &choice);
                clearbuffer();

                switch (choice) {
                    case 1:
                        printf("Enter updated activity name: ");
                        fgets(updatedActivity.name, sizeof(updatedActivity.name), stdin);
                        updatedActivity.name[strcspn(updatedActivity.name, "\n")] = '\0';
                        break;
                    case 2:
                        printf("Enter updated day: ");
                        fgets(updatedActivity.day, sizeof(updatedActivity.day), stdin);
                        updatedActivity.day[strcspn(updatedActivity.day, "\n")] = '\0';
                        for (int i = 0; updatedActivity.day[i]; i++) {
                            updatedActivity.day[i] = toupper(updatedActivity.day[i]);
                        }
                        while (!is_valid_day(updatedActivity.day)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.day, sizeof(updatedActivity.day), stdin);
                            updatedActivity.day[strcspn(updatedActivity.day, "\n")] = '\0';
                            for (int i = 0; updatedActivity.day[i]; i++) {
                                updatedActivity.day[i] = toupper(updatedActivity.day[i]);
                        }
                        }
                        break;
                    case 3:
                        printf("Enter updated start time: ");
                        fgets(updatedActivity.startTime, sizeof(updatedActivity.startTime), stdin);
                        updatedActivity.startTime[strcspn(updatedActivity.startTime, "\n")] = '\0';
                        while (!isValidTimeFormat(updatedActivity.startTime)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.startTime, sizeof(updatedActivity.startTime), stdin);
                            updatedActivity.startTime[strcspn(updatedActivity.startTime, "\n")] = '\0';
                        }
                        break;
                    case 4:
                        printf("Enter updated end time: ");
                        fgets(updatedActivity.endTime, sizeof(updatedActivity.endTime), stdin);
                        updatedActivity.endTime[strcspn(updatedActivity.endTime, "\n")] = '\0';
                        while (!isValidTimeFormat(updatedActivity.endTime) || !isEndTimeGreaterThanStartTime(updatedActivity.startTime, updatedActivity.endTime)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.endTime, sizeof(updatedActivity.endTime), stdin);
                            updatedActivity.endTime[strcspn(updatedActivity.endTime, "\n")] = '\0';
                        }
                        break;
                    case 5:
                        printf("Enter updated venue: ");
                        fgets(updatedActivity.venue, sizeof(updatedActivity.venue), stdin);
                        updatedActivity.venue[strcspn(updatedActivity.venue, "\n")] = '\0';
                        break;
                    case 6:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
                
                }while (choice != 6&&validate(updatedActivity.intakeCode,updatedActivity.day,updatedActivity.startTime,updatedActivity.endTime)==0);

// Write the updated activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s\n",
                    updatedActivity.code,updatedActivity.intakeCode, updatedActivity.name, updatedActivity.day,
                    updatedActivity.startTime, updatedActivity.endTime, updatedActivity.venue);
            printf("Activity updated successfully.\n");

        } else {
            // Write the unchanged activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s\n",
                    updatedActivity.code,updatedActivity.intakeCode, updatedActivity.name, updatedActivity.day,
                    updatedActivity.startTime, updatedActivity.endTime, updatedActivity.venue);       
            }
        }
    

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(coreTxt);
    rename("temp.txt", coreTxt);

    if (!found) {
        printf("Activity with code %s not found.\n", activityCode);
    }
}

void updateElective() {
    FILE* file = fopen(electiveTxt, "r+");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    struct Activity updatedActivity;
    char activityCode[30];
    printf("Enter the code of the activity to update: ");
    scanf("%29s", activityCode);

    int found = 0;

    // Create a temporary file to store updated data
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating a temporary file");
        fclose(file);
        return;
    }

    while (fscanf(file, "%29[^,],%29[^,],%99[^,],%9[^,],%9[^,],%9[^,],%29[^,],%f\n",
                  updatedActivity.code, updatedActivity.intakeCode, updatedActivity.name, updatedActivity.day,
                  updatedActivity.startTime, updatedActivity.endTime, updatedActivity.venue,
                  &updatedActivity.credits) == 8) {

        if (strcmp(updatedActivity.code, activityCode) == 0) {
            // Activity found, allow updates
            found = 1;

            printf("Update activity details:\n");
            printf("1. Intake Code\n");
            printf("2. Activity name\n");
            printf("3. Day\n");
            printf("4. Start time\n");
            printf("5. End time\n");
            printf("6. Venue\n");
            printf("7. Credit\n");
            printf("8. Exit\n");

            int choice;
            do {
                printf("Enter your choice: ");
                scanf("%d", &choice);
                clearbuffer();

                switch (choice) {
                    case 1:
                        printf("Enter updated intake code: ");
                        fgets(updatedActivity.intakeCode, sizeof(updatedActivity.intakeCode), stdin);
                        updatedActivity.intakeCode[strcspn(updatedActivity.intakeCode, "\n")] = '\0';
                        break;
                    case 2:
                        printf("Enter updated activity name: ");
                        fgets(updatedActivity.name, sizeof(updatedActivity.name), stdin);
                        updatedActivity.name[strcspn(updatedActivity.name, "\n")] = '\0';
                        break;
                    case 3:
                        printf("Enter updated day: ");
                        fgets(updatedActivity.day, sizeof(updatedActivity.day), stdin);
                        updatedActivity.day[strcspn(updatedActivity.day, "\n")] = '\0';
                        for (int i = 0; updatedActivity.day[i]; i++) {
                            updatedActivity.day[i] = toupper(updatedActivity.day[i]);
                        }
                        while (!is_valid_day(updatedActivity.day)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.day, sizeof(updatedActivity.day), stdin);
                            updatedActivity.day[strcspn(updatedActivity.day, "\n")] = '\0';
                            for (int i = 0; updatedActivity.day[i]; i++) {
                                updatedActivity.day[i] = toupper(updatedActivity.day[i]);
                        }
                        }
                        break;
                    case 4:
                        printf("Enter updated start time: ");
                        fgets(updatedActivity.startTime, sizeof(updatedActivity.startTime), stdin);
                        updatedActivity.startTime[strcspn(updatedActivity.startTime, "\n")] = '\0';
                        while (!isValidTimeFormat(updatedActivity.startTime)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.startTime, sizeof(updatedActivity.startTime), stdin);
                            updatedActivity.startTime[strcspn(updatedActivity.startTime, "\n")] = '\0';
                        }
                        break;
                    case 5:
                        printf("Enter updated end time: ");
                        fgets(updatedActivity.endTime, sizeof(updatedActivity.endTime), stdin);
                        updatedActivity.endTime[strcspn(updatedActivity.endTime, "\n")] = '\0';
                        while (!isValidTimeFormat(updatedActivity.endTime) || !isEndTimeGreaterThanStartTime(updatedActivity.startTime, updatedActivity.endTime)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.endTime, sizeof(updatedActivity.endTime), stdin);
                            updatedActivity.endTime[strcspn(updatedActivity.endTime, "\n")] = '\0';
                        }
                        break;
                    case 6:
                        printf("Enter updated venue: ");
                        fgets(updatedActivity.venue, sizeof(updatedActivity.venue), stdin);
                        updatedActivity.venue[strcspn(updatedActivity.venue, "\n")] = '\0';
                        break;
                    case 7:
                        printf("Enter the updated credit: ");
                        scanf("%f", &updatedActivity.credits);
                        break;
                    case 8:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
            } while (choice != 8&&validate(updatedActivity.intakeCode,updatedActivity.day,updatedActivity.startTime,updatedActivity.endTime)==0);

            // Write the updated activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%.1f\n",
                    updatedActivity.code, updatedActivity.intakeCode, updatedActivity.name, updatedActivity.day,
                    updatedActivity.startTime, updatedActivity.endTime, updatedActivity.venue,
                    updatedActivity.credits);
            printf("Activity updated successfully.\n");
        } else {
            // Write the unchanged activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%.1f\n",
                    updatedActivity.code, updatedActivity.intakeCode, updatedActivity.name, updatedActivity.day,
                    updatedActivity.startTime, updatedActivity.endTime, updatedActivity.venue,
                    updatedActivity.credits);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(electiveTxt);
    rename("temp.txt", electiveTxt);

    if (!found) {
        printf("Activity with code %s not found.\n", activityCode);
    }
}


void updatedTalk(){
    FILE* file = fopen(workshopTxt, "r+");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    struct Activity updatedActivity;
    char activityCode[30];
    printf("Enter the code of the activity to update: ");
    scanf("%s", activityCode);

    int found = 0;
 
    // Create a temporary file to store updated data
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (fscanf(file, "%29[^,],%99[^,],%19[^,],%9[^,],%9[^,],%29[^,\n]\n",
                updatedActivity.code, updatedActivity.name, updatedActivity.date,
                updatedActivity.startTime,updatedActivity.endTime,updatedActivity.venue) == 6) {

        if (strcmp(updatedActivity.code, activityCode) == 0) {
            // Activity found, allow updates
            found = 1;

            printf("Update activity details:\n");
            printf("1. Activity name\n");
            printf("2. Date\n");
            printf("3. Start time\n");
            printf("4. End time\n");
            printf("5. Venue\n");
            printf("6. Exit\n");

            int choice;
            do {
                printf("Enter your choice: ");
                scanf("%d", &choice);
                clearbuffer();

                switch (choice) {
                    case 1:
                        printf("Enter updated activity name: ");
                        fgets(updatedActivity.name, sizeof(updatedActivity.name), stdin);
                        updatedActivity.name[strcspn(updatedActivity.name, "\n")] = '\0';
                        break;
                    case 2:
                        printf("Enter updated date: ");
                        fgets(updatedActivity.date, sizeof(updatedActivity.date), stdin);
                        updatedActivity.date[strcspn(updatedActivity.date, "\n")] = '\0';
                        break;
                    case 3:
                        printf("Enter updated start time: ");
                        fgets(updatedActivity.startTime, sizeof(updatedActivity.startTime), stdin);
                        updatedActivity.startTime[strcspn(updatedActivity.startTime, "\n")] = '\0';
                        while (!isValidTimeFormat(updatedActivity.startTime)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.startTime, sizeof(updatedActivity.startTime), stdin);
                            updatedActivity.startTime[strcspn(updatedActivity.startTime, "\n")] = '\0';
                        }
                        break;
                    case 4:
                        printf("Enter updated end time: ");
                        fgets(updatedActivity.endTime, sizeof(updatedActivity.endTime), stdin);
                        updatedActivity.endTime[strcspn(updatedActivity.endTime, "\n")] = '\0';
                        while (!isValidTimeFormat(updatedActivity.endTime) || !isEndTimeGreaterThanStartTime(updatedActivity.startTime, updatedActivity.endTime)) {
                            printf("Your input is invalid. Please type again: ");
                            fgets(updatedActivity.endTime, sizeof(updatedActivity.endTime), stdin);
                            updatedActivity.endTime[strcspn(updatedActivity.endTime, "\n")] = '\0';
                        }
                        break;
                    case 5:
                        printf("Enter updated venue: ");
                        fgets(updatedActivity.venue, sizeof(updatedActivity.venue), stdin);
                        updatedActivity.venue[strcspn(updatedActivity.venue, "\n")] = '\0';
                        break;
                    case 6:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 6);

            // Write the updated activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s\n", updatedActivity.code, updatedActivity.name, updatedActivity.date,updatedActivity.startTime,updatedActivity.endTime,updatedActivity.venue);
        } else {
            // Activity not found, write the original activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s\n", updatedActivity.code, updatedActivity.name, updatedActivity.date, updatedActivity.startTime,updatedActivity.endTime,updatedActivity.venue);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(workshopTxt);
    rename("temp.txt", workshopTxt);

    if (!found) {
        printf("Activity with code %s not found.\n", activityCode);
    }
}



void updateCompetition() {
    FILE* file = fopen(competitionTxt, "r+");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    struct Activity updatedActivity;
    char activityCode[30];
    printf("Enter the code of the activity to update: ");
    scanf("%s", activityCode);

    int found = 0;
 
    // Create a temporary file to store updated data
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (fscanf(file, "%29[^,],%99[^,],%19[^,],%29[^,\n]\n",
                updatedActivity.code, updatedActivity.name, updatedActivity.date,
                 updatedActivity.venue) == 4) {

        if (strcmp(updatedActivity.code, activityCode) == 0) {
            // Activity found, allow updates
            found = 1;

            printf("Update activity details:\n");
            printf("1. Activity name\n");
            printf("2. Date\n");
            printf("3. Venue\n");
            printf("4. Exit\n");
            int choice;
            do {
                printf("Enter your choice: ");
                scanf("%d", &choice);
                clearbuffer();

                switch (choice) {
                    case 1:
                        printf("Enter updated activity name: ");
                        fgets(updatedActivity.name, sizeof(updatedActivity.name), stdin);
                        updatedActivity.name[strcspn(updatedActivity.name, "\n")] = '\0';
                        break;
                    case 2:
                        printf("Enter updated date: ");
                        fgets(updatedActivity.date, sizeof(updatedActivity.date), stdin);
                        updatedActivity.date[strcspn(updatedActivity.date, "\n")] = '\0';
                        break;
                    case 3:
                        printf("Enter updated venue: ");
                        fgets(updatedActivity.venue, sizeof(updatedActivity.venue), stdin);
                        updatedActivity.venue[strcspn(updatedActivity.venue, "\n")] = '\0';
                        break;
                    case 4:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 4);

            // Write the updated activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s\n", updatedActivity.code, updatedActivity.name, updatedActivity.date, updatedActivity.venue);
        } else {
            // Activity not found, write the original activity to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s\n", updatedActivity.code, updatedActivity.name, updatedActivity.date, updatedActivity.venue);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(competitionTxt);
    rename("temp.txt", competitionTxt);

    if (!found) {
        printf("Activity with code %s not found.\n", activityCode);
    }
}                           

void updateClub() {
    FILE* file = fopen(clubTxt, "r+");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    struct Activity updatedActivity;
    char activityCode[30];
    printf("Enter the code of the activity to update: ");
    scanf("%s", activityCode);

    int found = 0;
 
    // Create a temporary file to store updated data
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (fscanf(file, "%29[^,],%29[^,]", updatedActivity.code,updatedActivity.name) == 2){
        if (strcmp(updatedActivity.code, activityCode) == 0) {
            // Activity found, allow updates
            found = 1;

            printf("Update activity details:\n");
            printf("1. Activity name\n");   
            printf("2. Exit\n");


            int choice;
            do {
                printf("Enter your choice: ");
                scanf("%d", &choice);
                clearbuffer();

                switch (choice) {
                    case 1:
                        printf("Enter updated activity name: ");
                        fgets(updatedActivity.name, sizeof(updatedActivity.name), stdin);
                        updatedActivity.name[strcspn(updatedActivity.name, "\n")] = '\0';
                        break;
                    case 2:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 2);

            // Write the updated activity to the temporary file
            fprintf(tempFile, "%s,%s\n", updatedActivity.code, updatedActivity.name);
        } else {
            // Activity not found, write the original activity to the temporary file
            fprintf(tempFile, "%s,%s\n", updatedActivity.code, updatedActivity.name);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Delete the original file
    remove(clubTxt);
    rename("temp.txt", clubTxt);

    if (found) {
        printf("Activity updated successfully.\n");
    } else {
        printf("Activity not found.\n");
    }
}

// Function to delete an activity by ID
void deleteActivity(const char *filename, const char *idToDelete) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[1000];
    int deleted = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char temp[1000];
        strcpy(temp, line);  // Create a copy of the line

        // Tokenize the line to get the ID
        char *token = strtok(temp, ",");
        if (token == NULL) {
            continue; // Skip empty lines
        }

        // Check if the ID in the line matches the one to delete
        if (strcmp(token, idToDelete) == 0) {
            deleted = 1;
        } else {
            // Write the line to the temporary file with a newline
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Close the original file and replace it with the temporary file
    remove(filename);
    rename("temp.txt", filename);

    if (deleted) {
        printf("Activity with ID %s deleted.\n", idToDelete);
    } else {
        printf("Activity with ID %s not found.\n", idToDelete);
    }
}

enum Day {
    MON, TUE, WED, THU, FRI, SAT, SUN
};

// Function to compare activities for sorting
int compareActivities(const void *a, const void *b) {
    struct Activity *activityA = (struct Activity *)a;
    struct Activity *activityB = (struct Activity *)b;

    // Compare day
    enum Day dayA, dayB;
    if (strcmp(activityA->day, "MON") == 0) {
        dayA = MON;
    } else if (strcmp(activityA->day, "TUE") == 0) {
        dayA = TUE;
    } else if (strcmp(activityA->day, "WED") == 0) {
        dayA = WED;
    } else if (strcmp(activityA->day, "THU") == 0) {
        dayA = THU;
    } else if (strcmp(activityA->day, "FRI") == 0) {
        dayA = FRI;
    } else if (strcmp(activityA->day, "SAT") == 0) {
        dayA = SAT;
    } else if (strcmp(activityA->day, "SUN") == 0) {
        dayA = SUN;
    }

    if (strcmp(activityB->day, "MON") == 0) {
        dayB = MON;
    } else if (strcmp(activityB->day, "TUE") == 0) {
        dayB = TUE;
    } else if (strcmp(activityB->day, "WED") == 0) {
        dayB = WED;
    } else if (strcmp(activityB->day, "THU") == 0) {
        dayB = THU;
    } else if (strcmp(activityB->day, "FRI") == 0) {
        dayB = FRI;
    } else if (strcmp(activityB->day, "SAT") == 0) {
        dayB = SAT;
    } else if (strcmp(activityB->day, "SUN") == 0) {
        dayB = SUN;
    }

    if (dayA < dayB) {
        return -1;
    } else if (dayA > dayB) {
        return 1;
    }

    // Compare start time
    int startTimeA = atoi(activityA->startTime);
    int startTimeB = atoi(activityB->startTime);
    if (startTimeA < startTimeB) {
        return -1;
    } else if (startTimeA > startTimeB) {
        return 1;
    }

    // Compare end time
    int endTimeA = atoi(activityA->endTime);
    int endTimeB = atoi(activityB->endTime);
    if (endTimeA < endTimeB) {
        return -1;
    } else if (endTimeA > endTimeB) {
        return 1;
    }

    return 0;

}

void timetable() {
    // Open the file for reading
    FILE *file = fopen(coreTxt, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read activities from the file
    struct Activity activities[100];  // Adjust the size based on your needs
    int activityCount = 0;

    while (fscanf(file, "%19[^,],%19[^,],%49[^,],%3[^,],%9[^,],%9[^,],%19[^\n]\n",
                  activities[activityCount].code,
                  activities[activityCount].intakeCode,
                  activities[activityCount].name,
                  activities[activityCount].day,
                  activities[activityCount].startTime,
                  activities[activityCount].endTime,
                  activities[activityCount].venue) == 7) {
        activityCount++;
    }

    FILE *electiveFile = fopen(electiveTxt, "r");
    if (electiveFile == NULL) {
        perror("Error opening file");
        return;
    }

    while(fscanf(electiveFile, "%19[^,],%19[^,],%49[^,],%3[^,],%9[^,],%9[^,],%19[^,],%f\n",
                  activities[activityCount].code,
                  activities[activityCount].intakeCode,
                  activities[activityCount].name,
                  activities[activityCount].day,
                  activities[activityCount].startTime,
                  activities[activityCount].endTime,
                  activities[activityCount].venue,
                  &activities[activityCount].credits) == 8) {
        activityCount++;
    }

    // Close the file
    fclose(file);

    // Sort activities
    qsort(activities, activityCount, sizeof(struct Activity), compareActivities);

    // Get user input for the intake code
    char searchIntakeCode[20];
    printf("Enter the intake code to search: ");
    scanf("%19s", searchIntakeCode);

    // Print the activities for the specified intake code
    printf("\nActivities for Intake Code %s:\n", searchIntakeCode);
    printf("Day\tTime\t\tCode\t\tName\t\t\tVenue\n");
    for (int i = 0; i < activityCount; i++) {
        if (strcmp(activities[i].intakeCode, searchIntakeCode) == 0) {
            printf("%s\t%s-%s\t%s\t%s\t%s\n",activities[i].day,activities[i].startTime, activities[i].endTime,
                   activities[i].code, activities[i].name, activities[i].venue);
        }
    }
}


void programCoodinatorMain() {
    int choice;
    int funtionchoice;
    char idToDelete[30];
    int cont=1;
    do{
    printf("Menu\n");
    printf("1. Add activity\n");
    printf("2. Update activity\n");
    printf("3. Delete activity\n");
    printf("4. View timetable\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        do{
        printf("Select type of activity:\n");
        printf("1.Elective/Specialise module\n");
        printf("2.Talks/Workshop\n");
        printf("3.Clubs/Societies\n");
        printf("4.Competitions\n");
        printf("5.Core Module\n");
        scanf(" %d", &funtionchoice);
        switch(funtionchoice){
            case 1:
                    clearbuffer();
                    addElective();
                break;
            case 2:
                    clearbuffer();
                    addTalk();
                break;
            case 3:
                    clearbuffer();
                    addClub();
                break;
            case 4:
                    clearbuffer();
                    addCompetition();
                break;
            case 5:
                    clearbuffer();
                    defineCoreModule();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("Do you want to continue to add Activity? (1 for yes, 0 for no): ");
        scanf("%d",&cont);
        }while(cont==1);
        break;
    case 2:
        do{
        printf("Select the file to update activities:\n");
        printf("1. Elective/Specialise module\n");
        printf("2. Talks/Workshop\n");
        printf("3. Clubs/Societies\n");
        printf("4. Competitions\n");
        printf("5. Core Module\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            clearbuffer();
            updateElective();
            break;
        case 2:
            clearbuffer();
            updatedTalk();
            break;
        case 3:
            clearbuffer();
            updateClub();
            break;
        case 4:
            clearbuffer();
            updateCompetition();
            break;
        case 5:
            clearbuffer();
            updateCoreModule();
            break;
        
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printf("Do you want to continue to update activity? (1 for yes, 0 for no): ");
        scanf("%d",&cont);
        }while(cont==1);
        break;
    case 3:
        do{
        printf("Select the file to delete activities:\n");
        printf("1. Elective/Specialise module\n");
        printf("2. Talks/Workshop\n");
        printf("3. Clubs/Societies\n");
        printf("4. Competitions\n");
        printf("5.Core Module\n");
        scanf("%d", &choice);
        switch (choice) {
        
        case 1:
            printf("Enter the ID of the activity to delete: ");
            scanf("%s", idToDelete);
            deleteActivity(electiveTxt, idToDelete);
            break;
        case 2:
            printf("Enter the ID of the activity to delete: ");
            scanf("%s", idToDelete);
            deleteActivity(workshopTxt, idToDelete);
            break;
        case 3:
            printf("Enter the ID of the activity to delete: ");
            scanf("%s", idToDelete);
            deleteActivity(clubTxt, idToDelete);
            break;
        case 4:
            printf("Enter the ID of the activity to delete: ");
            scanf("%s", idToDelete);
            deleteActivity(competitionTxt, idToDelete);
            break;
        case 5:
            printf("Enter the ID of the activity to delete: ");
            scanf("%s", idToDelete);
            deleteActivity(coreTxt, idToDelete);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printf("Do you want to continue to delete activity? (1 for yes, 0 for no): ");
        scanf("%d",&cont);
        }while(cont==1);
        break;
    case 4:
        do{
        timetable();
        printf("Do you want to continue to view timetable? (1 for yes, 0 for no): ");
        scanf("%d",&cont);
        }while(cont==1);
        break;
    case 5:
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        break;
    }
    printf("Do you want to continue to other function? (1 for yes, 0 for no): ");
    scanf("%d",&cont);
    }while(cont==1);
    if (cont==0){
        printf("Thank you for using this program");
    }
}

// int main(){
//     programCoodinatorMain();
//     return 0;
// }