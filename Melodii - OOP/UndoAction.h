#include "Melodie.h"
#include "RepoMelodie.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

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