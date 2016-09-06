#include <iostream>

#define max(a, b) ((a > b) ? a : b)

struct node
{
    long long value;
    struct node *left;
    struct node *right;
    long long left_tree;
};

struct node *new_node(long long value)
{
    struct node *res = new node();
    res->value = value;
    res->left = nullptr;
    res->right = nullptr;
    res->left_tree = 1;
    return res;
}

struct node *insert(struct node *curr, long long value)
{
    if (curr == nullptr)
        return new_node(value);

    if (value < curr->value)
    {
        curr->left_tree++;
        curr->left = insert(curr->left, value);
    }
    else
        curr->right = insert(curr->right, value);

    return curr;
}

struct node *once_right_alot_left(struct node *curr)
{
    struct node *curr1 = curr;
    while (curr1->right != nullptr)
        curr1 = curr1->right;

    return curr1;
}

struct node *remove(struct node *root, long long value)
{
    if (root == nullptr)
        return root;

    if (value < root->value)
    {
        root->left_tree --;
        root->left = remove(root->left, value);
    }
    else if (value > root->value)
        root->right = remove(root->right, value);
    else
    {
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            struct node *temp;
            if(root->left)
            {
                root->left_tree --;
                temp = root->left;
            }
            else
            {
                temp = root->right;
            }
            
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else               
                *root = *temp; 

            free(temp);
        }
        else
        {
            root->left_tree --;
            struct node *temp = once_right_alot_left(root->left);
            
            root->value = temp->value;
            root->right = remove(root->right, temp->value);
        }
    }

    if (root == nullptr)
        return root;

    return root;
}

long long res;

void find(struct node *curr, long long value)
{
    if (value < curr->value)
    {
        find(curr->left, value);
    }
    else if (value > curr->value)
    {
        res += curr->left_tree;
        find(curr->right, value);
    }
    else
    {
        res += curr->left_tree;
    }
}

void find2(struct node *curr)
{
    if (res < curr->left_tree)
    {
        find2(curr->left);
    }
    else if (res > curr->left_tree)
    {
        res -= curr->left_tree;
        find2(curr->right);
    }
    else
    {
        std::cout << curr->value << '\n';
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    struct node *curr = nullptr;

    long long q;
    std::cin >> q;

    for (long long i = 0; i < q; i++)
    {
        char ch;
        std::cin >> ch;
        if (ch == 'a')
        {
            long long n;
            std::cin >> n;
            curr = insert(curr, n);
        }
        if (ch == 'r')
        {
            long long n;
            std::cin >> n;
            curr = remove(curr, n);
        }
        if (ch == '[')
        {
            long long x;
            std::cin >> x;
            res = x;
            find2(curr);
        }
        if (ch == 'i')
        {
            long long n;
            std::cin >> n;
            res = 0;
            find(curr, n);
            std::cout << res << '\n';
        }
    }
}
