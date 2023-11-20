#include "RepoMelodie.h"

RepoMelodie::RepoMelodie(string f) {
	fisier = f;
	loadFromFile();
}
void RepoMelodie::loadFromFile() {
	std::ifstream fin(fisier);
	if (!fin.is_open()) {
		throw RepoExceptions("Nu s-a putut deschide fisierul!\n");
	}
	string line, word;
	while (getline(fin, line)) {
		if (line == "") {
			continue;
		}
		int id = 0;
		string titlu, artist, gen;
		int cnt = 0;
		std::stringstream s(line);
		while (getline(s, word, ',')) {
			if (cnt == 0) {
				id = stoi(word);
			}
			else if (cnt == 1) {
				titlu = word;
			}
			else if (cnt == 2) {
				artist = word;
			}
			else if (cnt == 3) {
				gen = word;
			}
			cnt++;
		}
		Melodie m{ id, titlu, artist, gen };
		melodii.push_back(m);
	}
	fin.close();
}
void RepoMelodie::saveToFile(vector<Melodie> mel) {
	std::ofstream fout(fisier);
	for (auto& el : mel) {
		fout << el.getId() << ',' << el.getTitlu() << ',' << el.getArtist() << ',' << el.getGen() << '\n';
	}
	fout.close();
}

Melodie RepoMelodie::findOne(int id) {
	for (auto& el : melodii) {
		if (el.getId() == id) {
			return el;
		}
	}
	throw RepoExceptions("Nu exista aceasta melodie!\n");
}

void RepoMelodie::adauga(Melodie m) {
	for (auto& el : melodii) {
		if (el.getId() == m.getId()) {
			throw RepoExceptions("Exista deja aceasta melodie!\n");
		}
	}
	melodii.push_back(m);
	saveToFile(melodii);
}
void RepoMelodie::sterge(int id) {
	bool gasit = false;
	int poz = 0;
	for (auto& el : melodii) {
		if (el.getId() == id) {
			gasit = true;
			break;
		}
		poz++;
	}
	if (!gasit) {
		throw RepoExceptions("Nu exista aceasta melodie!\n");
	}
	melodii.erase(melodii.begin() + poz, melodii.begin() + poz + 1);
	saveToFile(melodii);
}

void RepoMelodie::modifica(Melodie m) {
	bool gasit = false;
	for (auto& el : melodii) {
		if (el.getId() == m.getId()) {
			gasit = true;
			el = m;
			break;
		}
	}
	if (!gasit) {
		throw RepoExceptions("Nu exista aceasta melodie!\n");
	}
	saveToFile(melodii);
}

vector<Melodie> RepoMelodie::getAll() {
	return melodii;
}

void testRepository() {
	RepoMelodie repo{ "testeRepo.txt" };
	assert(repo.getAll().size() == 15);
	Melodie m{ 1000, "TITLU", "ARTIST", "pop" };
	repo.adauga(m);
	assert(repo.getAll().size() == 16);
	assert(repo.getAll()[repo.getAll().size() - 1].getId() == 1000);
	try {
		repo.adauga(m);
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(true);
	}
	repo.sterge(m.getId());
	assert(repo.getAll().size() == 15);
	try {
		repo.sterge(m.getId());
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(true);
	}
}
