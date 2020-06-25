#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <string.h>
#include <windows.h>

#include "source.h"

#pragma once
#pragma comment(lib, "winmm.lib")

using namespace std;


struct _POINT {
    int x, y;
};
class SNAKE {
private:
    vector <_POINT> A;
    //_POINT A[1000];
    _POINT temp;
    _POINT qua;
    string name = { "A" };
    int Leng;
    int Huong;
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
        gotoXY(consox2 + 2, 5); cout << "s to save game";
        gotoXY(consox2 + 2, 6); cout << "ESC to exit";
    }
    void New();

    void Continue();
    //Các hàm Setter và Getter
    void SetHuong(int a);
    int GetSpeed();
    void SetScore(int x);
    int GetScore();
    string GetName();
    //Di chuyển con rắn
    void DiChuyen();
    //Vẽ con rắn, một bước di chuyển sẽ vẽ thêm đầu và xoá phần đuôi
    void Ve();
    //Tạo quả và vẽ quả, ko cần refresh khung hình
    void TaoQua();
    //Kiểm tra có ăn quả sau mỗi lần di chuyển, nếu có tạo mới quả
    void AnQua();
    //Kiểm tra có cắn phải đuôi sau mỗi lần di chuyển
    bool CheckCanDuoi();
    //Kiểm tra có đập đầu vào tường trong chế độ classic
    bool CheckClassic();
    //Kiểm tra nếu đụng tường thì đưa đầu qua bên kia
    void CheckModern();

    void SaveScore();

    void SaveGame();
   
    
};


