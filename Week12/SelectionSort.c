typedef int Data;

void swap(Data* a, Data* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// bigger go behind
void SelectionSort(Data* list, int n)
{
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            // Find an index with the min element
            if (list[j] < list[min])
                min = j;
        }
        // Exchange the min element and the i-th element
        swap(&list[i], &list[min]);
    }
}

/*
Time complexity
Best case == Worst case -> O(n^2)
(n - 1) + (n - 2) + ... + 2 + 1

Not stable, the movement of elements are not adjacent
eg. 
4* 2 4** 1 5
1 2 4** 4* 5 // unstable!!
*/