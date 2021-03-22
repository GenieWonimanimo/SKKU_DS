int rfindMaxTail(int * arr, int n, int max)
{
    if (n == 1) return max;
    else
    {
        if (max < arr[n - 1])
            max = arr[n - 1];
        
        return rfindMaxTail(arr, n - 1, max);
    }
}