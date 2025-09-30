#include<iostream>
#include<vector>
#include<utility>
#include<string>
using namespace std;

void display_board(vector<vector<char> > board)
{
    int n = board.size();
    cout << "  ";
    for (int i = 0; i < n; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << i << " ";
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
int game_ends(const vector<vector<char> > &board)
{
    int n = board.size();
    for (int i = 0; i < n; i++) {
        if (board[0][i]  == 'B') return -1;
    }
        
    for (int i = 0; i < n; i++) {
        if (board[n-1][i] == 'W') return 1;
    }
        
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j]=='W')
            {
                if (board[i+1][j] == '*')
                    return 2;
                if (j>0 and board[i+1][j-1]=='B')
                    return 2;
                if (j<n-1 and board[i+1][j+1]=='B')
                    return 2;
            }
            else if (board[i][j]=='B')
            {
                if (board[i-1][j] == '*')
                    return 2;
                if (j>0 and board[i-1][j-1] == 'W')
                    return 2;
                if (j<n-1 and board[i-1][j+1]=='W')
                    return 2;      
            }          
            else
            {
                continue;
            }
        }
    }
        
    return 0;
}
int analyze(vector<vector<char> > &board,bool white_move, vector<int> &greatest_move)
{
    int n = board.size();
    // display_board()
    // board is a list of list and white_move is a bool variable'''
    int ans = game_ends(board);
    if (ans!=2) return ans;

    if (white_move)
    {
        int temp = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
                if (board[i][j] == 'W')
                {
                    board[i][j] = '*';
                    if (board[i+1][j] == '*')
                    {
                        board[i+1][j] = 'W';
                        int t= analyze(board,!white_move,greatest_move);
                        if (temp < t)
                        {
                            temp = t;
                            greatest_move = {i,j,i+1,j};
                        }
                        board[i+1][j] = '*';
                        if (temp==1)
                        {
                            board[i][j] = 'W';
                            return 1;
                        }
                    }
                        
                    if (j>0 and board[i+1][j-1]=='B')
                    {
                        board[i+1][j-1] = 'W';
                        int t= analyze(board,! white_move,greatest_move);
                        if (temp < t)
                        {
                            temp = t;
                            greatest_move = {i,j,i+1,j-1};
                        }
                        board[i+1][j-1] = 'B';
                        if (temp==1)
                        {
                            board[i][j] = 'W';
                            return 1;
                        }
                    }
                    
                        
                    if (j!=n-1 and board[i+1][j+1]=='B' )
                    {
                        board[i+1][j+1] = 'W';
                        
                        int t= analyze(board,! white_move,greatest_move);
                        if (temp < t)
                        {
                            temp = t;
                            greatest_move = {i,j,i+1,j+1};
                        }
                        board[i+1][j+1] = 'B';
                        if (temp==1)
                        {
                            board[i][j] = 'W';
                            return 1;
                        }
                    }
                        
                    board[i][j] = 'W';
                }
            }
        }
        return temp;
    }

    int temp = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (board[i][j] == 'B')
            {
                board[i][j] = '*';
                if (board[i-1][j] == '*')
                {
                    board[i-1][j] = 'B';
                    int t = analyze(board,! white_move,greatest_move);
                    if (temp > t)
                    {
                        temp = t;
                        greatest_move = {i,j,i-1,j};
                    }
                    board[i-1][j] = '*';
                    if (temp==-1)
                    {
                        board[i][j] = 'B';
                        return -1;
                    }
                }
                if (j>0 and board[i-1][j-1]=='W')
                {
                    board[i-1][j-1] = 'B';
                    int t= analyze(board,! white_move,greatest_move);
                    if (temp > t)
                    {
                        temp = t;
                        greatest_move = {i,j,i-1,j-1};
                    }
                    board[i-1][j-1] = 'W';
                    if (temp==-1)
                    {
                        board[i][j] = 'B';
                        return -1;
                    }
                }
                if (j!=n-1 and board[i-1][j+1]=='W' )
                {
                    board[i-1][j+1] = 'B';
                    int t= analyze(board,! white_move,greatest_move);
                    if (temp > t)
                    {
                        temp = t;
                        greatest_move = {i,j,i-1,j+1};
                    }
                    board[i-1][j+1] = 'W';  
                    if (temp==-1)
                    {
                        board[i][j] = 'B';
                        return -1;
                    }   
                }
                board[i][j] = 'B';
            }
        }
}
    return temp;
}

int main()
{
    vector<int> greatest_move(4);
    vector<vector<char> > board = {{'W','W','*','W','W'},{'*','*','W','*','*'},{'*','*','*','*','*'},{'*','*','*','*','*'},{'B','B','B','B','B'}};
    //vector<vector<char> > board = {{'*','W','W','W'},{'W','*','*','*'},{'*','*','*','*'},{'B','B','B','B'}};
    cout << analyze(board,false,greatest_move);
    cout << endl;
    for (auto it:greatest_move)
    {
        cout << it;
    }
    cout << endl;
    for (auto it:board)
    {
        for (auto it1:it)
        {
            cout << it1;
        }
        cout << endl;
    
    }
}
// leftmost or rightmost ->  0 
// If you push pawns second from the end -> 0
// middle pawn -> 1
