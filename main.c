/*
                            Sub-Marine
    -----------------------------------------------------------
        General	: Sub-Marin game
    -----------------------------------------------------------
        Input	:
    -----------------------------------------------------------
        Process : A game of two player submarin
    -----------------------------------------------------------
        Output	: Winner
    -----------------------------------------------------------
        Author	: Avishay Shriki 
        Date	: 06/11/24
    -----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ff printf
#define MIN_BORD_SIZE 0
#define MAX_BORD_SIZE 99


#define RESET "\033[0;0m"
#define RED "\033[0;31m"
#define B_RED "\033[0;41m"
#define BLACK "\033[0;30m"
#define GREEN "\033[0;32m"
#define B_GREEN "\033[0;42m"
#define WHITE "\033[0;37m"
#define B_WHITE "\033[0;47m"
#define BLUE "\033[0;34m"
#define B_BLUE "\033[0;44m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"

int show_submarine = 1, player = 0, count_of_hit[2] = {0, 0};

// massages
void print_welcome_message();
void place_instructions(int player);
void start_game_massage();

int get_bord_size();

void draw_line(int length);
void draw_spaces(int space);
void draw_bord(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size);
void draw_cell(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size, int line);
void draw_numbers(int border_size);
int chack_place_validetion(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size, int x, int y, char direc, int sub_size);

void update_bord(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int x, int y, char direc, int sub_size);
void update_hit_bord(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int x, int y);

void change_player();

void make_move(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size);
int is_shot_valide(int border_size, int x, int y);
int is_cell_shoted(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size, int x, int y);

void place_submarine(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size);

void clear_terminal();

// שחקן 2 זה ספרת העשרות שחקן 1 זה ספרת האחדות

int main()
{
    int border_size;
    print_welcome_message();
    border_size = get_bord_size();
    char bord[MAX_BORD_SIZE][MAX_BORD_SIZE] = {0};
    draw_bord(bord, border_size);
    place_submarine(bord, border_size);
    change_player();
    place_submarine(bord, border_size);
    start_game_massage();
    while (count_of_hit[0] < 35 && count_of_hit[1] < 35)
    {
        change_player();
        make_move(bord, border_size);
    }
    if (count_of_hit[0] == 35)
    {
        ff("Player 1 win");
    }
    else
    {
        ff("Player 2 win");
    }

    return 0;
}

void print_welcome_message()
{
    const int border_length = 50;
    char *title = "Welcome to Sub Marine game\n";
    char *description = "In this game two player are putting sub-marine \nin the ocean and the perpes of the game is to \ntake down all the sub-marine\n";

    draw_line(border_length);
    draw_spaces((border_length / 2 - strlen(title) / 2));
    printf(BLUE);
    printf("%s", title);
    printf(WHITE);
    printf("%s", description);
    printf("%10s", "The first player who take down all the sub-marine wins\n");
    draw_line(border_length);
}

void place_instructions(int player)
{
    clear_terminal();
    ff("\n");
    ff("\n");
    ff("\n");
    ff("This is player %d torn to put the sub-marine\n", player + 1);
    printf("entering submarine in this formar:" GREEN " x " RESET "," PURPLE " y" RESET "(like 28 , 4)\n");
    printf("when the first number is the row and the scond is the square in the row\n");
    printf("the location is the submarine head, if you place it horizontally it will place to the right\n");
    printf("if you place it vertically it will place towards down\n");
    printf("\n");
}

void clear_terminal()
{
    system("clear");
}

int get_bord_size()
{
    int flag = 0, border_size = MAX_BORD_SIZE;
    do
    {
        if (flag)
        {
            if (border_size > MAX_BORD_SIZE)
                printf("The bord size is to big \n");
            if (border_size < MIN_BORD_SIZE)
                printf("The bord size is to small \n");
        }
        printf("Enter bord size \n");
        scanf("%d", &border_size);
        flag = 1;
    } while (border_size > MAX_BORD_SIZE || border_size < MIN_BORD_SIZE);
    return border_size;
}

void draw_line(int length)
{
    ff("     ");
    for (size_t i = 0; i < length; i++)
    {
        printf("-");
    }
    printf("\n");
}

void draw_spaces(int space)
{
    for (size_t i = 0; i < space; i++)
    {
        printf(" ");
    }
}

void draw_cell(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size, int line)
{
    int i, cell_value;
    for (i = 0; i < border_size; i++)
    {
        if (player)
        {
            cell_value = bord[line][i] / 10;
        }
        else
        {
            cell_value = bord[line][i] % 10;
        }
        ff(BLUE);
        ff("|");
        switch (cell_value)
        {
        case 0:
            ff(B_BLUE);
            break;
        case 1:
            ff(B_WHITE);
            break;
        case 2:
            show_submarine ? ff(B_GREEN) : ff(B_BLUE);
            break;
        case 3:
            ff(B_RED);
            break;
        default:
            ff(PURPLE);
            break;
        }
        ff("    " RESET);
    }
    ff(BLUE);
    ff("|");
    ff("\n");
}

void draw_bord(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size)
{
    draw_numbers(border_size);
    int i;
    for (i = 0; i < border_size; i++)
    {
        ff(BLUE);
        draw_line(border_size * 5 + 1);
        ff(PURPLE);
        ff("%3d  ", i + 1);
        draw_cell(bord, border_size, i);
    }
    draw_line(border_size * 5 + 1);
    ff(RESET);
}

void draw_numbers(int border_size)
{
    int i;
    ff(YELLOW "     " RESET);
    for (i = 1; i <= border_size; i++)
    {
        ff(GREEN "%4d " RESET, i);
    }
    ff("\n");
}

void place_submarine(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size)
{
    int is_valide_place = 1;
    int sub_size, k, j, x, y;
    char direc = 'v', trash;
    clear_terminal();
    place_instructions(player);
    //  שיננו בפור מחמש לשלוש וגם בפור הפנימי משש לארבע
    for (sub_size = 1; sub_size <= 2; sub_size++)
    {
        for (j = 1; j <= 3 - sub_size; j++)
        {
            do
            {
                draw_bord(bord, border_size);
                if (sub_size > 1)
                {
                    do
                    {
                        if (direc != 'v' && direc != 'h')
                        {
                            ff("The direction is not ok please enter just 'v' or 'h' \n");
                        }
                        getchar();
                        ff("In which direction would you like to put the submarine(v-vertical , h-horizontal) \n");
                        scanf("%c", &direc);
                    } while (direc != 'v' && direc != 'h');
                }
                do
                {
                    if (!is_valide_place)
                    {
                        ff("The coordinates that you put is not OK please check the instructions\n");
                    }
                    ff("Please enter the place of the %d submarine at size of %d square(you have %d more to place)\n", j, sub_size, 6 - sub_size - j);
                    scanf("%d%c%d", &x, &trash, &y);
                    getchar();
                    x--;
                    y--;
                } while (x > border_size || y > border_size);
                clear_terminal();
                is_valide_place = chack_place_validetion(bord, border_size, x, y, direc, sub_size);
            } while (!is_valide_place);
            update_bord(bord, x, y, direc, sub_size);
        }
    }
}

int chack_place_validetion(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size, int x, int y, char direc, int sub_size)
{
    int is_valide_place = 1, i, j;
    if (direc == 'v')
    {
        if (y + sub_size > border_size)
        {
            is_valide_place = 0;
        }
        else
        {
            for (i = x - 1; i <= x + 1; i++)
            {
                for (j = y - 1; j <= y + sub_size; j++)
                {
                    if (i >= 0 && j >= 0 && i < border_size && j < border_size)
                    {
                        if (player)
                        {
                            if (bord[j][i] / 10 == 2)
                            {
                                is_valide_place = 0;
                            }
                        }
                        else
                        {
                            if (bord[j][i] % 10 == 2)
                            {
                                is_valide_place = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (x + sub_size > border_size)
        {
            is_valide_place = 0;
        }
        else
        {
            for (i = x - 1; i <= x + sub_size; i++)
            {
                for (j = y - 1; j < y + 1; j++)
                {
                    if (i >= 0 && j >= 0 && i < border_size && j < border_size)
                    {
                        if (player)
                        {
                            if (bord[j][i] / 10 == 2)
                            {
                                is_valide_place = 0;
                            }
                        }
                        else
                        {
                            if (bord[j][i] % 10 == 2)
                            {
                                is_valide_place = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return is_valide_place;
}

void update_bord(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int x, int y, char direc, int sub_size)
{
    int i, value = 2;
    if (player)
    {
        value = 20;
    }
    if (direc == 'v')
    {
        for (i = y; i < y + sub_size; i++)
        {
            bord[i][x] += value;
        }
    }
    else
    {
        for (i = x; i < x + sub_size; i++)
        {
            bord[y][i] += value;
        }
    }
}

void change_player()
{
    player = !player;
}

void start_game_massage()
{
    clear_terminal();
    ff("\n");
    ff("\n");
    ff("Now you will start the game\n");
    ff("Every torn you can make one move \n");
    ff("You can chose one coordination to shot a missile and try to hit a sub-marine\n");
}

void make_move(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size)
{
    clear_terminal();
    int show_bord = 0, valid_shot = 1, shoted_cell = 1;
    show_submarine = 1;
    int x, y;
    char trash;
    ff("This is player %d torn to shot a missile\n", player + 1);
    ff("IF you want to see your bord enter 1 else enter 2\n");
    scanf("%d", &show_bord);
    if (show_bord == 1)
    {
        draw_bord(bord, border_size);
    }
    show_submarine = 0;
    getchar();
    ff("press enter to continu\n");
    getchar();
    clear_terminal();
    change_player();
    draw_bord(bord, border_size);
    ff("The place that you already shot will be in color white or red(red if you hit a sub-marine and white if you hit the water) \n");
    do
    {
        if (!shoted_cell)
        {
            ff("The cell thet you chose is alredy been shot\n");
        }
        ff("Please chose a coordinates where to shot (" GREEN "x" RESET "," PURPLE "y" RESET ")\n");
        scanf("%d%c%d", &x, &trash, &y);
        x--;
        y--;
        valid_shot = is_shot_valide(border_size, x, y);
        if (!valid_shot)
        {
            ff("The coordination that you enter is iligal\n");
        }
        else
        {
            shoted_cell = is_cell_shoted(bord, border_size, x, y);
        }
    } while (!valid_shot || !shoted_cell);
    update_hit_bord(bord, x, y);
    change_player();
}

int is_cell_shoted(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int border_size, int x, int y)
{
    int shoted_cell = 1;
    if (player)
    {
        if (bord[y][x] / 10 == 1 || bord[y][x] / 10 == 3)
        {
            shoted_cell = 0;
        }
    }
    else
    {

        if (bord[y][x] % 10 == 1 || bord[y][x] % 10 == 3)
        {
            shoted_cell = 0;
        }
    }
    return shoted_cell;
}

int is_shot_valide(int border_size, int x, int y)
{
    int is_valide = 1, i, j;
    if (x >= border_size || y >= border_size)
    {
        is_valide = 0;
    }

    return is_valide;
}

void update_hit_bord(char bord[MAX_BORD_SIZE][MAX_BORD_SIZE], int x, int y)
{
    if (player)
    {
        bord[y][x] += 10;
        if (bord[y][x] / 10 == 3)
        {
            ff("You hit the sub-marine\n");
            count_of_hit[!player]++;
        }
        else
        {
            ff("You hit the water\n");
        }
    }
    else
    {
        bord[y][x] += 1;
        if (bord[y][x] % 10 == 3)
        {
            ff("You hit the sub-marine\n");
            count_of_hit[!player]++;
        }
        else
        {
            ff("You hit the water\n");
        }
    }
    ff("Press enter to continue");
    getchar();
}
