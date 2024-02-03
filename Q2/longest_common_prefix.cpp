#include <bits/stdc++.h>
using namespace std;

string longestCommonPrefix(vector<string> &strs)
{
    if (strs.size() == 0)
        return "";

    string prefix = strs[0];

    for (int i = 0; i < strs.size(); i++)
    {
        while (strs[i].find(prefix) != 0)
        {
            prefix = prefix.substr(0, prefix.length() - 1);
        }
    }
    return prefix;
}

// Alternate solution if we are allowed to sort the array
string longestCommonPrefix2(vector<string> &strs)
{
    string prefix = "";
    sort(strs.begin(), strs.end());
    string first = strs[0];
    string last = strs[strs.size() - 1];

    for (int i = 0; i < first.size(); i++)
    {
        if (first[i] == last[i])
            prefix += first[i];
        else
            break;
    }
    return prefix;
}

int main()
{
    vector<string> strs = {"flower", "flow", "flight"};
    string result1 = longestCommonPrefix(strs);
    string result2 = longestCommonPrefix2(strs);

    cout << "Longest common prefix : " << endl;
    cout << "Solution 1 : " << result1 << endl;
    cout << "Solution 2 : " << result2 << endl;

    return 0;
}
