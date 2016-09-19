#include "gui.h"
#include "ui_mainwindow.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
}

Gui::~Gui()
{
    delete ui;
}
