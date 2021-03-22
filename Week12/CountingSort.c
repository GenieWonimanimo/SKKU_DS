// 시험 출제!! unstable->stable
#define MAX_SIZE    100
typedef int Data;

void CountingSort(Data* list, int n)
{
    Data count[MAX_SIZE];
    Data output[MAX_SIZE];

    // Counting the redundant elements
    for (int i = 0; i < n; i++)
        count[list[i]]++;
    
    // Cumulate the number of elements
    for (int i = 1; i < MAX_SIZE; i++)
        count[i] += count[i - 1];
    
    // Read the elements in the list and copy them to the output list
    /*
    // it is unstable
    for (int i = 0; i < n; i++) 
    {
        output[count[list[i]] - 1] = list[i];
        count[list[i]]--;
    }
    */
    // it is stable
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[list[i]] - 1] = list[i];
        count[list[i]]--;
    }

    // Copy the output list to the original list
    for (int i = 0; i < n; i++)
        list[i] = output[i];
}

/*
The time complexity is linear in the number of items and the difference between the max and min key val
often used as a subroutine in another sorting algorithm, radix sort(can handle larger keys more efficiently)
*/