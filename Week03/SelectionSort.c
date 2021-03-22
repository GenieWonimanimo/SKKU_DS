#include <stdio.h>

void Swap(int * a, int * b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int arr[], int size)
{
    int i, j, min;
    for (i = 0; i < size - 1; i++)
    {
        min = i;
        for (j = i + 1; j < size; j++)
            if (arr[j] < arr[min])
                min = j;
        Swap(&arr[i], &arr[min]);
    }
}

int main(void)
{
    int arr[] = {5, 1, 3, 9, 2, 4, 8, 5, 6, 10, 0};
    int i;
    
    for (i = 0; i < sizeof(arr) / sizeof(int); i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    sort(arr, sizeof(arr) / sizeof(int));
    for (i = 0; i < sizeof(arr) / sizeof(int); i++)
        printf("%d ", arr[i]);
    return 0;
}