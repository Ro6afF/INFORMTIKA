#include <iostream>
#include <string>

struct node
{
    bool isEnd;
    node *children[30];
};

node *root;

void add(std::string str)
{
    node *curr = root;

    for (int i = 0; i < (int)str.size(); i++)
    {
        int ch = str[i] - 'a';
        if (curr->children[ch] == nullptr)
        {
            curr->children[ch] = new node();
        }
        curr = curr->children[ch];
    }
    curr->isEnd = true;
}

void remove(std::string str)
{
    node *curr = root;
    for (int i = 0; i < (int)str.size(); i++)
    {
        int ch = str[i] - 'a';
        curr = curr->children[ch];
    }
    curr->isEnd = false;
}

bool has(std::string str)
{
    node *curr = root;
    for (int i = 0; i < (int)str.size(); i++)
    {
        int ch = str[i] - 'a';
        if (curr->children[ch] == nullptr)
        {
            return false;
        }
        curr = curr->children[ch];
    }
    return curr->isEnd;
}

int main()
{
    root = new node();
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::string str;
        std::cin >> str;
        if (str == "add")
        {
            std::cin >> str;
            add(str);
        }
        else if (str == "rem")
        {
            std::cin >> str;
            remove(str);
        }
        else
        {
            std::cin >> str;
            std::cout << has(str) << std::endl;
        }
    }
    return 0;
}
