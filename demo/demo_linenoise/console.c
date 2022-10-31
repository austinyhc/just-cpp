#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"

void completion(const char *buf, linenoiseCompletions *lc)
{
    if (buf[0] == 'h') {
        linenoiseAddCompletion(lc, "hello");
        linenoiseAddCompletion(lc, "hello there");
    }
}

char *hints(const char *buf, int *color, int *bold)
{
    if (!strcasecmp(buf, "git remote add")) {
        *color = 35;
        *bold = 0;
        return " <name> <url>";
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    char *cmdline;

    linenoiseSetCompletionCallback(completion);
    linenoiseSetHintsCallback(hints);

    while ((cmdline = linenoise("hello> ")) != NULL) {

        if (!strcmp(cmdline, "clear")) {
            linenoiseClearScreen();
            linenoiseFree(cmdline);
            continue;
        }

        if (cmdline[0] != '\0' && cmdline[0] != '/') {
            printf("You wrote: %s\n", cmdline);
            linenoiseHistoryAdd(cmdline);
            linenoiseHistorySave("history.txt");
        } else if (!strncmp(cmdline, "/historylen", 11)) {
            int len = atoi(cmdline+11);
            linenoiseHistorySetMaxLen(len);
        } else if (cmdline[0] == '/') {
            printf("Unrecognized command: %s\n", cmdline);
        }
        linenoiseFree(cmdline);
    }
    return 0;
}
