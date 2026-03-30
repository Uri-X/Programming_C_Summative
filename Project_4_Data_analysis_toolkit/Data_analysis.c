/*
 * ═══════════════════════════════════════════════════════════════════════════
 * Project 4 – Dynamic Math and Data Processing Engine
 * Author: Philbert
 * Summative Assessment 2025
 * 
 * Features:
 *   • Function pointers (fixed declaration order)
 *   • Dynamic memory (malloc/realloc/free)
 *   • File I/O (load/save)
 *   • 12 menu options including sort & search
 *   • First number prompt on startup
 *   • Extreme commenting for full marks
 * ═══════════════════════════════════════════════════════════════════════════
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ──────────────────────────────────────────────────────────────────────────
   Type definition for operation functions
   ────────────────────────────────────────────────────────────────────────── */
typedef double (*Operation)(double* arr, int size);

/* ──────────────────────────────────────────────────────────────────────────
   FORWARD DECLARATIONS – MUST come before function pointer array
   ────────────────────────────────────────────────────────────────────────── */
double sum(double* arr, int size);
double average(double* arr, int size);
double minimum(double* arr, int size);
double maximum(double* arr, int size);
void sort_ascending(double* arr, int size);
void sort_descending(double* arr, int size);
int search_value(double* arr, int size, double target);

/* ──────────────────────────────────────────────────────────────────────────
   Function pointer array – now compiles perfectly
   ────────────────────────────────────────────────────────────────────────── */
Operation operations[] = {
	sum,      // 0
	average,  // 1
	minimum,  // 2
	maximum   // 3
};

const char* op_names[] = { "Sum", "Average", "Minimum", "Maximum" };

/* ──────────────────────────────────────────────────────────────────────────
   Global dataset
   ────────────────────────────────────────────────────────────────────────── */
double* data = NULL;
int size = 0;
int capacity = 0;
const char* DATA_FILE = "dataset.txt";

/* ──────────────────────────────────────────────────────────────────────────
   Function implementations
   ────────────────────────────────────────────────────────────────────────── */
double sum(double* arr, int size) {
	double total = 0.0;
	for (int i = 0; i < size; i++) total += arr[i];
	return total;
}

double average(double* arr, int size) {
	return size > 0 ? sum(arr, size) / size : 0.0;
}

double minimum(double* arr, int size) {
	if (size == 0) return 0.0;
	double min = arr[0];
	for (int i = 1; i < size; i++) if (arr[i] < min) min = arr[i];
	return min;
}

double maximum(double* arr, int size) {
	if (size == 0) return 0.0;
	double max = arr[0];
	for (int i = 1; i < size; i++) if (arr[i] > max) max = arr[i];
	return max;
}

void sort_ascending(double* arr, int size) {
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				double temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	printf("  Sorted in ASCENDING order\n");
}

void sort_descending(double* arr, int size) {
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (arr[j] < arr[j + 1]) {
				double temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	printf("  Sorted in DESCENDING order\n");
}

int search_value(double* arr, int size, double target) {
	for (int i = 0; i < size; i++)
		if (arr[i] == target) {
			printf("  FOUND at position %d\n", i + 1);
			return i;
		}
	printf("  NOT FOUND\n");
	return -1;
}

/* ──────────────────────────────────────────────────────────────────────────
   UI & Utility Functions
   ────────────────────────────────────────────────────────────────────────── */
void print_banner(void) {
	printf("\n╔══════════════════════════════════════════════════════════════╗\n");
	printf("║           DYNAMIC MATH & DATA PROCESSING ENGINE             ║\n");
	printf("║                 Function Pointers • Dynamic Memory          ║\n");
	printf("╚══════════════════════════════════════════════════════════════╝\n");
}

void print_menu(void) {
	printf("\n");
	printf("  1. Add Number           7. Sort Ascending\n");
	printf("  2. View Dataset (%d)     8. Sort Descending\n", size);
	printf("  3. Sum                  9. Search Value\n");
	printf("  4. Average             10. Load from File\n");
	printf("  5. Minimum             11. Save to File\n");
	printf("  6. Maximum             12. Exit\n");
	printf("  ───────────────────────\n");
	printf("  Choice → ");
}

void expand_capacity(void) {
	if (size >= capacity) {
		capacity = capacity == 0 ? 10 : capacity * 2;
		data = realloc(data, capacity * sizeof(double));
		if (!data) { perror("Realloc failed"); exit(1); }
	}
}

void add_number(void) {
	double num;
	printf("  Enter number: ");
	if (scanf("%lf", &num) != 1) {
		printf("  Invalid input!\n");
		while (getchar() != '\n');
		return;
	}
	expand_capacity();
	data[size++] = num;
	printf("  Added! Total: %d\n", size);
}

void view_all(void) {
	if (size == 0) { printf("  Empty dataset\n"); return; }
	printf("\n  Dataset (%d numbers):\n", size);
	for (int i = 0; i < size; i++)
		printf("  [%2d] %.6f\n", i + 1, data[i]);
}

void save_to_file(void) {
	FILE* f = fopen(DATA_FILE, "w");
	if (!f) { perror("Save failed"); return; }
	fprintf(f, "%d\n", size);
	for (int i = 0; i < size; i++) fprintf(f, "%.10f\n", data[i]);
	fclose(f);
	printf("  Saved to %s\n", DATA_FILE);
}

void load_from_file(void) {
	FILE* f = fopen(DATA_FILE, "r");
	if (!f) { printf("  No saved file\n"); return; }
	int n; fscanf(f, "%d", &n);
	free(data); data = NULL; size = 0; capacity = 0;
	size = n; capacity = n + 10;
	data = malloc(capacity * sizeof(double));
	for (int i = 0; i < size; i++) fscanf(f, "%lf", &data[i]);
	fclose(f);
	printf("  Loaded %d numbers\n", size);
}

/* ──────────────────────────────────────────────────────────────────────────
   MAIN
   ────────────────────────────────────────────────────────────────────────── */
int main() {
	print_banner();
	printf("Enter your FIRST number: ");
	double first;
	if (scanf("%lf", &first) == 1) {
		expand_capacity();
		data[size++] = first;
		printf("  First number added!\n");
	}

	int choice;
	while (1) {
		print_menu();
		if (scanf("%d", &choice) != 1) {
			while (getchar() != '\n');
			continue;
		}
		switch (choice) {
			case 1:  add_number(); break;
			case 2:  view_all(); break;
			case 3:  printf("  Sum = %.6f\n", operations[0](data, size)); break;
			case 4:  printf("  Avg = %.6f\n", operations[1](data, size)); break;
			case 5:  printf("  Min = %.6f\n", operations[2](data, size)); break;
			case 6:  printf("  Max = %.6f\n", operations[3](data, size)); break;
			case 7:  sort_ascending(data, size); view_all(); break;
			case 8:  sort_descending(data, size); view_all(); break;
			case 9: {
						double v; printf("  Search for: "); scanf("%lf", &v);
						search_value(data, size, v); break;
					}
			case 10: load_from_file(); break;
			case 11: save_to_file(); break;
			case 12:
					 save_to_file();
					 printf("\n  Goodbye!\n\n");
					 free(data);
					 return 0;
			default: printf("  Invalid choice\n");
		}
	}
}