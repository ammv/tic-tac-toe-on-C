#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define MAP_SIZE    9

#define EMPTY       -1 // 2
#define ZERO        0 // 3
#define CROSS       1 // 4
#define CURSOR      2

#define MAP_FORMATTER   " %s | %s | %s"
#define MAP_SPLIT       "---+---+---"
#define MAP_PRINT       MAP_FORMATTER "\n"  \
                        MAP_SPLIT "\n"      \
                        MAP_FORMATTER "\n"  \
                        MAP_SPLIT "\n"      \
                        MAP_FORMATTER "\n"

#define KEY_RIGHT   75
#define KEY_LEFT    77
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_ESC     27
#define KEY_ENTER   13

#define BG_WHITE_ESCAPE     "\033[47m"
#define BG_BLACK_ESCAPE     "\033[40m"
#define BG_BLUE_ESCAPE      "\033[44m"
#define RESET_ESCAPE        "\033[0m"

char* code_to_str(int code)
{
    char *strs[] = {BG_BLACK_ESCAPE " " RESET_ESCAPE, 
                    BG_BLACK_ESCAPE "O" RESET_ESCAPE,
                    BG_BLACK_ESCAPE "X" RESET_ESCAPE};
    if(code > 1)
    {
        code -= 3;
        strs[0] = BG_WHITE_ESCAPE " " RESET_ESCAPE;
        strs[1] = BG_BLUE_ESCAPE "O" RESET_ESCAPE;
        strs[2] = BG_BLUE_ESCAPE "X" RESET_ESCAPE;
        
    }

    if(code == EMPTY)
    {
        return strs[code+1];
    }
    else if(code == ZERO)
    {
        return strs[code+1];
    }
    return strs[code+1];
    
}

void display_map(char map[], int x, int y)
{
    int pos = y*3+x;
    map[pos] += 3;
    printf(MAP_PRINT,
        code_to_str(map[8]), code_to_str(map[7]), code_to_str(map[6]),
        code_to_str(map[5]), code_to_str(map[4]), code_to_str(map[3]),
        code_to_str(map[2]), code_to_str(map[1]), code_to_str(map[0]));
    map[pos] -= 3;
}

void init_map(char map[])
{
    for(int i = 0; i < MAP_SIZE; i++)
    {
        map[i] = EMPTY;
    }
}

int get_key()
{
    int ch;
    while(1)
    {
        ch = getch();
        if(ch == 0 || ch == 224)
        {
            ch = getch();
            if(ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_RIGHT)
            {
                return ch;
            }
        }
        else if(ch == KEY_ESC || ch == KEY_ENTER)
        {
            return ch;
        }  
    }
}

char check_winner(char map[])
{
    for(int i = 0; i < MAP_SIZE; i++)
    {
        if(map[i] == EMPTY)
        {
            map[i] = -3;
        }
    }
    char winner_combinations[MAP_SIZE-1] = {
        map[0]+map[1]+map[2],
        map[3]+map[4]+map[5],
        map[6]+map[7]+map[8],

        map[0]+map[3]+map[6],
        map[1]+map[4]+map[7],
        map[2]+map[5]+map[8],

        map[2]+map[4]+map[6],
        map[0]+map[4]+map[8],
    };

    for(int i = 0; i < MAP_SIZE-1; i++)
    {
        if(winner_combinations[i] >= 0 && winner_combinations[i] % 3 == 0)
        {
            return 1;
        }
    }

    for(int i = 0; i < MAP_SIZE; i++)
    {
        if(map[i] == -3)
        {
            map[i] = EMPTY;
        }
    }

    char draw = -1;
    for(int i = 0; i < MAP_SIZE; i++)
    {
        if(map[i] == EMPTY)
        {
            draw = 0;
            break;
        }
    }

    return draw;
}

int start_game()
{
    char map[MAP_SIZE];
    _Bool flag = 1;
    int x = 0, y = 0;

    init_map(map);

    char current_step = CROSS;

    while(flag)
    {
        // Clear console
        printf("\e[1;1H\e[2J");
        display_map(map, x, y);
        
        char winner = check_winner(map);
        if(winner == 1)
        {
            printf("\nWin %s\nPress any key to restart or Esc to close..", code_to_str(!current_step));
            return getch();
        }
        else if(winner == 0)
        {
            printf("\nStep %s", code_to_str(current_step));
        }
        else
        {
            printf("\nDraw\n\nPress any key to restart or Esc to close..");
            return getch();
        }
        switch (get_key())
        {
            case KEY_DOWN:
                if(y != 0) y--;
                break;

            case KEY_UP:
                if(y != 2) y++;
                break;

            case KEY_RIGHT:
                if(x != 2) x++;
                break;

            case KEY_LEFT:
                if(x != 0) x--;
                break;

            case KEY_ENTER:
                if(map[y*3+x] == EMPTY)
                {
                    map[y*3+x] = current_step;
                    current_step = !current_step;
                }
                break;

            case KEY_ESC:
                flag = 0;;
        }
    }
    return 0;
}

int main()
{
    // Hide cursor
    printf("\e[?25l");

    printf("Press to start...");
    getch();

    while(1)
    {
        if(start_game() == 27)
        {
            printf("\e[1;1H\e[2JBye!");
            return 0;
        }
        // Clear console
        printf("\e[1;1H\e[2J");
    }
    

    return 0;
}