
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// MACROS
#define LOGIN_FILE "adminlogin.csv"
#define MENU_FILE "menu.csv"
#define RESTAURANTS_FILE "restaurants.csv"
#define OFFER_FILE "offer.csv"
#define MAX_RESTAURANTS 100
#define MAX_STRING_SIZE 20

// Structure details
struct admin {
    int restaurant_id;
    char user_name[20];
    char password[20];
    char restaurant_name[30];
};

struct hotel {
    char restaurant_name[30];
    int menu_start;
    int menu_end;
    float rating;
};

struct menu {
    int menu_index;
    char menu_item[30];
    float price;
    float rating;
    char type[20];
    char category[10];
};

struct offer {
    char rest_name[20];
    char item_name[30];
    float discounted_price;
} offer_details[20];

int offer_count = 0;

// Global variables
struct admin admin_details[100];
int admin_count = 0;

struct hotel restaurant[100];
int restaurant_count = 0;

struct menu menu_details[1000];
int menu_count = 0;

// Function prototypes
void loadlogin(const char *filename);
void read_restaurants(const char *filename);
void readmenu(const char *filename);
void add_item_to_menu(char rest_name[20], char item_name[30], float price, float rating, char type[20], char category[10]);
void delete_item_from_menu(char rest_name[20], char item_name[30]);
void update_price(char rest_name[20], char item_name[30], float price);
void write_rest_file(const char *filename);
void update_offer_details(char rest[20], char item[30], float percent);
void delete_offer(char rest[20], char item[30]);
void write_offerdetails(char *filename, char rest[20], char foodname[30], float price);
void write_menu(const char *filename);
void show_menu(char rest_name[30]);

/*int main() {
    char username[MAX_STRING_SIZE];
    char password[MAX_STRING_SIZE];
    char restaurant_name[MAX_STRING_SIZE];
    char item_name[MAX_STRING_SIZE];
    char type[MAX_STRING_SIZE];
    char category[MAX_STRING_SIZE];
    float price;
    float percent;
    int choice;
    int flag = 0;
    loadlogin(LOGIN_FILE);
    readmenu(MENU_FILE);
    read_restaurants(RESTAURANTS_FILE);

    do {
        printf("Enter the Username: ");
        scanf("%19s", username);  // Limiting input size to prevent overflow
        printf("Enter the password: ");
        scanf("%19s", password);  // Limiting input size to prevent overflow

        for (int i = 0; i < admin_count; i++) {
            if (strcmp(admin_details[i].user_name, username) == 0 && strcmp(admin_details[i].password, password) == 0) {
                printf("Login Successful...\n");

                do {
                    printf("        ADMIN's PAGE      \n");
                    printf("=============================\n");
                    printf("1. ADD ITEM IN MENU.\n");
                    printf("2. DELETE ITEM FROM MENU.\n");
                    printf("3. UPDATE PRICE IN THE MENU.\n");
                    printf("4. UPDATE OFFER DETAILS.\n");
                    printf("5. DELETE THE OFFER.\n");
                    printf("6. SHOW MENU.\n");
                    printf("7. EXIT\n");
                    printf("=============================\n");
                    printf("Enter your Choice: ");
                    if (scanf("%d", &choice) != 1) {
                        printf("Invalid input. Please enter a number.\n");
                        while (getchar() != '\n');  // Clear input buffer
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            printf("Enter the Restaurant name: ");
                            scanf(" %[^\n]%*c", restaurant_name);
                            printf("Enter the food name: ");
                            scanf(" %[^\n]%*c", item_name);
                            printf("Enter the price of the food item: ");
                            while (scanf("%f", &price) != 1 || price < 0) {
                                printf("Invalid price. Please enter a positive number: ");
                                while (getchar() != '\n');  // Clear input buffer
                            }
                            printf("Enter the type of the food (e.g., American, Italian): ");
                            scanf("%19s", type);
                            printf("Enter the Category of the food (e.g., Veg, Non-Veg): ");
                            scanf("%9s", category);
                            add_item_to_menu(restaurant_name, item_name, price, 0, type, category);
                            break;

                        case 2:
                            printf("Enter the Restaurant name: ");
                            scanf(" %[^\n]%*c", restaurant_name);
                            printf("Enter the Food name: ");
                            scanf(" %[^\n]%*c", item_name);
                            delete_item_from_menu(restaurant_name, item_name);
                            break;

                        case 3:
                            printf("Enter the Restaurant name: ");
                            scanf(" %[^\n]%*c", restaurant_name);
                            printf("Enter the item name: ");
                            scanf(" %[^\n]%*c", item_name);
                            printf("Enter the price to be updated: ");
                            while (scanf("%f", &price) != 1 || price < 0) {
                                printf("Invalid price. Please enter a positive number: ");
                                while (getchar() != '\n');  // Clear input buffer
                            }
                            update_price(restaurant_name, item_name, price);
                            break;

                        case 4:
                            printf("Enter the restaurant name: ");
                            scanf(" %[^\n]%*c", restaurant_name);
                            printf("Enter the food name: ");
                            scanf(" %[^\n]%*c", item_name);
                            printf("Enter the percentage of discount: ");
                            while (scanf("%f", &percent) != 1 || percent < 0 || percent > 100) {
                                printf("Invalid percentage. Please enter a number between 0 and 100: ");
                                while (getchar() != '\n');  // Clear input buffer
                            }
                            update_offer_details(restaurant_name, item_name, percent);
                            break;

                        case 5:
                            printf("Enter the restaurant name: ");
                            scanf(" %[^\n]%*c", restaurant_name);
                            printf("Enter the food name: ");
                            scanf(" %[^\n]%*c", item_name);
                            delete_offer(restaurant_name, item_name);
                            break;

                        case 6:
                            printf("Enter the Restaurant name: ");
                            scanf(" %[^\n]%*c", restaurant_name);
                            show_menu(restaurant_name);
                            break;

                        case 7:
                            printf("Exiting admin menu...\n");
                            break;

                        default:
                            printf("Invalid choice. Please select a valid option.\n");
                            break;
                    }
                } while (choice != 7);

                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            printf("Invalid username or password. Please try again.\n");
        }
    } while (flag == 0);

    return 0;
}*/

void loadlogin(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error in opening the file\n");
        return;
    }
    admin_count = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^\n]", &admin_details[admin_count].restaurant_id,
                  admin_details[admin_count].user_name,
                  admin_details[admin_count].password,
                  admin_details[admin_count].restaurant_name) != EOF) {
        admin_count++;
    }
    fclose(file);
}

void read_restaurants(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    restaurant_count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (restaurant_count >= MAX_RESTAURANTS) {
            printf("Reached maximum restaurant limit of %d\n", MAX_RESTAURANTS);
            break;
        }
        char *token = strtok(line, ",");

        strncpy(restaurant[restaurant_count].restaurant_name, token, 19);
        restaurant[restaurant_count].restaurant_name[19] = '\0'; // Ensure null-terminated

        token = strtok(NULL, ",");
        restaurant[restaurant_count].menu_start = atoi(token);

        token = strtok(NULL, ",");
        restaurant[restaurant_count].menu_end = atoi(token);

        token=strtok(NULL,",");
        restaurant[restaurant_count].rating = atof(token);

        restaurant_count++;
    }
    fclose(file);
}

void readmenu(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error in opening the file...\n");
        return;
    }
    menu_count = 0;
    while (fscanf(file, "%d,%[^,],%f,%f,%[^,],%[^\n]",
                  &menu_details[menu_count].menu_index,
                  menu_details[menu_count].menu_item,
                  &menu_details[menu_count].price,
                  &menu_details[menu_count].rating,
                  menu_details[menu_count].type,
                  menu_details[menu_count].category) != EOF) {
        menu_count++;
    }
    fclose(file);
}

void write_rest_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    for (int i = 0; i < restaurant_count; i++) {
        fprintf(file, "%s,%d,%d,%f\n", restaurant[i].restaurant_name, restaurant[i].menu_start, restaurant[i].menu_end,restaurant[i].rating);
    }
    fclose(file);
}

void write_menu(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    for (int i = 0; i < menu_count; i++) {
        fprintf(file, "%d,%s,%.2f,%.2f,%s,%s\n",
                menu_details[i].menu_index,
                menu_details[i].menu_item,
                menu_details[i].price,
                menu_details[i].rating,
                menu_details[i].type,
                menu_details[i].category);
    }
    fclose(file);
}
void add_item_to_menu(char rest_name[20], char item_name[30], float price, float rating, char type[20], char category[10]) {
    int rest_index = -1;

    // Find the restaurant index by name
    for (int i = 0; i < restaurant_count; i++) {
        if (strcmp(restaurant[i].restaurant_name, rest_name) == 0) {
            rest_index = i;
            break;
        }
    }

    if (rest_index == -1) {
        printf("                                                \033[101m\033[1;97m  Restaurant not found.  \033[0m\n");
        return;
    }

    int menu_start = restaurant[rest_index].menu_start;
    int menu_end = restaurant[rest_index].menu_end;

    // Shift menu items to the right to make space for the new item
    for (int i = menu_count; i > menu_end; i--) {
        menu_details[i] = menu_details[i - 1];
        menu_details[i].menu_index = i + 1;
    }

    // Insert new item
    menu_details[menu_end].menu_index = menu_end + 1;
    strcpy(menu_details[menu_end].menu_item, item_name);
    menu_details[menu_end].price = price;
    menu_details[menu_end].rating = rating;
    strcpy(menu_details[menu_end].type, type);
    strcpy(menu_details[menu_end].category, category);

    // Update current restaurant's menu_end
    restaurant[rest_index].menu_end++;

    // Adjust the start and end indices of subsequent restaurants
    for (int i = rest_index + 1; i < restaurant_count; i++) {
        restaurant[i].menu_start++;
        restaurant[i].menu_end++;
    }

    menu_count++; // Increment total menu count

    // Persist changes to files
    write_rest_file(RESTAURANTS_FILE);
    write_menu(MENU_FILE);
    printf("\n");
    printf("                                                \033[42m\033[1;97m  Item added successfully.  \033[0m\n");
}

void delete_item_from_menu(char rest_name[20], char item_name[30]) {
    int rest_index = -1;

    // Find the restaurant index by name
    for (int i = 0; i < restaurant_count; i++) {
        if (strcmp(restaurant[i].restaurant_name, rest_name) == 0) {
            rest_index = i;
            break;
        }
    }

    if (rest_index == -1) {
        printf("                                            \033[101m\033[1;97m  Restaurant not found.  \033[0m\n");
        return;
    }

    int menu_start = restaurant[rest_index].menu_start;
    int menu_end = restaurant[rest_index].menu_end;

    int item_index = -1;
    // Find the index of the item to be deleted
    for (int i = menu_start - 1; i < menu_end; i++) {
        if (strcmp(menu_details[i].menu_item, item_name) == 0) {
            item_index = i;
            break;
        }
    }

    if (item_index == -1) {
        printf("                                            \033[101m\033[1;97m  Item not found in the menu.  \033[0m\n");
        return;
    }

    // Shift menu items to the left to fill the gap
    for (int i = item_index; i < menu_count - 1; i++) {
        menu_details[i] = menu_details[i + 1];
        menu_details[i].menu_index = i + 1;
    }
    menu_count--; // Decrement total menu count

    // Update current restaurant's menu_end
    restaurant[rest_index].menu_end--;

    // Adjust the start and end indices of subsequent restaurants
    for (int i = rest_index + 1; i < restaurant_count; i++) {
        restaurant[i].menu_start--;
        restaurant[i].menu_end--;
    }

    // Persist changes to files
    write_rest_file(RESTAURANTS_FILE);
    write_menu(MENU_FILE);

    printf("                                                \033[42m\033[1;97m  Item deleted successfully.  \033[0m\n");
}
void update_price(char rest_name[20], char item_name[30], float price) {
    int st=0;
    int end=0;
    for(int i=0;i<restaurant_count;i++){
        if(strcmp(tolower(restaurant[i].restaurant_name),tolower(rest_name))==0){
            st=restaurant[i].menu_start;
            end=restaurant[i].menu_end;
        }
    }
    int found=0;
    for(int i=0;i<menu_count;i++){
        if(strcmp(tolower(menu_details[i].menu_item),tolower(item_name))==0){
            if(menu_details[i].menu_index>=st && menu_details[i].menu_index<=end){
                menu_details[i].price=price;
                found=1;
            }
        }
    }
    if(found==1){
        write_menu(MENU_FILE);
        printf("\n");
        printf("\n");
        printf("                                              \033[42m\033[1;97m The price updated successfully.. \033[0m\n");
    }
    else{
        printf("                                              \033[101m\033[1;97m  Item not found!  \033[0m\n");
    }
}



void update_offer_details(char rest[20], char item[30], float percent) {
    float original_price;
    for (int i = 0; i < menu_count; i++){
        if (strcmp(menu_details[i].menu_item, item) == 0) {
            original_price = menu_details[i].price;
            break;
        }
    }

    float new_price = original_price - (original_price * percent / 100);
    write_offerdetails(OFFER_FILE, rest, item, new_price);
    printf("\n");
    printf("                                                   \033[42m\033[1;97m  The offer details updated.  \033[0m\n");
}

void delete_offer(char rest[20], char item[30]) {
    int index = -1;
    for (int i = 0; i < offer_count; i++) {
        if (strcmp(offer_details[i].rest_name, rest) == 0 && strcmp(offer_details[i].item_name, item) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n");
        printf("\n");
        printf("                                                \033[101m\033[1;97m  Offer not found.  \033[0m\n");
        return;
    }

    for (int i = index; i < offer_count - 1; i++) {
        offer_details[i] = offer_details[i + 1];
    }
    offer_count--;

    FILE *file = fopen(OFFER_FILE, "w");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    if (offer_count > 0){
    for (int i = 0; i < offer_count; i++) {
        fprintf(file, "%s,%s,%.2f\n", offer_details[i].rest_name, offer_details[i].item_name, offer_details[i].discounted_price);
    }
    }
    fclose(file);
    printf("\n");

    printf("                                    `               \033[42m\033[1;97m  Offer deleted successfully.  \033[0m\n");
}

void write_offerdetails(char *filename, char rest[20], char foodname[30], float price) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    fprintf(file, "%s,%s,%.2f\n", rest, foodname, price);
    strcpy(offer_details[offer_count].rest_name, rest);
    strcpy(offer_details[offer_count].item_name, foodname);
    offer_details[offer_count].discounted_price = price;
    offer_count++;

    fclose(file);
}

void show_menu(char rest_name[20]) {
    int rest_index = -1;

    for (int i = 0; i < restaurant_count; i++) {
        if (strcmp(restaurant[i].restaurant_name, rest_name) == 0) {
            rest_index = i;
            break;
        }
    }

    if (rest_index == -1) {
        printf("                                                \033[101m\033[1;97m  Restaurant not found.  \033[0m\n");
        return;
    }

    int menu_start = restaurant[rest_index].menu_start;
    int menu_end = restaurant[rest_index].menu_end;
    printf("\n");
    printf("                                          \033[1;97mMenu for\033[0m \033[1;93m\033[40m%s\033[0m:\n", rest_name);
    printf("\n");
    printf("\n");
    printf("                                              \033[1;93m\033[40mINDEX -> FOOD -> PRICE -> RATING -> TYPE -> CATAGORY \033[0m");
    printf("\n");
    for (int i = menu_start - 1; i < menu_end; i++) {
        printf("                                                  \033[1;97m%d. %s -  Rs %.2f - %.1f stars - %s - %s\033[0m\n",
               menu_details[i].menu_index,
               menu_details[i].menu_item,
               menu_details[i].price,
               menu_details[i].rating,
               menu_details[i].type,
               menu_details[i].category);
        printf("\n");
    }


}
