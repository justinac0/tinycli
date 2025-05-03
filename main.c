#include "tinycli.h"

#include <stdbool.h>

// GLOBAL STATE
Screen currentScreen;
Screen mainScreen;
Screen settingsScreen;

bool running = true;

// OPTION CALLBACKS
void print_something();
void main_menu_screen();
void settings_screen();
void exit_cli();

Option mainOptions[3] = {
    {
        .text = "Print Something",
        .callback = print_something
    },
    {
        .text = "Goto Settings Screen",
        .callback = settings_screen
    },
    {
        .text = "Exit",
        .callback = exit_cli
    },
};

Option settingsOptions[1] = {
    {
        .text = "Goto Main Menu Screen",
        .callback = main_menu_screen
    },
};

void print_something() {
    printf("something\n");
}

void main_menu_screen() {
    screen_switch(&currentScreen, &mainScreen);
}

void settings_screen() {
    screen_switch(&currentScreen, &settingsScreen);
}

void exit_cli() {
    printf("exiting cli...\n");
    running = false;
}

int main(void) {
    screen_create(&mainScreen, "Main Menu", mainOptions, 3);
    screen_create(&settingsScreen, "Settings", settingsOptions, 1);
    screen_switch(&currentScreen, &mainScreen);

    while (running) {
        screen_update(&currentScreen);
    }

    return 0;
}
