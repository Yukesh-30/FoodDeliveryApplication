#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MENU_ITEMS 1000
#define MAX_STRING_LENGTH 100
#define MENU_FILE "menu.csv"
#define CART_FILE "cart.csv"
#define OFFER_FILE "offer.csv"

struct menu1 {
    int menu_index;
    char foodname[MAX_STRING_LENGTH];
    float price;
    float rating;
    char catagory[MAX_STRING_LENGTH];
    char type[MAX_STRING_LENGTH];
} m_details[MAX_MENU_ITEMS];

int menu_item_count = 0;

struct filtered {
    int index;
    char food_name[MAX_STRING_LENGTH];
    float price;
    float rating;
} filter[100];

int filter_count = 0;

struct offer1 {
    int item_index;
    char rest[MAX_STRING_LENGTH];
    char item_name[MAX_STRING_LENGTH];
    float price;
} o_details[100];

int o_count = 0;

// Function Prototypes
void loadMenu1();
void filtermenu(char type[10], float min, float max, float rating, char catagory[50]);
int displayitems();
void sort_based_on_rating();
void add_item_to_cart(const char *filename, int index);
int loadoffer1();
void add_offer_to_cart(const char *filename, int index);

/*int main() {
    int choice;
    loadMenu(MENU_FILE);

    char type[10];
    float min;
    float max;
    float rating;
    char catagory[20];

    printf("Enter the food type (Veg or Non-veg): ");
    scanf("%s", type);
    printf("Enter the Minimum Price: ");
    scanf("%f", &min);
    printf("Enter the Maximum Price: ");
    scanf("%f", &max);
    printf("Enter the Minimum Rating: ");
    scanf("%f", &rating);
    printf("Enter the Category (i.e American/Indian/Italian): ");
    scanf("%s", catagory);

    filtermenu(type, min, max, rating, catagory);
    sort_based_on_rating();
    displayitems();

    while (1) {
        printf("Enter index of the item to be added in the cart (0 to finish): ");
        scanf("%d", &choice);
        if (choice == 0) {
            break;
        } else {
            add_item_to_cart(CART_FILE, choice);
        }
    }

    int offer_choice;
    printf("Are you excited to see the offer available? (1-YES or 0-NO): ");
    scanf("%d", &offer_choice);

    if (offer_choice == 1) {
        loadoffer(OFFER_FILE);
        printf("Do you want to add an offer item to the cart? (1-YES or 0-NO): ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter the index of the offer item to add to the cart: ");
            scanf("%d", &choice);
            add_offer_to_cart(CART_FILE, choice);
        } else {
            printf("Thank you for browsing offers!\n");
        }
    }

    return 0;
}*/

void filtermenu(char type[10], float min, float max, float rating, char catagory[50]) {
    int filter_i = 1;
    for (int i = 0; i < menu_item_count; i++) {
        if(strcmp(strlwr(catagory),strlwr(m_details[i].catagory))==0){
           if (strcmp(type, m_details[i].type) == 0) {
            if (m_details[i].price > min && m_details[i].price < max) {
                if (m_details[i].rating > rating) {
                    filter[filter_count].index = filter_i++;
                    strcpy(filter[filter_count].food_name, m_details[i].foodname);
                    filter[filter_count].price = m_details[i].price;
                    filter[filter_count].rating = m_details[i].rating;
                    filter_count++;
                    }
                }
            }
        }

    }
}

void sort_based_on_rating() {
    for (int i = 0; i < filter_count - 1; i++) {
        for (int j = 0; j < filter_count - i - 1; j++) {
            if (filter[j].rating < filter[j + 1].rating) {
                struct filtered temp = filter[j];
                filter[j] = filter[j + 1];
                filter[j + 1] = temp;
            }
        }
    }
}

int displayitems() {
    if (filter_count!=0){
        printf("\n");
        printf("                                    \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("\n");
        printf("                                       \033[1;97mRecommendation based on your preference:\033[0m\n");
        printf("\n");
        printf("                                    \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("\n");
        printf("                                        \033[1;93m\033[40mINDEX -> FOOD -> PRICE -> RATING\033[0m\n");
        printf("\n");
        for (int i = 0; i < filter_count; i++) {
            printf("                                      \033[1;97m%d  %s  Rs %.2f  %.2f\033[0m\n", i + 1, filter[i].food_name, filter[i].price, filter[i].rating);
        }
        printf("\n");
        printf("                                    \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        return 1;
    }

    if(filter_count==0){
        printf("\n");
        printf("                                           \033[101m\033[1;97mSorry,No item found as per your preference.\033[0m\n");
        printf("\n");
        printf("                                   \033[1;93m\033[40m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");

    return 0;
    }
}

void loadMenu1() {
    FILE *file = fopen(MENU_FILE, "r");
    if (file == NULL) {
        printf("Error in opening the file...!");
        exit(1);
    }

    while (fscanf(file, "%d,%[^,],%f,%f,%[^,],%[^\n]\n",
                  &m_details[menu_item_count].menu_index,
                  m_details[menu_item_count].foodname,
                  &m_details[menu_item_count].price,
                  &m_details[menu_item_count].rating,
                  m_details[menu_item_count].catagory,
                  m_details[menu_item_count].type) != EOF) {
        menu_item_count++;
    }
    fclose(file);
}

int loadoffer1() {
    FILE *file = fopen(OFFER_FILE, "r");
    if (file == NULL) {
        printf("Error in opening the offer file...!\n");
        exit(1);
    }
    o_count = 0;
    while (fscanf(file, "%[^,],%[^,],%f\n",
                  o_details[o_count].rest,
                  o_details[o_count].item_name,
                  &o_details[o_count].price) != EOF) {
        o_details[o_count].item_index = o_count + 1;
                o_count++;

    }
    fclose(file);
    if(o_count!=0){
        printf("\n");
        printf("                                                           \033[1;93m\033[40m================================\033[0m\n");
        printf("\n");
        printf("                                                                  \033[1;97mAvailable Offers:\033[0m\n");
        printf("\n");
        printf("                                                           \033[1;93m\033[40m================================\033[0m\n");
        printf("\n");
        for (int i = 0; i < o_count; i++) {
            printf("\n");
            printf("                                                            \033[1;97m%d - %s - Rs %.2f from %s\033[0m\n",
                   o_details[i].item_index,
                   o_details[i].item_name,
                   o_details[i].price,
                   o_details[i].rest);
        }
        printf("                                                           \033[1;93m\033[40m================================\033[0m\n");
        return 1;
    }
    else{
        printf("\n");
        printf("                                                            \033[101m\033[1;97mSorry! No offers available.\033[0m\n");
        return 0;
    }

}

void add_offer_to_cart(const char *filename, int index) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error in opening the cart file\n");
        exit(1);
    }

    int quantity;
    printf("\n");
    printf("                                               \033[1;97mEnter the quantity:\033[0m ");
    scanf("%d", &quantity);

    printf("%d",ftell(file));
    for (int i = 0; i < o_count; i++) {
        if (o_details[i].item_index == index) {
            fprintf(file, "%d,%s,%.2f,%d\n", i+1 ,o_details[i].item_name, o_details[i].price, quantity);
            printf("                                                        \033[1;97m%d %s (offer) added to cart.\033[0m\n", quantity, o_details[i].item_name);
            fclose(file);
            return;
        }
    }
    printf("\n");
    printf("                                                                    \033[101m\033[1;97mOffer item not found.\033[0m\n");
    fclose(file);
}

void add_item_to_cart(const char *filename, int index) {
    int quantity;
    printf("\n");
    printf("                                                                    \033[1;97mEnter the quantity to be added:\033[0m ");
    scanf("%d", &quantity);
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error in opening the file\n");
        exit(1);
    }
    if (index > 0 && index <= filter_count) {
        fprintf(file, "%d,%s,%.2f,%d\n", index - 1 ,filter[index - 1].food_name, filter[index - 1].price, quantity);
        fflush(file);
        printf("                                                                \033[1;97m%d %s added to cart.\033[0m\n", quantity, filter[index - 1].food_name);
    } else {
        printf("                                                                \033[101m\033[1;97mInvalid index.\033[0m\n");
    }
    fclose(file);
}
