#ifndef MENU_H
#define MENU_H

#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
//DLA SZABLONU function
//który potrafi przechowywaæ, kopiowaæ oraz wywo³ywaæ zarówno funkcje, wyra¿enia lambda jak i metody klas.
#include <functional> 

using namespace std ;


//KLASA MENU.   WYPISUJE MENU I URUCHAMIA ODPOWIEDZNIA KLASE
template< class Typ > class cMenu
{
	public:

		struct sDane                      //STRUKTURA DO PRZECHOWYWANIA NAZWY I FUNKCJI W MENU
		{
			string Nazwa ;
			function < Typ > funkcja ; //function BEDZIE PRZECHOWYWAC ADRES FUNKCJI
		}Dane ;
		
		bool wypisz() ;					  //FUNKCJA WYPISUJACA MENU

		void Dodaj() 
		{
			vecWypis.push_back(Dane) ;
		}

		//KONSTRUKTOR
		cMenu() : pozycja(0)  , prawda(true) { } ;

	private:

		int pozycja ;                    //ZMIENNA DO WYBRANIA ODPOWIEDNIEJ FUNKCJI
		bool prawda ;					 //ZMIENNA DO WYJSCIA Z PETLI WYPISUJACEJ

		vector < sDane > vecWypis ;      //vector PRZECHOWUJACY DANE ZE STRUKTURY
};

template< class Typ >
bool cMenu<Typ>::wypisz()
{
	while(prawda)
	{
		cout << string(26,'*') 
			 << "\n****Program treningowy****\n"
			 << "*Poruszamy sie strzalkami*\n"
			 << "**A zatwierdzamy ENTEREM**\n"
			 << string(26,'*') << "\n\n" ;

		//WYPISANIE MENU
		for( int i = 0 ; i < (static_cast<int>(vecWypis.size())) ; i++ )  //i MNIEJSZE OD ILOSCI ELEMENTOW W vector
		{
			if ( i == pozycja )
				cout << setw(20) << left << vecWypis[i].Nazwa << "<------\n" ;
			else
				cout << setw(20) << left << vecWypis[i].Nazwa << "\n" ;
		}
		

		//POBIERANIE ZNAKU Z KLAWIATURY
		int znak = getch() ;

		//WYBIERANIE ODPOWIEDNIEJ STRZALKI
		switch(znak)
		{
			case 224:            //ZNAK SPECJALNY
				if( kbhit() )    //FUNKCJA SPRAWDZAJACA CZY JEST ZNAK SPECJALNY
				{
					znak = getch();
					switch( znak )
					{
						case 72: //STRZALKA W GORE
							pozycja-- ;
							if(pozycja < 0) pozycja = 0 ;
							break ;
						case 80: //STRZALKA W DOL
							pozycja++ ;
							if(pozycja >= (static_cast<int>(vecWypis.size()))) pozycja = (vecWypis.size()) - 1 ;
							break ;
						default:
							break ;
					}
				}
				break ;
			case 13:
				//JESLI POZYCJA = 2 (WYJSCIE) TO KONCZYMY
				if(pozycja==0) { prawda = false ; return false ;}
				//JESLI POZYCJA = 0 LUB 1 TO URUCHAMIAMY ODPOWIEDZNIA FUNKCJE
				if(pozycja < (static_cast<int>(vecWypis.size())) && pozycja > 0) { system("cls") ; vecWypis[pozycja].funkcja() ; }
				break;
			default:
				break;
		} //SWITCH ZNAK
		system("cls") ;     //CZYSZCZENIE EKRANU
	} //WHILE
	return true ;
} 

#endif