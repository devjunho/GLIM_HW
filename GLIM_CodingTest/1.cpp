#include <iostream>

int solution (int n, int k)
{
    int answer = 0;
    int bonusDrink = 0;

    while (n <= 0 || 1000 <= n)
    {
        std::cout << "양꼬치 인분 수가 잘못 입력되었습니다. 다시 입력해주세요: "<< std::endl;
        std::cin >> n;
    }
    
    while (k < n/10 || 1000 <= k)
    {
        std::cout << "음료수 수량이 잘못 입력되었습니다. 다시 입력해주세요: " << std::endl;
        std::cin >> k;
    }

    if (10 <= n)
    {
        bonusDrink = n / 10;
    }

    answer = n * 12000 + k * 2000 - bonusDrink * 2000;

    return answer;
}