#ifndef CDR_HEADER_H_INCLUDED
#define CDR_HEADER_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <stdarg.h>

#define MAX_LENGTH 1024

// Log levels
#define LOG_LEVEL_FATAL   0
#define LOG_LEVEL_INFO    1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_DEBUG   3


typedef struct user_data
{
	char msisdn[10];
	char opbrand[15];
	char opmmc[10];
	char calltype[10];
	char dur[10];
	char download[10];
	char upload[10];
	char thirdpartymsisdn[10];
	char thirdpartyopbrand[10];
}cdr_record;


typedef struct interoperator
{
	char opname[20];
	char opmmc[20];
	long int incomingcall;
	long int outgoingcall;
	long int incomingsms;
	long int outgoingsms;
	long int downloaded;
	long int uploaded;
}IOP;

void logmessage(int, const char*, ...);


void mainMenu();
void logIn();
void signUp();
int userAllowed(const char[], const char[]);

//int billingMenu();

void billingMenu(cdr_record*);

cdr_record* process_cdr();

void Find_CustInfo(cdr_record*);
void Store_CustInfo(cdr_record*);

void interOperatorBilling(cdr_record*);
void interOperatorBillingFile(cdr_record*);
//void customerBillingFile(cdr_record*);

int n;

#endif
