#ifndef TINYCLI_H
#define TINYCLI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_STR_LEN 32 
#define MAX_OPTION_COUNT 32

typedef void (*OptionCB)(void);

typedef struct {
    uint8_t text[MAX_STR_LEN+1];
    OptionCB callback; // function called when option is selected
} Option;

typedef struct {
    uint8_t header[MAX_STR_LEN+1];
    Option *options;
    uint8_t count;
} Screen;

void screen_create(Screen *screen, uint8_t *header, Option *options, uint8_t count);
void screen_draw(Screen *screen);
uint8_t screen_handle_input(Screen *screen);
void screen_switch(Screen *current, Screen *next);
void screen_clear();

void screen_create(Screen* screen, uint8_t *header, Option *options, uint8_t count) {
    if (screen == NULL) {} // bad
    if (options == NULL) {} // bad

    screen->count = count;
    if (screen->count > MAX_OPTION_COUNT) {} // bad

    int length = strlen(header);
    if (length > MAX_STR_LEN) {} // bad

    memset(screen->header, 0, MAX_STR_LEN+1);
    memcpy(screen->header, header, length);
    screen->options = options;
}

void screen_draw(Screen *screen) {
    int length = strlen(screen->header);
    for (int i = 0; i < MAX_STR_LEN; i++) {
        printf("-");
    }
    printf("\n  %s\n", screen->header);
    for (int i = 0; i < MAX_STR_LEN; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < screen->count; i++) {
        printf("\t%d. %s\n", i+1, screen->options[i].text);
    }

    printf("\n");
}

uint8_t screen_handle_input(Screen *screen) {
    if (screen == NULL) {
        printf("screen is NULL, cannot handle input\n");
    }

    printf("> Select an option from: 1-%d\n", screen->count);

    int val;
    uint8_t line[MAX_STR_LEN+1];
    memset(line, 0, MAX_STR_LEN+1);
    fgets(line, MAX_STR_LEN+1, stdin);

    for (int i = 0; i < MAX_STR_LEN; i++) {
        uint8_t c = line[i];
        if (c == 0 || c == '\n' || c == '\r') break;

        if (c < '0' || c > '9') {
            printf("enter a digit... retry...\n");
            return 0;
        }
    }

    val = atoi(line);
    if (val <= 0 || val > screen->count) {
        printf("input number not valid... retry...\n");
        return 0;
    }

    return (uint8_t)val;
}

void screen_switch(Screen *current, Screen *next) {
    if (current == NULL || next == NULL) return;
    if (next->options == NULL) return;

    memcpy(current->header, next->header, MAX_STR_LEN);
    current->options = next->options;
    current->count = next->count;

    screen_clear();
    screen_draw(current);
}

void screen_clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

#endif // TINYCLI_H
