#include "secondwindow.h"
#include "books.h"
#include "customerlist.h"
#include "store.h"
#include "transaction.h"
#include "transactionlist.h"
#include <QWidget>
#include <qdatetime.h>
#include <QDateTime>
#include <QDebug>
#include "customernamewindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "transactionmainwindow.h"
#include "magazines.h"

SecondWindow::SecondWindow( Store *str, CustomerList *customers, TransactionList *transactions,QWidget *parent)
    : QMainWindow{parent} , storeBook(str), customerName(customers), tranList(transactions)
{

    labelTitle =new QLabel("Complete the required data");
    labelCustomer =new QLabel("Select the customer");
    labelItem =new QLabel("Select the item");
    typeLabel =new QLabel("Item type");
    quantityLabel = new QLabel("Item quantity");
    comboBoxCustomer = new QComboBox();
    comboBoxItem = new QComboBox();
    spinBox = new QSpinBox();
    listWidget = new QListWidget();
    addButton = new QPushButton("Add item");
    doneButton = new QPushButton("Done");
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    layout = new QGridLayout(widget);
    t = new QLabel;

    setupUi();

    // Open CustomerNameWindow to add new customers
    CustomerNameWindow *customerWindow = new CustomerNameWindow(customerName, this);
     customerWindow->show();
    window = new MainWindow(storeBook, this);

    spinBox->setMinimum(1);
    spinBox->setMaximum(10000);


    connect(addButton,SIGNAL(clicked(bool)),this,SLOT(addItem2()));
    connect(doneButton,SIGNAL(clicked(bool)),this,SLOT(exit()));

    connect(customerWindow, &::CustomerNameWindow::customerAded, this, &SecondWindow::updateCustomerComboBox);

    connect(window, &::MainWindow::items, this, &::SecondWindow::updateItemComboBox);
    connect(customerWindow,&::CustomerNameWindow::showItemWindow,this,&SecondWindow::showItemsW);
    connect(window, &MainWindow::closed, this, &SecondWindow::show);
    connect(comboBoxItem, &QComboBox::currentTextChanged,this, &SecondWindow::onComboBoxTextChanged);


}

void SecondWindow::onComboBoxTextChanged(const QString &text)
{
    QString type;

    for(auto i : storeBook->getItemLIst())
    {
        if(text==i->getName())
        {
            type = i->getType();
        }
    }
    t->setText(type);
}

void SecondWindow::check(QString n, QString i)
{
    if(tranList->checkItem(n,i))
    {
        QMessageBox::information(this,"Item Lists","Item is is added to the record");
    }
    else
    {
        QMessageBox::warning(this,"Item List","Item already exists in the record");
    }

}

void SecondWindow::addItem2()
{
    QString name = comboBoxCustomer->currentText();
    QString type = "unknown";
    QString selectedItem = comboBoxItem->currentText();

    for (Item* i : storeBook->getItemLIst()) {
        if (i->getName() == selectedItem) {
            type = i->getType();
            break;

        }
    }

    tran = new Transaction(comboBoxItem->currentText(),type,spinBox->value(),QDateTime::currentDateTime(),comboBoxCustomer->currentText());

    listWidget->addItem(tran->getItem() + " (" + type + ") x" + QString::number(tran->getQuantity()));

    check(name, selectedItem);


    tranList->record(name,tran);

    spinBox->setValue(0);

}

void SecondWindow::exit()
{
    emit customerListFinalized();
    emit showTranWindow();
    this->close();
}

void SecondWindow::setupUi()
{
     setWindowTitle("Shop");
    layout->addWidget(labelTitle, 0,1);
    layout->addWidget(labelCustomer, 1,0);
    layout->addWidget(comboBoxCustomer, 1,1);
    layout->addWidget(labelItem, 2,0);
    layout->addWidget(comboBoxItem, 2,1);
    layout->addWidget(typeLabel, 3,0);
    layout->addWidget(t, 3,1);
    layout->addWidget(quantityLabel, 4,0);
    layout->addWidget(spinBox, 4,1);
    layout->addWidget(addButton, 4,2);
    layout->addWidget(listWidget, 5,0,2,3);
    layout->addWidget(doneButton, 7,1,1,1);

}

void SecondWindow::updateCustomerComboBox()
{
    comboBoxCustomer->clear();
    for (int i = 0; i < customerName->getCustomerNameList().size(); i++) {
        comboBoxCustomer->addItem(customerName->getCustomerNameList().at(i)->getName());
    }

}

void SecondWindow::updateItemComboBox()
{
    comboBoxItem->clear();
    QSet<QString> seenNames;
    for(int i =0; i < storeBook->getItemLIst().size(); i++ )
    {
        QString name = storeBook->getItemLIst().at(i)->getName();

        if (!seenNames.contains(name)) {
            seenNames.insert(name);
            comboBoxItem->addItem(name);
        }
    }
}

void SecondWindow::showItemsW()
{
    window->show();
}

void SecondWindow::showThirdW()
{
    emit showThirdWindow();
}


