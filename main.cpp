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
void highscore(int chedochoi);
int select(int max, int pos, int seefirst);
bool run();
bool Play(int chedochoi, int mode = 0, int option = 1);

int main()
{
    SetConsoleTitleW(L"Rắn săn mồi by KhanhKhangNga2020");
    srand(time(NULL));

    while (run());

       system("pause");
    return 0;
}

//Khang tổ chức đọc file điểm cao lên và cout tất cả ở đây
void highscore(int chedochoi)
{
    string temp;
    int so;
    ifstream infile;
    if (chedochoi == 0) infile.open("highscoreclassic.txt", std::ios::in);
    else infile.open("highscoremorden.txt", std::ios::in);
    
    while (!infile.eof())
    {
        getline(infile, temp, ';');
        if (temp != "")
        {
            std::cout << setw(20) << left << temp;
            infile >> so;
            std::cout << setw(10) << left << so;
            getline(infile, temp, ';');
            infile >> so;
            std::cout << so << endl;
            getline(infile, temp, '\n');
           
        }
        else break;
    }   
    infile.close();
    return;

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
        case(1): while (Play(0)); break;
        case(2): while (Play(1)); break;
        
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

        int chedochoi;
        chedochoi = select(3, 15) - 1;
        /* gotoXY(0, 5);
         cout << chedochoi << endl;
         int a;
         cin >> a;*/
        system("cls");

        if (chedochoi == 3) goto posx;

        int option = 0;
        gotoXY(0, 0);
        std::cout << setw(20) << left << "Name";
        std::cout << setw(10) << left << "Level";
        std::cout << "Score" << endl;
        // Đọc file lên Ngà chỉ đọc danh sách các tài khoản đã tạm dừng để đưa ra lựa chọn

        ifstream infile;
        if (chedochoi == 0) infile.open("savegameclassic.txt", std::ios::in);
        else infile.open("savegamemorden.txt", std::ios::in);
        string temp;
        while (!infile.eof())
        {
            getline(infile, temp, ';');
            if (temp != "")
            {
                option++;
                std::cout << setw(20) << left << temp;
                getline(infile, temp, ';');
                std::cout << setw(10) << left << temp;
                getline(infile, temp, ';');
                std::cout << temp << endl;
                getline(infile, temp, '\n');
            }
            else break;

        }
        infile.close();
        //
        cout << "Return" << endl;
        gotoXY(40, 1); cout << "<-";
        selection = select(option + 1, 40); //1
        system("cls");
        if (selection != option + 1)
            while (Play(chedochoi, 1, selection));
        else goto posx;

    }break;

    case (3):
    {
        gotoXY(0, 0);
        cout << "Highscore: " << endl;
        std::cout << setw(20) << left << "Name";
        std::cout << setw(10) << left << "Level";
        std::cout << "Score" << endl;
       
        cout << "Classic:" << endl << endl;
        highscore(0);
        cout << endl << "Morden:" << endl << endl;
        highscore(1);
        cout << endl;
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

bool Play(int chedochoi, int mode, int option)
{
    string name;
    int level;
    int Huong;
    system("cls");
    if (mode == 0)
    {
        cout << "Name: ";
        cin >> name;
        cout << "Select" << endl;
        cout << "Level 1" << endl;
        cout << "Level 2" << endl;
        cout << "Level 3" << endl;
        cout << "Level 4" << endl;
        gotoXY(15, 2); cout << "<-";
        level = select(4, 15, 1);
    
        system("cls");
    }

    SNAKE* s;
    s = new SNAKE;
    char t;
    
    s->SetChedochoi(chedochoi);
    if (mode == 0)
    {
        s->New(name, level);
        Huong = 0;
    }
    else if (mode == 1)
    {
        s->Continue(option);
        Huong = s->GetHuong();
    }

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
                    s->SetHuong(Huong);
                } break;
                case (80):if (Huong != 3)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 1;
                    s->SetHuong(Huong);
                } break;
                case (75):if (Huong != 0)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 2;
                    s->SetHuong(Huong);
                } break;
                case (77):if (Huong != 2)
                {
                    PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                    Huong = 0;
                    s->SetHuong(Huong);
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
                    if (mode == 0)
                    {
                        Huong = 0;
                        s->New(name, level);
                    }
                    else if (mode == 1)
                    {                
                        s->Continue(option);
                        Huong = s->GetHuong();
                    }

                }
            }break;
            }
        }
        s->DiChuyen();
        if (chedochoi == 1)s->CheckModern();
        else if (s->CheckClassic() == true) 
        {
            PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);

            gotoXY(0, 0);
            cout << "GAME OVER !!!"; break;
        }
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
    delete s;
    return 0;
}
