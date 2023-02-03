#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

enum Player {RED,BLUE,YELLOW,GREEN};

void Draw_Land_Boarder(int land);
void Primary_Rand(int );
int land_position_x(int i);
int land_position_y(int i);
void soldier_display(void);
void wrong_input(void);
int whose_turn_is_it(int );
void primary_whose_turn_is_it(int);
int check_land_is_correct(int ,int );
void soldier_counter(int*, int* , int* , int* );
void soldier_transition(int , int );
void Risk(int , int );
int deffend_member_number(int );
int attack_member_number(int );
int which_land_is_near(int , int );
void turn1(void);


ALLEGRO_FONT *font1;
ALLEGRO_SAMPLE *sample;

int Land_quantity[29];
int Land_player[29];
int primary_numbers;
int Turn_counter=0;


int main()
{
    int width = 1200;
    int height = 800;
    int fps = 30;
    int x,y;
    bool done = true;
    int n=1;
    int land=0;
    int i,j;
    int v;
    int turn;
    int red,green,blue,yellow;
    int red_capacity,green_capacity,yellow_capacity,blue_capacity;
    int key=0;
    int DoIt=1;
    int can_I_write_turn=0;
    int round=0;
    int can_I_count=1;
    int land1,land2;
    int situation=1;
    int ready_for_next_round=0;
    int R=1,B=1,Y=1,G=1;
    int flag=0;



    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);




    ALLEGRO_TIMER *timer = al_create_timer(1.0/fps);
    font1 = al_load_ttf_font("Oswald-Regular.ttf",24,0);
    ALLEGRO_FONT *font2 = al_create_builtin_font();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *display = al_create_display(width,height);
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *bitmap1 = al_load_bitmap("true.jpg");
    ALLEGRO_BITMAP *bitmap2 = al_load_bitmap("10.jpg");
    ALLEGRO_BITMAP *bitmap3 = al_load_bitmap("11.jpg");
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_SAMPLE *test_sample = al_load_sample("AnyConv.com__Welcome.opus");
    sample = al_load_sample("click.mp3");

    al_register_event_source(queue , al_get_keyboard_event_source());
    al_register_event_source(queue , al_get_display_event_source(display));
    al_register_event_source(queue , al_get_mouse_event_source());
    al_register_event_source(queue , al_get_timer_event_source(timer));


    for (i=0 ; i<29 ; i++)     // this place works as the soldiers without flags.
        Land_quantity[i]++;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
    al_start_timer(timer);
    al_play_sample(test_sample,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);

    while (done)                // the menu
    {

        al_wait_for_event(queue , &event);
        al_draw_bitmap(bitmap1 ,0,0,0);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            x = event.mouse.x;
            y = event.mouse.y;
            al_get_mouse_state (&mouse_state);

            if (mouse_state.buttons == 1 && x>=752 && x<=877 && y>=200 && y<=435)
            {
                primary_numbers = 4;
                al_play_sample(sample,1,0,2,ALLEGRO_PLAYMODE_ONCE,NULL);
                al_draw_rectangle(752,200,877,435, al_map_rgb(0,0,0),5);
                al_flip_display();
                al_rest(0.2);
                done = false;
            }
            else if (mouse_state.buttons == 1 && x>=894 && x<=1019 && y>=200 && y<=435)
            {
                primary_numbers = 3;
                al_play_sample(sample,1,0,2,ALLEGRO_PLAYMODE_ONCE,NULL);
                al_draw_rectangle(894,200,1019,435, al_map_rgb(0,0,0),5);
                al_flip_display();
                al_rest(0.2);
                done = false;
            }
            else if (mouse_state.buttons == 1 && x>=1035 && x<=1160 && y>=200 && y<=435)
            {
                primary_numbers = 2;
                al_play_sample(sample,1,0,2,ALLEGRO_PLAYMODE_ONCE,NULL);
                al_draw_rectangle(1035,200,1160,435, al_map_rgb(0,0,0),5);
                al_flip_display();
                al_rest(0.2);
                done = false;
            }

        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            exit(1);
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            al_flip_display();
        }
    }
    al_destroy_bitmap(bitmap1);
    al_destroy_sample(test_sample);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Primary_Rand(primary_numbers);
    done = true;
    al_start_timer(timer);
    al_draw_bitmap(bitmap2, 0, 0, 0);  // has to exist;
    soldier_display();
    turn=whose_turn_is_it(land);
    al_flip_display();                                    // has to exist;
    v=1;

    //777777777777777777777777777777777777777777

    printf("%d\n",primary_numbers);
    if (primary_numbers==2)   // the use of capacity is to know how much soldiers we need at the beginning.
    {
        red_capacity = 30;
        blue_capacity = 30;
        red = 15;
        blue = 14; // and it is blue's turn;
    }
    else if (primary_numbers==3)
    {
        red_capacity =25;
        blue_capacity =25;
        yellow_capacity =25;
        red = 10;
        blue =10;
        yellow = 9; // and it is yellow's turn
    }
    else if (primary_numbers==4)
    {
        red_capacity =20;
        blue_capacity =20;
        yellow_capacity =20;
        green_capacity =20;
        red = 8;
        blue = 7; // and it is blue's turn
        yellow =7;
        green =7;
    }

    //777777777777777777777777777777777777777777



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"Put your soldiers at one of your land.");
    al_flip_display(); // has to exist to be one step ahead.
    while (1)  // at this loop players put their soldiers for the first time.
    {
        al_wait_for_event(queue,&event);
        al_get_mouse_state(&mouse_state);

        if (event.type == ALLEGRO_EVENT_TIMER && v==1)
        {
            v=0;
            al_draw_bitmap(bitmap2, 0, 0, 0);
            al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"Put your soldiers at one of your land.");
        }
        DoIt=1;

        //////////////////////////////////////////////////////////////  works as land selection
        while (DoIt)
        {
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                x = event.mouse.x;
                y = event.mouse.y;
                al_get_mouse_state(&mouse_state);

                if (mouse_state.buttons == 1 && x >= 35 && x <= 215)
                {
                    if (y >= 35 && y <= 110)
                        land = 0;
                    else if (y >= 120 && y <= 195)
                        land = 1;
                    else if (y >= 205 && y <= 280)
                        land = 2;
                    else if (y >= 290 && y <= 365)
                        land = 3;
                    else if (y >= 375 && y <= 450)
                        land = 4;
                    else if (y >= 460 && y <= 535)
                        land = 5;
                    else
                    {
                        al_flip_display();
                        land = -1;
                    }
                }
                else if (mouse_state.buttons == 1 && x >= 225 && x <= 405)
                {
                    if (y >= 35 && y <= 110)
                        land = 6;
                    else if (y >= 120 && y <= 195)
                        land = 7;
                    else if (y >= 460 && y <= 535)
                        land = 8;
                    else
                    {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 415 && x <= 595)
                {
                    if (y >= 35 && y <= 110)
                        land = 9;
                    else if (y >= 120 && y <= 195)
                        land = 10;
                    else if (y >= 205 && y <= 280)
                        land = 11;
                    else if (y >= 375 && y <= 450)
                        land = 12;
                    else if (y >= 460 && y <= 535)
                        land = 13;
                    else if (y >= 545 && y <= 620)
                        land = 14;
                    else
                    {
                        al_flip_display();
                        land = -1;
                    }
                }
                else if (mouse_state.buttons == 1 && x >= 605 && x <= 785)
                {
                    if (y >= 35 && y <= 110)
                        land = 15;
                    else if (y >= 120 && y <= 195)
                        land = 16;
                    else if (y >= 205 && y <= 280)
                        land = 17;
                    else if (y >= 290 && y <= 365)
                        land = 18;
                    else if (y >= 375 && y <= 450)
                        land = 19;
                    else if (y >= 460 && y <= 535)
                        land = 20;
                    else
                    {
                        al_flip_display();
                        land = -1;
                    }
                }
                else if (mouse_state.buttons == 1 && x >= 795 && x <= 975)
                {
                    if (y >= 35 && y <= 110)
                        land = 21;
                    else if (y >= 120 && y <= 195)
                        land = 22;
                    else if (y >= 205 && y <= 280)
                        land = 23;
                    else if (y >= 290 && y <= 365)
                        land = 24;
                    else
                    {
                        al_flip_display();
                        land = -1;
                    }
                }
                else if (mouse_state.buttons == 1 && x >= 985 && x <= 1165)
                {
                    if (y >= 35 && y <= 110)
                        land = 25;
                    else if (y >= 120 && y <= 195)
                        land = 26;
                    else if (y >= 205 && y <= 280)
                        land = 27;
                    else if (y >= 290 && y <= 365)
                        land = 28;
                    else
                    {
                        al_flip_display();
                        land = -1;
                    }
                }

                if (land!=-1)
                {
                    if (check_land_is_correct(land,turn)==1)
                    {
                        turn = whose_turn_is_it(land);

                        Land_quantity[land]++;

                        if (Land_player[land]==RED)
                            red++;
                        else if (Land_player[land]==BLUE)
                            blue++;
                        else if (Land_player[land]==YELLOW)
                            yellow++;
                        else if (Land_player[land]==GREEN)
                            green++;
                    }
                    else
                    {
                        primary_whose_turn_is_it(turn);
                        al_flip_display();
                    }
                }

                Draw_Land_Boarder(land);
                soldier_display();
                v = 1;

                if (land==-1)
                {
                    primary_whose_turn_is_it(turn);
                    al_flip_display();
                }
            }


            DoIt=0;

        }
        //////////////////////////////////////////////////////////////  works as land selection

        //9999999999999999999999999999999999999999999999999999999999999999999999999999999999999
        if (primary_numbers==2)   // this part ends the loop
        {
            if (red==red_capacity && blue==blue_capacity)
                break;
        }
        else if (primary_numbers==3)
        {
            if (red==red_capacity && blue==blue_capacity && yellow==yellow_capacity)
                break;
        }
        else if (primary_numbers==4)
        {
            if (red==red_capacity && blue==blue_capacity && yellow==yellow_capacity && green==green_capacity)
                break;
        }
        //99999999999999999999999999999999999999999999999999999999999999999999999999999999999999


        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(1);


        //printf("%d",turn);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////


    al_draw_bitmap(bitmap2,0,0,0);
    soldier_display();
    primary_whose_turn_is_it(turn);
    Draw_Land_Boarder(land);
    al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"Put your BONUS soldiers at one of your land.");
    // those up are used to be one step ahead.
    al_flip_display();
    round=0;
    can_I_count=1;

    //************************************************************************************************************
    while (1) // the game:
    {
        al_wait_for_event(queue,&event);
        al_get_mouse_state(&mouse_state);


        if (event.type == ALLEGRO_EVENT_TIMER && v == 1)
        {
            v = 0;
            if (round==1)  // // it is late for one click anywhere
            {
                al_draw_bitmap(bitmap3, 0, 0, 0);
                al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"You can either ATTACK or MOVE your soldier."
                                                                     " click next player when you are done.");
            }
            else if (round==0)   // it is late for one click anywhere
            {
                al_draw_bitmap(bitmap2, 0, 0, 0);
                al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"Put your BONUS soldiers at one of your land.");
            }

            if (can_I_write_turn!=1)
                primary_whose_turn_is_it(turn); ////// problem with next player. (solved looks like to be)
            else
                can_I_write_turn=0;

            //printf("*\n");
            //printf("situation=%d\n", situation);
            //printf("red=%d,blue=%d,yellow=%d,green=%d,round=%d,turn=%d,turn_counter=%d", red, blue, yellow, green, round,turn,Turn_counter);
            //printf("\n red_capacity=%d,blue_capasicy=%d,yellow_capasity=%d,green_capasity=%d",red_capacity,blue_capacity,yellow_capacity,green_capacity);

            /*for (i=0 ; i<29 ; i++)
            {
                if (land[i]==RED)

            }*/

        }

        if (ready_for_next_round==primary_numbers)
        {
            round=0;
            al_draw_bitmap(bitmap2, 0, 0, 0);
            al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"Put your BONUS soldiers at one of your land.");
            ready_for_next_round=0;
            can_I_count=1;
        }

        if (can_I_count == 1)
        {
            soldier_counter(&red_capacity,&blue_capacity,&yellow_capacity,&green_capacity);
            can_I_count=0;
            R=1;
            B=1;
            Y=1;
            G=1;
        }

        if (round == 0)
        {

            //////////////////////////////////////////////////////////////  works as land selection
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                x = event.mouse.x;
                y = event.mouse.y;
                al_get_mouse_state(&mouse_state);

                if (mouse_state.buttons == 1 && x >= 35 && x <= 215)
                {
                    if (y >= 35 && y <= 110)
                        land = 0;

                    else if (y >= 120 && y <= 195) {
                        land = 1;
                    } else if (y >= 205 && y <= 280) {
                        land = 2;
                    } else if (y >= 290 && y <= 365) {
                        land = 3;
                    } else if (y >= 375 && y <= 450) {
                        land = 4;
                    } else if (y >= 460 && y <= 535) {
                        land = 5;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 225 && x <= 405)
                {
                    if (y >= 35 && y <= 110)
                        land = 6;
                    else if (y >= 120 && y <= 195)
                        land = 7;
                    else if (y >= 460 && y <= 535)
                        land = 8;
                    else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 415 && x <= 595)
                {
                    if (y >= 35 && y <= 110) {
                        land = 9;
                    } else if (y >= 120 && y <= 195) {
                        land = 10;
                    } else if (y >= 205 && y <= 280) {
                        land = 11;
                    } else if (y >= 375 && y <= 450) {
                        land = 12;
                    } else if (y >= 460 && y <= 535) {
                        land = 13;
                    } else if (y >= 545 && y <= 620) {
                        land = 14;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 605 && x <= 785)
                {
                    if (y >= 35 && y <= 110) {
                        land = 15;
                    } else if (y >= 120 && y <= 195) {
                        land = 16;
                    } else if (y >= 205 && y <= 280) {
                        land = 17;
                    } else if (y >= 290 && y <= 365) {
                        land = 18;
                    } else if (y >= 375 && y <= 450) {
                        land = 19;
                    } else if (y >= 460 && y <= 535) {
                        land = 20;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 795 && x <= 975)
                {
                    if (y >= 35 && y <= 110) {
                        land = 21;
                    } else if (y >= 120 && y <= 195) {
                        land = 22;
                    } else if (y >= 205 && y <= 280) {
                        land = 23;
                    } else if (y >= 290 && y <= 365) {
                        land = 24;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 985 && x <= 1165)
                {
                    if (y >= 35 && y <= 110) {
                        land = 25;
                    } else if (y >= 120 && y <= 195) {
                        land = 26;
                    } else if (y >= 205 && y <= 280) {
                        land = 27;
                    } else if (y >= 290 && y <= 365) {
                        land = 28;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                if (land!=-1)
                {
                    if (check_land_is_correct(land,turn)==1)
                    {
                        Land_quantity[land]++;
                        primary_whose_turn_is_it(turn);
                        al_flip_display();

                        if (Land_player[land]==RED)
                            red++;
                        else if (Land_player[land]==BLUE)
                            blue++;
                        else if (Land_player[land]==YELLOW)
                            yellow++;
                        else if (Land_player[land]==GREEN)
                            green++;
                    }

                }


                Draw_Land_Boarder(land);
                soldier_display();
                v = 1;
            }
            //////////////////////////////////////////////////////////////  works as land selection

        }


        if (turn==RED && red>=red_capacity && R==1)
        {
            round=1;
            R=0;
            al_flip_display();
            al_draw_bitmap(bitmap3, 0, 0, 0);
            al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"You can either ATTACK or MOVE your soldier."
                                                                 " click next player when you are done.");
            primary_whose_turn_is_it(turn);
            al_flip_display();
            situation=0;  // subhan allah : works properly.

        }
        else if (turn==BLUE && blue>=blue_capacity && B==1)
        {
            round = 1;
            B = 0;
            al_flip_display();
            al_draw_bitmap(bitmap3, 0, 0, 0);
            al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"You can either ATTACK or MOVE your soldier."
                                                                 " click next player when you are done.");
            primary_whose_turn_is_it(turn);
            al_flip_display();
            situation=0;  // subhan allah : works properly.
        }
        else if (turn==YELLOW && yellow>=yellow_capacity && Y==1)
        {
            round=1;
            Y=0;
            al_draw_bitmap(bitmap3, 0, 0, 0);
            al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"You can either ATTACK or MOVE your soldier."
                                                                 " click next player when you are done.");
            primary_whose_turn_is_it(turn);
            al_flip_display();
            situation=0; // subhan allah : works properly.
        }
        else if (turn==GREEN && green>=green_capacity && G==1)
        {
            round = 1;
            G = 0;
            al_draw_bitmap(bitmap3, 0, 0, 0);
            al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 655, 0, "You can either ATTACK or MOVE your soldier."
                                                                       " click next player when you are done.");
            primary_whose_turn_is_it(turn);
            al_flip_display();
            situation = 0;  // subhan allah : works properly.
        }


        if (round==1)
        {

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                x = event.mouse.x;
                y = event.mouse.y;
                al_get_mouse_state(&mouse_state);

                if (mouse_state.buttons == 1 && x >= 35 && x <= 215) {
                    if (y >= 35 && y <= 110)
                        land = 0;
                    else if (y >= 120 && y <= 195) {
                        land = 1;
                    } else if (y >= 205 && y <= 280) {
                        land = 2;
                    } else if (y >= 290 && y <= 365) {
                        land = 3;
                    } else if (y >= 375 && y <= 450) {
                        land = 4;
                    } else if (y >= 460 && y <= 535) {
                        land = 5;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 225 && x <= 405) {
                    if (y >= 35 && y <= 110)
                        land = 6;
                    else if (y >= 120 && y <= 195)
                        land = 7;
                    else if (y >= 460 && y <= 535)
                        land = 8;
                    else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 415 && x <= 595) {
                    if (y >= 35 && y <= 110) {
                        land = 9;
                    } else if (y >= 120 && y <= 195) {
                        land = 10;
                    } else if (y >= 205 && y <= 280) {
                        land = 11;
                    } else if (y >= 375 && y <= 450) {
                        land = 12;
                    } else if (y >= 460 && y <= 535) {
                        land = 13;
                    } else if (y >= 545 && y <= 620) {
                        land = 14;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 605 && x <= 785) {
                    if (y >= 35 && y <= 110) {
                        land = 15;
                    } else if (y >= 120 && y <= 195) {
                        land = 16;
                    } else if (y >= 205 && y <= 280) {
                        land = 17;
                    } else if (y >= 290 && y <= 365) {
                        land = 18;
                    } else if (y >= 375 && y <= 450) {
                        land = 19;
                    } else if (y >= 460 && y <= 535) {
                        land = 20;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 795 && x <= 975) {
                    if (y >= 35 && y <= 110) {
                        land = 21;
                    } else if (y >= 120 && y <= 195) {
                        land = 22;
                    } else if (y >= 205 && y <= 280) {
                        land = 23;
                    } else if (y >= 290 && y <= 365) {
                        land = 24;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }
                else if (mouse_state.buttons == 1 && x >= 985 && x <= 1165) {
                    if (y >= 35 && y <= 110) {
                        land = 25;
                    } else if (y >= 120 && y <= 195) {
                        land = 26;
                    } else if (y >= 205 && y <= 280) {
                        land = 27;
                    } else if (y >= 290 && y <= 365) {
                        land = 28;
                    } else {
                        al_flip_display();
                        land = -1;
                    }

                }

                if (mouse_state.buttons == 1 && x >= 960 && x <= 1140)     // new key bottom
                    if (y >= 680 && y <= 755)
                    {
                        al_draw_rectangle(960, 680, 1140, 755, al_map_rgb(0, 0, 0), 3);
                        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 695, 0, "NEXT player's turn.");
                        al_flip_display();
                        al_draw_bitmap(bitmap2, 0, 0, 0);
                        al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"Put your BONUS soldiers at one of your land.");
                        soldier_display();
                        ready_for_next_round++;
                        turn = whose_turn_is_it(land);
                        al_flip_display();

                        can_I_write_turn=1; // makes the interference with primary_whose_turn_is_it solved.
                        round=0;
                        situation=1; // this makes them not use the first land of red and second land of blue.

                        land = -2;     // is this one working properly? (solved) seems to be fine.
                        // problem. (solved) : recognize this as a wrong input.
                    }

                if (land!=-1 && land!=-2)
                {

                    if (situation == 1)
                    {
                        if (check_land_is_correct(land, turn) == 1  && land!=-2)
                        {
                            land1 = land;
                            situation = 2;
                            printf("\n****land1=%d,situation=%d\n", land, situation);
                        }
                    }
                    else if (situation == 2)
                    {
                        land2 = land;
                        situation = 1;
                        printf("\n****land2=%d,situation=%d\n", land, situation);
                        if (Land_player[land1] == Land_player[land2])
                            soldier_transition(land2, land1);
                        else if (which_land_is_near(land1, land2) == 1)   // works properly.
                            Risk(land1, land2);
                        else
                        {
                            al_draw_text(font1, al_map_rgb(255, 255, 255), 280, 735, 0, "can not attack. "
                                                                                        "the selected lands are not next to each other.");
                            al_flip_display();
                        }
                    }


                    al_flip_display();
                    if (flag==1)
                    {
                        al_draw_bitmap(bitmap3, 0, 0, 0);
                        soldier_display();
                        primary_whose_turn_is_it(turn);
                        al_draw_text(font1, al_map_rgb(255,255,255),50,655,0,"You can either ATTACK or MOVE your soldier."
                                                                             " click next player when you are done.");
                        Draw_Land_Boarder(land);
                        al_flip_display();
                        flag=0;
                    }
                    else
                        Draw_Land_Boarder(land);
                    al_flip_display();
                    v = 1;
                }
                else if (land==-1)
                {
                    al_flip_display();
                    Draw_Land_Boarder(land);
                    flag=1;

                }
                soldier_display();

                if (situation==0) // subhan allah ! works properly.
                    situation=1;


            }
        }


        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;


    }
    //************************************************************************************************************


    al_destroy_sample(sample);
    al_destroy_bitmap(bitmap2);
    al_destroy_bitmap(bitmap3);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_font(font1);
}



void Draw_Land_Boarder(int land)
{
    //al_flip_display();
    int x,y;
    if (land==-2)
    {
        x = 960;
        y = 680;
        al_flip_display();
    }
    else if (land==-1)
    {
        x = -1;
        y = -1;
    }
    else
    {
        x = land_position_x(land);
        y = land_position_y(land);
    }


    if (x==-1 && y==-1)
        al_draw_text(font1, al_map_rgb(255,255,255),50,695,0,"please mark a valid position!");
    else
    {
        al_draw_rectangle(x, y, x + 180, y + 75, al_map_rgb(0, 0, 0), 3);
        if (land!=-2)
            al_draw_textf(font1, al_map_rgb(255, 255, 255), 50, 695, 0, "LAND %d marked.", land);
        al_flip_display();
        al_play_sample(sample,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);

    }


}

void soldier_display(void)
{
    int i;
    int x[29],y[29];
    for (i=0 ; i<29 ; i++)
    {
        x[i]=land_position_x(i)+80;
        y[i]=land_position_y(i)+20;
        if (Land_player[i]==GREEN)
            al_draw_textf(font1 , al_map_rgb(0,150,40),x[i],y[i],0,"%d",Land_quantity[i]);
        else if (Land_player[i]==RED)
            al_draw_textf(font1 , al_map_rgb(255,0,0),x[i],y[i],0,"%d",Land_quantity[i]);
        else if (Land_player[i]==YELLOW)
            al_draw_textf(font1 , al_map_rgb(200,200,10),x[i],y[i],0,"%d",Land_quantity[i]);
        else if (Land_player[i]==BLUE)
            al_draw_textf(font1 , al_map_rgb(0,0,220),x[i],y[i],0,"%d",Land_quantity[i]);


    }
    al_flip_display();
}

int land_position_x(int i)
{
    int x;
    switch (i)
    {
        case 0 :
        case 1 :
        case 2 :
        case 3 :
        case 4 :
        case 5 :
            x=35;break;
        case 6 :
        case 7 :
        case 8 :
            x=225;break;
        case 9 :
        case 10 :
        case 11 :
        case 12 :
        case 13 :
        case 14 :
            x=415;break;
        case 15 :
        case 16 :
        case 17 :
        case 18 :
        case 19 :
        case 20 :
            x=605;break;
        case 21 :
        case 22 :
        case 23 :
        case 24 :
            x=795; break;
        case 25 :
        case 26 :
        case 27 :
        case 28 :
            x=985;break;

    }
    return x;
}

int land_position_y(int i)
{
    int y;
    switch (i)
    {
        case 0 :
        case 6 :
        case 9 :
        case 15 :
        case 25 :
        case 21 :
            y=35; break;
        case 1 :
        case 7 :
        case 10 :
        case 16 :
        case 22 :
        case 26 :
            y=120; break;
        case 2 :
        case 11 :
        case 17 :
        case 23 :
        case 27 :
            y=205; break;
        case 4 :
        case 12 :
        case 19 :
            y=375; break;
        case 5 :
        case 8 :
        case 13 :
        case 20 :
            y=460; break;
        case 14 :
            y=545; break;
        case 3 :
        case 18 :
        case 24 :
        case 28 :
            y=290; break;
    }

    return y;
}

void wrong_input(void)
{
    al_draw_text(font1, al_map_rgb(255,255,255),210,695,0,"wrong input ! this is not your land. try another one.");
    al_flip_display();
}

void turn1(void)
{
    if (Turn_counter+1 >= primary_numbers)
        Turn_counter=0;
    else
        Turn_counter++;

}

int whose_turn_is_it(int land)
{
    int turn;
    if (Turn_counter == 0)
    {
        turn = RED;
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is red player's turn.");
    }
    else if (Turn_counter == 1)
    {
        turn = BLUE;
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is blue player's turn.");
    }
    else if (Turn_counter == 2)
    {
        turn = YELLOW;
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is yellow player's turn.");
    }
    else if (Turn_counter == 3)
    {
        turn = GREEN;
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is green player's turn.");
    } else
        turn =-1;


    //   if (land!=-1)   // what was this used to be work for?
    turn1();
    //turn2(land);
    al_flip_display();

    return turn;
}

void primary_whose_turn_is_it(int turn)
{
    if (turn == 0)
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is red player's turn.");
    else if (turn == 1)
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is blue player's turn.");
    else if (turn == 2)
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is yellow player's turn.");
    else if (turn == 3)
        al_draw_text(font1, al_map_rgb(255, 255, 255), 50, 735, 0, "It is green player's turn.");
}

void Primary_Rand(int primary_numbers)
{
    int yellow=0,red=0,blue=0,green=0;
    int i=0,n,a;

    if (primary_numbers == 4)
    {
        srand(time(0));

        while (i < 29)               // this place gives the soldiers random flags.
        {
            a = rand() % 4;

            if (a == 0 && red < 8)
            {
                Land_player[i] = RED;
                red++;
                i++;
            }

            if (a == 1 && blue < 7)
            {
                Land_player[i] = BLUE;
                blue++;
                i++;
            }

            if (a == 2 && yellow < 7)
            {
                Land_player[i] = YELLOW;
                yellow++;
                i++;
            }

            if (a == 3 && green < 7)
            {
                Land_player[i] = GREEN;
                green++;
                i++;
            }
        }
        Turn_counter=1;  // blue player starts
    }

    else if (primary_numbers == 3)
    {
        srand(time(0));

        while (i < 29)               // this place gives the soldiers random flags.
        {
            a = rand() % 3;

            if (a == 0 && red < 10)
            {
                Land_player[i] = RED;
                red++;
                i++;
            }
            if (a == 1 && blue < 10)
            {
                Land_player[i] = BLUE;
                blue++;
                i++;
            }
            if (a == 2 && yellow < 9)
            {
                Land_player[i] = YELLOW;
                yellow++;
                i++;
            }
        }
        Turn_counter=2; // yellow player starts
    }

    else if (primary_numbers == 2)
    {
        srand(time(0));

        while (i < 29)               // this place gives the soldiers random flags.
        {
            a = rand() % 2;

            if (a == 0 && red < 15)
            {
                Land_player[i] = RED;
                red++;
                i++;
            }
            if (a == 1 && blue < 14)
            {
                Land_player[i] = BLUE;
                blue++;
                i++;
            }
        }
        Turn_counter=1; // blue player starts
    }

}  // works properly.

int check_land_is_correct(int land, int turn)
{
    if (Land_player[land] != turn  && land!=-2)
    {
        wrong_input();
        return 0;
    }
    else
        return 1;
}

void soldier_counter(int *red, int *blue, int *yellow, int *green)
{

    int a,n,i;
    int r,b,y,g;

    ////////////////////////////////////////////////////////////////////
    r=0,b=0,y=0,g=0;
    for (i=0 ; i<29 ; i++)                           // general counter
    {
        if (Land_player[i]==RED)
            r++;

        else if (Land_player[i]==BLUE)
            b++;

        else if (Land_player[i]==YELLOW)
            y++;

        else if (Land_player[i]==GREEN)
            g++;
    }

    *red += (r/3);
    *blue += (b/3);
    *yellow += (y/3);
    *green += (g/3);


    ///////////////////////////////////////////////////////////////////////
    r=0,b=0,y=0,g=0;
    for (i=0 ; i<=8 ; i++)                           //  america bonus
    {
        if (Land_player[i]==RED)
            r++;
        else if (Land_player[i]==BLUE)
            b++;
        else if (Land_player[i]==YELLOW)
            y++;
        else if (Land_player[i]==GREEN)
            g++;
    }
    if (r==9)
        *red+=3;
    if (b==9)
        *blue+=3;
    if (y==9)
        *yellow+=3;
    if (g==9)
        *green+=3;
    ///////////////////////////////////////////////////////////////////////
    r=0,b=0,y=0,g=0;
    for (i=9 ; i<=11 ; i++)                            // Europe bonus
    {
        if (Land_player[i]==RED)
            r++;
        else if (Land_player[i]==BLUE)
            b++;
        else if (Land_player[i]==YELLOW)
            y++;
        else if (Land_player[i]==GREEN)
            g++;
    }
    for (i=15 ; i<=17 ; i++)
    {
        if (Land_player[i]==RED)
            r++;
        else if (Land_player[i]==BLUE)
            b++;
        else if (Land_player[i]==YELLOW)
            y++;
        else if (Land_player[i]==GREEN)
            g++;
    }
    if (r==6)
        *red+=4;
    if (b==6)
        *blue+=4;
    if (y==6)
        *yellow+=4;
    if (g==6)
        *green+=4;
    ///////////////////////////////////////////////////////////////////////
    r=0,b=0,y=0,g=0;
    for (i=12 ; i<=14 ; i++)                            // Africa bonus
    {
        if (Land_player[i]==RED)
            r++;
        else if (Land_player[i]==BLUE)
            b++;
        else if (Land_player[i]==YELLOW)
            y++;
        else if (Land_player[i]==GREEN)
            g++;
    }
    for (i=18 ; i<=20 ; i++)
    {
        if (Land_player[i]==RED)
            r++;
        else if (Land_player[i]==BLUE)
            b++;
        else if (Land_player[i]==YELLOW)
            y++;
        else if (Land_player[i]==GREEN)
            g++;
    }
    if (r==6)
        *red+=2;
    if (b==6)
        *blue+=2;
    if (y==6)
        *yellow+=2;
    if (g==6)
        *green+=2;
    ///////////////////////////////////////////////////////////////////////////
    r=0,b=0,y=0,g=0;
    for (i=21 ; i<=28 ; i++)                           //  asia bonus
    {
        if (Land_player[i]==RED)
            r++;
        else if (Land_player[i]==BLUE)
            b++;
        else if (Land_player[i]==YELLOW)
            y++;
        else if (Land_player[i]==GREEN)
            g++;
    }
    if (r==8)
        *red+=4;
    if (b==8)
        *blue+=4;
    if (y==8)
        *yellow+=4;
    if (g==8)
        *green+=4;
    ////////////////////////////////////////////////////////////////////////////


}    // works properly.

void soldier_transition(int land1, int land2)
{
    if (land1!=land2)
        if (Land_player[land1]==Land_player[land2])
        {
            if (Land_quantity[land2]>=2)
            {
                Land_quantity[land1]++;
                Land_quantity[land2]--;

                al_draw_text(font1, al_map_rgb(255,255,255),280,735,0,"SOLDIER TRANSITION done.");

            }
            else
            {
                al_draw_text(font1,al_map_rgb(255,255,255),280,735,0,"This soldier transition can not be done."
                                                                     " low soldier numbers.");
            }
        }
    al_flip_display();
}

int attack_member_number(int land1)
{
    int a;
    if (Land_quantity[land1]>=4)
        return 3;
    else {
        a = Land_quantity[land1] - 1;
        return a;   // if 0 is returned , no attack happens , has to be dealt with in the outcome function;
    }

}

int deffend_member_number(int land2)
{
    if (Land_quantity[land2]>=2)
        return 2;
    else
        return 1;
}

void Risk(int land1, int land2)
{
    int n1,n2;
    int temp;

    n1=attack_member_number(land1);
    n2=deffend_member_number(land2);
    int attack[n1], deffend[n2], i, j;

    if (n1<=0)
    {
        al_draw_text (font1 , al_map_rgb(255,255,255), 280 , 735 , 0 , "Can not attack,"
                                                                       " low soldiers at the selected land.");
    }
    else
    {
        al_draw_text(font1, al_map_rgb(255,255,255),280,735,0,"ATTACK and RISK! ");

        srand(time(0));


        for (i=0 ; i<n1 ; i++)
            attack[i] = (rand() % 6) + 1;

        for (i=0 ; i<n2 ; i++)
            deffend[i] = (rand() % 6) + 1;


        for (i=0 ; i<n1 ; i++)                 // this loop orders the random numbers;
        {
            for (j=i+1 ; j<n1 ; j++)
                if (attack[i] < attack[j])
                {
                    temp = attack[i];
                    attack[i] = attack[j];
                    attack[j] = temp;
                }
        }

        for (i=0; i<n2 ; i++)                 // this loop orders the random numbers;
        {
            for (j=i+1 ; j<n2 ; j++)
                if (deffend[i] < deffend[j])
                {
                    temp = deffend[i];
                    deffend[i] = deffend[j];
                    deffend[j] = temp;
                }
        }
        printf("n1=%d,n2=%d,attack[0]=%d,attack[1]=%d,attack[2]=%d,diffend[0]=%d,diffend[1]=%d",n1,n2,attack[0],attack[1],attack[2],deffend[0],deffend[1])
                ;
        for (i=0 ; i<2 ; i++)
        {
            if (attack[i] <= deffend[i])
            {
                //Land_quantity[land1]--;   // reduce soldier number from attacker
                n1--;
            }
            else
                Land_quantity[land2]--;   // reduce soldier number from deffender
        }

        if (Land_quantity[land2]<=0  && n1!=0)       // changing flag if the attacker wins.   /////////////////////////////////////////////////////////////
        {
            Land_quantity[land2] = n1;
            Land_quantity[land1] -= n1;
            Land_player[land2] = Land_player[land1];
        }
    }


}

int which_land_is_near(int land1, int land2)
{
    switch (land1)
    {
        case 0:
            if (land2 == 1 || land2 == 6)
                return 1;
            else
                return 0;
            break;
        case 1:
            if (land2 == 0 || land2 ==2 || land2==7)
                return 1;
            else
                return 0;
            break;
        case 2:
            if (land2==3 || land2==1)
                return 1;
            else
                return 0;
            break;
        case 3:
            if (land2==2 || land2==4)
                return 1;
            else
                return 0;
            break;
        case 4:
            if (land2==3 || land2==5)
                return 1;
            else
                return 0;
            break;
        case 5:
            if (land2==4 || land2==8)
                return 1;
            else
                return 0;
            break;
        case 6:
            if (land2==0 || land2==7 || land2==9)
                return 1;
            else
                return 0;
            break;
        case 7:
            if (land2==1 || land2==6 || land2==10)
                return 1;
            else
                return 0;
            break;
        case 8:
            if (land2==5 || land2==13)
                return 1;
            else
                return 0;
            break;
        case 9:
            if (land2==6 || land2==10 || land2==15)
                return 1;
            else
                return 0;
            break;
        case 10:
            if (land2==7 || land2==9 || land2==11 || land2==16)
                return 1;
            else
                return 0;
            break;
        case 11:
            if (land2==10 || land2==17)
                return 1;
            else
                return 0;
            break;
        case 12:
            if (land2==19 || land2==13)
                return 1;
            else
                return 0;
            break;
        case 13:
            if (land2==8 || land2==12 || land2==14 || land2==20)
                return 1;
            else
                return 0;
            break;
        case 14:
            if (land2==13)
                return 1;
            else
                return 0;
            break;
        case 15:
            if (land2==9 || land2==16 || land2==21)
                return 1;
            else
                return 0;
            break;
        case 16:
            if (land2==10 || land2==15 || land2==17 || land2==22)
                return 1;
            else
                return 0;
            break;
        case 17:
            if (land2==11 || land2==16 || land2==18 || land2==23)
                return 1;
            else
                return 0;
            break;
        case 18:
            if (land2==17 || land2==19 || land2 ==24)
                return 1;
            else
                return 0;
            break;
        case 19:
            if (land2==12 || land2==18 || land2==20)
                return 1;
            else
                return 0;
            break;
        case 20:
            if (land2==19 || land2==13)
                return 1;
            else
                return 0;
            break;
        case 21:
            if (land2==15 || land2==22 || land2==25)
                return 1;
            else
                return 0;
            break;
        case 22:
            if (land2==16 || land2==21 || land2==23 || land2==26)
                return 1;
            else
                return 0;
            break;
        case 23:
            if (land2==17 || land2==22 || land2==24 || land2==27)
                return 1;
            else
                return 0;
            break;
        case 24:
            if (land2==18 || land2==23 || land2==28)
                return 1;
            else
                return 0;
            break;
        case 25:
            if (land2==21 || land2==26)
                return 1;
            else
                return 0;
            break;
        case 26:
            if (land2==25 || land2==22 || land2==27)
                return 1;
            else
                return 0;
            break;
        case 27:
            if (land2==26 || land2==23 || land2==28)
                return 1;
            else
                return 0;
            break;
        case 28:
            if (land2==27 || land2==24)
                return 1;
            else
                return 0;
            break;
    }
}       // works properly.
