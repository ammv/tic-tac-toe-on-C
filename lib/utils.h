#ifndef _UTILS_H
#define _UTILS_H

#define KEY_RIGHT   77
#define KEY_LEFT    75
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_ESC     27
#define KEY_ENTER   13

// Centring the str
char *
str_center(char str[], unsigned int new_length, char placeholder);

// hide cursor in console
void hide_cursor();

// show cursor in console
void show_cursor();

// clear the console
void clear_console();

// get key: arrows, enter or ESC
char get_key();

// contactenae string
char* concat(const char *s1, const char *s2);

// enable ansi sequances
void enable_ansi_in_windows_cmd();

#endif
