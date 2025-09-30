import chess
import math
import solve_puzzle
M = ""

computer_move = True

# Implementing iterative deepening here.
def search(chess_board):
    global M
    depth = 1
    search_cancelled = False
    while not search_cancelled and depth <= 10:
        M = ""
        solve_puzzle(chess_board,depth)
        print(f"Best move for depth {depth} is {M}")
        depth += 1
