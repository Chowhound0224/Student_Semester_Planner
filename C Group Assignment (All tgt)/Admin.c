#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "Student.c"
#include "ProgramLeader.c"
#include "ProgramCoordinator.c"

struct User {
    char ID[50];
    char name[50];
    int age;
    char DOB[12];
    char identificationNumber[20];
    char address[100];
    char gender;
    char phoneNumber[20];
    char email[50];
    char race[20];
    char nationality[50];
    char password[50];
    char reconfirmedPassword[50];
    char accountstatus[50];
};

struct AccountStatus {
    char name[50];
    char accountstatus[10];
};

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int compare(char *str1, const char *str2) {
    // Trim leading spaces
    while (*str1 == ' ') {
        str1++;
    }

    // Trim trailing spaces
    int len = strlen(str1);
    while (len > 0 && str1[len - 1] == ' ') {
        len--;
    }

    // Null-terminate the trimmed string
    str1[len] = '\0';

    // Compare the trimmed string with the provided ID
    return strcmp(str1, str2);
}

char *generateID(int role, const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    int count = 1;
    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL) {
        count += 1;
    }
    fclose(file);

    char num[6]; // Assuming a maximum of 5 digits plus a null-terminator
    sprintf(num, "%05d", count); // Format the integer

    char *result = (char *)malloc(10); // Allocate memory for the result (assuming a maximum of 9 characters)
    
    if (result == NULL) {
        // Handle memory allocation error
        return NULL;
    }

    switch (role){
        case 1:
            strcpy(result, "STUD");
            break;
        case 2:
            strcpy(result, "COOR");
            break;
        case 3:
            strcpy(result, "LEAD");
            break;
        case 4:
            strcpy(result, "ADMIN");
            break;
        default:
            free(result); // Free the allocated memory in case of an invalid role
            printf("\033[1;31m");
            printf("error!\n");
            printf("\033[0m");
            printf("Invalid choice. Your registration has failed.\n");
            return NULL;
    }

    strcat(result, num); // Concatenate the string and formatted integer
    return result;
}

//Function use to validate the DOB
int check_leap_year(int year) {
    if (year % 4 == 0 && year % 100 != 0){
        return 1;
    } else if (year % 400 == 0){
        return 1;
    } else {
        return 0;
    }
}

int DOBValidation(const char *date) {
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) == 3) {
        if (year >= 1923 && year <= 2123 && month >= 1 && month <= 12) {
            int max_days_in_month;
            if (month == 2) {
                if (check_leap_year(year)) {
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

//Function use to validate the numbers
int numbersValidation(const char *num){
    for (int i = 0; num[i] != '\0' ; i++) {
        if (num[i] < '0' || num[i] > '9') {
            return 0;
        }
    }
    return 1; //all characters are numbers
}

//Function use to validate the age
int ageValidation(const int age) {
    while (age < 15 || age > 100) {
        printf("\033[1;31m");
        printf("error!\n");
        printf("\033[0m");
        printf("Invalid age range for university. Please enter a valid age range.\n");
        printf("Please enter your age: ");
        scanf("%d", &age);
    } // while (user->age < 0 || user->age > 100
    return age;
}
//Function use to validate the gender
char genderValidation(char gender){
    while ((gender != 'M' && gender != 'm') && (gender != 'F' && gender != 'f')) {
        printf("\033[1;31m");
        printf("error!\n");
        printf("\033[0m");
        printf("Please enter valid gender (M/F).");
        scanf(" %c", &gender);
    }
    return gender;
}

void passwordValidation(char *password, char *reconfirmedPassword){
    while (strcmp(password,reconfirmedPassword) != 0) {
        printf("\033[1;31m");
        printf("error!\n");
        printf("\033[0m");
        printf("Your passwords do not match. Please re-enter your password.\n");
        printf("Please enter your password: ");
        scanf("%s",password);
        clearBuffer();
        printf("Please re-enter your password to confirm: ");
        scanf("%s", reconfirmedPassword);
        clearBuffer();
    }
}

//Function use to update the user data
void updatedInformation(const char *filename, const int role){
    
    struct User user;
    FILE *file = fopen(filename, "r+");

    if (file == NULL) {
        printf("\033[1;31m");
        printf("error\n");
        printf("\033[0m");
        printf("The file is invalid as there are no any data in it.\n");
        return ;
    }

    char id[50];
    int found = 0;
    clearBuffer();

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\033[1;31m");
        printf("error\n");
        printf("\033[0m");
        printf("The file is invalid as there are no any data in it.\n");
        fclose(file);
        return;
    }

    printf("Please enter the ID that you want to update: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0'; // Remove the newline character

    while((fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^,],%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
    user.ID,user.name,&user.age,user.DOB,user.identificationNumber,user.address,&user.gender,user.phoneNumber,
    user.email,user.race,user.nationality,user.password,user.accountstatus)) != EOF) {


            if (strcmp(user.ID, id) == 0) {
                printf("User found \n");
                found = 1;
                int updateChoice;

            switch(role){
            case 1:
                printf(" --------------------------------------\n");
                printf("|     Update Student's Information     |\n");
                printf(" --------------------------------------\n");
                printf("|      1. Name                         |\n");
                printf("|      2. Age                          |\n");
                printf("|      3. Password                     |\n");
                printf("|      4. Account status               |\n");
                printf("|      5. Exit                         |\n");
                printf(" --------------------------------------\n");
                printf("|     Choice:                          |\n");
                printf(" --------------------------------------\n");

                do{
                printf("Please enter your choice: \n");
                scanf("%d", &updateChoice);
                clearBuffer();

                if (updateChoice == 1) {
                    printf("Please enter your name: ");
                    fgets(user.name, sizeof(user.name), stdin);
                    user.name[strlen(user.name) - 1] = '\0';
                    // Convert each character to uppercase and add a space between each character
                    for (int i = 0; user.name[i] != '\0'; i++) {
                        user.name[i] = toupper(user.name[i]);
                        }
                    break;

                } else if (updateChoice == 2) {
                    printf("Please enter your age: ");
                    scanf("%2d", &user.age);
                    ageValidation(user.age);
                    clearBuffer(); // Clear the input buffer
                    break;

                } else if (updateChoice == 3) {
                    printf("Please enter your password: ");
                    scanf("%s", user.password);
                    clearBuffer();
                    printf("Please re-enter your password to confirm: ");
                    scanf("%s", user.reconfirmedPassword);
                    passwordValidation(user.password,user.reconfirmedPassword);
                    clearBuffer();
                    break;

                } else if (updateChoice == 4) {
                    printf("Please enter the account status (Active/Left/Graduated): ");
                    scanf("%s", &user.accountstatus);
                    clearBuffer();
                    break;

                } else if (updateChoice == 5) {
                    printf("Thank you for using our system.\n");
                    break;
                } else {
                    printf("\033[1;31m");
                    printf("error\n");
                    printf("\033[0m");
                    printf("Invalid choice. Please enter a valid choice.\n");
                }

                } while (updateChoice != 5);
                break;
            case 2:
                printf(" ------------------------------------------------------\n");
                printf("|       Update Program Coordinator's Information       |\n");
                printf(" ------------------------------------------------------\n");
                printf("|           1. Name                                    |\n");
                printf("|           2. Age                                     |\n");
                printf("|           3. Password                                |\n");
                printf("|           4. Account status                          |\n");
                printf("|           5. Exit                                    |\n");
                printf(" ------------------------------------------------------\n");
                printf("|             Choice:                                  |\n");
                printf(" ------------------------------------------------------\n");

                do{ 
                printf("Please enter your choice: \n");
                scanf("%d", &updateChoice);
                clearBuffer();

                if (updateChoice == 1) {
                    printf("Please enter your name: ");
                    fgets(user.name, sizeof(user.name), stdin);
                    user.name[strlen(user.name) - 1] = '\0';
                    // Convert each character to uppercase and add a space between each character
                    for (int i = 0; user.name[i] != '\0'; i++) {
                        user.name[i] = toupper(user.name[i]);
                        }
                    break;

                } else if (updateChoice == 2) {
                    printf("Please enter your age: ");
                    scanf("%2d", &user.age);
                    ageValidation(user.age);
                    clearBuffer(); // Clear the input buffer
                    break;
                } else if (updateChoice == 3) {
                    printf("Please enter your password: ");
                    scanf("%s", user.password);
                    clearBuffer();
                    printf("Please re-enter your password to confirm: ");
                    scanf("%s", user.reconfirmedPassword);
                    passwordValidation(user.password,user.reconfirmedPassword);
                    clearBuffer();
                    break;
                } else if (updateChoice == 4) {
                    printf("Please enter the account status (Active/Left/Graduated): ");
                    scanf("%s", &user.accountstatus);
                    clearBuffer();
                    break;
                } else if (updateChoice == 5) {
                    printf("Thank you for using our system.\n");
                    break;
                } else {
                    printf("\033[1;31m");
                    printf("error\n");
                    printf("\033[0m");
                    printf("Invalid choice. Please enter a valid choice.\n");
                }

                } while (updateChoice != 5);
                break;
            case 3:
                printf(" -----------------------------------------------\n");
                printf("|     Update Programme Leader's Information     |\n");
                printf(" -----------------------------------------------\n");
                printf("|         1. Name                               |\n");
                printf("|         2. Age                                |\n");
                printf("|         3. Password                           |\n");
                printf("|         4. Account status                     |\n");
                printf("|         5. Exit                               |\n");
                printf(" -----------------------------------------------\n");
                printf("|          Choice:                              |\n");
                printf(" -----------------------------------------------\n");

                do{
                printf("Please enter your choice: \n");
                scanf("%d", &updateChoice);
                clearBuffer();

                if (updateChoice == 1) {
                    printf("Please enter your name: ");
                    fgets(user.name, sizeof(user.name), stdin);
                    user.name[strlen(user.name) - 1] = '\0';
                    // Convert each character to uppercase and add a space between each character
                    for (int i = 0; user.name[i] != '\0'; i++) {
                        user.name[i] = toupper(user.name[i]);
                        }
                    break;
                } else if (updateChoice == 2) {
                    printf("Please enter your age: ");
                    scanf("%2d", &user.age);
                    ageValidation(user.age);
                    clearBuffer(); // Clear the input buffer
                    break;
                } else if (updateChoice == 3) {
                    printf("Please enter your password: ");
                    scanf("%s", user.password);
                    clearBuffer();
                    printf("Please re-enter your password to confirm: ");
                    scanf("%s", user.reconfirmedPassword);
                    passwordValidation(user.password,user.reconfirmedPassword);
                    clearBuffer();
                    break;
                } else if (updateChoice == 4) {
                    printf("Please enter the account status (Active/Left/Graduated): ");
                    scanf("%s", &user.accountstatus);
                    clearBuffer();
                    break;
                } else if (updateChoice == 5) {
                    printf("Thank you for using our system.\n");
                    break;
                } else {
                    printf("\033[1;31m");
                    printf("error\n");
                    printf("\033[0m");
                    printf("Invalid choice. Please enter a valid choice.\n");
                }

                } while (updateChoice != 4);
                break;

            case 4:
                printf(" --------------------------------------------\n");
                printf("|     Update Administrator's Information     |\n");
                printf(" --------------------------------------------\n");
                printf("|        1. Name                             |\n");
                printf("|        2. Age                              |\n");
                printf("|        3. Password                         |\n");
                printf("|        4. Account status                   |\n");
                printf("|        5. Exit                             |\n");
                printf(" --------------------------------------------\n");
                printf("|          Choice:                           |\n");
                printf(" --------------------------------------------\n");

                do{
                printf("Please enter your choice: \n");
                scanf("%d", &updateChoice);
                clearBuffer();

                if (updateChoice == 1) {
                    printf("Please enter your name: ");
                    fgets(user.name, sizeof(user.name), stdin);
                    user.name[strlen(user.name) - 1] = '\0';
                    // Convert each character to uppercase and add a space between each character
                    for (int i = 0; user.name[i] != '\0'; i++) {
                        user.name[i] = toupper(user.name[i]);
                        }
                    break;
                } 
                else if (updateChoice == 2) {
                    printf("Please enter your age: ");
                    scanf("%2d", &user.age);
                    ageValidation(user.age);
                    clearBuffer(); // Clear the input buffer
                    break;

                } else if (updateChoice == 3) {
                    printf("Please enter your password: ");
                    scanf("%s", user.password);
                    clearBuffer();
                    printf("Please re-enter your password to confirm: ");
                    scanf("%s", user.reconfirmedPassword);
                    passwordValidation(user.password,user.reconfirmedPassword);
                    clearBuffer();
                    break;

                } else if (updateChoice == 4) {
                    printf("Please enter the account status (Active/Left/Graduated): ");
                    scanf("%s", user.accountstatus);
                    clearBuffer();
                    break;

                } else if (updateChoice == 5) {
                    printf("Thank you for using our system.\n");
                    break;
                } else {
                    printf("\033[1;31m");
                    printf("error\n");
                    printf("\033[0m");
                    printf("Invalid choice. Please enter a valid choice.\n");
                }

                } while (updateChoice != 5);
                break;
            default:
                printf("Invalid choice\n");
                // Call the registration function with user and filename.
                break;
            }
                fprintf(tempFile, "%s,%s,%d,%s,%s,%s,%c,%s,%s,%s,%s,%s,%s\n",
                    user.ID,user.name,user.age,user.DOB,user.identificationNumber,user.address,
                    toupper(user.gender),user.phoneNumber,user.email,user.race,user.nationality,user.password,user.accountstatus);
                    printf("The information has been updated successfully.\n");
        } else {
                fprintf(tempFile, "%s,%s,%d,%s,%s,%s,%c,%s,%s,%s,%s,%s,%s\n",
                    user.ID,user.name,user.age,user.DOB,user.identificationNumber,user.address,
                    toupper(user.gender),user.phoneNumber,user.email,user.race,user.nationality,user.password,user.accountstatus);
            }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);

    if (!found) {
        printf("\033[1;31m");
        printf("The ID that you entered is not found.\n");
        printf("\033[0m");
    }
}


//Function use to register new users
void registerUser(struct User *user, const char *filename, const int role) {
    FILE *file = fopen(filename, "a");
    int i=0;

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    strcpy(user->ID, generateID(role, filename)); //call generateID function and copy the result to user->ID

    printf("Please enter your name: ");
    fgets(user->name, sizeof(user->name), stdin); // Read up to 49 characters plus a null terminator from stdin
    user->name[strlen(user->name) - 1] = '\0';

    // Convert each character to uppercase and add a space between each character
    for (int i = 0; user->name[i] != '\0'; i++) {
        user->name[i] = toupper(user->name[i]);
        }

    printf("Please enter your age: ");
    scanf("%2d", &user->age);
    user->age = ageValidation(user->age);
    clearBuffer(); // Clear the input buffer

    printf("Please enter your date of birth (DD-MM-YYYY): ");
    fgets(user->DOB, 12, stdin); // Read up to 11 characters plus a null terminator from stdin
    user->DOB[strcspn(user->DOB, "\n")] = '\0'; // Replace the newline character with a null terminator
    fflush(stdin);
    while (!DOBValidation(user->DOB)) {
        printf("\033[1;31m");
        printf("error\n");
        printf("\033[0m");
        printf("Invalid date format or out-of-range values. Please enter a valid date.\n");
        printf("Please enter your date of birth (DD-MM-YYYY): ");
        fgets(user->DOB, 12, stdin); // Read up to 11 characters plus a null terminator from stdin
        user->DOB[strcspn(user->DOB, "\n")] = '\0'; // Replace the newline character with a null terminator
        fflush(stdin);
    }
    
    printf("Please enter your identification number: ");
    scanf("%s", user->identificationNumber);
    numbersValidation(user->identificationNumber);
    clearBuffer();
    
    printf("Please enter your address: ");
    fgets(user->address, sizeof(user->address), stdin);
    user->address[strlen(user->address) - 1] = '\0';
    // Convert each character to uppercase and add a space between each character
    for (int i = 0; user->address[i] != '\0'; i++) {
        user->address[i] = toupper(user->address[i]);
        }
    fflush(stdin);

    printf("Please enter your gender (M/F): "); 
    scanf(" %c", &user->gender); 
    genderValidation(user->gender);
    clearBuffer(); 

    printf("Please enter your phone number: ");
    scanf("%s", user->phoneNumber);
    numbersValidation(user->phoneNumber);
    clearBuffer();

    printf("Please enter your email: ");
    scanf("%s", user->email);
    clearBuffer();

    printf("Please enter your race: ");
    scanf("%s", user->race);
    clearBuffer();

    printf("Please enter your nationality: ");
    scanf("%s", user->nationality);
    clearBuffer();

    printf("Please enter your password: ");
    scanf("%s", user->password);
    clearBuffer();

    printf("Please re-enter your password to confirm: ");
    scanf("%s", user->reconfirmedPassword);
    passwordValidation(user->password,user->reconfirmedPassword);
    clearBuffer();

    printf("Your account was registered successfully!\n");

    // Write user data to the file
    fprintf(file, "%s,%s,%d,%s,%s,%s,%c,%s,%s,%s,%s,%s,Active\n",
        user->ID,user->name,user->age,user->DOB,user->identificationNumber,user->address,
        toupper(user->gender),user->phoneNumber,user->email,user->race,user->nationality,user->password);
    fclose(file);
}

//function to login system
int login(char *name, char *password) {
    FILE *f, *g, *h, *k;
    struct User student[100], coordinator[100], leader[100], administrator[100];
    int permission = 0;
    int i = 0;

    f=fopen("student.txt","r");
    g=fopen("coordinator.txt","r");
    h=fopen("leader.txt","r");
    k=fopen("administrator.txt","r");


    while (fscanf(f,"%[^,],%[^,],%d,%[^,],%[^,],%[^,],%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                    student[i].ID,student[i].name,&student[i].age,student[i].DOB,
                    student[i].identificationNumber,student[i].address,&student[i].gender,student[i].phoneNumber,
                    student[i].email,student[i].race,student[i].nationality,student[i].password,student[i].accountstatus) != EOF){
        i++;
    }
    while (fscanf(g,"%[^,],%[^,],%d,%[^,],%[^,],%[^,],%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                    coordinator[i].ID,coordinator[i].name,&coordinator[i].age,coordinator[i].DOB,
                    coordinator[i].identificationNumber, coordinator[i].address, &coordinator[i].gender,coordinator[i].phoneNumber,
                    coordinator[i].email,coordinator[i].race,coordinator[i].nationality,coordinator[i].password,coordinator[i].accountstatus) != EOF){
        i++;
    }

    while (fscanf(h,"%[^,],%[^,],%d,%[^,],%[^,],%[^,],%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                        leader[i].ID,leader[i].name,&leader[i].age,leader[i].DOB,
                        leader[i].identificationNumber,leader[i].address,&leader[i].gender,leader[i].phoneNumber,
                        leader[i].email,leader[i].race,leader[i].nationality,leader[i].password,leader[i].accountstatus) != EOF){
            i++;
        }
    while (fscanf(k,"%[^,],%[^,],%d,%[^,],%[^,],%[^,],%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                        administrator[i].ID,administrator[i].name,&administrator[i].age,administrator[i].DOB,administrator[i].identificationNumber,administrator[i].address,
                        &administrator[i].gender,administrator[i].phoneNumber,administrator[i].email,administrator[i].race,administrator[i].nationality,administrator[i].password,administrator[i].accountstatus) != EOF){
            i++;
        }
    fclose(f);
    fclose(g);
    fclose(h);
    fclose(k);

    for (int j = 0; j < i; j++) {
        if (strcmp(name, student[j].ID) == 0 && strcmp(password, student[j].password) == 0) {
            printf("Welcome %s!\n", student[j].name);
            permission = 1;
            break;
        } else if (strcmp(name, coordinator[j].ID) == 0 && strcmp(password, coordinator[j].password) == 0) {
            printf("Welcome %s!\n", coordinator[j].name);
            permission = 2;
            break;
        } else if (strcmp(name, leader[j].ID) == 0 && strcmp(password, leader[j].password) == 0) {
            printf("Welcome %s!\n", leader[j].name);
            permission = 3;
            break;
        } else if (compare(name, administrator[j].ID) == 0 && compare(password, administrator[j].password) == 0) {
            printf("Welcome %s!\n", administrator[j].name);
            permission = 4;
            break;
        } 
    }
    if (permission !=1 && permission !=2 && permission !=3 && permission !=4)
    {
        printf("\033[1;31m");
        printf("error\n");
        printf("\033[0m");
        printf("Invalid username or password.\n");
        permission = 5;
    }
    
    return permission;
}

void forgetpassword(){
    FILE *f;
    struct User user;
    int permission = 0;
    int i = 0;
    char ID[50];
    int found = 0;
    int updateChoice;
    char filename[20];

    for(updateChoice=1;updateChoice<=4;updateChoice++)
    if(updateChoice == 1){
        strcpy(filename, "student.txt");
        f=fopen(filename,"r");
        break;
    }
    else if(updateChoice == 2){
        strcpy(filename, "coordinator.txt");
        f=fopen(filename,"r");
        break;
    }
    else if(updateChoice == 3){
        strcpy(filename, "leader.txt");
        f=fopen(filename,"r");
        break;
    }
    else if(updateChoice == 4){
        strcpy(filename, "administrator.txt");
        f=fopen(filename,"r");
        break;
    }
    else{
        printf("Invalid choice\n");
        break;
    }

    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("The file is invalid as there are no any data in it.\n");
        fclose(f);
        return;
    }

    do{
    printf("Enter ur id number:");
    scanf("%s", ID);
    while((fscanf(f, "%[^,],%[^,],%d,%[^,],%[^,],%[^,],%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
    user.ID,user.name,&user.age,user.DOB,user.identificationNumber,user.address,&user.gender,user.phoneNumber,
    user.email,user.race,user.nationality,user.password,user.accountstatus)) != EOF) {
        if (strcmp(user.ID, ID) == 0){
            found==1;
            printf("Please enter your password: ");
            scanf("%s", user.password);
            printf("Please re-enter your password to confirm: ");
            scanf("%s", user.reconfirmedPassword);
            passwordValidation(user.password,user.reconfirmedPassword);
            fprintf(tempFile, "%s,%s,%d,%s,%s,%s,%c,%s,%s,%s,%s,%s,%s\n",
                    user.ID,user.name,user.age,user.DOB,user.identificationNumber,user.address,
                    toupper(user.gender),user.phoneNumber,user.email,user.race,user.nationality,user.password,user.accountstatus);
                    printf("The information has been updated successfully.\n");
        }
        else{
            fprintf(tempFile, "%s,%s,%d,%s,%s,%s,%c,%s,%s,%s,%s,%s,%s\n",
                    user.ID,user.name,user.age,user.DOB,user.identificationNumber,user.address,
                    toupper(user.gender),user.phoneNumber,user.email,user.race,user.nationality,user.password,user.accountstatus);
        }
    }
    if (!found) {
        printf("\033[1;31m");
        printf("The ID that you entered is not found.\n");
        printf("\033[0m");
    }

    }while(found==0);
    fclose(f);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);
}

int main() {
    int choice;
    char username[50];
    char password[50];
    int reset;
    int permit;
    int wrong=0;
    int proceed;

    printf("Welcome to The Student Semester Planner System!\n");
    printf("----------------------------------\n");
    printf("|            Main Menu           |\n");
    printf("----------------------------------\n");
    printf("|         1. Login               |\n");
    printf("|         2. Exit                |\n");
    printf("----------------------------------\n");
    printf("|         Choice:                |\n");
    printf("----------------------------------\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Please enter your ID: \n");
        scanf("%s",username);
        clearBuffer();

        printf("Please enter your password: \n");
        scanf("%s", password);
        clearBuffer();

        permit=login(username, password);
        while (permit==5){
            wrong++;
            printf("Please enter your ID: \n");
            scanf("%s",username);
            clearBuffer();

            printf("Please enter your password: \n");
            scanf("%s", password);
            clearBuffer();

            permit=login(username, password);
            if (wrong==2){
                printf("\033[1;31m");
                printf("error\n");
                printf("\033[0m");
                printf("You have entered the wrong username or password for 3 times.\n");
                printf("Do you want reset ur password?\n");
                printf("1. YES\n");
                printf("2. NO\n");
                scanf(" %d", &reset);
                if (reset==1){
                    forgetpassword();
                }
                else
                {
                    printf("Thank you for using our system.\n");
                    exit(0);
                }

            }
        }
        }else if (choice == 2) {
        printf("Goodbye and have a nice day ahead!\n");
    } 

    else {
        printf("\033[1;31m");
        printf("error!\n");
        printf("\033[0m");
        printf("Invalid choice.\n");
        printf("Please enter a valid choice: ");
        scanf("%d", &choice);
    }

    switch (permit) {
    case 1:
        studentMain(username);
        break;
    case 2:
        programCoodinatorMain();
        break;
    case 3:
        programLeaderMain();
        break;
    case 4:
        printf(" -------------------------------------\n");
        printf("|         Administrator Menu          |\n");
        printf(" -------------------------------------\n");
        printf("|     1. Register a new account       |\n");
        printf("|     2. Update Information           |\n");
        printf("|     3. Exit                         |\n");
        printf(" -------------------------------------\n");
        printf("|     Choice:                         |\n");
        printf(" -------------------------------------\n");
        scanf("%d", &choice);
        clearBuffer();
    
    if (choice == 1) {
        struct User user;
        char filename[20], c;
        char input[20];
        do{
        printf(" -------------------------------------------\n");
        printf("|         Register a new account            |\n");
        printf(" -------------------------------------------\n");
        printf("|        1. Student                         |\n");
        printf("|        2. Programme Coordinator           |\n");
        printf("|        3. Programme Leader                |\n");
        printf("|        4. Administrator                   |\n");
        printf("|        5. Exit                            |\n");
        printf(" -------------------------------------------\n");
        printf("|      Role:                                |\n");
        printf(" -------------------------------------------\n");
        int role;
        scanf("%d", &role);
        clearBuffer();

        switch (role) {
            case 1:
                registerUser(&user, "student.txt", role);
                break;
            case 2:
                registerUser(&user, "coordinator.txt", role);
                break;
            case 3:
                registerUser(&user, "leader.txt", role);
                break;
            case 4:
                registerUser(&user, "administrator.txt", role);
                break;
            case 5:
                printf("Thank you for using our system.\n");
                break;
            default:
                printf("\033[1;31m");
                printf("error!\n");
                printf("\033[0m");
                printf("Invalid choice. Your registration has failed.\n");
                break;
        }
        if (role == 1 || role == 2 || role == 3 || role == 4){
            printf("Do you want to proceed with other role?");
            printf("1. Yes\n");
            printf("2. No\n");
            scanf(" %d", &proceed);
        }
        else{
            printf("\033[1;31m");
            printf("error\n");
            printf("\033[0m");
            printf("Invalid choice. Please enter a valid choice.\n");
            printf("Do you want to proceed with other role?");
            printf("1. Yes\n");
            printf("2. No\n");
            scanf("%d", &proceed);
        }
    }while (proceed==1);}
    

    else if (choice == 2) {
        do{
        printf(" -------------------------------------------\n");
        printf("|             Update account                |\n");
        printf(" -------------------------------------------\n");
        printf("|        1. Student                         |\n");
        printf("|        2. Programme Coordinator           |\n");
        printf("|        3. Programme Leader                |\n");
        printf("|        4. Administrator                   |\n");
        printf("|        5. Exit                            |\n");
        printf(" -------------------------------------------\n");
        printf("|      Update role:                         |\n");
        printf(" -------------------------------------------\n");
        int role;
        scanf("%d", &role);
        
        switch (role)
        {
        case 1:
            updatedInformation("student.txt", role);
            break;
        case 2:
            updatedInformation("coordinator.txt", role);
            break;
        case 3:
            updatedInformation("leader.txt", role);
            break;
        case 4:
            updatedInformation("administrator.txt", role);
            break;
        case 5:
            printf("Thank you for using our system.\n");
            break;
        default:
            printf("\033[1;31m");
            printf("error\n");
            printf("\033[0m");
            printf("Invalid choice. Your update has failed.\n");
            break;
        }
        if (role == 1 || role == 2 || role == 3 || role == 4){
            printf("Do you want to proceed with other role?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            scanf("%d", &proceed);
        }
        else{
            printf("\033[1;31m");
            printf("error\n");
            printf("\033[0m");
            printf("Invalid choice. Please enter a valid choice.\n");
            printf("Do you want to proceed with other role?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            scanf("%d", &proceed);
        }
    } while (proceed==1);

    } else if (choice == 3) {
        printf("Goodbye and have a nice day ahead!\n");
    } else {
        printf("\033[1;31m");
        printf("error!\n");
        printf("\033[0m");
        printf("Invalid choice.\n");
        printf("Please enter a valid choice: ");
        scanf("%d", &choice);
        }
    }
}


