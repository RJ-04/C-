#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

struct Bst
{
    int data;
    struct Bst *left;
    struct Bst *right;
};
struct Bst *root = NULL;

//----------------------------------------------------------------------

struct Bst *create_new_node(int data)
{
    struct Bst *new_node = (struct Bst *)malloc(sizeof(struct Bst));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

//----------------------------------------------------------------------

struct Bst *insert_new_node(struct Bst *node, int data)
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

struct Bst *search_data(struct Bst *node, int data)
{
    if (node == NULL)
    {
        return NULL;
    }
    else if (node->data == data)
    {
        return node;
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

int find_height(struct Bst *node)
{
    if (node == NULL)
    {
        return 0;
    }

    int left_height = find_height(node->left);
    int right_height = find_height(node->right);

    if (left_height >= right_height)
    {
        return left_height + 1;
    }
    else if (right_height > left_height)
    {
        return right_height + 1;
    }
}

//----------------------------------------------------------------------

int find_diameter(struct Bst *node)
{
    if (node == NULL)
    {
        return 0;
    }

    int left_height = find_height(node->left);
    int right_height = find_height(node->right);

    int current_diammeter = left_height + right_height + 1;

    int left_diameter = find_diameter(node->left);
    int right_diameter = find_diameter(node->right);

    if (left_diameter >= right_diameter)
    {
        if (current_diammeter >= left_diameter)
        {
            return current_diammeter;
        }
        else if (left_diameter > current_diammeter)
        {
            return left_diameter;
        }
    }
    else if (right_diameter > left_diameter)
    {
        if (current_diammeter >= right_diameter)
        {
            return current_diammeter;
        }
        else if (right_diameter > current_diammeter)
        {
            return right_diameter;
        }
    }
}

int diameter(struct Bst *node, int *height)
{
    if (node == NULL)
    {
        *height = 0;
        return 0;
    }

    int left_height = 0, right_height = 0;

    int left_diameter = diameter(node->left, &left_height);
    int right_diameter = diameter(node->right, &right_height);

    int current_diameter = left_height + right_height + 1;
    if (left_height >= right_height)
    {
        *height = left_height + 1;
    }
    else
    {
        *height = right_height + 1;
    }

    if (left_diameter >= right_diameter)
    {
        if (current_diameter >= left_diameter)
        {
            return current_diameter;
        }
        else if (left_diameter > current_diameter)
        {
            return left_diameter;
        }
    }
    else if (right_diameter > left_diameter)
    {
        if (current_diameter >= right_diameter)
        {
            return current_diameter;
        }
        else if (right_diameter > current_diameter)
        {
            return right_diameter;
        }
    }
}

//----------------------------------------------------------------------

void Preorder(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    printf(" %d ", node->data);
    Preorder(node->left);
    Preorder(node->right);
}

void Inorder(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    Inorder(node->left);
    printf(" %d ", node->data);
    Inorder(node->right);
}

void Postorder(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    Postorder(node->left);
    Postorder(node->right);
    printf(" %d ", node->data);
}

//----------------------------------------------------------------------

int search(int inorder[], int start, int end, int current)
{
    for (int i = 0; i <= end; i = i + 1)
    {
        if (inorder[i] == current)
        {
            return i;
        }
    }
    return -1;
}

struct Bst *build_tree_using_preorder_inorder(int preorder[], int inorder[], int start, int end)
{
    static int idx = 0;
    if (start > end)
    {
        return NULL;
    }

    int current = preorder[idx];
    idx = idx + 1;
    struct Bst *node = create_new_node(current);
    if (start == end)
    {
        return node;
    }

    int pos = search(inorder, start, end, current);
    node->left = build_tree_using_preorder_inorder(preorder, inorder, start, pos - 1);
    node->right = build_tree_using_preorder_inorder(preorder, inorder, pos + 1, end);

    return node;
}

/* only a complete bst can be recreated using preorder and postorder */

struct Bst *build_tree_using_postorder_inorder(int postorder[], int inorder[], int start, int end)
{
    static int idx = 4;
    if (start > end)
    {
        return NULL;
    }

    int current = postorder[idx];
    idx = idx - 1;
    struct Bst *node = create_new_node(current);
    if (start == end)
    {
        return node;
    }

    int pos = search(inorder, start, end, current);
    node->right = build_tree_using_postorder_inorder(postorder, inorder, pos + 1, end);
    node->left = build_tree_using_postorder_inorder(postorder, inorder, start, pos - 1);

    return node;
}

//----------------------------------------------------------------------

bool is_bst_util(struct Bst *node, int min_value, int max_value)
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
    return is_bst_util(node, INT_MIN, INT_MAX);
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
    temp->next = NULL;

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

int queue_size()
{
    if (queue_empty() == true)
    {

        return 0;
    }

    int size = 1;
    struct ptr *temp = head;

    while (temp != tail)
    {
        size = size + 1;
        temp = temp->next;
    }
    return size;
}

void level_order(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    queue_push(node);

    while (!queue_empty())
    {
        struct ptr *current = queue_front();

        printf(" %d ", current->adr->data);
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

struct Bst *Delete_node(struct Bst *node, int data)
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

struct Bst *get_successor(struct Bst *node, int data)
{
    struct Bst *current = search_data(node, data);
    if (current == NULL)
    {
        return NULL;
    }
    if (current->right != NULL)
    {
        return find_min(current->right);
    }
    else
    {
        struct Bst *successor = NULL;
        struct Bst *ancestor = node;
        while (ancestor != current)
        {
            if (current->data < ancestor->data)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
            {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}

//----------------------------------------------------------------------

int count_nodes(struct Bst *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return (count_nodes(node->left) + count_nodes(node->right) + 1);
}

//----------------------------------------------------------------------

int sum_nodes(struct Bst *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return (sum_nodes(node->left) + sum_nodes(node->right) + (node->data));
}

//----------------------------------------------------------------------

int sum_replace(struct Bst *node)
{
    if (node == NULL)
    {
        return 0;
    }

    int left_subtree_sum = sum_replace(node->left);
    int right_subtree_sum = sum_replace(node->right);

    return (node->data = left_subtree_sum + right_subtree_sum + node->data);
}

//----------------------------------------------------------------------
bool IS_Balanced(struct Bst *node, int *height)
{
    if (node == NULL)
    {
        return true;
    }

    int left_height = 0;
    int right_height = 0;

    if (IS_Balanced(node->left, &left_height) == false)
    {
        return false;
    }
    if (IS_Balanced(node->right, &right_height) == false)
    {
        return false;
    }

    if (left_height >= right_height)
    {
        *height = left_height + 1;
    }
    else
    {
        *height = right_height + 1;
    }
    if ((left_height - right_height) <= 1 && (left_height - right_height) >= -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_baalanced(struct Bst *node)
{
    if (node == NULL)
    {
        return true;
    }

    if (is_baalanced(node->left) == false)
    {
        return false;
    }
    if (is_baalanced(node->right) == false)
    {
        return false;
    }

    int left_height = find_height(node->left);
    int right_height = find_height(node->right);

    if ((left_height - right_height) <= 1 && (left_height - right_height) >= -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//----------------------------------------------------------------------

void right_view(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    queue_push(node);

    while (!queue_empty())
    {
        int n = queue_size();

        for (int i = 0; i < n; i = i + 1)
        {
            struct ptr *current = queue_front();

            if (i == n - 1)
            {
                printf("%d ", current->adr->data);
            }
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
    }
    head = NULL;
    tail = NULL;

    return;
}

void left_view(struct Bst *node)
{
    if (node == NULL)
    {
        return;
    }

    queue_push(node);

    while (!queue_empty())
    {
        int n = queue_size();

        for (int i = 0; i < n; i = i + 1)
        {
            struct ptr *current = queue_front();

            if (i == 0)
            {
                printf("%d ", current->adr->data);
            }
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
    }
    head = NULL;
    tail = NULL;

    return;
}

//----------------------------------------------------------------------

struct Bst *lowest_common_ancestor(struct Bst *node, int n, int m)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->data == n || node->data == m)
    {
        return node;
    }

    struct Bst *left = lowest_common_ancestor(node->left, n, m);
    struct Bst *right = lowest_common_ancestor(node->right, n, m);

    if (left != NULL && right != NULL)
    {
        return node;
    }
    if (left == NULL && right == NULL)
    {
        return NULL;
    }
    if (left != NULL)
    {
        return lowest_common_ancestor(node->left, n, m);
    }

    return lowest_common_ancestor(node->right, n, m);
}

//----------------------------------------------------------------------

int find_distance(struct Bst *node, int k, int distance)
{
    if (node == NULL)
    {
        return -1;
    }
    if (node->data == k)
    {
        return distance;
    }

    int left = find_distance(node->left, k, distance + 1);
    if (left != -1)
    {
        return left;
    }

    return find_distance(node->right, k, distance + 1);
}

int distance_between_nodes(struct Bst *node, int n, int m)
{
    struct Bst *lca = lowest_common_ancestor(node, n, m);

    int d1 = find_distance(lca, n, 0);
    int d2 = find_distance(lca, m, 0);

    return (d1 + d2);
}

//----------------------------------------------------------------------

void flatten(struct Bst *node)
{
    if (node == NULL || (node->left == NULL && node->right == NULL))
    {
        return;
    }

    if (node->left != NULL)
    {
        flatten(node->left);

        struct Bst *temp = node->right;
        node->right = node->left;
        node->left = NULL;

        struct Bst *t = node->right;
        while (t->right != NULL)
        {
            t = t->right;
        }
        t->right = temp;
    }

    flatten(node->right);
}

//----------------------------------------------------------------------

void print_subtree(struct Bst *node, int k) /* case 1  */
{
    if (node == NULL || k < 0)
    {
        return;
    }

    if (k == 0)
    {
        printf("%d ", node->data);
        return;
    }

    print_subtree(node->left, k - 1);
    print_subtree(node->right, k - 1);
}

int print_nodes_at_k(struct Bst *node, struct Bst *target, int k)
{
    if (node == NULL)
    {
        return -1;
    }

    if (node == target)
    {
        print_subtree(node, k);
        return 0;
    }

    int distance_left = print_nodes_at_k(node->left, target, k);
    if (distance_left != -1)
    {
        if ((distance_left + 1) == k)
        {
            printf("%d ", node->data);
        }
        else
        {
            print_subtree(node->right, k - distance_left - 2);
        }
        return (distance_left + 1);
    }
    int distance_right = print_nodes_at_k(node->right, target, k);
    if (distance_right != -1)
    {
        if ((distance_right + 1) == k)
        {
            printf("%d ", node->data);
        }
        else
        {
            print_subtree(node->left, k - distance_right - 2);
        }
        return (distance_right + 1);
    }

    return -1;
}

//----------------------------------------------------------------------

int max(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int max_path_sum_util(struct Bst *node, int *ans)
{
    if (node == NULL)
    {
        return 0;
    }

    int left = max_path_sum_util(node->left, ans);
    int right = max_path_sum_util(node->right, ans);

    int node_max = max(
        max(node->data, node->data + left + right),
        max(node->data + left, node->data + right));

    *ans = max(*ans, node_max);
    int single_path_sum = max(node->data, max(node->data + left, node->data + right));

    return single_path_sum;
}

int max_path_sum(struct Bst *node)
{
    int ans = INT_MIN;
    max_path_sum_util(node, &ans);
    return ans;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

int main()
{
    // int size;
    // int height = 0;
    // printf("size: ");
    // scanf("%d", &size);
    // int data_arr[size];
    // srand(time(NULL));

    // for (int i = 0; i < size; i++)
    // {
    //     data_arr[i] = rand() % 10;
    //     printf("%d ", data_arr[i]);
    //     insert_new_node(root, data_arr[i]);
    // }
    root = create_new_node(-1);
    root->left = create_new_node(-2);
    root->right = create_new_node(3);
    root->left->left = create_new_node(-4);
    root->right->right = create_new_node(5);

    printf("\n%d ", max_path_sum(root));

    return 0;
}
