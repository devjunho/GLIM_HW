#include <iostream>
#include <string>

int solution(std::string my_string, std::string is_prefix)
{
    int answer = 0;

    for (int i=0; i<(int)is_prefix.size(); i++)
    {
        if (my_string[i] != is_prefix[i])
        {
            return answer;
        }
    }
    
    answer = 1;

    return answer;
}