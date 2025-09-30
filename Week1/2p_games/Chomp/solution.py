import pygame
import sys

pygame.init()

width = 800
height = 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Chomp Game')


rows = 6
cols = 8
square_size = 50
padding = 10

black = (0, 0, 0)
brown = (139, 69, 19)
white = (255, 255, 255)


font = pygame.font.Font(None, 36)


game_over = False
turn = 0  


chocolate = [[True for _ in range(cols)] for _ in range(rows)]

def draw_chocolate():
    for row in range(rows):
        for col in range(cols):
            if chocolate[row][col]:
                pygame.draw.rect(screen, brown,
                                 (col * (square_size + padding) + padding,
                                  row * (square_size + padding) + padding,
                                  square_size, square_size))
            else:
                pygame.draw.rect(screen, white,
                                 (col * (square_size + padding) + padding,
                                  row * (square_size + padding) + padding,
                                  square_size, square_size))

def chomp(row, col):
    global game_over
    for r in range(row, rows):
        for c in range(col, cols):
            chocolate[r][c] = False
    if row == 0 and col == 0:
        game_over = True

def display_winner():
    loser = "Player 1" if turn == 1 else "Player 2"
    text = font.render(f'{loser} is a fucking loser !', True, white, brown)
    text_rect = text.get_rect(center=(width // 2, height - 50))
    screen.blit(text, text_rect)

def display_turn():
    player_turn = "Player 1's Turn" if turn == 0 else "Player 2's Turn"
    text = font.render(player_turn, True, white)
    text_rect = text.get_rect(center=(width // 2, 500))
    screen.blit(text, text_rect)

def main_game_loop():
    running = True
    global turn
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                x, y = event.pos
                col = x // (square_size + padding)
                row = y // (square_size + padding)
                if chocolate[row][col]: 
                    chomp(row, col)
                    turn = 1 - turn

        screen.fill(black) 
        draw_chocolate() 
        display_turn()   
        if game_over:
            display_winner()

        pygame.display.flip()  

if __name__ == "__main__":
    main_game_loop()
