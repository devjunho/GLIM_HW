#include <iostream>
#include <vector>

int solution(std::vector<std::vector<int>> board, int k)
{
    int answer = 0;

    int i;
    int j;

    i = board.size();
    j = board[0].size();

    for(int y=0; y<i; y++)
    {
        for(int x=0; x<j; x++)
        {
            if(y+x <= k)
            {
                answer += board[y][x];
            }
        }
    }

    return answer;
}