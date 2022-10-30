#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
int main()
{
    char *line;
    while (1)
    {
        line = readline("tebbi=>");
        if (strlen(line) == 0)
            {
                rl_redisplay()
                clear_history();
            }
        rl_on_new_line();
        add_history(line);
        printf("hahahahaha   %s\n", line);
    }
}