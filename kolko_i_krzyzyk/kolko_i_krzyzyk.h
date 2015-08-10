#ifndef KOLKO_KRZYZYK_H
#define KOLKO_KRZYZYK_H

using namespace std ;

//ZMIENNA STANU GRY
enum GAME_STATE { GS_NOT_START ,
				  GS_START     ,
				  GS_WIN       ,
				  GS_DRAW      } ;
//ZNIENNA ZNAKU
enum SINGS { SNG_CROSS  = 'X' ,
			 SNG_CIRCLE = 'O' } ;

class CGracz
{
public:

	//WYPISZ ZNAK
	SINGS Wypisz_znak(void) { return Znak ;} 
	//WYPISZ IMIE
	string Wypisz_imie(void) { return Imie ;} 
	//KONSTRUKTOR
	CGracz(string nazwa , SINGS znak) : Imie(nazwa) , Znak(znak) {}

private:

	string Imie ;
	SINGS Znak ;
};

class kolko_i_krzyzyk
{
public:

	GAME_STATE GS_StanGry ;

	//KONSTRUKTOR
	kolko_i_krzyzyk(CGracz * Gracz) ;

	//FUNKCJE :
	//FUNKCJA RYSUJACA PLANSZE I WYPISUJACA ODPOWIEDNI KOMUNIKAT
	bool Rysuj(void) ;
	//FUNKCJA WYKONUJACA RUCH I WPRAWDZAJACA WYGRANA
	bool Ruch(int pole , CGracz *Gracz1 , CGracz *Gracz2) ;

private:

	//ZMIENNA WYPELNIENIA PLANSZY
	enum FIELD { FLD_EMPTY  = 0 ,
				 FLD_CROSS  = SNG_CROSS  ,
				 FLD_CIRCLE = SNG_CIRCLE } ;
	//PLANSZA
	FIELD F_Plansza[3][3] ;
	//DANE DO PRZECHOWYWANIA AKTUALNEGO GRACZA
	CGracz *Aktualny_Gracz ;
};

void Gra();

#endif