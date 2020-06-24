#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <string.h>

#include <vector>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;
int select(int max, int pos);
bool run();
bool PlayClassic();
bool PlayMorden();

void gotoXY(int x, int y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;
    CursorPosition.X = x; // Locates column
    CursorPosition.Y = y; // Locates Row
    SetConsoleCursorPosition(console, CursorPosition); // Sets position for next thing to be printed
}

void changColor(int k)
{
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, k);
}

void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setFontSize(int FontSize)
{
    CONSOLE_FONT_INFOEX info = { 0 };
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = FontSize; // leave X as zero
    info.FontWeight = FW_NORMAL;
    wcscpy_s(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

struct _POINT {
    int x, y;
};

class SNAKE {
private:
    vector <_POINT> A;
    //_POINT A[1000];
    _POINT temp;
    _POINT qua;
    int Leng;
    int Huong = 0;
    int score = 0;
    int timedelay = 200; //Độ khó
    //Các tham số giới hạn 4 cạnh của khung trò chơi
    int consox1 = 0, consox2 = 0, consoy1 = 0, consoy2 = 0;
public:
    //Thiết đặt mặc định
    SNAKE(int x1 = 0, int x2 = 50, int y1 = 0, int y2 = 25)
    {
        consox1 = x1, consox2 = x2, consoy1 = y1, consoy2 = y2;
        //Vẽ khung viền 
        gotoXY(consox1, consoy1);
        for (int i = consox1; i <= consox2; i++)
            cout << "-";
        gotoXY(consox1, consoy2);
        for (int i = consox1; i <= consox2; i++)
            cout << "-";
        for (int i = consoy1 + 1; i < consoy2; i++)
        {
            gotoXY(consox1, i); cout << "|";
        }
        for (int i = consoy1 + 1; i < consoy2; i++)
        {
            gotoXY(consox2, i); cout << "|";
        }
        gotoXY(consox2 + 2, 0); cout << "SCORE:    0";
        gotoXY(consox2 + 2, 2); cout << "\"p\" to pause";
        gotoXY(consox2 + 2, 3); cout << "\"p\ to continue";
        gotoXY(consox2 + 2, 4); cout << "F5 to restart";
        gotoXY(consox2 + 2, 5); cout << "ESC to MENU";
 
        New();
   
    }
    void New()
    {
        //Thiết đặt thông số con rắn
        Leng = 10;
        for (int i = 0; i < Leng; i++)
        {
            A.push_back(temp);
            A[i].x = 10 + Leng - i - 1; A[i].y = 10;
        }
        A.push_back(temp);


        //Vẽ con rắn ban đầu
        for (int i = Leng - 1; i > 0; i--)
        {
            gotoXY(A[i].x, A[i].y);

            cout << "O";
        }
        gotoXY(A[0].x, A[0].y);
        cout << "+";

        //Tạo và vẽ quả
        TaoQua();
    }

    //Các hàm Setter và Getter
    void SetHuong(int a)
    {
        Huong = a;
    }
    int GetSpeed()
    {
        return timedelay;
    }
    /*int Getconsox1() { return consox1; }
    int Getconsox2() { return consox2; }
    int Getconsoy1() { return consoy1; }
    int Getconsoy2() { return consoy2; }*/
    //Di chuyển con rắn 
    void DiChuyen()
    {
        
        for (int i = Leng; i > 0; i--) A[i] = A[i - 1];
     
        if (Huong == 0) A[0].x = A[1].x + 1;
        if (Huong == 1) A[0].y = A[1].y + 1;
        if (Huong == 2) A[0].x = A[1].x - 1;
        if (Huong == 3) A[0].y = A[1].y - 1;
    }
    //Vẽ con rắn, một bước di chuyển sẽ vẽ thêm đầu và xoá phần đuôi
    void Ve()
    {
        gotoXY(A[Leng ].x, A[Leng ].y); cout << " ";
        changColor(1 + rand() % 15);
        gotoXY(A[1].x, A[1].y); cout << "O";
        changColor(15);
        gotoXY(A[0].x, A[0].y); cout << "+";
        
    }
    //Tạo quả và vẽ quả, ko cần refresh khung hình
    void TaoQua() 
    {
        int x, y;
        bool checkxfail = true, checkyfail = true;
        
        while (checkxfail || checkyfail)
        {
            x = consox1 + 1 + rand() % (consox2 - consox1 - 1);
            y = consoy1 + 1 + rand() % (consoy2 - consoy1 - 1);
            if (x == qua.x && y == qua.y) continue;
            int i;
            for (i = 0; i < Leng; i++)
            {
                if (x == A[i].x && y == A[i].y)
                {
                    i = -1;
                    break;
                }
            }
            if (i == Leng) break;
        }

        qua.x = x;
        qua.y = y;
        gotoXY(qua.x, qua.y);
        cout << "*";
    }
    //Kiểm tra có ăn quả sau mỗi lần di chuyển, nếu có tạo mới quả
    void AnQua()
    { 
        if (A[0].x == qua.x && A[0].y == qua.y)
        {
            PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
            score += 10;
            gotoXY(consox2 + 8, 0);
            cout << setw(6) << score;
            Leng++;
            A.push_back(temp);
            TaoQua();

        }
    }
    //Kiểm tra có cắn phải đuôi sau mỗi lần di chuyển
    bool CheckCanDuoi()
    {
        for (int i = 1; i < Leng; i++)
        {
            if (A[0].x == A[i].x && A[0].y == A[i].y)
            {
                return true;
            }
        }
        return false;
    }
    //Kiểm tra có đập đầu vào tường trong chế độ classic
    bool CheckClassic()
    {
        if (A[0].x == consox1 || A[0].x == consox2 || A[0].y == consoy1 || A[0].y == consoy2)
            return true;
        return false;
    }
    //Kiểm tra nếu đụng tường thì đưa đầu qua bên kia
    void CheckModern()
    {
        if (A[0].x == consox1) 
        {
            A[0].x = consox2 - 1; return;
        }
        if (A[0].x == consox2)
        {
            A[0].x = consox1 + 1; return;
        }
        if (A[0].y == consoy1)
        {
            A[0].y = consoy2 - 1; return;
        }
        if (A[0].y == consoy2)
        {
            A[0].y = consoy1 + 1; return;
        }
    }
};




int main()
{
    SetConsoleTitleW(L"Rắn săn mồi by khanhzum!");
    srand(time(NULL));

    while (run());

 //   system("pause");
    return 0;
}

int select(int max, int pos)
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

                gotoXY(pos, selection); cout << "  ";
                selection--;
                if (selection == 0) selection = max;
                gotoXY(pos, selection); cout << "<-";
                //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
                break;
            case (80):

                gotoXY(pos, selection); cout << "  ";
                selection++;
                if (selection == max + 1) selection = 1;
                gotoXY(pos, selection); cout << "<-";
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
    int mode;
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
    mode = 1;
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

        mode = select(3, 15);
        system("cls");
        switch (mode)
        {
        case(1): while (PlayClassic()); break;
        case(2): while (PlayMorden()); break;
        case(3): goto posx; break;
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
    selection = select(2, 12);
    
    if (selection == 1)
    {
        //PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_SYNC);
        return 1;
    }
    if (selection == 2) return 0;
    

    return 0;
}

bool PlayClassic()
{
    system("cls");
    SNAKE s;
    char t;

    int Huong = 0;

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
            
            case (112):
            {
                while (1)
                {
                    char c;
                    c = _getch();
                    if (c == 'p')break;
                }
            }break;

            case (27): return 0 ; break;

            case (0):
            {
                t = _getch();
                if (t == 63) return 1;
            }break;
            }
        }

        s.SetHuong(Huong);

        s.DiChuyen();
        s.AnQua();

        if (s.CheckCanDuoi() == true || s.CheckClassic() == true)
        {
            PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);

            gotoXY(0,0);
            cout << "GAME OVER !!!"; break;
        }
        s.Ve();
        Sleep(s.GetSpeed());
    }

    return 0;
}

bool PlayMorden()
{
    system("cls");
    SNAKE s;
    char t;

    int Huong = 0;

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
            
            case (112):
            {
                while (1)
                {

                    char c;
                    c = _getch();
                    if (c == 'p')break;
                }
            }break;

            case (27): return 0; break;

            case (0):
            {
                t = _getch();
                if (t == 63) return 1;
            }break;
            }
        }

        s.SetHuong(Huong);

        s.DiChuyen();
        s.CheckModern();
        s.AnQua();

        if (s.CheckCanDuoi() == true )
        {
            PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);

            gotoXY(0, 0);
            cout << "GAME OVER !!!"; break;
        }
        s.Ve();
        Sleep(s.GetSpeed());
    }
    return 0;
}