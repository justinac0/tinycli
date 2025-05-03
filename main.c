#include "tinycli.h"

Screen currentScreen;
Screen foodScreen;
Screen pizzaScreen;

void default_option_callback();
void pizza();

Option FoodOptions[3] = {
    {
        .text = "Pizza",
        .callback = pizza
    },
    {
        .text = "Salad",
        .callback = default_option_callback
    },
    {
        .text = "Pretzels",
        .callback = default_option_callback
    },
};

Option PizzaOptions[1] = {
    {
        .text = "Pepperoni",
        .callback = default_option_callback
    },
};

void default_option_callback() {
    screen_switch(&currentScreen, &foodScreen);
}

void pizza() {
    screen_switch(&currentScreen, &pizzaScreen);
}

int main(void) {
    screen_create(&foodScreen, "Food Options", FoodOptions, 3);
    screen_create(&pizzaScreen, "Pizza Options", PizzaOptions, 1);
    screen_switch(&currentScreen, &foodScreen);

    while (1) {
        uint8_t selection = screen_handle_input(&currentScreen);
        if (selection > 0) {
            currentScreen.options[selection-1].callback();
        }
    }

    return 0;
}
