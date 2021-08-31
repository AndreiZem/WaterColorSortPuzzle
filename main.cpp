#include <iostream>
#include <fstream>
#include <vector>
#include <set>
//#include "windows.h"
#include <string>
#include <unistd.h>

#define M_K 14

using namespace std;

unsigned char kolb;

struct XYkol {
    unsigned int x;
    unsigned int y;
};

XYkol XYkolba[M_K];

struct T {
    int step; // из какого положения
    unsigned char pole[M_K][4]; // поле
};

struct Tt {
    unsigned short pole[M_K]; // поле
};

bool operator<(const Tt& lhs, const Tt& rhs)
{
    int i = 0;
    while ((lhs.pole[i] == rhs.pole[i]) && (i < M_K - 1)) i++;
    return (lhs.pole[i] < rhs.pole[i]);
}


set <Tt> Mem;
vector<T> WtCl(1);

int tet_st;
int pos_st;

void vivod(int n)
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < kolb; j++)
        {

            if (WtCl[n].pole[j][i] == 0) cout << "(  ) ";
            else
            {
                //\x1b[31mTest\x1b[0m
                cout << "(";
              if   (WtCl[n].pole[j][i] <10) cout << "0";
                cout << (int) WtCl[n].pole[j][i];


                /*
                if (WtCl[n].pole[j][i] <= 7)
                    cout << "\x1b[" << 40 + WtCl[n].pole[j][i] << "m \x1b[0m";
                else
                    cout << "\x1b[30;" << 40 + WtCl[n].pole[j][i] - 6 << "m@\x1b[0m";
*/

                cout << ") ";

            }


        }
        cout << endl;
    }
    return;
}



void klikscreen(int n, int nn)
{
    for (int i = 0; i < kolb; i++)
        for (int j = 0; j < 4; j++)
        {
            if (WtCl[n].pole[i][j] != WtCl[nn].pole[i][j])
                if (WtCl[nn].pole[i][j] == 0) // отсюда взяли (первый клик)
                {
//                    string sss = "c://Users//PRESS//source//repos//WaterColorSortPuzzle//WaterColorSortPuzzle//adb shell input tap ";
                    string sss = "adb shell input tap ";
                 sss+= to_string(XYkolba[i].y);
                 sss += " ";
                 sss +=  to_string(XYkolba[i].x+60);
//                 sss += " > fil.txt";
                    cout << "U3:" << i ;
                 system(sss.c_str());
//                    usleep(300);
                    j = 5; i = kolb;
                }
        }

    /*

    #include <unistd.h>
//...
#include <unistd.h>
sleep(5);

    */


    for (int i = 0; i < kolb; i++)
        for (int j = 0; j < 4; j++)
        {
            if (WtCl[n].pole[i][j] != WtCl[nn].pole[i][j])
                if (WtCl[nn].pole[i][j] != 0) // куда залить (второй клик )
            {
                    string sss = "adb shell \"input tap ";
//                    string sss = "c://Users//PRESS//source//repos//WaterColorSortPuzzle//WaterColorSortPuzzle//adb shell input tap ";
                    sss += (to_string(XYkolba[i].y ));
                    sss += " ";
                    sss += to_string(XYkolba[i].x +60 );
//                    sss += "; input tap ";
//                    sss += (to_string(XYkolba[i].y ));
//                    sss += " ";
//                    sss += to_string(XYkolba[i].x +60 );
                    sss += "\"";
 //                   sss += " > fil.txt";

                    cout << sss;
                    cout << " -> B:" << i << endl;

                    system(sss.c_str());

    //                 system(sss.c_str());

   //             usleep(300);

                j = 5; i = kolb;
            }
        }



    return;
}

int proverka(int n)
{
    for (int i = 0; i < kolb; i++) {
        if ((WtCl[n].pole[i][0] != WtCl[n].pole[i][1]) ||
            (WtCl[n].pole[i][0] != WtCl[n].pole[i][2]) ||
            (WtCl[n].pole[i][0] != WtCl[n].pole[i][3]))
            return 0;

    }
    return 1;
}

int SortStep(int n)
{
    Tt buff;
    for (int i = 0; i < kolb; i++) {
        for (int j = 0; j < kolb; j++) {
            if ((i != j) && // не одна и таже колба
                (WtCl[n].pole[i][3] != 0) && // первая колба не пустая
                (WtCl[n].pole[j][0] == 0) // во второй колбе есть место
                )
            {
                // сколько есть места и какой цвет можно лить
                int mesto = 1;
                while ((mesto < 4) && (WtCl[n].pole[j][mesto] == 0)) mesto++;

                int cvet;
                if (mesto == 4) cvet = 0;
                else cvet = WtCl[n].pole[j][mesto]; // цввет на который лить, 0 - любой
                // если колба пустая проверить были ли до нее пустые колбы если да то ее не использовать

                int z = 1;
                if (cvet == 0)
                    for (int k = (j - 1); k >= 0; k--)
                        if ((WtCl[n].pole[k][0] == 0) &&
                            (WtCl[n].pole[k][1] == 0) &&
                            (WtCl[n].pole[k][2] == 0) &&
                            (WtCl[n].pole[k][3] == 0))
                            z = 0;//break;
                if (z == 1) // это не первая пустая колба пропускаем ее

                {
                    // сколько цвета в колбе
                    int Skolko = 0;
                    int Pusto = 0;
                    // пропускаем пустоту если колба не полная
                    while (WtCl[n].pole[i][Pusto] == 0) Pusto++;
                    int Cvet = WtCl[n].pole[i][Pusto];
                    // сколько цвета можно перелить
                    while (((Pusto + Skolko) < 4) && Cvet == WtCl[n].pole[i][Pusto + Skolko]) Skolko++;

                    if (((cvet == 0) || (cvet == Cvet)) && (Skolko < 4)/*не передвигать целую залитую*/)
                    {
                        if (mesto < Skolko) Skolko = mesto;

                        // можно перелить
 //                       cout << i << " -> " << j << " (";
 //                       for (int t = 0; t < Skolko; t++)  cout << (int)Cvet;
 //                       cout << ")" << endl;

                        // добовляем поле
                        T buffer;
                        buffer.step = n;
                        // копируем
                        for (int a = 0; a < M_K; a++)
                            for (int b = 0; b < 4; b++)
                                buffer.pole[a][b] = WtCl[n].pole[a][b];
                        // переливаем;
                        for (int a = Skolko + Pusto - 1; a >= 0; a--)   buffer.pole[i][a] = 0;
                        for (int a = mesto - 1; a >= mesto - Skolko; a--)   buffer.pole[j][a] = Cvet;


                        // проверка если есть такой элемент то не добовлять

                        for (z = 0; z < M_K; z++)
                            buff.pole[z] = (buffer.pole[z][0] << 12) | (buffer.pole[z][1] << 8) | (buffer.pole[z][2] << 4) | buffer.pole[z][3];
                        // отсортируем буфер ( для уменьшения одинаковых вариантов

                        int d = 1;
                        unsigned short dd;
                        while (d)
                        {
                            d = 0;
                            for (z = 0; z < M_K - 1; z++)
                                if (buff.pole[z] < buff.pole[z + 1])
                                {
                                    dd = buff.pole[z + 1];
                                    buff.pole[z + 1] = buff.pole[z];
                                    buff.pole[z] = dd;
                                    d = 1;
                                }
                        }

                        int aaa = Mem.size();
                        Mem.insert(buff);
                        int aaa1 = Mem.size();

                        if (aaa != aaa1) WtCl.push_back(buffer);

                        if (proverka(WtCl.size() - 1)) return 0;

                    }
                }
            }
        }
    }
    return 1;
}


int koord(int i, int j) {
    return (i * 720 + j) * 4 + 12;
};

unsigned char conv(int i)
{
    if (i == 0x76) return 2;
    if (i == 0x52) return 6;
    if (i == 0x0c) return 8;
    if (i == 0xe8) return 9;
    if (i == 0x64) return 12;
    if (i == 0xe7) return 11;
    if (i == 0xf1) return 3;
    if (i == 0x45) return 4;
    if (i == 0xc0) return 1;
    if (i == 0x61) return 7;
    if (i == 0x7b) return 10;
    if (i == 0x72) return 5;


    return 0;

}

unsigned char sap[54] = {
    0x42,0x4d,0x36,0x30,0x2a,0x00,0x00,0x00,  0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
    0x00,0x00,0xd0,0x02,0x00,0x00,0x00,0x05,  0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
    0x00,0x00,0x00,0x30,0x2a,0x00,0xc4,0x0e,  0x00,0x00,0xc4,0x0e,0x00,0x00,0x28,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00
};




int main()
{
    cout << "WatterSort!\n";
/*
    HDC hdc = GetDC(GetConsoleWindow());
    for (int x = 0; x < 256; ++x)
        for (int y = 0; y < 256; ++y)
            SetPixel(hdc, x, y, RGB(127, x, y))
*/
    // делаем скриншот телефоена
// for Win
//ddfdd:
//system("c://Users//PRESS//source//repos//WaterColorSortPuzzle//WaterColorSortPuzzle//adb exec-out screencap > screen.bbb");


// for Linx
system("adb exec-out screencap > screen.bbb");



// из сырого изоьражения делаем bmp (только для просмотра)
    unsigned char i_n;
    vector <unsigned char> vec;
    ifstream input("screen.bbb", std::ios::binary | ios::in);

    if (!input) {

  //      goto ddfdd;

        return 1;
    }
    for (int i = 0; !input.eof(); i++)
    {
        input.read((char*)&i_n, 1);
        vec.push_back(i_n);
    }
    input.close();
    T cv;
    cv.step = -1;


    for (int a = 0; a < M_K; a++)
        for (int b = 0; b < 4; b++)
            cv.pole[a][b] = 0;


    int nomKol = 0;

    // находим колбы на экране телефона

    for (int i = 0; i < 1200; i++)
    {
        for (int j = 0; j < 700; j++)
        {
            int a = 0;
            int zz = koord(i, j);
            while ((vec[zz + a] & 0xf0) == 0xc0)
                if (vec[zz + (++a)] == 0xff) a++;

            if (a > 200)
            {
                XYkolba[nomKol].x = i;
                XYkolba[nomKol].y = j + a / 8;
 //               cout << "kolba x=" << i << " y=" << j + a / 8 << " a=" << a << endl;
                for (int z = zz; z < zz + a; z++) // отмечаем горлышко колбы
                    if (vec[z] != 0xff) vec[z] = 0xff;

                int Delta = 70; // расстояние между кубиками
                for (int z = 0; z < 4; z++)
                    cv.pole[nomKol][z] = conv(vec[koord(i + a / 6 + (z * Delta), XYkolba[nomKol].y)]);

              for (int z = i; z < i+a ; z++) // полоска на колбе по центру
                {
                /*

                cout << hex << static_cast<int>(vec[koord(z + 40, jj)]) << "."
                    << hex << static_cast<int>(vec[koord(z + 40 + 70, jj)]) << "."
                    << hex << static_cast<int>(vec[koord(z + 40 + 70 + 70, jj)]) << "."
                    << hex << static_cast<int>(vec[koord(z + 40 + 70 + 70 + 70, jj)]) << " ";
                 */


                vec[koord(z , XYkolba[nomKol].y)] = 255;
                vec[koord(z , XYkolba[nomKol].y) + 1] = 255;
                vec[koord(z,  XYkolba[nomKol].y) + 2] = 255;


                }



                nomKol++;
               // cout << dec << endl;

            }


        }
    }

    // определяем света в колбах





    vector <unsigned char> nvec;
    nvec.resize(720 * 1280 * 3 + 54);
    // копируем шапку






    int i;

    for (i = 0; i < 54; i++) nvec[i] = sap[i];
    int ii = 12;

    for (int i = 1279; i>=0; i--)
    for (int j = 0; j < 720 ; j++)
    {
        int r = vec[ii++];
        int g = vec[ii++];
        int b = vec[ii++];

        nvec[(i * 720 + j) * 3 +54] = b;
        nvec[(i * 720 + j) * 3 +55] = g;
        nvec[(i * 720 + j) * 3 +56] = r;
        ii++;
    }


    std::ofstream binary_file("fil.bmp", std::ios::out | std::ios::binary);
    binary_file.write((char*)&nvec[0], nvec.size());
    binary_file.close();



kolb = nomKol; // количество колб



    WtCl[0] = cv;

    /*
        WtCl[0] = { -1, //spep
       {{ 1,  2,  3,  4},
        { 3,  5,  6,  1},
        { 7,  4,  3,  6},
        { 7,  8,  2,  5},
        { 8,  9,  1,  10},
        { 5,  10, 9,  5},
        { 3,  2,  8,  4},
        { 11, 6,  9,  4},
        { 8,  9,  11, 7},
        { 10, 1,  11, 2},
        { 10, 7,  11, 6},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0}}
        };

    */

    cout << "!!!!WatterSort!\n";



    unsigned int tet_st = 0;

    while (SortStep(tet_st))
    {
        tet_st++;
        if (tet_st >= WtCl.size())
        {
            cout << "net rehenia";
            return 1;
        }
    }

    // вывод результата
    vector<int> shag;
    int pos_st = WtCl.size() - 1;
    while (pos_st >= 0)
    {
        shag.push_back(pos_st);
        pos_st = WtCl[pos_st].step;
    }

    int step = 0;
    for (int x = shag.size() - 1; x > 0; --x)
    {
        cout << "Step " << step << endl;
        vivod(shag[x]);

        klikscreen(shag[x], shag[x-1]);

        step++;
    }
    vivod(shag[0]);




}

