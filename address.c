#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h> // For tolower

#define V 15 // Number of areas (nodes in the graph)
#define INF INT_MAX
#define MAX_NAME_LENGTH 30

#define AREA_FILE "area.csv"
#define REST_FILE "restaurants.csv"
#define MENU_FILE "menu.csv"
#define CART_FILE "cart.csv"
#define MAX_CART_ITEMS 50

// Structures to store area, restaurant, and menu details
struct areas {
    int area_index;
    char area_name[50];
    int rest_start;
    int rest_end;
}area_details[30];

int area_count = 0;


struct rest {
    int index;
    char name[20];
    int menu_s;
    int menu_e;
    float rate;
}r_d[100];
int rc = 0;


struct menu3 {
    int item_index;
    char food_name[30];
    float price;
    float rating;
    char type[20];
    char category[10];
} m_d[200];
int m = 0;

// Structure to represent a cart item
struct ci {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
};

// Cart to store added items
struct ci cart[MAX_CART_ITEMS];
int cart_size = 0;



// Load area from file
void loadarea() {
    FILE *file = fopen(AREA_FILE, "r");
    if (file == NULL) {
        printf("Error in Opening the file..\n");
        return;
    }
    while(fscanf(file,"%d,%[^,],%d,%d\n",
                      &area_details[area_count].area_index,
                      area_details[area_count].area_name,
                      &area_details[area_count].rest_start,
                      &area_details[area_count].rest_end)!=EOF){
                    //printf("%d\n",area_details[area_count].area_index);
                    area_count++;

                }

    fclose(file);
}

// Load restaurant from file
void loadrestaurant() {
    FILE *file = fopen(REST_FILE, "r");
    if (file == NULL) {
        printf("Error in opening the file...\n");
        return;
    }
    int i=1;
    while(fscanf(file,"%[^,],%d,%d,%f\n",
                 r_d[rc].name,
                 &r_d[rc].menu_s,
                 &r_d[rc].menu_e,
                 &r_d[rc].rate)!=EOF){
                r_d[rc].index=i;
                rc++;
                i++;


          }
    i = 1;
    fclose(file);
}

void load_menu_1() {

    FILE *file = fopen(MENU_FILE, "r");
    if (file == NULL) {
        printf("Error in Opening the file..\n");
        return;
    }

    while (fscanf(file, "%d,%[^,],%f,%f,%[^,],%[^\n]\n",
                  &m_d[m].item_index,
                  m_d[m].food_name,
                  &m_d[m].price,
                  &m_d[m].rating,
                  m_d[m].type,
                  m_d[m].category) != EOF) {
        m++;
    }
    fclose(file);
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to implement Dijkstra's algorithm for a graph represented using adjacency matrix
void dijkstra(int graph[V][V], int src, int dist[]) {
    int sptSet[V]; // Shortest path tree set

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = 0;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

// Function to print the three closest areas
void printClosestAreas(int dist[], char areas[V][20], int src) {
    printf("\n");
    printf("                                                  \033[1;97m The closest areas to %s are: \033[0m\n", areas[src]);

    int sorted_indices[V];
    for (int i = 0; i < V; i++)
        sorted_indices[i] = i;

    // Bubble sort based on distance
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < V - i - 1; j++) {
            if (dist[sorted_indices[j]] > dist[sorted_indices[j + 1]]) {
                int temp = sorted_indices[j];
                sorted_indices[j] = sorted_indices[j + 1];
                sorted_indices[j + 1] = temp;
            }
        }
    }
    int index=1;
    printf("\n");
    printf("                                                  \033[1;93m\033[40m INDEX  ->   AREA  ->   DISTANCE\033[0m  \n");
    printf("\n");
    int recommendations = 0;
    for (int i = 1; i < V && recommendations < 3; i++) { // Start from 1 to skip the source itself
        if (dist[sorted_indices[i]] != INF) {
            printf("\n");
            printf("                                                  \033[1;97m %d      -       %s      -  (Distance: %d km) \033[0m\n", sorted_indices[i]+1 , areas[sorted_indices[i]], dist[sorted_indices[i]]);
            recommendations++;
            index++;
        }
    }
}

// Function to display restaurants in the selected area
void displayRestaurantsInArea(int areaIndex) {
    int stRes = -1;
    int enRes = -1;
    for (int i = 0; i < area_count; i++) {
        if (area_details[i].area_index == areaIndex) {
            stRes = area_details[i].rest_start;
            enRes = area_details[i].rest_end;
            break;
        }
    }

    if (stRes == -1 || enRes == -1) {
        printf("                                            \033[101m\033[1;97m Invalid area index. No restaurants found. \033[0m\n");
        return;
    }
    printf("\n");
    printf("                                                    \033[1;97m Restaurants in the selected area: \033[0m\n");
    printf("\n");
    printf("                                                    \033[1;93m\033[40m INDEX -> RESTAURANT NAME\033[0m \n");
    for (int i = stRes; i <= enRes; i++) {
        printf("                                                        \033[1;97m%d.%s\033[0m\n",r_d[i-1].index,r_d[i-1].name);
    }
}

// Function to display menu and add items to the cart
void displayMe(int restIndex) {
    int s = -1;
    int e = -1;
    for (int i = 0; i < rc; i++) {
        if (restIndex == r_d[i].index) {
            s = r_d[i].menu_s;
            e = r_d[i].menu_e;
            break;
        }
    }


    if (s == -1 || e == -1) {
        printf("\n");
        printf("                                            \033[101m\033[1;97m Invalid restaurant index. No menu found.\033[0m\n");
        return;
    }
    printf("\n");
    printf("                                                  \033[1;97m Menu for the selected restaurant:\033[0m\n");
    printf("\n");
    printf("                                                  \033[1;93m\033[40m INDEX   ->  FOOD  ->   PRICE \033[0m ");
    printf("\n");
    for (int i = s-1; i <e; i++) {
        printf("\n");
        printf("                                                  \033[1;97m%d - %s - Rs %0.2f\033[0m\n", m_d[i].item_index, m_d[i].food_name, m_d[i].price);
    }

    int addCart;
    printf("\n");
    printf("                                                  \033[1;97mDo you want to add an item to the cart?\033[0m (\033[1;32m1\033[0m-Yes or \033[1;31m0\033[0m-No): ");
    scanf("%d", &addCart);
    if (addCart == 1) {
        int itemID, quantity;
        printf("\n");
        printf("                                                  \033[1;97m Enter the item index to add to cart:\033[0m ");
        scanf("%d", &itemID);
        printf("\n");
        printf("                                                  \033[1;97m Enter the quantity: \033[0m");
        scanf("%d", &quantity);
        int found=0;
        //printf("%d",cart_size);
        for(int i=s-1;i<e;i++){
            if(m_d[i].item_index==itemID){
                cart[cart_size].id=itemID;
                strcpy(cart[cart_size].name,m_d[i].food_name);
                cart[cart_size].price=m_d[i].price;
                cart[cart_size].quantity=quantity;
                cart_size++;
                found=1;
            }
        }
        if(found==1){
            printf("\n");
            printf("                                            \033[42m\033[101m  ITEM ADDED SUCCESSFULLY.. \033[0m\n");
        }

    }
}

// Function to load the cart from file
void loadCart() {
    FILE *file = fopen(CART_FILE, "r");
    if (file == NULL) {
        printf("Error opening cart file.\n");
        return;
    }
    while (fscanf(file, "%d,%[^,],%f,%d\n",
                  &cart[cart_size].id,
                  cart[cart_size].name,
                  &cart[cart_size].price,
                  &cart[cart_size].quantity) != EOF) {
        cart_size++;
        if (cart_size >= MAX_CART_ITEMS) {
            printf("\n");
            printf("                                                    \033[101m\033[1;97mCart is full, cannot load more items.\033[0m\n");
            break;
        }

    }
    fclose(file);
}

// Function to save the cart to file
void saveCart() {
    FILE *file = fopen(CART_FILE, "w");
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return;
    }
    for (int i = 0; i < cart_size; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n", cart[i].id, cart[i].name, cart[i].price, cart[i].quantity);
    }
    fclose(file);
}

// Convert a string to lowercase
void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Main function
/*int main() {
    loadCart();
    loadarea();
    loadrestaurant();
    load_menu_1();
    //loadCart();// Load cart from file

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
    printf("Enter your current area: ");
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
        printf("Area not found. Please restart the program and enter a valid area.\n");

    }

    int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i
    dijkstra(graph, src, dist);

    printClosestAreas(dist, areas, src);

    int showRestaurants;
    while (1) {
        printf("Do you want to see the restaurants in any of these areas? (1-Yes or 0-No): ");
        scanf("%d", &showRestaurants);
        if (showRestaurants == 0 || showRestaurants == 1) {
            break;
        }
        printf("Invalid input. Please enter 1 for Yes or 0 for No.\n");
    }

    if (showRestaurants == 0) {
        printf("Exiting the program. Have a nice day!\n");

    }

    int areaIndex;
    while (1) {
        printf("Enter the area index to see the restaurants: ");
        scanf("%d", &areaIndex);
        if (areaIndex >= 0 && areaIndex < area_count) {
            break;
        }
        printf("Invalid area index. Please enter a valid index.\n");
    }
    displayRestaurantsInArea(areaIndex);

    int showMenu;
    while (1) {
        printf("Do you want to see the menu of any restaurant? (1-Yes or 0-No): ");
        scanf("%d", &showMenu);
        if (showMenu == 0 || showMenu == 1) {
            break;
        }
        printf("Invalid input. Please enter 1 for Yes or 0 for No.\n");
    }

    if (showMenu == 0) {
        printf("Exiting the program. Have a nice day!\n");

    }

    int restIndex;
    while (1) {
        printf("Enter the restaurant index to see the menu: ");
        scanf("%d", &restIndex);
        if (restIndex > 0 && restIndex <= rc) {
            break;
        }
        printf("Invalid restaurant index. Please enter a valid index.\n");
    }
    displayMe(restIndex);

    // Save the cart to the file after modifications
    saveCart();
    return 0;
}*/

