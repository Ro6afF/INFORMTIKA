#include <vector>


int QmKuftaci(int min_ball,int max_ball,int current_number_balls)
{
    std::vector<bool> t;
    t.resize((unsigned int) (-1) / 2);
    t[0] = false;
    for(int i = 1; i < current_number_balls; i++)
    {
        if(i < min_ball)
        {
            t[i] = false;
        }
        else if (i < max_ball)
        {
            t[i] = true;
        }
        else
        {
            for(int j = min_ball; j <= max_ball; i++)
            {
                if(t[i - j])
                {
                    t[i] = true;
                    goto Go;
                }
            }
            t[i] = false;
Go:
            i++;
            i--;
        }
    }
    for(int i = min_ball; i <= max_ball; i++)
    {
        if(!t[current_number_balls - i])
        {
            return i;
        }
    }
    return -1;
}
