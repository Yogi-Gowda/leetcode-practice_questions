#include <stdbool.h>
#include <stdio.h>
bool dfs(int* arr, int arrSize, int index) {

    // Outside array
    if(index < 0 || index >= arrSize)
        return false;

    // Already visited
    if(arr[index] < 0)
        return false;

    // Found zero
    if(arr[index] == 0)
        return true;

    // Store jump value
    int jump = arr[index];

    // Mark visited
    arr[index] = -arr[index];

    // Explore both directions
    return dfs(arr, arrSize, index + jump) ||
           dfs(arr, arrSize, index - jump);
}

bool canReach(int* arr, int arrSize, int start) {

    return dfs(arr, arrSize, start);
}

int main() {
    int arr[] = {4, 2, 3, 0, 3, 1, 2};
    //int arr[] = {3, 0, 2, 1, 2};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int start = 0;

    if (canReach(arr, arrSize, start)) {
        printf("Can reach zero from index %d\n", start);
    } else {
        printf("Cannot reach zero from index %d\n", start);
    }

    return 0;
}