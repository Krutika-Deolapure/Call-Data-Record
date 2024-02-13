#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../HDR/CDR_header.h"
#define SIZE 10

// File contains following functions- 
// Find_CustInfo() 
// Store_CustInfo()
// inter_Op() : helping function to check if record is between same or diff operators

int inter_Op(char op1[], char op2[]){
	return (strcmp(op1, op2));
}

void Find_CustInfo(cdr_record *data){
         logmessage(LOG_LEVEL_INFO,"Starting Customer Information Search...");
	if(data == NULL){
                 logmessage(LOG_LEVEL_WARNING,"Please process CDR data first");
		//printf("Please process CDR data first");
		return;
}
else{
	char inputID[7];
        printf("Enter MSISDN: ");
	scanf("%s", inputID);
	int check = 0;

	// Variables to hold values to be printed
	char msid[7];
	// In same provider data
	char in_call_op[SIZE], out_call_op[SIZE];
	strcpy(in_call_op, "0") ; 
	strcpy(out_call_op, "0");
	int sms_in_op = 0, sms_out_op = 0;
	
	// For external provider data
	char in_call_out[SIZE], out_call_out[SIZE];
	strcpy(in_call_out, "0") ;
	strcpy(out_call_out, "0");
	int sms_in_out = 0, sms_out_out = 0;

	char MB_up[SIZE], MB_down[SIZE];
	strcpy(MB_up, "0");
	strcpy(MB_down, "0");	
	
	for(int i=0; i<n; i++){
		if(strcmp(data[i].msisdn, inputID) == 0){
			// User found	
			check = 1;
			strcpy(msid, data[i].msisdn);			
			if(strcmp(data[i].calltype, "MOC") == 0){
				if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
					strcpy(out_call_out, data[i].dur);
				}
				else{
					strcpy(out_call_op, data[i].dur);
				}	
			}
			else if(strcmp(data[i].calltype, "MTC") == 0){
				if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
					strcpy(in_call_out, data[i].dur);
				}
				else{
					strcpy(in_call_op, data[i].dur);
				}
			}
			else if(strcmp(data[i].calltype, "SMS-MO") == 0){
				if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
					sms_out_out = 1;
				}
				else{
					sms_out_op = 1;
				}
			}
			else if(strcmp(data[i].calltype, "SMS-MT") == 0){
				if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
					sms_in_out = 1;
				}
				else{
					sms_in_op = 1;
				}
			}
			else if(strcmp(data[i].calltype, "GPRS") == 0){
				strcpy(MB_up, data[i].upload);
				strcpy(MB_down, data[i].download); 
			}
			else{
				printf("Error in CDR data");
				break;
			}
		
                        logmessage(LOG_LEVEL_INFO,"# Customers Data Base:    ");
			//printf("\n#Customers Data Base: \n");
			printf("Customer ID: %s  (%s) \n", msid, data[i].opbrand);
			printf("* Services within the mobile operator * \n");
			printf("Incoming voice call duration: %s sec \n", in_call_op);
			printf("Outgoing voice call duration: %s sec \n", out_call_op);
			printf("Incoming SMS messages: %d \n", sms_in_op);
			printf("Outgoing SMS messages: %d \n", sms_out_op);

			printf("\n* Services outside the mobile operator * \n");
			printf("Incoming voice call duration: %s sec \n", in_call_out);
			printf("Outgoing voice call duration: %s sec \n", out_call_out);
			printf("Incoming SMS messages: %d \n", sms_in_out);
			printf("Outgoing SMS messages: %d \n", sms_out_out);

			printf("\n* Internet use * \n");
			printf("MB downloaded: %s | MB uploaded: %s \n", MB_down, MB_up);

			break;
		}
	}
	
	if(check == 0){
                logmessage(LOG_LEVEL_WARNING,"MSISDN not found");
		//printf("MSISDN not found");
	}
}
}

void Store_CustInfo(cdr_record *data){
logmessage(LOG_LEVEL_INFO,"Storing Customer Information...");
if(data == NULL){
	return;
}
else{
    FILE *fp;
    fp = fopen("../DATA/CB.txt","w");
    if(fp == NULL){
            logmessage(LOG_LEVEL_FATAL,"Failed to open file for writing C    ustomer Billing Data.");
	    printf("\n\n Please try later\n\n");
	    exit(EXIT_FAILURE);
    }
	
    else{
        
	fprintf(fp, "# Customers Data Base: \n");

	for(int i=0; i<n; i++){    
            char in_call_op[SIZE], out_call_op[SIZE];
            strcpy(in_call_op, "0") ;
            strcpy(out_call_op, "0");
            int sms_in_op = 0, sms_out_op = 0;
            
            // For external provider data
            char in_call_out[SIZE], out_call_out[SIZE];
            strcpy(in_call_out, "0") ;
            strcpy(out_call_out, "0");
            int sms_in_out = 0, sms_out_out = 0;
            
            char MB_up[SIZE], MB_down[SIZE];
            strcpy(MB_up, "0");
            strcpy(MB_down, "0");
                 
            if(strcmp(data[i].calltype, "MOC") == 0){
                if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
                    strcpy(out_call_out, data[i].dur);
                }
                else{
                    strcpy(out_call_op, data[i].dur);
                }
          }
            else if(strcmp(data[i].calltype, "MTC") == 0){
                if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
                    strcpy(in_call_out, data[i].dur);
                }
                else{
                    strcpy(in_call_op, data[i].dur);
                }
        }
            else if(strcmp(data[i].calltype, "SMS-MO") == 0){
                if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
                    sms_out_out = 1;
                }
                else{
                    sms_out_op = 1;
               }
           
            }
            else if(strcmp(data[i].calltype, "SMS-MT") == 0){
                if(inter_Op(data[i].opmmc, data[i].thirdpartyopbrand)){
                    sms_in_out = 1;
                }
               else{
                    sms_in_op = 1;
               }
          }
            else if(strcmp(data[i].calltype, "GPRS") == 0){
                strcpy(MB_up, data[i].upload);
                strcpy(MB_down, data[i].download);
            }
            else{
                printf("Error in CDR data");
                break;
          }
          
            fprintf(fp, "Customer ID: %s (%s) \n", data[i].msisdn, data[i].opbrand);
            fprintf(fp, "	* Services within the mobile operator * \n");
            fprintf(fp, "	Incoming voice call duration: %s sec \n", in_call_op);
            fprintf(fp, "	Outgoing voice call duration: %s sec \n", out_call_op);
            fprintf(fp, "	Incoming SMS messages: %d \n", sms_in_op);
 	    fprintf(fp, "	Outgoing SMS messages: %d \n", sms_out_op);
            fprintf(fp, "	* Services outside the mobile operator * \n");
            fprintf(fp, "	Incoming voice call duration: %s sec \n", in_call_out);
            fprintf(fp, "	Outgoing voice call duration: %s sec \n", out_call_out);
            fprintf(fp, "	Incoming SMS messages: %d \n", sms_in_out);
            fprintf(fp, "	Outgoing SMS messages: %d \n", sms_out_out);
            fprintf(fp, "	* Internet use * \n");
            fprintf(fp, "	MB downloaded: %s | MB uploaded: %s \n \n", MB_down, MB_up);
    }
    
        fclose(fp);
         logmessage(LOG_LEVEL_INFO,"Customer Information stored successfully. CB.txt ready");
       // printf("\nCB.txt ready");
}
}
}
