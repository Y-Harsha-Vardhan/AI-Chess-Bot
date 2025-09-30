# It's just me playing chess for the first time using chess library.
import chess
import requests
import re
from solve_puzzle import solve_puzzle

chess_board = chess.Board()

# print(chess_board.legal_moves)




# chess_board.generate_legal_captures
# chess_board.push_san('e4')
# print(chess_board)

# print(chess.parse_square('h3'))

puzzles = []
puzzle_solutions = []

# links = []

# string = 'https://www.sparkchess.com/mate-in/two/page/'
# for i in range(1,5):
#     text = requests.get(string + f"{i}")
#     links += re.findall(r'<a class="puzzle-link-wrapper" href="([^"]*)">',text.text) 

# for link in links:
#     txt = requests.get(link).text
#     # puzzle_fen = re.search(r'<p class="puzzle-fen">(.*)</code>',txt).group()
#     # puzzles.append((re.search(r'>([^<]*)</code>',puzzle_fen).group())[1:-7])
    
#     solution = re.search(r'<p class="puzzle-solution"(.*)</p>',txt).group()
#     puzzle_solutions.append((re.search(r'<code>(.*)</code>',solution).group())[5:-7])
#     ...
# # print(puzzles)
# print(puzzle_solutions)

puzzle_solutions = ['1. Qg6+ hxg6 2. Bxg6#', '1... Rg1+ 2. Kxg1 Rxf1#', '1... Bb5+ 2. Nc4 Rd2#', '1. Qf8+ Kxf8 2. Rd8# ', '1. Qxh6+ Rxh6 2. Rg8# ', '1. Qd8+ Bxd8 2. Re8# ', '1... Nh4+ 2. Ke1 Nxf3#', '1. Ra6 bxa6 2. b7#', '1... Qxh2+ 2. Kxh2 Rh4#', '1. h5+ Kh6 2. Nf7#', '1... Be3+ 2. Qxe3 Qg4#', '1. Rxf6+ Nxf6 2. g5#', '1. Qb8+ Nxb8 2. Rd8#', '...1.dxe1=N 2.Kg1 Qg2#', '1.Re8 Bxe8 2.Qc7#', '1.Rh8+ Bxh8 2.Rxh8#', '1.Rh8+ Bxh8 2.Nh7#', '1.Ne6+ Bxe6 2.Bh6#', '1.Ne7 Nxf5 2.Qg6#', '1.Qg6+ hxg6 2.fxg6#', '1.Qxf2+Rxf2 2.Re1#', '1.Bxe3+Qxe3 2.Qg2#', '1.Rxg7+ Rxg7 2.Nf6#', '1.Qd5+ Ka6 2.cxb8=N#', '1.Qg8+ Kxg8 2.f7#', '1.Qh6 Kxh6 2.Bxf6#']
puzzles = ['r2qk2r/pb4pp/1n2Pb2/2B2Q2/p1p5/2P5/2B2PPP/RN2R1K1 w - - 1 0', '6k1/pp4p1/2p5/2bp4/8/P5Pb/1P3rrP/2BRRN1K b - - 0 1', '8/2k2p2/2b3p1/P1p1Np2/1p3b2/1P1K4/5r2/R3R3 b - - 0 1', '6k1/5p2/1p5p/p4Np1/5q2/Q6P/PPr5/3R3K w - - 1 0', 'r1b2k1r/ppppq3/5N1p/4P2Q/4PP2/1B6/PP5P/n2K2R1 w - - 1 0', 'r1b2k1r/ppp1bppp/8/1B1Q4/5q2/2P5/PPP2PPP/R3R1K1 w - - 1 0', 'rn2kb1r/ppp1pppp/8/8/4q3/3P1N1b/PPP1BPnP/RNBQ1K1R b kq - 0 1', 'kbK5/pp6/1P6/8/8/8/8/R7 w - -', '4r1k1/pQ3pp1/7p/4q3/4r3/P7/1P2nPPP/2BR1R1K b - - 0 1', 'r4R2/1b2n1pp/p2Np1k1/1pn5/4pP1P/8/PPP1B1P1/2K4R w - - 1 0', '7r/p3ppk1/3p4/2p1P1Kp/2Pb4/3P1QPq/PP5P/R6R b - - 0 1', '4r3/pbpn2n1/1p1prp1k/8/2PP2PB/P5N1/2B2R1P/R5K1 w - - 1 0', '4kb1r/p2n1ppp/4q3/4p1B1/4P3/1Q6/PPP2PPP/2KR4 w k - 1 0', '2r2r2/6kp/3p4/3P4/4Pp2/5P1P/PP1pq1P1/4R2K b - - 0 1', 'r2k2nr/pp1b1Q1p/2n4b/3N4/3q4/3P4/PPP3PP/4RR1K w - - 0 1', '1r3rk1/1pnnq1bR/p1pp2B1/P2P1p2/1PP1pP2/2B3P1/5PK1/2Q4R w - - 0 1', '1r3k2/2n1p1b1/3p2QR/p1pq1pN1/bp6/7P/2P2PP1/4RBK1 w - - 0 1', 'r2q1k1r/ppp1bB1p/2np4/6N1/3PP1bP/8/PPP5/RNB2RK1 w - - 0 1', 'r2qrb2/p1pn1Qp1/1p4Nk/4PR2/3n4/7N/P5PP/R6K w - - 0 1', 'r4br1/3b1kpp/1q1P4/1pp1RP1N/p7/6Q1/PPB3PP/2KR4 w - - 0 1', '4r1k1/5ppp/pp6/2pp4/3b2bq/BQN5/PPP2PPP/5RK1 b - - 0 1', '4k2r/1q1p1pp1/p3p3/1pb1P3/2r3P1/P1N1P2p/1PP1Q2P/2R1R1K1 b k - 0 1', 'Q7/2r2rpk/7p/7N/3PpN2/1p2P3/1K4R1/5q2 w - - 0 1', '1rb4r/pkPp3p/1b1P3n/1Q6/N3Pp2/8/P1P3PP/7K w - - 0 1', '3r1b1k/5Q1p/p2p1P2/5R2/4q2P/1P2P3/PB5K/8 w', 'r1bq2r1/b4pk1/p1pp1p2/1p2pP2/1P2P1PB/3P4/1PPQ2P1/R3K2R w']
chess_board = chess.Board(puzzles[0])
for i in range(len(puzzles)):
    solve_puzzle(puzzles[i])
