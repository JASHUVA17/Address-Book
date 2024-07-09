#include "header.h"

Status Add_Contacts(Address* member,int num) 				// Function to add a new contact.
{
    char str[50],arr[20]; 						// Arrays to store temporary string data.
    int flag = 0; 							// Flag to indicate if the name already exists.
    FILE *fptr = fopen("Address.txt","r"); 				// Open the address file in read mode.
    if (fptr == NULL ) 							// Check if the file could not be opened.
    {
        printf("---------------------------------------------\n"); 	// Print a separator line.
        printf("ERROR : UNABLE TO OPEN THE FILE\n"); 			// Print an error message.
        printf("---------------------------------------------\n");	// Print a separator line.
    }
    printf("Enter Name : "); 						// Prompt for the name input.
    getchar(); 								// Clear the input buffer.
    scanf("%[^\n]",arr); 						// Read the input name.
    while(fscanf(fptr,"%s",str) != EOF)	 				// Read each line from the file until EOF.
    {
        char *name = strtok(str,","); 					// Extract the name from the line.
        if ( Check(arr,name) == FAILURE ) 				// Check if the name already exists.
        {
            flag = 1; 							// Set flag if name exists.
            break; 							// Exit the loop.
        }
    }
    fclose(fptr); 							// Close the file.
    if ( flag == 1 ) 							// Check if the flag is set indicating the name exists.
    {
        printf("---------------------------------------------\n"); 	// Print a separator line.
        printf("ERROR : NAME ALREADY EXISTS\n"); 			// Print an error message.
        printf("---------------------------------------------\n"); 	// Print a separator line.
        return FAILURE; 						// Return failure status.
    }
    strcpy(member->name,arr); 						// Copy the input name to the member structure.
    printf("Enter Mobile Number : "); 					// Prompt for mobile number.
    scanf("%s",arr); 							// Read the mobile number.
    if(strlen(arr) != 10 ) 						// Check if the mobile number is not 10 digits.
    {
        printf("---------------------------------------------\n"); 	// Print a separator line.
        printf("ERROR PLEASE ENTER VALID MOBILE NUMBER \n"); 		// Print an error message.
        printf("---------------------------------------------\n"); 	// Print a separator line.
        return FAILURE; 						// Return failure status.
    }
    strcpy(member->mobile,arr); 					// Copy the mobile number to the member structure.
    printf("Enter Email.Id : "); 					// Prompt for email.
    scanf("%s",arr); 							// Read the email.
    char *at_sign = strchr(arr, '@'); 					// Check for '@' in the email.
    if (at_sign == NULL || at_sign == arr) 				// Validate the presence of '@'.
    {
        printf("---------------------------------------------\n"); 	// Print a separator line.
        printf("ERROR : PLEASE ENTER VALID EMAIL-ID\n"); 		// Print an error message.
        printf("---------------------------------------------\n"); 	// Print a separator line.
        return FAILURE; 						// Return failure status.
    }
    if (strstr(arr,".com") == 0) 					// Check for '.com' in the email.
    {
        printf("---------------------------------------------\n"); 	// Print a separator line.
        printf("ERROE : EMAIL-ID MUST CONTAIN '.com'\n"); 		// Print an error message (typo in "ERROE").
        printf("---------------------------------------------\n"); 	// Print a separator line.
        return FAILURE; 						// Return failure status.
    }
    strcpy(member->gmail, arr); 					// Copy the email to the member structure.
    printf("Enter Location : "); 					// Prompt for location.
    getchar(); 								// Clear the input buffer.
    scanf("%[^\n]",arr); 						// Read the location.
    strcpy(member->location,arr); 					// Copy the location to the member structure.
    if ( num == 0 ) 							// Check if num is zero indicating new entry.
    {
        Copy_File(member);					 	// Call function to copy member details to file.
    }
    return SUCCESS; 							// Return success status.
}

Status Check(char *user_name, char *arr) 			// Function to check if a name exists.
{
    if ( strcmp(user_name,arr) == SUCCESS ) 			// Compare input name with existing name.
    {
        return FAILURE; 					// Return failure if names match.
    }
    return SUCCESS; 						// Return success if names do not match.
}

void Copy_File(Address *member) 			// Function to copy contact details to the file.
{
    FILE *fptr = fopen("Address.txt","a"); 		// Open the address file in append mode.
    fseek(fptr, 0, SEEK_END); 				// Move to the end of the file.
    if(fptr != NULL) 					// Check if file pointer is valid.
    {
        fprintf(fptr, "%s,", member ->name); 		// Write the name to the file.
        fprintf(fptr, "%s,", member ->mobile); 		// Write the mobile to the file.
        fprintf(fptr, "%s,", member ->gmail); 		// Write the email to the file.
        fprintf(fptr, "%s\n", member ->location); 	// Write the location to the file.
    }
    fclose(fptr); 					// Close the file.
}

Status Edit_Details(Address *member) 					// Function to edit existing contact details.
{
    char arr[50], str[150],n_value[100]; 				// Arrays to store temporary string data.
    int flag = 0; 							// Flag to indicate if the contact was found.
    FILE *fptr = fopen("Address.txt", "r");	 			// Open the address file in read mode.
    FILE *fptr1 = fopen("temp.txt", "w"); 				// Open a temporary file in write mode.
    if ( fptr == NULL || fptr1 == NULL ) 				// Check if files could not be opened.
    {
        printf("---------------------------------------------\n");	// Print a separator line.
        printf("ERROR : UNABLE TO OPEN THE FILE\n"); 			// Print an error message.
        printf("---------------------------------------------\n"); 	// Print a separator line.
        return FAILURE; 						// Return failure status.
    }
    printf("Enter Name you want to change: "); 				// Prompt for the name to edit.
    getchar(); 								// Clear the input buffer.
    scanf("%[^\n]",arr); 						// Read the name to edit.
    while(fscanf(fptr,"%[^\n]\n",str) != EOF) 				// Read each line from the file until EOF.
    {
        char *name=strtok(str,","); 					// Extract the name from the line.
        char *mobile=strtok(NULL,","); 					// Extract the mobile number.
        char *gmail=strtok(NULL,","); 					// Extract the email.
        char *location=strtok(NULL,"\n"); 				// Extract the location.
        flag=0; 							// Reset the flag.
        if ( strcmp(arr,name) == 0 ) 					// Check if the name matches the input.
        {
            flag = 1; 							// Set flag if name matches.
            Add_Contacts(member,1); 					// Call function to add contact details.
            fprintf(fptr1, "%s,", member ->name); 			// Write new name to the temporary file.
            fprintf(fptr1, "%s,", member ->mobile);	 		// Write new mobile to the temporary file.
            fprintf(fptr1, "%s,", member ->gmail); 			// Write new email to the temporary file.
            fprintf(fptr1, "%s\n", member ->location); 			// Write new location to the temporary file.
        }
        if ( flag == 0 ) 						// Check if flag is not set.
        {
            fprintf(fptr1,"%s,%s,%s,%s\n",name,mobile,gmail,location); 	// Write original details to temporary file.
        }
    }
    fclose(fptr); 							// Close the address file.
    fclose(fptr1); 							// Close the temporary file.
    fptr = fopen("Address.txt","w"); 					// Reopen the address file in write mode.
    fseek(fptr,0,SEEK_SET); 						// Move to the start of the file.
    fptr1 = fopen("temp.txt","r"); 					// Reopen the temporary file in read mode.
    char ch; 								// Character variable for file copying.
    while ( fread(&ch,1,1,fptr1) > 0 ) 					// Read each character from temporary file.
    {
        fwrite(&ch,1,1,fptr); 						// Write each character to the address file.
    }
    fclose(fptr); 							// Close the address file.
    fclose(fptr1); 							// Close the temporary file.
    return SUCCESS; 							// Return success status.
}

Status Search() 								// Function to search for a contact.
{
    char arr[50], str[150]; 							// Arrays to store temporary string data.
    int option, flag = 0,error_flag = 0; 					// Variables for option selection and flagging errors.
    FILE *fptr = fopen("Address.txt", "r"); 					// Open the address file in read mode.
    if (fptr == NULL) 								// Check if file could not be opened.
    {
        printf("---------------------------------------------\n"); 		// Print a separator line.
        printf("ERROR : UNABLE TO OPEN THE FILE\n"); 				// Print an error message.
        printf("---------------------------------------------\n"); 		// Print a separator line.
        return FAILURE; 							// Return failure status.
    }
    printf("1.Name\n2.Contact\n3.Gmail\n4.Location\n5.Exit\nEnter Your option for Searching type : "); // Prompt for search type.
    scanf("%d", &option); 
    getchar();
    switch(option)
    {
        case 1: 
	    printf("Search Name : "); 						// Prompt for name.
            scanf("%[^\n]", arr); 						// Read the name.
            break; 
	case 2 :
            printf("Search Mobile Number : "); 					// Prompt for mobile number.
            scanf("%s", arr); 							// Read the mobile number.
            break; 
	case 3 :
            printf("Search Email-ID : "); 					// Prompt for email.
            scanf("%s", arr); 							// Read the email.
            break;
	case 4 : 
	    printf("Search Location : "); 					// Prompt for location.
            scanf("%[^\n]", arr); 						// Read the location.
            break; 
        case 5: 
	    return 0; 
        default: 
            printf("---------------------------------------------\n"); 		// Print a separator line.
            printf("ERROR : PLEASE ENTER VALID OPTION\n"); 			// Print an error message.
            printf("---------------------------------------------\n"); 		// Print a separator line.
            fclose(fptr); 							// Close the file.
            return FAILURE; 							// Return failure status.
    }
    while (fscanf(fptr,"%[^\n]\n",str) != EOF) 					// Read each line from the file until EOF.
    {
        flag = 0; 								// Reset the flag.
        char *name=strtok(str,","); 						// Extract the name from the line.
        char *mobile=strtok(NULL,","); 						// Extract the mobile number.
        char *gmail=strtok(NULL,","); 						// Extract the email.
        char *location=strtok(NULL,","); 					// Extract the location.
        if ( option == 1 ) 							// Check if search option is name.
        {
            if ( strncmp(arr,name,strlen(arr)) == 0 ) 				// Compare input name with file name.
            {
                flag = 1; 							// Set flag if match found.
            }
        }
        else if ( option == 2 )		 					// Check if search option is mobile number.
        {
            if ( strncmp(arr,mobile,strlen(arr)) == 0 ) 			// Compare input mobile with file mobile.
            {
                flag = 1;	 						// Set flag if match found.
            }
        }
        else if ( option == 3 ) 						// Check if search option is email.
        {
            if ( strncmp(arr,gmail,strlen(arr)) == 0 ) 				// Compare input email with file email.
            {
                flag = 1; 							// Set flag if match found.
            }
        }
        else if ( option == 4 ) 						// Check if search option is location.
        {
            if ( strncmp(arr,location,strlen(arr)) == 0 ) 			// Compare input location with file location.
            {
                flag = 1; 							// Set flag if match found.
            }
        }
        if (flag == 1) 								// Check if flag is set.
        {
            error_flag = 1; 							// Set error flag if match found.
            printf("---------------------------------------------\n"); 		// Print a separator line.
            printf("Name     : %s\n",name); 					// Print the name.
            printf("Contact  : %s\n",mobile); 					// Print the mobile number.
            printf("Gmail    : %s\n",gmail); 					// Print the email.
            printf("Location : %s\n",location); 				// Print the location.
            printf("---------------------------------------------\n"); 		// Print a separator line.
        }
    }
    if ( error_flag == 0 ) 							// Check if no match was found.
    {
        printf("---------------------------------------------\n"); 		// Print a separator line.
        printf("RECORD NOT FOUND FOR GIVEN DATA\n"); 				// Print an error message.
        printf("---------------------------------------------\n"); 		// Print a separator line.
        return FAILURE; 							// Return failure status.
    }
    return SUCCESS; 								// Return success status.
}

Status Print_Details() 							// Function to print all contact details.
{
    FILE *fptr = fopen("Address.txt","r"); 				// Open the address file in read mode.
    if ( fptr == NULL ) 						// Check if the file could not be opened.
    {
        return FAILURE; 						// Return failure status.
    }
    char str[150]; 							// Array to store temporary string data.
    int flag=0; 							// Flag to indicate if there are any records.
    while(fscanf(fptr,"%[^\n]\n",str) != EOF) 				// Read each line from the file until EOF.
    {
        flag=1; 							// Set the flag indicating records exist.
        char *name = strtok(str,","); 					// Extract the name from the line.
        char *mobile = strtok(NULL,","); 				// Extract the mobile number.
        char *gmail = strtok(NULL,","); 				// Extract the email.
        char *location = strtok(NULL,"\n"); 				// Extract the location.
        printf("---------------------------------------------\n"); 	// Print a separator line.
        printf("Name     : %s\n",name); 				// Print the name.
        printf("Contact  : %s\n",mobile); 				// Print the mobile number.
        printf("Gmail    : %s\n",gmail); 				// Print the email.
        printf("Location : %s\n",location); 				// Print the location.
        printf("---------------------------------------------\n"); 	// Print a separator line.
    }
    if ( flag == 0 )							// Check if no records were found.
    {
        return FAILURE; 						// Return failure status.
    }
    return SUCCESS; 							// Return success status.
}

Status Delete_Contacts() 								// Function to delete a contact.
{
    char arr[50], str[150]; 								// Arrays to store temporary string data.
    int flag = 0; 									// Flag to indicate if the contact was found.
    FILE *fptr = fopen("Address.txt", "r");				 		// Open the address file in read mode.
    FILE *fptr1 = fopen("temp.txt", "w"); 						// Open a temporary file in write mode.
    if ( fptr == NULL || fptr1 == NULL ) 						// Check if files could not be opened.
    {
        printf("---------------------------------------------\n"); 			// Print a separator line.
        printf("ERROR : UNABLE TO OPEN THE FILE\n"); 					// Print an error message.
        printf("---------------------------------------------\n"); 			// Print a separator line.
        return FAILURE; 								// Return failure status.
    }
    printf("Enter Name you want to delete : "); 					// Prompt for the name to delete.
    getchar(); 										// Clear the input buffer.
    scanf("%[^\n]",arr); 								// Read the name to delete.
    while(fscanf(fptr,"%[^\n]\n",str) != EOF) 						// Read each line from the file until EOF.
    {
        char *name=strtok(str,","); 							// Extract the name from the line.
        char *mobile=strtok(NULL,","); 							// Extract the mobile number.
        char *gmail=strtok(NULL,","); 							// Extract the email.
        char *location=strtok(NULL,"\n"); 						// Extract the location.
        flag=0; 									// Reset the flag.
        if ( strcmp(arr,name) == 0 ) 							// Check if the name matches the input.
        {
            flag = 1; 									// Set flag if name matches.
            continue; 									// Skip writing this line to the temporary file.
        }
        fprintf(fptr1,"%s,%s,%s,%s\n",name,mobile,gmail,location); 			// Write the details to the temporary file.
    }
    fclose(fptr); 									// Close the address file.
    fclose(fptr1); 									// Close the temporary file.
    fptr = fopen("Address.txt","w"); 							// Reopen the address file in write mode.
    fseek(fptr,0,SEEK_SET); 								// Move to the start of the file.
    fptr1 = fopen("temp.txt","r"); 							// Reopen the temporary file in read mode.
    char ch; 										// Character variable for file copying.
    while ( fread(&ch,1,1,fptr1) > 0 ) 							// Read each character from temporary file.
    {
        fwrite(&ch,1,1,fptr); 								// Write each character to the address file.
    }
    fclose(fptr); 									// Close the address file.
    fclose(fptr1); 									// Close the temporary file.
    if ( flag == 0 ) 									// Check if the contact was not found.
    {
        printf("---------------------------------------------\n"); 			// Print a separator line.
        printf("GIVEN DATA NOT FOUND\n"); 						// Print an error message.
        printf("---------------------------------------------\n"); 			// Print a separator line.
        return FAILURE; 								// Return failure status.
    }
    return SUCCESS; 									// Return success status.
}

