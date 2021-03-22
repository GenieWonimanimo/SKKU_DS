typedef int Data;

void swap(Data* a, Data* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// bigger go behind
void InsertionSort(Data* list, int n)
{
    int j, key;
    for (int i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0; j--)
        {
            // If the j-th element is greater than key,
            // move to the next position
            if (key < list[j])
                list[j + 1] = list[j];
            else
                break;
        }
        // list[j]  key and list[j + 1] is empty
        // move the key to the (j + 1)th element
        list[j + 1] = key;
    }
}

/*
Best case O(n) // already sorted
Worst case O(n^2)

It is stable(similar to bubble sort)
*/