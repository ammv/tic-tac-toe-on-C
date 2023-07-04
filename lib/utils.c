#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define KEY_RIGHT   77
#define KEY_LEFT    75
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_ESC     27
#define KEY_ENTER   13

char *
str_center(char str[], unsigned int fieldSize, char fillChar)
{
    int strLen = strlen(str);
    int padding = fieldSize - strLen;
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    // Создаем новую строку с заданным размером
    char* centeredStr = (char*) malloc((fieldSize + 1) * sizeof(char));
    if (centeredStr == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    // Заполняем новую строку символами заполнения слева
    for (int i = 0; i < leftPadding; i++) {
        centeredStr[i] = fillChar;
    }
    // Копируем исходную строку в центр новой строки
    strncpy(centeredStr + leftPadding, str, strLen);
    // Заполняем новую строку символами заполнения справа
    for (int i = leftPadding + strLen; i < fieldSize; i++) {
        centeredStr[i] = fillChar;
    }
    // Добавляем завершающий нулевой символ
    centeredStr[fieldSize] = '\0';
    return centeredStr;
}

void hide_cursor()
{
    printf("\e[?25l");
}

void show_cursor()
{
    printf("\e[?25h");
}

void clear_console()
{
    printf("\e[1;1H\e[2J");
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

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void enable_ansi_in_windows_cmd()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return;
    }
    dwMode |= 0x0004 ;
    if (!SetConsoleMode(hOut, dwMode)) {
        return;
    }
}

#endif