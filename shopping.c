#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "feedback.c"
#include "coupon.c"
#include "reco.c"
#define MAX_ITEMS 1000
#define MAX_NAME_LENGTH 100
#define MENU_FILE "menu.csv"
#define RESTAURANTS_FILE "restaurants.csv"
#define CART_FILE "cart.csv"
#define FILE_NAME "credit.csv"
#define TRANSACTIONS_FILE "transaction.csv"
#define COUPON_CODE "coupon.csv"



typedef struct {
    char user_name[60];
    int user_account_number;
    float credit;
    char password[60];
} UserData;

UserData user_data[100];
int user_count = 0;

struct MenuItem {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
};

struct MenuItem menu[MAX_ITEMS];
int menuSize = 0;

struct Restaurant {
    char name[MAX_NAME_LENGTH];
    int menuStart;
    int menuEnd;
    float ratings;
};

struct Restaurant restaurants[MAX_ITEMS];
int restc = 0;

struct CartItem {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
};

struct CartItem item[60];
int ic;


void readfile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening file.\n");
        exit(1);
    }

    while (fscanf(file, "%[^,],%d,%f,%[^,\n]\n", user_data[user_count].user_name, &user_data[user_count].user_account_number, &user_data[user_count].credit, user_data[user_count].password) != EOF) {
        user_count++;
    }

    fclose(file);
}

bool validate_credit(float credit, int user_acc_num, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (user_data[i].user_account_number == user_acc_num) {
            if (strcmp(user_data[i].password, password) == 0) {
                if (user_data[i].credit < credit) {
                    printf("\n");
                    printf("                                                              \033[101m\033[1;97m  Only Cash on delivery available. Invalid balance...! \033[0m\n");
                    return false;
                } else {
                    user_data[i].credit -= credit;
                    printf("\n");
                    // Update amount in file (will be done after payment confirmation)
                    printf("                                                            \033[42m\033[1;97m  Payment successful. Remaining balance: %.2f \033[0m\n", user_data[i].credit);
                    printf("\n");
                    return true;
                }
            } else {
                printf("\n");
                printf("                                                                           \033[101m\033[1;97m  Invalid password. \033[0m\n");
                return false;
            }
        }
    }
    printf("\n");
    printf("                                                                    \033[101m\033[1;97m Account number not found. \033[0m\n");
    system("pause");
    system("cls");
    return false;
}

void updatecredits(const char *filename) {
    FILE *file = fopen(filename, "w"); // Opening file in write mode to overwrite existing content
    if (file == NULL) {
        printf("Error in opening file.\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s,%d,%.2f,%s\n", user_data[i].user_name, user_data[i].user_account_number, user_data[i].credit, user_data[i].password);
    }
    fclose(file);
}

void loadMenu() {
    FILE *file = fopen(MENU_FILE, "r");
    if (file == NULL) {
        printf("Error opening menu file.\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%f", &menu[menuSize].id, menu[menuSize].name, &menu[menuSize].price);
        menuSize++;
    }

    fclose(file);
}

void loadRestaurants() {
    FILE *file = fopen(RESTAURANTS_FILE, "r");
    if (file == NULL) {
        printf("Error opening restaurants file.\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d,%d,%f",restaurants[restc].name, &restaurants[restc].menuStart, &restaurants[restc].menuEnd,&restaurants[restc].ratings);
        restc++;
    }

    fclose(file);
}

struct MenuItem* findMenuItem(int id) {
    for (int i = 0; i < menuSize; ++i) {
        if (menu[i].id == id) {
            return &menu[i];
        }
    }
    return NULL;
}

void displayRestaurants() {
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                            \033[103m\033[30m  Available Restaurants:  \033[0m\n");
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                           \033[1;93m\033[40m INDEX  ->  RESTAURANT NAME \033[0m\n");
    for (int i = 0; i < restc; ++i) {
        printf("\n");
        printf("                                            \033[1;97m %d.        %s \033[0m\n", i + 1, restaurants[i].name);
    }
}

void displayMenu(int restaurantIndex) {
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                                   \033[103m\033[30m%s    MENU \033[0m\n", restaurants[restaurantIndex].name);
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                            \033[1;93m\033[40m INDEX   ->    FOOD  ->  PRICE \033[0m \n");
    printf("\n");
    for (int i = restaurants[restaurantIndex].menuStart - 1; i < restaurants[restaurantIndex].menuEnd; i++) {
        printf("\n");
        printf("                                            \033[1;97m %d.   %s   -   Rs %.2f \033[0m\n", menu[i].id, menu[i].name, menu[i].price);

    }
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
}

void displayCart() {
    struct CartItem item;
    FILE *file = fopen(CART_FILE, "r");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                                                \033[103m\033[30m Your Cart \033[0m\n");
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                          \033[1;93m\033[40m INDEX  ->  FOOD  ->  QUANTITY  ->  PRICE \033[0m\n");
    printf("\n");
    float totalPrice = 0.0;
    while (fscanf(file, "%d,%[^,],%f,%d\n", &item.id,item.name, &item.price, &item.quantity) != EOF) {
        printf("                                            \033[1;97m %d. %s   -   %d      - Rs. %.2f each \033[0m\n", item.id,item.name, item.quantity, item.price);
        totalPrice += item.price * item.quantity;
    }
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                                \033[1;97m Total Price: \033[0m \033[1;93m\033[40m Rs. Rs%.2f \033[0m\n", totalPrice); // Display total price
    printf("\n");
   printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");

    fclose(file);
}

void addToCart(int itemId, int quantity) {
    struct MenuItem *menu_item = findMenuItem(itemId);
    if (menu_item == NULL) {
        printf("                                            Item not found in the menu.\n");
        return;
    }

    FILE *file = fopen(CART_FILE, "a");
    if (file == NULL) {
        printf("                                            \033[101m\033[1;97m Error opening cart file.\033[0m\n");
        exit(1);
    }

    fprintf(file, "%d,%s,%.2f,%d\n", itemId,menu_item->name, menu_item->price, quantity);
    fclose(file);
    printf("                                                    \033[42m\033[1;97m %d %s added to cart.\033[0m\n", quantity, menu_item->name);
}

void removeFromCart(int itemId) {
    FILE *file = fopen(CART_FILE, "r");
    if (file == NULL) {
        printf("                                            \033[101m\033[1;97mError opening cart file.\033[0m\n");
        return;
    }
    ic = 0;
    while (fscanf(file, "%d,%99[^,],%f,%d\n", &item[ic].id, item[ic].name, &item[ic].price, &item[ic].quantity) != EOF) {
        ic++;
    }
    fclose(file);

    // Remove the item by shifting elements
    bool itemFound = false;
    for (int i = 0; i < ic; i++) {
        if (item[i].id == itemId) {
            itemFound = true;
            for (int j = i; j < ic - 1; j++) {
                item[j] = item[j + 1];
            }
            ic--;
            break;
        }
    }

    if (!itemFound) {
        printf("\n");
        printf("                                                              \033[101m\033[1;97m  Item not found in cart. \033[0m\n");
        return;
    }


    file = fopen(CART_FILE, "w");
    if (file == NULL) {
        printf("                                            \033[101m\033[1;97mError opening cart file for writing.\033[0m\n");
        return;
    }

    for (int i = 0; i < ic; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n", item[i].id, item[i].name, item[i].price, item[i].quantity);
    }
    fclose(file);

    printf("\n");
    printf("                                                              \033[42m\033[1;97m  Item removed from the cart. \033[0m\n");
}



void updateQuantity(int itemId, int newQuantity) {
    FILE *file = fopen(CART_FILE, "r");
    if (file == NULL) {
        printf("Error opening cart file.\n");
        return;
    }
    ic = 0;
    while (fscanf(file, "%d,%99[^,],%f,%d\n", &item[ic].id, item[ic].name, &item[ic].price, &item[ic].quantity) != EOF) {
        ic++;
    }
    for(int i=0;i<ic;i++){
        if(item[i].id==itemId){
            item[i].quantity=newQuantity;
        }
    }
    file = fopen(CART_FILE, "w");
    if (file == NULL) {
        printf("                                            \033[101m\033[1;97mError opening cart file for writing.\033[0m\n");
        return;
    }

    for (int i = 0; i < ic; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n", item[i].id, item[i].name, item[i].price, item[i].quantity);
    }
    fclose(file);
    printf("\n");
    printf("                                                              \033[42m\033[1;97m  Quantity updated in the cart. \033[0m\n");
}

void saveTransaction(const char *items) {
    FILE *file = fopen(TRANSACTIONS_FILE, "a");
    if (file == NULL) {
        printf("Error opening transactions file.\n");
        return;
    }

    fprintf(file, "%s\n", items);
    fclose(file);
}

void placeOrder() {
    displayCart();

    float totalPrice = 0;
    FILE *file = fopen(CART_FILE, "r");
    if (file == NULL) {
        printf("\n");
        printf("                                                                        \033[101m\033[1;97m Cart is empty. \033[0m\n");
        return;
    }
    struct CartItem item;
    char transactionItems[500] = "";
    bool firstItem = true;
    int c_count=0;
    while (fscanf(file, "%d,%[^,],%f,%d\n", &item.id,item.name, &item.price, &item.quantity) != EOF) {
        float itemTotalPrice = item.price * item.quantity;
        totalPrice += itemTotalPrice;
        if (!firstItem) {
            strcat(transactionItems, ",");
        }
        strcat(transactionItems, item.name);
        firstItem = false;
        c_count++;
    }
    fclose(file);
    int empty;
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                                         \033[103m\033[30m READY TO FEAST ? ORDER NOW \033[0m \n");
    printf("\n");
    printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=\033[0m\n");
    printf("\n");
    printf("                                          \033[1;97mDo you have any coupon code to apply?\033[0m(\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No) :");
    scanf("%d",&empty);
    printf("\n");
    if(empty==1){
        char code[10];
        float total_amount;

        readcoupons(COUPON_CODE);

        printf("                                        \033[1;97mEnter the coupon code:\033[0m");
        scanf("%s", code);
        printf("\n");
        if (validate_coupon(code)) {
            calculate_amount(code,&totalPrice);

            update_coupon_file(COUPON_CODE);
        } else {
            printf("\n");
            printf("                                                    \033[101m\033[1;97m  Invalid Coupon: %s \033[0m\n", code);
        }
    }


    //printf("Total Price: $%.2f\n", totalPrice);
    if(c_count!=0){
        char confirm;
        int c;
        printf("                                         \033[1;93m\033[40m To Taste the feast  =>\033[0m Confirm order (\033[1;32mY\033[0m-Yes/\033[1;31mN\033[0m-No): ");
        scanf(" %c", &confirm);
        printf("\n");

        if (confirm == 'Y' || confirm == 'y') {
            int account_number;
            char password[10];
            printf("                                         \033[1;97mDo you want to rate the food items\033[0m (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No) :");
            scanf("%d",&c);
            printf("\n");
            if(c==1){
                loadMe();
                loadRe();
                loadca();
                collect_rating();
                updaterestrating();
                write_m();

                write_r();

            }
            system("cls");
            printf("\n");
            printf("                                         \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=\033[0m\n");
            printf("\n");
            printf("                                                             \033[103m\033[30m ACCOUNT DETAILS \033[0m  \n");
            printf("\n");
            printf("                                         \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=\033[0m\n");
            printf("\n");
            printf("\n");
            printf("                                                       \033[1;97mEnter your Account number: \033[0m ");
            scanf("%d", &account_number);
            printf("\n");
            printf("                                                       \033[1;97mEnter the Password: \033[0m ");
            scanf("%s", password);
            printf("\n");
            readcart(CART_FILE);
            recommend recommended_list[10];
            read_transactions(TRANSACTIONS_FILE);
            ItemSupport item_supports[MAX_ITEMS] = {0};
            int num_items = 0;



            generate_frequent_itemsets(item_supports, &num_items);
            generate_association_rules(item_supports, num_items);
            char cart[MAX_ITEMS][MAX_ITEM_NAME_LEN];
            for(int i=0;i<c_c;i++){
            strcpy(cart[i],c_items[i].item_name);
            }
                // Example cart items
                //const char cart[MAX_ITEMS][MAX_ITEM_NAME_LEN] = {"milk", "bread"};
                //int cart_size = 2;

            recommend_items(item_supports, num_items, cart, c_c,recommended_list);
            if (validate_credit(totalPrice, account_number, password)) {
                updatecredits(FILE_NAME); // Update credits after payment confirmation

                file = fopen(CART_FILE, "w");
                if (file == NULL) {
                    printf("Error clearing cart.\n");
                    return;
                }
                fclose(file);

                saveTransaction(transactionItems); // Save transaction items
                printf("\n");
                printf("                                                      \033[42m \033[1;97m  Order placed successfully.\033[0m\n");
                cart_count=0;

                }

        } else {
            printf("\n");
            printf("                                                           \033[101m\033[1;97m  Order canceled.\033[0m\n");
            }
        }
    else{
        printf("\n");
        printf("                                                               \033[101m\033[1;97m Your Cart is empty.\033[0m");
    }


}



/*int main() {
    readfile(FILE_NAME);
    loadMenu();
    loadRestaurants();
    int restaurantIndex;
    int itemId, quantity;
    int choice;

    while (1) {
        printf("              DELIVER EASE              \n");
        printf("========================================\n");
        printf("1. TO VIEW THE RESTAURANTS.\n");
        printf("2. TO VIEW THE MENU.\n");
        printf("3. TO VIEW CART.\n");
        printf("4. TO ADD ITEM IN CART.\n");
        printf("5. TO REMOVE ITEM FROM THE CART.\n");
        printf("6. TO UPDATE QUANTITY IN THE CART.\n");
        printf("7. TO PLACE THE ORDER.\n");
        printf("8. Exit\n");
        printf("=========================================\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayRestaurants();
                break;
            case 2:
                printf("Enter the index of the restaurant you want to view menu for: ");
                scanf("%d", &restaurantIndex);
                if (restaurantIndex >= 1 && restaurantIndex <= restaurantCount) {
                    displayMenu(restaurantIndex - 1);
                } else {
                    printf("Invalid restaurant index.\n");
                }
                break;
            case 3:
                displayCart();
                break;
            case 4:
                printf("Enter the ID of the item you want to add to cart: ");
                scanf("%d", &itemId);
                printf("Enter the quantity: ");
                scanf("%d", &quantity);
                addToCart(itemId, quantity);
                break;
            case 5:
                printf("Enter the ID of the item you want to remove from the cart: ");
                scanf("%d", &itemId);
                removeFromCart(itemId);
                break;
            case 6:
                printf("Enter the ID of the item you want to update the quantity for: ");
                scanf("%d", &itemId);
                printf("Enter the new quantity: ");
                scanf("%d", &quantity);
                updateQuantity(itemId, quantity);
                break;
            case 7:
                placeOrder();
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}*/

