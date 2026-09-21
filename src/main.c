#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

int main(void)
{
    char input[MAX_INPUT_SIZE];

    printf("=================================\n");
    printf("      CDB Database Engine\n");
    printf("          Version 0.1\n");
    printf("=================================\n");

    while (1)
    {
        printf("CDB> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(input, "help") == 0)
        {
            printf("\nAvailable commands:\n");
            printf("  help\n");
            printf("  exit\n\n");
        }
        else if (strlen(input) == 0)
        {
            continue;
        }
        else
        {
            printf("Unknown command: %s\n", input);
        }
    }

    return 0;
}
