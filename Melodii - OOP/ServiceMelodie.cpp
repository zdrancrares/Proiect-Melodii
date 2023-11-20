#include "ServiceMelodie.h"
#include <map>

vector<Melodie> ServiceMelodie::getAll() {
	return repo.getAll();
}
void ServiceMelodie::adauga_melodie(string titlu, string artist, string gen) {
	int id = 0;
	for (int i = 1; i < 10000000; i++) {
		if (id_melodii[i] == 0) {
			id = i;
			break;
		}
	}
	Melodie m{ id, titlu, artist, gen };
	id_melodii[id] = 1;
	validator.valideaza(m);
	repo.adauga(m);
	undoActions.push_back(new UndoAdd(repo, m));
	notify();
}
void ServiceMelodie::sterge_melodie(int id) {
	Melodie m = repo.findOne(id);
	repo.sterge(id);
	undoActions.push_back(new UndoDelete{ repo, m });
	id_melodii[id] = 0;
	notify();
}

void ServiceMelodie::modifica_melodie(int id, string titluNou, string artistNou, string genNou) {
	Melodie m{ id, titluNou, artistNou, genNou };
	validator.valideaza(m);
	Melodie copie = repo.findOne(m.getId());
	repo.modifica(m);
	undoActions.push_back(new UndoUpdate{ repo, m });
	notify();
}
int ServiceMelodie::nrAcelasiArtist(string artist) {
	int count = 0;
	for (auto& el : repo.getAll()) {
		if (el.getArtist() == artist) {
			count++;
		}
	}
	return count;
}
int ServiceMelodie::nrAcelasiGen(string gen) {
	int count = 0;
	for (auto& el : repo.getAll()) {
		if (el.getGen() == gen) {
			count++;
		}
	}
	return count;
}
vector<Melodie> ServiceMelodie::sortArtist(vector<Melodie> mel) {
	sort(mel.begin(), mel.end(), [&](Melodie m1, Melodie m2) {
		return m1.getArtist() < m2.getArtist();
		});
	return mel;
}

void ServiceMelodie::undo() {
	if (undoActions.empty()) {
		throw ServiceExceptions("Nu se mai poate face undo.\n");
	}
	UndoAction* action = undoActions.back();
	action->doUndo();
	undoActions.pop_back();
	delete action;
}

void testService() {
	RepoMelodie repo{ "testeService.txt" };
	ValidatorMelodie validator;
	ServiceMelodie srv{ repo, validator };
	assert(srv.getAll().size() == 15);
	try {
		srv.adauga_melodie("TITLUUU", "ARTISTTT", "folk");
	}
	catch (ValidatorExceptions& ex) {
		assert(false);
	}
	assert(srv.getAll().size() == 16);
	Melodie last = srv.getAll()[srv.getAll().size() - 1];
	assert(last.getArtist() == "ARTISTTT");
	assert(last.getTitlu() == "TITLUUU");
	assert(last.getGen() == "folk");
	int idLast = last.getId();
	srv.sterge_melodie(idLast);
	assert(srv.getAll().size() == 15);
	Melodie first = srv.sortArtist(srv.getAll())[0];
	assert(first.getArtist() == "andreea");
	assert(srv.nrAcelasiArtist("rares") == 4);
	assert(srv.nrAcelasiArtist("andreea") == 2);
	assert(srv.nrAcelasiGen("rock") == 3);
	assert(srv.nrAcelasiGen("disco") == 4);
}
