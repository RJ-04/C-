#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

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
    else if (data > node->data)
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

long long int find_height(struct Bst *node)
{
    if (node == NULL)
    {
        return -1;
    }

    long long int left_height = find_height(node->left);
    long long int right_height = find_height(node->right);

    if (left_height > right_height)
    {
        return left_height + 1;
    }
    else if (right_height > left_height)
    {
        return right_height + 1;
    }
    else if (left_height == right_height)
    {
        return left_height + 1;
    }
}

//----------------------------------------------------------------------

void preorder(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    printf(" %lld ", node->data);
    preorder(node->left);
    preorder(node->right);
}

//----------------------------------------------------------------------

void inorder(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    inorder(node->left);
    printf(" %lld ", node->data);
    inorder(node->right);
}

//----------------------------------------------------------------------

void postorder(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    postorder(node->left);
    postorder(node->right);
    printf(" %lld ", node->data);
}

//----------------------------------------------------------------------

bool is_bst_util(struct Bst *node, long long int min_value, long long int max_value)
{
    if (node == NULL)
    {
        return true;
    }
    if (node->data >= min_value && node->data <= max_value && is_bst_util(node->left, min_value, node->data) && is_bst_util(node->right, node->data, max_value))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_bst(struct Bst *node)
{
    return is_bst_util(node, LLONG_MIN, LLONG_MAX);
}

//----------------------------------------------------------------------

struct ptr
{
    struct Bst *adr;
    struct ptr *next;
};
struct ptr *head = NULL;
struct ptr *tail = NULL;

struct ptr *queue_push(struct Bst *node)
{
    struct ptr *temp = (struct ptr *)malloc(sizeof(struct ptr));
    temp->adr = node;

    if (head == NULL && tail == NULL)
    {
        temp->next = NULL;
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        temp->next = NULL;
        tail = temp;
    }
    return temp;
}

struct ptr *queue_front()
{
    return head;
}

void queue_pop()
{
    if (head == NULL)
    {
        return;
    }

    struct ptr *temp = head;
    head = head->next;
    free(temp);
}

bool queue_empty()
{
    if (head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void level_order(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    queue_push(node);

    while (queue_empty() == false)
    {
        struct ptr *current = queue_front();
        printf(" %lld ", current->adr->data);

        if (current->adr->left != NULL)
        {
            queue_push(current->adr->left);
        }
        if (current->adr->right != NULL)
        {
            queue_push(current->adr->right);
        }
        queue_pop();
    }
    head = NULL;
    tail = NULL;
}

//----------------------------------------------------------------------

struct Bst *find_min(struct Bst *node)
{
    if (node->left == NULL)
    {
        return node;
    }

    else if (node->left != NULL)
    {
        return find_min(node->left);
    }
}

struct Bst *Delete_node(struct Bst *node, long long int data)
{
    if (node == NULL)
    {
        return node;
    }
    else if (data < node->data)
    {

        node->left = Delete_node(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = Delete_node(node->right, data);
    }
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            node = NULL;
        }
        else if (node->left == NULL && node->right != NULL)
        {
            struct Bst *temp = node;
            node = node->right;
            free(temp);
        }
        else if (node->right == NULL && node->left != NULL)
        {
            struct Bst *temp = node;
            node = node->left;
            free(temp);
        }
        else
        {
            struct Bst *temp = find_min(node->right); /* find_max(node->left); */
            node->data = temp->data;
            node->right = Delete_node(node->right, temp->data); /*  node->left = Delete_node(node->left,temp->data); */
        }
    }
    return node;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

int main()
{

    long long int size;
    printf("size: ");
    scanf("%lld", &size);
    long long int data_arr[size];
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        data_arr[i] = rand() % 100;
        printf("%lld ", data_arr[i]);
        insert_new_node(root, data_arr[i]);
    }

    printf("\nlevel order: ");
    level_order(root);

    long long int n;
    printf("\nn= ");
    scanf("%lld", &n);
    Delete_node(root, n);

    return 0;
}
