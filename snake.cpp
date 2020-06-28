#include "snake.h"
#include <string.h>
#include <vector>
#include <string>
#include <ctime>
#include<fstream>
#include "source.h"
#include <iostream>
#include <cstdlib>



using namespace std;

void SNAKE::New(string name)
{
    //Thiết đặt thông số con rắn
    SNAKE::name = name;
    score = 0;
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
void SNAKE::Continue(int option)
{
    //Ngà lấy dữ liệu của tài khoản số option lên và khởi tạo thông số con rắn trong phần này
    ifstream infile;
    infile.open("savegame.txt", std::ios::in);
    //chá»n dÃ²ng 1

    string temp;
    for (int i = 0; i < option - 1; ++i)
    {
        getline(infile, temp, '\n');
    }

    getline(infile, name, ' ');
    infile >> score;
    infile >> Huong;
    infile >> Leng;
    for (int i = 0; i < Leng; i++)
    {
        /*temp.x = A[i].x;
        temp.y = A[i].y;*/
        A.push_back(SNAKE::temp);
        infile >> A[i].x;
        getline(infile, temp, ' ');
        infile >> A[i].y;
    }
    A.push_back(SNAKE::temp);
    infile.close();



    //Váº½ con ráº¯n ban Ä‘áº§u
    for (int i = Leng-1; i > 0; i--)
    {
        gotoXY(A[i].x, A[i].y);

        cout << "O";
    }
    gotoXY(A[0].x, A[0].y);
    cout << "+";

    //Táº¡o vÃ  váº½ quáº£
    TaoQua();
}
   
int SNAKE::GetConsox2()
{
    return consox2;
}

void SNAKE::SetHuong(int a)
{
    Huong = a;
}
int SNAKE::GetSpeed()
{
    return timedelay;
}
void SNAKE::SetScore(int x)
{
    score = x;
}
int SNAKE::GetScore()
{
    return score;
}
string SNAKE::GetName()
{
    return name;
}
    
void SNAKE::DiChuyen()
{
    for (int i = Leng; i > 0; i--) A[i] = A[i - 1];
    if (Huong == 0) A[0].x = A[1].x + 1;
    if (Huong == 1) A[0].y = A[1].y + 1;
    if (Huong == 2) A[0].x = A[1].x - 1;
    if (Huong == 3) A[0].y = A[1].y - 1;
}
    //Vẽ con rắn, một bước di chuyển sẽ vẽ thêm đầu và xoá phần đuôi
void SNAKE::Ve()
{
    gotoXY(A[Leng].x, A[Leng].y); cout << " ";
    changColor(1 + rand() % 15);
    gotoXY(A[1].x, A[1].y); cout << "O";
    changColor(15);
    gotoXY(A[0].x, A[0].y); cout << "+";

}
    //Tạo quả và vẽ quả, ko cần refresh khung hình
void SNAKE::TaoQua()
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
void SNAKE::AnQua()
{
    if (A[0].x == qua.x && A[0].y == qua.y)
    {
        //PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
        score += 10;
        gotoXY(consox2 + 8, 0);
        cout << setw(6) << score;
        temp.x = A[Leng].x;
        temp.y = A[Leng].y;
        Leng++;

        A.push_back(temp);
        TaoQua();
    }
}
    //Kiểm tra có cắn phải đuôi sau mỗi lần di chuyển
bool SNAKE::CheckCanDuoi()
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
bool SNAKE::CheckClassic()
{
    if (A[0].x == consox1 || A[0].x == consox2 || A[0].y == consoy1 || A[0].y == consoy2)
        return true;
    return false;
}
    //Kiểm tra nếu đụng tường thì đưa đầu qua bên kia
void SNAKE::CheckModern()
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

//Khang lưu điểm ở đây
void SNAKE::SaveScore()
{
    ofstream outfile;
    outfile.open("highscore.txt", std::ios::app);
    outfile << endl << name << " ;" << score;
    outfile.close();
}
void SNAKE::SaveGame()
{
    ofstream out;
    out.open("savegame.txt", std::ios::app);

    out  << name << " " << score << " " << Huong << " "  << Leng ;
    for (int i = 0; i < Leng; i++)
    {
        out << " " << A[i].x << " " << A[i].y ;
    }
    out << endl;
    out.close();
    //Lưu các thông số bao gồm mã số định danh (nếu có), tên, điểm, độ dài, các thông số phần thân con rắn
}

