#include <iostream>

int calculation(int a, int b)
{
    int answer = 0;

    if(1<=b && b<10)
    {
        a *= 10;
    }
    else if(b<100)
    {
        a *= 100;
    }
    else if(b<1000)
    {
        a *= 1000;
    }
    else
    {
        a *= 10000;
    }

    answer = a + b;

    return answer;
}


int solution(int a, int b)
{
    int answer = 0;

    int frist = 0;
    int second = 0;

    frist = calculation(a, b);

    second = calculation(b, a);

    if(frist >= second)
    {
        answer = frist;
    }
    else
    {
        answer = second;
    }

    return answer;
}