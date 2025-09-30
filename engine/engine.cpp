#include<iostream>
#include"chess.hpp"
#include<utility>
#include<vector>
#include<map>
#include<string>
#include<cmath>
#include<chrono>
#include<cstdint>
#include<fstream>
#include<cassert>
#include<set>


#define print(str) cout<<str<<"\n";
using namespace chess;
using namespace std;

std::map<Piece,int> piece_value;
int piece_value_index[] = {100,300,320,500,900,1100,100,300,320,500,900,1100}; // used only for move ordering (that's why I have assigned value for King)
std::map<Piece,std::array<std::array<int,8>,8 > > mp;

std::array<std::array<int,8> , 8> black_king_mid_game_table =
{{
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {20, 20,  0,  0,  0,  0, 20, 20},
    {20, 30, 10,  0,  0, 10, 30, 20}
}};
std::array<std::array<int,8> , 8> white_king_mid_game_table =
{{
        {20, 30, 10,  0,  0, 10, 30, 20},
        {20, 20,  0,  0,  0,  0, 20, 20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30}
}};
std::array<std::array<int,8> , 8> black_king_end_game_table = 
{{
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}
}};
std::array<std::array<int,8> , 8> white_king_end_game_table = 
{{
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}
}};


    

struct poly_book_entry {
    uint64_t key;
    uint16_t move;
    uint16_t weight;
    uint32_t learn;
} ;

struct move_score{
    int score;
    Move move;
    move_score(int score, Move move)
    {
        this->score = score;
        this->move = move;
    }
    bool operator<(const move_score &other) const
    {
        if (score!=other.score)return score > other.score;
        return uci::moveToUci(move) > uci::moveToUci(other.move);
    } 
    bool operator==(const move_score &other) const
    {
        return (score == other.score) && (uci::moveToUci(move) == uci::moveToUci( other.move ));
    }
};
void init();
int get_polyglot_move_from_uci(string &move);
bool move_exists(Board &board, string &move);
void free_book();
int get_move_from_book(chess::Board &board);
string get_uci_from_polyglot_move(int move);
uint16_t bigEndianToLittleEndian16(uint16_t key);
uint64_t decode_key(uint64_t key);
void init_book();
void search_position(Board &board);
int alpha_beta(int alpha, int beta, int depth, Board & board);
int evaluate(Board &board);
bool game_ends(const Board &board);
// void print_result(const Board &board, bool engine_move);


void init()
{

    piece_value[chess::Piece::BLACKBISHOP]=   320;
    piece_value[chess::Piece::WHITEBISHOP]=   320;
    piece_value[chess::Piece::WHITEPAWN]=     100;
    piece_value[chess::Piece::BLACKPAWN]=     100;
    piece_value[chess::Piece::BLACKKNIGHT]=   300;
    piece_value[chess::Piece::WHITEKNIGHT]=   300;
    piece_value[chess::Piece::WHITEROOK]=     500;
    piece_value[chess::Piece::BLACKROOK]=     500;
    piece_value[chess::Piece::WHITEQUEEN]=    900;
    piece_value[chess::Piece::BLACKQUEEN]=    900;



    mp[chess::Piece::BLACKPAWN] = 
    {{
        {0,0,0,0,0,0,0,0},
        {50,50,50,50,50,50,50,50},
        {10,10,25,30,30,25,10,10},
        {5,5,10,25,25,10,5,5},
        {0,0,0,20,20,0,0,0},
        {5,-5,-10,0,0,-10,-5,5},
        {5,10,10,-20,-20,10,10,5},
        {0,0,0,0,0,0,0,0}
    }};
    mp[chess::Piece::WHITEPAWN] = 
    {{
        {0,0,0,0,0,0,0,0},
        {5,10,10,-20,-20,10,10,5},
        {5,-5,-10,0,0,-10,-5,5},
        {0,0,0,20,20,0,0,0},
        {5,5,10,25,25,10,5,5},
        {10,10,25,30,30,25,10,10},
        {50,50,50,50,50,50,50,50},
        {0,0,0,0,0,0,0,0},
    }};
    mp[chess::Piece::BLACKKNIGHT] =
    {{
        {-50,-30,-20,-20,-20,-20,-30,-50},
        {-40,-20,0,5,5,0,-20,-40},
        {-20,5,10,15,15,10,5,-20},
        {-20,-10,15,20,20,15,-10,-20},
        {-20,-10,15,20,20,15,-10,-20},
        {-20,-5,10,15,15,10,-5,-20},
        {-40,-20,0,5,5,0,-20,-40},
        {-50,-30,-20,-20,-20,-20,-30,-50}
    }};
    mp[chess::Piece::WHITEKNIGHT] =
    {{
        {-50,-30,-20,-20,-20,-20,-30,-50},
        {-40,-20,0,5,5,0,-20,-40},
        {-20,-5,10,15,15,10,-5,-20},
        {-20,-10,15,20,20,15,-10,-20},
        {-20,-10,15,20,20,15,-10,-20},
        {-20,5,10,15,15,10,5,-20},
        {-40,-20,0,5,5,0,-20,-40},
        {-50,-30,-20,-20,-20,-20,-30,-50}
    }};
    mp[chess::Piece::BLACKBISHOP] =
    {{
        {-20, -10, -10, -10, -10, -10, -10, -20 },
        {-10, 5, 0, 0, 0, 0, 5, -10}, 
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 5, 10, 10, 10, 10, 5, -10}, 
        {-10, 5, 5, 10, 10, 5, 5, -10}, 
        {-10, 0, 5, 10, 10, 5, 0, -10}, 
        {-10, 0, 0, 0, 0, 0, 0, -10}, 
        {-20, -10, -10, -10, -10, -10, -10, -20}
    }};
    mp[chess::Piece::WHITEBISHOP] =
    {{
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10}, 
        {-10, 0, 5, 10, 10, 5, 0, -10}, 
        {-10, 5, 5, 10, 10, 5, 5, -10}, 
        {-10, 5, 10, 10, 10, 10, 5, -10}, 
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 5, 0, 0, 0, 0, 5, -10}, 
        {-20, -10, -10, -10, -10, -10, -10, -20 }        
    }};
    mp[chess::Piece::BLACKQUEEN]=
    {{
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        {-5,  0,  5,  5,  5,  5,  0, -5},
        { 0,  0,  5,  5,  5,  5,  0, -5},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}

    }};
    mp[chess::Piece::WHITEQUEEN]=
    {{
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        { 0,  0,  5,  5,  5,  5,  0, -5},
        {-5,  0,  5,  5,  5,  5,  0, -5},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
    }};
    mp[chess::Piece::BLACKROOK]=
    {{
        {0,10,10,10,10,10,10,0},
        {30,30,30,30,30,30,30,30},
        {-5,0,0,0,0,0,0,-5},
        {-5,0,0,0,0,0,0,0},
        {-5,0,0,0,0,0,0,-5},
        {-5,0,0,0,0,0,0,-5},
        {-5,0,5,5,5,5,0,5},
        {-5,0,5,5,5,5,0,-5}

    }};
    mp[chess::Piece::WHITEROOK]=
    {{
        {-5,0,5,5,5,5,0,-5},
        {-5,0,5,5,5,5,0,5},
        {-5,0,0,0,0,0,0,-5},
        {-5,0,0,0,0,0,0,-5},
        {-5,0,0,0,0,0,0,0},
        {-5,0,0,0,0,0,0,-5},
        {30,30,30,30,30,30,30,30},
        {0,10,10,10,10,10,10,0}   
    }};
}


int opening_entries_count = 0;
poly_book_entry * entries;


const int MAX_DEPTH = 32;
const int INFINITE = 1000000;

const int Pawn_isolated = -10;
const int WhitePassedPawn[8] = {0,5,10,20,35,60,100,200};
const int BlackPassedPawn[8] = {200,100,60,35,20,10,5,0};
const int rook_open_file = 10;
const int rook_semi_open_file = 5;
const int queen_open_file = 5;
const int queen_semi_open_file = 3;
bool first_move = false;
unordered_map<uint64_t,  pair< pair<  pair<Move,int> , int > ,char> >   hash_table; // Move, Score, Depth, Flag

uint64_t file_mask[8];
uint64_t rank_mask[8];
uint64_t black_passers[64];
uint64_t white_passers[64]; // Passer is a pawn which has No enemy pawn in front of it in either its own file or any of the adjacent files
uint64_t isolated_pawns[64]; // A pawn with no friendly pawn (i.e of same color) of either of the adjacent files


// Move search_history[13][64];
Move killers[2][MAX_DEPTH]; 

int get_polyglot_move_from_uci(string &move)
{
    int from = (move[0]-'a') + 8*(move[1]-'1');
    int to = (move[2]-'a') + 8*(move[3]-'1');
    if (move.length()==5)
    {
        switch (move[4])
        {
        case 'q':
            return (from << 6) | to | (4 << 12);
        case 'r':
            return (from << 6) | to | (3 << 12);
        case 'b':
            return (from << 6) | to | (2 << 12);
        case 'n':
            return (from << 6) | to | (1 << 12);
        default:
            break;
        }
    }
    return (from << 6) | to;
}
void clear_data()
{
    int index1,index2;
   
    for (index1 = 0 ; index1 < 2; index1++)
    {
        for (index2 = 0 ; index2 < MAX_DEPTH ; index2++)
        {
            killers[index1][index2] = 0;
        }
    }
    
}
bool endgame(int *count, chess::Color color)
{
    if (color == Color::WHITE)
    {
        if (count[10]==0 || (count[9]==1 && count[7]+count[8]<=1) || (count[9]==0 && count[7]+count[8]<=3))
        {
            return true;
        }
    }
    else
    {
        if (count[4]==0 || (count[3]==1 && count[1]+count[2]<=1) || (count[3]==0 && count[1]+count[2]<=3))
        {
            return true;
        }
    }
    return false;
}
bool dead_draw(int *count)
{
    
    if (count[0] == 0 && count[3] == 0 && count[4] == 0 && count[6]==0 && count[9]==0 && count[10]==0)
    {
        cout << count[0] << count[3] << count[4] << count[6] << count[9] << count[10] << "\n";
        if ((count[1]+count[2]<=1) && (count[7]+count[8]<=1))
        {
            return true;
        }
        if (count[1]==2 && count[2]==0 && (count[7]+count[8])<=1)
        {
            return true;
        }
        if (count[7]==2 && count[8]==0 && (count[1]+count[2])<=1)
        {
            return true;
        }
        if (count[1]==0 && count[7]==0 && ((count[2]==2 && count[8]==1) || (count[2]==1 && count[8]==2)))
        {
            return true;
        }
        
    }   
    return false;
}
void print_board_given_int(uint64_t temp)
{
    for (int i = 0 ; i < 64 ; i++)
    {
        if (i%8==0) cout << "\n";
        cout << ((1ULL<<i) & temp ? 1 : 0) << " ";
    }
    cout << "\n";

}
void init_eval_masks()
{
    map<Piece,int> count_of_pieces;

    for (int line = 0 ; line < 8 ; line++)
    {
        file_mask[line] = 0;
        rank_mask[line] = 0;
    }
    for (int rank = 0; rank < 8 ; rank++)
    {
        for (int file = 0 ;  file < 8 ; file++)
        {
            int sq = 8*rank + file;
            file_mask[file] |= (1ULL<<sq);
            rank_mask[rank] |= (1ULL<<sq);
        }
    }
    
    for (int i = 0 ; i < 64 ; i++)
    {
        black_passers[i] = white_passers[i] = isolated_pawns[i] = 0;
    }
    for (int i = 0 ; i < 64 ; i++)
    {
        int target_sq = i+8;
        while (target_sq < 64)
        {
            white_passers[i] |= (1ULL<<target_sq);
            target_sq += 8;
        }
        target_sq = i-8;
        while (target_sq >= 0)
        {
            black_passers[i] |= (1ULL<<target_sq);
            target_sq -= 8;
        }

        if ((i & 7) !=0) // Not the leftmost column (or a-file)
        {
            isolated_pawns[i] |= file_mask[(i&7)-1];
            target_sq = i + 7;
            while (target_sq < 64)
            {
                white_passers[i] |= (1ULL << (target_sq));
                target_sq += 8;
            }
            target_sq = i - 9;
            while (target_sq >= 0)
            {
                black_passers[i] |= (1ULL << (target_sq));
                target_sq -= 8;
            }
        } 
        if ((i&7)!=7) // Not the righmost column (or h-file)
        {
            isolated_pawns[i] |= file_mask[(i&7)+1];

            target_sq = i + 9;
            while (target_sq < 64)
            {
                white_passers[i] |= (1ULL << (target_sq));
                target_sq += 8;
            }
            target_sq = i - 7;
            while (target_sq >= 0)
            {
                black_passers[i] |= (1ULL << (target_sq));
                target_sq -= 8;
            }
        }
    }
}
int basic_evaluation(Board &board)
{
    if (board.isInsufficientMaterial())
    {
        return 0;
    }
    int count[13];
    for (int i = 0 ; i < 13 ; i++) count[i] = 0;
    int white = 0 , black = 0;
    for (int row = 0 ; row < 8 ; row++)
    {
        for (int col = 0 ; col < 8 ; col++)
        {
            Piece piece_present = board.at(Square(8*row+col));
            if (piece_present.color() == Color::BLACK)
            {
                assert(piece_present > 5);
            }
            count[piece_present]++;
        }
    }
    bool endgame_yet_white = endgame(count,Color::WHITE);
    bool endgame_yet_black = endgame(count,Color::BLACK);
    for (int row = 0 ; row < 8 ; row++)
    {
        for (int col = 0 ; col < 8 ; col++)
        {
            Piece piece_present = board.at(Square(8*row+col));
            
            if (piece_present == Piece::NONE)
            {
                continue;
            }
            else if(piece_present == Piece::WHITEKING || piece_present == Piece::BLACKKING)
            {
                if (piece_present == Piece::WHITEKING)
                {
                    if (endgame_yet_white)
                    {
                        white += white_king_end_game_table[row][col];
                    }
                    else
                    {
                        white += white_king_mid_game_table[row][col];
                    }
                    
                }
                else
                {
                    if (endgame_yet_black)
                    {
                        black += black_king_end_game_table[row][col];
                    }
                    else
                    {
                        black += black_king_mid_game_table[row][col];
                    }
                }
            }
            else{
                
                int curr = piece_value[piece_present] + mp[piece_present][row][col];
                // cout << row << " " << col << " " << curr << "\n"; 
                // cout << piece_present << " " << curr << "\n"; 
                if (piece_present.color() == Color::BLACK)
                {
                    black += curr;
                }
                else
                {
                    white += curr;
                }
                // if (piece_present == Piece::WHITEPAWN)
                // {
                //     if (white_passers[8*row+col] & board.pieces(PieceType::PAWN,Color::BLACK))
                //     {
                //         white += WhitePassedPawn[col];
                //         // cout << row << col << "passer" << endl;
                //     }
                //     if (isolated_pawns[8*row+col] & board.pieces(PieceType::PAWN,Color::WHITE))
                //     {
                //         white += Pawn_isolated;
                //         // cout << row << col << "isolated" << endl;
                //     }
                    
                // }
                // if (piece_present == Piece::BLACKPAWN)
                // {
                //     if (black_passers[8*row+col] & board.pieces(PieceType::PAWN,Color::WHITE))
                //     {
                //         black += BlackPassedPawn[col];
                //         cout << row << col << "passer" << endl;
                //     }
                //     if (isolated_pawns[8*row+col] & board.pieces(PieceType::PAWN,Color::BLACK))
                //     {
                //         black += Pawn_isolated;
                //         cout << row << col << "isolated" << endl;
                //     }
                    
                // }
                // if (piece_present == Piece::WHITEROOK)
                // {
                //     if (!(file_mask[col] & board.pieces(PieceType::PAWN)))
                //     {
                //         white += rook_open_file;
                //     }
                //     else if (!(file_mask[col] & board.pieces(PieceType::PAWN,Color::WHITE)))
                //     {
                //         white += rook_semi_open_file;
                //     }
                // }
                // if (piece_present == Piece::WHITEQUEEN)
                // {
                //     if (!(file_mask[col] & board.pieces(PieceType::PAWN)))
                //     {
                //         white += queen_open_file;
                //     }
                //     else if (!(file_mask[col] & board.pieces(PieceType::PAWN,Color::WHITE)))
                //     {
                //         white += queen_semi_open_file;
                //     }
                // }
                // if (piece_present == Piece::BLACKROOK)
                // {
                //     if (!(file_mask[col] & board.pieces(PieceType::PAWN)))
                //     {
                //         black += rook_open_file;
                //     }
                //     else if (!(file_mask[col] & board.pieces(PieceType::PAWN,Color::BLACK)))
                //     {
                //         black += rook_semi_open_file;
                //     }
                // }
                // if (piece_present == Piece::BLACKQUEEN)
                // {
                //     if (!(file_mask[col] & board.pieces(PieceType::PAWN)))
                //     {
                //         black += queen_open_file;
                //     }
                //     else if (!(file_mask[col] & board.pieces(PieceType::PAWN,Color::WHITE)))
                //     {
                //         black += queen_semi_open_file;
                //     }
                // }
            }


        }
    }
    // if (dead_draw(count))
    // {
    //     cout << "D";
    //     return 0;
    // }
    return white-black;
}

int evaluate(Board &board)
{
    if (board.sideToMove() == Color::WHITE) return basic_evaluation(board);
    return -1*basic_evaluation(board);
}


int alpha_beta(int alpha, int beta, int depth, Board & board,int& num_nodes, int num_ply = 0)
{
    num_nodes++;
    if (depth == 0)
    {
        return evaluate(board);
    }
    if ((board.isHalfMoveDraw() || board.isRepetition(2)) && num_ply!=0)
    {
        return 0;
    }
    bool color = (board.sideToMove() == Color::WHITE);
    Movelist moves;
    movegen::legalmoves(moves,board);
    Move best_move = -1; 
    if (moves.size()==0)
    {
        if (!board.inCheck())
        {
            return 0; // Stalemate
        }
        
        return -INFINITE + MAX_DEPTH - depth;
    }
    if (hash_table.find(board.zobrist())!=hash_table.end())
    {
        auto temp = hash_table[board.zobrist()];
        if (temp.first.second >= depth)
        {
            if (temp.second == 'E')
            {
                return temp.first.first.second;
            }
            else if (temp.second=='L')
            {
                alpha = max(alpha,temp.first.first.second);
            }
            else
            {
                beta = min(beta,temp.first.first.second);
            }
            if (alpha >= beta)
            {
                return temp.first.first.second;
            }
        }
        
        best_move = temp.first.first.first;
    }
   
    
    
    int value = -INFINITE;
    
    set<move_score> move_set_ordered;
    for (auto move:moves)
    {
        if (move == best_move )
        {
            move_set_ordered.insert(move_score(10000,move));
        }
        if (board.isCapture(move))
        {
            move_set_ordered.insert(move_score(piece_value_index[board.at(move.to())] - piece_value_index[board.at(move.from())],move));
            /*Wrong value for en-passants.Shouldn't affect the search too much though*/
        }
        
        
        else if (killers[0][num_ply] == move)
        {
            move_set_ordered.insert(move_score(-2000,move));
        }
        else if (killers[1][num_ply] == move)
        {
            move_set_ordered.insert(move_score(-3000,move));
        }
        else
        {
            move_set_ordered.insert(move_score(-10000,move));
        }
    }
    for (auto Move : move_set_ordered)
    {
       
        board.makeMove(Move.move);
        int val = -alpha_beta(-beta,-alpha,depth-1,board,num_nodes,num_ply+1);
        board.unmakeMove(Move.move);
    
        if (value < val)
        {
            value = val;
            best_move = Move.move;
            alpha = max(alpha,val);
        }
        
        if (alpha >= beta)
        {
            if (!board.isCapture(Move.move))
            {
                killers[1][num_ply] = killers[0][num_ply];
                killers[0][num_ply] = Move.move;
            }
            hash_table[board.zobrist()] = make_pair(make_pair(make_pair(best_move,value),depth),'L');
            return value;

        }

    }
    if (alpha == value) // It means we have improved 
    {
        string temp = uci::moveToUci(best_move);
        hash_table[board.zobrist()] = make_pair(make_pair(make_pair(best_move,value),depth),'E');
        return value;
    }
    hash_table[board.zobrist()] = make_pair(make_pair(make_pair(best_move,value),depth),'U');
    return value;
}

void search_position(Board &board)
{
    int num_nodes = 0;
    Move best_move;
    int best_score = -INFINITE;
    
    clear_data();

    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();

    int time_allowed = (first_move ? 15 : 8);
    for (int current_depth = 1 ; current_depth <= MAX_DEPTH ; current_depth++)
    {
        best_score = alpha_beta(-INFINITE,INFINITE,current_depth,board,num_nodes);
        best_move = hash_table[board.zobrist()].first.first.first;

        auto cur = std::chrono::system_clock::now();
        cout << current_depth << " " << uci::moveToUci( best_move )<< "\n";
        std::chrono::duration<double> elapsed_seconds = cur - start;
        if (elapsed_seconds.count() > time_allowed) break;
    }
    cout << "Number of nodes visited is " << num_nodes << "\n";
}



void init_book()
{
    std::ifstream open_file("Titans.bin",std::ios::binary);
    if (!open_file)
    {
        exit(1);
    }
    else
    {
        open_file.seekg(0,open_file.end);
        long long position = open_file.tellg();

        if (position < sizeof(poly_book_entry))
        {
            cout << "Error: Opening book is too small\n";
            exit(1);
        }
        opening_entries_count = position/sizeof(poly_book_entry);
        // cout << "Opening book has " << opening_entries_count << " entries\n";

        entries = new poly_book_entry[opening_entries_count];
        open_file.seekg(0,open_file.beg);

        open_file.read((char *)entries,opening_entries_count*sizeof(poly_book_entry));
        // cout << "Opening book loaded successfully\n" << "It has " << opening_entries_count << " entries\n";
    }
}

uint64_t decode_key(uint64_t key)
{
    // copied from Chat-GPT 😅
    return ((key >> 56)) |          // move byte 7 to byte 0
           ((key >> 40) & 0xFF00) |        // move byte 6 to byte 1
           ((key >> 24) & 0xFF0000) |      // move byte 5 to byte 2
           ((key >> 8) & 0xFF000000) |     // move byte 4 to byte 3
           ((key << 8) & 0xFF00000000) |   // move byte 3 to byte 4
           ((key << 24) & 0xFF0000000000) |// move byte 2 to byte 5
           ((key << 40) & 0xFF000000000000)|// move byte 1 to byte 6
           ((key << 56)); // move byte 0 to byte 7
}

uint16_t bigEndianToLittleEndian16(uint16_t key) {
    return ((key >> 8)) | ((key << 8));
}

string get_uci_from_polyglot_move(const int move)
{
    string uci = "";
    uci += 'a' + ((move >> 6) & 7);
    uci += '1' + ((move >> 9) & 7);
    uci += 'a' + (move & 7);
    uci += '1' + ((move >> 3) & 7);
    switch ((move >> 12) & 7)
    {
    case 4:
        uci += 'q';
        break;
    case 3:
        uci += 'r';
        break;
    case 2:
        uci += 'b';
        break;
    case 1:
        uci += 'n';
        break;
    default:
        break;
    }
    return uci;
}

int get_move_from_book(chess::Board &board)
{
    uint64_t key = board.zobrist();

    int left = 0 , right = opening_entries_count-1;

    int min_index = -1;
    while (left < right)
    {
        int mid = (left+right)/2;
        uint64_t book_key = decode_key(entries[mid].key);
        if (book_key == key)
        {

            left = mid-1;
            while (entries[mid].key == entries[left].key)
            {
                left--;
            }
            min_index = left+1;

            break;
        }
        else if (book_key < key)
        {
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }
    if (entries[left].key == key)
    {
        min_index = left;
    }
    if (left!=right && entries[right].key == key)
    {
        min_index = right;
    }
    // cout << min_index << count << "\n";
    return min_index;
}

void free_book()
{
    delete[] entries;
}

bool move_exists(Board &board, string &move)
{
    Movelist moves;
    movegen::legalmoves(moves,board);
    
    return find(moves.begin(),moves.end(),uci::uciToMove(board,move)) != moves.end();
}


bool game_ends(const Board &board)
{
    return board.isGameOver().second != GameResult::NONE;
}
// void print_result(const Board &board, bool engine_move)
// {
//     auto result = board.isGameOver();
//     if (result.second == GameResult::DRAW)
//     {
//         cout << "Game is a draw\n";
//     }
//     else if (result.second == GameResult::LOSE)
//     {
//         cout << "Congratulations!!! You Won\n";
//     }
//     else
//     {
//         cout << "Sorry, you lost\n";
//     }
//     return;
// }
void display(const Board &board)
{
    cout << board;
}
void play(Board &board)
{
    bool engine_move;
    bool opening = true;
    cout << "Do you want to play the first move (Enter y/n): ";
    char choice;
    cin >> choice;
    engine_move = ((choice == 'n') || (choice == 'N')) ;
    cout << "Enter your moves in UCI Notation\n";

    while (!game_ends(board))
    {
        if (engine_move)
        {
            if (opening)
            {
                int index = get_move_from_book(board);
                if (index == -1)
                {
                    opening = false;
                    first_move = true;
                    // cout << "Opening book exhausted\n";
                }
                else
                {
                    Move best_move = uci::uciToMove(board,get_uci_from_polyglot_move(bigEndianToLittleEndian16(entries[index].move)));
                    board.makeMove(best_move);
                    cout << uci::moveToUci(best_move) << "\n";
                }
            }
            if (!opening)
            {
                
                search_position(board);
                string move_uci_string = uci::moveToUci(hash_table[board.zobrist()].first.first.first);
                cout << move_uci_string << endl;
                board.makeMove(uci::uciToMove(board,move_uci_string));
                first_move = false;
            

            }
        }
        else
        {
            cout << "Enter your move: ";
            string move;
            cin >> move;

            Movelist moves;
            movegen::legalmoves(moves, board);
            
            while (true)
            {
                bool found = false;
                auto uci_move = uci::uciToMove(board,move);
                for (auto &it:moves)
                {
                    if (it == uci_move)
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
                cout << "Invalid Move\nEnter move again: ";
                cin >> move;
                continue;
            }
            board.makeMove(uci::uciToMove(board,move));
        }
        engine_move = !engine_move;
        display(board);
    }
    // print_result(board,engine_move);
}


int main()
{
    init();
    string fen_str = "r1b1kb1r/ppp1pppp/2n5/q2P4/4pB2/2P1Q3/P3PPPP/R3KBNR b KQkq - 0 11";
    chess::Board board = Board(fen_str);
    
    
    init_book();
    init_eval_masks();
    


    play(board);


    free_book();

    return 0;    
}