#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#define BG_WHITE_ESCAPE     "\033[47m"
#define BG_BLUE_ESCAPE      "\033[44m"

#define FG_GREEN_ESCAPE     "\033[32m"
#define FG_RED_ESCAPE      "\033[31m"

#define RESET_ESCAPE        "\033[00m"

#define EASY_DIFFICULT 0
#define MEDIUM_DIFFICULT 1
#define HARD_DIFFICULT 2

struct Vector2
{
    int x;
    int y;
};

struct TripleVector2
{
    struct Vector2 v1;
    struct Vector2 v2;
    struct Vector2 v3;
};

void reset_board(char (*board)[3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            board[i][k] = ' ';
        }
    }
}

char * highlight_char(char cell, char need_highlight)
{
    if(need_highlight)
    {
        switch(cell)
        {
            case 'X':
                return BG_BLUE_ESCAPE "X" RESET_ESCAPE;
            case 'O':
                return BG_BLUE_ESCAPE "O" RESET_ESCAPE;
            case ' ':
                return BG_WHITE_ESCAPE " " RESET_ESCAPE;
        }
    }
    else
    {
        switch(cell)
        {
            case 'X':
                return RESET_ESCAPE "X" RESET_ESCAPE;
            case 'O':
                return RESET_ESCAPE "O" RESET_ESCAPE;
            case ' ':
                return RESET_ESCAPE " " RESET_ESCAPE;
        }
    }
}

// 6,1,6,1

void printf_board(char *strs[], size_t size)
{
    printf("+%s+\n", strs[0]);
    printf("|                                        |\n");

    printf("|%s|\n", strs[1]);
    printf("|%s|\n", strs[4]);
    printf("|%s|\n", strs[2]);
    printf("|%s|\n", strs[4]);
    printf("|%s|\n", strs[3]);

    printf("|                                        |\n");
    printf("+----------------------------------------+\n");

    for (size_t i = 0; i < size; i++)
    {
        free(strs[i]);
    }
}

void display_board_for_move(char (*board)[3], int x, int y)
{
    char *strs[] = {
        str_center("GAME", 40, '-'),

        (char *)malloc(sizeof (char) * 41+36),
        (char *)malloc(sizeof (char) * 41+36),
        (char *)malloc(sizeof (char) * 41+36),

        str_center("---+---+---", 40, ' ')
    };

    char buffer[39];
    char *fmt = "%s | %s | %s";

    for (size_t i = 1; i < 4; i++)
    {
        int index = i-1; 
        
        sprintf(buffer, fmt, 
            highlight_char(board[index][0], index == y && 0 == x),
            highlight_char(board[index][1], index == y && 1 == x),
            highlight_char(board[index][2], index == y && 2 == x));
        strs[i] = str_center(buffer, 40+30, ' ');
    }
    printf_board(strs, sizeof(strs)/sizeof(strs[0]));
}

void display_board(char (*board)[3])
{
    char *strs[] = {
        str_center("GAME", 40, '-'),

        (char *)malloc(sizeof (char) * 41),
        (char *)malloc(sizeof (char) * 41),
        (char *)malloc(sizeof (char) * 41),

        str_center("---+---+---", 40, ' ')
    };

    char buffer[10];
    char *fmt = "%c | %c | %c";

    for (size_t i = 1; i < 4; i++)
    {
        sprintf(buffer, fmt, 
            board[i-1][0],
            board[i-1][1],
            board[i-1][2]);
        strs[i] = str_center(buffer, 40, ' ');
    }
    printf_board(strs, sizeof(strs)/sizeof(strs[0]));
}

int check_free_spaces(char (*board)[3])
{
    int free_spaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if(board[i][k] != ' ')
            {
                free_spaces--;
            }
        }
    }

    return free_spaces;
}

void set_optimal_pos(char (*board)[3], int *x, int *y)
{
    _Bool flag = 0;

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t k = 0; k < 3; k++)
        {
            if(board[i][k] == ' ')
            {
                *y = i;
                *x = k;
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            flag = 1;
            break;
        }
    }
}

int player_move(char (*board)[3], char player)
{
    
    int x = 0, y = 0;
    char step;
    _Bool flag = 1;
    
    set_optimal_pos(board, &x, &y);

    while(flag)
    {
        display_board_for_move(board, x, y);

        switch((step = get_key()))
        {
            case KEY_DOWN:
                if(y != 2) y++;
                break;

            case KEY_UP:
                if(y != 0) y--;
                break;

            case KEY_RIGHT:
                if(x != 2) x++;
                break;

            case KEY_LEFT:
                if(x != 0) x--;
                break;

            case KEY_ENTER:
                if(board[y][x] == ' ')
                {
                    board[y][x]= player;
                    flag = 0;
                }
                break;

            case KEY_ESC:
                return 1;
        }
        clear_console();
    }
    return 0;
    
}

void shuffle(struct TripleVector2 array[]) {
    int n = 8;
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          struct TripleVector2 t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void collect_win_poses(struct TripleVector2 win_poses[])
{
    // Horizontal
    win_poses[0] = (struct TripleVector2){{0,0}, {0,1}, {0,2}};
    win_poses[1] = (struct TripleVector2){{1,0}, {1,1}, {1,2}};
    win_poses[2] = (struct TripleVector2){{2,0}, {2,1}, {2,2}};

    // Vertical
    win_poses[3] = (struct TripleVector2){{0,0}, {1,0}, {2,0}};
    win_poses[4] = (struct TripleVector2){{0,1}, {1,1}, {2,1}};
    win_poses[5] = (struct TripleVector2){{0,2}, {1,2}, {2,2}};

    // Diagonal
    win_poses[6] = (struct TripleVector2){{0,0}, {1,1}, {2,2}};
    win_poses[7] = (struct TripleVector2){{0,2}, {1,1}, {2,0}};

    for (size_t i = 0; i < 5; i++)
    {
        shuffle(win_poses);
    }
}

double get_rate(char (*board)[3], char computer, struct Vector2 *v2)
{
    if(board[v2->x][v2->y] == computer)
    {
        return 1.5f;
    }
    else if(board[v2->x][v2->y] == ' ')
    {
        return 0.5f;
    }
    else
    {
        return -1.0f;
    }
}

void calculate_rates(double rates[], char (*board)[3], struct TripleVector2 win_poses[], char computer)
{
    for (size_t i = 0; i < 8; i++)
    {
        struct TripleVector2 tv2 = win_poses[i];

        rates[i] = get_rate(board, computer, &tv2.v1) + 
                get_rate(board, computer, &tv2.v2) + 
                get_rate(board, computer, &tv2.v3);
    }
}

int get_max_rate_index(double rates[])
{
    int max_rate_index = 0;
    for (size_t i = 1; i < 8; i++)
    {
        if(rates[i] > rates[max_rate_index])
        {
            max_rate_index = i;
        }
    }
    return max_rate_index;
}

int get_min_rate_index(double rates[])
{
    int min_rate_index = 0;
    for (size_t i = 1; i < 8; i++)
    {
        if(rates[i] < rates[min_rate_index])
        {
            min_rate_index = i;
        }
    }
    return min_rate_index;
}

int get_best_win_pos_middle(char (*board)[3], struct TripleVector2 win_poses[], char computer)
{
    double rates[8];

    calculate_rates(rates, board, win_poses, computer);
    
    return get_max_rate_index(rates);
}

int get_best_win_pos_hard(char (*board)[3], struct TripleVector2 win_poses[], char computer)
{
    double rates[8];

    calculate_rates(rates, board, win_poses, computer);

    int max_rate_index = get_max_rate_index(rates);
    int min_rate_index = get_min_rate_index(rates);

    if(rates[min_rate_index] == -1.5f && rates[max_rate_index] != 3.5f)
    {
        return min_rate_index;
    }
    return max_rate_index;
}

void computer_easy_step(char (*board)[3], char computer, int *x, int *y)
{
    srand(time(0));
    do
    {
            *x = rand() % 3;
            *y = rand() % 3;
    } while (board[*x][*y] != ' ');
}

void choice_pos_in_win_poses(char (*board)[3], int *x, int *y, struct TripleVector2 best_win_pos)
{
    while(1)
    {
        switch (rand() % 3)
        {
            case 0:
                if(board[best_win_pos.v1.x][best_win_pos.v1.y] == ' ')
                {
                    *x = best_win_pos.v1.x;
                    *y = best_win_pos.v1.y;
                    return;
                }
                break;

            case 1:
                if(board[best_win_pos.v2.x][best_win_pos.v2.y] == ' ')
                {
                    *x = best_win_pos.v2.x;
                    *y = best_win_pos.v2.y;
                    return;
                }
                break;

            case 2:
                if(board[best_win_pos.v3.x][best_win_pos.v3.y] == ' ')
                {
                    *x = best_win_pos.v3.x;
                    *y = best_win_pos.v3.y;
                    return;
                }
                break;
        }
    }
}

void computer_medium_step(char (*board)[3], char computer, int *x, int *y)
{
    struct TripleVector2 win_poses[8];
    collect_win_poses(win_poses);

    struct TripleVector2 best_win_pos = win_poses[get_best_win_pos_middle(board, win_poses, computer)];

    choice_pos_in_win_poses(board, x, y, best_win_pos);
    
}

char board_is_clear(char (*board)[3])
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t k = 0; k < 3; k++)
        {
            if(board[i][k] != ' ')
            {
                return 1;
            }
        }
        
    }

    return 0;
    
}

void collect_angle_poses(struct Vector2 angle_poses[])
{
    angle_poses[0] = (struct Vector2){0, 0};
    angle_poses[1] = (struct Vector2){0, 2};
    angle_poses[2] = (struct Vector2){2, 0};
    angle_poses[3] = (struct Vector2){2, 2};

    if(rand() % 2 == 0)
    {
        struct Vector2 buffer = angle_poses[0];
        angle_poses[0] = angle_poses[3];
        angle_poses[3] = buffer;
    }

    if(rand() % 3 == 0)
    {
        struct Vector2 buffer = angle_poses[1];
        angle_poses[1] = angle_poses[2];
        angle_poses[2] = buffer;
    }
}

struct Vector2 get_best_angle(char (*board)[3], struct Vector2 angle_poses[], char computer)
{
    int taked_angle_index = -1;

    for (size_t i = 0; i < 4; i++)
    {
        if(board[angle_poses[i].x][angle_poses[i].y] == computer)
        {
            taked_angle_index = i;
            break;
        }
    }

    if(board[1][1] != ' ')
    {
        if(taked_angle_index == 0)
        {
            return angle_poses[3];
        }
        else if(taked_angle_index == 3)
        {
            return angle_poses[0];
        }
        else if(taked_angle_index == 1)
        {
            return angle_poses[2];
        }
        else
        {
            return angle_poses[1];
        }
    }
    else
    {
        for (size_t i = 0; i < 4; i++)
        {
            if(i != taked_angle_index)
            {
                return angle_poses[i];
            }
        }
    }
}

int count_of_taked_angle_poses(char (*board)[3], char computer, struct Vector2 angle_poses[])
{
    int count = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if(board[angle_poses[i].x][angle_poses[i].y] == computer)
        {
            count++;
        }
    }
    return count;
    
}

void computer_hard_step(char (*board)[3], char computer, int *x, int *y)
{
    struct Vector2 angle_poses[4];
    collect_angle_poses(angle_poses);

    // if(check_free_spaces(board) >= 8 && count_of_taked_angle_poses(board, computer, angle_poses) < 2)
    // {
    //     struct Vector2 best_angle = get_best_angle(board, angle_poses, computer);
    //     *x = best_angle.x;
    //     *y = best_angle.y;
    // }
    // else
    // {
    //     struct TripleVector2 win_poses[8];
    //     collect_win_poses(win_poses);

    //     struct TripleVector2 best_win_pos = win_poses[get_best_win_pos_hard(board, win_poses, computer)];

    //     choice_pos_in_win_poses(board, x, y, best_win_pos);
    // }

    struct TripleVector2 win_poses[8];
        collect_win_poses(win_poses);

        struct TripleVector2 best_win_pos = win_poses[get_best_win_pos_hard(board, win_poses, computer)];

        choice_pos_in_win_poses(board, x, y, best_win_pos);
}

void computer_move(char (*board)[3], char computer, char difficult)
{
    int x = -1, y = -1;

    if(difficult == EASY_DIFFICULT)
    {
        computer_easy_step(board, computer, &x, &y);
    }
    else if(difficult == MEDIUM_DIFFICULT)
    {
        computer_medium_step(board, computer, &x, &y);
    }
    else if(difficult == HARD_DIFFICULT)
    {
        computer_hard_step(board, computer, &x, &y);
    }

    if(x != -1 && y != -1)
    {
        board[x][y] = computer; 
    }

    
}

char check_winner(char (*board)[3], char *win_type, char *win_data)
{
    // check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] != ' ' && board[i][0] == board[i][1] &&  board[i][0] == board[i][2])
        {
            *win_type = 0;
            *win_data = i;
            return board[i][0];
        }      
    }

    // check columns
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] != ' ' && board[0][i] == board[1][i] &&  board[0][i] == board[2][i])
        {
            *win_type = 1;
            *win_data = i;
            return board[0][i];
        }      
    }

    // check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        *win_type = 2;
        *win_data = 0;
        return board[0][0];
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        *win_type = 2;
        *win_data = 1;
        return board[0][2];
    }

    return ' ';
}

/*
    Если буква маленькая, значит она победная, если она совпадает с символовом победителя, красим в зеленый, иначе в красный
    иначе никак не красим
*/
char* highlight_winner_char(char cell, char winner, char player)
{
    switch(cell)
    {
        case 'O':
            return RESET_ESCAPE "O" RESET_ESCAPE;
        case 'X':
            return RESET_ESCAPE "X" RESET_ESCAPE;
        case ' ':
            return RESET_ESCAPE " " RESET_ESCAPE;

        case 'o':
            if(winner == player && cell == player)
            {
                return FG_GREEN_ESCAPE "O" RESET_ESCAPE;
            }
            else
            {
                return FG_RED_ESCAPE "O" RESET_ESCAPE;
            }
            
            
        case 'x':
            if(winner == player && cell == player)
            {
                return FG_GREEN_ESCAPE "X" RESET_ESCAPE;
            }
            else
            {
                return FG_RED_ESCAPE "X" RESET_ESCAPE;
            }
            
    }
}

void lower_winner(char (*board)[3], char win_type, char win_data)
{
    if(win_type == 0)
    {
        board[win_data][0] += 32;
        board[win_data][1] += 32;
        board[win_data][2] += 32;
    }
    else if(win_type == 1)
    {
        board[0][win_data] += 32;
        board[1][win_data] += 32;
        board[2][win_data] += 32;
    }
    else if(win_type == 2)
    {
        board[1][1] += 32;
        if(win_data == 0)
        {
            board[0][0] += 32;
            board[2][2] += 32;
        }
        else
        {
            board[0][2] += 32;
            board[2][0] += 32;
        }
    }
}

void print_winner(char (*board)[3], char winner, char player, char win_type, char win_data)
{
    char *strs[] = {
        str_center("GAME", 40, '-'),

        (char *)malloc(sizeof (char) * 41+36),
        (char *)malloc(sizeof (char) * 41+36),
        (char *)malloc(sizeof (char) * 41+36),

        str_center("---+---+---", 40, ' ')
    };

    char buffer[39];
    char *fmt = "%s | %s | %s";

    lower_winner(board, win_type, win_data);

    winner += 32;
    player += 32;

    for (size_t i = 1; i < 4; i++)
    {
        int index = i-1; 
        
        sprintf(buffer, fmt, 
            highlight_winner_char(board[index][0], winner, player),
            highlight_winner_char(board[index][1], winner, player),
            highlight_winner_char(board[index][2], winner, player));
        strs[i] = str_center(buffer, 40+30, ' ');
    }
    printf_board(strs, sizeof(strs)/sizeof(strs[0]));
}