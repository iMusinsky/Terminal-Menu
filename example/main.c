#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bash_menu.h"

int main()
{
    char *test_text[] = {"1. 1", "2. 2", "3. 3", "4. Exit"};
    unsigned lines = 4;
    unsigned start_point = 1;

    char attr[] = "4";
    print_config *cfg = init_print_cfg();

    int res = get_choice(cfg, NULL, test_text, lines);

    printf("result = %d\n", res);

    return 0;
}
