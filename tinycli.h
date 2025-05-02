#ifndef TINYCLI_H
#define TINYCLI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_STR_LEN 64 
#define MAX_OPTION_COUNT 32

typedef void (*OptionCB)(void);

typedef struct {
    uint8_t text[MAX_STR_LEN+1];
    OptionCB callback; // function called when option is selected
} Option;

typedef struct {
    Option *options;
    uint8_t count;
} Screen;

void screen_create(Screen* screen, Option *options, uint8_t count);
void screen_draw(Screen *screen);
uint8_t screen_handle_input(Screen *screen);
void screen_switch(Screen *current, Screen *next);
void screen_clear();

void screen_create(Screen* screen, Option *options, uint8_t count) {
    if (screen == NULL) {} // bad
    if (options == NULL) {} // bad

    screen->options = options;
    screen->count = count;

    if (screen->count > MAX_OPTION_COUNT) {} // bad
}

void screen_draw(Screen *screen) {
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
    scanf("%d", &val);
    if (val <= 0 || val > screen->count) {
        printf("input number not valid... retry...\n");
        return 0;
    }

    return (uint8_t)val;
}

void screen_switch(Screen *current, Screen *next) {
    if (current == NULL || next == NULL) return;

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
