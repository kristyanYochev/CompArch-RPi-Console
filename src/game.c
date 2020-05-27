#include <game.h>
#include <string.h>
#include <graphics.h>
#include <controller.h>
#include <delay.h>

#define MENU_ITEMS_COUNT 2

typedef struct {
    char content[256];
    unsigned int x;
    unsigned int y;
} menu_item_t;

static color_t BLACK = {
    .color_array = {0x00, 0x00, 0x00, 0x00}
};

static color_t WHITE = {
    .color_array = {0xFF, 0xFF, 0xFF, 0x00}
};


static void init_menu_item(menu_item_t * item, char * content, unsigned int x, unsigned int y);
static void show_menu_item_active(menu_item_t * item);
static void show_menu_item_inactive(menu_item_t * item);

static void main_menu()
{
    menu_item_t items[MENU_ITEMS_COUNT];

    init_menu_item(&items[0], "New Game", 480, 350);
    init_menu_item(&items[1], "Exit", 480, 380);
    int selected_menu_item = 0;

    controller_input_t input;
    controller_input_t last_input;
    last_input.raw_data = 0x00;

    while (1)
    {
        limit_rate(30);
        input = get_controller_state(0);
        if (input.input_data.down && !last_input.input_data.down)
        {
            selected_menu_item = (selected_menu_item + 1) % MENU_ITEMS_COUNT;
        }

        if (input.input_data.up && !last_input.input_data.up)
        {
            selected_menu_item = (selected_menu_item - 1) % MENU_ITEMS_COUNT;
        }

        last_input = input;

        clear_screen();
        for (int i = 0; i < MENU_ITEMS_COUNT; i++)
        {
            if (i == selected_menu_item)
            {
                show_menu_item_active(&items[i]);
            }
            else
            {
                show_menu_item_inactive(&items[i]);
            }
        }
        show_screen();
    }
}

void start_game()
{
    main_menu();
}

static void init_menu_item(menu_item_t * item, char * content, unsigned int x, unsigned int y)
{
    strcpy(item->content, content);
    item->x = x;
    item->y = y;
}

static void show_menu_item_active(menu_item_t * item)
{
    draw_text(item->x, item->y, item->content, BLACK, WHITE);
}

static void show_menu_item_inactive(menu_item_t * item)
{
    draw_text(item->x, item->y, item->content, WHITE, BLACK);
}
