import json
import copy  # use it for deepcopy if needed
import math  # for math.inf
import logging
import random

logging.basicConfig(format='%(levelname)s - %(asctime)s - %(message)s', datefmt='%d-%b-%y %H:%M:%S',
                    level=logging.INFO)

# Global variables in which you need to store player strategies (this is data structure that'll be used for evaluation)
# Mapping from histories (str) to probability distribution over actions
strategy_dict_x = {}
strategy_dict_o = {}
results_x = {}
results_o = {}


class History:
    def __init__(self, history=None):
        """
        # self.history : Eg: [0, 4, 2, 5]
            keeps track of sequence of actions played since the beginning of the game.
            Each action is an integer between 0-8 representing the square in which the move will be played as shown
            below.
              ___ ___ ____
             |_0_|_1_|_2_|
             |_3_|_4_|_5_|
             |_6_|_7_|_8_|

        # self.board
            empty squares are represented using '0' and occupied squares are either 'x' or 'o'.
            Eg: ['x', '0', 'x', '0', 'o', 'o', '0', '0', '0']
            for board
              ___ ___ ____
             |_x_|___|_x_|
             |___|_o_|_o_|
             |___|___|___|

        # self.player: 'x' or 'o'
            Player whose turn it is at the current history/board

        :param history: list keeps track of sequence of actions played since the beginning of the game.
        """
        if history is not None:
            self.history = history
            self.board = self.get_board()
        else:
            self.history = []
            self.board = ['0', '0', '0', '0', '0', '0', '0', '0', '0']
        self.player = self.current_player()

    def current_player(self):
        """ Player function
        Get player whose turn it is at the current history/board
        :return: 'x' or 'o' or None
        """
        total_num_moves = len(self.history)
        if total_num_moves < 9:
            if total_num_moves % 2 == 0:
                return 'x'
            else:
                return 'o'
        else:
            return None

    def get_board(self):
        """ Play out the current self.history and get the board corresponding to the history in self.board.

        :return: list Eg: ['x', '0', 'x', '0', 'o', 'o', '0', '0', '0']
        """
        board = ['0', '0', '0', '0', '0', '0', '0', '0', '0']
        for i in range(len(self.history)):
            if i % 2 == 0:
                board[self.history[i]] = 'x'
            else:
                board[self.history[i]] = 'o'
        return board

    def is_win(self):
        for row in range(3):
            if self.board[row * 3] == self.board[row * 3 + 1] == self.board[row * 3 + 2] and self.board[row * 3] != '0':
                if self.current_player() == self.board[row * 3]:
                    return 1
                else:
                    return -1
            
        for column in range(3):
            if self.board[column] == self.board[column + 3] == self.board[column + 6] and self.board[column] != '0':
                if self.current_player() == self.board[column]:
                    return 1
                else:
                    return -1
        if self.board[0] == self.board[4] == self.board[8] and self.board[0] != '0':
                if self.current_player() == self.board[0]:
                    return 1
                else:
                    return -1
        
        if self.board[2] == self.board[4] == self.board[6] and self.board[2] != '0':
                if self.current_player() == self.board[2]:
                    return 1
                else:
                    return -1
        return 0
        # check if the board position is a win for either players
        # Feel free to implement this in anyway if needed

    def is_draw(self):
        
        for square in range(9):
            if self.board[square] == '0':
                return False
        
        return True
        # check if the board position is a draw
        # Feel free to implement this in anyway if needed
        

    def get_valid_actions(self):
        empty_squares = []
        for index in range(9):
            if self.board[index] == '0':
                empty_squares.append(index)

        return empty_squares
        # get the empty squares from the board
        # Feel free to implement this in anyway if needed
        

    def is_terminal_history(self):

        # check if the history is a terminal history
        # Feel free to implement this in anyway if needed
        pass

    def get_utility_given_terminal_history(self):
        winning = self.is_win()
        if winning!=0:
            return winning
        if self.is_draw():
            return 0
        
        return None
        # Feel free to implement this in anyway if needed


    def update_history(self, action):
        # In case you need to create a deepcopy and update the history obj to get the next history object.
        # Feel free to implement this in anyway if needed
        pass


def backward_induction(history_obj:History):
    """
    :param history_obj: Histroy class object
    :return: best achievable utility (float) for th current history_obj
    """
    global strategy_dict_x, strategy_dict_o

    string_of_history = ""

    for history in history_obj.history:
        string_of_history = string_of_history + str(history)

    if history_obj.current_player() == 'x' and string_of_history in strategy_dict_x.keys():
        return results_x[string_of_history]
    
    if history_obj.current_player() == 'o' and string_of_history in strategy_dict_o.keys():
        return results_o[string_of_history]
    
    result = history_obj.get_utility_given_terminal_history()


    if result is None:

        distribution = {str(i):0 for i in range(9)}
        win_possibilities = []
        draw_possibilities = []

        for action in history_obj.get_valid_actions():
            new_history = copy.copy(history_obj.history)
            new_history.append(action)

            result_at_child = backward_induction(History(new_history))

            if result_at_child ==  -1:
                win_possibilities.append(action)
            
            elif result_at_child == 0:
                draw_possibilities.append(action)

            else:
                pass

        
        if len(win_possibilities) != 0:

            for i in win_possibilities:
                distribution[str(i)] = 1/len(win_possibilities)
            
         
            if history_obj.current_player() == 'o':
                    results_o[string_of_history] =  1
                    strategy_dict_o[string_of_history] = distribution           
            else:
                    results_x[string_of_history] =  1
                    strategy_dict_x[string_of_history] = distribution                
    
            return 1
        
        elif len(draw_possibilities) != 0:

            for i in draw_possibilities:
                distribution[str(i)] = 1/len(draw_possibilities)

            if history_obj.current_player() == 'o':
                    results_o[string_of_history] =  0
                    strategy_dict_o[string_of_history] = distribution           
            else:
                    results_x[string_of_history] =  0
                    strategy_dict_x[string_of_history] = distribution      
            return 0
        else:
            length = len(history_obj.get_valid_actions())
            for i in history_obj.get_valid_actions():
                distribution[str(i)] = 1/length
            distribution[str(random.choice(history_obj.get_valid_actions()))] = 1
            if history_obj.current_player() == 'o':
                    results_o[string_of_history] =  -1
                    strategy_dict_o[string_of_history] = distribution           
            else:
                    results_x[string_of_history] =  -1
                    strategy_dict_x[string_of_history] = distribution      
            return -1


    else:

        if history_obj.current_player() == 'o':
            results_o[string_of_history] = result
        else:
            results_x[string_of_history] = result

        return result


    # TODO implement
    # (1) Implement backward induction for tictactoe
    # (2) Update the global variables strategy_dict_x or strategy_dict_o which are a mapping from histories to
    # probability distribution over actions.
    # (2a)These are dictionary with keys as string representation of the history list e.g. if the history list of the
    # history_obj is [0, 4, 2, 5], then the key is "0425". Each value is in turn a dictionary with keys as actions 0-8
    # (str "0", "1", ..., "8") and each value of this dictionary is a float (representing the probability of
    # choosing that action). Example: {”0452”: {”0”: 0, ”1”: 0, ”2”: 0, ”3”: 0, ”4”: 0, ”5”: 0, ”6”: 1, ”7”: 0, ”8”:
    # 0}}
    # (2b) Note, the strategy for each history in strategy_dict_x and strategy_dict_o is probability distribution over
    # actions. But since tictactoe is a PIEFG, there always exists an optimal deterministic strategy (SPNE). So your
    # policy will be something like this {"0": 1, "1": 0, "2": 0, "3": 0, "4": 0, "5": 0, "6": 0, "7": 0, "8": 0} where
    # "0" was the one of the best actions for the current player/history.
    return -2
    # TODO implement


def solve_tictactoe():
    backward_induction(History())
    with open('./policy_x.json', 'w') as f:
        json.dump(strategy_dict_x, f)
    with open('./policy_o.json', 'w') as f:
        json.dump(strategy_dict_o, f)
    return strategy_dict_x, strategy_dict_o


if __name__ == "__main__":
    logging.info("Start")
    solve_tictactoe()
    logging.info("End")
