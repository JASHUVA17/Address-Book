#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    char name[50];
    char mobile[11];
    char gmail[50];
    char location[50];
}Address;

typedef enum
{
    SUCCESS,
    FAILURE,
}Status;

Status Add_Contacts(Address *member,int num);
Status Check(char *user_name, char *arr);
void Copy_File(Address *member);
Status Edit_Details();
Status Search();
Status Print_Details();
Status Delete_Contacts();
