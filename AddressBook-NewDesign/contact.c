#include "contact.h"
#include <ctype.h>
#include <string.h>	
#include <stdlib.h>

/* Function declarations and function calls */

/* The start function is to display the columns such as Name Number Emmail */
void start(AddressBook *addressBook)
{
    printf("------------------------------------------------------------------------------------\n");
    printf("Name				Number				Email\n");
    printf("------------------------------------------------------------------------------------\n");
}
void end(AddressBook *addressBook)
{
    printf("------------------------------------------------------------------------------------\n");
}

/* Initializing the contacts taken from the file and storing it in structure*/
void initialize(AddressBook *addressBook)
{
    char *token,str[200];
    FILE *ptr;
    /* Opening the book.csv file in a file pointer and storing the file contents 
     * in the structure */
    ptr=fopen("book.csv","r");
    if(ptr==NULL)
    {
	printf("Unable to open the file");
    }
    /* It will read the first line in the csv file */
    fscanf(ptr,"%[^\n]",str);
    token=strtok(str,"#");
    addressBook->contactCount=atoi(token);
    addressBook->contacts=malloc((addressBook->contactCount)*sizeof(Contact));
    /* this loop is to store the contents except the first line 
     * in the csv file */
    for(int i=0;i<addressBook->contactCount;i++)
    {
	fscanf(ptr," %[^\n]",str);
	token=strtok(str,",");
	strcpy(addressBook->contacts[i].name,token);
	token =strtok(NULL,",");
	strcpy(addressBook->contacts[i].phone,token);
	token=strtok(NULL,",");
	strcpy(addressBook->contacts[i].email,token);   
    }    
}

/* list contacts definition is to listing the contacts in the structure which 
 * is copied from the file */
void listContacts(AddressBook *addressBook) 
{
    start(addressBook);
    for(int i=0;i<addressBook->contactCount;i++)
    {
	printf("%-30s	%-30s	%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    end(addressBook);
}

/* create contact definition is to create new contacts */
void createContact(AddressBook *addressBook) 
{
    /* getting the details from the user and storing in a 
     * character array */
    listContacts(addressBook);
    char name[50],phone[20],email[30],ch,ch1;
    do
    {
	printf("Enter the name: ");
	scanf(" %[^\n]",name);
	int len=0,i=0,count=0;
	do
	{
	    /* Condition checking for contact number 
	     * whether it was given previously or not */
	    len=0,i=0;
	    printf("Enter the phone number: ");
	    scanf(" %s",phone);
	    while(phone[i]!='\0')
	    {
		if(isdigit(phone[len]))
		{
		    len++;
		}i++;
	    }
	    if(len!=10)
	    {
		printf("Number is invalid\nEnter the number again \n");
	    }
	    for(int j=0;j<addressBook->contactCount;j++)
	    {
		if((strcmp(addressBook->contacts[j].phone,phone))==0)
		{
		    printf("Number is already present\n");
		    len=0;
		    break;
		}
	    }
	}while(len!=10);
	do
	{
	    /* Checking whether the email is already give if not store the email
	     * or if it previously stored display error */
	    count=0;
	    printf("Enter the email Id: ");
	    scanf(" %s",email);
	    if(email[0]!='@')
	    {
		if((strstr(email,"@"))&&(strstr(email,".com")))
		{
		    count++;
		}
		if(count==0)
		{
		    printf("Invalid\n");
		}
		for(int j=0;j<addressBook->contactCount;j++)
		{
		    if((strcmp(addressBook->contacts[j].email,email))==0)
		    {
			printf("Email is already present\n");
			count=0;
			break;
		    }
		}
	    }
	}while(count==0);
	/* If all the information are valid storing it in the structure and 
	 * increasing the array size by realloc */
	addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount+1)*sizeof(Contact));
	strcpy(addressBook->contacts[addressBook->contactCount].name,name);
	strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
	strcpy(addressBook->contacts[addressBook->contactCount].email,email);
	addressBook->contactCount++;
	printf("Do you want to continue:y/n\n");
	scanf(" %c",&ch);
    }while(ch!='n');
    end(addressBook);    
}

/* Search contact function definition */
void searchContact(AddressBook *addressBook) 
{
    listContacts(addressBook);
    char name[50],phone[50],email[50],ch;
    do
    {
	/* A promt message to the user that search by options */
	int n,len=0,i=0,flag=0;
	printf("Search options by:\n1.search by name:\n2.search by contact:\n3.search by email:\nENyter you choice:  ");
	scanf("%d",&n);
	switch(n)
	{
	    case 1:printf("Enter the name: ");
		   getchar();
		   scanf("%[^\n]",name);
		   int count=0;
		   /* Searching the contact in the structure by running two loops if it is there 
		    * display the contact else print not available */
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].name,name))==0)
		       {
			   start(addressBook);
			   printf("%-30s   %-30s   %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			   end(addressBook);
			   flag=1;
			   break;
		       }
		   }
		   if(flag==0)
		   {
		       printf("Not available\n");
		   }
		   break;
	    case 2:do
		   {
		       /* Searching the contact by phone number and
			* if it is there print the details else not available */
		       len=0,i=0;
		       printf("Enter the phone number: ");
		       scanf(" %s",phone);
		       while(phone[i]!='\0'){
			   if(isdigit(phone[len]))
			   {
			       len++;
			   }i++;}
		       if(len!=10)
			   printf("Number is invalid\n");
		   }while(len!=10);
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].phone,phone))==0)
		       {
			   start(addressBook);
			   printf("%-30s   %-30s   %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			   end(addressBook);
			   flag=1;
			   break;
		       }
		   }
		   if(flag==0)
		   {
		       printf("Not available\n");
		   }
		   break;
	    case 3:do
		   {
		       /* Searching the contact by email and
			* if it is there print the details else not available */
		       count=0;
		       printf("Enter the email Id: ");
		       scanf(" %s",email);
		       if(email[0]!='@')
		       {
			   if((strstr(email,"@"))&&(strstr(email,".com")))
			   {
			       count++;
			   }
			   if(count==0)
			   {
			       printf("Invalid\n");
			   }
		       }
		   }while(count==0);
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].email,email))==0)
		       {
			   start(addressBook);
			   printf("%-30s   %-30s   %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			   end(addressBook);
			   flag=1;
			   break;
		       }
		   }
		   if(flag==0)
		   {
		       printf("Not available\n");
		   }
		   break;
	    default:printf("Invalid Input\n");
	}/* Until the user gives n the loop runs */
	printf("Do you want to continue:y/n");
	scanf(" %c",&ch);
    }while(ch!='n');
}
void editContact(AddressBook *addressBook)
{
    listContacts(addressBook);
    char name[50],phone[50],email[50],newemail[50],newphone[50],ch,ch1;
    do
    {
	/* Initially promting the user with search options */
	int n,flag=0,count=0;
	printf("Options\n1.search by name:\n2.search by contact:\n3.search by email:\nEnter your choice here:  ");
	scanf("%d",&n);
	switch(n)
	{
	    case 1:printf("Enter the name: ");
		   getchar();
		   scanf("%[^\n]",name);
		   count=0;
		   /* Searching the contact by phone number and
	            * if it is there print the details else not available */
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].name,name))==0)
		       {
			   start(addressBook);
			   printf("%-30s   %-30s   %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			   end(addressBook);
			   /* if the contact is present function call to edit the name number and contact\
			    *  which is edit1 */
   			   edit1(addressBook,&addressBook->contacts[i]);
			   flag=1;
			   break;
		       }
		   }
		   if(flag==1)
		   {
		       printf("Contact edited successfully\n");
		   }
		   else
		   {
		       printf("Not Availabe\n");
		   }
		   break;
	    case 2:printf("Enter the Contact number: ");
		   getchar();
		   scanf("%[^\n]",phone);
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].phone,phone))==0)
		       {
			   start(addressBook);
			   printf("%-30s   %-30s   %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			   end(addressBook);
			   /* if the contact is present function call to edit the name number and contact\
			    *  which is edit1 */
			   edit1(addressBook,&addressBook->contacts[i]);
			   flag=1;
			   break;
		       }
		   }
		   if(flag==1)
		   {
		       printf("Not available\n");
		       printf("Contact edited successfully\n");
		   }
		   else
		   {
		       printf("Not available\n");
		   }
		   break;
	    case 3:printf("Enter the Email Address: ");
		   getchar();
		   scanf("%[^\n]",email);
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].email,email))==0)
		       {
			   start(addressBook);
			   printf("%-30s   %-30s   %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			   end(addressBook);
			   /* if the contact is present function call to edit the name number and contact\
			    *  which is edit1 */
			   edit1(addressBook,&addressBook->contacts[i]);
			   flag=1;
			   break;
		       }
		   }
		   if(flag==1)
		   {
		       printf("Contact edited successfully\n");
		   }
		   else
		   {
		       printf("Not available\n");
		   }
		   break;

	    default:printf("Invalid Input\n");
	}
	printf("Do you want to continue:y/n\n");
	scanf(" %c",&ch);
    }while(ch != 'n');
    	
}

/* Deleting the contact function call */
void deleteContact(AddressBook *addressBook) 
{
    listContacts(addressBook);
    char name[50],phone[50],newemail[50],ch,ch1;
    do
    {
	int flag=0;
	int n;
	/* Promting the user with search options */
	printf("Search by:\n1. search by name:\n2. search by contact:\n3. search by email:\nEnter your choice here: ");
	scanf("%d",&n);
	switch(n)
	{
	    case 1:printf("Enter the name: ");
		   getchar();
		   scanf("%[^\n]",name);
		   int count=0;
		   /* Searching the contact by name and
		    * if it is there print the details and delete the contact
		    * else not available */
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].name,name))==0)
		       {
			   flag=1;
			   for(int j=i;j<addressBook->contactCount;j++)
			   {
			       addressBook->contacts[j]=addressBook->contacts[j+1];
			   }
		       }
		   }
		   if(flag==1)
		   {
		       (addressBook->contactCount)--;
		       addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount)*sizeof(Contact));
		       printf("Contact Successfully Deleted\n");
		   }
		   else
		   {
		       printf("Not available\n");
		   }
		   break;
	    case 2:printf("Enter the Contact Number: ");
		   getchar();
		   scanf("%[^\n]",phone);
		   /* Searching the contact by number and
		    * if it is there print the details and delete the contact
		    * else not available */
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].phone,phone))==0)
		       {
			   flag=1;
			   for(int j=i;j<addressBook->contactCount;j++)
			   {
			       addressBook->contacts[j]=addressBook->contacts[j+1];
			   }
		       }
		   }
		   if(flag==1)
		   {
		       (addressBook->contactCount)--;
		       addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount)*sizeof(Contact));
		       printf("Contact Successfully Deleted\n");
		   }
		   else
		   {
		       printf("Not available\n");
		   }
		   break;
	    case 3:printf("Enter the Email Address: ");
		   getchar();
		   scanf("%[^\n]",newemail);
		   /* Searching the contact by email and
		    * if it is there print the details and delete the contact
		    * else not available */
		   for(int i=0;i<addressBook->contactCount;i++)
		   {
		       if((strcmp(addressBook->contacts[i].email,newemail))==0)
		       {
			   flag=1;
			   for(int j=i;j<addressBook->contactCount;j++)
			   {
			       addressBook->contacts[j]=addressBook->contacts[j+1];
			   }
		       }
		   }
		   if(flag==1)
		   {
		       (addressBook->contactCount)--;
		       addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount)*sizeof(Contact));
		       printf("Contact Successfully Deleted\n");
		   }
		   else
		   {
		       printf("Not available\n");
		   }
		   break;
	    default:printf("Invalid Input\n");
	}
	printf("Do you want to continue:y/n\n");
	scanf(" %c",&ch);
    }while(ch != 'n');
}
/* A fucntion call to save the structure elements to the book.csv file */
void Save(AddressBook *addressBook)
{
    /* Opening the book.csv in a file pointer with w command 
     * and storing the structure in the book.csv if the user gives save and s */
    FILE *ptr;
    ptr=fopen("book.csv","w");
    if(ptr==NULL)
    {
	printf("Unable to open the file");
    }
    /* updating the first line with cuyrrent count */
    fprintf(ptr,"#%d#\n",(addressBook->contactCount));
    for(int i=0;i<addressBook->contactCount;i++)
    {
	fprintf(ptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void edit1(AddressBook *addressBook,Contact *contact)
{
    /* editing the contact by the options */
    char name[50],phone[50],email[50],newemail[50],newphone[50];
    int num,count=0;
    printf("Optins\n1.edit name:\n2.Edit number:\n3.edit email:\nEnter your choice here:  ");
    scanf("%d",&num);
    switch(num)
    {
        case 1:printf("Enter the new name: ");
               scanf(" %[^\n]",contact->name);
               break;
        case 2:int len=0,j=0;
               do
               {
                   len=0,j=0;
                   printf("Enter the New contact Number: ");
                   scanf("%s",newphone);
                   while(newphone[j]!='\0')
                   {
                       if(isdigit(newphone[len]))
                       {
                           len++;
                       }j++;
                   }
                   if(len!=10)
                   {
                       printf("Number is invalid\nEnter the number again \n");
                   }
                   for(int j=0;j<addressBook->contactCount;j++)
                   {
                       if((strcmp(addressBook->contacts[j].phone,newphone))==0)
                       {
                           printf("Number is already present\n");
                           len=0;
                           break;
                       }
                   }
               }while(len!=10);
               strcpy(contact->phone,newphone);
               break;
        case 3:do
               {
                   printf("Enter the New email Address: ");
                   scanf(" %s",newemail);
                   if(newemail[0]!='@')
                   {
                       if((strstr(newemail,"@"))&&(strstr(newemail,".com")))
                       {
                           count++;
                       }
                       if(count==0)
                           printf("Invalid\n");
                   }
                   for(int j=0;j<addressBook->contactCount;j++)
                   {
                       if((strcmp(addressBook->contacts[j].email,newemail))==0)
                       {
                           printf("Email is already present\n");
                           count=0;
                           break;
                       }
                   }
               }while(count==0);
               strcpy(contact->email,newemail);
               break;
        default:printf("Invalid\n");
    }
}
