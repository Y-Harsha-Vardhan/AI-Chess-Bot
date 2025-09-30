/*
sequence of numbers a1,a2,....,an such that a1>=a2>=a3....>=an . Initially all have same value k.
One who leads to sequence being empty loses
On each turn a person choses 1<=i<=n and some number alpha<ai and after that move aj=min(aj,alpha)
 
1 -> player playing first wins 

f(1) = 0
f(n) = 1 if n > 1


f(1,1) = 1
f(2,1) = 0
f(n,1) = 1 if n > 2 ( first player ensures that next state is (2,1) )


f(2,2) = 1 ( because of f(2,1) )

f(n,2) = !f(n) || !f(n,1) || !f(k,2) for k in [2,n)
f(n,2) = !f(k,2) for k in [2,n)

f(3,2) = 0
f(n,2) = 1 if n > 3

f(3,3) = 1 (coz of (3,2))
f(4,3) = 0

f(n+1,n) = 0
else f(a,b) = 1 given a,b>0

f(1,1,1) = 1
f(2,1,1) = 1
f(3,1,1) = 0
f(4,1,1) = 1
f(a,b,1) = !f(a,b) || !f(a,k,1) || !f(d,min(d,b),1) for d in [1,a) for k in [1,b) (a!=1)


In case of a square first player is always winning as they can chose the (2,2) square which leaves with L shaped structure which is always losing for the player playing first i.e second player who is the one playing the first move in L-shaped will lose.
*/

#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;

int main()
{
    map<vector<int>,bool> mp;
    mp[{0}] = 1;
    mp[{1}] = 0;
    for (int i =2 ; i <= 15 ; i++) mp[{i}] = 1;
    for (int i = 1 ; i <= 15 ; i++)
    {
        for (int j = 1 ; j<=i ; j++)
        {
        
            mp[{i,j}] = false;
            for (int t = j-1 ; t>0 ; t--)
            {
                if (!mp[{i,t}]) 
                {
                    mp[{i,j}] = true;
                }
            }
            if (!mp[{i}]) mp[{i,j}] = true;
            for (int k = i-1 ; k>0 ; k--)
            {
                if (!mp[{k,min(k,j)}]) mp[{i,j}] = true;
            }
        }
    }
    for (int i = 1 ; i <= 15 ; i++)
    {
        for (int j = 1 ; j<=i ; j++)
        {
            for (int k = 1 ; k<=j ; k++)
            {
                mp[{i,j,k}] = false;
                if (!mp[{i,j}]) mp[{i,j,k}] = true;
                for (int t=1 ; t<k ; t++)
                {
                    if (!mp[{i,j,t}]) mp[{i,j,k}] = true;
                }
                if (!mp[{i}]) mp[{i,j,k}] = true;
                for (int t = 1 ; t < j ; t++)
                {
                    if (!mp[{i,t,min(k,t)}]) mp[{i,j,k}] = true;
                }
                for (int t = 1 ; t < i ; t++)
                {
                    if (!mp[{t,min(t,j),min(t,k)}]) mp[{i,j,k}] = true;
                }

            }
        }
    }
    for (int first = 1 ; first <=15 ; first++)
    {
        for (int second = 1 ; second <=first ; second++)
        {
            for (int third = 1 ; third <= second ; third++)
            {
                    for (int fourth = 1 ; fourth <=third ; fourth++)
                    {
                        mp[{first,second,third,fourth}] = false;
                        if (!mp[{first}]) mp[{first,second,third,fourth}] = true;
                        if (!mp[{first,second}]) mp[{first,second,third,fourth}] = true;
                        if (!mp[{first,second,third}]) mp[{first,second,third,fourth}] = true;
                        for (int t = 1 ; t < fourth && !mp[{first,second,third,fourth}] ; t++)
                        {
                            if (!mp[{first,second,third,t}]) mp[{first,second,third,fourth}] = true;
                        }
                        for (int t = 1 ; t < third && !mp[{first,second,third,fourth}] ; t++)
                        {
                            if (!mp[{first,second,t,min(t,fourth)}]) mp[{first,second,third,fourth}] = true;
                        }
                        for (int t = 1 ; t < second && !mp[{first,second,third,fourth}] ; t++)
                        {
                            if (!mp[{first,t,min(third,t),min(t,fourth)}]) mp[{first,second,third,fourth}] = true;
                        }
                        for (int t = 1 ; t < first && !mp[{first,second,third,fourth}] ; t++)
                        {
                            if (!mp[{t,min(t,second),min(third,t),min(t,fourth)}]) mp[{first,second,third,fourth}] = true;
                        }

                    }  
            }  
        }   
    }
    for (auto it:mp)
    {
        if (!it.second and it.first.size()==3)
        {
            cout << it.first[1] << " " << it.first[2] << " -> " << it.first[0] << endl;
        }
        if (!it.second and it.first.size()==4)
        {
            cout << it.first[1] << " " << it.first[2] << " " << it.first[3] << " -> " << it.first[0] << endl;
        }
        
    }
}
