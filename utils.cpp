#include "utils.h"
int Utils::line = 20;


void Utils::printLog(string log){
    Utils::writeChar(5, Utils::line,log, 15);
    Utils::line++;
}

void Utils::writeChar(short x, short y, string pchar, char color)
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    COORD loc = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << pchar;
}
void Utils::cleanConsole(short xStart,short xEnd, short y)
{
    COORD loc;
    loc.Y = y;
    for (short i = xStart; i < xEnd; i++)
    {
        loc.X = i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
        cout << " " << endl;
        ;
    }
}
void Utils::chooseUtil(int &option, int &key, bool &flag, int x, int y, vector<string> &options){
    while (true)
    {
        if (kbhit())
        {
            char ch;
            ch = getch();
            if (ch == 27)
            {
                exit(0);
            }
            if (ch == 72 || ch == 80 || ch == '\r')
            {
                if (ch == 72)
                {
                    Utils::writeChar(x, y + option, "  ", 0);
                    option--;
                }
                else if (ch == 80)
                {
                    Utils::writeChar(x, y + option, "  ", 0);
                    option++;
                }
                if (option < 0)
                {
                    option = 0;
                }
                else if (option >= options.size())
                {
                    option--;
                }
                Utils::writeChar(x, y + option, "                         ", 0);
                Sleep(100);
                Utils::writeChar(x, y + option, "→", 15);
                Utils::writeChar(x+2, y + option, options[option], 15);

                if (ch == '\r')
                {
                    key = option;
                    flag = true;
                }
            }
        }
        if (flag)
            break;
    }
}
