#include <stdio.h> 
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "lib/utils.h"

#include "lib/ttt_funcs.h"

// -------------------------CODE SPLIT------------------------------

int start_game();

void menu_exit_update_format()
{
    switch (menu_exit_status)
        {
            case MENU_EXIT_YES:
                menu_exit_yes_fmt = MENU_CHOICE_FORMAT;
                menu_exit_yes_str = "<Yes>";
                break;

            case MENU_EXIT_NO:
                menu_exit_no_fmt = MENU_CHOICE_FORMAT;
                menu_exit_no_str = "<No>";
                break;
        }
}

void menu_exit_clear_format()
{
    menu_exit_no_fmt = MENU_NOT_CHOICE_FORMAT;
    menu_exit_yes_fmt = MENU_NOT_CHOICE_FORMAT;

    menu_exit_no_str = "No";
    menu_exit_yes_str = "Yes";

    
}

void menu_exit_print()

{
    char *strs[] = {
        str_center("EXIT", 40, '-'),
        str_center("Are you sure?", 40, ' '),
        str_center(menu_exit_no_str, 40, ' '),
        str_center(menu_exit_yes_str, 40, ' ')};

    printf("+%s+\n" , strs[0]);
    printf(MENU_SPACE);
    printf("|%s|\n", strs[1]);

    printf(menu_exit_no_fmt, strs[2]);
    printf(menu_exit_yes_fmt, strs[3]);

    printf(MENU_SPACE);
    printf(MENU_BOTTOM);

    for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); i++)
    {
        free(strs[i]);
    }
    
}

void menu_exit_action()
{
    clear_console();
    switch (menu_exit_status)
    {
        case MENU_EXIT_YES:
            printf("Bye!\n");
            exit(0);
            break;

        case MENU_EXIT_NO:
            return;
            break;
    }
}

void menu_exit()
{
    _Bool flag = 1;
    while(flag)
    {
        clear_console();
        
        menu_exit_update_format();
        menu_exit_print();
        menu_exit_clear_format();

        switch(get_key())
        {
            case KEY_DOWN:
                if(menu_exit_status != MENU_EXIT_YES)
                {
                    menu_exit_status++;
                }
                
                break;

            case KEY_UP:
                if(menu_exit_status != MENU_EXIT_NO)
                {
                    menu_exit_status--;
                }
                break;

            case KEY_ENTER:
                menu_exit_action();
                flag = 0;
                break;
        }

        
    }
}

// -------------------------CODE SPLIT------------------------------

void menu_difficult_update_format()
{
    switch (menu_difficult_status)
        {
            case MENU_DIFFICULT_EASY:
                menu_difficult_easy_fmt = MENU_CHOICE_FORMAT;
                menu_difficult_easy_str = "<Easy>";
                break;

            case MENU_DIFFICULT_MEDIUM:
                menu_difficult_medium_fmt = MENU_CHOICE_FORMAT;
                menu_difficult_medium_str = "<Medium>";
                break;

            case MENU_DIFFICULT_HARD:
                menu_difficult_hard_fmt = MENU_CHOICE_FORMAT;
                menu_difficult_hard_str = "<Hard>";
                break;
        }
}

void menu_difficult_clear_format()
{
    menu_difficult_easy_fmt = MENU_NOT_CHOICE_FORMAT;
    menu_difficult_medium_fmt = MENU_NOT_CHOICE_FORMAT;
    menu_difficult_hard_fmt = MENU_NOT_CHOICE_FORMAT;

    menu_difficult_easy_str = "Easy";
    menu_difficult_medium_str = "Medium";
    menu_difficult_hard_str = "Hard";
}

char * get_curent_difficult()
{
    switch (COMPUTER_DIFFICULT)
    {
        case EASY_DIFFICULT:
            return "\e[38;5;046mEasy\e[0m";
            break;

        case MEDIUM_DIFFICULT:
            return "\e[38;5;214mMedium\e[0m";
            break;

        case HARD_DIFFICULT:
            return "\e[38;5;196mHard\e[0m";
            break;
    }
}

void menu_difficult_print()
{
    char *current_diff = concat("Current is ", get_curent_difficult());
    char *strs[] = {
        str_center("DIFFICULT", 40, '-'),
        str_center(current_diff, 55, ' '),
        str_center(menu_difficult_easy_str, 40, ' '), 
        str_center(menu_difficult_medium_str, 40, ' '),
        str_center(menu_difficult_hard_str, 40, ' ')};

    printf("+%s+\n", strs[0]);
    printf(MENU_SPACE);

    printf("|%s|\n", strs[1]);
    printf(menu_difficult_easy_fmt, strs[2]);
    printf(menu_difficult_medium_fmt, strs[3]);
    printf(menu_difficult_hard_fmt, strs[4]);

    printf(MENU_SPACE);
    printf(MENU_BOTTOM);


    for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); i++)
    {
        free(strs[i]);
    }
    free(current_diff);
    
}

void menu_difficult_action()
{
    clear_console();
    switch (menu_difficult_status)
    {
        case MENU_DIFFICULT_EASY:
            COMPUTER_DIFFICULT = EASY_DIFFICULT;
            break;

        case MENU_DIFFICULT_MEDIUM:
            COMPUTER_DIFFICULT = MEDIUM_DIFFICULT;
            break;

        case MENU_DIFFICULT_HARD:
            COMPUTER_DIFFICULT = HARD_DIFFICULT;
            break;
    }
}

void menu_difficult()
{
    _Bool flag = 1;
    while(flag)
    {
        clear_console();
        
        menu_difficult_update_format();
        menu_difficult_print();
        menu_difficult_clear_format();

        switch(get_key())
        {
            case KEY_DOWN:
                if(menu_difficult_status != MENU_DIFFICULT_HARD)
                {
                    menu_difficult_status++;
                }
                
                break;

            case KEY_UP:
                if(menu_difficult_status != MENU_DIFFICULT_EASY)
                {
                    menu_difficult_status--;
                }
                break;

            case KEY_ENTER:
                menu_difficult_action();
                menu_main_status = MENU_MAIN_START;
                flag = 0;
                break;
        }

        
    }
}

// -------------------------CODE SPLIT------------------------------

void menu_main_update_format()
{
    switch (menu_main_status)
        {
            case MENU_MAIN_START:
                menu_main_start_fmt = MENU_CHOICE_FORMAT;
                menu_main_start_str = "<Start>";
                break;

            case MENU_MAIN_DIFFUCULT:
                menu_main_difficult_fmt = MENU_CHOICE_FORMAT;
                menu_main_difficult_str = "<Difficult>";
                break;

            case MENU_MAIN_EXIT:
                menu_main_exit_fmt = MENU_CHOICE_FORMAT;
                menu_main_exit_str = "<Exit>";
                break;
        }
}

void menu_main_clear_format()
{
    menu_main_start_fmt = MENU_NOT_CHOICE_FORMAT;
    menu_main_difficult_fmt = MENU_NOT_CHOICE_FORMAT;
    menu_main_exit_fmt = MENU_NOT_CHOICE_FORMAT;

    menu_main_start_str = "Start";
    menu_main_difficult_str = "Difficult";
    menu_main_exit_str = "Exit";
}

void menu_main_print()
{
    char *strs[] = {
        str_center("MENU", 40, '-'),
        str_center(menu_main_start_str, 40, ' '),
        str_center(menu_main_difficult_str, 40, ' '),
        str_center(menu_main_exit_str, 40, ' ')
    };

    printf("+%s+\n", strs[0]);
    printf(MENU_SPACE);

    printf(menu_main_start_fmt, strs[1]);
    printf(menu_main_difficult_fmt, strs[2]);
    printf(menu_main_exit_fmt, strs[3]);

    printf(MENU_SPACE);
    printf(MENU_BOTTOM);

    for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); i++)
    {
        free(strs[i]);
    }
}

void menu_main_action()
{
    clear_console();
    switch (menu_main_status)
    {
        case MENU_MAIN_START:
            start_game();
            break;

        case MENU_MAIN_EXIT:
            menu_exit();
            break;

        case MENU_MAIN_DIFFUCULT:
            menu_difficult();
            break;
    }
}

void menu_main()
{
    while(1)
    {
        clear_console();

        menu_main_update_format();
        menu_main_print();
        menu_main_clear_format();

        switch(get_key())
        {
            case KEY_DOWN:
                if(menu_main_status != MENU_MAIN_EXIT)
                {
                    menu_main_status++;
                }
                break;

            case KEY_UP:
                if(menu_main_status != MENU_MAIN_START)
                {
                    menu_main_status--;
                }
                break;

            case KEY_ENTER:
                menu_main_action();
                break;
        }
    }
}

// -------------------------CODE SPLIT------------------------------

void set_test_positions()
{
    board[0][0] = PLAYER;
    board[1][1] = PLAYER;
    board[0][2] = PLAYER;

    board[1][2] = COMPUTER;
    board[2][2] = COMPUTER;
}

int start_game()
{
    char winner = ' ';

    char win_type = -1;
    char win_data = -1;

    char who_move = rand() % 2 ? PLAYER: COMPUTER;
    //char who_move = COMPUTER;

    reset_board(board);
    clear_console();

    //set_test_positions();

    while(winner == ' ' && check_free_spaces(board) != 0)
    {
        if(who_move == PLAYER)
        {
            if(player_move(board, PLAYER))
            {  
                break;
            }
            winner = check_winner(board, &win_type, &win_data);
            who_move = COMPUTER;
        }
        
        if(winner == ' ' && check_free_spaces(board) != 0)
        {

            computer_move(board, COMPUTER, COMPUTER_DIFFICULT);
            winner = check_winner(board, &win_type, &win_data);
            who_move = PLAYER;
        }
    }

    print_winner(board, winner, PLAYER, win_type, win_data);
    getch();

    return 0;
}



int main()
{
    enable_ansi_in_windows_cmd();
    clear_console();
    hide_cursor();
    menu_main();

    return 0;
}
