#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_management.h"
#include "STD_TYPES.h"



int main(void)
{
    Node* head = NULL;
    u8 flag = 1;
    while (flag == 1)
    {
        u16 ID;
        char idStr[10];
        u16 age;
        char name[100];
        char gender[10];

        u8 mode,adminSevice;
        char modeStr[10];
        char passStr[10];
        u16 pass;
        u8 flag1 = 1;
        printf("Enter '1' for admin mode.\n");
        printf("Enter '2' for user mode.\n");
        printf("Enter '3' to close the app.\n");
        printf("Choose your mode :  ");
        fgets(modeStr, sizeof(modeStr), stdin);
        modeStr[strcspn(modeStr, "\n")] = '\0'; // إزالة السطر الجديد
        mode = (u8)strtoul(modeStr, NULL, 10);

        switch (mode)
        {
        case 1:                          //ADMIN SERVICE START FROM HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            for (u8 i = 1; i < 4; i++)
            {
                printf("Without any spaces.\nEnter the password :");
                fgets(passStr, sizeof(passStr), stdin);
                passStr[strcspn(passStr, "\n")] = '\0'; // إزالة السطر الجديد
                pass = (u16)strtoul(passStr, NULL, 10);
                if (pass==1234)                                       //CHECK FROM PASSWORD IF CORRECT 
                {
                    printf("Enter '1' to add new patient record.\n");
                    printf("Enter '2' to edit patient record.\n");
                    printf("enter '3' to reserve a slot with the doctor.\n");
                    printf("Enter '4' to cansel reservation.\n");
                    printf("Choose the option :");
                    fgets(modeStr, sizeof(modeStr), stdin);
                    modeStr[strcspn(modeStr, "\n")] = '\0'; // إزالة السطر الجديد
                    adminSevice = (u8)strtoul(modeStr, NULL, 10);
                    switch (adminSevice)
                    {
                    case 1:
                        while (flag1 == 1)
                        {
                            addpatient(&head);
                            printf("Enter '1' to add new record '0' to end :");
                            fgets(modeStr, sizeof(modeStr), stdin);
                            modeStr[strcspn(modeStr, "\n")] = '\0'; // إزالة السطر الجديد
                            flag1 = (u8)strtoul(modeStr, NULL, 10);
                        }
                        break;
                    case 2:
                        while (flag1 == 1)
                        {
                            printf("Enter patient ID: ");
                            fgets(idStr, sizeof(idStr), stdin);
                            idStr[strcspn(idStr, "\n")] = '\0';  // Remove newline character
                            ID = (unsigned short)strtoul(idStr, NULL, 10);

                            Node* foundNode = findNodeByID(head, ID);

                            if (foundNode != NULL) {
                                printf("Updating patient data...\n");
                                patientInfo(&age, name, gender);
                                updatePatient(head, ID, name, gender, age);
                            }
                            printf("Enter '1' to edit new record '0' to end :");
                            fgets(modeStr, sizeof(modeStr), stdin);
                            modeStr[strcspn(modeStr, "\n")] = '\0'; // إزالة السطر الجديد
                            flag1 = (u8)strtoul(modeStr, NULL, 10);
                        }
                        break;
                    case 3:
                        ReserveaASlot();
                        break;
                    case 4:
                        while (flag1 == 1)
                        {
                            printf("Enter patient ID :");
                            fgets(idStr,10,stdin);
                            idStr[strcspn(idStr,"\n")]='\0';                 //REMOVE NWE LINE 
                            ID = (u16)strtoul(idStr, NULL, 10);    // to conveert string to int 

                            CancleByID(&slot1, ID);

                            printf("Enter '1' to cancle another one '0' to end :");
                            fgets(modeStr, sizeof(modeStr), stdin);
                            modeStr[strcspn(modeStr, "\n")] = '\0'; // إزالة السطر الجديد
                            flag1 = (u8)strtoul(modeStr, NULL, 10);
                        }
                        break;
                    default:
                        printf("Incorrect choice!\n");
                        break;
                    }                                                            //THE END OF ADMIN SWITCH CASE!!!!!!!
                    break;
                }
                else                                                            // IF THE PASSWORD WRONG!!!!!!!!!
                {
                    printf("Wrong password !\nyou have only %d attempts.\n",3-i);
                }
            }
            break;
        case 2:                        //USER MODE !!!!!!!!!!!1
            while (flag1 == 1)
            {
                printf("Enter patient ID :");
                fgets(idStr,10,stdin);
                idStr[strcspn(idStr,"\n")]='\0';                 
                ID = (u16)strtoul(idStr, NULL, 10);    

                Node* last = findNodeByID( head, ID);
                if (last == NULL) printf("There is no patient record with this ID!\n");
                
                if (last != NULL)
                {
                    printInfo(last);
                }
                
                findReservatoinByID(&slot1, ID);

                printf("Enter '1' to another inquiry '0' to end :");
                fgets(modeStr, sizeof(modeStr), stdin);
                modeStr[strcspn(modeStr, "\n")] = '\0'; // إزالة السطر الجديد
                flag1 = (u8)strtoul(modeStr, NULL, 10);
            }
            break;
        case 3:                                                           //TO END PROGRAM
            flag = 0;
            break;
        default:                                                            //INCORRECT CHOICE BETWEEN ADMIN & USER & END PROGRAM!!!!!! 
            printf("Incorrect entery");
            break;
        }
    }
}