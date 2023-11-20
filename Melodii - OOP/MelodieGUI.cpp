#include "MelodieGUI.h"

MyTableModel::MyTableModel(ServiceMelodie& s) :srv{ s } {
	this->melodii = srv.sortArtist(srv.getAll());
}
int MyTableModel::rowCount(const QModelIndex& parent) const  {
	return melodii.size();
}
int MyTableModel::columnCount(const QModelIndex& parent) const  {
	return 6;
}
QVariant MyTableModel::data(const QModelIndex& index, int role) const  {
	if (role == Qt::DisplayRole) {
		Melodie m = melodii[index.row()];
		if (index.column() == 0) {
			return QString::number(m.getId());
		}
		else if (index.column() == 1) {
			return QString::fromStdString(m.getTitlu());
		}
		else if (index.column() == 2) {
			return QString::fromStdString(m.getArtist());
		}
		else if (index.column() == 3) {
			return QString::fromStdString(m.getGen());
		}
		else if (index.column() == 4) {
			return QString::number(srv.nrAcelasiArtist(m.getArtist()));
		}
		else if (index.column() == 5) {
			return QString::number(srv.nrAcelasiGen(m.getGen()));
		}
	}
	return QVariant{};
}
QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return "ID";
			case 1:
				return "Titlu";
			case 2:
				return "Artist";
			case 3:
				return "Gen";
			case 4:
				return "Nr. acelasi artist";
			case 5:
				return "Nr. acelasi gen";
			}
		}
	}
	return QVariant{};
}
void MyTableModel::setMelodii(vector<Melodie> mel) {
	this->melodii = mel;
	auto topLeft = createIndex(0, 0);
	auto bottomRight = createIndex(rowCount(), columnCount());
	emit layoutChanged();
	emit dataChanged(topLeft, bottomRight);
}

MelodieGUI::MelodieGUI(ServiceMelodie& s) : srv{ s } {
	model = new MyTableModel{ srv };
	table->setFixedHeight(300);
	this->setFixedSize(800, 550);
	initGUI();
	connectGUI();
	srv.addObserver(this);
	reloadList(srv.sortArtist(srv.getAll()));
}
void MelodieGUI::initGUI() {
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setModel(model);
	QVBoxLayout* mainLy = new QVBoxLayout;
	setLayout(mainLy);
	QHBoxLayout* susLy = new QHBoxLayout;
	susLy->addWidget(table);
	QVBoxLayout* susDrLy = new QVBoxLayout;
	susLy->addLayout(susDrLy);
	QFormLayout* formLy = new QFormLayout;
	formLy->addRow("ID", txtId);
	formLy->addRow("Titlu", txtTitlu);
	formLy->addRow("Artist", txtArtist);
	formLy->addRow("Gen", txtGen);
	susDrLy->addLayout(formLy);
	susDrLy->addWidget(btnAdd);
	susDrLy->addWidget(btnDelete);
	susDrLy->addWidget(btnUpdate);
	susDrLy->addWidget(btnUndo);
	susDrLy->addWidget(btnStats);
	QHBoxLayout* josLy = new QHBoxLayout;
	mainLy->addLayout(susLy);
	mainLy->addLayout(josLy);
}

void MelodieGUI::update() {
	reloadList(srv.sortArtist(srv.getAll()));
}

void MelodieGUI::connectGUI() {
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
		if (table->selectionModel()->selectedIndexes().isEmpty()) {
			txtId->setText("");
			txtTitlu->setText("");
			txtArtist->setText("");
			txtGen->setText("");
			return;
		}
		auto row = table->selectionModel()->selectedIndexes().at(0).row();
		txtId->setText(table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toString());
		txtTitlu->setText(table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString());
		txtArtist->setText(table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString());
		txtGen->setText(table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toString());
		});
	QObject::connect(btnAdd, &QPushButton::clicked, [this] {
		string titlu = txtTitlu->text().toStdString();
		string artist = txtArtist->text().toStdString();
		string gen = txtGen->text().toStdString();
		try {
			srv.adauga_melodie(titlu, artist, gen);
			reloadList(srv.sortArtist(srv.getAll()));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (ValidatorExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
		repaint();
		});
	QObject::connect(btnDelete, &QPushButton::clicked, [this] {
		int id = txtId->text().toInt();
		try {
			srv.sterge_melodie(id);
			reloadList(srv.sortArtist(srv.getAll()));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		repaint();
		});
	QObject::connect(btnUpdate, &QPushButton::clicked, [this] {
		int id = txtId->text().toInt();
		string titlu = txtTitlu->text().toStdString();
		string artist = txtArtist->text().toStdString();
		string gen = txtGen->text().toStdString();
		try {
			srv.modifica_melodie(id, titlu, artist, gen);
			reloadList(srv.sortArtist(srv.getAll()));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (ValidatorExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
		});
	QObject::connect(btnUndo, &QPushButton::clicked, [this] {
		try {
			srv.undo();
			reloadList(srv.sortArtist(srv.getAll()));
		}
		catch (ServiceExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (ValidatorExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
		});
	QObject::connect(btnStats, &QPushButton::clicked, this, &MelodieGUI::openGenreWindows);
}
void MelodieGUI::reloadList(vector<Melodie> mel) {
	model->setMelodii(mel);
}
void MelodieGUI::paintEvent(QPaintEvent* event) {
	QPainter painter{ this };
	painter.setPen(Qt::green);
	int stangaSus1 = 40;
	int stangaSus2 = 30;

	int dreaptaSus1 = width() - 70;
	int dreaptaSus2 = 30;

	int stangaJos1 = 40;
	int stangaJos2 = height() - 70;

	int dreaptaJos1 = width() - 70;
	int dreaptaJos2 = height() - 70;

	QRect rec1(stangaSus1, stangaSus2, 50, 50);
	QRect rec2(dreaptaSus1, dreaptaSus2, 50, 50);
	QRect rec3(stangaJos1, stangaJos2, 50, 50);
	QRect rec4(dreaptaJos1, dreaptaJos2, 50, 50);

	painter.drawEllipse(rec1);
	painter.drawEllipse(rec2);
	painter.drawEllipse(rec3);
	painter.drawEllipse(rec4);

	painter.setPen(Qt::blue);
	painter.drawText(rec1.center().x() + 120, rec1.center().y(), "ROCK");
	painter.setPen(Qt::green);
	for (int i = 0; i < srv.nrAcelasiGen("rock"); i++) {
		QPoint center = rec1.center();
		painter.drawEllipse(center, rec1.width() + (i + 1) * 7, rec1.height() + (i + 1) * 7);
	}
	painter.setPen(Qt::blue);
	painter.drawText(rec2.center().x() - 150, rec2.center().y(), "FOLK");
	painter.setPen(Qt::green);
	for (int i = 0; i < srv.nrAcelasiGen("folk"); i++) {
		QPoint center = rec2.center();
		painter.drawEllipse(center, rec2.width() + (i + 1) * 7, rec2.height() + (i + 1) * 7);
	}
	painter.setPen(Qt::blue);
	painter.drawText(rec3.center().x() + 120, rec3.center().y(), "DISCO");
	painter.setPen(Qt::green);
	for (int i = 0; i < srv.nrAcelasiGen("disco"); i++) {
		QPoint center = rec3.center();
		painter.drawEllipse(center, rec3.width() + (i + 1) * 7, rec3.height() + (i + 1) * 7);
	}
	painter.setPen(Qt::blue);
	painter.drawText(rec4.center().x() - 150, rec4.center().y(), "POP");
	painter.setPen(Qt::green);
	for (int i = 0; i < srv.nrAcelasiGen("pop"); i++) {
		QPoint center = rec4.center();
		painter.drawEllipse(center, rec4.width() + (i + 1) * 7, rec4.height() + (i + 1) * 7);
	}
}

GenreWindow::GenreWindow(ServiceMelodie& service, const QString& genre, int number): srv { service }{
	QVBoxLayout* layout = new QVBoxLayout(this);
	QString labelText = "Sunt " + QString::number(number) + " melodii din genul " + genre;
	this->labelTextField = labelText;
	QLabel* label = new QLabel(labelText, this);
	this->label = label;
	layout->addWidget(label);
	setLayout(layout);
	this->number = number;
	this->genre = genre;
	srv.addObserver(this);
}

void MelodieGUI::openGenreWindows() {
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			GenreWindow* window = new GenreWindow(srv, "rock", srv.nrAcelasiGen("rock"));
			window->show();
		}
		else if (i == 1) {
			GenreWindow* window = new GenreWindow(srv, "pop", srv.nrAcelasiGen("pop"));
			window->show();
		}
		else if (i == 2) {
			GenreWindow* window = new GenreWindow(srv, "disco", srv.nrAcelasiGen("disco"));
			window->show();
		}
		else if (i == 3) {
			GenreWindow* window = new GenreWindow(srv, "folk", srv.nrAcelasiGen("folk"));
			window->show();
		}
	}
}

void GenreWindow::update() {
	int number = srv.nrAcelasiGen(genre.toStdString());
	QString labelText = "Sunt " + QString::number(number) + " melodii din genul " + genre;
	label->setText(labelText);
}
