#include "Melodie.h"
/// <summary>
/// Clasa de exceptii pentru validare
/// </summary>
class ValidatorExceptions {
private:
	string message;
public:
	ValidatorExceptions(string message) {
		this->message = message;
	}
	string getMessage() {
		return this->message;
	}
};

class ValidatorMelodie {
public:
	/// <summary>
	/// Metoda care valideaza o entitate de tipul Melodie
	/// </summary>
	/// <param name="m">Melodia de validat</param>
	/// <throws ValidationException>In cazul in care entitatea nu este valida</throws>
	void valideaza(Melodie m);
};