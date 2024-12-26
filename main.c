#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "login.c"
#include "admin.c"
#include "shopping.c"
#include "filter.c"
#include "address.c"
#include "search.c"


int main(){
    loadCart();
    int choice;
    do{
        printf("                                        \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m     \n");
        printf("\n");
        printf("                                                \033[30m\033[103m  DELIVER EASE \033[0m   \n");
        printf("\n");
        printf("                                        \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m     \n");
        printf("\n");
        printf("                                        \033[97m1.CUSTOMER PAGE.\033[0m            \n");
        printf("\n");
        printf("                                        \033[97m2.ADMIN PAGE.\033[0m               \n");
        printf("\n");
        printf("                                        \033[97m3.EXIT.\033[0m                    \n");
        printf("\n");
        printf("                                        \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m     \n");
        printf("\n");
        printf("                                        \033[97mEnter the choice :\033[0m");
        scanf("%d",&choice);

        if(choice==1){
            //CUSTOMER
            system("cls");
            int l_choice;
            printf("                                        \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m     \n");
            printf("\n");
            printf("                                                 \033[30m\033[103m CUSTOMER'S PAGE \033[0m   \n");
            printf("\n");
            printf("                                        \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m     \n");
            printf("\n");
            printf("                                           \033[97m1. SIGN UP.\033[0m\n");
            printf("\n");
            printf("                                           \033[97m2. LOGIN.\033[0m\n");
            printf("\n");
            printf("                                           \033[97m3. BACK.\033[0m\n");
            printf("\n");
            printf("                                        \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m     \n");
            printf("\n");
            printf("                                           \033[97mEnter your choice:\033[0m ");
            scanf("%d", &l_choice);
            int log_flag= 0;
            switch (l_choice) {
            case 1:
                system("cls");
                signUp();
                system("pause");
                system("cls");
                printf("                                       \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                printf("\n");
                printf("                                                \033[103m\033[30mLOGIN TO GET IN-TO THE APP\033[0m    \n");
                printf("\n");
                printf("                                       \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                printf("\n");
                loadFromFile();
                login();
                log_flag = 1;
                system("cls");


                break;
            case 2:
                system("cls");
            // Load customer data before login
                loadFromFile();
                printf("                                       \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                printf("\n");
                printf("                                                \033[103m\033[30mLOGIN TO GET IN-TO THE APP\033[0m    \n");
                printf("\n");
                printf("                                       \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                printf("\n");
                login();
                log_flag = 1;
                system("cls");

                break;
            case 3:
                break;
            default:
                printf("                                                     Invalid choice.\n");
                break;
            }
        int l;
        if(log_flag){
                while(1){
                    printf("\n");
                    printf("                                      \033[1;93m\033[40m============================================\033[0m\n");
                    printf("\n");
                    printf("                                                 \033[103m\033[30m WELCOME TO DELIVER EASE \033[0m        \n");
                    printf("\n");
                    printf("                                      \033[1;93m\033[40m============================================\033[0m\n");
                    printf("\n");
                    printf("                                       \033[1;97m 1.TO SEE THE NEARBY RESTAUARANT BY AREAS. \033[0m\n");
                    printf("\n");
                    printf("                                       \033[1;97m 2.TO NAVIGATE TO SHOPPING PAGE. \033[0m\n");
                    printf("\n");
                    printf("                                        \033[1;97m3.TO OPEN SEARCH BAR.\033[0m\n");
                    printf("\n");
                    printf("                                       \033[1;97m 4.BACK. \033[0m\n");
                    printf("\n");
                    printf("                                      \033[1;93m\033[40m============================================\033[0m\n");
                    printf("\n");
                    printf("                                        \033[1;97mEnter the choice : \033[0m");
                    scanf("%d",&l);
                    system("cls");
                    if(l==1){
                        loadarea();
                        loadrestaurant();
                        load_menu_1();
                         // Load cart from file

                        // Use loaded area names in the areas array
                        char areas[V][20];
                        for (int i = 0; i < area_count; i++) {
                            strcpy(areas[i], area_details[i].area_name);

                        }

                        // Graph representation (Adjacency matrix with distances in km)
                        int graph[V][V] = {
                            // T.Nagar Adyar Velachery Guindy AnnaNagar Mylapore Nungambakkam Saidapet Egmore Tambaram Porur Thiruvanmiyur Chromepet BesantNagar Thoraipakkam
                            { 0,  7,  8,  4, 10,  6,  4,  3,  6, 20, 12,  8, 18,  8, 10 }, // T. Nagar
                            { 7,  0,  4,  6, 15,  5,  9,  5, 10, 25, 16,  5, 22,  3,  7 }, // Adyar
                            { 8,  4,  0,  6, 12, 10, 10,  5, 12, 20, 14,  7, 17,  5,  6 }, // Velachery
                            { 4,  6,  6,  0, 10,  6,  8,  3,  9, 22,  9,  8, 19,  7,  9 }, // Guindy
                            {10, 15, 12, 10,  0, 12,  5, 10,  4, 30, 20, 15, 28, 17, 20 }, // Anna Nagar
                            { 6,  5, 10,  6, 12,  0,  5,  5,  5, 25, 14,  8, 21,  5,  8 }, // Mylapore
                            { 4,  9, 10,  8,  5,  5,  0,  6,  3, 20, 12, 12, 24, 10, 13 }, // Nungambakkam
                            { 3,  5,  5,  3, 10,  5,  6,  0,  9, 22,  8,  6, 18,  5,  7 }, // Saidapet
                            { 6, 10, 12,  9,  4,  5,  3,  9,  0, 27, 18, 15, 30, 15, 17 }, // Egmore
                            {20, 25, 20, 22, 30, 25, 20, 22, 27,  0, 18, 23,  5, 22, 25 }, // Tambaram
                            {12, 16, 14,  9, 20, 14, 12,  8, 18, 18,  0, 14, 20, 15, 17 }, // Porur
                            { 8,  5,  7,  8, 15,  8, 12,  6, 15, 23, 14,  0, 20,  4,  3 }, // Thiruvanmiyur
                            {18, 22, 17, 19, 28, 21, 24, 18, 30,  5, 20, 20,  0, 18, 15 }, // Chromepet
                            { 8,  3,  5,  7, 17,  5, 10,  5, 15, 22, 15,  4, 18,  0,  4 }, // Besant Nagar
                            {10,  7,  6,  9, 20,  8, 13,  7, 17, 25, 17,  3, 15,  4,  0 }  // Thoraipakkam
                        };

                        char user_area[20];
                        printf("\n");
                        printf("                                              \033[1;93m\033[40m============================================\033[0m\n");
                        printf("\n");
                        printf("                                                           \033[103m\033[30m NEARBY RESTAURANTS \033[0m \n");
                        printf("\n");
                        printf("                                              \033[1;93m\033[40m============================================\033[0m\n");
                        printf("\n");
                        printf("                                                  \033[1;97m Enter your current area: \033[0m");
                        scanf("%s", user_area);
                        toLowerCase(user_area);

                        int src = -1;
                        for (int i = 0; i < area_count; i++) {
                            char area_lower[20];
                            strcpy(area_lower, areas[i]);
                            toLowerCase(area_lower);
                            if (strcmp(area_lower, user_area) == 0) {
                                src = i;
                                break;
                            }
                        }

                        if (src == -1) {
                            printf("\n");
                            printf("                                                  \033[101m\033[1;97m No Restaurant found near you... \033[0m\n");
                            system("pause");
                        }


                        if (src != -1){
                                int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i
                                dijkstra(graph, src, dist);

                                printClosestAreas(dist, areas, src);
                            int showRestaurants;
                            while (1) {
                                printf("\n");
                                printf("                                                  \033[1;97m Do you want to see the\033[0m \033[1;34mrestaurants\033[0m \033[1;97min any of these areas? (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ");
                                scanf("%d", &showRestaurants);
                                if (showRestaurants == 0 || showRestaurants == 1) {
                                    break;
                                }
                                printf("\n");
                                printf("                                                    \033[101m\033[1;97mInvalid input. \033[0m \033[1;97mPlease enter \033[1;32m1\033[0m for Yes or \033[1;31m0\033[0m for No.\033[0m\n");
                            }

                            if (showRestaurants == 0) {
                                printf("\n");
                                printf("                                                                         \033[42m\033[1;97m Thank you...! \033[0m\n");
                                system("pause");

                            }
                            if(showRestaurants==1){
                                int areaIndex;
                                while (1) {
                                    printf("\n");
                                    printf("                                                  \033[1;97mEnter the \033[1;34marea index\033[0m to \033[1;97msee the restaurants:\033[0m ");
                                    scanf("%d", &areaIndex);
                                    if (areaIndex >= 0 && areaIndex < area_count) {
                                        break;
                                    }
                                    printf("\n");
                                    printf("                                                     \033[101m\033[1;97m Invalid area index. Please enter a valid index. \033[0m\n");
                                }
                                displayRestaurantsInArea(areaIndex);
                                int showMenu;
                            while (1) {
                                printf("\n");
                                printf("                                                  \033[1;97mDo you want to see the\033[0m \033[1;34mmenu\033[0m \033[1;97mof any restaurant? (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): \033[0m");
                                scanf("%d", &showMenu);
                                if (showMenu == 0 || showMenu == 1) {
                                    break;
                                }
                                printf("\n");
                                printf("                                                                    \033[101m\033[1;97m Invalid input.\033[0m \033[1;97mPlease enter\033[0m \033[1;32m1\033[0m \033[1;97mfor Yes or\033[0m \033[1;31m0\033[0m \033[1;97mfor No. \033[0m\n");
                            }

                            if (showMenu == 0) {
                                printf("\n");
                                printf("                                                                            \033[42m\033[1;97m Thank you...! \033[0m\n");
                                system("pause");

                            }
                            if(showMenu==1){
                                int restIndex;
                                while (1) {
                                    printf("\n");
                                    printf("                                                 \033[1;97m Enter the \033[1;34mrestaurant index\033[0m \033[1;97mto see the menu: \033[0m\033[0m");
                                    scanf("%d", &restIndex);
                                    if (restIndex > 0 && restIndex <= rc) {
                                        break;
                                    }
                                    printf("                                                                \033[101m\033[1;97m Invalid restaurant index. Please enter a valid index.\033[0m\n");
                                }
                                displayMe(restIndex);
                                // Save the cart to the file after modifications
                                saveCart();
                              }
                        }

                        }

                    }

                    else if(l==2){
                        readfile(FILE_NAME);// Start shopping
                        loadMenu();
                        loadRestaurants();
                        int restaurantIndex;
                        int itemId, quantity;
                        int choice;
                        int c;

                        while (1) {
                            printf("\n");
                            printf("                               \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                            printf("\n");
                            printf("                                            \033[103m\033[30m SHOPPING PAGE \033[0m             \n");
                            printf("\n");
                            printf("                               \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 1. TO VIEW THE RESTAURANTS.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 2. TO VIEW THE MENU.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 3. TO VIEW CART.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 4. TO ADD ITEM IN CART.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 5. TO REMOVE ITEM FROM THE CART.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 6. TO UPDATE QUANTITY IN THE CART.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 7. TO PLACE THE ORDER.\033[0m\n");
                            printf("\n");
                            printf("                                   \033[1;97m 8. Back \033[0m\n");
                            printf("\n");
                            printf("                               \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                            printf("\n");
                            printf("                                \033[1;97mEnter your choice:\033[0m ");
                            scanf("%d", &choice);
                            system("cls");
                            switch (choice) {
                                case 1:
                                    displayRestaurants();
                                    break;
                                case 2:
                                    displayRestaurants();
                                    printf("\n");
                                    printf("                                        \033[1;97mEnter the index of the\033[0m \033[1;34mrestaurant\033[0m \033[1;97myou want to view menu for:\033[0m");
                                    scanf("%d", &restaurantIndex);
                                    system("cls");
                                    if (restaurantIndex>=1) {
                                        displayMenu(restaurantIndex - 1);
                                        printf("\n");
                                        printf("\n");
                                        printf("                                            \033[1;97mDo you want to apply filter\033[0m (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No):");
                                        scanf("%d",&c);
                                        system("pause");
                                        system("cls");
                                        if(c==1){
                                            int choice;
                                            loadMenu1();

                                            char type[10];
                                            float min;
                                            float max;
                                            float rating;
                                            char catagory[20];
                                            printf("\n");
                                            printf("                                   \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                                            printf("\n");
                                            printf("                                           \033[103m\033[30m  FILTER DETAILS \033[0m       \n");
                                            printf("\n");
                                            printf("                                   \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                                            printf("\n");
                                            printf("                                    \033[1;97mEnter the food type\033[0m (\033[1;32mVeg or Non-veg\033[0m): ");
                                            scanf("%s", type);
                                            printf("\n");
                                            printf("                                    \033[1;97mEnter the Minimum Price range :\033[0m ");
                                            scanf("%f", &min);
                                            printf("\n");
                                            printf("                                    \033[1;97mEnter the Maximum Price range:\033[0m ");
                                            scanf("%f", &max);
                                            printf("\n");
                                            printf("                                    \033[1;97mEnter the Minimum Rating(\033[1;32mbetween 1 to 5\033[0m):\033[0m ");
                                            scanf("%f", &rating);
                                            printf("\n");
                                            printf("                                    \033[1;97mEnter the Cuisine \033[0m(\033[1;32mi.e American/Indian/Italian\033[0m): ");
                                            scanf("%s", catagory);
                                            printf("\n");

                                            filtermenu(type, min, max, rating, catagory);
                                            sort_based_on_rating();
                                            if(displayitems()){



                                            while (1) {
                                                printf("                                    \033[1;97m Enter index of the item to be added in the cart\033[0m (\033[1;31m 0 to finish\033[0m): ");
                                                scanf("%d", &choice);
                                                if (choice == 0) {
                                                    break;

                                                } else {
                                                    add_item_to_cart(CART_FILE, choice);
                                                }
                                            }
                                            }

                                            int offer_choice;
                                            printf("\n");
                                            printf("                                    \033[1;97m Are you excited to see the\033[0m \033[1;93m\033[40moffer available\033[0m? (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ");
                                            scanf("%d", &offer_choice);

                                            if (offer_choice == 1) {
                                                if(loadoffer1()){
                                                    printf("\n");
                                                    printf("                                    \033[1;97mDo you want to add any of this item to the cart?\033[0m (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ");
                                                    scanf("%d", &choice);

                                                    if (choice == 1) {
                                                        printf("\n");
                                                        printf("                                    \033[1;97mEnter the index of the offer item to add to the cart:\033[0m ");
                                                        scanf("%d", &choice);
                                                        add_offer_to_cart(CART_FILE, choice);
                                                    } else {
                                                        printf("                                                    \033[42m\033[1;97m  Shop more for Exciting offers!  \033[0m\n");
                                                    }
                                                }

                                            }

                                        }

                                    } else {
                                        printf("                                                \033[101m\033[1;97m  Invalid restaurant index.  \033[0m\n");
                                    }
                                    break;
                                case 3:
                                    displayCart();
                                    break;
                                case 4:
                                    printf("\n");
                                    printf("                                            \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=\033[0m");
                                    printf("\n");
                                    printf("                                                            \033[103m\033[30m  ADD FOOD TO CART \033[0m\n");
                                    printf("\n");
                                    printf("                                            \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=\033[0m");
                                    printf("\n");
                                    printf("                                            \033[1;97mEnter the ID of the food you want to add to cart:\033[0m ");
                                    scanf("%d", &itemId);
                                    printf("\n");
                                    printf("                                            \033[1;97mEnter the quantity: \033[0m");
                                    scanf("%d", &quantity);
                                    printf("\n");
                                    addToCart(itemId, quantity);
                                    break;
                                case 5:
                                    displayCart();
                                    printf("\n");
                                    printf("                                         \033[1;97mEnter the ID of the food item you want to \033[1;34mremove\033[0m from the cart: \033[0m");
                                    scanf("%d", &itemId);
                                    printf("\n");
                                    removeFromCart(itemId);
                                    break;
                                case 6:
                                    displayCart();
                                    printf("\n");
                                    printf("                                        \033[1;97mEnter the ID of the item you want to \033[0m\033[1;34mupdate the quantity for: \033[0m");
                                    scanf("%d", &itemId);
                                    printf("\n");
                                    printf("                                        \033[1;97mEnter the new quantity: \033[0m");
                                    scanf("%d", &quantity);
                                    printf("\n");
                                    updateQuantity(itemId, quantity);
                                    break;
                                case 7:
                                    placeOrder();
                                    break;
                                case 8:
                                    break;
                                default:
                                    printf("                                            \033[101m\033[1;97m Invalid choice. Please try again. \033[0m\n");
                            }
                            if(choice==8){
                            break;
                        }
                        system("pause");
                        system("cls");
                        }// shopping end
                    }
                    else if(l==3){
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
                            printf("                                             \033[103m \033[30m SEARCH BAR \033[0m\n");
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
                                printf("                                       \033[1;97mEnter the \033[1;93m\033[40mrestaurant name:\033[0m ");
                                fgets(rest_name, sizeof(rest_name), stdin);
                                rest_name[strcspn(rest_name, "\n")] = '\0'; // Remove the newline character from fgets
                                search_and_display_restaurant(rest_name);
                            } else if (choice == 2) {
                                printf("\n");
                                printf("                                       \033[1;97mEnter the \033[1;93m\033[40mFood name:\033[0m ");
                                fgets(menu_name, sizeof(menu_name), stdin);
                                menu_name[strcspn(menu_name, "\n")] = '\0'; // Remove the newline character from fgets
                                search_and_display_menu(menu_name);
                            } else if (choice == 3) {
                                break;
                            } else {
                                printf("                                    \033[101m\033[1;97mInvalid Choice.......\033[0m\n");
                            }
                        }

                    }
                    else if(l==4){
                        break;
                    }
                    system("cls");
                }



            }

        }




        else if(choice==2){
            //ADMIN
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
                system("cls");
                printf("                                           \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                printf("\n");
                printf("                                                   \033[103m\033[30m ADMIN's LOGIN PAGE \033[0m       \n");
                printf("\n");
                printf("                                           \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                printf("\n");
                printf("                                           \033[1;97m Enter the admin's Username:\033[0m ");
                scanf("%19s", username);  // Limiting input size to prevent overflow
                printf("\n");
                printf("                                           \033[1;97m Enter the password: \033[0m");
                scanf("%19s", password);  // Limiting input size to prevent overflow

                for (int i = 0; i < admin_count; i++) {
                    if (strcmp(admin_details[i].user_name, username) == 0 && strcmp(admin_details[i].password, password) == 0) {
                        printf("\n");
                        printf("\n");
                        printf("\n");
                        printf("                                                    \033[42m\033[1;97m  Login Successful...  \033[0m\n");
                        system("pause");
                        system("cls");



                    do {
                        printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                        printf("\n");
                        printf("                                                       \033[103m\033[30m ADMIN's PAGE \033[0m     \n");
                        printf("\n");
                        printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m1. ADD ITEM IN MENU.\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m2. DELETE ITEM FROM MENU.\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m3. UPDATE PRICE IN THE MENU.\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m4. UPDATE OFFER DETAILS.\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m5. DELETE THE OFFER DETAILS.\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m6. SHOW MENU OF THE RESTAURANT.\033[0m\n");
                        printf("\n");
                        printf("                                             \033[1;97m7. BACK.\033[0m\n");
                        printf("\n");
                        printf("                                          \033[1;93m\033[40m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
                        printf("\n");
                        printf("                                          \033[1;97mEnter your Choice: \033[0m");
                        if (scanf("%d", &choice) != 1) {
                            printf("                                        \033[101m\033[1;97mInvalid input. Please enter a number.\033[0m\n");
                            while (getchar() != '\n');  // Clear input buffer
                                continue;
                        }

                        switch (choice) {
                            case 1:
                                printf("\n");
                                printf("                                          \033[1;97mEnter the Restaurant name:\033[0m ");
                                scanf(" %[^\n]%*c", restaurant_name);
                                printf("\n");
                                printf("                                          \033[1;97mEnter the Food Name: \033[0m");
                                scanf(" %[^\n]%*c", item_name);
                                printf("\n");
                                printf("                                          \033[1;97mEnter the price of the food item:\033[0m ");
                                while (scanf("%f", &price) != 1 || price < 0) {
                                    printf("                                        \033[101m\033[1;97mInvalid price.\033[0m \n Please enter a positive number: ");
                                    while (getchar() != '\n');  // Clear input buffer
                                }
                                printf("\n");
                                printf("                                          \033[1;97mEnter the type of the food\033[0m \033[1;32m(e.g., American, Italian)\033[0m:\033[0m ");
                                scanf("%19s", type);
                                printf("\n");
                                printf("                                          \033[1;97mEnter the Category of the food\033[0m \033[1;32m(e.g., Veg, Non-Veg)\033[0m:\033[0m ");
                                scanf("%9s", category);
                                printf("\n");
                                add_item_to_menu(restaurant_name, item_name, price, 0, type, category);
                                    break;

                                case 2:
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the Restaurant name:\033[0m ");
                                    scanf(" %[^\n]%*c", restaurant_name);
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the Food name:\033[0m ");
                                    scanf(" %[^\n]%*c", item_name);
                                    printf("\n");
                                    delete_item_from_menu(restaurant_name, item_name);
                                    break;

                                case 3:
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the Restaurant name: ");
                                    scanf(" %[^\n]%*c", restaurant_name);
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the item name: \033[0m");
                                    scanf(" %[^\n]%*c", item_name);
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the price to be updated:\033[0m ");
                                    while (scanf("%f", &price) != 1 || price < 0) {
                                        printf("                                            \033[101mInvalid price.\033[0m \n \033[1;97mPlease enter a positive number:\033[0m ");
                                        while (getchar() != '\n');  // Clear input buffer
                                    }
                                    update_price(restaurant_name, item_name, price);
                                    break;

                                case 4:
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the restaurant name:\033[0m ");
                                    scanf(" %[^\n]%*c", restaurant_name);
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the food name: \033[0m");
                                    scanf(" %[^\n]%*c", item_name);
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the percentage of discount: \033[0m");
                                    while (scanf("%f", &percent) != 1 || percent < 0 || percent > 100) {
                                        printf("                                            \033[101m\033[1;97mInvalid percentage.\033[0m \n \033[1;97m Please enter a number between 0 and 100:\033[0m ");
                                        while (getchar() != '\n');  // Clear input buffer
                                    }
                                    update_offer_details(restaurant_name, item_name, percent);
                                    break;

                                case 5:
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the restaurant name: \033[0m");
                                    scanf(" %[^\n]%*c", restaurant_name);
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the food name:\033[0m ");
                                    scanf(" %[^\n]%*c", item_name);
                                    printf("\n");
                                    delete_offer(restaurant_name, item_name);
                                    break;

                                case 6:
                                    printf("\n");
                                    printf("                                          \033[1;97mEnter the Restaurant name:\033[0m ");
                                    scanf(" %[^\n]%*c", restaurant_name);
                                    printf("\n");
                                    show_menu(restaurant_name);
                                    break;

                                case 7:
                                    printf("\n");
                                    printf("                                                \033[42m\033[1;97mExiting admin menu...\033[0m\n");
                                    break;

                                default:
                                    printf("\n");
                                    printf("                                            \033[101m\033[1;97mInvalid choice. Please select a valid option.\033[0m\n");
                                    break;
                            }
                            system("pause");
                            system("cls");
                        } while (choice != 7);

                        flag = 1;
                        break;
                    }
                }

            if (flag == 0) {
                printf("\n");
                printf("                                                        \033[101m\033[1;97mInvalid username or password. Please try again.\033[0m\n");
                system("pause");
                system("cls");
            }
        } while (flag == 0);


        }
        else if(choice!=3){
            printf("                                                    \033[1;97mEnter the correct choice:\033[0m");
        }

    system("cls");
    }while(choice!=3);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                                                                        \033[42m\033[1;97mThank You For Visiting... ! \033[0m     ");
}
