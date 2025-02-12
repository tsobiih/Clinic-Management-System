#ifndef PATIENT_MANAGEMENT_H
#define PATIENT_MANAGEMENT_H

#include "STD_TYPES.h"

// Define the Node structure
typedef struct Node {
    u16 age;
    u16 ID;
    char gender[10];
    char name[100];
    struct Node* next;
} Node;

//Define reservation slots
typedef struct reservation
{
    u16 ID;
    char time[50];
    u8 index;
    struct reservation* next;

} reservation;

extern reservation slot1;
extern reservation slot2;
extern reservation slot3;
extern reservation slot4;
extern reservation slot5;

// Function prototypes
Node* createNode(u16 age, u16 ID, char* name, char* gender);
int idexist(Node* head, u16 ID);
void addpatient(Node** head);
void printList(Node* head);
Node* findNodeByID(Node* head, u16 ID);
void updatePatient(Node* head, u16 ID, char* Newname, char* Newgender, u16 Newage);
void ReserveaASlot(void);
void patientInfo(u16* age, char* name, char* gender);
void CancleByID(reservation* head, u16 ID);
void link_slots(void);
void printInfo(Node *last);
void findReservatoinByID(reservation* head, u16 ID);


#endif // PATIENT_MANAGEMENT_H
