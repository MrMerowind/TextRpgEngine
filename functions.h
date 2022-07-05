#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

string getkeyBuffer;

class cl_debug{

fstream debugfile;
string dt;
public:
cl_debug()
{
    dt = "data/logs/error_log.txt";
    debugfile.open(dt.c_str(),ios::out);
}
~cl_debug()
{
    debugfile.close();
}
    void EngineError(string text)
    {
        debugfile<<"[EngineError] "<<text<<endl;
    }
    void GameError(string text)
    {
        debugfile<<"[GameError] "<<text<<endl;
    }
    void GameCrash(string text)
    {
        cls;
        cout<<"[Game Crash]"<<endl<<text<<" :(";
        getch();
        exit(0);
    }

};
cl_debug debug;

string cut_string(string text,int value)
{
    if(value < 1)
    {
        debug.EngineError("cut_string() bad value");
    }
    string a;
    string b;
    bool cut = false;
    for(int x = 0; x < (int)text.size();x++)
    {
        if(text[x] == '=') cut = true;
        else if(cut == false) a += text[x];
        else if(cut == true)  b += text[x];
    }
    if(value == 1) return a;
    else if(value == 2) return b;
    else return "";
}

string cut_string_coma(string text,int value,string filename)
{
    if(value < 0)
    {
        debug.EngineError("cut_string_coma() bad value");
        return "";
    }
    vector<string> part;
    part.push_back("");
    int bracketCounter = 0;
    for(int x = 0; x < (int)text.size();x++)
    {
        if(text[x] == '\\')
        {
            if((int)text.size() > x+1)
            {
                part[part.size()-1] += "\\" + text[x+1];
                x++;
            }
            else
            {
                string errorTmp = "Missing character after \\ in " + filename + " in line: " + text;
                debug.GameError(errorTmp);
            }
        }
        else if(text[x] == ',' && bracketCounter == 0)
        {
            part.push_back("");
        }
        else if(text[x] == '[')
        {
            bracketCounter++;
            part[part.size()-1] += '[';
        }
        else if(text[x] == ']')
        {
            bracketCounter--;
            part[part.size()-1] += ']';
        }
        else part[part.size()-1] += text[x];

        if(bracketCounter < 0)
        {
            string errorTmp = "Missing bracket in " + filename + " in line: " + text;
            debug.GameError(errorTmp);
        }
    }
    if(bracketCounter != 0)
    {
        string errorTmp = "Missing bracket in " + filename + " in line: " + text;
        debug.GameError(errorTmp);
    }
    if(value < (int)part.size()) return part[value];
    return "";
}

int string_to_int(string text)
{
    return (int)atoi(text.c_str());
}

string int_to_string(int value)
{
    stringstream ss;
    ss<<value;
    string text;
    ss>>text;
    return text;
}

string double_to_string(double value)
{
    ostringstream strs;
    strs << value;
    string str = strs.str();
    return str;
}


#endif // FUNCTIONS_H_INCLUDED
