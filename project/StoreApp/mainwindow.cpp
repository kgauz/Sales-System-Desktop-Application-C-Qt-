#include "mainwindow.h"
#include "books.h"
#include "magazines.h"
#include "store.h"
#include <QWidget>
#include <QDebug>
#include "secondwindow.h"

MainWindow::MainWindow(Store* s,QWidget *parent)
    : QMainWindow(parent), store(s)
{

    title_label = new QLabel("Complete the required data");
    item_label = new QLabel("Item type");
    name_label = new QLabel("Name of item");
    box = new QComboBox();
    edit_name = new QLineEdit();
    add_button = new QPushButton("Add item");
    submit = new QPushButton("Done");

    //add types to the comboBox
    box->addItem("Books");
    box->addItem("Magazines");

    //layouts = new QGridLayout();
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    layouts= new QGridLayout(widget);


    setupUi();
    add_button->setEnabled(false);
    submit->setEnabled(false);

    connect(add_button,SIGNAL(clicked(bool)),this,SLOT(addItem()));
    connect(submit,SIGNAL(clicked(bool)),this,SLOT(closeWindow()));
    connect(edit_name,SIGNAL(textChanged(QString)),this,SLOT(enable()));


}

MainWindow::~MainWindow() {}

void MainWindow::addItem()
{
    Item *item = nullptr;

    if(box->currentText() == "Books")
    {
        item = new Books(edit_name->text());
    }
    else
    {
        item = new Magazines(edit_name->text());

    }

    store->addItem(item);


    if(store->getItemLIst().size() != 0)
    {
        submit->setEnabled(true);
    }
    else
    {
        submit->setEnabled(false);
    }


    emit items();
    edit_name->clear();

}

void MainWindow::closeWindow()
{
   emit closed();
   this->close();
}

void MainWindow::enable()
{
    if(edit_name->text().size() != 0)
    {
        add_button->setEnabled(true);
    }
    else
    {
        add_button->setEnabled(false);
    }
}

void MainWindow::setupUi()
{
    setWindowTitle("Add Item");

    layouts->addWidget(title_label,0,1);
    layouts->addWidget(item_label,1,0);
    layouts->addWidget(box,1,1);
    layouts->addWidget(name_label,2,0);
    layouts->addWidget(edit_name,2,1);
    layouts->addWidget(add_button,5,1);
    layouts->addWidget(submit,6,1,2,2);

}
