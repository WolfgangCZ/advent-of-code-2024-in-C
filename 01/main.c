
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define CAP 1000
#define FILE_NAME "input_a.txt"

int list_a[CAP];
int list_b[CAP];

void print_arr(int *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int create_int(int *arr, int length)
{
    int number = 0;
    for (int i = 0; i < length; i++)
    {
        number += arr[i] * pow(10, (length-i-1)); 
    }
    return number;
}

void swap_sort(int *arr, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i+1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int main(void)
{
    char buffer[100];
    FILE *file = fopen(FILE_NAME, "r"); 
    char ch;
    int number[100];
    int a_count = 0;
    int b_count = 0;
    int digit_count = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch >= '0' && ch <='9') 
        {
            number[digit_count] = (ch - '0');  
            digit_count++;
        }
        else if (ch == ' ')
        {
            if (digit_count != 0)
            {
                list_a[a_count] = create_int(number, digit_count);
                digit_count = 0;
                a_count++;
            }
            continue;
        }
        else if (ch == '\n')
        {
            if (digit_count != 0)
            {
                list_b[b_count] = create_int(number, digit_count);
                digit_count = 0;
                b_count++;
            }
            continue;
        }
    }
    swap_sort(list_a, a_count);
    swap_sort(list_b, b_count);
    int length_sum = 0;
    for (int i = 0; i < a_count; i++)
    {
        length_sum += abs(list_a[i] - list_b[i]);
    }
    printf("result1: %d\n", length_sum);
    int similiarity_score = 0;
    for (int i = 0; i < a_count; i++)
    {
        int multiplier = 0;
        for (int j = 0; j < b_count; j++)
        {
            if (list_a[i] == list_b[j])            
            {
                multiplier++;
            }
        }
        similiarity_score += list_a[i] * multiplier;
    }
    printf("result2: %d\n", similiarity_score);
    fclose(file);
    return 0;
}
