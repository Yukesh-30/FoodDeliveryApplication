#include<stdio.h>
#include<string.h>

#define MENU_FILE "menu.csv"
#define RESTAURANTS_FILE "restaurants.csv"
#define CART_FILE "cart.csv"


struct menu2{
    int menu_index;
    char menu_food_name[50];
    float price;
    float rating;
    char type[20];
    char category[20];
}me_details[1000];
int mc=0;
struct cart{
    int item_index;
    char item_name[50];
    float price;
    float quantity;
    float rating;
}cart_details[100];
extern int cart_count=0;

struct reataurants{
    char name[50];
    int menustart;
    int menuend;
    float rating;

}resta[100];
int restaurantCount=0;
void loadMe() {
    FILE *file = fopen(MENU_FILE, "r");
    if (file == NULL) {
        printf("Error in opening the file...!");
    }
    mc=0;
    while (fscanf(file, "%d,%[^,],%f,%f,%[^,],%[^\n]\n",
                  &me_details[mc].menu_index,
                  me_details[mc].menu_food_name,
                  &me_details[mc].price,
                  &me_details[mc].rating,
                  me_details[mc].type,
                  me_details[mc].category) != EOF) {
       mc++;
    }
    fclose(file);
}

void loadca() {
    FILE *file = fopen(CART_FILE, "r");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    cart_count=0;
    while (fscanf(file, "%d,%[^,],%f,%d\n", &cart_details[cart_count].item_index,cart_details[cart_count].item_name, &cart_details[cart_count].price, &cart_details[cart_count].quantity) != EOF){
        cart_count++;
    }
    fclose(file);
}
void loadRe() {
    FILE *file = fopen(RESTAURANTS_FILE, "r");
    if (file == NULL) {
        printf("Error opening restaurants file.\n");
        exit(1);
    }
    restaurantCount=0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d,%d",resta[restaurantCount].name, &resta[restaurantCount].menustart, &resta[restaurantCount].menuend);
        restaurantCount++;
    }


    fclose(file);
}
void collect_rating() {
    for (int i = 0; i < cart_count; i++) {
        printf("\n");
        printf("                                            \033[1;97mEnter the rating for\033[0m \033[1;93m\033[40m%s\033[0m: ", cart_details[i].item_name);
        scanf("%f", &cart_details[i].rating);
    }

    for (int i = 0; i < mc; i++) {
        for (int j = 0; j < cart_count; j++) {
            if (strcmp(me_details[i].menu_food_name, cart_details[j].item_name) == 0) {
                me_details[i].rating = cart_details[j].rating;
                break;  // Found the matching item, no need to continue
            }
        }
    }

}

void updaterestrating() {
    for (int i = 0; i < restaurantCount; i++) {
        int menu_count = resta[i].menuend - resta[i].menustart + 1;
        float sum = 0;

        // Calculate sum of ratings for the restaurant
        for (int j = 0; j < menu_count; j++) {
            sum += me_details[resta[i].menustart + j].rating;
        }
        // Calculate average rating
        if (menu_count > 0) {
            resta[i].rating = sum / menu_count;
        }else {
            resta[i].rating = 0.0;  // Handle division by zero or no menu items
        }
    }

}



void write_r() {
    FILE *file = fopen(RESTAURANTS_FILE, "w");
    if (file == NULL) {
        printf("Error in opening the file %s.\n", RESTAURANTS_FILE);
        return;
    }

    for (int i = 0; i < restaurantCount; i++) {
        fprintf(file, "%s,%d,%d,%.2f\n",
                resta[i].name,
                resta[i].menustart,
                resta[i].menuend,
                resta[i].rating);
    }

    fclose(file);
}

void write_m() {
    FILE *file = fopen(MENU_FILE, "w");
    if (file == NULL) {
        printf("Error in opening the file %s.\n", MENU_FILE);
        return;
    }

    for (int i = 0; i < mc; i++) {
        fprintf(file, "%d,%s,%.2f,%.2f,%s,%s\n",
                me_details[i].menu_index,
                me_details[i].menu_food_name,
                me_details[i].price,
                me_details[i].rating,
                me_details[i].type,
                me_details[i].category);
    }

    fclose(file);
}


/*int main(){

    loadMe();
    loadRe();
    loadca();
    collect_rating();
    updaterestrating();
    write_m();
    write_r();
}*/


