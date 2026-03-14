#include "customernamewindow.h"
#include "customer.h"
#include <QDebug>
#include <QMessageBox>

CustomerNameWindow::CustomerNameWindow(CustomerList *existingList, QWidget *parent)
    : QMainWindow{parent}, list(existingList)
{
    name_label = new QLabel("Customer Name");
    lineEdit = new QLineEdit();
    button = new QPushButton("Add Customer Name");
    widget = new QWidget(this);
    setCentralWidget(widget);
    layout = new QGridLayout(widget);

    setWindowTitle("Add customer");

    //add item to the layout
    layout->addWidget(name_label,0,0);
    layout->addWidget(lineEdit,0,1);
    layout->addWidget(button, 2,1,1,1);

    doneButton = new QPushButton("Done");
    layout->addWidget(doneButton, 3, 1, 1, 1);

    button->setEnabled(false);
    doneButton->setEnabled(false);

    connect(doneButton, &QPushButton::clicked, this, &CustomerNameWindow::emitFinalized);
    connect(lineEdit,SIGNAL(textChanged(QString)),this, SLOT(display()));
    connect(button,SIGNAL(clicked(bool)),this,SLOT(addNames()));

}

void CustomerNameWindow::addNames()
{
    customer = new Customer(lineEdit->text());
    list->addCustomerNames(customer);

    lineEdit->clear();
    lineEdit->setFocus();

    if(list->getCustomerNameList().size() != 0)
    {
        doneButton->setEnabled(true);
    }
    else
    {
        doneButton->setEnabled(false);
    }


}

void CustomerNameWindow::emitFinalized()
{
    emit customerAded();
    emit showItemWindow();
    this->close();        // Close the window
}

void CustomerNameWindow::display()
{
    if(lineEdit->text().size() != 0)
    {
        button->setEnabled(true);
    }
    else
    {
        button->setEnabled(false);
    }

}

