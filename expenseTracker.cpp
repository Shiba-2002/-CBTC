#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CATEGORY_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100

typedef struct {
    char date[11];  // Format: YYYY-MM-DD
    double amount;
    char category[MAX_CATEGORY_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} Expense;
#define MAX_EXPENSES 100

Expense expenses[MAX_EXPENSES];
int expense_count = 0;

void add_expense() {
    if (expense_count >= MAX_EXPENSES) {
        printf("Cannot add more expenses. Maximum limit reached.\n");
        return;
    }

    Expense new_expense;
    
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", new_expense.date);
    
    printf("Enter amount: ");
    scanf("%lf", &new_expense.amount);
    
    printf("Enter category: ");
    scanf("%s", new_expense.category);
    
    printf("Enter description: ");
    scanf(" %[^\n]%*c", new_expense.description); // Read until newline

    expenses[expense_count++] = new_expense;
    printf("Expense added successfully!\n");
}

void list_expenses() {
    printf("\nListing all expenses:\n");
    printf("ID  Date        Amount   Category                Description\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < expense_count; i++) {
        Expense e = expenses[i];
        printf("%-3d %-10s %-8.2lf %-20s %-s\n", i+1, e.date, e.amount, e.category, e.description);
    }
}

void save_expenses() {
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL) {
        printf("Could not open file to save expenses.\n");
        return;
    }

    for (int i = 0; i < expense_count; i++) {
        Expense e = expenses[i];
        fprintf(file, "%s %.2lf %s %s\n", e.date, e.amount, e.category, e.description);
    }

    fclose(file);
    printf("Expenses saved to expenses.txt\n");
}

void load_expenses() {
    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL) {
        printf("No expenses to load.\n");
        return;
    }

    expense_count = 0;
    while (fscanf(file, "%10s %lf %49s %99[^\n]", 
                  expenses[expense_count].date, 
                  &expenses[expense_count].amount, 
                  expenses[expense_count].category, 
                  expenses[expense_count].description) != EOF) {
        expense_count++;
        if (expense_count >= MAX_EXPENSES) {
            break;
        }
    }

    fclose(file);
    printf("Expenses loaded from expenses.txt\n");
}
void generate_report() {
    double category_totals[MAX_EXPENSES];
    char categories[MAX_EXPENSES][MAX_CATEGORY_LENGTH];
    int category_count = 0;

    for (int i = 0; i < expense_count; i++) {
        Expense e = expenses[i];
        int found = 0;
        
        for (int j = 0; j < category_count; j++) {
            if (strcmp(e.category, categories[j]) == 0) {
                category_totals[j] += e.amount;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(categories[category_count], e.category);
            category_totals[category_count] = e.amount;
            category_count++;
        }
    }

    printf("\nExpenses by Category:\n");
    for (int i = 0; i < category_count; i++) {
        printf("%s: %.2lf\n", categories[i], category_totals[i]);
    }
}
void print_menu() {
    printf("\nExpense Tracker\n");
    printf("1. Add Expense\n");
    printf("2. List Expenses\n");
    printf("3. Save Expenses\n");
    printf("4. Load Expenses\n");
    printf("5. Generate Report\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main() {
    load_expenses();

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_expense();
                break;
            case 2:
                list_expenses();
                break;
            case 3:
                save_expenses();
                break;
            case 4:
                load_expenses();
                break;
            case 5:
                generate_report();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

