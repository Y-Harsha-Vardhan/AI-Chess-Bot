print("Enter the size of the list")
n = int(input())
L = list(map(int, 
    input("Enter the numbers :\n").strip().split()))
print(L)
temp = L.copy()
for length in range(2,n+1):
    temp = [ max(L[start]-temp[start+1],L[start+length-1]-temp[start]) for start in range(0,n-length+1) ]
    
if temp[0] > 0:
    print("Player1 wins")
elif temp[0] == 0:
    print("Draw")
else:
    print("Player2 wins")