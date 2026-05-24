#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int* arr, int n, int d, int index, int* dp) {

    if(dp[index] != 0)
        return dp[index];

    int ans = 1;

    for(int i = index + 1;
        i <= index + d && i < n;
        i++) {

        if(arr[i] >= arr[index])
            break;

        ans = max(ans,
                  1 + dfs(arr, n, d, i, dp));
    }

    for(int i = index - 1;
        i >= index - d && i >= 0;
        i--) {

        if(arr[i] >= arr[index])
            break;

        ans = max(ans,
                  1 + dfs(arr, n, d, i, dp));
    }

    dp[index] = ans;

    return ans;
}

int maxJumps(int* arr, int arrSize, int d) {

    int dp[1001] = {0};

    int result = 1;

    for(int i = 0; i < arrSize; i++) {

        result = max(result,
                     dfs(arr, arrSize, d, i, dp));
    }

    return result;
}

int main() {
    int arr[] = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
    int d = 2;
    int result = maxJumps(arr, sizeof(arr) / sizeof(arr[0]), d);
    printf("Maximum jumps: %d\n", result);
    return 0;
}