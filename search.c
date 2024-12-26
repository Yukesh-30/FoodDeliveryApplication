#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define REST_FILE "restaurants.csv"
#define MENU_FILE "menu.csv"
#define CART_FILE "cart.csv"

struct hotel1 {
    int hotel_id;
    char name[30];
    int s; // start index of the menu
    int e; // end index of the menu
    float rate;
} hotel_details[100];

int hotel_count = 0;

struct menu5 {
    int id;
    char f_name[30];
    float price;
    float rating;
    char cuisine[30];
    char category[30];
} menu_info[1000];

int m_c = 0;

struct cart5 {
    int index;
    char i_name[30];
    float price;
    int quantity;
} cart_info[60];

int cc = 0;

void r_menu(const char *filename);
void r_rest(const char *filename);
void r_cart(const char *filename);
void write_cart(const char *filename);
void search_and_display_restaurant(char name[30]);
void search_and_display_menu(char name[30]);

/*int main() {
    r_menu(MENU_FILE);
    r_rest(REST_FILE);
    r_cart(CART_FILE);
    int choice;
    char rest_name[30];
    char menu_name[30];

    while (1) {
        printf("\n");
        printf("                            \033[1;93m\033[40m =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-= \033[0m\n");
        printf("\n");
        printf("                                        \033[103m \033[30m SEARCH BAR \033[0m\n");
        printf("\n");
        printf("                            \033[1;93m\033[40m =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-= \033[0m\n");
        printf("\n");
        printf("                                \033[1;97m      1. Search by restaurant.\033[0m\n");
        printf("\n");
        printf("                                \033[1;97m      2. Search by menu items.\033[0m\n");
        printf("\n");
        printf("                                \033[1;97m      3. Back.\033[0m\n");
        printf("\n");
        printf("                            \033[1;93m\033[40m =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-= \033[0m\n");
        printf("\n");
        printf("                               \033[1;97m        Enter the choice: \033[0m");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the buffer
        system("cls");

        if (choice == 1) {
            printf("\n");
            printf("                                       \033[1;97mEnter the restaurant name:\033[0m ");
            fgets(rest_name, sizeof(rest_name), stdin);
            rest_name[strcspn(rest_name, "\n")] = '\0'; // Remove the newline character from fgets
            search_and_display_restaurant(rest_name);
        } else if (choice == 2) {
            printf("\n");
            printf("                                       \033[1;97mEnter the Food name:\033[0m ");
            fgets(menu_name, sizeof(menu_name), stdin);
            menu_name[strcspn(menu_name, "\n")] = '\0'; // Remove the newline character from fgets
            search_and_display_menu(menu_name);
        } else if (choice == 3) {
            break;
        } else {
            printf("                                    \033[101m\033[1;97mInvalid Choice.......\033[0m\n");
        }
    }

    return 0;
}*/

void r_menu(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening the file %s...\n", filename);
        return;
    }
    while (fscanf(file, "%d,%[^,],%f,%f,%[^,],%[^,\n]\n",
                  &menu_info[m_c].id,
                  menu_info[m_c].f_name,
                  &menu_info[m_c].price,
                  &menu_info[m_c].rating,
                  menu_info[m_c].cuisine,
                  menu_info[m_c].category) != EOF) {
        m_c++;
    }
    fclose(file);
}

void r_rest(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening the file %s...\n", filename);
        return;
    }
    while (fscanf(file, "%[^,],%d,%d,%f\n",
                  hotel_details[hotel_count].name,
                  &hotel_details[hotel_count].s,
                  &hotel_details[hotel_count].e,
                  &hotel_details[hotel_count].rate) != EOF) {
        hotel_details[hotel_count].hotel_id = hotel_count; // Use hotel_count as hotel_id
        hotel_count++;
    }
    fclose(file);
}

void r_cart(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening the file %s...\n", filename);
        return;
    }
    while (fscanf(file, "%d,%[^,],%f,%d\n",
                  &cart_info[cc].index,
                  cart_info[cc].i_name,
                  &cart_info[cc].price,
                  &cart_info[cc].quantity) != EOF) {
        cc++;
    }
    fclose(file);
}

void search_and_display_restaurant(char name[30]) {
    printf("\n");
    int flag = 0;
    int st, en;
    int hotel_index = -1; // To store the index of the matched restaurant
    for (int i = 0; i < hotel_count; i++) {
        if (strcasecmp(name, hotel_details[i].name) == 0) { // Case-insensitive comparison
            flag = 1;
            hotel_index = i;
            st = hotel_details[i].s;
            en = hotel_details[i].e;
            break;
        }
    }

    if (flag == 0) {
        printf("                                                    \033[101m\033[1;97mThe restaurant not found....!\033[0m\n");
        system("pause");
        system("cls");
    } else {
        printf("\n");
        printf("\t\t\t\t\t\t\tThe restaurant \033[1;93m\033[40m%s\033[0m is found\n", hotel_details[hotel_index].name);
        printf("\n");
        printf("\t\t\t\t\t\033[1;97mDo you want to see the menu in the %s :\033[0m(\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ", hotel_details[hotel_index].name);
        int c1;
        scanf("%d", &c1);
        system("pause");
        system("cls");
        if (c1 == 1) {
            printf("\n");
            printf("                                              \033[1;97mThe menu for \033[0m\033[1;93m\033[40m%s\033[0m:\n", hotel_details[hotel_index].name);
            printf("\n");
            printf("                                              \033[1;93m\033[40mINDEX -> FOODNAME -> PRICE\033[0m\n");
            for (int i = st-1;i <en; i++) {
                printf("\n");
                printf("                                                    \033[1;97m%d -> %s -> Rs. %.2f\033[0m\n", menu_info[i].id, menu_info[i].f_name, menu_info[i].price);
            }
            printf("\n");
            printf("                                              \033[1;97mDo you want to add the item to the cart? \033[0m(\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ");
            int c2;
            scanf("%d", &c2);

            if (c2 == 1) {
                int id, quantity;
                printf("\n");
                printf("                                              \033[1;97mEnter the id of the food item: \033[0m");
                scanf("%d", &id);
                printf("\n");
                printf("                                              \033[1;97mEnter the quantity: \033[0m");
                scanf("%d", &quantity);

                if (id >= st && id <= en) {
                    cart_info[cc].index = id;
                    strcpy(cart_info[cc].i_name, menu_info[id].f_name);
                    cart_info[cc].price = menu_info[id].price;
                    cart_info[cc].quantity = quantity;
                    cc++;
                    write_cart(CART_FILE);
                    printf("\n");
                    printf("                                                    \033[42m\033[1;97m  ITEM ADDED IN CART \033[0m");
                    printf("\n");
                    system("pause");
                    system("cls");
                } else {
                    printf("                                               \033[101m\033[1;97mInvalid food item ID.\033[0m\n");
                }
                system("pause");
                system("cls");
            } else {
                printf("\n");
                printf("                                                     \033[42m\033[1;97m Shop more......:) \033[0m\n");
                /*system("pause");
                system("cls");*/
            }

        } else {
            printf("\n");
            printf("                                                         \033[42m\033[1;97m Shop More.....:) \033[0m\n");
            system("pause");
            system("cls");
        }
    }
}

void search_and_display_menu(char name[30]) {
    int found = 0;
    int index;
    for (int i = 0; i < m_c; i++) {
        if (strcasecmp(menu_info[i].f_name, name) == 0) { // Case-insensitive comparison
            found = 1;
            index = i;
            break;
        }
    }

    if (found == 0) {
        printf("\n");
        printf("                                                \033[101m\033[1;97m Food not found \033[0m\n");
        printf("\n");
        system("pause");
        system("cls");
    }
    else {
        printf("\n");
        printf("                                            \033[42m\033[1;97m Item found in the menu... \033[0m\n");
        printf("\n");
        printf("                                                       \033[1;93m\033[40m%s -> Rs %.2f\033[0m\n", menu_info[index].f_name, menu_info[index].price);
        printf("\n");
        printf("                                       \033[1;97mDo you want to add the food item to the cart?\033[0m (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ");
        int c3;
        scanf("%d", &c3);

        if (c3 == 1) {
            int quantity;
            printf("\n");
            printf("                                       \033[1;97mEnter the quantity:\033[0m ");
            scanf("%d", &quantity);

            cart_info[cc].index = menu_info[index].id;
            strcpy(cart_info[cc].i_name, menu_info[index].f_name);
            cart_info[cc].price = menu_info[index].price;
            cart_info[cc].quantity = quantity;
            cc++;
            write_cart(CART_FILE);
            printf("\n");
            printf("                                            \033[42m\033[1;97m  ITEM ADDED IN CART \033[0m");
            printf("\n");
            system("pause");
            system("cls");
        } else {
            printf("\n");
            printf("                                                                    \033[42m\033[1;97mShop more......:) \033[0m\n");
            system("pause");
            system("cls");
        }

    }
}

void write_cart(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error in opening the file %s...\n", filename);
        return;
    }
    for (int i = 0; i < cc; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n",
                cart_info[i].index,
                cart_info[i].i_name,
                cart_info[i].price,
                cart_info[i].quantity);
    }
    fclose(file);
}
