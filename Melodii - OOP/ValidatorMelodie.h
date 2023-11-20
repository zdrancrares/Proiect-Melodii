#include "Melodie.h"

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
	void valideaza(Melodie m);
};