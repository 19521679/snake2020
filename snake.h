#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <string.h>
#include <windows.h>
#include<fstream>

#include "source.h"

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
    int chedochoi=0;
    string name = { "A" };
    int Leng = 10;
    int Huong;
    int score = 0;
    int level;
    int timedelay = 200; //Độ khó
    //Các tham số giới hạn 4 cạnh của khung trò chơi
    int consox1 = 0; int consox2 = 50; int consoy1 = 0; int consoy2 = 25;
public:
    //Thiết đặt mặc định
    SNAKE();
    SNAKE(int x1, int x2, int y1, int y2);
    
    void Init()
    {
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
    void New(string name,int level);

    void Continue(int option);

    //Các hàm Setter và Getter
    int GetConsox2();
    void SetHuong(int a);
    int GetHuong();
    int GetSpeed();
    void SetScore(int x);
    int GetScore();
    string GetName();
    void SetChedochoi(int x)
    {
        chedochoi = x;
    }
    //Di chuyển con rắn
    void DiChuyen();
    //Vẽ con rắn, một bước di chuyển sẽ vẽ thêm đầu và xoá phần đuôi
    void Ve();
    //Tạo quả và vẽ quả, ko cần refresh khung hình
    void TaoQua();
    void VeQua();
    //Kiểm tra có ăn quả sau mỗi lần di chuyển, nếu có tạo mới quả
    void AnQua();
    //Kiểm tra có cắn phải đuôi sau mỗi lần di chuyển
    bool CheckCanDuoi();
    //Kiểm tra có đập đầu vào tường trong chế độ classic
    bool CheckClassic();
    //Kiểm tra nếu đụng tường thì đưa đầu qua bên kia
    void CheckModern();
    //Lưu điểm
    void SaveScore();
    //Lưu Game để có thể tiếp tục
    void SaveGame(); 
};


