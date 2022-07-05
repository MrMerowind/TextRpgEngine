#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cctype>
#include <cmath>

// Defines
#define cls system("cls")

using namespace std;

#include "declarations.h"

#include "calculator.h"

#include "functions.h"

#include "classes.h"

// Globalne kontenery
cl_config config;
cl_quest quests;
cl_item items;
cl_mob mobs;
cl_npc npcs;
cl_location locations;

#include "parser.h"
cl_parser parser;

#include "game.h"
cl_game game;

void showMenu()
{
    cout<<"1.New game"<<endl;
    cout<<"2.Load game"<<endl;
    cout<<"3.Authors"<<endl;
    cout<<"4.Help"<<endl;
    cout<<"5.Exit"<<endl;
}


int main()
{
    //Variables reset
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    reload_game = false;
    // Wczytywanie danych
    config.load();
    locations.load();
    npcs.load();
    mobs.load();

    //Presets
    SetWindowSize(config.window_width,config.window_height);
    SetWindowLong(GetActiveWindow(), GWL_STYLE, GetWindowLong(GetActiveWindow(), GWL_STYLE)&~WS_SIZEBOX);

    // Menu
    while(true)
    {
        cls;
        game.menu();
        char cmd;
        cmd = getch();
        if(cmd == '1') game.newGame();
        else if(cmd == '2') game.loadGame();
        else if(cmd == '3') game.authors();
        else if(cmd == '4') game.help();
        else if(cmd == '5') game.exit_program();


    }

    return 0;
}
