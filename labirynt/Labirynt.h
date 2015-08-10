#ifndef LABIRYNT_H
#define LABIRYNT_H

#include <string>
#include <vector>
#include <dirent.h>


using namespace std ;


class Labirynt
{
public:

	//STAN GRY
	enum MODE
	{
		M_EXIT	,
		M_WIN	,
		M_EDIT	,
		M_GAME
	}TRYB ;

	//ZMIENNA PRZECHOWUJACA ZNAKI NA PLANSZY
	enum SINGS
	{
		GRACZ   = '$' ,
		TLO     = ' ' ,
		SCIANA1 = '|' ,
		SCIANA2 = '-' ,
		META    = '@' ,
		EDIT    = '#' ,
		CHECK   = '*'
	};

	//KONSTRUKTOR
	Labirynt() : iLicznik(0) , TRYB(M_EXIT) {} 

	//WYNKCJA RYSUJACA PLANSZE
	bool Narysuj() ;
	
	//FUNKCJA WYKONUJACA RUCH GRACZA
	bool Ruch() ;

	//ROBIMY NOWA MAPE
	bool NEW() ;

	//EDYCJA STAREJ MAPY
	bool EDITION() ;
	
	//SPRAWDZA CZY MOZNA UKONCZYC LABIRYNT
	bool CHECKS() ;

	//KASUJ MAPE
	bool DELETE_MAP() ;

	//POROWNANIE POZYCJI GRACZA I METY
	bool Koniec()
	{
		if(sGracz.x == sMeta.x && sGracz.y == sMeta.y)
			return true ;
		return false ;
	}

	//WYPISUJE PLIKI Z FOLDERU ORAZ WYBIERA
	bool Wypisz_pliki(vector <string> &SPIS , int &wyb) ;

private:

	//STRUKTURA PRZECHOWUJACA POZYCJE GRACZA, METY, WSKAZNIKA EDYCJI NA PLANSZY
	struct Pozycja
	{
		int x ;
		int y ;
	}sGracz , sWskaznik , sMeta ;

	int iLicznik ;           //ZMIENNA PRZECHOWUJACA ILOSC RUCHOW GRACZA NA PLANSZY

	//STRUKTURA Z PLANSZA I JEJ NAZWA
	struct sDanePlanszy
	{
		char cNazwaPlanszy[100]  ;
		SINGS PLANSZA [20][20]  ;
	}sPlansza , sDodatkowa ;

	//POBIERANIE NAZWY PLIKU
	bool NazwaPliku() ;

	//POBIERANIE DANYCH O MAPIE (POLA ITP.)
	bool OtworzPlik() ;

};

#endif