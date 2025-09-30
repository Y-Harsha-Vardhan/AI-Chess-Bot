#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;
void evaluate(map<vector<int>,bool> &mp , int len , vector<int> &nums, vector<int> &temp , int index)
{
    // evaluates chomp position for a given length
    if (index == len)
    {
        if (mp[temp]) return;
        mp[temp] = false;
        for (int i = len-1 ; i >= 0 && !mp[temp] ; i--)
        {
            for (int val = 0 ; val < temp[i] && !mp[temp] ; val++)
            {
                vector<int> a(temp.begin(),temp.end());
                for (int j = i + 1; j < len ; j++)
                {
                    a[j] = min(a[j],val);
                }
                if (!mp[a]) mp[temp] = true;
            }
            
        }
        return;
    }
    for (int i = 1 ; i <= nums[index] ; i++)
    {
        if (index && i > temp[index-1]) break;
        temp[index] = i;
        evaluate(mp,len,nums,temp,index+1);
    }
    return;
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    
    for (int i = 0 ; i < n ; i++) cin>>nums[i];
    int max_num = nums[0];
    map<vector<int>,bool> mp;

    vector<int> temp(n,0);
    mp[temp] = true;
    temp[0] = 1;
    mp[temp] = false;
    for (int i = 2 ; i < nums[0] ; i++)
    {
        temp[0] = i;
        mp[temp] = true;
    }
    for (int len = 2; len <= n ; len++)
    {
        vector<int> temp(n,0);
        evaluate(mp,len,nums,temp,0);
    }
    for (auto it:mp)
    {
        for (auto it1:it.first) cout<<it1<<" ";
        if (it.second) cout<<"W";
        else cout<<"L";
        cout << endl;
    }
}