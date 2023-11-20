#pragma once
#include "Melodie.h"
#include <vector>
#include <fstream>
#include <sstream>

using std::vector;

class RepoExceptions {
private:
	string msg;
public:
	//constructor
	//param<m>mesajul cu care este initializat - string
	RepoExceptions(string m) :msg{ m } {};
	//functie de get pentru mesaj
	string getMsg() {
		return this->msg;
	}
};

class RepoMelodie
{
private:
	string fisier;
	vector<Melodie> melodii;
public:
	/// <summary>
	/// Constructor care primeste fisierul
	/// </summary>
	/// <param name="f">fisierul cu care va lucra repository-ul de melodii - string</param>
	RepoMelodie(string f);
	//Subalgoritm care incarca datele din fisier(citeste datele din fisier)
	void loadFromFile();
	//Subalgoritm care salveaza un vector de melodii in fisier
	//param mel(vector<Melodie>) -> vectorul care se salveaza in fisier
	void saveToFile(vector<Melodie> mel);
	Melodie findOne(int id);
	/// <summary>
	/// Metoda care adauga o melodie in repository
	/// </summary>
	/// <param name="m">melodia de adaugat - Melodie</param>
	/// <throws RepoException: daca melodia este deja in fisier</throws>
	void adauga(Melodie m);
	/// <summary>
	/// Metoda care sterge o melodie din repository
	/// </summary>
	/// <param name="id">id-ul melodiei de sters - int</param>
	/// <throws RepoException: daca melodia nu exista in repository</throws>
	void sterge(int id);
	/// <summary>
	/// Metoda care modifica o melodie data
	/// </summary>
	/// <param name="m">melodia de modificat - Melodie</param>
	/// <throws RepoException: daca melodia nu exista in fisier</throws>
	void modifica(Melodie m);
	//Returneaza o lista cu melodiile din repository
	vector<Melodie> getAll();
};

//Functie de test pentru RepoMelodie
void testRepository();
