#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITEMS 1000
#define MAX_TRANSACTIONS 1000
#define BILLFILE "transaction.csv"

typedef struct {
    char items[MAX_ITEMS][50];
    int numItems;
} transc;

transc transcs[MAX_TRANSACTIONS];
int numTransactions = 0;

typedef struct {
    char item[50];
    int support;
} is;

is frequentItems[MAX_ITEMS];
int numFrequentItems = 0;


void readTransactions(const char *billFile);
void countSupport();
void provideRecommendations();

/*int main() {
    readTransactions(BILLFILE);
    countSupport();
    provideRecommendations();
    return 0;
}*/

void readTransactions(const char *billFile) {
    FILE *file = fopen(billFile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        int itemIndex = 0;
        while (token != NULL && itemIndex < MAX_ITEMS) {
            strcpy(transcs[numTransactions].items[itemIndex], token);
            itemIndex++;
            token = strtok(NULL, ",");
        }
        transcs[numTransactions].numItems = itemIndex;
        numTransactions++;
    }

    fclose(file);
}

void countSupport() {
    for (int i = 0; i < numTransactions; i++) {
        for (int j = 0; j < transcs[i].numItems; j++) {
            bool found = false;
            for (int k = 0; k < numFrequentItems; k++) {
                if (strcmp(frequentItems[k].item, transcs[i].items[j]) == 0) {
                    frequentItems[k].support++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(frequentItems[numFrequentItems].item, transcs[i].items[j]);
                frequentItems[numFrequentItems].support = 1;
                numFrequentItems++;
            }
        }
    }

}

void provideRecommendations() {

    int maxSupport[4] = {0};
    char mostFrequentItems[4][50];
    for (int i = 0; i < numFrequentItems; i++) {
        for (int j = 0; j < 4; j++) {
            if (frequentItems[i].support > maxSupport[j]) {
                for (int k = 3; k > j; k--) {
                    maxSupport[k] = maxSupport[k - 1];
                    strcpy(mostFrequentItems[k], mostFrequentItems[k - 1]);
                }
                maxSupport[j] = frequentItems[i].support;
                strcpy(mostFrequentItems[j], frequentItems[i].item);
                break;
            }
        }
    }
    printf("                                                  \033[1;93m\033[40mo-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\033[0m\n");
    printf("\n");
    printf("                                                      \033[1;97mTop Selling Food items in our application\033[0m\n");
    printf("\n");
    for (int i = 0; i < 1; i++) {
        printf("                                                            \033[1;97m%d. %s\033[0m\n", i + 1, mostFrequentItems[i]);
    }
    printf("                                                  \033[1;93m\033[40mo-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\033[0m\n");
}

