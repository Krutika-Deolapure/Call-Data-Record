#include "../HDR/CDR_header.h"

void interOperatorBillingFile(cdr_record *data)
{
if(data == NULL){
        logmessage(LOG_LEVEL_WARNING,"Please process CDR file first");
	//printf("Please process CDR file first");
	return;  
}
else{
    int i, k;
    IOP op[5];
    int check=0;
    //char msg[2048] = {0};
    //char temp[MAX_LENGTH];
    char op_number[MAX_LENGTH];
    FILE *fp;
 
     logmessage(LOG_LEVEL_INFO,"Opening file for writing Inter-Operator Bi    lling Data...");
    fp = fopen("../DATA/IOSB.txt", "w");
    if(fp == NULL)
    {
        logmessage(LOG_LEVEL_FATAL,"Failed to open file for writing Inter    -Operator Billing Data.");
        printf("\n\n Please Try Later\n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\n\nEnter the operator number\n");
        scanf("%s", op_number);
 
        for(k = 0; k < 5; k++)
        {
            //bzero(op[k].opname, 20);
            op[k].incomingcall = 0;
            op[k].outgoingcall = 0;
            op[k].incomingsms = 0;
            op[k].outgoingsms = 0;
            op[k].downloaded = 0;
            op[k].uploaded = 0;
        }
 
        // Initialize opmmc values
        strcpy(op[0].opmmc, "42500");
        strcpy(op[1].opmmc, "42501");
        strcpy(op[2].opmmc, "42502");
        strcpy(op[3].opmmc, "42503");
        strcpy(op[4].opmmc, "42504");
 
        for(i = 0; i < n; i++)
        {
            for(k = 0; k < 5; k++)
            {
                if(strcmp(op[k].opmmc, data[i].opmmc) == 0)
                {
                    if(strcmp(data[i].calltype, "MOC") == 0)
                    {
                        op[k].outgoingcall += atol(data[i].dur);
                    }
                    else if(strcmp(data[i].calltype, "MTC") == 0)
                    {
                        op[k].incomingcall += atol(data[i].dur);
                    }
                    else if(strcmp(data[i].calltype, "SMS-MO") == 0)
                    {
                        op[k].outgoingsms += 1;
                    }
                    else if(strcmp(data[i].calltype, "SMS-MT") == 0)
                    {
                        op[k].incomingsms += 1;
                    }
                    else if(strcmp(data[i].calltype, "GPRS") == 0)
                    {
                        op[k].downloaded += atol(data[i].download);
                        op[k].uploaded += atol(data[i].upload);
                    }
                    strcpy(op[k].opname, data[i].opbrand);
                }

            }
        }
 
        // Print specific operator's data based on the entered operator number
        for(k = 0; k < 5; k++)
        {
            if(strcmp(op_number, op[k].opmmc) == 0)
            {
                check=1;
                 logmessage(LOG_LEVEL_INFO,"Printing specific operator's d    ata based on the entered operator number...");
                printf("\n\nOperator Brand : %s ( %s )", op[k].opname, op[k].opmmc);
                printf("\nIncoming Voice Call Durations: %ld sec", op[k].incomingcall);
                printf("\nOutgoing Voice Call Durations: %ld sec", op[k].outgoingcall);
                printf("\nIncoming SMS Messages: %ld", op[k].incomingsms);
                printf("\nOutgoing SMS Messages: %ld", op[k].outgoingsms);
                printf("\nMB Downloaded: %ld | MB Uploaded: %ld\n", op[k].downloaded, op[k].uploaded);
                break; // No need to continue looping once data is printed
            }
   } 
 

           if(check==0)
           {
             logmessage(LOG_LEVEL_FATAL,"Invalid Operator Number\n\n");
             //printf("Invalid Operator Number\n\n");
            
         }


        // Write all operators' data to file
         logmessage(LOG_LEVEL_INFO,"Writing all operators' data to file...");
        fprintf(fp, "# Operator Data Base: \n\n");
        for(k = 0; k < 5; k++)
        {
            fprintf(fp, "\nOperator Brand : %s ( %s )", op[k].opname, op[k].opmmc);
            fprintf(fp, "\nIncoming Voice Call Durations: %ld sec", op[k].incomingcall);
            fprintf(fp, "\nOutgoing Voice Call Durations: %ld sec", op[k].outgoingcall);
            fprintf(fp, "\nIncoming SMS Messages: %ld", op[k].incomingsms);
            fprintf(fp, "\nOutgoing SMS Messages: %ld", op[k].outgoingsms);
            fprintf(fp, "\nMB Downloaded: %ld | MB Uploaded: %ld\n\n", op[k].downloaded, op[k].uploaded);
        }
    }
    fclose(fp);
    logmessage(LOG_LEVEL_INFO,"Inter-Operator Billing File processing completed.");

}
}

