#pragma once
#include "ServiceMelodie.h"
#include <qwidget.h>
#include <qtableview.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qlabel.h>

class MyTableModel : public QAbstractTableModel {
private:
	ServiceMelodie& srv;
	vector<Melodie> melodii;
public:
	MyTableModel(ServiceMelodie& s);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	//Functie care seteaza melodiile in tabel
	//param<mel> lista de melodii de pus in table - vector<Melodie>
	void setMelodii(vector<Melodie> mel);
};

class MelodieGUI : public QWidget, public Observer
{
private:
	ServiceMelodie& srv;
	QTableView* table = new QTableView;
	MyTableModel* model;
	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtArtist = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{ "Adauga melodie" };
	QPushButton* btnDelete = new QPushButton{ "Sterge melodie" };
	QPushButton* btnUpdate = new QPushButton{ "Modifica melodie" };
	QPushButton* btnUndo = new QPushButton{ "Undo" };
	QPushButton* btnStats = new QPushButton{ "Statistici genuri" };
public:
	//Constructor
	//param<s>: Service-ul de melodii cu care lucreaza fereastra
	MelodieGUI(ServiceMelodie& s);
	//Functie care initializeaza componentele de pe fereastra
	void initGUI();
	//Functie care conecteaza slot-urile la semnalele corespunzatoare
	void connectGUI();
	//Functie care incarca in tabel o lista de melodii
	//<param>mel - lista de melodii care se incarca in tabel - vector<Melodie>
	void reloadList(vector<Melodie> mel);
	/// Functie care deseneaza cercuri concentrice pe ecran pentru fiecare gen in parte
	void paintEvent(QPaintEvent* event) override;
	void openGenreWindows();
	void update();
	~MelodieGUI() {
		srv.removeObserver(this);
	}
};

class GenreWindow : public QWidget, public Observer {
	Q_OBJECT
private:
	int number;
	QLabel* label;
	QString labelTextField;
	ServiceMelodie& srv;
	QString genre;
public:
	GenreWindow(ServiceMelodie& service,const QString& genre, int number);
	void update();
	~GenreWindow() {
		srv.removeObserver(this);
	}
};

