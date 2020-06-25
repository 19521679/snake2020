#include "snake.h"
#include <string.h>
#include <vector>
#include <string>
#include <ctime>
#include "source.h"

#pragma once

using namespace std;



void SNAKE::New()
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
void SNAKE::Continue()
{

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
void SNAKE::SaveScore()
{
    SNAKE s;

    //lưu điểm, lưu tên
    //ostream os;
    //file: tên; điểm
    //os= s.GetScore();

    //return os;
}
void SNAKE::SaveGame()
{
}

