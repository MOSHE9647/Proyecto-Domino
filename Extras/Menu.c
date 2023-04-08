#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios old, new;

/* Initialize new terminal i/o settings */
void init_termios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void reset_termios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo)
{
  char ch;
  init_termios(echo);
  ch = getchar();
  reset_termios();
  return ch;
}

/* Read 1 character without echo */
char getch()
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche()
{
  return getch_(1);
}

typedef struct {
    char* label;
    int is_disabled;
} MenuItem;

typedef struct {
    MenuItem* items;
    int length;
    int selected_index;
} Menu;

Menu create_menu(MenuItem* items, int length)
{
    Menu menu = { items, length, 0 };
    return menu;
}

void print_menu(Menu* menu)
{
    int i;
    printf("--------------------\n");
    for (i = 0; i < menu->length; i++) {
        printf("%s%s\n", (menu->selected_index == i) ? "> " : "", menu->items[i].label);
    }
    printf("--------------------\n");
}

void navigate_menu(Menu* menu, char input)
{
    switch (input) {
        case 'w':
            if (menu->selected_index > 0) {
                menu->selected_index--;
            }
            break;
        case 's':
            if (menu->selected_index < menu->length - 1) {
                menu->selected_index++;
            }
            break;
    }
}

int main()
{
    MenuItem items[] = {
        { "Option 1", 0 },
        { "Option 2", 0 },
        { "Option 3", 1 },
        { "Option 4", 0 }
    };
    int length = sizeof(items) / sizeof(items[0]);
    Menu menu = create_menu(items, length);

    char input;
    while (1) {
        system("clear");
        print_menu(&menu);
        input = getche();
        navigate_menu(&menu, input);
    }
}