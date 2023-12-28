#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "terminal_menu.h"

int main()
{
    char *test_text[] = {"1. 1", "2. 2", "3. 3", "4. Exit"};
    unsigned lines = 4;
    print_config *cfg = init_print_cfg();

    set_text_color(cfg, TEXT_TYPE_SELECTED, MAGNETA);
    set_text_bold(cfg, TEXT_TYPE_SELECTED);

    int res = get_choice(cfg, test_text, lines);

    printf("result = %d\n", res);

    return 0;
}
