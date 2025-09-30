n = int(input("How many rows do you want: "))

L = [2*i+1 for i in range(n)]

player1 = True
def display():
    for i in range(n):
        print((i+1),"   ","  "*(n-i-1),"* "*L[i],sep='')
def play():
    display()
    global L
    global player1
    if player1 == True:
        s = input("Enter Player1 move ")
    else:
        s = input("Enter Player2 move ")
    
    row_number,sticks_removed = list(map(int,s.strip().split("-")))

    while  row_number>0 and row_number<=n and L[row_number-1] < sticks_removed:
        print("Enter a valid move\n ")
        if player1 == True:
            s = input("Enter Player1 move ")
        else:
            s = input("Enter Player2 move ")
        row_number,sticks_removed = list(map(int,s.strip().split("-")))

    L[row_number-1]-=sticks_removed

    if L==[0]*n:
        if player1:
            print("Player1 wins")
        else:
            print("Player2 wins")
        exit(0)

    player1 = not player1
    play()

if __name__== '__main__':
    play()
