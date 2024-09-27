#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t ListNode;

struct node_t {
    int       data;
    ListNode* next;
};

ListNode* MakeNewListNode(int data)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));

    if (!node) {
        printf("[ERROR] Could not allocate memory for new node\n");
        exit(1);
    }

    node->data = data;
    node->next = NULL;

    return node;
}

ListNode* DetectCycleLocation(ListNode* node);

void PrintNode(ListNode* node)
{
    int       cycle_count    = 0;
    ListNode* cycle_location = DetectCycleLocation(node);
    if (cycle_location) {
        printf("[INFO] List is cyclic, trimming down to the beginning of the next cycle.\n");
    }
    ListNode* current = node;
    while (current) {
        printf("%d\n", current->data);

        if (current == cycle_location) {
            cycle_count++;
        }
        if (cycle_count == 2) {
            printf("LinkedList entered to an endless cycle here, stopping.\n");
            break;
        }

        current = current->next;
    }
}

ListNode* ReverseLinkedList(ListNode* node)
{
    ListNode* current   = node;
    ListNode* register1 = NULL;
    ListNode* register2 = NULL;
    while (current) {
        if (!register1 && !register2) {
            register1 = current;
        } else if (register1 && !register2) {
            register1->next = NULL;
            register2       = current;
        } else {
            register2->next = register1;
            register1       = register2;
            if (!current->next) {
                current->next = register2;
                return current;
            }
            register2 = current;
        }
        current = current->next;
    }
    return NULL;
}

void ClearLinkedList(ListNode* node)
{
    ListNode* current = node;
    ListNode* prev    = NULL;

    ListNode* cycle_location = DetectCycleLocation(node);
    while (current) {
        prev    = current;
        current = current->next;
        if (prev == cycle_location)
            prev->next = NULL;
        else {
            free(prev);
        }
    }
}

ListNode* DetectCycleLocation(ListNode* node)
{
    ListNode* one_step_pointer = node;
    ListNode* two_step_pointer = node;
    while (true) {
        one_step_pointer = one_step_pointer->next;
        if (!two_step_pointer->next)
            return NULL;
        two_step_pointer = two_step_pointer->next->next;
        if (!one_step_pointer || !two_step_pointer)
            return NULL;

        if (one_step_pointer == two_step_pointer)
            return one_step_pointer;
    }
}

int main(int argc, char* argv[])
{
    ListNode* node1 = MakeNewListNode(1);
    ListNode* node2 = MakeNewListNode(2);
    ListNode* node3 = MakeNewListNode(3);
    ListNode* node4 = MakeNewListNode(4);
    ListNode* node5 = MakeNewListNode(5);
    node5->next     = node1;
    node4->next     = node5;
    node3->next     = node4;
    node2->next     = node3;
    node1->next     = node2;
    PrintNode(node1);
    ClearLinkedList(node1);
    return EXIT_SUCCESS;
}
