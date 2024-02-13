#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HDR/CDR_header.h"

//#define MAX 100

cdr_record *process_cdr()
{
	 logmessage(LOG_LEVEL_INFO,"Processing CDR file...");
         n = 0;
	 FILE *fp;
         fp = fopen("../DATA/data.cdr", "r"); 
         cdr_record *usr = NULL;
         char record[9][MAX_LENGTH];
         char line[MAX_LENGTH]={0};
         int i = 0;
         
         if(fp == NULL)
         {
                 logmessage(LOG_LEVEL_FATAL,"Failed to open CDR file for     processing.");
                 printf("\n\nPlease try Later");
                 return NULL;
         }
         else
         {
                 while(fgets(line,MAX_LENGTH,fp)!=NULL)
                 {
                         char *token = strtok(line,"|");
                        // strcpy(record[0], token);
                          while(token != NULL)
                         {
                                 if(i ==7 && strcmp(record[3],"GPRS")==0)
                                 {
                                         strcpy(record[i]," ");
                                         i++;
                                         continue;
                                 }
                                 strcpy(record[i],token);
                                 token = strtok(NULL, "|");
                                 i++;
                         }

                         i = 0;
                         n++;
                        // printf("%d ", n);
                         usr = realloc(usr, n*sizeof(cdr_record));

                         strcpy(usr[n-1].msisdn, record[0]);
                         strcpy(usr[n-1].opbrand, record[1]);
                         strcpy(usr[n-1].opmmc, record[2]);
                         strcpy(usr[n-1].calltype, record[3]);
                         strcpy(usr[n-1].dur, record[4]);
                         strcpy(usr[n-1].download, record[5]);
                         strcpy(usr[n-1].upload, record[6]);
                         strcpy(usr[n-1].thirdpartymsisdn, record[7]);
                         strcpy(usr[n-1].thirdpartyopbrand, record[8]);

                 }
        }

        fclose(fp);
        logmessage(LOG_LEVEL_INFO,"CDR file processed successfully.");
 	return usr;

}
