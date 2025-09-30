n = int(input("Enter the size of the board : "))

white = True
board = [['W']*n]
L = [['*' for _ in range(n)] for _ in range(n-2)]
board.extend(L)
board.append(['B']*n)

def display_board():
    global board
    print("  ",end="")
    for i in range(n):
        print(i,end=' ')
    print()

    for i in range(n):
        print(i,end = " ")
        for j in range(n):
            print(board[i][j],end = ' ')
        print()
def game_ends(board):
    
    for i in range(n):
        if board[0][i]   == 'B':
            return -1
        
    for i in range(n):
        if board[n-1][i] == 'W':
            return 1
        
    for i in range(n):
        for j in range(n):
            if board[i][j]=='W':
                if board[i+1][j] == '*':
                    return False
                if j>0 and board[i+1][j-1]=='B':
                    return False
                if j<n-1 and board[i+1][j+1]=='B':
                    return False
            elif board[i][j]=='B':
                if board[i-1][j] == '*':
                    return False
                if j>0 and board[i-1][j-1] == 'W':
                    return False
                if j<n-1 and board[i-1][j+1]=='W':
                    return False                
            else:
                pass
    return 0
while True:
    display_board()
    if white == True:
        
        while True:
            valid_move = False
            move = input("Enter your move as white ").strip()
            if len(move)!=4:
                print("You entered invalid move")
                continue
            final_x,final_y,initial_x,initial_y = list(map(int,list(move)))

            if initial_x<0 or initial_x>=n or initial_y<0 or initial_y>=n or final_x<0 or final_y<0 or final_x>=n or final_y>=n or final_x!=initial_x+1:
                print("You entered invalid move")
                continue
            if board[initial_x][initial_y] == 'W':
                if final_y==initial_y:
                    if board[final_x][final_y] == '*':
                        
                        board[initial_x][initial_y] = '*'
                      
                        board[final_x][final_y] = 'W'
                        
                        valid_move = True
                    else:
                        print("You entered invalid move")
                        continue                    
                elif final_y == initial_y + 1 or final_y == initial_y - 1 :
                    if board[final_x][final_y] == 'B':
                        board[final_x][final_y] = 'W'
                        board[initial_x][initial_y] = '*'
                        valid_move = True
                    else:
                        print("You entered invalid move")
                        continue    
                else:
                    print("You entered invalid move")
                    continue                      
            else:
                print("You entered invalid move")
                continue

            if valid_move:
                break

    else:
        
        while True:
            valid_move = False
            move = input("Enter your move as black ").strip()
            if len(move)!=4:
                print("You entered invalid move")
                continue
            final_x,final_y,initial_x,initial_y = list(map(int,list(move)))

            if initial_x<0 or initial_x>=n or initial_y<0 or initial_y>=n or final_x<0 or final_y<0 or final_x>=n or final_y>=n or final_x!=initial_x-1:
                print("You entered invalid move")
                continue
            if board[initial_x][initial_y] == 'B':
                if final_y==initial_y:
                    if board[final_x][final_y] == '*':
                        board[initial_x][initial_y] = '*'
                        board[final_x][final_y] = 'B'
                        valid_move = True
                    else:
                        print("You entered invalid move")
                        continue                    
                elif final_y == initial_y + 1 or final_y == initial_y - 1 :
                    if board[final_x][final_y] == 'W':
                        board[final_x][final_y] = 'B'
                        board[initial_x][initial_y] = '*'
                        valid_move = True
                    else:
                        print("You entered invalid move")
                        continue 
                else:
                    print("You entered invalid move")
                    continue                                   
            else:
                print("You entered invalid move")
                continue

            if valid_move:
                break
    white = not white

    result = game_ends(board)

    if type(result) == type(1):
        if result == 0:
            print("\nIt's a draw")
        elif result == -1:
            print("\nBlack wins") 
        else:
            print("\nWhite wins")
        exit(0)
