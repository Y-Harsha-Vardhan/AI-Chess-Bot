import chess
import math

M = ""

computer_move = True

values = {'p':10,'n':30,'b':31,'r':50,'q':90,'P':10,'N':30,'B':31,'R':50,'Q':90,'K':0,'k':0}
vals = {'n':20,'b':21,'r':30,'q':80}
squares = {'a1':chess.A1,'b1':chess.B1,'c1':chess.C1,'d1':chess.D1,'e1':chess.E1,'f1':chess.F1,'g1':chess.G1,'h1':chess.H1,'a2':chess.A2,'b2':chess.B2,'c2':chess.C2,'d2':chess.D2,'e2':chess.E2,'f2':chess.F2,'g2':chess.G2,'h2':chess.H2,'a3':chess.A3,'b3':chess.B3,'c3':chess.C3,'d3':chess.D3,'e3':chess.E3,'f3':chess.F3,'g3':chess.G3,'h3':chess.H3,'a4':chess.A4,'b4':chess.B4,'c4':chess.C4,'d4':chess.D4,'e4':chess.E4,'f4':chess.F4,'g4':chess.G4,'h4':chess.H4,'a5':chess.A5,'b5':chess.B5,'c5':chess.C5,'d5':chess.D5,'e5':chess.E5,'f5':chess.F5,'g5':chess.G5,'h5':chess.H5,'a6':chess.A6,'b6':chess.B6,'c6':chess.C6,'d6':chess.D6,'e6':chess.E6,'f6':chess.F6,'g6':chess.G6,'h6':chess.H6,'a7':chess.A7,'b7':chess.B7,'c7':chess.C7,'d7':chess.D7,'e7':chess.E7,'f7':chess.F7,'g7':chess.G7,'h7':chess.H7,'a8':chess.A8,'b8':chess.B8,'c8':chess.C8,'d8':chess.D8,'e8':chess.E8,'f8':chess.F8,'g8':chess.G8,'h8':chess.H8}

# board = chess.Board('r5rk/5p1p/5R2/4B3/8/8/7P/7K w')

def order(moves,board):
    global squares,values,vals
    mp = dict()
    for move in moves:
        mp[move] = 0
        board.push(move)
        if board.is_check():
            mp[move] += 5
        board.pop()
        if board.piece_at(squares[str(move)[2:4]]) is not None:
            # print(board.piece_at(squares[str(move)[2:]]))
            mp[move] += (5*values[str(board.piece_at(squares[str(move)[2:4]]))] - values[str(board.piece_at(squares[str(move)[:2]]))])
        if move.promotion is not None:
            promotion_piece = chess.PIECE_SYMBOLS[move.promotion].lower()
            mp[move] += vals[promotion_piece] 
            
    sorted(mp.items(), key = lambda x: x[1])
    return mp.keys()
def eval_position(chess_board):
    global values
    ans = 0
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece is not None:
            val = 1
            if piece.color == 'BLACK':
                val = -1
            val *= values[str(piece)]
    return ans
def solve_puzzle(chess_board,depth = 5,alpha = -math.inf,beta = math.inf , max_player_flag = True):
    global M
    curr_move = ""
    
    if chess_board.is_checkmate():
        if max_player_flag:
            return -10000
        return 10000
    if chess_board.is_stalemate():
         return 0
    if depth == 0:
        return eval_position(chess_board)
    # print(chess_board.legal_moves)
    
   
    if max_player_flag == True:
        value = -math.inf
    else:
        value = math.inf
    moves = order(board.legal_moves,board)
   
    for move in moves:
        chess_board.push(move)
        val = solve_puzzle(chess_board,depth-1,alpha,beta,not max_player_flag)
        chess_board.pop()
        if (max_player_flag):
            if value < val:
                    value = val
                    curr_move = chess_board.san(move)
                  
            alpha = max(alpha,val)
        else:
            if value > val:
                    value = val
                    curr_move = chess_board.san(move)
            beta = min(beta,val)
        
        if alpha >= beta:
            
            M = curr_move
            return value
    M = curr_move
    return value
def play_move():
    global board,computer_move,M
    if board.is_checkmate():
        if computer_move:
            print("You won")
            return
        else:
            print("You lost")
        return 
    if board.is_stalemate():
        print("Stalemate")
        return
    if (computer_move):
        solve_puzzle(board)
        board.push_san(M)
        computer_move = False
        print(board)
    else:
        move = input('Enter your move ')
        print(move)
        move = board.parse_san(move)
        while move not in board.legal_moves:
            move = input('Enter your move')
        board.push(move)
        print(move)
        computer_move = True
    play_move()

# play_move()
