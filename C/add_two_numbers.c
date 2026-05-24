#include <stdio.h>
#include <stdlib.h>
struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* current = &dummy;
    int carry = 0;
    while(l1 != NULL || l2 != NULL || carry != 0){
        int sum = carry;
        if(l1 != NULL){
            sum = sum + l1 -> val;
            l1 = l1 -> next;
        }
        if(l2 != NULL){
            sum = sum + l2 -> val;
            l2 = l2 -> next;
        }
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode -> val = sum % 10;

        carry = sum / 10;
        newNode -> next = NULL;
        current -> next = newNode;
        current = current -> next;
    }
    return dummy.next;
}

int main(){
    struct ListNode* l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* l2 = (struct ListNode*)malloc(sizeof(struct ListNode));

    l1 -> val = 2;
    l1 -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1 -> next -> val = 4;
    l1 -> next -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1 -> next -> next -> val = 3;
    l1 -> next -> next -> next = NULL;

    l2 -> val = 5;
    l2 -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2 -> next -> val = 6;
    l2 -> next -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2 -> next -> next -> val = 4;
    l2 -> next -> next -> next = NULL;

    struct ListNode* result = addTwoNumbers(l1, l2);
    printf("Result: ");
    while(result != NULL){
        printf("%d ", result->val);
        result = result->next;
    }
    printf("\n");

}