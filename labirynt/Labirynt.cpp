#include <iostream>
#include <string>
#include <vector>
#include <iomanip>			//MANIPULATORY
#include <conio.h>
#include <fstream>			//OPERACJE NA PLIKACH
#include <ctime>			//BIBLIOTEKA CZASU
#include <dirent.h>			//BIBLIOTEKA PRZESZUKIWANIA PLIKOW
#include <cstdio>			//SRAND    STRCPY
#include "Labirynt.h"
#include <Moje\Menu.h>		//MENU

using namespace std ;

extern Labirynt::MODE TRYB ;

//FUNKCJA CENTRUJACA WPISANY TEKST
string center(string input, int width) 
{ 
	input = string((width - input.length()) / 2, ' ') + input + string((width - input.length()) / 2, ' ') ;
    return input ;
}

//SPRAWDZA POPRAWNOSC cin I ZWRACA LICZBE -1
bool zab_cin(int & wyb)
{
	do
	{
		cin.clear() ;	//CZYSCI FLAGI BLEDU
		cin.sync()  ;	//CZYSCI BUFOR Z POZOSTALYCH ZNAKOW

		cin  >> wyb ;
		if(cin.good()) break;
		cout << "\nTO NIE CYFRA.\n\tNUMER: " ;
	}while(true) ;

	wyb-- ;
	return true ;
}

int Random(int nMin , int nMax)
{
	return rand() % nMax + nMin;
}

bool Labirynt::NazwaPliku()
{
	//URUCHOMIENIE LOSOWANIA LICZBY
	srand ( static_cast<unsigned int>(time(NULL)) ) ;

	vector <string> NazwyPlikow ;

	DIR* pdir = NULL ;	//WSKAZNIK SCIEZKI
	struct dirent * ps_dirent = NULL ;	//readdir ZWRACA STRUKTURE dirent

	pdir = opendir ("Maps") ; //OTWIERAMY SCIEZKE DO PLIKOW

	if(pdir)	//JESLI UDALO SIE OTWOZYC SCIEZKE
	{
		while(ps_dirent = readdir(pdir))	//JESLI COS JEST TO CZYTAJ
		{
			//strstr PRZESZUKUJE 1 const char * I SZUKA W NIM 2 const char * ZWRACA const char * LUB NULL JESLI NIC NIE ZNAJDZIE
			if(!(strstr(ps_dirent->d_name , "adi") == NULL))  
				NazwyPlikow.push_back(ps_dirent->d_name) ;
		}

		if(NazwyPlikow.empty())
		{
			cout << "\n\n\n\tW PLIKU \"MAPS\" NIE MA MAP" ;
			getch() ;
			return false ;
		}
	}
	else 
	{
		cout << "\n\nNie mozna otworzyc sciezki do Maps. Plik moze nie istniec lub byc poza glownym folderem.\n"
			 << "Tworze folder \"Maps\" w glownym folderze " ;
		system("mkdir Maps") ;
		getch() ;
		return false ;
	}

	int a = Random(0,NazwyPlikow.size()) ;

	strcpy(sPlansza.cNazwaPlanszy , NazwyPlikow[a].c_str()) ;

	closedir(pdir) ;	//ZAMYKAMY SCIEZKE
	return true ;
}

bool Labirynt::OtworzPlik()
{
	string lokalizacja = "Maps\\" ;
	lokalizacja = lokalizacja + sPlansza.cNazwaPlanszy ;

	ifstream strumien (lokalizacja.c_str() , ios::in | ios::binary ) ;

	if(strumien)
		strumien.read( reinterpret_cast<char*>(&sPlansza) , sizeof(sPlansza)) ;

	else
	{
		cout << "BLAD OTWARCIA PLIKU." ;
		getch() ;
		strumien.clear() ;		//CZYSZCZENIE STRUMIENIA Z BLEDOW
		strumien.close() ;
		return false ;
	}

	for(int y = 0 ; y < 20 ; y++)			//WIERSZ
		for(int x = 0 ; x < 20 ; x++)		//KOLUMNA
		{
			if(sPlansza.PLANSZA[y][x] == META)
			{
				sMeta.y = y ;
				sMeta.x = x ;
			}
			if(sPlansza.PLANSZA[y][x] == GRACZ)
			{
				sGracz.y = y ;
				sGracz.x = x ;
			}
		} ;

	iLicznik = 0 ;

	strumien.clear() ;
	strumien.close() ;
	return true ;
}

bool Labirynt::Narysuj()
{
	switch(TRYB)
	{
		case M_EXIT:
			//WYBIERANIE PLANSZY
			if(NazwaPliku() && OtworzPlik())
				return true ;

			else
				return false ;

			break ;

		case M_GAME:

			system("cls") ;

			cout << string(40,'*') 
				<< "\n*" << center("Gra LABIRYNT", 38) << "*\n"
				<< string(40,'*') << endl ;
	
			//GORA MAPY
			cout << "\n\n\t" << string(22,'*') << endl ;

			//WIERSZE
			for(int y = 0 ; y < 20 ; y++)
			{
				cout << "\t*" ;
				//POLA WIERSZA
				for(int x = 0 ; x < 20 ; x++)
					cout << static_cast<char>(sPlansza.PLANSZA[y][x]) ;
				cout << "*\n" ;
			}

			//DOL MAPY
			cout << "\t" << string(22,'*') << "\n\n\n" << endl ;

			cout << "\t\tLEGENDA\n" 
				 << "'$'     GRACZ"
				 << "\t'@'     META\n"
				 << "'|'\tSCIANY\t'-'\n"
				 << "PORUSZASZ SIE STRZALKAMI\n" 
				 << "Wykonales " << iLicznik << " ruchow." ;

			return true ;

			break ;

		case M_WIN:

			system("cls") ;

			cout << string(40,'*') 
				 << "\n*" << center("Gra LABIRYNT", 38) << "*\n"
				 << string(40,'*') << endl ;
	
			//GORA MAPY
			cout << "\n\n\t" << string(22,'*') << endl ;

			//WIERSZE
			for(int y = 0 ; y < 20 ; y++)
			{
				cout << "\t*" ;
				//POLA WIERSZA
				for(int x = 0 ; x < 20 ; x++)
					cout << static_cast<char>(sPlansza.PLANSZA[y][x]) ;
				cout << "*\n" ;
			}

			//DOL MAPY
			cout << "\t" << string(22,'*') << "\n\n\n" << endl ;


			cout << "Przeszles labirynt w " << iLicznik << " ruchow." ;

			TRYB = M_EXIT ;

			getch() ;

			return false ;		//WYJSCIE Z GRY

			break ;
		
		case M_EDIT:

			system("cls") ;

			cout << string(40,'*') 
				<< "\n*" << center("EDYTOR", 38) << "*\n"
				<< string(40,'*') << endl ;
	
			//GORA MAPY
			cout << "\n\n\t" << string(22,'*') << endl ;

			//WIERSZE
			for(int y = 0 ; y < 20 ; y++)
			{
				cout << "\t*" ;
				//POLA WIERSZA
				for(int x = 0 ; x < 20 ; x++)
					cout << static_cast<char>(sDodatkowa.PLANSZA[y][x]) ;
				cout << "*\n" ;
			}

			//DOL MAPY
			cout << "\t" << string(22,'*') << "\n\n\n" << endl ;

			cout << "\t\tLEGENDA\n" 
				 << "1 - SCIANA '|'\t2 - SCIANA '-'\t3 - GRACZ '$'\n"
				 << "     \t4 - META '@'\t5 - TLO ' '\n"
				 << "ESC - WYJSCIE BEZ ZAPISU ZMIAN\tENTER - ZATWIERDZ ZMIANY\n"
				 << "PORUSZASZ SIE WSKAZNIKIEM '#'\tZA POMOCA STRZALEK" ;

			break ;
	}
	return true ;
}

bool Labirynt::Ruch()
{
	int x1 , y1 ;		//ZMIENNE DO SPRAWDZENIA CZY POLE JEST PUSTE CZY PELNE

	//POBIERANIE ZNAKU Z KLAWIATURY
	int znak = getch() ;

	switch(TRYB)
	{
		case M_GAME:			//GRA
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
								
								x1 = sGracz.x ;
								y1 = sGracz.y - 1 ;

								//if( y1 < 0 ) { iLicznik++ ; break ; }   PRAWDOPODOBNIE NIEPOTRZEBNE
								if(sPlansza.PLANSZA[y1][x1] == TLO)
								{
									sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
									sPlansza.PLANSZA[y1][x1] = GRACZ ;
									sGracz.y = y1 ;
									iLicznik++ ;
								}else
									if(sPlansza.PLANSZA[y1][x1] == META)
									{
										sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
										sPlansza.PLANSZA[y1][x1] = GRACZ ;
										sGracz.y = y1 ;
										iLicznik++ ;
										TRYB = M_WIN ;
									}else iLicznik++ ;

								break ;

							case 80: //STRZALKA W DOL
								
								x1 = sGracz.x ;
								y1 = sGracz.y + 1 ;

								//if( y1 > 19 ) { iLicznik++ ; break ; }   PRAWDOPODOBNIE NIEPOTRZEBNE
								if(sPlansza.PLANSZA[y1][x1] == TLO)
								{
									sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
									sPlansza.PLANSZA[y1][x1] = GRACZ ;
									sGracz.y = y1 ;
									iLicznik++ ;
								}else
									if(sPlansza.PLANSZA[y1][x1] == META)
									{
										sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
										sPlansza.PLANSZA[y1][x1] = GRACZ ;
										sGracz.y = y1 ;
										iLicznik++ ;
										TRYB = M_WIN ;
									}else iLicznik++ ;

								break ;

							case 75: //STRZALKA W LEWO
								
								x1 = sGracz.x - 1 ;
								y1 = sGracz.y ;

								//if( x1 < 0 ) { iLicznik++ ; break ; }   PRAWDOPODOBNIE NIEPOTRZEBNE
								if(sPlansza.PLANSZA[y1][x1] == TLO)
								{
									sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
									sPlansza.PLANSZA[y1][x1] = GRACZ ;
									sGracz.x = x1 ;
									iLicznik++ ;
								}else
									if(sPlansza.PLANSZA[y1][x1] == META)
									{
										sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
										sPlansza.PLANSZA[y1][x1] = GRACZ ;
										sGracz.x = x1 ;
										iLicznik++ ;
										TRYB = M_WIN ;
									}else iLicznik++ ;

								break ;

							case 77: //STRZALKA W PRAWO
								
								x1 = sGracz.x + 1;
								y1 = sGracz.y ;

								//if( x1 > 19 ) { iLicznik++ ; break ; }   PRAWDOPODOBNIE NIEPOTRZEBNE
								if(sPlansza.PLANSZA[y1][x1] == TLO)
								{
									sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
									sPlansza.PLANSZA[y1][x1] = GRACZ ;
									sGracz.x = x1 ;
									iLicznik++ ;
								}else
									if(sPlansza.PLANSZA[y1][x1] == META)
									{
										sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
										sPlansza.PLANSZA[y1][x1] = GRACZ ;
										sGracz.x = x1 ;
										iLicznik++ ;
										TRYB = M_WIN ;
									}else iLicznik++ ;

								break ;
						}
					}
					break ;

				case 76:			//duze L OSZUSTWO

					sPlansza.PLANSZA[sMeta.y][sMeta.x] = GRACZ ;
					sPlansza.PLANSZA[sGracz.y][sGracz.x] = TLO ;
					sGracz.x = sMeta.x ;
					sGracz.y = sMeta.y ;
					iLicznik++ ;
					TRYB = M_WIN ;
					break ;
			}
			break ;

		case M_EDIT:				//EDYCJA MAPY
			switch(znak)
			{
				case 224:            //ZNAK SPECJALNY
					if( kbhit() )    //FUNKCJA SPRAWDZAJACA CZY JEST ZNAK SPECJALNY
					{
						znak = getch();
						switch( znak )
						{
							case 72: //STRZALKA W GORE

								x1 = sWskaznik.x ;
								y1 = sWskaznik.y - 1 ;

								if(y1 < 0) break ;		//JESLI WSKAZNIK WYJDZIE POZAPLANSZE

								for(int y = 0 ; y < 20 ; y++)
									for(int x = 0 ; x < 20 ; x++)
										sDodatkowa.PLANSZA[y][x] = sPlansza.PLANSZA[y][x] ;		//przekopiowanie planszy do pomocnej planszy

								sWskaznik.x = x1 ;
								sWskaznik.y = y1 ;

								sDodatkowa.PLANSZA[sWskaznik.y][sWskaznik.x] = EDIT ;		//PRZYPISANIE WSKAZNIKA DO PLANSZY

								break ;

							case 80: //STRZALKA W DOL

								x1 = sWskaznik.x ;
								y1 = sWskaznik.y + 1 ;

								if(y1 > 19) break ;		//JESLI WSKAZNIK WYJDZIE POZAPLANSZE

								for(int y = 0 ; y < 20 ; y++)
									for(int x = 0 ; x < 20 ; x++)
										sDodatkowa.PLANSZA[y][x] = sPlansza.PLANSZA[y][x] ;		//przekopiowanie planszy do pomocnej planszy

								sWskaznik.x = x1 ;
								sWskaznik.y = y1 ;

								sDodatkowa.PLANSZA[sWskaznik.y][sWskaznik.x] = EDIT ;			//PRZYPISANIE WSKAZNIKA DO PLANSZY

								break ;

							case 75: //STRZALKA W LEWO

								x1 = sWskaznik.x - 1 ;
								y1 = sWskaznik.y ;

								if(x1 < 0) break ;		//JESLI WSKAZNIK WYJDZIE POZAPLANSZE

								for(int y = 0 ; y < 20 ; y++)
									for(int x = 0 ; x < 20 ; x++)
										sDodatkowa.PLANSZA[y][x] = sPlansza.PLANSZA[y][x] ;		//przekopiowanie planszy do pomocnej planszy

								sWskaznik.x = x1 ;
								sWskaznik.y = y1 ;

								sDodatkowa.PLANSZA[sWskaznik.y][sWskaznik.x] = EDIT ;			//PRZYPISANIE WSKAZNIKA DO PLANSZY

								break ;

							case 77: //STRZALKA W PRAWO

								x1 = sWskaznik.x + 1;
								y1 = sWskaznik.y ;

								if(x1 > 19) break ;		//JESLI WSKAZNIK WYJDZIE POZAPLANSZE

								for(int y = 0 ; y < 20 ; y++)
									for(int x = 0 ; x < 20 ; x++)
										sDodatkowa.PLANSZA[y][x] = sPlansza.PLANSZA[y][x] ;		//przekopiowanie planszy do pomocnej planszy

								sWskaznik.x = x1 ;
								sWskaznik.y = y1 ;

								sDodatkowa.PLANSZA[sWskaznik.y][sWskaznik.x] = EDIT ;			//PRZYPISANIE WSKAZNIKA DO PLANSZY

								break ;
						}
					}
					break ;

					//WPROWADZENIE ZNAKU DO MAPY

				case 49:		//CYFRA 1     
					//SCIANA1 = '|'
					sPlansza.PLANSZA[sWskaznik.y][sWskaznik.x] = SCIANA1 ;
					break ;

				case 50:		//CYFRA 2
					//SCIANA2 = '-'
					sPlansza.PLANSZA[sWskaznik.y][sWskaznik.x] = SCIANA2 ;
					break ;

				case 51:		//CYFRA 3
					//GRACZ   = '$'
					//JESLI JUZ GDZIES JEST GRACZ TO GO SKASUJ
					for(int y = 0 ; y < 20 ; y++)
						for(int x = 0 ; x < 20 ; x++)
							if(sPlansza.PLANSZA[y][x] == GRACZ)
								sPlansza.PLANSZA[y][x] = TLO ;
					sPlansza.PLANSZA[sWskaznik.y][sWskaznik.x] = GRACZ ;
					break ;

				case 52:		//CYFRA 4
					//META    = '@'
					//JESLI JUZ GDZIES JEST META TO JA SKASUJ
					for(int y = 0 ; y < 20 ; y++)
						for(int x = 0 ; x < 20 ; x++)
							if(sPlansza.PLANSZA[y][x] == META)
								sPlansza.PLANSZA[y][x] = TLO ;
					sPlansza.PLANSZA[sWskaznik.y][sWskaznik.x] = META ;
					break ;

				case 53:		//CYFRA 5
					//TLO     = ' '
					sPlansza.PLANSZA[sWskaznik.y][sWskaznik.x] = TLO ;
					break ;

				case 27:		//ESC    WYJSCIE
					return false ;
					break ;

				case 13:		//ENTER		ZATWIERDZ MAPE
					TRYB = M_EXIT ;
					break ;
			}
			break ;
	}
	return true ;
}

bool Labirynt::NEW()
{
	TRYB = M_EDIT ;

	sWskaznik.x = 0 ;
	sWskaznik.y = 0 ;

	system("cls") ;

	for(int y = 0 ; y < 20 ; y++)			//WIERSZE
		for(int x = 0 ; x < 20 ; x++)		//KOLUMNY
		{
			sPlansza.PLANSZA[y][x] = TLO ;		//CZYSCIMY PLANSZE
			sDodatkowa.PLANSZA[y][x] = TLO ;	//CZYSCIMY DODATKOWA
		}
	sDodatkowa.PLANSZA[sWskaznik.y][sWskaznik.x] = EDIT ;

	while(true)
	{	//PETLA POZWALAJACA NA WYKONYWANIE ZMIAN
		while(TRYB == M_EDIT)
		{
			Narysuj() ;
			if(!Ruch())
			{
				cout << "\n\nWYCHODZE BEZ ZAPISYWANIA ZMIAN" ;
				getch() ;
				return false ;
			}
		}
		if(CHECKS())
			break ;
		else
		{
			cout << "\nPLANSZY NIE DA SIE UKONCZYC" ;
			getch() ;
			TRYB = M_EDIT ;
		}
	}//WHILE(TRUE)

	system("cls") ;
	cout << "\n\n\n\tPODAJ NAZWE MAPY: " ;
	cin  >> sPlansza.cNazwaPlanszy ;

	string napis = "MAPS\\" ;
	napis += sPlansza.cNazwaPlanszy ;
	napis += ".adi" ;

	fstream zapis(napis.c_str() , ios::out | ios::binary) ;

	if(zapis)
	{
		zapis.write( reinterpret_cast<char*>(&sPlansza) , sizeof(sPlansza)) ;

		cout << "\nPLANSZA ZAPISANA" ;
		getch() ;
	}
	return true ;
}

bool Labirynt::EDITION()
{
	TRYB = M_EDIT ;

	sWskaznik.x = 0 ;
	sWskaznik.y = 0 ;

	system("cls") ;

	int i_nrPlanszy ;
	vector <string> VECs_Nazwa ;

	if(Wypisz_pliki(VECs_Nazwa , i_nrPlanszy))
	{
		string wybor = "MAPS\\" + VECs_Nazwa[i_nrPlanszy] ;

		//OTWIERAMY PLIK DO PISANIA I CZYTANIA BINARNEGO
		fstream plik(wybor.c_str() , ios::in | ios::out | ios::binary) ;
		
		if(plik)
		{
			//POBIERAMY Z PLIKU DANE DO sPlansza
			plik.read( reinterpret_cast<char*>(&sPlansza) , sizeof(sPlansza)) ;

			for(int y = 0 ; y < 20 ; y++)
				for(int x = 0 ; x < 20 ; x++)
					sDodatkowa.PLANSZA[y][x] = sPlansza.PLANSZA[y][x] ;

			while(true)
			{	//PETLA POZWALAJACA NA WYKONYWANIE ZMIAN
				while(TRYB == M_EDIT)
				{
					Narysuj() ;
					if(!Ruch())
					{
						cout << "\n\nWYCHODZE BEZ ZAPISYWANIA ZMIAN" ;
						getch() ;
						return false ;
					}
				}
				if(CHECKS())
					break ;
				else
				{
					cout << "\nPLANSZY NIE DA SIE UKONCZYC" ;
					getch() ;
					TRYB = M_EDIT ;
				}
			}//WHILE(TRUE)

			plik.seekp(0 , ios::beg) ; //WSKAZNIK DO PISANIA , 2 ARGUMENT DOMNIEMANY = ios::beg
			plik.write( reinterpret_cast<char*>(&sPlansza) , sizeof(sPlansza)) ;
		}
	}

	return true ;
}

bool Labirynt::CHECKS()
{
	//PRZEKOPIOWANIE PLANSZY DO POMOCNEJ TABLICY
	for(int y = 0 ; y < 20 ; y++)
		for(int x = 0 ; x < 20 ; x++)
		{
			sDodatkowa.PLANSZA[y][x] = sPlansza.PLANSZA[y][x] ;
			if(sDodatkowa.PLANSZA[y][x] == GRACZ)
			{
				sGracz.y = y ;
				sGracz.x = x ;
			}
		};

	for(;;)
	{
		//SPRAWDZANIE CZY ZARAZ OBOK JEST META JESLI TAK ZWRACA TRUE
		if(sDodatkowa.PLANSZA[sGracz.y - 1][sGracz.x] == META ||
		   sDodatkowa.PLANSZA[sGracz.y + 1][sGracz.x] == META ||
		   sDodatkowa.PLANSZA[sGracz.y][sGracz.x - 1] == META ||
		   sDodatkowa.PLANSZA[sGracz.y][sGracz.x + 1] == META )
		   return true ;
		
		//SPRAWDZAMY CZY POLE == TLO
		//JESLI TAK TO PRZESUWAMY GRACZA NA TA POZYCJE A NA STAREJ WPROWADZAMY ZNAK CHECK
		if(sDodatkowa.PLANSZA[sGracz.y - 1][sGracz.x] == TLO)
		{
			sDodatkowa.PLANSZA[sGracz.y][sGracz.x] = CHECK ;
			sGracz.y = sGracz.y - 1 ;
			continue ;
		}

		//SPRAWDZAMY CZY POLE == TLO
		//JESLI TAK TO PRZESUWAMY GRACZA NA TA POZYCJE A NA STAREJ WPROWADZAMY ZNAK CHECK
		if(sDodatkowa.PLANSZA[sGracz.y + 1][sGracz.x] == TLO)
		{
			sDodatkowa.PLANSZA[sGracz.y][sGracz.x] = CHECK ;
			sGracz.y = sGracz.y + 1 ;
			continue ;
		}
					
		//SPRAWDZAMY CZY POLE == TLO
		//JESLI TAK TO PRZESUWAMY GRACZA NA TA POZYCJE A NA STAREJ WPROWADZAMY ZNAK CHECK
		if(sDodatkowa.PLANSZA[sGracz.y][sGracz.x - 1] == TLO)
		{
			sDodatkowa.PLANSZA[sGracz.y][sGracz.x] = CHECK ;
			sGracz.x = sGracz.x - 1 ;
			continue ;
		}
						
		//SPRAWDZAMY CZY POLE == TLO
		//JESLI TAK TO PRZESUWAMY GRACZA NA TA POZYCJE A NA STAREJ WPROWADZAMY ZNAK CHECK
		if(sDodatkowa.PLANSZA[sGracz.y][sGracz.x + 1] == TLO)
		{
			sDodatkowa.PLANSZA[sGracz.y][sGracz.x] = CHECK ;
			sGracz.x = sGracz.x + 1 ;
			continue ;
		}

		//JESLI ZADNE POLE OBOK NIE ROWNA SIE TLO TO SZUKAMY POLA == CHECK GDZIE OBOK JEST POLE == TLO
		int y = 0 , x ;
		bool wyjscie = true ;

		while(y < 20 && wyjscie == true)
		{
			x = 0 ;
			while(x < 20)
			{
				//JESLI POLE == CHECK SPRAWDZ CZY JAKIES OBOK ROWNA SIE TLO
				if(sDodatkowa.PLANSZA[y][x] == CHECK)
					if(sDodatkowa.PLANSZA[y - 1][x] == TLO ||
					   sDodatkowa.PLANSZA[y + 1][x] == TLO ||
					   sDodatkowa.PLANSZA[y][x - 1] == TLO ||
					   sDodatkowa.PLANSZA[y][x + 1] == TLO)
					{
					//JESLI PRAWDA TO PRZYPISZ NOWE DANE
						sGracz.y = y ;
						sGracz.x = x ;
						wyjscie = false ;
						break ;
					}
					x++ ;
				}
				y++ ;
			}
			//JESLI NIE MA TAKIEGO MIEJSCA FUNKCJA ZWRUCI FALSE
			if(wyjscie == true)
				return false ;
		}
}

bool Labirynt::Wypisz_pliki(vector <string> &SPIS , int &wyb)
{
	DIR* pdir = NULL ;	//WSKAZNIK SCIEZKI
	struct dirent * ps_dirent = NULL ;	//readdir ZWRACA STRUKTURE dirent

	pdir = opendir ("Maps") ; //OTWIERAMY SCIEZKE DO PLIKOW

	if(pdir)	//JESLI UDALO SIE OTWOZYC SCIEZKE
	{
		while(ps_dirent = readdir(pdir))	//JESLI COS JEST TO CZYTAJ
		{
			//strstr PRZESZUKUJE 1 const char * I SZUKA W NIM 2 const char * ZWRACA const char * LUB NULL JESLI NIC NIE ZNAJDZIE
			if(!(strstr(ps_dirent->d_name , "adi") == NULL))  
				SPIS.push_back(ps_dirent->d_name) ;
		}

		if(SPIS.empty())
		{
			cout << "\n\n\n\tW PLIKU \"MAPS\" NIE MA MAP" ;
			getch() ;
			return false ;
		}

		while(true)
		{
			system("cls") ;
			
			cout << "\n\n\tLISTA MAP:\n" ;

			for(int i = 0 ; i < (static_cast<int>(SPIS.size())) ; i++)
				cout << "\n\t" << i+1 << " " << SPIS[i] ;

			cout << "\nNUMER: " ;

			if(zab_cin(wyb) && wyb >= 0 && wyb < (static_cast<int>(SPIS.size())))
				break ;

			cout << "\nNIE MA TAKIEJ OPCJI." ;
			getch() ;
		}
	}else
	{
		cout << "\nNIE UDALO SIE OTWOZYC SCIEZKI." ;
		getch() ;
		return false ;
	}
	closedir(pdir) ;	//ZAMYKAMY SCIEZKE
	return true ;
}

bool Labirynt::DELETE_MAP()
{
	system("cls") ;

	vector <string> VECs_Nazwy ;
	int i_liczba ;
	if(Wypisz_pliki(VECs_Nazwy , i_liczba))
	{
		string s_Wybrana = "MAPS\\" + VECs_Nazwy[i_liczba] ;

		remove(s_Wybrana.c_str()) ;
	}
	return true ;
}