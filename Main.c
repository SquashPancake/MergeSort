#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // <-- ADD THIS

#define MAX_NUMBERS 100

int ask(int numbers[], int max);
void mergesort(int numbers[], int left, int right);
void merge(int numbers[], int left, int mid, int right);

int main(void)
{
    int numbers[MAX_NUMBERS];
    int count = ask(numbers, MAX_NUMBERS);
    mergesort(numbers, 0, count - 1);
    printf("You inserted %i numbers\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("%d,", numbers[i]);
    }
    printf("\n");

    return 0;
}

int ask(int numbers[], int max)
{
    char input[100];
    int count = 0;

    printf("Welcome!\nAfter inserting all the numbers, type 'Done' to end.\n");

    while (true)
    {
        printf("Insert a number: ");
        scanf("%s", input); // Read input as string

        // Check if user typed "Done" (case-insensitive)
        if (strcasecmp(input, "Done") == 0)
        {
            printf("Let me sort them for you...\n");
            break;
        }

        // Try to convert input to int
        char *endptr;
        int num = strtol(input, &endptr, 10);
        if (*endptr != '\0')
        {
            printf("Invalid input. Please enter a number or 'Done'.\n");
            continue;
        }

        // Save the number
        if (count < MAX_NUMBERS)
        {
            numbers[count++] = num;
        }
        else
        {
            printf("Too many numbers! Max is %d.\n", MAX_NUMBERS);
            break;
        }
    }
    return count;
}

void mergesort(int numbers[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergesort(numbers, left, mid);
        mergesort(numbers, mid + 1, right);
        merge(numbers, left, mid, right);
    }
}

void merge(int numbers[], int left, int mid, int right)
{
    int l = mid - left + 1;
    int r = right - mid;

    int s1[l];
    int s2[r];

    for (int i = 0; i < l; i++)
    {
        s1[i] = numbers[left + i];
    }
    for (int j = 0; j < r; j++)
    {
        s2[j] = numbers[mid + 1 + j];
    }

    int temp[right + 1];
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < l && j < r)
    {
        if (s1[i] <= s2[j])
        {
            temp[k] = s1[i];
            i++;
        }
        else
        {
            temp[k] = s2[j];
            j++;
        }
        k++;
    }

    while (i < l)
    {
        temp[k] = s1[i];
        i++;
        k++;
    }

    while (j < r)
    {
        temp[k] = s2[j];
        j++;
        k++;
    }

    for (int m = 0; m < k; m++)
        numbers[left + m] = temp[m];
}
