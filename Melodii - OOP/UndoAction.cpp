#include "UndoAction.h"

void UndoAdd::doUndo() {
	repo.sterge(melodieAdaugata.getId());;
}

void UndoDelete::doUndo() {
	repo.adauga(melodieStearsa);;
}

void UndoUpdate::doUndo() {
	repo.modifica(melodieModificata);;
}