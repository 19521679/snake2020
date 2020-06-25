#include <iostream>
#include <string>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#include "source.h"
#include "snake.h"


using namespace std;
void highscore();
int select(int max, int pos, int seefirst);
bool run();
bool PlayClassic(int mode);
bool PlayMorden(int mode);

int main()
{
    SetConsoleTitleW(L"Rắn săn mồi by khanhzum!");
    srand(time(NULL));

    while (run());

    //   system("pause");
    return 0;
}


void highscore()
{

}

int select(int max, int pos, int seefirst = 0)
{
    int selection = 1;
    char key;
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case (-32):
        {
            key = _getch();
            switch (key)
            {
            case (72):

                gotoXY(pos, selection + seefirst); cout << "  ";
                selection--;
                if (selection == 0) selection = max;
                gotoXY(pos, selection + seefirst); cout << "<-";
                //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
                break;
            case (80):

                gotoXY(pos, selection + seefirst); cout << "  ";
                selection++;
                if (selection == max + 1) selection = 1;
                gotoXY(pos, selection + seefirst); cout << "<-";
                //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
                break;
            }
        }break;
        case (13):
        {
            //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
            return selection;
        }
        }
    }
}

bool run()
{
    int selection;
    char key;
    setFontSize(100);
    system("cls");
    while (!_kbhit()) //Đổi màu SNAKE///////////////////////////////////////////////////////////////
    {

        gotoXY(0, 1);
        changColor(1 + rand() % 15);
        cout << " - SNAKE -  ";
        Sleep(300);
    }

    key = _getch();

    gotoXY(0, 0);
    changColor(15);
    setFontSize(20);

posx:;

    system("cls");

    selection = 1;
    gotoXY(0, 0);
    //step1: select///////////////////////////////////////////////////////////////
    cout << endl;
    cout << "New Game" << endl;
    cout << "Continue" << endl;
    cout << "High Score" << endl;
    cout << "About" << endl;
    cout << "Exit" << endl;
    gotoXY(15, 1); cout << "<-";

    selection = select(5, 15);

    //step2: do///////////////////////////////////////////////////////////////
    system("cls");
    switch (selection)
    {
    case (1):
    {
        gotoXY(0, 0);
        cout << endl;
        cout << "Classic" << endl;
        cout << "Morden" << endl;
        cout << "Return" << endl;
        gotoXY(15, 1); cout << "<-";

        selection = select(3, 15);
        system("cls");
        switch (selection)
        {
        case(1): while (PlayClassic(1)); break;
        case(2): while (PlayMorden(1)); break;
        case(3): goto posx;
        }
    } break;
    case (2):
    {
        gotoXY(0, 0);
        cout << endl;
        cout << "hello" << endl;
        cout << "Return <-";
        while (1)
        {
            key = _getch();
            if (key == 13)
            {
                //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
                goto posx;
            }
        }
    }break;

    case (3):
    {
        gotoXY(0, 0);
        cout << endl;
        highscore();
        cout << "Return <-";
        while (1)
        {
            key = _getch();
            if (key == 13)
            {
                //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
                goto posx;
            }
        }
    }break;

    case (4):
    {
        gotoXY(0, 0);
        cout << endl;
        cout << "Develop by " << endl;
        cout << "Le Mai Duy Khanh " << endl;
        cout << "Nguyen Le Nguyen Khang " << endl;
        cout << "Nguyen Tan Nga " << endl;
        cout << "   from UIT with love <3!!! " << endl;
        cout << "Return <-";
        while (1)
        {
            key = _getch();
            if (key == 13)
            {
                //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
                goto posx;
            }
        }
    }break;
    case (5):return 0; break;
    }

    //step3: again?///////////////////////////////////////////////////////////////
    gotoXY(0, 0);
    cout << "****************" << endl;
    cout << "* Play Again ? *" << endl;
    cout << "*     YES      *" << endl;
    cout << "*     NO       *" << endl;
    cout << "****************" << endl;
    gotoXY(12, 2); cout << "<-";
    selection = select(2, 12, 1);

    if (selection == 1)
    {
        //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
        return 1;
    }

    return 0;
}

bool PlayClassic(int mode = 1)
{
    system("cls");
    SNAKE* s;
    s = new SNAKE;
    char t;
    int Huong = 0;
    int colorsavegame = 9;

    if (mode == 1) s->New();
    else if (mode == 2) s->Continue();

    while (1)
    {
        if (_kbhit())
        {
            t = _getch();
            switch (t)
            {   
            //phím mũi tên
            case (-32):
            {
                t = _getch();
                switch (t)
                {
                case (72):if (Huong != 1)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 3;
                } break;
                case (80):if (Huong != 3)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 1;
                } break;
                case (75):if (Huong != 0)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 2;
                } break;
                case (77):if (Huong != 2)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 0;
                } break;
                }
            }break;

            //phím p
            case (112):
            {
                //while (1)
                {
                    char c;
                    c = _getch();
                    if (c == 'p')break;
                }
            }break;

            //phím s
            case (115): 
            {
                s->SaveGame();
                if (colorsavegame == 14) colorsavegame = 9;
                else colorsavegame++;
                changColor(colorsavegame);
                gotoXY(s->GetConsox2() + 2, 8);               
                cout << "Has Save!!!";
                changColor(15);
            }break;

            //phím ESC
            case (27): 
            {
                int selection;
                gotoXY(0, 0);
                cout << "****************" << endl;
                cout << "*  Save Game ? *" << endl;
                cout << "*     YES      *" << endl;
                cout << "*     NO       *" << endl;
                cout << "****************" << endl;
                gotoXY(12, 2); cout << "<-";
                selection = select(2, 12, 1);
                if (selection == 1)
                {
                    s->SaveGame();
                }
                return 0;
            }break;

            //phím F5
            case (0):
            {
                t = _getch();
                if (t == 63)
                {
                    system("cls");
                    delete s;
                    s = new SNAKE;
                    Huong = 0;
                    if (mode == 1) s->New();
                    else if (mode == 2) s->Continue();
                }
            }break;
            }
        }

        s->SetHuong(Huong);
        s->DiChuyen();
        s->AnQua();
        if (s->CheckCanDuoi() == true || s->CheckClassic() == true)
        {
            PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);

            gotoXY(0, 0);
            cout << "GAME OVER !!!"; break;
        }
        s->Ve();
        Sleep(s->GetSpeed());
    }

    s->SaveScore();
    return 0;
}

bool PlayMorden(int mode = 1)
{
    system("cls");
    SNAKE* s;
    s = new SNAKE;
    char t;
    int Huong = 0;

    if (mode == 1) s->New();
    else if (mode == 2) s->Continue();

    while (1)
    {
        if (_kbhit())
        {
            t = _getch();
            switch (t)
            {
            case (-32):
            {
                t = _getch();
                switch (t)
                {
                case (72):if (Huong != 1)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 3;
                } break;
                case (80):if (Huong != 3)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 1;
                } break;
                case (75):if (Huong != 0)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 2;
                } break;
                case (77):if (Huong != 2)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 0;
                } break;
                }
            }break;

            //phím p
            case (112):
            {
                while (1)
                {
                    char c;
                    c = _getch();
                    if (c == 'p')break;
                }
            }break;

            //phím s
            case (115): s->SaveGame(); break;

                //phím ESC
            case (27):
            {
                int selection;
                gotoXY(0, 0);
                cout << "****************" << endl;
                cout << "* Save Game ? *" << endl;
                cout << "*     YES      *" << endl;
                cout << "*     NO       *" << endl;
                cout << "****************" << endl;
                gotoXY(12, 2); cout << "<-";
                selection = select(2, 12, 1);
                if (selection == 1)
                {
                    s->SaveGame();
                    return 0;
                }
                else return 0;
            }break;

            //phím F5
            case (0):
            {
                t = _getch();
                if (t == 63)
                {
                    system("cls");
                    delete s;
                    s = new SNAKE;
                    Huong = 0;
                    if (mode == 1) s->New();
                    else if (mode == 2) s->Continue();
                }
            }break;
            }
        }

        s->SetHuong(Huong);
        s->DiChuyen();
        s->CheckModern();
        s->AnQua();
        if (s->CheckCanDuoi() == true)
        {
            PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);

            gotoXY(0, 0);
            cout << "GAME OVER !!!"; break;
        }
        s->Ve();
        Sleep(s->GetSpeed());
    }
    s->SaveScore();
    return 0;
}
