/****************************************************************************************************************************************************
**					                               SAKARYA ÜNİVERSİTESİ
**			                               BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				                               BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				                                PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI........:PROJE
**				ÖĞRENCİ ADI..........: İrem YALÇIN
**				ÖĞRENCİ NUMARASI.....: G171210026
**				DERS GRUBU...........: 2B
*********************************************************************************************************************************************************/

#include "pch.h"
#include <iostream>
#include<Windows.h>

using namespace std;


//Sahne Değişkenleri
const int widht = 100;
const int height = 25;
char sahne[height][widht];
char karakterler[256];

//Mermi Değişkenleri
const int maxMermiSayısı = 10;
const char mermiView = 219;
int mermiSayısı = -1;

//Mekik Değişkenleri
const int mekikBoyutu = 5;
const char mekikView = 219;

//Düşman Değişkenleri
const int maxDüşmanSayısı = 100;
int düşmanSayısı = 0;
int bayrak = 0;



struct uzayMekiğiParçaları
{
	int x;
	int y;
};
uzayMekiğiParçaları uzayMekiği[mekikBoyutu];

class Mermi
{
public:
	int x;
	int y;
	char view = mermiView;
};
Mermi mermi[maxMermiSayısı];

struct düşman
{
	int x, y;
	char düşmanview = 254;
};
düşman Düşman[maxDüşmanSayısı];

//Uzay Mekiği Fonksiyonları
void uzayMekiğiOluştur()
{
	uzayMekiği[0].x = 10;       uzayMekiği[0].y = 1;

	uzayMekiği[1].x = 11;       uzayMekiği[1].y = 2;

	uzayMekiği[2].x = 12;       uzayMekiği[2].y = 3;

	uzayMekiği[3].x = 13;       uzayMekiği[3].y = 2;

	uzayMekiği[4].x = 14;       uzayMekiği[4].y = 1;

}
void uzayMekiğiniÇiz()
{
	for (int i = 0; i < mekikBoyutu; i++)
	{

		int x = uzayMekiği[i].x;
		int y = uzayMekiği[i].y;

		if (x == 0)
		{
			for (int i = 0; i < mekikBoyutu; i++)
			{
				uzayMekiği[i].x++;
			}
		}

		if (x == height - 1)
		{
			for (int i = 0; i < mekikBoyutu; i++)
			{
				uzayMekiği[i].x--;
			}
		}

		else

			sahne[x][y] = mekikView;

	}
}


//Mermi Fonksiyonları
void mermiOluştur()
{
	mermiSayısı++;
	int x = uzayMekiği[2].x; 
	int y = uzayMekiği[2].y;
	
	mermi[mermiSayısı].x = x;
	mermi[mermiSayısı].y = y; 
	mermi[mermiSayısı].view = mermiView;
}
void mermiÇiz()
{
	for (int i = 0; i <= mermiSayısı; i++)
	{
		int x, y;
		x = mermi[i].x;
		y = mermi[i].y;

		if (y < widht - 1)
		{
			sahne[x][y] = mermi[i].view;
		}
		else
			mermi[i].view = ' ';		
	}
}
void mermiHareketEttir()
{
	for (int i = 0; i < mermiSayısı; i++)
	{
		mermi[i].y++;	
	}
}


//Diğer Fonksiyonlar
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hidecursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorinfo);
}
void karakterata(char karakterler[])
{
	for (int i = 0; i < 256; i++)
	{
		karakterler[i] = (char)(GetAsyncKeyState(i) >> 8);
	}
}
void karakterkontrol()
{
	karakterata(karakterler);
	
	if (karakterler['S'] != 0)
	{
		for (int i = 0; i < mekikBoyutu; i++)
		{
			uzayMekiği[i].x++;
		}
	}

	if (karakterler['W'] != 0)
	{
		for (int i = 0; i < mekikBoyutu; i++)
		{
			uzayMekiği[i].x--;
		}
	}
	
	if (karakterler['F'] != 0)
	{
		mermiOluştur();
	}

	else
		return;
}


//Sahne Fonksiyonları
void sahneSil()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			sahne[i][j] = ' ';
		}
	}
}
void sahneSınırlarınıÇiz()
{
	for (int i = 0; i < height; i++)
	{
		sahne[i][0] = 219;
		sahne[i][widht - 1] = 219;
	}

	for (int j = 0; j < widht; j++)
	{
		sahne[0][j] = 219;
		sahne[height - 1][j] = 219;
	}
}
void sahneÇiz()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			cout << sahne[i][j];
		}
		cout << endl;
	}
}

//Düşman Fonksiyonları
void düşmanOluştur()
{
	düşmanSayısı++;
	int x;  x = rand() % 20 + 2;
	Düşman[düşmanSayısı - 1].x = x;
	Düşman[düşmanSayısı - 1].y = widht - 2;

}
void düşmanÇiz()
{
	int x, y;
	for (int i = 0; i < düşmanSayısı; i++)
	{
		x = Düşman[i].x;
		y = Düşman[i].y;

		if (y > 2)
		{
			
/*			for(int j=0;j<mermiSayısı;j++) 
			{
				int mermiX, mermiY;
				mermiX = mermi[j].x;
				mermiY = mermi[j].y;
				
				if((mermiX==x || mermiX==x+1) && mermiY=y-1)
				{
					mermi[j].view = ' ';
					Düşman[i].düşmanview = ' ';
					sahne[x][y] = Düşman[i].düşmanview;
					sahne[x][y + 2] = Düşman[i].düşmanview;
					sahne[x + 1][y + 2] = Düşman[i].düşmanview;
					sahne[x + 1][y + 2] = Düşman[i].düşmanview;
				}

				else
				{
					sahne[x][y] = Düşman[i].düşmanview;
					sahne[x][y + 2] = Düşman[i].düşmanview;
					sahne[x + 1][y] = Düşman[i].düşmanview;
					sahne[x + 1][y + 2] = Düşman[i].düşmanview;
				}
			}*/	

			sahne[x][y] = Düşman[i].düşmanview;
			sahne[x][y + 2] = Düşman[i].düşmanview;
			sahne[x + 1][y] = Düşman[i].düşmanview;
			sahne[x + 1][y + 2] = Düşman[i].düşmanview;
		}
		else
		{
			Düşman[i].düşmanview = ' ';
			sahne[x][y] = Düşman[i].düşmanview;
			sahne[x][y + 2] = Düşman[i].düşmanview;
			sahne[x + 1][y + 2] = Düşman[i].düşmanview;
			sahne[x + 1][y + 2] = Düşman[i].düşmanview;
		}
	}
}
void düşmanıHareketEttir()
{
	for (int i = 0; i < düşmanSayısı; i++)
	{
		Düşman[i].y--;
		bayrak++;
	}
	if (bayrak % 40 == 0)
	{
		if (bayrak == 0) { return; }
		else
		{
			/*sahne[0][0] = 'a';*/
			düşmanOluştur();
		}
	}
	else
		return;
}



int main()
{
    uzayMekiğiOluştur();
	düşmanOluştur();

	while (true)
	{
		sahneSil();
		sahneSınırlarınıÇiz();
		karakterkontrol();
		uzayMekiğiniÇiz();
		mermiÇiz();
		mermiHareketEttir();
		düşmanÇiz();
		düşmanıHareketEttir();

		gotoxy(0, 0);
		sahneÇiz();
		Sleep(10);
	}
}
