#pragma once
#include <string>
#include <assert.h>

using std::string;

class Melodie
{
private:
	int id = 0;
	string titlu, artist, gen;
public:
	//Constructor default
	Melodie() {};
	/// <summary>
	/// Constructor pentru melodie cu toate atributele
	/// </summary>
	/// <param name="i">id-ul melodiei - int</param>
	/// <param name="t">titlul melodiei - string</param>
	/// <param name="a">artistul melodiei - string</param>
	/// <param name="g">genul melodiei - string</param>
	Melodie(int i, string t, string a, string g);
	/// <summary>
	/// Constructor de copiere pentru Melodie
	/// </summary>
	/// <param name="other">obiect de tip Melodie pe care in copiem in this</param>
	Melodie(const Melodie& other);
	/// <summary>
	/// Overrid = operator
	/// </summary>
	/// <param name="other">Melodia de asignat</param>
	/// <returns>referinta la this</returns>
	Melodie& operator=(const Melodie& other);
	//Functie de get pentru ID
	int getId();
	//Functie de get pentru titlu
	string getTitlu();
	//Functie de get pentru artist
	string getArtist();
	//Functie de get pentru gen
	string getGen();
};

//Functie de test pentru Melodie
void testDomain();

