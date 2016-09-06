#include <iostream>

struct hash
{
    unsigned hash_code;
    unsigned a, m;
    unsigned max_pow;
    hash(unsigned a, unsigned m)
    {
        this->a = a;
        this->max_pow = 1;
        this->m = m;
    }

    void asd(unsigned n)
    {
        for (unsigned i = 1; i < n; i++)
        {
            max_pow = ((unsigned long long)(max_pow)*a) % m;
        }
    }

    unsigned hashh(const std::string &s)
    {
        unsigned h = 0;
        for (size_t i = 0; i < s.size(); i++)
            h = ((((unsigned long long)(h)*a) % m) + s[i]) % m;
        return hash_code = h;
    }

    unsigned roll(char rem, char add)
    {
        hash_code += m;
        hash_code -= ((unsigned long long)(rem)*max_pow) % m;
        hash_code %= m;
        hash_code = ((unsigned long long)(hash_code)*a) % m;
        hash_code += add;
        hash_code %= m;
        return hash_code;
    }
};

int main()
{
    std::string text, patt;
    std::cin >> text >> patt;

    hash text_hash(256, 1e9 + 7);
    hash patt_hash(256, 1e9 + 7);

    text_hash.asd(patt.size());
    text_hash.hashh(text.substr(0, patt.size()));
    patt_hash.asd(patt.size());
    patt_hash.hashh(patt);
    if (text_hash.hash_code == patt_hash.hash_code)
    {
        if (text.substr(0, patt.size()) == patt)
            std::cout << 1 << "\n";
    }
    for (size_t i = patt.size(); i < text.size(); i++)
    {
        text_hash.roll(text[i - patt.size()], text[i]);
        if (text_hash.hash_code == patt_hash.hash_code)
        {
                std::cout << i - patt.size() + 2 << "\n";
        }
    }
}
