#ifndef _TTT_FUNCS_H
#define _TTT_FUNCS_H

#include "../config.h"

void reset_board(char (*board)[3]);
void display_board(char (*board)[3]);
int check_free_spaces(char (*board)[3]);
int player_move(char (*board)[3], char player);
void computer_move(char (*board)[3], char computer, char difficult);
char check_winner(char (*board)[3], char *win_type, char *win_data);
void print_winner(char (*board)[3], char winner, char player, char win_type, char win_data);
void clear_console();

char * highlight_char(char cell, char need_highlight);
void display_board_for_move(char (*board)[3], int x, int y);

#endif