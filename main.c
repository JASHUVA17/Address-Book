#include "header.h"

int main()
{
    Address member;
    int choice;
    while(1)
    {
	printf("1.Add Contact\n2.Edit\n3.Search\n4.Print\n5.Delete\n6.Exit\nEnter Your Choce : ");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1 :
		if ( Add_Contacts(&member,0) == SUCCESS )
		{
		    printf("---------------------------------------------\n");
		    printf("CONTACT SAVED SUCCESSFULLY\n");
		    printf("---------------------------------------------\n");
		}
		else
		{
		    printf("---------------------------------------------\n");
		    printf("CONTACT SAVED FAILURE\n");
		    printf("---------------------------------------------\n");
		}
		break;
	    case 2 :
		if ( Edit_Details(&member) == SUCCESS )
		{
		    printf("---------------------------------------------\n");
		    printf("DETAILS EDITED SUCCESSFULLY\n");
		    printf("---------------------------------------------\n");
		}
		else
		{
		    printf("---------------------------------------------\n");
		    printf("DETAILS EDITED FAILURE\n");
		    printf("---------------------------------------------\n");
		}
		break;
	    case 3 :
		if ( Search() == SUCCESS )
		{
		    printf("---------------------------------------------\n");
		    printf("SEARCHING CONTACT SUCCESSFULLY\n");
		    printf("---------------------------------------------\n");
		}
		else
		{
		    printf("---------------------------------------------\n");
		    printf("SEARCHING CONTACT FAILURE\n");
		    printf("---------------------------------------------\n");
		}
		break; 
	    case 4 :	
		if ( Print_Details() == SUCCESS )
		{
		    printf("---------------------------------------------\n");
		    printf("PRINTED DETAILS SUCCESSFULLY\n");
		    printf("---------------------------------------------\n");
		}
		else
		{
		    printf("---------------------------------------------\n");
		    printf("PRINTED DETAILS FAILURE\n");
		    printf("---------------------------------------------\n");
		}
		break;
	    case 5:
		if ( Delete_Contacts() == SUCCESS )
		{
		    printf("---------------------------------------------\n");
		    printf("DETAILS DELETED SUCCESSFULLY\n");
		    printf("---------------------------------------------\n");
		}
		else
		{
		    printf("---------------------------------------------\n");
		    printf("DETAILS DELETED FAILURE\n");
		    printf("---------------------------------------------\n");
		}
		break;
	    case 6 :
		return 0;
	    default :
		printf("---------------------------------------------\n");
		printf("ERROR : ENTER VALID CHOICE\n");
		printf("---------------------------------------------\n");
	}
    }

}
