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
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void PrintNode(ListNode* node)
{
    ListNode* current = node;
    while (current) {
        printf("%d\n", current->data);
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
}

int main(int argc, char* argv[])
{
    ListNode* head_node = MakeNewListNode(1);
    if (!head_node) {
        printf("[ERROR] Could not allocate memory for new node\n");
        return EXIT_FAILURE;
    }
    head_node->next                         = MakeNewListNode(2);
    head_node->next->next                   = MakeNewListNode(3);
    head_node->next->next->next             = MakeNewListNode(4);
    head_node->next->next->next->next       = MakeNewListNode(5);
    head_node->next->next->next->next->next = NULL;

    /* PrintNode(head_node); */
    ListNode* last_node = ReverseLinkedList(head_node);
    PrintNode(last_node);

    return EXIT_SUCCESS;
}
