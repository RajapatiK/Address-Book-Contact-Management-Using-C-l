#include "contact.h"
#include<string.h>
#include<stdlib.h>

int main()
{
    int n;
    /* Iniatializing a variable for the structure as s */
    AddressBook s;
    initialize(&s);
    /* Displaying the options for the user to do choose 
     * and promting the options again and againn until the 
     * user gives exit */
    do
    {
	printf("Address Book Menu: \n1. Create Contact\n2. Search Contact\n3. Edit Contact\n4. Delete Contact\n5. List all contacts\n6. Save and Exit\n7. Exit\nEnter your choice: ");
	scanf("%d",&n);
	switch(n)
	{
	    /* Function calls happens for each operations within the switch case
	     * according to the users prefernce */
	    case 1:createContact(&s);
		   break;
	    case 2:searchContact(&s);
		   break;
	    case 3:editContact(&s);
		   break;
	    case 4:deleteContact(&s);
		   break;
	    case 5:listContacts(&s);
		   break;
	    case 6:printf("do you want to save:y/n\n");
		   char ch;
		   scanf(" %c",&ch);
		   if(ch=='y'||ch=='Y')
		   {
		       Save(&s);
		       n=7;
		       printf("Exit\n");
		   }
		   else
		   {
		       n=7;
		       printf("Exit\n");
		   }
		   break;
	    case 7:printf("Exit\n");
		   break;
	    default:printf("Invalid\n");
	}
	/* loop terminates when the user gives 7 as input */
    }while(n!=7);
}


