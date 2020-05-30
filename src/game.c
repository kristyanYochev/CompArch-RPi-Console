#include <game.h>
#include <string.h>
#include <graphics.h>
#include <controller.h>
#include <delay.h>
#include <rand.h>

char colliding(
    int x1, int y1, int width1, int height1,
    int x2, int y2, int width2, int height2
);

#pragma region colors
static const color_t BLACK = {
    .color_array = {0x00, 0x00, 0x00, 0x00}
};

static const color_t WHITE = {
    .color_array = {0xFF, 0xFF, 0xFF, 0x00}
};

static const color_t RED = {
    .color_array = {0xFF, 0x00, 0x00, 0x00}
};

static const color_t PLAYER_COLOR = {
    .color_array = {0x00, 0x00, 0xFF, 0x00}
};
#pragma endregion

#pragma region menu_item_declaration
#define MENU_ITEMS_COUNT 2

typedef struct {
    char content[256];
    unsigned int x;
    unsigned int y;
} menu_item_t;

static void init_menu_item(menu_item_t * item, char * content, unsigned int x, unsigned int y);
static void show_menu_item_active(menu_item_t * item);
static void show_menu_item_inactive(menu_item_t * item);
static void clear_menu_item(menu_item_t * item);
#pragma endregion

#pragma region game_object_declaration
typedef struct {
    int x;
    int y;
    int prev_x;
    int prev_y;
    int width;
    int height;
    int speed_x;
    int speed_y;
    color_t color;
} game_object_t;

static void init_game_object(game_object_t * object, int x, int y, int width, int height, color_t color);
static void update_game_object(game_object_t * object);
static void set_game_object_position(game_object_t * object, int x, int y);
static void draw_game_object(game_object_t * object);

#pragma endregion

static void main_menu();
static void game();

void start_game()
{
    main_menu();
}

#pragma region game_scenes
static void main_menu()
{
    menu_item_t items[MENU_ITEMS_COUNT];

    init_menu_item(&items[0], "New Game", 480, 350);
    init_menu_item(&items[1], "Exit", 480, 380);
    int selected_menu_item = 0;

    controller_input_t input;
    controller_input_t last_input;
    last_input.raw_data = 0x00;

    char exits = 0;

    while (!exits)
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

        if (input.input_data.select)
        {
            exits = 1;
        }

        last_input = input;

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

    for (int i = 0; i < MENU_ITEMS_COUNT; i++)
    {
        clear_menu_item(&items[i]);
    }

    switch (selected_menu_item)
    {
        case 0:
            game();
            break;
        case 1:
            return;
        default:
            break;
    }
}

typedef struct {
    int x;
    int y;
    int width;
    int height;
    char hit;
} brick_t;

static void init_brick(brick_t * brick, int x, int y, int width, int height)
{
    brick->x = x;
    brick->y = y;
    brick->width = width;
    brick->height = height;
    brick->hit = 0;
}

static void draw_brick(brick_t * brick)
{
    draw_rectangle(brick->x, brick->y, brick->width, brick->height, ((brick->hit) ? BLACK : RED));
}

static void game()
{
    game_object_t player;
    init_game_object(&player, 480, 650, 150, 21, PLAYER_COLOR);

    game_object_t ball;
    init_game_object(&ball, 525, 640, 10, 10, WHITE);

#define BRICK_COUNT 40

    brick_t bricks[BRICK_COUNT];

    for (int i = 0; i < BRICK_COUNT; i++)
    {
        init_brick(&bricks[i],
            16 + (i % 10) * ((1024 - 32) / 10), 
            32 + (i / 10) * 30,
            ((1024 - 32) / 10) - 20,
            20
        );
    }

    char ball_released = 0;
    char exits = 0;

    controller_input_t input;

    ball.speed_x = 20;

    rand_init();

    for (int i = 0; i < BRICK_COUNT; i++)
    {
        draw_brick(&bricks[i]);
    }

    while (!exits)
    {
        limit_rate(30);
        input = get_controller_state(0);

        if (input.input_data.left)
        {
            player.speed_x = -20;
            if (!ball_released)
            {
                ball.speed_x = -20;
            }
        }
        else if (input.input_data.right)
        {
            player.speed_x = 20;
            if (!ball_released)
            {
                ball.speed_x = 20;
            }
        }
        else
        {
            player.speed_x = 0;
            if (!ball_released)
            {
                ball.speed_x = 0;
            }
        }

        if (input.input_data.a && !ball_released)
        {
            ball_released = 1;
            ball.speed_x = rand(-10, 10);
            ball.speed_y = rand(-10, -5);
        }

        if (ball.x <= 0 || ball.x + ball.width >= get_screen_width())
        {
            ball.speed_x = -ball.speed_x;
        }

        if (ball.y <= 0)
        {
            ball.speed_y = -ball.speed_y;
        }

        if (colliding(
            ball.x, ball.y, ball.width, ball.height,
            player.x, player.y, player.width, player.height
        ))
        {
            ball.speed_y = -ball.speed_y;
            ball.speed_x = 50 * (ball.x - player.x - player.width/2) / player.width;
        }

        for (int i = 0; i < BRICK_COUNT; i++)
        {
            if (bricks[i].hit) continue;

            if (colliding(
                ball.x, ball.y, ball.width, ball.height,
                bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height
            ))
            {
                if (bricks[i].x < ball.x + ball.width / 2 &&
                    ball.x + ball.width / 2 < bricks[i].x + bricks[i].width)
                {
                    bricks[i].hit = 1;
                    draw_brick(&bricks[i]);
                    ball.speed_y = -ball.speed_y;
                }
                else if (bricks[i].y < ball.y + ball.height / 2 &&
                    ball.y + ball.height / 2 < bricks[i].y + bricks[i].height)
                {
                    bricks[i].hit = 1;
                    draw_brick(&bricks[i]);
                    ball.speed_x = -ball.speed_x;
                }
                else
                {
                    bricks[i].hit = 1;
                    draw_brick(&bricks[i]);
                    ball.speed_x = -ball.speed_x;
                    ball.speed_y = -ball.speed_y;
                }
            }
        }

        update_game_object(&player);
        update_game_object(&ball);

        draw_game_object(&player);
        draw_game_object(&ball);

        draw_rectangle(0, 0, 1, get_screen_height(), WHITE);
        draw_rectangle(get_screen_width() - 1, 0, 1, get_screen_height(), WHITE);
        // show_screen();
    }
}
#pragma endregion

#pragma region menu_item_implementation
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

static void clear_menu_item(menu_item_t * item)
{
    clear_text(item->x, item->y, item->content, BLACK);
}
#pragma endregion

#pragma region game_object_implementation
static void init_game_object(game_object_t * object, int x, int y, int width, int height, color_t color)
{
    object->x = x;
    object->y = y;
    object->prev_x = x;
    object->prev_y = y;
    object->width = width;
    object->height = height;
    object->speed_x = 0;
    object->speed_y = 0;
    object->color = color;
}

static void draw_game_object(game_object_t * object)
{
    draw_rectangle(object->prev_x, object->prev_y, object->width, object->height, BLACK);
    delay_us_st(object->height + 20);
    draw_rectangle(object->x, object->y, object->width, object->height, object->color);
}

static void update_game_object(game_object_t * object)
{
    set_game_object_position(object, object->x + object->speed_x, object->y + object->speed_y);
}

static void set_game_object_position(game_object_t * object, int x, int y)
{
    if (x < 0)
    {
        x = 0;
    }

    if (x + object->width > get_screen_width())
    {
        x = get_screen_width() - object->width;
    }

    if (y < 0)
    {
        y = 0;
    }

    if (y + object->height > get_screen_height())
    {
        y = get_screen_height() - object->height;
    }

    object->prev_x = object->x;
    object->prev_y = object->y;
    object->x = x;
    object->y = y;
}
#pragma endregion

char colliding(
    int x1, int y1, int width1, int height1,
    int x2, int y2, int width2, int height2
)
{
    if (x1 >= x2 + width2 || x2 >= x1 + width1) return 0;

    if (y1 >= y2 + height2 || y2 >= y1 + height1) return 0;

    return 1;
}