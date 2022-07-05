#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

class cl_player
{
public:
    string name;
    float max_hp;
    float hp;
    string item_weapon;
    string item_helmet;
    string item_gloves;
    string item_pants;
    string item_armour;
    string item_boots;
    vector<string> global_script;
    vector<string> inventory_list;
    int level;
    int exp;
    vector<int> exp_for_level;
    string current_location;
    int current_location_next;
    bool locationEnter;

    int getExpNeededOnLvl(int lvl)
    {
        if(lvl-1>=(int)exp_for_level.size()) return 99999;
        else return exp_for_level[lvl];

    }

};
cl_player player;

class cl_config
{
public:
    string window_title;
    string starting_location;
    string exit_info;
    string authors_info;
    int window_width;
    int window_height;
    string help;
    int player_start_hp;
    vector<string> location_display;
    void load()
    {
        fstream configfile;
        configfile.open("data/config.txt");
        if(configfile.good() == false)
        {
            debug.EngineError("data/config.txt is unable to open");
        }
        else
        {
            string line;
            while(configfile.eof() == false)
            {
                getline(configfile,line);
                if(line[0] == '#') continue;
                else if(cut_string(line,1) == "WindowTitle") window_title = cut_string(line,2);
                else if(cut_string(line,1) == "StartingLocation") starting_location = cut_string(line,2);
                else if(cut_string(line,1) == "ExitInfo") exit_info = cut_string(line,2);
                else if(cut_string(line,1) == "Authors") authors_info = cut_string(line,2);
                else if(cut_string(line,1) == "WindowWidth") window_width = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "WindowHeight") window_height = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "PlayerStartingHp") player_start_hp = string_to_int(cut_string(line,2));
                else
                {
                    string strtmp = "data/config.txt is broken on line: " + line;
                    debug.GameError(strtmp);
                }
            }
        }
        SetWindowText(GetForegroundWindow(),window_title.c_str());

        fstream helpfile;
        helpfile.open("data/help.txt");
        if(helpfile.good() == false)
        {
            debug.EngineError("data/help.txt is unable to open");
        }
        else
        {
            string line;
            while(helpfile.eof() == false)
            {
                getline(helpfile,line);
                if(line[0] == '#') continue;
                else
                {
                    help += line;
                    help += '\n';
                }
            }
        }

        fstream locationdisplayfile;
        locationdisplayfile.open("data/location_display.txt");
        if(locationdisplayfile.good() == false)
        {
            debug.EngineError("data/location_display.txt is unable to open");
        }
        else
        {
            string line;
            while(locationdisplayfile.eof() == false)
            {
                getline(locationdisplayfile,line);
                if(line[0] == '#') continue;
                else
                {
                    if(line == "[KeepRunning]")
                    {
                        while(locationdisplayfile.eof() == false)
                        {
                            getline(locationdisplayfile,line);
                            if(line[0] == '#') continue;
                            else if(line == "[/KeepRunning]")
                            {
                                break;
                            }
                            else
                            {
                                player.global_script.push_back(line);
                            }
                        }
                    }
                    else location_display.push_back(line);
                }
            }
        }
        locationdisplayfile.close();
        configfile.close();
        helpfile.close();
    }

};
class cl_quest
{
public:
    string name;
    vector<string> reward_list;
};
class cl_item
{
public:
    string name;
    float price;
    // co bedzie dawac
};
struct str_mob
{
    string name;
    float hp;
    float damage;
    float block;
    float crit_chance;
    vector<string> loot_list;
    vector<int> loot_chance;
};

class cl_mob
{
public:
    vector<str_mob>table;
    void load()
    {
        fstream mobfile;
        mobfile.open("data/mobs.txt");
        if(mobfile.good() == false)
        {
            debug.EngineError("data/mobs.txt is unable to open");
        }
        else
        {
            string line;
            str_mob mobTmp;
            mobTmp.name="Not created";
            mobTmp.block=0;
            mobTmp.crit_chance=0;
            mobTmp.damage=0;
            mobTmp.hp=0;
            while(mobfile.eof() == false)
            {
                getline(mobfile,line);
                if(line[0] == '#') continue;
                else if(cut_string(line,1) == "MobName")
                {
                    table.push_back(mobTmp);
                    table[table.size() - 1].name = cut_string(line,2);

                }
                else if(cut_string(line,1) == "Hp") table[table.size() - 1].hp = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "Damage") table[table.size() - 1].damage = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "Block") table[table.size() - 1].block = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "CritChance") table[table.size() - 1].crit_chance = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "Loot")
                {
                    table[table.size() - 1].loot_list.push_back(cut_string(line,2));
                    table[table.size() - 1].loot_chance.push_back(100);
                }
                else if(cut_string(line,1) == "LootChance") table[table.size() - 1].loot_chance[table[table.size() - 1].loot_chance.size()-1] = string_to_int(cut_string(line,2));
                else
                {
                    string strtmp = "data/mobs.txt is broken on line: " + line;
                    debug.GameError(strtmp);
                }
            }
        }
        mobfile.close();
    }
};



struct str_npc
{
    string name;
    bool buyItems;
    bool sellItems;
    vector<string> item_list;
    vector<string> quest_list;
    vector<string> talk_list;
};

class cl_npc{
public:
    vector<str_npc> table;
    void load()
    {
        fstream npcfile;
        npcfile.open("data/npcs.txt");
        if(npcfile.good() == false)
        {
            debug.EngineError("data/npcs.txt is unable to open");
        }
        else
        {
            string line;
            str_npc npcTmp;
            npcTmp.name="Not created";
            npcTmp.buyItems=false;
            npcTmp.sellItems=false;
            while(npcfile.eof() == false)
            {
                getline(npcfile,line);
                if(line[0] == '#') continue;
                else if(cut_string(line,1) == "NpcName")
                {
                    table.push_back(npcTmp);
                    table[table.size() - 1].name = cut_string(line,2);

                }
                else if(cut_string(line,1) == "SellItems")
                {
                    string tmp = cut_string(line,2);
                    if(tmp[0]=='t' || tmp[0]=='T') table[table.size() - 1].sellItems = true;
                    else table[table.size() - 1].sellItems = false;
                }
                else if(cut_string(line,1) == "BuyItems")
                {
                    string tmp = cut_string(line,2);
                    if(tmp[0]=='t' || tmp[0]=='T') table[table.size() - 1].buyItems = true;
                    else table[table.size() - 1].buyItems = false;
                }
                else if(cut_string(line,1) == "Quest") table[table.size() - 1].quest_list.push_back(cut_string(line,2));
                else if(cut_string(line,1) == "Talk") table[table.size() - 1].talk_list.push_back(cut_string(line,2));
                else if(cut_string(line,1) == "Item") table[table.size() - 1].item_list.push_back(cut_string(line,2));
                else
                {
                    string strtmp = "data/npcs.txt is broken on line: " + line;
                    debug.GameError(strtmp);
                }
            }
        }
        npcfile.close();
    }


};
struct str_locations
{
    string name;
    string description;
    string locationTag;
    bool mobsAttackOnEnter;
    vector<string> npc_list;
    vector<string> mob_list;
    vector<int> mob_spawn_chance;
    vector<string> path_list;

};




class cl_location
{
public:
    vector<str_locations> table;
    int getID(string locationName)
    {
        for(int x=0; x<(int)table.size(); x++)
        {
            if(table[x].name == locationName) return x;
        }

        return -1;
    }
    void load()
    {
        fstream locationfile;
        locationfile.open("data/locations.txt");
        if(locationfile.good() == false)
        {
            debug.EngineError("data/locations.txt is unable to open");
        }
        else
        {
            string line;
            str_locations locationTmp;
            locationTmp.name = "Not created";
            locationTmp.mobsAttackOnEnter = false;
            locationTmp.description = "There is nothing around you. You are in the middle of nothing.";
            locationTmp.locationTag = "Default";
            while(locationfile.eof() == false)
            {
                getline(locationfile,line);
                if(line[0] == '#') continue;
                else if(cut_string(line,1) == "LocationName")
                {
                    table.push_back(locationTmp);
                    table[table.size() - 1].name = cut_string(line,2);

                }
                else if(cut_string(line,1) == "LocationDescription") table[table.size() - 1].description = cut_string(line,2);
                else if(cut_string(line,1) == "LocationTag") table[table.size() - 1].locationTag = cut_string(line,2);
                else if(cut_string(line,1) == "Npc") table[table.size() - 1].npc_list.push_back(cut_string(line,2));
                else if(cut_string(line,1) == "Mob")
                {
                    table[table.size() - 1].mob_list.push_back(cut_string(line,2));
                    table[table.size() - 1].mob_spawn_chance.push_back(100);
                }
                else if(cut_string(line,1) == "MobSpawnChance")
                    table[table.size()-1].mob_spawn_chance[table[table.size()-1].mob_spawn_chance.size()-1] = string_to_int(cut_string(line,2));
                else if(cut_string(line,1) == "Path") table[table.size()-1].path_list.push_back(cut_string(line,2));
                else
                {
                    string strtmp = "data/locations.txt is broken on line: " + line;
                    debug.GameError(strtmp);
                }
            }
        }
        locationfile.close();
    }
};

#endif // CLASSES_H_INCLUDED
