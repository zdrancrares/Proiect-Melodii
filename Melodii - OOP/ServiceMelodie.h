#pragma once
#include "RepoMelodie.h"
#include "Observer.h"
#include "ValidatorMelodie.h"
#include "UndoAction.h"
#include <time.h>
#include <algorithm>
#include <map>

class ServiceExceptions {
private:
	string message;
public:
	ServiceExceptions(string msg) {
		this->message = msg;
	}
	string getMessage() {
		return this->message;
	}
};

class ServiceMelodie: public Observable
{
private:
	RepoMelodie& repo;
	ValidatorMelodie& validator;
	vector<UndoAction*> undoActions = {};
	std::map<int, int> id_melodii;

public:
	//Constructorul Service-ului de melodii
	//param<r>: Repository-ul de melodii cu care lucreaza service-ul - referinta la RepoMelodie
	ServiceMelodie(RepoMelodie& r, ValidatorMelodie& v) : repo{ r }, validator{ v } {
		for (auto& el : repo.getAll()) {
			id_melodii[el.getId()] = 1;
		}
	};
	//Functie care returneaza lista de melodii din repository
	vector<Melodie> getAll();
	/// <summary>
	/// Functie care adauga o melodie in lista de melodii
	/// </summary>
	/// <param name="titlu">Titlul melodiei de adaugat - string</param>
	/// <param name="artist">Artistul melodiei de adaugat - string</param>
	/// <param name="gen">Genul melodiei de adaugat - string</param>
	void adauga_melodie(string titlu, string artist, string gen);
	/// <summary>
	/// Functie care sterge o melodie din lista de melodii
	/// </summary>
	/// <param name="id">id-ul melodiei de sters - int</param>
	void sterge_melodie(int id);
	void modifica_melodie(int id, string titluNou, string artistNou, string genNou);
	/// <summary>
	/// Functie care returneaza numarul de melodii care au acelasi artist cu cel primit ca argument
	/// </summary>
	/// <param name="artist">artistul pentru care se numara melodiile - string</param>
	/// <returns>numarul de melodii cu acelasi artist</returns>
	int nrAcelasiArtist(string artist);
	/// <summary>
	/// Functie care returneaza numarul de melodii care au acelasi gen cu cel primit ca argument
	/// </summary>
	/// <param name="gen">genul pentru care se numara melodiile - string</param>
	/// <returns>numarul de melodii cu acelasi gen</returns>
	int nrAcelasiGen(string gen);
	/// <summary>
	/// Functie de sortare crescatoare a unei liste de melodii dupa artist 
	/// </summary>
	/// <param name="mel">lista de melodii de sortat - vector<Melodie></param>
	/// <returns>lista sortata in functie de artisti</returns>
	vector<Melodie> sortArtist(vector<Melodie> mel);
	void undo();
};

//Functie de test pentru ServiceMelodie
void testService();

