#ifndef __BASH_MENU_H__
#define __BASH_MENU_H__

enum BasicColor
{
    BLACK   = 0,
    RED     = 1,
    GREEN   = 2,
    YELLOW  = 3,
    BLUE    = 4,
    MAGNETA = 5,
    CYAN    = 6,
    WHITE   = 7,
};

struct RGB
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};


typedef enum
{
    TEXT_TYPE_SELECTED,
    TEXT_TYPE_OTHER   ,
} TextType;

typedef struct print_config print_config;
struct print_config* init_print_cfg();
void deinit_print_cfg(struct print_config *obj);

int get_choice(struct print_config const * const cfg, char *text[], unsigned lines);

// return 0 if success
int off_text_color    (print_config * const obj, TextType type);
int set_text_color    (print_config * const obj, TextType type, enum BasicColor color);
int set_text_color_rgb(print_config * const obj, TextType type, struct RGB      color);


int off_background_color    (print_config * const obj, TextType type);
int set_background_color    (print_config * const obj, TextType type, enum BasicColor color);
int set_background_color_rgb(print_config * const obj, TextType type, struct RGB      color);

int set_text_bold(print_config * const obj, TextType type);
int off_text_bold(print_config * const obj, TextType type);

int set_text_italic(print_config * const obj, TextType type);
int off_text_italic(print_config * const obj, TextType type);

int set_text_underline(print_config * const obj, TextType type); 
int off_text_underline(print_config * const obj, TextType type); 

#endif // !__BASH_MENU_H__
