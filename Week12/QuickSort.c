typedef int Data;

void swap(Data* a, Data* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int Partition(Data* list, int left, int right)
{
    int pivot = list[left], temp;
    int low = left + 1, high = right;

    while (1)
    {
        while (low < right && list[low] < pivot)
            low++; // Move low until pivot < list[low]
        while (high > left && list[high] >= pivot)
            high--; // Move high until pivot >= list[high]
        
        if (low < high)
            swap(&list[low], &list[high]); // Swap list[low] and list[high]
        else
            break;
    }
    swap(&list[left], &list[high]);
    return high; // return the pivot position
}

void QuickSort(Data* list, int left, int right)
{
    if (left < right)
    {
        // The mid refers to the pivot position
        int mid = Partition(list, left, right);

        // All elements are less than the pivot
        QuickSort(list, left, mid - 1);

        // All elements are greater than the pivot
        QuickSort(list, mid + 1, right);
    }
}

/*
Time complexity
We expect that the list will be split into two halves in an average case
T(n) = 2T(n/2) + cn
O(nlogn) (average and best case)

in the worst case (reversely sorted), O(n^2)

The worse case occurs if the pivot is selected as an extremely skewed case
The time complexity of quick sort mainly depends on pivot selection

How to choose a good pivot in quick sort?
random
median of 1th, middle and last elements
*/