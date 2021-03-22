#include <stdio.h>

int bsearch(int arr[], int low, int high, int target)
{
    if (low > high) return -1;
    else
    {
        {
            int mid = (low + high) / 2;
            if (target == arr[mid])
                return mid;
            else if (target < arr[mid])
                bsearch(arr, low, mid - 1, target);
            else
                bsearch(arr, mid + 1, high, target);
        }
    }
    
}

int main(void)
{
    int arr[] = {1, 5, 17, 25, 27, 29, 51, 55, 71, 80, 90, 95};
    int i;
    for (i = 0; i < sizeof(arr) / sizeof(int); i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("target ÀÇ ÀÎµ¦½º´Â %d. \n", bsearch(arr, 0, sizeof(arr) / sizeof(int), 90));

    return 0;
}