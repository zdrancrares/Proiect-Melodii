#include "Melodie.h"
#include "RepoMelodie.h"

/// <summary>
/// Clasa abstracta pentru undo
/// </summary>
class UndoAction {
public:
	/// <summary>
	/// Metoda pur virtuala care va fi implementata de toate sub-clasele pentru a efectua operatia
	/// corecta de undo
	/// </summary>
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

/// <summary>
/// Clasa care face undo la operatia de adaugare a unei melodii
/// </summary>
class UndoAdd : public UndoAction {
private:
	Melodie melodieAdaugata;
	RepoMelodie& repo;
public:
	UndoAdd(RepoMelodie& r, const Melodie& m) : repo{ r }, melodieAdaugata{ m } {
	}
	void doUndo() override;
	~UndoAdd() = default;
};

/// <summary>
/// Clasa care face undo la operatia de stergere a unei melodii
/// </summary>
class UndoDelete : public UndoAction {
private:
	Melodie melodieStearsa;
	RepoMelodie& repo;
public:
	UndoDelete(RepoMelodie& r, const Melodie& m) : repo{ r }, melodieStearsa{ m } {
	}
	void doUndo() override;
	~UndoDelete() = default;
};

/// <summary>
/// Clasa care face undo la operatia de modificare a unei melodii
/// </summary>
class UndoUpdate : public UndoAction {
private:
	Melodie melodieModificata;
	RepoMelodie& repo;
public:
	UndoUpdate(RepoMelodie& r, const Melodie& m) : repo{ r }, melodieModificata{ m } {
	}
	void doUndo() override;
	~UndoUpdate() = default;
};