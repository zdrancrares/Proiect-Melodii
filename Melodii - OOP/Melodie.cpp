#include "Melodie.h"

Melodie::Melodie(int i, string t, string a, string g) {
	id = i;
	titlu = t;
	artist = a;
	gen = g;
}

Melodie::Melodie(const Melodie& other) {
	this->id = other.id;
	this->titlu = other.titlu;
	this->artist = other.artist;
	this->gen = other.gen;
}

Melodie& Melodie::operator=(const Melodie& other) {
	this->id = other.id;
	this->titlu = other.titlu;
	this->artist = other.artist;
	this->gen = other.gen;
	return *this;
}
int Melodie::getId() { return this->id; };

string Melodie::getTitlu() { return this->titlu; }

string Melodie::getArtist() { return this->artist; }

string Melodie::getGen() { return this->gen; }

void testDomain() {
	Melodie m{ 53624, "melodieee", "salut", "rock" };
	assert(m.getId() == 53624);
	assert(m.getTitlu() == "melodieee");
	assert(m.getArtist() == "salut");
	assert(m.getGen() == "rock");
}
