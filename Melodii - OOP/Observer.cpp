#include "Observer.h"

void Observable::addObserver(Observer* ob) {
	observers.push_back(ob);
}

void Observable::removeObserver(Observer* ob) {
	observers.erase(remove(observers.begin(), observers.end(), ob), observers.end());
}

void Observable::notify() {
	for (auto& ob : observers) {
		ob->update();
	}
}