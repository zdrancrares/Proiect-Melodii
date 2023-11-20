#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MelodiiOOP.h"

class MelodiiOOP : public QMainWindow
{
    Q_OBJECT

public:
    MelodiiOOP(QWidget *parent = nullptr);
    ~MelodiiOOP();

private:
    Ui::MelodiiOOPClass ui;
};
