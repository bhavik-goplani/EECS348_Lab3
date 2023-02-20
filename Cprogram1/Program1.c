#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to generate the sales report
void generate_sales_report(float sales[], char **months) {
    printf("Monthly sales report for 2022:\n\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < 12; i++) {
        float sale = sales[i];
        printf("%-15s\t$%.2f\n", months[i], sale);
    }
}

// Function to calculate the minimum, maximum, and average of the monthly sales
void calculate_sales_summary(float sales[], float *min_sale, float *max_sale, float *avg_sale, char **months) {
    *min_sale = sales[0];
    *max_sale = sales[0];
    *avg_sale = 0.0f;
    char *min_month = months[0];
    char *max_month = months[0];
    for (int i = 0; i < 12; i++) {
        float sale = sales[i];
        min_month = (sale < *min_sale) ? months[i] : min_month;
        max_month = (sale > *max_sale) ? months[i] : max_month;
        *min_sale = (sale < *min_sale) ? sale : *min_sale;
        *max_sale = (sale > *max_sale) ? sale : *max_sale;
        *avg_sale += sale;
    }
    *avg_sale /= 12;
    printf("Sales summary:\n\n");
    printf("Minimum sales:  $%.2f \t(%s)\n", *min_sale, min_month);
    printf("Maximum sales:  $%.2f \t(%s)\n", *max_sale, max_month);
    printf("Average sales:  $%.2f \n", *avg_sale);
}

// Function to calculate the six-month moving averages
void calculate_six_month_moving_averages(float sales[], float moving_averages[], char **months) {
    for (int i = 5; i < 12; i++) {
        float moving_average = 0.0f;
        for (int j = i - 5; j <= i; j++) {
            moving_average += sales[j];
        }
        moving_averages[i-5] = moving_average / 6;
    }
    printf("Six-Month Moving Average Report:\n\n");
    printf("Month\t\tSales\n");
    for (int i = 5; i < 12; i++) {
        printf("%-15s - %-15s $%.2f\n", months[i-5], months[i], moving_averages[i-5]);
    }
}

// Function to generate the monthly sales report from highest to lowest
void generate_sales_report_highest_to_lowest(float sales[], char **months) {
    int sorted_indices[12];
    for (int i = 0; i < 12; i++) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < 11; i++) {
        for (int j = i + 1; j < 12; j++) {
            if (sales[sorted_indices[i]] < sales[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }
    printf("Sales Report (Highest to Lowest):\n\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < 12; i++) {
        int month = sorted_indices[i];
        float sale = sales[sorted_indices[i]];
        printf("%-15s\t$%.2f\n", months[month], sale);
    }
}

int main() {
    float sales[12];
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    float min_sale, max_sale, avg_sale;
    float moving_averages[7];
    
    // Read the monthly sales numbers from the input file
    FILE *fp = fopen("sales.txt", "r");
    for (int i = 0; i < 12; i++) {
        fscanf(fp, "%f", &sales[i]);
    }
    fclose(fp);
    
    // Generate the sales report
    generate_sales_report(sales, months);
    printf("\n");
    
    // Calculate the sales summary
    calculate_sales_summary(sales, &min_sale, &max_sale, &avg_sale, months);
    printf("\n");
    calculate_six_month_moving_averages(sales, moving_averages, months);
    printf("\n");
    generate_sales_report_highest_to_lowest(sales, months);
}