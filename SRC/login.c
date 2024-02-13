#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../HDR/CDR_header.h"

void signUp();
void logIn();
int userAllowed(const char user_name[], const char password[]);


void signUp() {
    char user_name[MAX_LENGTH];
    char password[MAX_LENGTH];
    char re_password[MAX_LENGTH];

    logmessage(LOG_LEVEL_INFO,"*****SIGNUP*****");


    printf("\n\n*****SIGNUP*****\n");
    printf("Enter user ID: ");
    scanf("%s", user_name);
    printf("Enter the password: ");
    scanf("%s", password);
    printf("Re-enter the password: ");
    scanf("%s", re_password);

    if (strcmp(password, re_password) == 0) {
        if (userAllowed(user_name, password)) {
            logmessage(LOG_LEVEL_WARNING,"User already exists!");
            //printf("\nUser already exists!\n");
            logIn();
        } else {
            FILE *fp = fopen("../DATA/users.txt", "a+");
            if (fp == NULL) {
                 logmessage(LOG_LEVEL_FATAL,"Failed to open user details file for writing.");
                //printf("\nFailed to open user details file for writing.\n");
                exit(EXIT_FAILURE);
            }

            fprintf(fp, "%s %s\n", user_name, password);
            fclose(fp);

            logmessage(LOG_LEVEL_INFO,"Registration successful");
            //printf("\nRegistration successful\n");
            logIn();  // Call logIn function after successful signup
        }
    } else {
        logmessage(LOG_LEVEL_WARNING,"Password mismatch");
        //printf("Password mismatch\n");
    }
}

void logIn() {
    char user_name[MAX_LENGTH];
    char password[MAX_LENGTH];

    logmessage(LOG_LEVEL_INFO,"******LOGIN******");
    //printf("\n\n******LOGIN******\n");
    printf("Enter user ID: ");
    scanf("%s", user_name);

    printf("Enter the password: ");
    scanf("%s", password);

    if (userAllowed(user_name, password)) {
        logmessage(LOG_LEVEL_INFO,"Login Successful");
        //printf("\nLogin Successful\n");
        mainMenu();
    } else {
        logmessage(LOG_LEVEL_WARNING,"Authentication Failed");
        //printf("\nAuthentication Failed\n");
    }
}

int userAllowed(const char user_name[], const char password[]) {
    char exist_username[MAX_LENGTH];
    char exist_password[MAX_LENGTH];

    FILE *fp = fopen("../DATA/users.txt", "r");
    if (fp == NULL) {
        logmessage(LOG_LEVEL_FATAL,"Failed to open user details file.");
        //printf("\n\nFailed to open user details file.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s %s\n", exist_username, exist_password) == 2) {
        if (strcmp(user_name, exist_username) == 0 && strcmp(password, exist_password) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
       


   
       
