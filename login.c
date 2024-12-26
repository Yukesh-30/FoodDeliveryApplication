#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "about.c"
#define LOGIN_FILE "login.csv"

// Define the structure for customer details
struct customer {
    char name[100];
    char phno[12];
    char password[9];
    struct address {
        int door_no;
        char street[100];
        char area[100];
        char district[100];
        char pincode[7];
    } address_detail;
};

// Declare an array to store customer information
struct customer a[100];
int customerCount = 0; // Global variable to keep track of the number of customers

// Function declarations
void signUp();
void login();
void saveToFile(struct customer *cust);
void loadFromFile();

// Main function
/*void main() {
    int choice;

    printf("1. SIGN UP\n");
    printf("2. LOGIN\n");
    printf("Select your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            signUp();
            break;
        case 2:
            // Load customer data before login
            loadFromFile();
            login();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}*/

void signUp() {
    int F = 1;
    int T = 1;
    printf("                                            \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                                            \033[103m\033[30mSIGN UP DETAILS\033[0m       \n");
    printf("\n");
    printf("                                            \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                             \033[1;97mEnter username:\033[0m ");
    scanf(" %[^\n]", a[customerCount].name);
    printf("\n");

    while (F != 0) {
        printf("\n");
        printf("                                             \033[1;97mEnter the password pin (should contain \033[1;93m\033[40m8\033[0m-digit number):\033[0m ");
        scanf("%s", a[customerCount].password);
        printf("\n");
        printf("                                             \033[1;97mEnter your password pin for confirmation:\033[0m ");
        char duplicate_password[9];
        scanf("%s", duplicate_password);
        printf("\n");
        if ((strlen(a[customerCount].password) == 8) && (strcmp(a[customerCount].password, duplicate_password) == 0)) {
            printf("\n                                                   \033[42m\033[1;97m Password saved successfully \033[0m     \n\n\n");
            system("pause");
            system("cls");
            F = 0;
        } else {
            printf("                                                      \033[101m\033[1;97m Sorry, invalid password. Enter the password again. \033[0m            \n");
            F = 1;
            system("pause");
        }
    }
    printf("                                                \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                                         \033[103m\033[30m PERSONAL DETAILS \033[0m\n");
    printf("\n");
    printf("                                                \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    while (T != 0) {
        printf("                                                 \033[1;97m Enter your phone number: \033[0m");
        scanf("%s", a[customerCount].phno);
        printf("\n");

        if (strlen(a[customerCount].phno) == 10) {
            printf("                                                 \033[1;97m Enter door number: \033[0m ");
            scanf("%d", &a[customerCount].address_detail.door_no);
            printf("\n");
            printf("                                                 \033[1;97m Enter your street: \033[0m ");
            scanf(" %[^\n]", a[customerCount].address_detail.street);
            printf("\n");
            printf("                                                 \033[1;97m Enter your  area: \033[0m ");
            scanf(" %[^\n]", a[customerCount].address_detail.area);
            printf("\n");
            printf("                                                 \033[1;97m Enter your district: \033[0m");
            scanf("%s", a[customerCount].address_detail.district);
            printf("\n");

            while (T != 0) {
                printf("                                                 \033[1;97m Enter pincode: \033[0m");
                scanf("%s", a[customerCount].address_detail.pincode);

                if (strlen(a[customerCount].address_detail.pincode) == 6) {
                    printf("\n");
                    printf("\n");
                    printf("                                                        \033[42m\033[1;97m Thank you \033[0m\n");
                    T = 0;
                    printf("\n");
                    printf("                                                \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");

                } else {
                    printf("\n");
                    printf("                                                        \033[101m\033[1;97m Invalid pincode! \033[0m\n");
                    T = 1;
                }
            }
            system("pause");
            system("cls");
            //new code
            about();
            int m;
            while(1){
                printf("                                        \033[1;97mDo you Accept the terms and condition to enter the app (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No):\033[0m");
                scanf("%d",&m);
                if(m==1){
                    printf("\n");
                    printf("                                            \033[1;93m\033[40mHere you go... !\033[0m");
                    break;
                    system("pause");
                    system("cls");
                }
            }

            // Save the customer details to the file
            saveToFile(&a[customerCount]);
            customerCount++;
        } else {
            printf("\n");
            printf("                                                    \033[101m\033[1;97m Invalid phone number! \033[0m \n");
            printf("\n");
            T = 1;
        }
    }
}

// Function to save customer details to a file
void saveToFile(struct customer *cust) {
    FILE *fp;
    fp = fopen(LOGIN_FILE, "a");

    fprintf(fp, "%s,%s,%s,%d,%s,%s,%s,%s\n",
            cust->name,
            cust->password,
            cust->phno,
            cust->address_detail.door_no,
            cust->address_detail.street,
            cust->address_detail.area,
            cust->address_detail.district,
            cust->address_detail.pincode);

    fclose(fp);
}

// Function to load customer details from the file
void loadFromFile() {
    FILE *fp;
    char buffer[512]; // Buffer to hold each line
    int count = 0;

    fp = fopen(LOGIN_FILE, "r");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        sscanf(buffer, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%s",
               a[count].name,
               a[count].password,
               a[count].phno,
               &a[count].address_detail.door_no,
               a[count].address_detail.street,
               a[count].address_detail.area,
               a[count].address_detail.district,
               a[count].address_detail.pincode);
        count++;
    }

    customerCount = count;
    fclose(fp);
}

// Function for the login process
void login() {
    char name[20];
    char user_password[20];
    int found = 0;

    while (1) {
        printf("\n");
        printf("                                             \033[1;97m Enter username: \033[0m");
        scanf("%s", name);

        // Check if the user exists
        found = 0;
        for (int i = 0; i < customerCount; i++) {
            if (strcmp(a[i].name, name) == 0) {
                found = 1;
                printf("\n");
                // User exists, check the password
                printf("                                             \033[1;97m Enter password pin: \033[0m");
                scanf("%s", user_password);

                if (strcmp(a[i].password, user_password) == 0) {
                    printf("\n");
                    printf("                                                    \033[42m\033[1;97m Login Successful...! \033[0m\n");
                    printf("\n");
                    system("pause");
                    return; // Exit the function after successful login
                } else {
                    printf("\n");
                    printf("                                                    \033[101m\033[1;97m Incorrect password. Please try again. \033[0m\n");
                    printf("\n");
                    break; // Exit the for loop and retry password
                }
            }
        }

        if (!found) {
            printf("\n");
            printf("                                             \033[101m\033[1;97m User name doesn't exist. Please try again. \033[0m\n");
        }

        /*char choice;
        printf("\n");
        printf("                                             \033[1;97m Do you want to try again? (y/n): \033[30m");
        scanf(" %c", &choice); // Space before %c to ignore any previous newline character

        if (choice == 'n' || choice == 'N') {
            printf("                                            \033[104m\033[1;97m Exiting login... \033[0m\n");
            return; // Exit the function
        }*/
    }
}
