import random
mp = dict()
def init_zobrist():
    # fill a table of random numbers/bitstrings
    table = [[0 for j in range(12)] for i in range(64)]
    for i in range( 64 ):  # loop over the board, represented as a linear array
        for j in range(12):      # loop over the pieces
            table[i][j] = random.randint(0,(1<<64)-1)
    black_to_move = random.randint(0,(1<<64)-1)
    # hash for castling rights too

def store_hash()