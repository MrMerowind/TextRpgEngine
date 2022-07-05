#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class cl_game
{

public:
    void game()
    {
        getkeyBuffer = "";
        int cmd = 0;
        exit_ = false;
        bool bGame = true;
        while(bGame)
        {
            cls;
            show_location(player.current_location);
            cout<<endl;
            while(true)
            {
                if(exit_)
                {

                    exit_game();
                    return;
                }
                cout<<"\r     \r";
                cout<<cmd;
                for(int x = 0; x < (int)player.global_script.size();x++) parser.parse(player.global_script[x],"data/location_display.txt");
                while(kbhit())
                {char znak = getch();
                if(znak == '0') cmd=cmd*10+0;
                else if(znak == '1') cmd=cmd*10+1;
                else if(znak == '2') cmd=cmd*10+2;
                else if(znak == '3') cmd=cmd*10+3;
                else if(znak == '4') cmd=cmd*10+4;
                else if(znak == '5') cmd=cmd*10+5;
                else if(znak == '6') cmd=cmd*10+6;
                else if(znak == '7') cmd=cmd*10+7;
                else if(znak == '8') cmd=cmd*10+8;
                else if(znak == '9') cmd=cmd*10+9;
                else if(znak == (char)(8)) cmd=cmd/10;
                else if(znak == (char)(13))
                {
                    if(cmd < (int)locations.table[locations.getID(player.current_location)].path_list.size() && cmd >= 0)
                    {
                        if(locations.getID(locations.table[locations.getID(player.current_location)].path_list[cmd])!=-1)
                        {
                            player.current_location = locations.table[locations.getID(player.current_location)].path_list[cmd];
                            player.locationEnter = true;
                            game();
                            return;
                        }
                        else
                        {
                            string errorTmp = "Trying to visit location that does not exist: " + locations.table[locations.getID(player.current_location)].path_list[cmd];
                            debug.GameError(errorTmp);
                        }
                    }
                    else
                    {
                        cmd = 0;
                    }
                }
                else getkeyBuffer += znak;
                }

                if(cmd > 1000) cmd = cmd /10;
            }


        }
    }
    void drawLine(string paste)
    {
        for(int x=0;x<(int)paste.size();x++)
                {
                    if(paste[x] == '&' && x+3 < (int)paste.size())
                    {
                        string tmp = "";
                        tmp += paste[x+1];
                        tmp += paste[x+2];
                        tmp += paste[x+3];
                        SetConsoleTextAttribute(hConsole, string_to_int(tmp));
                        x+=3;
                    }
                    else
                    {
                        cout<<paste[x];
                    }
                }
                cout<<endl;
    }
    void show_location(string location_name)
    {
        int locationID = locations.getID(player.current_location);
        if(locationID == -1)
        {
            string errorMsg = "Starting location does not exist in data/locations.txt: " + player.current_location;
            debug.GameError(errorMsg);
            debug.GameCrash("Starting location does not exist");
        }
        else
        {
            for(int x=0; x<(int)config.location_display.size(); x++)
            {
                if(reload_game)
                {
                    reload_game=false;
                    game();
                    return;
                }
                string paste = parser.parse(config.location_display[x],"data/locations.txt");
                drawLine(paste);
            }
        }

    }
    void menu()
    {
        vector<string>co;
        co.push_back("&046");cls;
        co.push_back("[SetCursorPosition,30,1]&164                   -\\[Menu\\]-                  &047");
        co.push_back("[SetCursorPosition,30,2]&0461.New game                                   ");
        co.push_back("[SetCursorPosition,30,3]&0462.Load game                                  ");
        co.push_back("[SetCursorPosition,30,4]&0463.Authors                                    ");
        co.push_back("[SetCursorPosition,30,5]&0464.Help                                       ");
        co.push_back("[SetCursorPosition,30,6]&0465.Exit                                       &015");
        for(int x=0;x<(int)co.size();x++)
        {
            drawLine(parser.parse(co[x],"Menu"));
        }

    }

    void newGame()
    {
        player.exp = 0;
        player.level = 1;
        player.hp = config.player_start_hp;
        player.max_hp = config.player_start_hp;
        player.item_armour = "empty";
        player.item_boots = "empty";
        player.item_gloves = "empty";
        player.item_helmet = "empty";
        player.item_pants = "empty";
        player.item_weapon = "empty";
        player.locationEnter = false;
        player.current_location_next = 0;
        player.inventory_list.clear();
        player.current_location = config.starting_location;
        getkeyBuffer = "";
        cls;
        cout<<"Write your name: ";
        cin>>player.name;
        game();

    }
    void loadGame()
    {
        cls;
        cout<<"[Feature] Loading a game is not available yet";
        getch();
    }
    void authors()
    {
        vector<string>co;
        co.push_back("&046");cls;
        co.push_back("[SetCursorPosition,30,1]&164         -\\[Engine Created By\\]-         &047");
        co.push_back("[SetCursorPosition,30,2]&046     MrMerowind (ernest1511@wp.pl)     ");
        co.push_back("[SetCursorPosition,30,5]&164         -\\[Engine Testers\\]-            &047");
        co.push_back("[SetCursorPosition,30,6]&046     Jeszcze nikt nie testowau xD      ");
        co.push_back("[SetCursorPosition,30,9]&164         -\\[Game Created By\\]-           &047");
        co.push_back("[SetCursorPosition,30,10]&046%Authors%");
        co.push_back("[SetCursorPosition,30,13]&164         -\\[Special thanks to\\]-         &047");
        co.push_back("[SetCursorPosition,30,14]&046        Nikt sobie nie zasluzyl        &015");
        string auth = "Authors";
        for(int x =0;x< (int)co.size();x++)
        drawLine(parser.parse(co[x],auth));
        getch();

    }
    void help()
    {
        cls;
        cout<<config.help;
        getch();

    }
    void exit_game()
    {
        return;
    }
    void exit_program()
    {
        exit(0);
    }



};


#endif // GAME_H_INCLUDED
