#include <stdio.h>
int findMin(int* nums, int numsSize) {

    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        //using binary search technique 
        int mid = left + (right - left) / 2;

        // Minimum is in right half
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        }

        // Minimum is in left half including mid
        else if (nums[mid] < nums[right]) {
            right = mid;
        }

        // Duplicate values
        else {
            right--;
        }
    }

    return nums[left];
}

int main() {
    int nums[] = {3, 4, 5, 1, 2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int min = findMin(nums, numsSize);
    printf("The minimum element in the rotated sorted array is: %d\n", min);
    return 0;
}