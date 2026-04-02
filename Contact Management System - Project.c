//Contact Management System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    struct Contact* next;
};

struct Contact* head = NULL;

// 🔹 Check Duplicate
int isDuplicate(char name[]) {
    struct Contact* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// 🔹 Add Contact
void addContact() {
    struct Contact* newNode = (struct Contact*)malloc(sizeof(struct Contact));

    printf("Enter Name: ");
    scanf(" %[^\n]", newNode->name);

    if (isDuplicate(newNode->name)) {
        printf("Contact already exists!\n");
        free(newNode);
        return;
    }

    printf("Enter Phone: ");
    scanf("%s", newNode->phone);

    printf("Enter Email: ");
    scanf("%s", newNode->email);

    newNode->next = head;
    head = newNode;

    printf("Contact Added Successfully!\n");
}

// 🔹 Display Contacts
void displayContacts() {
    struct Contact* temp = head;

    if (temp == NULL) {
        printf("No contacts available!\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (temp != NULL) {
        printf("Name: %s | Phone: %s | Email: %s\n",
               temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
}

// 🔹 Delete Contact
void deleteContact() {
    char name[50];
    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    struct Contact *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Contact not found!\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Contact Deleted Successfully!\n");
}

// 🔹 Sort Contacts (Insertion Sort)
void sortContacts() {
    struct Contact *sorted = NULL;
    struct Contact* current = head;

    while (current != NULL) {
        struct Contact* next = current->next;

        if (sorted == NULL || strcmp(sorted->name, current->name) >= 0) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Contact* temp = sorted;
            while (temp->next != NULL &&
                   strcmp(temp->next->name, current->name) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    head = sorted;
    printf("Contacts Sorted Successfully!\n");
}

// 🔹 Convert Linked List to Array
int listToArray(struct Contact* arr[]) {
    struct Contact* temp = head;
    int i = 0;

    while (temp != NULL) {
        arr[i++] = temp;
        temp = temp->next;
    }

    return i;
}

// 🔹 Binary Search
void binarySearchContact() {
    struct Contact* arr[100];
    int n = listToArray(arr);

    if (n == 0) {
        printf("No contacts available!\n");
        return;
    }

    char key[50];
    printf("Enter name to search (sorted list required): ");
    scanf(" %[^\n]", key);

    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(arr[mid]->name, key);

        if (cmp == 0) {
            printf("Found: %s | %s | %s\n",
                   arr[mid]->name,
                   arr[mid]->phone,
                   arr[mid]->email);
            return;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("Contact not found!\n");
}

// 🔹 Main
int main() {
    int choice;

    while (1) {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Sort Contacts\n");
        printf("5. Binary Search Contact\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: deleteContact(); break;
            case 4: sortContacts(); break;
            case 5: binarySearchContact(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}