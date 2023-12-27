#include "ansi_esc_code.h"

#include "stdio.h"

void hide_cursor(void)
{
    printf("\x1b[?25l");
}

void show_cursor(void)
{
    printf("\x1b[?25h");
}


void erase_data(unsigned i)
{
    if (i > 2) return ;
    printf("\x1b[%uJ", i);
}

void erase_screen(void)
{
    erase_data(2);
}


void cursor_position(unsigned y, unsigned x)
{
    printf("\x1b[%u;%uH", y, x);
}


void erase_line(unsigned i)
{
    printf("\x1b[%uK", i);
}

void errase_full_line()
{
    erase_line(2);
}


// SGR - Select Graphics Rendition
void reset_all_sgr_attr()
{
    printf("\x1b[0m");
}

void change_text_color(unsigned color)
{
    if (color > 7) { return; }
    printf("\x1b[3%dm", color);
}

void change_background_color(unsigned color)
{
    if (color > 7) { return; }
    printf("\x1b[4%dm", color);
}

void change_text_color_rgb(unsigned char r, unsigned char g, unsigned char b)
{
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

void change_background_color_rgb(unsigned char r, unsigned char g, unsigned char b)
{
    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}

void text_bold()
{
    printf("\x1b[1m");
}
void text_italic()
{
    printf("\x1b[3m");
}
void text_underline()
{
    printf("\x1b[4m");
}
