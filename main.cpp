#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "source.h"
#include "snake.h"
#include <fstream>


using namespace std;
void highscore();
int select(int max, int pos, int seefirst);
bool run();
bool PlayClassic(int mode = 1, int option = 1);
//bool PlayMorden(int mode);

int main()
{
    SetConsoleTitleW(L"Rắn săn mồi by khanhzum!");
    srand(time(NULL));

    while (run());
    
    //   system("pause");
    return 0;
}

//Khang tổ chức đọc file điểm cao lên và cout tất cả ở đây
void highscore()
{

    ifstream infile;
    infile.open("highscore.txt", std::ios::in);
    string highscoreshow;
    int highscoreshow1;
    while (!infile.eof())
    {
        /*
        getline(infile, highscoreshow,';');
        std::cout << setw(20) << left << highscoreshow;
        cin >> highscoreshow1;

        std::cout << highscoreshow1 << endl;
        getline(infile, highscoreshow);*/
        getline(infile, highscoreshow, ';');
        std::cout << setw(20) << left << highscoreshow;
        infile >> highscoreshow1;
        getline(infile, highscoreshow);


        std::cout << highscoreshow1 << endl;
        

    }
    
    infile.close();

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
    //Đổi màu SNAKE///////////////////////////////////////////////////////////////
    system("cls");
    while (!_kbhit()) 
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
        case(1): while (PlayClassic()); break;
        case(2):
        {
            gotoXY(0, 0);
            cout << endl;
            cout << "Coming soon!!!" << endl;
            cout << "Return" << endl;
            gotoXY(15, 2); cout << "<-";

            selection = select(1, 15, 1);
            goto posx;
            //while (PlayMorden()); break;
        }
        
        case(3): goto posx;
        }
    } break;
    case (2):
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
        case(1):
        {
            int option = 0;
            gotoXY(0, 0);
            cout << endl;
            // Đọc file lên Ngà chỉ đọc danh sách các tài khoản đã tạm dừng để đưa ra lựa chọn

            ifstream infile;
            infile.open("savegame.txt", std::ios::in);
            string temp;
            while (!infile.eof())
            {
                getline(infile, temp, ' ');
                std::cout << setw(20) << left << temp;
                getline(infile, temp, ' ');
                std::cout << temp << endl;
                getline(infile, temp, '\n');
                option++;
            }

            infile.close();
            //
            cout << "Return" << endl;
            gotoXY(23, 1); cout << "<-";
            selection = select(option + 1, 23); //1
            system("cls");
            if (selection != option + 1)
                while (PlayClassic(2, selection));
            else goto posx;

        }break;
        case(2):
        {
            gotoXY(0, 0);
            cout << endl;
            cout << "Coming soon!!!" << endl;
            cout << "Return" << endl;
            gotoXY(15, 2); cout << "<-";

            selection = select(1, 15, 1);
            goto posx;

        }break;

        case(3): goto posx;
        }break;
        
    }break;

    case (3):
    {
        gotoXY(0, 0);
        cout << "Highscore: " << endl;
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

bool PlayClassic(int mode, int option)
{
    string name;
    system("cls");
    if (mode == 1)
    {
        cout << "Name: ";   
        cin >> name;
        system("cls");
    }

    SNAKE* s;
    s = new SNAKE;
    char t;
    int Huong = 0;

    if (mode == 1) s->New(name);
    else if (mode == 2) s->Continue(option);

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

                changColor(1+rand()%15);
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
                s->SaveScore();
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
                    s->New(name);
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

/*
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
*/