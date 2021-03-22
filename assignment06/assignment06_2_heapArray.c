#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
enum {INSERT = 'I', DELETE = 'D', COUNT = 'C', RANGECOUNT = 'R', TOP = 'T'};

int main(void)
{
	short* inventory = (short *)calloc(10000000, sizeof(short));
	int inputCnt = 0;
	long long allDia = 0;
    int N;
    scanf(" %d", &N);
    for (int i = 0; i < N; i++)
    {
        char option;
        int n, m;
        scanf(" %c", &option);
        switch (option)
        {
            case INSERT:
                scanf(" %d %d", &n, &m);
				*(inventory + (n - 1)) += m;
				allDia += m;
                break;
            case DELETE:
                scanf(" %d %d", &n, &m);
				if (*(inventory + (n - 1)) >= m)
				{
					*(inventory + (n - 1)) -= m;
					allDia -= m;
				}
				else
				{
					allDia -= *(inventory+(n-1));
					*(inventory + (n - 1)) = 0;
				}
                break;
            case COUNT:
                scanf(" %d", &n);
				printf("%d\n", *(inventory + (n - 1)));
                break;
            case RANGECOUNT:
			{
				int cnt = 0;
                scanf(" %d %d", &n, &m);
				for (int i = n - 1; i < m; i++)
					cnt += *(inventory + i);
				printf("%d\n", cnt);
                break;
			}
			case TOP:
			{
				int cnt = 0;
				//printf("%lld", allDia);
                scanf(" %d", &n);
				if (allDia < n)
				{
					printf("-1\n");
					break;
				}
				for (int i = 0; i < 10000000; i++)
				{
					cnt += *(inventory + i);
					if (cnt >= n)
					{
						printf("%d\n", i + 1);
						break;
					}
				}
                break;
			}
            default:
                exit(1);
        }
    }
	free(inventory);
    return 0;
}