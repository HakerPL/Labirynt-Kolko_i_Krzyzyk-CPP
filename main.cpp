
#include <iomanip>									 //DO WYKOZYSTYWANIA MANIPULATOROW
#include <iostream>									 //STANDARDOWA BIBLIOTEKA STRUMIENI WYJSCIA/WEJSCIA
#include <conio.h>									//DLA getch I kbhit
#include <string>									//DLA KLASY STRING                            
//SZABLON vector PRZECHOWUJE DANE W TABLICY NIESKONCZONEJ (SAMA SIE POWIEKSZA)
#include <vector>
#include "labirynt\Labirynt.h"						//KLASA LABIRYNT
#include "kolko_i_krzyzyk\kolko_i_krzyzyk.h"		//KLASA KOLKO KRZYZYK
#include <Moje\Menu.h>								//BIBLIOTEKA MENU


using namespace std ;
using namespace std::tr1 ;
				
					//FUNKCJE DLA LABIRYNTU
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//DEKLARACJA GLOBALNA OBIEKTU LABIRYNT
Labirynt labirynt ;

//ZACZYNAMY GRE
void Start()
{
	while(labirynt.Narysuj())
	{
		if(labirynt.TRYB == Labirynt::M_GAME)
			labirynt.Ruch() ;
		if(labirynt.Koniec()) labirynt.TRYB = Labirynt::M_WIN ;
		if(labirynt.TRYB == Labirynt::M_EXIT)
			labirynt.TRYB = Labirynt::M_GAME ;
	} 
}

//FUNKCJE POMOCNE W MENU
void L_NEW()
{
	labirynt.NEW() ;
}
void L_EDI()
{
	labirynt.EDITION () ;
}
void L_DEL()
{
	labirynt.DELETE_MAP() ;
}
//MENU EDYCJI
void Edition_Map()
{
	//TWORZYMY OBIEKT cMenu KTORY PRZECHOWUJE FUNKCJE void(void)
	cMenu< void(void) > Menu2 ;
	//DODAJEMY DANE
	//1 EXIT
	Menu2.Dane.Nazwa   = "EXIT" ;
	Menu2.Dodaj() ;

	//2 NOWA MAPA
	Menu2.Dane.Nazwa   = "NOWA MAPA" ;
	Menu2.Dane.funkcja = L_NEW ;
	Menu2.Dodaj() ;

	//3 EDYCJA STAREJ MAPY
	Menu2.Dane.Nazwa   = "EDYCJA STAREJ MAPY" ;
	Menu2.Dane.funkcja = L_EDI ;
	Menu2.Dodaj() ;

	//4 KASUJ MAPE
	Menu2.Dane.Nazwa   = "KASUJ NIEPOTRZEBNA MAPE" ;
	Menu2.Dane.funkcja = L_DEL ;
	Menu2.Dodaj() ;

	//POKI NIE ZOSTANIE WYBRANE WYJSCIE PROGRAM BEDZIE DZIALAC
	while(Menu2.wypisz()) {}
}

//GLOWNE MENU LABIRYNTU
void Lab()
{
	//TWORZYMY OBIEKT cMenu KTORY PRZECHOWUJE FUNKCJE void(void)
	cMenu< void() > Menu1 ;
	//DODAJEMY DANE
	//1 EXIT
	Menu1.Dane.Nazwa   = "EXIT" ;
	Menu1.Dodaj() ;

	//2 ROZPOCZECIE GRY
	Menu1.Dane.Nazwa   = "START" ;
	Menu1.Dane.funkcja = Start ;
	Menu1.Dodaj() ;

	//3 EDYCJA MAP
	Menu1.Dane.Nazwa   = "EDYCJA" ;
	Menu1.Dane.funkcja = Edition_Map ;
	Menu1.Dodaj() ;

	//POKI NIE ZOSTANIE WYBRANE WYJSCIE PROGRAM BEDZIE DZIALAC
	while(Menu1.wypisz()) {}
}

					//FUNKCJE DLA KOLKO I KRZYZYK
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
extern kolko_i_krzyzyk *plansza ;         //GLOBALNY WSKAZNIK NA PLANSZE W INNYM PLIKU

int sprawdz()
{
	int wynik ;
	do
	{
		cin.clear()  ;                       //CZYSZCZENIE FLAG BLEDU JESLI COS ZLE PODALISMY
        cin.sync()   ;                       //CZYSZCZENIE BUFORA STRUMIENIA Z POZOSTALYCH ZNAKOW

		cin >> wynik ;

		if (cin.good()) break ;              //JESLI WSZYSTKO GRA PRZERYWAMY PETLE

		plansza->Rysuj() ;					 //NARYSUJ JESZCZE RAZ PLANSZE Z ODPOWIEDNIM KOMUNIKATEM

	}while(1) ;

	return wynik ;
}

void Gra()
{
	bool Kontynuowac = true ;
	while(Kontynuowac)
	{
		string Imie1 , Imie2 ;
		cout << "\n\n\n\n\n\n\n\n" << setw(25) << "Podaj imie Gracza nr 1\n" ;
		cin  >> Imie1 ;
		cout << "\n\n" << setw(25) << "Podaj imie Gracza nr 2\n" ;
		cin  >> Imie2 ;

		//URUCHAMIANIE FUNKCJI LOSUJACEJ
		srand (static_cast<unsigned int>(time(NULL))) ;
		//LOSUJEMY ZNAKI
		SINGS znak1 , znak2 ;
		//rand DOSTAJE CZAS OD srand I SPRAWDZA CZY ZOSTANIE RESZTA 1 CZY NIE 0
		int Rand = (rand() % 2 ) ;
		znak1 = (Rand == 1 ? SNG_CROSS  : SNG_CIRCLE) ;
		znak2 = (Rand == 1 ? SNG_CIRCLE : SNG_CROSS ) ;

		CGracz Gracz1(Imie1 , znak1) ;
		CGracz Gracz2(Imie2 , znak2) ;

		//LOSUJEMY ROZPOCZYNAJACEGO GRACZA
		CGracz *KtoZaczyna = ((rand() % 2) == 0 ? &Gracz1 : &Gracz2) ;

		kolko_i_krzyzyk Plansza(KtoZaczyna) ;

		plansza = &Plansza ;                    //PRZYPISANIE WSKAZNIKOWI ADRES Plansza

		Plansza.GS_StanGry = GS_START ;
		for(;;)
		{
			Plansza.Rysuj() ;
			//JESLI GRA SIE SKONCZYLA TO PRZERYWAMY PETLE
			if(Plansza.GS_StanGry != GS_START) break ;

			//URUCHAMIAMY FUNKCJE RUCH
			Plansza.Ruch(sprawdz() , &Gracz1 , &Gracz2) ;
		}
		
		cout << "\n\n\nWlaczyc od nowa gre ?? (1-TAK // 2-NIE)\n" ;
		int    aaa ;
		cin >> aaa ;
		if(aaa == 2) Kontynuowac = false ;
	}
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

int main()
{
	//TWORZYMY OBIEKT cMenu KTORY PRZECHOWUJE FUNKCJE void(void)
	cMenu< void() > Menu0 ;
	//DODAJEMY DANE
	//1 EXIT
	Menu0.Dane.Nazwa   = "EXIT" ;
	Menu0.Dodaj() ;

	//2 KOLKO I KRZYZYK
	Menu0.Dane.Nazwa   = "KOLKO I KRZYZYK" ;
	Menu0.Dane.funkcja = Gra ;
	Menu0.Dodaj() ;

	//3 LABIRYNT
	Menu0.Dane.Nazwa   = "LABIRYNT" ;
	Menu0.Dane.funkcja = Lab ;
	Menu0.Dodaj() ;

	//POKI NIE ZOSTANIE WYBRANE WYJSCIE PROGRAM BEDZIE DZIALAC
	while(Menu0.wypisz()) {}

	return 0 ;
}