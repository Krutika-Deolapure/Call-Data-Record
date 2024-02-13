#include "../HDR/CDR_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void logmessage(int level, const char *format, ...){
            va_list args;
            va_start(args, format);
            if (level <= LOG_LEVEL_DEBUG) {
                 printf("[%d]", level);
                 vprintf(format, args);
                 printf("\n");
          }
          va_end(args);
 }


int main(){
        logmessage(LOG_LEVEL_INFO,"Starting CDR Processing System...");
	while(1){
	int op;
	printf("\n*** CDR Processing System *** \n");
	printf("1. Login \n2. Sign Up \n3. Exit");
	printf("\nEnter choice: ");	
	scanf("%d", &op);
	
	switch(op){
		case 1: {
			logIn();
			} break;
		
		case 2: {
			signUp();
			} break;

		case 3: {
                        logmessage(LOG_LEVEL_INFO,"Exited");
			exit(1);
			}break;
		
		default: 
                         logmessage(LOG_LEVEL_WARNING,"Invalid choice.");
                        //printf("Invalid choice. \n");
	}
}
	return 0;
}

void mainMenu(){
        logmessage(LOG_LEVEL_INFO,"Entering Main Menu...");
	cdr_record *data = NULL;

	while(1){
	int op;
	printf("\n*** CDR Operations *** \n");
	printf("1. Process CDR File \n2. Print/Search Billing Information \n3. Logout");
	printf("\nEnter choice: ");
	scanf("%d", &op);

	switch(op){
		case 1: {
			if(data == NULL){
                                logmessage(LOG_LEVEL_INFO,"Processing CDR File...");
				cdr_record *tmp = process_cdr();
				data = tmp;
				if(data == NULL){
                                        logmessage(LOG_LEVEL_WARNING,"Processing Failed.");
					//printf("\nProcessing Failed. \n");
				}
				else{
                                        logmessage(LOG_LEVEL_INFO,"File Processed Successfully.");
					//printf("\n File Processed. \n ");
				}
			}
			else{
                                logmessage(LOG_LEVEL_WARNING,"File already processed.");
				//printf("File already processed. \n");
			}
		}
		break;

		case 2: {
                        logmessage(LOG_LEVEL_INFO,"Entering Billing Menu...");
			billingMenu(data);
		} break;

		case 3: {
                        logmessage(LOG_LEVEL_INFO,"Logging out...");
			free(data);
			return;
		}
		default: 
                        logmessage(LOG_LEVEL_WARNING,"Invalid Choice.");
                        //printf("Invalid Choice. \n");
	}
	}
        logmessage(LOG_LEVEL_INFO,"Exiting Main Menu...");
	return;
}

void billingMenu(cdr_record *data){
	int op;
	printf("\n*** Billing Menu *** \n");
	printf("1. Customer Billing \n2. Inter-Operator Billing \n3. Leave \n");
	printf("Enter choice: ");
	scanf("%d", &op);

	switch(op){
		case 1: {
                        logmessage(LOG_LEVEL_INFO,"Customer Billing Operation...");
			Find_CustInfo(data);
                	Store_CustInfo(data);      
		} break;

		case 2: {
                        logmessage(LOG_LEVEL_INFO,"Inter-Operator Billin Operation...");
			interOperatorBillingFile(data);	
		}
		break;
	}

}
