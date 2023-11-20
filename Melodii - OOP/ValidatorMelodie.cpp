#include "ValidatorMelodie.h"

void ValidatorMelodie::valideaza(Melodie m) {
	string errors = "";
	string titlu = m.getTitlu();
	if (titlu.empty() || titlu.size() > 30) {
		errors += "Titlul trebuie sa aiba o lungime cuprinsa intre 0 si 30 de caractere.\n";
	}
	string artist = m.getArtist();
	if (artist.empty() || artist.size() > 50) {
		errors += "Numele artistului trebuie sa aiba o lungime cuprinsa intre 0 si 50.\n";
	}
	string gen = m.getGen();
	if (gen != "rock" && gen != "folk" && gen != "disco" && gen != "pop") {
		errors += "Genul melodiei trebuie sa fie unul dintre: disco, folk, pop sau rock.\n";
	}
	if (!errors.empty()) {
		throw ValidatorExceptions(errors);
	}
}