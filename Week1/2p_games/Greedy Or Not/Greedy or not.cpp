#include<iostream>
using namespace std;
int main()
{
    cout << "Enter the size of the list\n";
    int n;
    cin>>n;
    int a[n];
    cout << "Enter the elements of the list\n";
    for (int i = 0 ; i < n ; i++)
    {
        cin >> a[i];
    }

    // dp[i][j] represents the difference between points of first and second player if the indices between i and i+j-1 (including both) are presented(i.e. numbers in those indices are the only ones valid for playing) and both play optimally.
    int dp[n][n+1];
    for (int start = 0 ; start < n ;start++)
    {
        dp[start][1] = a[start];
    }
    for (int len = 2 ; len<=n ; len++)
    {
        for (int start = 0 ; start <= n-len ; start++)
        {
            dp[start][len]= max(a[start]-dp[start+1][len-1],a[start+len-1]-dp[start][len-1]);
        }
    }
    if (dp[0][n] > 0)
    {
        cout << "Player1 wins";
    } 
    else if (dp[0][n] == 0)
    {
        cout << "Draw";
    }
    else
    {
        cout << "Player2 wins";
    }
}
