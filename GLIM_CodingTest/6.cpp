#include <iostream>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, vector<int> query)
{
    vector<int> answer;

    for (int i=0; i<(int)query.size(); i++)
    {
        if(i%2 == 0)    // 0 or 짝수 인덱스
        {
            if(query[i]+1 < (int)arr.size())
            {
                arr.erase(arr.begin() + query[i] + 1, arr.end());
            }
        }
        else            // 홀수 인덱스
        {
            if(query[i] > 0)
            {
                arr.erase(arr.begin(), arr.begin() + query[i]);
            }
        }
    }

    answer = arr;

    return answer;
}