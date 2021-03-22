typedef int Data;
#define MAX_SIZE    100

int MIN(double a, double b) {return (a >= b) ? b : a;}

void Merge(Data* list, int left, int mid, int right)
{
    int sorted[MAX_SIZE];
    int first = left, second = mid + 1, i = left;

    // Merge two lists by comparing elements in sequence
    while (first <= mid && second <= right)
    {
        if (list[first] <= list[second])
            sorted[i++] = list[first++];
        else
            sorted[i++] = list[second++];
    }

    // For remaining items, add them in sequence
    if (first > mid)
        for (int j = second; j <= right; j++)
            sorted[i++] = list[j];
    else
        for (int j = first; j <= mid; j++)
            sorted[i++] = list[j];
    
    // Copy the sorted list to the list
    for (int j = left; j <= right; j++)
        list[j] = sorted[j];
}

void MergeSort(Data* list, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2; // Equal partitioning
        MergeSort(list, left, mid); // Sorting sublists
        MergeSort(list, mid + 1, right); // Sorting sublists
        Merge(list, left, mid, right); // Merging two sublists
    }
}

// Iterative merge sort (Better than recursive)
void IterMergeSort(Data* list, int n)
{
    // Merge subarrays in bottom up manner. First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (int size = 1; size <= n - 1; size = 2 * size)
    {
        // Pick starting point of different subarrays of current size
        for (int left_start = 0; left_start < n - 1; left_start += 2 * size)
        {
            // Find ending point of left subarray
            // mid + 1 is starting point of right
            int mid = left_start + size - 1;
            int right_end = MIN(left_start + 2 * size - 1, n - 1);

            // Merge subarrays arr[left_start...mid] & arr[mid+1...right_end]
            Merge(list, left_start, mid, right_end);
        }
    }
}
/*
Time complexity
O(nlogn) (worst case and average case are equal)

It is stable
*/