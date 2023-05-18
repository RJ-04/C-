#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Bst
{
    long long int data;
    struct Bst *left;
    struct Bst *right;
};
struct Bst *root = NULL;

//----------------------------------------------------------------------

struct Bst *create_new_node(long long int data)
{
    struct Bst *new_node = (struct Bst *)malloc(sizeof(struct Bst));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

//----------------------------------------------------------------------

struct Bst *insert_new_node(struct Bst *node, long long int data)
{
    if (node == NULL)
    {
        node = create_new_node(data);
    }
    else if (data <= node->data)
    {
        node->left = insert_new_node(node->left, data);
    }
    else if (data >= node->data)
    {
        node->right = insert_new_node(node->right, data);
    }
    root = node;
    return node;
}

//----------------------------------------------------------------------

bool search_data(struct Bst *node, long long int data)
{
    if (node == NULL)
    {
        return false;
    }
    else if (node->data == data)
    {
        return true;
    }
    else if (data < node->data)
    {
        return search_data(node->left, data);
    }
    else
    {
        return search_data(node->right, data);
    }
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

int main()
{
    long long int size;
    printf("enter size: ");
    scanf("%lld", &size);
    if (size < 1)
    {
        printf("size cannot be less than 1");
        return 0;
    }
    long long int data_arr[size];

    for (int i = 0; i < size; i++)
    {
        data_arr[i] = rand() % 100;
        printf("%lld ", data_arr[i]);
        insert_new_node(root, data_arr[i]);
    }
    printf("\n");
    while (1)
    {
        long long int search;
        printf("\nenter data to search: ");
        scanf("%lld", &search);

        if (search_data(root, search) == true)
        {
            printf("found %lld", search);
        }
        else
        {
            printf("not found %lld", search);
        }

        char end;
        printf("\nDo you wish to end? Y / N: ");
        scanf(" %c", &end);
        switch (end)
        {
        case 'Y':
            return 0;
        case 'y':
            return 0;
        case 'N':
            break;
        case 'n':
            break;
        default:
            printf("Invalid input");
        }
    }
    return 0;
}
