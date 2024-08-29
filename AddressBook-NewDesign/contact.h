#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>


/* The structure to save the book.csv file */
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact *contacts;
    int contactCount;
} AddressBook;


/* Function declarartions */
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void Save(AddressBook *addressBook);
void edit1(AddressBook *addressBook,Contact *contact);

#endif
