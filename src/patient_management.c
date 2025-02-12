#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "patient_management.h"

// Define reservation slots as static variables
reservation slot1 = {0, "From 2pm to 2:30pm", 1, NULL};
reservation slot2 = {0, "From 2:30pm to 3pm", 2, NULL};
reservation slot3 = {0, "From 3pm to 3:30pm", 3, NULL};
reservation slot4 = {0, "From 4pm to 4:30pm", 4, NULL};
reservation slot5 = {0, "From 4:30pm to 5pm", 5, NULL};


//  link slots
void link_slots(void) {
    slot1.next = &slot2;
    slot2.next = &slot3;
    slot3.next = &slot4;
    slot4.next = &slot5;
    slot5.next = NULL;
}

// CREATE NODE
Node* createNode(u16 age, u16 ID,char* name,char* gender) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->age = age;
    newNode->ID=ID;
    strcpy(newNode->gender, gender);
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}


int idexist(Node* head,u16 ID)
{
    Node* last=head;
    while (last != NULL)
    {
        if (last->ID == ID)
        {
            return 1;
        }
        last = last->next;
    }
    return 0;
}

void addpatient(Node** head)
{
    u16 age,id;
    char name[100];
    char gender[10];
    char idStr[10];
    char ageStr[10];

    printf("Enter patient name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline character

    printf("Enter patient ID: ");
    fgets(idStr, sizeof(idStr), stdin);
    idStr[strcspn(idStr, "\n")] = '\0';  // Remove newline character
    id = (unsigned short)strtoul(idStr, NULL, 10);    // to conveert string to int 

    printf("Enter patient age: ");
    fgets(ageStr, sizeof(ageStr), stdin);
    ageStr[strcspn(ageStr, "\n")] = '\0';  // Remove newline character
    age = (unsigned short)strtoul(ageStr, NULL, 10);  // Convert string to unsigned short


    printf("Enter patient gender: ");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = '\0';  // Remove newline character

    if (idexist( *head , id))
    {
        printf("The id already exists.\n");
        return;
    }
    
    Node* newNode = createNode( age, id, name, gender);                             
    if (*head == NULL) 
    {
        *head = newNode;
    } 
    else 
    {
        Node* last=*head;
        while (last->next != NULL) 
        {
        last = last->next;
        }
        last->next = newNode;
    }
    printf("Patient record added successfully!\n");
}



void printList(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("Name: %s\nID: %hu\nAge: %hu\nGender: %s\n", temp->name, temp->ID, temp->age, temp->gender);
        printf("------------------------------------------\n");
        temp = temp->next;
    }
}

Node* findNodeByID(Node* head, u16 ID)
{
    Node* last = head;
    while (last != NULL)
    {
        if (last->ID == ID)
        {
            return last;
        }
        last = last->next;
    }
    printf("ID Not found.\n");
    return NULL;
}

void findReservatoinByID(reservation* head, u16 ID)
{
    reservation* last = head;
    while (last != NULL)
    {
        if (last->ID == ID)
        {
            printf("Reservation Info :\n");
            printf("ID : %hu\n",last->ID);
            printf("Time : %s\n",last->time);
            return;
        }
        last = last->next;
    }
    printf("There is no reservation with this ID!\n");
    return NULL;
}

void printInfo(Node* last)
{
    printf("Name : %s\n",last->name);
    printf("Id : %hu\n",last->ID);
    printf("Age : %hu\n",last->age);
    printf("Gender : %s\n",last->gender);
}

void updatePatient(Node* head,u16 ID,char* Newname,char* Newgender,u16 Newage)
{
    Node* node = findNodeByID(head, ID);
    if (node != NULL)
    {
        node->age = Newage;
        strcpy(node->name, Newname);
        strcpy(node->gender, Newgender);
        printf("Patient data updated successfully.\n");
    }
    else
    {
        printf("Patient with ID %hu not found.\n", ID);
    }
}

//Reseve slot
void ReserveaASlot(void)
{
    // Link the slots together
    link_slots();


    u8 flag=1;
    while (flag)
    {
        u8 ReservationSlot;
        u16 ReservationID;
        u8 slotCounter = 0;
        u8 isDuplicate = 0;  // Define isDuplicate outside the loop
        
        reservation* last = &slot1;
        printf("Available slots:\n");
        
        // Loop to display available slots
        while (last != NULL)
        {
            if (last->ID == 0)
            {
                printf("Enter '%hhu' for slot %s\n", last->index, last->time);
                slotCounter++;
            }
            last = last->next;
        }

        if (slotCounter == 0)
        {
            printf("There are no dates available today.\n");
            break;
        }

        // Input reservation ID
        printf("Enter the ID: ");
        scanf("%hu", &ReservationID);
        while (getchar() != '\n'); // Clear input buffer
        
        // Check for duplicate ID
        last = &slot1;
        while (last != NULL)
        {
            if (last->ID == ReservationID)
            {
                printf("ID already exists.\n");
                isDuplicate = 1;  // Set flag for duplicate ID
                break;
            }
            last = last->next;
        }
        
        if (isDuplicate) continue; // Restart the loop if duplicate found
        
        // Input reservation slot choice
        printf("Choose the slot: ");
        scanf("%hhu", &ReservationSlot);
        while (getchar() != '\n'); // Clear input buffer
        
        // Assign the ID to the chosen slot
        switch (ReservationSlot)
        {
        case 1:
            if (slot1.ID == 0)
            {
                slot1.ID = ReservationID;
                printf("Reservation successful.\n");
                break;
            }
            printf("Incorrect choice.\n");
            break;
        case 2:
            if (slot2.ID == 0)
            {
                slot2.ID = ReservationID;
                printf("Reservation successful.\n");
                break;
            }
            printf("Incorrect choice.\n");
            break;
        case 3:
            if (slot3.ID == 0)
            {
                slot3.ID = ReservationID;
                printf("Reservation successful.\n");
                break;
            }
            printf("Incorrect choice.\n");
            break;
        case 4:
            if (slot4.ID == 0)
            {
                slot4.ID = ReservationID;
                printf("Reservation successful.\n");
                break;
            }
            printf("Incorrect choice.\n");
            break;
        case 5:
            if (slot5.ID == 0)
            {
                slot5.ID = ReservationID;
                printf("Reservation successful.\n");
                break;
            }
            printf("Incorrect choice.\n");
            break;
        default:
            printf("Incorrect choice.\n");
            break;
        }
        printf("Do you want to book another slot? Enter 1 for Yes, 0 for No: ");
        scanf("%d", &flag);
        while (getchar() != '\n');
    }
    printf("Thank you!\nExiting...\n");
}


void patientInfo(u16* age, char* name, char* gender)
{
    char ageStr[10];

    printf("Enter patient name: ");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter patient age: ");
    fgets(ageStr, sizeof(ageStr), stdin);
    ageStr[strcspn(ageStr, "\n")] = '\0';  // Remove newline character
    *age = (u16)strtoul(ageStr, NULL, 10);

    printf("Enter patient gender: ");
    fgets(gender, 10, stdin);
    gender[strcspn(gender, "\n")] = '\0';
}


//CANCLE BY ID 
void CancleByID(reservation* head, u16 ID)
{
    reservation* last = head;
    while (last != NULL)
    {
        if (last->ID == ID)
        {
            last->ID=0;
            printf("Reservation cancled successfully!\n");
            return NULL;
        }
        last = last->next;
    }
    printf("ID Not found.\n");
    return NULL;
}