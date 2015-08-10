#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <conio.h>
#include "kolko_i_krzyzyk.h"


kolko_i_krzyzyk *plansza ;         //GLOBALNY WSKAZNIK NA PLANSZE

kolko_i_krzyzyk::kolko_i_krzyzyk(CGracz * Gracz)
{
	GS_StanGry = GS_NOT_START ;
	Aktualny_Gracz = Gracz ;
	for(int i = 0 ; i < 3 ; i++)
		for(int j = 0 ; j < 3 ; j++)
			F_Plansza[i][j] = FLD_EMPTY ;
}

bool kolko_i_krzyzyk::Rysuj()
{
	//JESLI GRA SIE NIE WLACZYLA, WYLACZAMY PROGRAM
	if(GS_StanGry == GS_NOT_START) 
	{ cout << "\n\n\n\n\n\n\n\n     Nastapil jakis blad" ; return false ;}

	//CZYSCIMY STARA ZAWARTOSC
	system("cls") ;

	cout << string(35, '*') 
		 << "\n*Grasz aktualnie w KOLKO I KRZYZYK*\n"
		 << "**********GRACZ VS GRACZ***********\n"
		 << string(35, '*') << "\n\n\n\n\n\n\n" ;


	//WYPISANIE PLANSZY
	int i = 0 ;             //ZMIENNA POTRZEBNA DO ODPOWIEDNIEGO WYPISANIA CYFR NA PLANSZY ORAZ WYPISANIA ZNAKU Z TABLICY
	for( int y = 0 ; y < 5 ; y++)
	{ 
		cout << setw(20) << right ;
		//WYPISANIE PRZERWY MIEDZY LINIAMI JESLI A == 1
		int a = y % 2 ;
		if(a == 1)
		{
			cout << setw(25) << right << "-----\n" ;
			continue ;
		}
		//WYPISANIE SYMBOLI X , O , LUB LICZBY
		for(int j = 0 ; j < 3 ; j++)
		{
			if(F_Plansza[i][j] == FLD_EMPTY)
			{
				if(j != 2) 
					cout << i * 3 + j + 1 << "|" ;
				else
					cout << i * 3 + j + 1 << "\n" ;
			}
			else
			{
				if(j != 2)
					cout << (F_Plansza[i][j] == FLD_CROSS ? 'X' : 'O') << "|" ;
				else 
					cout << (F_Plansza[i][j] == FLD_CROSS ? 'X' : 'O') << "\n" ;
			}
		}
			i++ ;
	}

	cout << "\n\n\n" ;

	//SPRAWDZANIE STANU GRY I WYPISANIE ODPOWIEDNIEGO KOMUNIKATU
	switch(GS_StanGry)
	{
		case GS_START :
			if( !cin.good())                                 //JESLI STRUMIEN CIN JEST W STANIE BLEDU
				cout << "Podales niewlasciwy znak!!!!!\n" ;

			cout << Aktualny_Gracz->Wypisz_imie() << " podaj nr pola gdzie zostanie wstawiony znak " 
				 << static_cast<char>(Aktualny_Gracz->Wypisz_znak()) << ".  Pole nr.: " ;
			break ;
		case GS_WIN :
			cout << Aktualny_Gracz->Wypisz_imie() << " WYGRAL!!" ;
			break ;
		case GS_DRAW :
			cout << "REMIS" ;
			break ;
	}
	return true ;
}

bool kolko_i_krzyzyk::Ruch(int pole , CGracz *Gracz1 , CGracz *Gracz2)
{
	//JESLI GRA SIE ZAKONCZYLA TO NIE MA SENSU WYKONYWANIE RUCHU
	if(GS_StanGry != GS_START) return false ;
	//SPRAWDZANIE POPRAWNOSCI
	if(!(pole <= 9 && pole >= 1)) return false ;

	int iY , iX ;
	//ZMIENNA KOLUMNY
	iY = (pole - 1) / 3 ;
	//ZMIENNA WIERSZA
	iX = (pole - 1) % 3 ;

	if(F_Plansza[iY][iX]  == FLD_EMPTY) 
		F_Plansza[iY][iX] = (static_cast<FIELD>(Aktualny_Gracz->Wypisz_znak())) ;
	else 
	{
		cout <<"\nPole jest zajete\n" ;
		return false ;
	}

	//SPRAWDZAMY PLANSZE CZY JEST WYGRANA , REMIS , CZY MOZNA DALEJ GRAC
	//ZMIENNA Z POLAMI DO WYGRANIA
	//1 WYMIAR MOZNA POMINAC, KOMPILATOR SAM TAM WPISZE WARTOSC
	//RESZTE TRZEBA WYPELNIC
	const int Line[][3][2] = { { {0,0} , {0,1} , {0,2} } ,  //POZIOM GORA
							   { {1,0} , {1,1} , {1,2} } ,  //POZIOM SRODEK
							   { {2,0} , {2,1} , {2,2} } ,  //POZIOM DOL

							   { {0,0} , {1,0} , {2,0} } ,  //PION LEWA
							   { {0,1} , {1,1} , {2,1} } ,  //PION SRODEK
							   { {0,2} , {1,2} , {2,2} } ,  //PION PRAWA

							   { {0,0} , {1,1} , {2,2} } ,  //PRZEKATNA \ (BACKSLASH)
							   { {2,0} , {1,1} , {0,2} } } ;//PRZEKATNA / (SLASH)

	//PETLA SPRAWDZAJACA WYGRANA
	FIELD F_Pole , F_InnePole ;
	int iZgodnePola ;

	//PRZEBIEG PO LINIACH
	for(int i = 0 ; i < 8 ; i++)
	{
		F_Pole = F_InnePole = FLD_EMPTY ;
		iZgodnePola = 0 ;
		//PRZEBIEG PO POLACH
		for(int j = 0 ; j < 3 ; j++)
		{
			F_Pole = F_Plansza[Line[i][j][0]][Line[i][j][1]] ;
			if(F_Pole != F_InnePole)
			{
				F_InnePole = F_Pole ;
				iZgodnePola = 1 ;
			}
			else iZgodnePola++ ;
		}

		//JESLI MAMY 3 IDENTYCZNE POLA I NIE SA TO POLA PUSTE TO ZNACZY ZE KTOS WYGRAL
		if(iZgodnePola == 3 && F_InnePole != FLD_EMPTY) 
		{
			GS_StanGry = GS_WIN ;
			return true ;
		}
	}

	//SPRAWDZAMY CZY JEST REMIS
	iZgodnePola = 0 ;
	for(int i = 0 ; i < 3 ; i ++)
		for(int j = 0 ; j < 3 ; j++)
			if(F_Plansza[i][j] != FLD_EMPTY)
				iZgodnePola++ ;

	if(iZgodnePola == 9)
	{
		//JESLI WSZYSTKIE POLA SA ZAPELNIONA I NIE SA TO POLA PUSTE
		//TO ZWRACAMY REMIS
		GS_StanGry = GS_DRAW ;
		return true ;
	}

	//JESLI NIE MA REMISU ANI WYGRANEJ TO ZMIENIAMY GRACZA
	Aktualny_Gracz = (Aktualny_Gracz == Gracz1 ? Gracz2 : Gracz1) ;
	return true ;
}