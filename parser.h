#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
struct vector2s
{
    string x;
    string y;
};

class cl_parser
{
public:
    vector<vector2s> variables;
    string script_run(string text,string filename)
    {
        // Dzielenie na czesci
        int bracketCounter = 0;
        vector<string> parts;
        parts.push_back("");
        for(int x =0; x<(int)text.size(); x++)
        {
            if(text[x] == '\\')
            {
                if((int)text.size() > x+1)
                {
                    parts[parts.size()-1] += "\\";
                    parts[parts.size()-1] += text[x+1];
                    x++;
                }
                else
                {
                    string errorTmp = "Nothing after '\\' in file " + filename + " in line: " + text;
                    debug.GameError(errorTmp);
                }
            }
            else if(text[x] == '[')
            {
                if(bracketCounter == 0)
                {
                    parts.push_back("[");
                }
                else parts[parts.size()-1] += "[";
                bracketCounter++;
            }
            else if(text[x] == ']')
            {
                bracketCounter--;
                if(bracketCounter < 0)
                {
                    string errorTmp = "Missing bracket in " + filename + " in line: " + text;
                    debug.GameError(errorTmp);
                    return "";
                }
                else if(bracketCounter > 0)
                {
                    parts[parts.size()-1] += "]";
                }
                else if(bracketCounter == 0)
                {
                    parts[parts.size()-1] += "]";
                    parts.push_back("");
                }
            }
            else
            {
                parts[parts.size()-1] += text[x];
            }
        }
        if(bracketCounter != 0)
        {
            string errorTmp = "Missing bracket in " + filename + " in line: " + text;
            debug.GameError(errorTmp);
        }

        // Wykonywanie funkcji
        for(int x = 1; x < (int)parts.size(); x+=2)
        {
            parts[x] = script_part(parts[x],filename);
        }

        // Scalanie
        string wholeTmp = "";
        for(int x = 0; x < (int)parts.size(); x++)
            wholeTmp += parts[x];

        // Usuwanie slash
        string noSlash = "";
        bool skip = false;
        for(int x = 0; x < (int)wholeTmp.size(); x++)
        {
            if(wholeTmp[x] == '\\' && skip == false)
            {
                skip = true;
            }
            else
            {
                skip = false;
                noSlash += wholeTmp[x];
            }
        }

        return noSlash;

        // Usuwanie sleszy pszy braketach

        // zwracanie scalonego tekstu
    }
    string script_part(string text,string filename)
    {
        if(text.size() < 1) return "";
        else if(text[0] == '[' && text[text.size()-1] == ']')
        {
            string text2 = "";
            for(int x = 1; x < (int)text.size() -1; x++)
            {
                text2 += text[x];
            }
            text = text2;
        }
        else return text;

        // Wykonywanie funkcji
        if(cut_string_coma(text,0,filename) == "OnLocationEnter")
        {
            if(player.locationEnter == true)
            {
                text = script_part(cut_string_coma(text,1,filename),filename);
                player.locationEnter = false;
            }
            else text = "";
        }
        else if(cut_string_coma(text,0,filename) == "DisplayFile")
        {
            displayFile(script_part(cut_string_coma(text,1,filename),filename));
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "DisplayFileNoParse")
        {
            displayFileNoParse(script_part(cut_string_coma(text,1,filename),filename));
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "DisplayFileNoParse")
        {
            displayFileNotChanged(script_part(cut_string_coma(text,1,filename),filename));
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "ClearScreen")
        {
            cls;
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "DisplayText")
        {
            text = script_part(cut_string_coma(text,1,filename),filename);
        }
        else if(cut_string_coma(text,0,filename) == "SetValue")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            bool isset = false;
            for(int x =0; x < (int)variables.size(); x++)
            {
                if(variables[x].x == z1)
                {
                    variables[x].y = z2;
                    isset = true;
                    break;
                }
            }
            if(isset == false)
            {
                vector2s tmp;
                tmp.x = z1;
                tmp.y = z2;
                variables.push_back(tmp);
            }
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "IsKeyPressed")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            if(getkeyBuffer.size() < 1) text = "false";
            for(int x = 0; x < (int)getkeyBuffer.size(); x++)
            {
                if(getkeyBuffer[x] == z1[0])
                {
                    getkeyBuffer.erase(x);
                    text = "true";
                    break;
                }
                else text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "ExitGame")
        {
            exit_ = true;
        }
        else if(cut_string_coma(text,0,filename) == "ReadWord")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2;
            cin>>z2;
            bool isset = false;
            for(int x =0; x < (int)variables.size(); x++)
            {
                if(variables[x].x == z1)
                {
                    variables[x].y = z2;
                    isset = true;
                    break;
                }
            }
            if(isset == false)
            {
                vector2s tmp;
                tmp.x = z1;
                tmp.y = z2;
                variables.push_back(tmp);
            }
            text = "";

        }
        else if(cut_string_coma(text,0,filename) == "ReadLine")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2;
            getline(cin,z2);
            bool isset = false;
            for(int x =0; x < (int)variables.size(); x++)
            {
                if(variables[x].x == z1)
                {
                    variables[x].y = z2;
                    isset = true;
                    break;
                }
            }
            if(isset == false)
            {
                vector2s tmp;
                tmp.x = z1;
                tmp.y = z2;
                variables.push_back(tmp);
            }
            text = "";

        }
        else if(cut_string_coma(text,0,filename) == "Wait")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            int z2 = string_to_int(z1);
            Sleep(z2);
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "Math")
        {
            string z1=script_run(cut_string_coma(text,1,filename),filename);
            if(Check(z1)==true)
            {
                text = double_to_string(Value_Of_Expr(z1));
            }
            else
            {
                string errorTmp = "Wrong mathematic data " + filename + " in line: " + text;
                debug.GameError(errorTmp);
                text = "";
            }



        }
        else if(cut_string_coma(text,0,filename) == "If")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            if(z1[0]== 't' || z1[0] == 'T')
            {
                text = script_part(cut_string_coma(text,2,filename),filename);
            }
            else
            {
                text = script_part(cut_string_coma(text,3,filename),filename);
            }

        }
        else if(cut_string_coma(text,0,filename) == "Not")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            if(z1[0]== 't' || z1[0] == 'T')
            {
                text = "false";
            }
            else
            {
                text = "true";
            }

        }
        else if(cut_string_coma(text,0,filename) == "Or")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if((z1[0]== 'f' || z1[0] == 'F')&&(z2[0]== 'f' || z2[0] == 'F'))
            {
                text = "false";
            }
            else
            {
                text = "true";
            }

        }
        else if(cut_string_coma(text,0,filename) == "And")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if((z1[0]== 't' || z1[0] == 'T')&&(z2[0]== 't' || z2[0] == 'T'))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "Equal")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if(string_to_int(z1) == string_to_int(z2))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "Greater")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if(string_to_int(z1) > string_to_int(z2))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "Lesser")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if(string_to_int(z1) < string_to_int(z2))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "LesserOrEqual")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if(string_to_int(z1) <= string_to_int(z2))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "GreaterOrEqual")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if(string_to_int(z1) >= string_to_int(z2))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "Compare")
        {
            string z1=script_run(cut_string_coma(text,1,filename),filename);
            string z2=script_run(cut_string_coma(text,2,filename),filename);
            if(z1 == z2)
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "Cut")
        {
            string z1=script_run(cut_string_coma(text,1,filename),filename);
            string z2=script_run(cut_string_coma(text,2,filename),filename);
            string z3=script_run(cut_string_coma(text,3,filename),filename);
            int a = string_to_int(z2);
            int b = string_to_int(z3);
            string net = "";
            for(int x = a;true;x++)
            {
                if(b>0)
                {
                    if(x <(int)z1.size()) net+=z1[x];
                    else net+= " ";
                    b--;
                }
                else break;
            }
            text = net;
        }
        else if(cut_string_coma(text,0,filename) == "Different")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            if(string_to_int(z1) != string_to_int(z2))
            {
                text = "true";
            }
            else
            {
                text = "false";
            }
        }
        else if(cut_string_coma(text,0,filename) == "SetCursorPosition")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            string z2=script_part(cut_string_coma(text,2,filename),filename);
            gotoxy(string_to_int(z1),string_to_int(z2));
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "Repeat")
        {
            string z1=script_part(cut_string_coma(text,1,filename),filename);
            text = "";
            for(int x =0;x<string_to_int(z1);x++)
            {
                text += script_part(cut_string_coma(text,2,filename),filename);
            }

        }
        else if(cut_string_coma(text,0,filename) == "CurrentLocationNextPath")
        {
            if(player.current_location_next > (int)locations.table[locations.getID(player.current_location)].path_list.size() - 1)
                    player.current_location_next = 0;
                text = locations.table[locations.getID(player.current_location)].path_list[player.current_location_next];
                player.current_location_next++;
        }
        else if(cut_string_coma(text,0,filename) == "WaitForKey")
        {
            getch();
            text = "";
        }
        else if(cut_string_coma(text,0,filename) == "Reload")
        {
            reload_game = true;
            text = "";
        }



        return text;
    }
    string parse(string text,string filename)
    {
        // Dzielenie na czesci
        vector<string>textList;
        textList.push_back("");
        for(int x=0; x<(int)text.size(); x++)
        {
            if(text[x] == '\\')
            {
                if((int)text.size() > x+1) // usuwanie sleszy przy % i zostawianie przy
                {
                    if(text[x+1] == '[') textList[textList.size()-1] += "\\[";
                    else if(text[x+1] == ']') textList[textList.size()-1] += "\\]";
                    else if(text[x+1] == '\\') textList[textList.size()-1] += "\\\\";
                    else textList[textList.size()-1] += text[x+1];
                }
                else
                {
                    string errorTmp = "Nothing after '\\' in file " + filename + " in line: " + text;
                    debug.GameError(errorTmp);
                }
                x++;
            }
            else if(text[x] == '%')
            {
                textList.push_back("");
            }
            else
            {
                textList[textList.size()-1] += text[x];
            }
        }
        // Wywolywanie api
        for(int x = 1; x<(int)textList.size(); x+=2)
        {
            if(textList[x] == "WindowTitle") textList[x] = config.window_title;
            else if(textList[x] == "StartingLocation") textList[x] = config.starting_location;
            else if(textList[x] == "ExitInfo") textList[x] = config.exit_info;
            else if(textList[x] == "PlayerName") textList[x] = player.name;
            else if(textList[x] == "PlayerLevel") textList[x] = int_to_string(player.level);
            else if(textList[x] == "CurrentLocationName") textList[x] = locations.table[locations.getID(player.current_location)].name;
            else if(textList[x] == "CurrentLocationDescription") textList[x] = locations.table[locations.getID(player.current_location)].description;
            else if(textList[x] == "CurrentLocationTag") textList[x] = locations.table[locations.getID(player.current_location)].locationTag;
            else if(textList[x] == "CurrentLocationPathsInRow")
            {
                textList[x] = "";
                for(int x = 0; x < (int)locations.table[locations.getID(player.current_location)].path_list.size(); x++)
                    textList[x] += int_to_string(x) + "." + locations.table[locations.getID(player.current_location)].path_list[x] + " ";
            }
            else if(textList[x] == "CurrentLocationPathsInColumn")
            {
                textList[x] = "";
                for(int x = 0; x < (int)locations.table[locations.getID(player.current_location)].path_list.size(); x++)
                {
                    textList[x] += int_to_string(x) + "." + locations.table[locations.getID(player.current_location)].path_list[x];
                    if(x != (int)locations.table[locations.getID(player.current_location)].path_list.size() - 1) textList[x] += "\n";
                }

            }
            else if(textList[x] == "CurrentLocationPathsNumber") textList[x] = int_to_string(locations.table[locations.getID(player.current_location)].path_list.size());
            else if(textList[x] == "PlayerName") textList[x] = player.name;
            else if(textList[x] == "PlayerMaxHp") textList[x] = int_to_string(player.max_hp);
            else if(textList[x] == "PlayerHp") textList[x] = int_to_string(player.hp);
            else if(textList[x] == "PlayerWeapon") textList[x] = player.item_weapon;
            else if(textList[x] == "Authors") textList[x] = config.authors_info;
            else if(textList[x] == "PlayerHelmet") textList[x] = player.item_helmet;
            else if(textList[x] == "PlayerGloves") textList[x] = player.item_gloves;
            else if(textList[x] == "PlayerPants") textList[x] = player.item_pants;
            else if(textList[x] == "PlayerArmour") textList[x] = player.item_armour;
            else if(textList[x] == "PlayerBoots") textList[x] = player.item_boots;
            else if(textList[x] == "PlayerLevel") textList[x] = int_to_string(player.level);
            else if(textList[x] == "PlayerExp") textList[x] = int_to_string(player.exp);
            else if(textList[x] == "PlayerExpForNextLevel") textList[x] = int_to_string(player.getExpNeededOnLvl(player.level));
            else if(textList[x] == "NextLine") textList[x] = "\n";
            else if(textList[x] == "PlayerName") textList[x] = player.name;
            else
            {
                bool changed = false;
                for(int z = 0; z<(int)variables.size(); z++)
                {
                    if(textList[x] == variables[z].x)
                    {
                        textList[x] = variables[z].y;
                        changed = true;
                        break;
                    }
                }
                if(!changed) textList[x] = "";
            }
        }
        // Scalanie tekstu
        string textAfter = "";
        for(int x =0; x < (int)textList.size(); x++)
            textAfter += textList[x];

        // Dzielenie tekstu pod funkcje [name,data]
        string textAfterAfter = script_run(textAfter,filename);

        // Zwracanie tekstupo parsowaniu
        return textAfterAfter;
    }
    void displayFile(string path)
    {
        fstream display_file;
        display_file.open(path.c_str(),ios::in);
        if(display_file.good())
        {
            while(!display_file.eof())
            {
                string line;
                getline(display_file,line);
                if(line.size() <= 0);
                else if(line[0] == '#') continue;
                cout<<parse(line,path)<<endl;
            }
        }
        else
        {
            string errorTmp = "Nie mozna odczytac pliku: " + path;
            debug.GameError(errorTmp);
        }
        display_file.close();
    }
    void displayFileNoParse(string path)
    {
        fstream display_file;
        display_file.open(path.c_str(),ios::in);
        if(display_file.good())
        {
            while(!display_file.eof())
            {
                string line;
                getline(display_file,line);
                if(line.size() <= 0);
                else if(line[0] == '#') continue;
                cout<<line<<endl;
            }
        }
        else
        {
            string errorTmp = "Nie mozna odczytac pliku: " + path;
            debug.GameError(errorTmp);
        }
        display_file.close();
    }
    void displayFileNotChanged(string path)
    {
        fstream display_file;
        display_file.open(path.c_str(),ios::in);
        if(display_file.good())
        {
            while(!display_file.eof())
            {
                string line;
                getline(display_file,line);
                cout<<line<<endl;
            }
        }
        else
        {
            string errorTmp = "Nie mozna odczytac pliku: " + path;
            debug.GameError(errorTmp);
        }
        display_file.close();
    }


};


#endif // PARSER_H_INCLUDED
