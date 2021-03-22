int fibo(int n)
{
    if (n == 1 || n == 2) return 1;
    else
        return fibo(n - 1) + fibo(n - 2);
}

int rfiboTail(int n, int prev, int cur)
{
    if (n == 1 || n == 2) return cur;
    else
        return rfiboTail(n - 1, cur, prev + cur);    
}