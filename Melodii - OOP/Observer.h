#pragma once
#include <vector>

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* ob);
	void removeObserver(Observer* ob);
protected:
	void notify();
};