#pragma once
#include <vector>

/// <summary>
/// Clasa Observer - sunt atente la fiecare modificare a subiectului(Observable)
/// </summary>
class Observer {
public:
	virtual void update() = 0;
};

/// <summary>
/// Clasa Observable la care se angajeaza obiecte de tipul observer
/// </summary>
class Observable {
private:
	std::vector<Observer*> observers;
public:
	/// <summary>
	/// Metoda pentru adaugarea unui observer
	/// </summary>
	/// <param name="ob">obiect de tip Observer* care se adauga</param>
	void addObserver(Observer* ob);
	/// <summary>
	/// Metoda pentru stergerea unui observer din lista
	/// </summary>
	/// <param name="ob">obiect de tip Observer* care se sterge</param>
	void removeObserver(Observer* ob);
protected:
	/// <summary>
	/// Metoda care notifica ca s-a schimbat ceva in subiect
	/// </summary>
	void notify();
};