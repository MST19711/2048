#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<graphics.h>
#include<Windows.h>
#include <conio.h>
#define KEY_DOWN(x) ((GetAsyncKeyState(x)&0x8000)?1:0)
using namespace std;
const int H = 600, W = 400;
int M[10][10];
int score;
int win = 2018;
bool lose = 0;
int times = 0;
bool In(int n, int size) {
    return (n >= 1 and n <= size);
}
int next_nonzero_add(int size, int i, int j, int di, int dj) {
    int ti = i, tj = j;
    while (M[ti][tj] == 0 and In(ti, size) and In(tj, size)) ti += di, tj += dj;
    if (ti != i)   return ti;
    if (tj != j)   return tj;
    return 0;
}
int rand_number() {
    int num = rand() % 8;
    num *= num, num *= num, num /= 1000, num++;
    cout << num << endl;
    int re = 1;
    num = min(10, num);
    while (num) {
        re *= 2;
        num--;
    }
    score += re;
    return re;
}
void add_in_map(int size) {
    srand(time(0) + times);
    int x = (rand() % size) + 1, y = (rand() % size) + 1;
    while (M[x][y] != 0)   x = (rand() % size) + 1, y = (rand() % size) + 1;
    M[x][y] = rand_number();
}
void init(int size) {
    srand(time(0) + times);
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            M[i][j] = (rand() % 4) < 3 ? 0 : rand_number();
        }
    }
}
int power(int x, int n) {
    int re = 0;
    while (x)   x/= n, re++;
    return re;
}
void draw(int size) {
    int windowL = W / 15, windowR = W - (W / 15);
    int windowT = W / 15, windowB = W - (W / 15);
    int blockw = (windowR - windowL) / 5;
    setfillcolor(RGB(187, 173, 160));
    solidroundrect(windowL - 10, windowT - 10, windowR + 10, windowB + 10, W / 80, W / 80);
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            int x = windowL + ((windowR - windowL) / 4) * (j - 1) + ((windowR - windowL) / 8);
            int y = windowL + ((windowR - windowL) / 4) * (i - 1) + ((windowR - windowL) / 8);
            if (M[i][j] == 0) {
                setfillcolor(RGB(205, 193, 180));
                solidroundrect(x-(blockw/2)+1, y+(blockw/2)+1, x + (blockw / 2), y - (blockw / 2), W / 100, W / 100);
            }
            else {
                int r = (230 + 2 * power(M[i][j], 2)) % 255, g = (255 + 225 - 6 * power(M[i][j], 2)) % 255, b = (255 + 201 - 6 * power(M[i][j], 2)) % 255;
                setfillcolor(RGB(r, g, b));
                solidroundrect(x - (blockw / 2) + 1, y + (blockw / 2) + 1, x + (blockw / 2), y - (blockw / 2), W / 100, W / 100);
                settextstyle((blockw/2), 0, _T("Consolas"));
                setbkmode(TRANSPARENT);
                settextcolor(RGB(119, 110, 101));
                RECT ADD = { x - (blockw / 2), y - (blockw / 4), x + (blockw / 2), y + (blockw / 2) };
                switch (M[i][j]) {
                    case 2: {drawtext(_T("2"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 4: {drawtext(_T("4"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 8: {drawtext(_T("8"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 16: {drawtext(_T("16"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 32: {drawtext(_T("32"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 64: {drawtext(_T("64"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 128: {drawtext(_T("128"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 256: {drawtext(_T("256"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 512: {drawtext(_T("512"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 1024: {drawtext(_T("1024"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 2048: {drawtext(_T("2048"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 4096: {drawtext(_T("4096"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 8192: {drawtext(_T("8192"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 16384: {drawtext(_T("16384"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 32768: {drawtext(_T("32768"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 65536: {drawtext(_T("65536"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 131072: {drawtext(_T("131072"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                    case 262144: {drawtext(_T("262144"), &ADD, DT_CENTER | DT_INTERNAL); break; }
                }
            }
        }
    }
}
int print(int size) {
    draw(size);
    lose = 1;
    system("cls");
    for (int k = 1; k <= (size * 11) + 1; k++) printf("-");
    cout << endl;
    for (int i = 1; i <= size; i++) {
        printf("|");
        for (int j = 1; j <= size; j++) {
            int tmp = M[i][j];
            if (tmp == 0)  lose = 0;
            if ((M[i][j] == M[i + 1][j] and i + 1 <= size) or
                (M[i][j] == M[i - 1][j] and i - 1 > 0) or
                (M[i][j] == M[i][j - 1] and j - 1 > 0) or
                (M[i][j] == M[i][j + 1] and j + 1 <= size))    lose = 0;
            if (tmp == win) {
                system("cls");
                cout << "You Win" << endl;
                cout << "score : " << score;
                return 1;
            }
            int l = 7;
            while (tmp /= 10)  l--;
            while (l--)  printf(" ");
            if (M[i][j] != 0)  printf("%d", M[i][j]);
            else    printf(" ");
            printf("  |");
        }
        cout << endl;
        for (int k = 1; k <= (size * 11) + 1; k++) cout << "-";
        cout << endl;
    }
    cout << "score : " << score << endl;
    cout << "r : restart a game" << endl;
    return 0;
}
void move_right(int size) {
    cout << "right" << endl;
    bool flag = 0;
    for (int i = 1; i <= size; i++) {
        for (int j = size; j >= 1; j--) {
            int tmp = next_nonzero_add(size, i, j, 0, -1);
            if (tmp != 0) {
                swap(M[i][j], M[i][tmp]);
                flag = 1;
            }
            if (M[i][j + 1] == M[i][j] and j != size and M[i][j] != 0) {
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag = 1;
                M[i][j + 1] *= 2;
                M[i][j] = 0;
                swap(M[i][j], M[i][next_nonzero_add(size, i, j, 0, -1)]);
            }
        }
    }
    if (flag)   add_in_map(size);
    cout << "right:down" << endl;
}
void move_left(int size) {
    cout << "left" << endl;
    bool flag = 0;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            int tmp = next_nonzero_add(size, i, j, 0, 1);
            if (tmp != 0 and tmp != size + 1) {
                swap(M[i][j], M[i][tmp]);
                flag = 1;
            }
            if (M[i][j - 1] == M[i][j] and j - 1 != 0 and M[i][j] != 0) {
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag = 1;
                M[i][j - 1] *= 2;
                M[i][j] = 0;
                swap(M[i][j], M[i][next_nonzero_add(size, i, j, 0, 1)]);
            }
        }
    }
    print(size);
    if (flag)   add_in_map(size);
    cout << "left:down" << endl;
}
void move_up(int size) {
    cout << "up" << endl;
    bool flag = 0;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            int tmp = next_nonzero_add(size, i, j, 1, 0);
            if (tmp != 0 and tmp != size + 1) {
                swap(M[i][j], M[tmp][j]);
                flag = 1;
            }
            if (M[i - 1][j] == M[i][j] and i - 1 != 0 and M[i][j] != 0) {
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag = 1;
                M[i - 1][j] *= 2;
                M[i][j] = 0;
                swap(M[i][j], M[next_nonzero_add(size, i, j, 1, 0)][j]);
            }
        }
    }
    if (flag)   add_in_map(size);
    cout << "up:done" << endl;
}
void move_down(int size) {
    cout << "down" << endl;
    bool flag = 0;
    for (int i = size; i >= 1; i--) {
        for (int j = 1; j <= size; j++) {
            int tmp = next_nonzero_add(size, i, j, -1, 0);
            if (tmp != 0 and tmp != size + 1) {
                swap(M[i][j], M[tmp][j]);
                flag = 1;
            }
            if (M[i + 1][j] == M[i][j] and i + 1 != 0 and M[i][j] != 0) {
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag = 1;
                M[i + 1][j] *= 2;
                M[i][j] = 0;
                swap(M[i][j], M[next_nonzero_add(size, i, j, -1, 0)][j]);
            }
        }
    }
    if (flag)   add_in_map(size);
    cout << "down:done" << endl;
}
int main() {
    initgraph(W, H, EW_SHOWCONSOLE);
    setbkcolor(RGB(250, 248, 239));
    cleardevice();
    int Size = 4;
    while (1) {
        setbkcolor(RGB(250, 248, 239));
        cleardevice();
        score = 0;
        lose = 0;
        times++;
        char o;
        system("cls");
        cout << "s:start" << endl << "e:exit" << endl;
        cin >> o;
        if (o == 'e') break;
        system("cls");
        init(Size);
        print(Size);
        while (1) {
            if (lose) {
                cout << "You lose" << endl;
                cout << "score : " << score << endl;
                cout << "press \"r\" to restart game" << endl;
                while (!KEY_DOWN(82));
                system("cls");
                break;
            }
            int pd = 0;
            if (KEY_DOWN(65)) {
                move_left(Size), pd = print(Size);//A 
                if (pd)  break;
                while (KEY_DOWN(65));
            }
            if (KEY_DOWN(68)) {
                move_right(Size), pd = print(Size);//D   
                if (pd)  break;
                while (KEY_DOWN(68));
            }
            if (KEY_DOWN(87)) {
                move_up(Size), pd = print(Size);//W  
                if (pd)  break;
                while (KEY_DOWN(87));
            }
            if (KEY_DOWN(83)) {
                move_down(Size), pd = print(Size);//S  
                if (pd)  break;
                while (KEY_DOWN(83));
            }
            if (KEY_DOWN(82)) {//R
                break;
            }
        }
    }
    return 0;
}