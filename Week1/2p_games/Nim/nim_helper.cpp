#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
int main()
{
    map<multiset<int>,bool> mp;
    mp[{1}]=1;mp[{2}]=1;mp[{3}]=1;mp[{4}]=1;mp[{5}]=1;mp[{6}]=1;mp[{7}]=1;
    for (int i = 1; i<=7 ; i++)
    {
    
        for (int j = i ; j<=7 ; j++)
        {
            if (i==1)
            {
                mp[{i,j}]=false ;
                for (int k = 1; k<j ; k++)
                {
                    if (!mp[{1,k}])
                    {
                        mp[{i,j}]=1;
                        break;
                    }
                }

            }
            else
            {
                mp[{i,j}] = false;
                for (int k = 1; k<j ; k++)
                {
                    if (!mp[{i,k}])
                    {
                        mp[{i,j}]=1;
                        break;
                    }
                }
                for (int k = 1 ; k < i ; k++)
                {
                    if (!mp[{k,j}])
                    {
                        mp[{i,j}]=1;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1 ; i <=7 ; i++)
    {
        for (int j = i ; j<=7 ; j++)
        {
            for (int k = j ; k<=7  ; k++)
            {
                
                mp[{i,j,k}]=!mp[{i,j}] || !mp[{i,k}] || !mp[{j,k}];
                
                for (int t = 1; t < i ; t++)
                {
                    if (!mp[{t,j,k}])
                    {
                        mp[{i,j,k}]=1;
                        break;
                    }
                }
                for (int t = 1; t < j ; t++)
                {
                    if (!mp[{i,t,k}])
                    {
                        mp[{i,j,k}]=1;
                        break;
                    }
                }
                for (int t = 1; t < k ; t++)
                {
                    if (!mp[{i,j,t}])
                    {
                        mp[{i,j,k}]=1;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1 ; i <=7 ; i++)
    {
        for (int j = i ; j<=7 ; j++)
        {
            for (int k = j ; k<=7  ; k++)
            {
                for (int a = k ; a<= 7 ; a++)
                {
                    mp[{i,j,k,a}]=!mp[{i,j,k}] || !mp[{i,k,a}] || !mp[{j,k,a}] || !mp[{i,j,a}];
                
                    for (int t = 1; t < i && !mp[{i,j,k,a}] ; t++)
                    {
                        if (!mp[{t,j,k,a}])
                        {
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                    for (int t = 1; t < j && !mp[{i,j,k,a}]; t++)
                    {
                        if (!mp[{i,t,k,a}])
                        {
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                    for (int t = 1; t < k && !mp[{i,j,k,a}] ; t++)
                    {
                        if (!mp[{i,j,t,a}])
                        {
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                    for (int t = 1; t < a && !mp[{i,j,k,a}] ; t++)
                    {
                        if (!mp[{i,j,k,t}])
                        {
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                }
            }
        }
    }
}