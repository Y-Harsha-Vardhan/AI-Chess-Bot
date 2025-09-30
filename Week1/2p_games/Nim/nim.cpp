#include<iostream>
#include<cstdlib>
using namespace std;
void computer_move(int * nums , int n)
{
    int Xor = 0;
    for (int i = 0 ; i < n ; i++) Xor ^= nums[i];
    
    if (Xor == 0)
    {
        // Computer can't win so just play a random move.
        for (int i = 0 ; i < n ; i++)
        {
            if (nums[i])
            {
                nums[i] = rand()%nums[i];
                break;
            }
        }
        return;
    }
    int k = 1;
    int XXor = Xor;
    while (Xor)
    {
        Xor >>= 1;
        k <<= 1;
    }
    k>>=1;
    
    // k finally becomes largest power of 2 in binary representation of variable Xor
    for (int i = 0; i < n ; i++)
    {
        if (nums[i] & k)
        {
            nums[i] = nums[i] ^ XXor;
            return;
        }
    }
}
bool end(int * nums , int n)
{
    for (int i = 0 ; i < n ; i++) 
    {
        if (nums[i]) return false;
    }
    return true;
}
int main()
{
    int n ;
    cout << "Enter the number of elements: ";
    cin >> n;
    int nums[n];
    cout << "Enter the elements";

    int Xor = 0;
    for (int i = 0 ; i < n ; i++)
    {
        cin >> nums[i];
        Xor ^= nums[i];
    }
    // if (Xor == 0)
    // {
    //     cout << "Player moving first loses";
    // }
    // else
    // {
    //     cout << "Player moving first wins";
    // }

    cout << "Do you want to play the first move (enter y/n): ";
    char input; bool player_move;
    cin >> input;

    if (input == 'y') player_move = true;
    else player_move = false;

    while (true)
    {
        if (player_move)
        {
            for (int i = 0 ; i < n ; i++)
            {
                cout << nums[i] << " ";  
            }
            cout << "\n";
            while (true)
            {
                cout << "Enter your move: ";
                int row , value;
                cin >> row >> value;
                if (row >0 && row <=n && value>=0 && nums[row-1] > value)
                {
                    nums[row-1] = value;
                    break;
                }
                else
                {
                    cout << "Invalid move\n";
                }
            }
            for (int i = 0 ; i < n ; i++)
            {
                cout << nums[i] << " ";  
            }
            cout << "\n";

            if (end(nums,n)) 
            {
                cout << "Congratulations!! You won";
                return 0;
            }
        }
        else
        {
            computer_move(nums,n);
            for (int i = 0 ; i < n ; i++)
            {
                cout << nums[i] << " ";  
            }
            cout << "\n";
            if (end(nums,n)) 
            {
                cout << "Sorry! You lost";
                return 0;
            }
        }
        player_move = !player_move;
    }

}