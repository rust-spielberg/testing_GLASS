# G.L.A.S.S. Interactive Tic-Tac-Toe Game
import sys

def print_board(board):
    print("\n  0   1   2")
    for idx, row in enumerate(board):
        print(f"{idx} {' | '.join(row)}")
        if idx < 2:
            print("  ---------")

def check_winner(board, player):
    for i in range(3):
        if all(board[i][j] == player for j in range(3)) or all(board[j][i] == player for j in range(3)):
            return True
    if all(board[i][i] == player for i in range(3)) or all(board[i][2 - i] == player for i in range(3)):
        return True
    return False

def main():
    board = [[" " for _ in range(3)] for _ in range(3)]
    current_player = "X"
    moves = 0
    
    print("=== G.L.A.S.S. Python Tic-Tac-Toe ===")
    print_board(board)
    
    while moves < 9:
        try:
            inp = input(f"\nPlayer {current_player}, enter row col (0-2 0-2): ")
            coords = list(map(int, inp.strip().split()))
            if len(coords) != 2:
                continue
            row, col = coords
            if board[row][col] != " ":
                print("Cell occupied! Choose another cell.")
                continue
            board[row][col] = current_player
            moves += 1
            print_board(board)
            
            if check_winner(board, current_player):
                print(f"\nPlayer {current_player} wins!")
                return
            current_player = "O" if current_player == "X" else "X"
        except (ValueError, IndexError):
            print("Invalid coordinates! Enter numbers 0, 1, or 2.")
            
    print("\nGame ended in a draw!")

if __name__ == "__main__":
    main()
