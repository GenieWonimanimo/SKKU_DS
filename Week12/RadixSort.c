#define MAX_SIZE    20
typedef int Data;
void Counting(int list[], int n, int exp)
{
    int count[10] = {0, };
    int output[MAX_SIZE];

    // Store count of occurrences in count list
    for (int i = 0; i < n; i++)
        count[(list[i] / exp) % 10]++;
    
    // Change count[i] so that count[i] contains actual position of this digit in output list
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Build the output list
    // this is stable -> Q
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(list[i] / exp) % 10] - 1] = list[i];
        count[(list[i] / exp) % 10]--;
    }

    // Copy the output list to list[], so that list[] now
    // contains sorted numbers according to current digit
    for (int i = 0; i < n; i++)
        list[i] = output[i];
}

void RadixSort(Data* list, int n)
{
    // Find the max number to know the number of digits
    int max = list[0];
    for (int i = 1; i < n; i++)
    {
        if (list[i] > max)
            max = list[i];
    }

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; max / exp > 0; exp *= 10)
        Counting(list, n, exp); // exp 1, 10, 100 // sort for each digits
}
/*
Q. unstable counting sort cannot be used for radix sort
A. in unstable algorithm, number that has lower val in prev exp located at behind in next exp
*/

/*
Time complexity of radix sort is O(dn)
d is the maximum number of digits
n is the number of elements
*/