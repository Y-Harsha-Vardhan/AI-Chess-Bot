# Strategos - An AI Chess Engine
Contains the weekly assignments given during the SOC Project-Queen's Gambit.
After Week 3, our primary focus shifted to building a chess engine. The result is **Strategos: an AI Chess Engine**. You can play against the engine by running the executable:

```console
./engine/engine
```

## Features

- **AI Chess Engine**: Evaluates positions and makes intelligent moves.
- **Custom Starting Positions**: Supports FEN (Forsyth-Edwards Notation) for setting up unique board states.
- **Command-Line Interface**: Simple and interactive gameplay experience.

## How to Play

1. Clone the repository:
  ```bash
  git clone https://github.com/yourusername/Strategos-AI-Chess-Engine.git
  cd Strategos-AI-Chess-Engine
  ```

2. Build the engine:
  ```bash
  make
  ```

3. Run the engine:
  ```bash
  ./engine/engine
  ```

4. Follow the on-screen instructions to play against the AI.

## Custom Starting Positions

To play with a custom starting position:

1. Open `engine.cpp`.
2. Locate the `main` function and update the `fen_str` variable:
  ```cpp
  string fen_str = "YOUR_FEN_STRING";
  chess::Board board = Board(fen_str);
  ```
3. Use [Chess.com](https://www.chess.com/analysis) to generate the FEN string for your desired position.
4. Rebuild the engine:
  ```bash
  make
  ```

## Contributions

Contributions are welcome! If you have ideas for improvements or find any issues, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
```console
./engine/engine
```
If you want a different starting position, do the following changes:



i) Inside the main function of engine.cpp, change the value of fen_str to the FEN of starting position you want. Go to [Chess.com](https://www.chess.com/analysis) and set up the position. Click on share button and you get the FEN notation of your desired position.


ii) Call the constructor of board with "fen_str"

  string fen_str = "FEN_POSITION_OF_YOUR_WISH";
  
  chess::Board board = Board(fen_str);
