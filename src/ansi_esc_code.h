#ifndef __ANSI_ESC_CODE_H__
#define __ANSI_ESC_CODE_H__

void hide_cursor(void);
void show_cursor(void);

void erase_screen(void);

void cursor_position(unsigned y, unsigned x);

void errase_full_line();

void reset_all_sgr_attr();

// The color value must be less than or equal to 7
void change_text_color(unsigned color);
void change_background_color(unsigned color);

void change_text_color_rgb(unsigned char r, unsigned char g, unsigned char b);
void change_background_color_rgb(unsigned char r, unsigned char g, unsigned char b);

void text_bold();
void text_italic();
void text_underline();

#endif // !__ANSI_ESC_CODE_H__
