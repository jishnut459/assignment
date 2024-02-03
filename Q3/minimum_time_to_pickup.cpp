#include <bits/stdc++.h>

using namespace std;

int minTimeToPickup(vector<string> &courier, vector<int> &travel)
{
    int n = courier.size();
    vector<int> cumulativeTime(n, 0);
    for (int j = 1; j <= travel.size(); j++)
    {
        cumulativeTime[j] = cumulativeTime[j - 1] + travel[j - 1];
    }

    int s_time = 0, m_time = 0, l_time = 0;
    int s_pos = 0, m_pos = 0, l_pos = 0;

    for (int i = 0; i < n; i++)
    {
        int s_count = 0, m_count = 0, l_count = 0;

        for (char c : courier[i])
        {
            switch (c)
            {
            case 'S':
                s_count++;
                break;
            case 'M':
                m_count++;
                break;
            case 'L':
                l_count++;
                break;
            }
        }

        if (s_count)
        {
            s_time += (cumulativeTime[i] - cumulativeTime[s_pos]) + s_count;
            s_pos = i;
        }
        if (m_count)
        {
            m_time += (cumulativeTime[i] - cumulativeTime[m_pos]) + m_count;
            m_pos = i;
        }
        if (l_count)
        {
            l_time += (cumulativeTime[i] - cumulativeTime[l_pos]) + l_count;
            l_pos = i;
        }
    }

    return (s_time + m_time + l_time);
}

int main()
{
    vector<string> courier1 = {"L", "M", "LM", "LL"};
    vector<int> travel1 = {2, 4, 3};
    int time = minTimeToPickup(courier1, travel1);
    cout << "Example 1: " << time << " minutes" << endl;

    vector<string> courier2 = {"SSS", "MLS", "LM"};
    vector<int> travel2 = {3, 10};
    cout << "Example 2: " << minTimeToPickup(courier2, travel2) << " minutes" << endl;

    return 0;
}
