#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a : b)

struct node
{
    int value;
    struct node *left;
    struct node *right;
    int height;
};

struct node *new_node(int value)
{
    struct node *res = (struct node *)malloc(sizeof(struct node));
    res->value = value;
    res->left = NULL;
    res->right = NULL;
    res->height = 1;
    return res;
}

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

struct node *rotate_right(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node *rotate_left(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int get_balance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node *insert(struct node *curr, int value)
{
    if (curr == NULL)
        return new_node(value);

    if (value < curr->value)
        curr->left = insert(curr->left, value);
    else
        curr->right = insert(curr->right, value);

    curr->height = max(height(curr->left), height(curr->right)) + 1;

    int balance = get_balance(curr);

    if (balance > 1 && value < curr->left->value)
        return rotate_right(curr);

    if (balance < -1 && value > curr->right->value)
        return rotate_left(curr);

    if (balance > 1 && value > curr->left->value)
    {
        curr->left = rotate_left(curr->left);
        return rotate_right(curr);
    }

    if (balance < -1 && value < curr->right->value)
    {
        curr->right = rotate_right(curr->right);
        return rotate_left(curr);
    }

    return curr;
}

struct node *once_right_alot_left(struct node *curr)
{
    struct node *curr1 = curr;

    while (curr1->left != NULL)
        curr1 = curr1->right;

    return curr1;
}

struct node *delete (struct node *curr, int value)
{
    if (curr == NULL)
        return curr;

    if (value < curr->value)
        curr->left = delete (curr->left, value);
    else if (value > curr->value)
        curr->right = delete (curr->right, value);
    else
    {
        if ((curr->left == NULL) || (curr->right == NULL))
        {
            struct node *temp = curr->left ? curr->left : curr->right;

            if (temp == NULL)
            {
                temp = curr;
                curr = NULL;
            }
            else
                *curr = *temp;

            free(temp);
        }
        else
        {
            struct node *temp = once_right_alot_left(curr->left);

            curr->value = temp->value;

            curr->right = delete (curr->right, temp->value);
        }
    }

    if (curr == NULL)
        return curr;

    curr->height = max(height(curr->left), height(curr->right)) + 1;

    int balance = get_balance(curr);

    if (balance > 1 && get_balance(curr->left) >= 0)
        return rotate_right(curr);

    if (balance > 1 && get_balance(curr->left) < 0)
    {
        curr->left = rotate_left(curr->left);
        return rotate_right(curr);
    }

    if (balance < -1 && get_balance(curr->right) <= 0)
        return rotate_left(curr);

    if (balance < -1 && get_balance(curr->right) > 0)
    {
        curr->right = rotate_right(curr->right);
        return rotate_left(curr);
    }

    return curr;
}

void print(struct node *curr)
{
    if (curr != NULL)
    {
        printf("%d ", curr->value);
        print(curr->left);
        print(curr->right);
    }
}

int main()
{
    struct node *curr = NULL;
    curr = insert(curr, 10);
    curr = insert(curr, 20);
    curr = insert(curr, 30);
    curr = insert(curr, 40);
    curr = insert(curr, 50);
    curr = insert(curr, 60);
    curr = insert(curr, 70);
    curr = insert(curr, 80);
    curr = insert(curr, 90);
    curr = insert(curr, 100);
    curr = delete(curr, 40);
    curr = delete(curr, 80);
    print(curr);
    printf("\n");
}
