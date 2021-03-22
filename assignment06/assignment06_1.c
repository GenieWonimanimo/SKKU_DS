#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct 
{
    bool remain;
    int pos;
    int start_pos;
    int end_pos;
    int inputtedOrder;
} Range;

typedef enum {POS, START_POS} KIND;
void Swap(Range* a, Range* b);
// sort lamps with start_pos
void Merge_StartPos(Range list[], int left, int mid, int right, int len);
// sort lampos with pos
void Merge_Pos(Range list[], int left, int mid, int right, int len);
void MergeSort(Range list[], int left, int right, KIND kind, int len);

// set all values each lamps have
void InitLamps(Range pLamps[], int len);
// remove lamps that don't have to exist
int RemoveLamps(Range pLamps[], int len);
// print pos of remain lamps
void PrintRemain(Range pLamps[], int len);

int main(void)
{
    int N;
    scanf(" %d", &N);
    Range* lamps = (Range *)malloc(sizeof(Range) * N);
    InitLamps(lamps, N);
    printf("%d\n", RemoveLamps(lamps, N));
    PrintRemain(lamps, N);
    return 0;
}

void Swap(Range* a, Range* b)
{
    Range tmp = *a;
    *a = *b;
    *b = tmp;
}

// sort lamps with start_pos
void Merge_StartPos(Range list[], int left, int mid, int right, int len)
{
    Range* sorted = (Range *)malloc(sizeof(Range) * len);
    int first = left, second = mid + 1, i = left;

    // Merge two lists by comparing elements in sequence
    while (first <= mid && second <= right)
    {
        if (list[first].start_pos <= list[second].start_pos)
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
    free(sorted);
}
// sort lamps with pos
void Merge_Pos(Range list[], int left, int mid, int right, int len)
{
    Range* sorted = (Range *)malloc(sizeof(Range) * len);
    int first = left, second = mid + 1, i = left;

    // Merge two lists by comparing elements in sequence
    while (first <= mid && second <= right)
    {
        if (list[first].pos <= list[second].pos)
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
    free(sorted);
}
void MergeSort(Range list[], int left, int right, KIND kind, int len)
{
    if (left < right)
    {
        int mid = (left + right) / 2; // Equal partitioning
        MergeSort(list, left, mid, kind, len); // Sorting left sublists(divide and conquer)
        MergeSort(list, mid + 1, right, kind, len); // Sorting right sublists(divide and conquer)
        if (kind == POS) Merge_Pos(list, left, mid, right, len);
        else if (kind == START_POS) Merge_StartPos(list, left, mid, right, len);
        else exit(1);
    }
}

// set all values each lamps have
void InitLamps(Range pLamps[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int pos, brightness;
        scanf(" %d %d", &pos, &brightness);
        pLamps[i].remain = true;
        pLamps[i].pos = pos;
        pLamps[i].start_pos = pos - brightness;
        pLamps[i].end_pos = pos + brightness;
        pLamps[i].inputtedOrder = i + 1;
    }
}

// remove lamps that don't have to exist
int RemoveLamps(Range pLamps[], int len)
{
    int remainNum = len;
    int brightEnd = -1;
    
    // Sort with START_POS
    MergeSort(pLamps, 0, len - 1, START_POS, len);
    // Sort lamps that have same start_pos with descending order
    for (int i = 0; i < len - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < len; j++)
        {
            // Find an index with the min element
            if (pLamps[j].start_pos == pLamps[max].start_pos)
                max = (pLamps[j].end_pos > pLamps[max].end_pos) ? j : max;
            else
                break;
        }
        // Exchange the min element and the i-th element
        Swap(&pLamps[i], &pLamps[max]);
    }

    // pos_j - brightness_j <= pos_i - brightness_i
    // &&
    // pos_i + brightness_i <= pos_j + brightness_j
    for (int i = 0; i < len - 1; i++)
    {
        brightEnd = (pLamps[i].end_pos > brightEnd) ? pLamps[i].end_pos : brightEnd;
        if (pLamps[i + 1].end_pos <= brightEnd)
        {
            pLamps[i + 1].remain = false;
            remainNum--;
        }
    }
    return remainNum;
}

void PrintRemain(Range pLamps[], int len) 
{
    MergeSort(pLamps, 0, len - 1, POS, len);
    for (int i = 0; i < len; i++)
    {
        if (pLamps[i].remain)
            printf("%d ", pLamps[i].inputtedOrder);
    }
}