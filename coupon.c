#include <stdio.h>
#include <string.h>

#define COUPON_CODE "coupon.csv"

struct coupon {
    char coupon[10];
    float coupon_percentage;
    int flag;
};

struct coupon coupon_details[50];
int coupon_count = 0;

void readcoupons(const char *filename);
int validate_coupon(const char *code);
void calculate_amount(const char *code, float* total_amount);
void update_coupon_file(const char *filename);

/*int main() {
    char code[10];
    float total_amount;

    readcoupons(COUPON_CODE);

    printf("Enter the coupon code:");
    scanf("%s", code);

    if (validate_coupon(code)) {
        total_amount = 100.0;
        calculate_amount(code, total_amount);

        update_coupon_file(COUPON_CODE);
    } else {
        printf("Invalid Coupon: %s\n", code);
    }

    return 0;
}*/

void readcoupons(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening the file...");
        return;
    }
    coupon_count = 0;
    while (fscanf(file, "%9[^,],%f,%d\n", coupon_details[coupon_count].coupon,
                  &coupon_details[coupon_count].coupon_percentage, &coupon_details[coupon_count].flag) != EOF) {
        coupon_count++;
    }

    fclose(file);
}

int validate_coupon(const char *code) {
    for (int i = 0; i < coupon_count; i++) {
        if (strcmp(coupon_details[i].coupon, code) == 0 && coupon_details[i].flag == 1) {
            coupon_details[i].flag = 0;
            return 1;
        }
    }
    return 0;

}

void calculate_amount(const char *code, float* total_amount) {
    for (int i = 0; i < coupon_count; i++) {
        if (strcmp(coupon_details[i].coupon, code) == 0) {
            float resultant_price = (*total_amount) - ((*total_amount) * (coupon_details[i].coupon_percentage / 100.0));
            printf("\n");
            printf("                                    \033[1;93m\033[40mo-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\033[0m\n");
            printf("\n");
            printf("                                        \033[1;97mAmount after applying coupon\033[0m \033[1;34m%s\033[0m: \033[1;97m₹ %.2f\033[0m\n", code, resultant_price);
            printf("\n");
            printf("                                    \033[1;93m\033[40mo-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\033[0m\n");
            printf("\n");
            (*total_amount)=resultant_price;
            return;
        }
    }
    printf("\n");
    printf("                                                    \033[101m\033[1;97m Coupon not found: %s\033[0m\n", code);

}

void update_coupon_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error in opening the file...");
        return;
    }

    for (int i = 0; i < coupon_count; i++) {
        fprintf(file, "%s,%.2f,%d\n", coupon_details[i].coupon, coupon_details[i].coupon_percentage, coupon_details[i].flag);
    }

    fclose(file);
}
