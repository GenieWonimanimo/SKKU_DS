typedef int Data;

void swap(Data* a, Data* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// bigger go behind
void BubbleSort(Data* list, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            // Compare each pair of adjacent items
            if (list[j] > list[j + 1])
            {
                // Swap if they are in the wrong order
                swap(&list[j], &list[j + 1]);
            }
        }
    }
}

/*
Time complexity
Best case == Worst case -> O(n^2)

It is stable
maintain original order
*/