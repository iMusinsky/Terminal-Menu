#include "terminal_menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

#include "ansi_esc_code.h"

const char up[]     = "\x1b[A";
const char down[]   = "\x1b[B";
const char result[] = "\x1b[C";


enum ColorType
{
    ColorTypeBasic,
    ColorTypeRGB,
    ColorTypeNone,
};

enum ChoiceResult
{
    BAD_RESULT = -1,
    RESULT     ,
    DOWN       ,
    UP         ,
};

struct text_attributes
{
    unsigned short is_bold      : 1;
    unsigned short is_italic    : 1;
    unsigned short is_underline : 1;
};

struct color_cfg
{
    int        color_type;
    int        basic_color;
    struct RGB rgb_color;
};

struct text_config
{
    struct color_cfg       text;
    struct color_cfg       background;
    struct text_attributes used_attrs;
};

struct print_config
{
    struct text_config selected_text;
    struct text_config other_text;
    struct text_config header;
};

int off_text_color(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
    switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.text.color_type = ColorTypeNone;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.text.color_type = ColorTypeNone;
        break;
    default:
        return -1;
    }
}

int off_background_color(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
    switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.background.color_type = ColorTypeNone;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.background.color_type = ColorTypeNone;
        break;
    default:
        return -1;
    }
}

int set_text_color(print_config * const obj, TextType type, enum BasicColor color)
{
    if (!obj) {
        return -1;
    }
    if (color < 0 || color > 7) {
        return -1;
    }

    switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.text.color_type  = ColorTypeBasic;
        obj->selected_text.text.basic_color = color;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.text.color_type  = ColorTypeBasic;
        obj->other_text.text.basic_color = color;
        break;
    default:
        return -1;
    }
    return 0;
}
int set_text_color_rgb(print_config * const obj, TextType type, struct RGB color)
{
    if (!obj) {
        return -1;
    }

    switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.text.color_type  = ColorTypeRGB;
        obj->selected_text.text.rgb_color = color;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.text.color_type  = ColorTypeRGB;
        obj->other_text.text.rgb_color = color;
        break;
    default:
        return -1;
    }
    return 0;
}


int set_background_color(print_config * const obj, TextType type, enum BasicColor color)
{
    if (!obj) {
        return -1;
    }
    if (color < 0 || color > 7) {
        return -1;
    }

    switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.background.color_type  = ColorTypeBasic;
        obj->selected_text.background.basic_color = color;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.background.color_type  = ColorTypeBasic;
        obj->other_text.background.basic_color = color;
        break;
    default:
        return -1;
    }
    return 0;
}

int set_background_color_rgb(print_config * const obj, TextType type, struct RGB color)
{
    if (!obj) {
        return -1;
    }

    switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.background.color_type = ColorTypeRGB;
        obj->selected_text.background.rgb_color  = color;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.background.color_type = ColorTypeRGB;
        obj->other_text.background.rgb_color  = color;
        break;
    default:
        return -1;
    }
    return 0;
}

int set_text_bold(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
        switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.used_attrs.is_bold = 1;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.used_attrs.is_bold = 1;
        break;
    default:
        return -1;
    }
    return 0;
}

int off_text_bold(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
        switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.used_attrs.is_bold = 0;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.used_attrs.is_bold = 0;
        break;
    default:
        return -1;
    }
    return 0;
}
int set_text_italic(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
        switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.used_attrs.is_italic = 1;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.used_attrs.is_italic = 1;
        break;
    default:
        return -1;
    }
    return 0;
}
int off_text_italic(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
        switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.used_attrs.is_italic = 0;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.used_attrs.is_italic = 0;
        break;
    default:
        return -1;
    }
    return 0;
}
int set_text_underline(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
        switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.used_attrs.is_underline = 1;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.used_attrs.is_underline = 1;
        break;
    default:
        return -1;
    }
    return 0;
}
int off_text_underline(print_config * const obj, TextType type)
{
    if (!obj) {
        return -1;
    }
        switch (type)
    {
    case TEXT_TYPE_SELECTED:
        obj->selected_text.used_attrs.is_underline = 0;
        break;
    case TEXT_TYPE_OTHER:
        obj->other_text.used_attrs.is_underline = 0;
        break;
    default:
        return -1;
    }
    return 0;
}

struct print_config* init_print_cfg()
{
    struct print_config *cfg = malloc(sizeof(*cfg));
    memset(cfg, 0, sizeof(*cfg));

    cfg->other_text.text.color_type  = ColorTypeBasic;
    cfg->other_text.text.basic_color = WHITE;

    cfg->other_text.background.color_type  = ColorTypeNone;

    cfg->selected_text = cfg->other_text;
    cfg->selected_text.text.basic_color = RED;
    cfg->selected_text.used_attrs.is_underline = 1;


    return cfg;
}

void deinit_print_cfg(struct print_config *obj)
{
    if (obj) {
        free(obj);
    }
}

int read_console()
{
    int rb = -1;

    struct termios oldt;
    tcgetattr( STDIN_FILENO, &oldt );

    struct termios newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );

    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    rb = fgetc(stdin);

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    return rb;
}

int is_up(char const * const choice, unsigned char_count)
{
    return strncmp(up, choice, strlen(up)) == 0 ? UP : BAD_RESULT;
}
int is_down(char const * const choice, unsigned char_count)
{
    return strncmp(down, choice, strlen(down)) == 0 ? DOWN : BAD_RESULT;
}
int is_result(char const * const choice, unsigned char_count)
{
    if (char_count == 0) { return BAD_RESULT; }

    if (strncmp(result, choice, strlen(result)) == 0 || *choice == 10) {
        return RESULT;
    } else {
        return BAD_RESULT;
    }
}

int is_hotkey(char const * const choice, unsigned char_count)
{
    if (is_up    (choice, char_count) == UP    ) { return UP;     }
    if (is_down  (choice, char_count) == DOWN  ) { return DOWN;   }
    if (is_result(choice, char_count) == RESULT) { return RESULT; }

    return BAD_RESULT;
}

int get_choice_from_console()
{
    unsigned length = 3;
    char buffer[length];
    memset(buffer, 0, length);

    for (size_t idx = 0; idx < length; ++idx) {
        buffer[idx] = read_console();

        int res = is_hotkey(buffer, idx + 1);
        if (res != BAD_RESULT) { return res; }
    }
    return BAD_RESULT;
}

void use_text_fmt(struct text_config fmt)
{
    if (fmt.used_attrs.is_bold)      { text_bold();      }
    if (fmt.used_attrs.is_italic)    { text_italic();    }
    if (fmt.used_attrs.is_underline) { text_underline(); }

    switch (fmt.text.color_type)
    {
    case ColorTypeBasic:
    {
        change_text_color(fmt.text.basic_color);
    } break;
    
    case ColorTypeRGB:
    { 
        change_text_color_rgb(fmt.text.rgb_color.r, fmt.text.rgb_color.g, fmt.text.rgb_color.b);
    } break;

    case ColorTypeNone:
    default:
        break;
    }

    switch (fmt.background.color_type)
    {
    case ColorTypeBasic:
    {
        change_background_color(fmt.background.basic_color);
    } break;
    
    case ColorTypeRGB:
    {
        change_background_color_rgb(fmt.text.rgb_color.r, fmt.text.rgb_color.g, fmt.text.rgb_color.b);
    } break;
    
    case ColorTypeNone:
    default:
        break;
    }
}

void print_line(char const * const text, unsigned line_coord, struct text_config fmt)
{
    if (!text) {
        return;
    }

    cursor_position(line_coord, 1);
    errase_full_line();
 
    use_text_fmt(fmt);

    printf("%s\n", text);

    reset_all_sgr_attr();
}

int get_choice(struct print_config const * const cfg, char *text[], unsigned lines)
{
    if (!cfg)  { return -1; }
    if (!text) { return -1; }
    if (lines == 0) { return -1; }

    hide_cursor();
    cursor_position(1, 1);
    erase_screen();



    unsigned start_point = 1;
    cursor_position(start_point + lines + 1, 1);
    errase_full_line();
    printf("↑ - Up / ↓ - Down / Enter or → - Select");

    print_line(text[0], start_point, cfg->selected_text);
    for (size_t i = 1; i < lines; ++i) {
        print_line(text[i], start_point + i, cfg->other_text);
    }

    int is_select    = 0;
    int need_reprint = 0;
    unsigned prev_line = 0;
    unsigned cur_line  = 0;
    do {
        enum ChoiceResult ch_res = get_choice_from_console();

        switch (ch_res)
        {
        case UP:
            prev_line = cur_line;
            cur_line += lines;
            cur_line -= 1;
            cur_line %= lines;

            need_reprint = 1;
            break;

        case DOWN:
            prev_line = cur_line;
            cur_line += 1;
            cur_line %= lines;

            need_reprint = 1;
            break;

        case RESULT:
            is_select = 1;
            break;
        
        case BAD_RESULT:
        default:
            break;
        }

        if (need_reprint) {
            print_line(text[prev_line], start_point + prev_line, cfg->other_text);
            print_line(text[cur_line], start_point + cur_line, cfg->selected_text);

            need_reprint = 0;
        }
    } while (!is_select);

    cursor_position(start_point + lines + 1, 1);
    errase_full_line();
    show_cursor();

    return cur_line + 1;
}
