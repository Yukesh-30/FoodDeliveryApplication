#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Overallrecomendation.c"
#define TRANSACTIONS_FILE "transaction.csv"
#define CART_FILE "cart.csv"
#define MAX_TRANSACTIONS 1000
#define MAX_ITEMS 1000
#define MAX_ITEM_NAME_LEN 20
#define MIN_SUPPORT 2
#define MIN_CONFIDENCE 0.5

typedef struct{
    char send[50];
    char receive[50];


}recommend;
struct carti{
    int id;
    char item_name[20];
    float price;
    int quantity;
}c_items[50];
int c_c=0;
typedef struct {
    char items[MAX_ITEMS][MAX_ITEM_NAME_LEN];
    int count;
} Transaction;

typedef struct {
    char item[MAX_ITEM_NAME_LEN];
    int support;
} ItemSupport;

Transaction transactions[MAX_TRANSACTIONS];
int num_transactions = 0;

void readcart(const char *filename){
    FILE *file=fopen(filename,"r");
    if(file==NULL){
        printf("Error in opening the file...");

    }
    while(fscanf(file,"%d,%[^,],%f,%d",
                 &c_items[c_c].id,
                 c_items[c_c].item_name,
                 &c_items[c_c].price,
                 &c_items[c_c].quantity)!=EOF){
                    c_c++;
                 }
    fclose(file);

}

void read_transactions(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file");
        exit(EXIT_FAILURE);
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        transactions[num_transactions].count = 0;
        char *token = strtok(line, ",\n");
        while (token) {
            strcpy(transactions[num_transactions].items[transactions[num_transactions].count++], token);
            token = strtok(NULL, ",\n");
        }
        num_transactions++;
    }
    fclose(file);
}

void generate_frequent_itemsets(ItemSupport *item_supports, int *num_items) {
    for (int i = 0; i < num_transactions; i++) {
        for (int j = 0; j < transactions[i].count; j++) {
            int found = 0;
            for (int k = 0; k < *num_items; k++) {
                if (strcmp(item_supports[k].item, transactions[i].items[j]) == 0) {
                    item_supports[k].support++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(item_supports[*num_items].item, transactions[i].items[j]);
                item_supports[*num_items].support = 1;
                (*num_items)++;
            }
        }
    }

    // Print frequent itemsets
    /*printf("Frequent itemsets:\n");
    for (int i = 0; i < *num_items; i++) {
        if (item_supports[i].support >= MIN_SUPPORT) {
            printf("%s: %d\n", item_supports[i].item, item_supports[i].support);
        }
    }*/
}

void generate_association_rules(ItemSupport *item_supports, int num_items) {
    for (int i = 0; i < num_items; i++) {
        if (item_supports[i].support >= MIN_SUPPORT) {
            for (int j = 0; j < num_items; j++) {
                if (i != j && item_supports[j].support >= MIN_SUPPORT) {
                    int count_both = 0;
                    for (int k = 0; k < num_transactions; k++) {
                        int found_i = 0, found_j = 0;
                        for (int l = 0; l < transactions[k].count; l++) {
                            if (strcmp(transactions[k].items[l], item_supports[i].item) == 0) {
                                found_i = 1;
                            }
                            if (strcmp(transactions[k].items[l], item_supports[j].item) == 0) {
                                found_j = 1;
                            }
                        }
                        if (found_i && found_j) {
                            count_both++;
                        }
                    }
                    double confidence = (double) count_both / item_supports[i].support;
                    if (confidence >= MIN_CONFIDENCE) {
                        //printf("%s -> %s (Confidence: %.2f)\n", item_supports[i].item, item_supports[j].item, confidence);
                    }
                }
            }
        }
    }
}

void recommend_items(ItemSupport *item_supports, int num_items, const char cart[MAX_ITEMS][MAX_ITEM_NAME_LEN], int cart_size, recommend arr[]) {
    int flag=0;
    for (int i = 0; i < cart_size; i++) {
        double max_confidence = 0.0;
        char recommended_item[MAX_ITEM_NAME_LEN] = "";

        for (int j = 0; j < num_items; j++) {
            if (strcmp(cart[i], item_supports[j].item) == 0) {
                for (int k = 0; k < num_items; k++) {
                    if (j != k) {
                        // Calculate confidence
                        int count_both = 0;
                        for (int l = 0; l < num_transactions; l++) {
                            int found_i = 0, found_k = 0;
                            for (int m = 0; m < transactions[l].count; m++) {
                                if (strcmp(transactions[l].items[m], item_supports[j].item) == 0) {
                                    found_i = 1;
                                }
                                if (strcmp(transactions[l].items[m], item_supports[k].item) == 0) {
                                    found_k = 1;
                                }
                            }
                            if (found_i && found_k) {
                                count_both++;
                            }
                        }
                        double confidence = (double) count_both / item_supports[j].support;
                        if (confidence >= MIN_CONFIDENCE && confidence > max_confidence) {
                            max_confidence = confidence;
                            strcpy(recommended_item, item_supports[k].item);
                        }
                    }
                }
            }
        }
        //printf("%d\n",strlen(recommended_item));
        //printf("%d",strlen(recommended_item));
        char dummy[20]="";
        strcpy(arr[i].receive,dummy);
        if (strlen(recommended_item) > 0) {
            strcpy(arr[i].send , cart[i]);
            strcpy(arr[i].receive, recommended_item);
            printf("                                        \033[1;93m\033[40mo-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\033[0m\n");
            printf("\n");
            printf("                                            \033[1;97mYou can also buy :\033[0m %s\033[0m       \n",arr[i].receive);
            printf("\n");
            printf("                                        \033[1;93m\033[40mo-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\033[0m\n");
            printf("\n");
            flag=1;
        }

    }
    if(flag==0){
            readTransactions(BILLFILE);
            countSupport();
            provideRecommendations();
    }
}/*

int main() {
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

    //printf("%s\n",recommended_list[0].receive);




*/
