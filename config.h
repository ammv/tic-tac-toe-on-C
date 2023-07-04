#ifndef _CONFIG_H
#define _CONFIG_H

#define EASY_DIFFICULT 0
#define MEDIUM_DIFFICULT 1
#define HARD_DIFFICULT 2

char COMPUTER_DIFFICULT = EASY_DIFFICULT;

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

// -------------------------CODE SPLIT------------------------------

#define MENU_CHOICE_FORMAT "|\e[38;5;50m%s\e[0m|\n"
#define MENU_NOT_CHOICE_FORMAT "|%s|\n"
#define MENU_SPACE "|                                        |\n"
#define MENU_BOTTOM "+----------------------------------------+\n"

// -------------------------CODE SPLIT------------------------------


enum MENU_EXIT_STATUS
{
    MENU_EXIT_NO,
    MENU_EXIT_YES
} menu_exit_status;

char *menu_exit_yes_fmt = MENU_NOT_CHOICE_FORMAT;
char *menu_exit_no_fmt = MENU_NOT_CHOICE_FORMAT;

char *menu_exit_yes_str = "Yes";
char *menu_exit_no_str = "No";

// -------------------------CODE SPLIT------------------------------

enum MENU_DIFFICULT_STATUS
{
    MENU_DIFFICULT_EASY,
    MENU_DIFFICULT_MEDIUM,
    MENU_DIFFICULT_HARD
} menu_difficult_status;

char *menu_difficult_easy_fmt = MENU_NOT_CHOICE_FORMAT;
char *menu_difficult_medium_fmt = MENU_NOT_CHOICE_FORMAT;
char *menu_difficult_hard_fmt = MENU_NOT_CHOICE_FORMAT;

char *menu_difficult_easy_str = "Easy";
char *menu_difficult_medium_str = "Medium";
char *menu_difficult_hard_str = "Hard";

// -------------------------CODE SPLIT------------------------------

enum MENU_MAIN_STATUS
{
    MENU_MAIN_START,
    MENU_MAIN_DIFFUCULT,
    MENU_MAIN_EXIT
} menu_main_status;


char *menu_main_start_fmt = MENU_NOT_CHOICE_FORMAT;
char *menu_main_difficult_fmt = MENU_NOT_CHOICE_FORMAT;
char *menu_main_exit_fmt = MENU_NOT_CHOICE_FORMAT;

char *menu_main_start_str = "Start";
char *menu_main_difficult_str = "Difficult";
char *menu_main_exit_str = "Exit";

// -------------------------CODE SPLIT------------------------------

#endif