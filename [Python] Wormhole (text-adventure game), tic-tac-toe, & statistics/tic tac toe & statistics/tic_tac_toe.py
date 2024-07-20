import pygame
import tkinter as tk
import os

# GLOBAL VARIABLES:


clear = lambda: os.system('cls')
clear()
print("\n\n")


# TIC_TAC_TOE

game_still_going = True
winner = None
current_player = "X"


# board
board = ["-", "-", "-",
         "-", "-", "-",
         "-", "-", "-"]


# display board
def display_board():
    print("")
    print(board[0] + " | " + board[1] + " | " + board[2])
    print(board[3] + " | " + board[4] + " | " + board[5])
    print(board[6] + " | " + board[7] + " | " + board[8])
    return


# play game
def play_game():
    display_board()

    # while not game_over()
    while game_still_going:

        handle_turn(current_player)

        check_if_game_over()

        flip_player()

    # GAME OVER
    if winner == "X" or winner == "O":
        print("\n" + winner + " won!")
    elif winner is None:
        print("\nCongrats, Cat!  The humans suck apparently...\n")
    return


def flip_player():
    global current_player
    if current_player == "X":
        current_player = "O"
    elif current_player == "O":
        current_player = "X"
    return


def handle_turn(player):
    print(player + "'s turn.")
    position = input("Choose a position 1-9 (starts at top left and numbered left to right): ")

    valid = False
    while not valid:

        while position not in ["1", "2", "3", "4", "5", "6", "7", "8", "9"]:
            position = input("Invalid choice! Choose 1-9: ")

        position = int(position) - 1

        if board[position] == "-":
            valid = True
        else:
            print("You can't go there! ")

    board[position] = player

    display_board()
    return


def check_if_game_over():
    check_if_winner()
    check_if_tie()
    return


def check_if_winner():
    global winner

    # check rows
    row_winner = check_rows()
    # check columns
    column_winner = check_columns()
    # check diags
    diag_winner = check_diags()

    if row_winner:
        winner = row_winner
    elif column_winner:
        winner = column_winner
    elif diag_winner:
        winner = diag_winner
    else:
        winner = None
    return


def check_rows():
    global game_still_going
    row_1 = board[0] == board[1] == board[2] != "-"
    row_2 = board[3] == board[4] == board[5] != "-"
    row_3 = board[6] == board[7] == board[8] != "-"
    if row_1 or row_2 or row_3:
        game_still_going = False
    # Check for "X" winner or "O" winner (checks single spot for "X" or "O")
    if row_1:
        return board[0]
    elif row_2:
        return board[3]
    elif row_3:
        return board[6]
    return


def check_columns():
    global game_still_going
    column_1 = board[0] == board[3] == board[6] != "-"
    column_2 = board[1] == board[4] == board[7] != "-"
    column_3 = board[2] == board[5] == board[8] != "-"
    if column_1 or column_2 or column_3:
        game_still_going = False
    # Check for "X" winner or "O" winner (checks single spot for "X" or "O")
    if column_1:
        return board[0]
    elif column_2:
        return board[1]
    elif column_3:
        return board[2]
    return


def check_diags():
    global game_still_going
    diag_1 = board[0] == board[4] == board[8] != "-"
    diag_2 = board[2] == board[4] == board[6] != "-"
    if diag_1 or diag_2:
        game_still_going = False
    # Check for "X" winner or "O" winner (checks single spot for "X" or "O")
    if diag_1:
        return board[0]
    elif diag_2:
        return board[2]
    return


def check_if_tie():
    global game_still_going
    if "-" not in board:
        game_still_going = False
    return


play_game()
