#include "transactionmainwindow.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include "udpsenderthread.h"
#include <QDomDocument>
#include "customernamewindow.h"
#include "mainwindow.h"

TransactionMainWindow::TransactionMainWindow(TransactionList *TranList, CustomerList *cusLists, Store *s,QWidget *parent)
    : QMainWindow{parent}, list(TranList), customerLists(cusLists),  store(s)
{
    // Setup toolbars
    file = new QToolBar("File", this);
    add = new QToolBar("Add", this);
    restore = new QToolBar("Restore", this);

    QAction* showXmlAction = new QAction("file", this);
    file->addAction(showXmlAction);

    QAction* addCustomerAction = new QAction("Add", this);
    add->addAction(addCustomerAction);
    connect(addCustomerAction, &QAction::triggered, this, &TransactionMainWindow::onAddCustomerClicked);

    QAction* restoreAction = new QAction("Restore", this);
    restore->addAction(restoreAction);
    connect(restoreAction, &QAction::triggered, this, &TransactionMainWindow::onRestoreClicked);


    connect(showXmlAction, &QAction::triggered, this, &TransactionMainWindow::onShowXmlClicked);



    addToolBar(file);
    addToolBar(add);
    addToolBar(restore);

    // Create central widget
    widget = new QWidget(this);
    setCentralWidget(widget);

    // Layout to manage the tree view
    layout = new QVBoxLayout();
    widget->setLayout(layout); // You were missing this line

    // Create and configure tree view
    tree = new QTreeView(this);
    itemModel = new QStandardItemModel(this);

    layout->addWidget(tree); // Ensure tree is added before setup


}


void TransactionMainWindow::setupUi()
{
    itemModel->clear();
    itemModel->setHorizontalHeaderLabels({"Transaction", "Type", "Quantity"});

    if (!list || !customerLists) {
        qDebug() << "Error: 'list' or 'customerLists' is null!";
        return;
    }

    QStringList customerNames = customerLists->getCustomerNamesAsStrings();
    qDebug() << "Customer list: " << customerNames;

    for (const QString &customerName : std::as_const(customerNames)) {
        QStandardItem *customerItem = new QStandardItem(customerName);

        QList<Transaction*> allTransactions = list->getRecordList();
        QList<Transaction*> transactions;
        for (Transaction* t : allTransactions) {
            if (t->getCN() == customerName) {
                transactions.append(t);
            }
        }

        if (transactions.isEmpty()) {
            customerItem->appendRow({
                new QStandardItem("No Transactions"),
                new QStandardItem(""),
                new QStandardItem("")
            });
        } else {
            // Group by formatted date string
            QMap<QString, QStandardItem*> dateMap;

            for (Transaction *record : std::as_const(transactions)) {
                QString dateStr = record->getDateTime().toString("yyyy/MM/dd HH:mm");
                QStandardItem *dateItem;

                if (!dateMap.contains(dateStr)) {
                    dateItem = new QStandardItem(dateStr);
                    dateMap[dateStr] = dateItem;
                    customerItem->appendRow({dateItem, new QStandardItem(), new QStandardItem()});
                } else {
                    dateItem = dateMap[dateStr];
                }

                QStandardItem *itemName = new QStandardItem(record->getItem());
                QStandardItem *typeItem = new QStandardItem(record->getType());
                QStandardItem *quantityItem = new QStandardItem(QString::number(record->getQuantity()));

                dateItem->appendRow({itemName, typeItem, quantityItem});
            }
        }

        itemModel->appendRow({customerItem, new QStandardItem(), new QStandardItem()});
    }

    tree->setModel(itemModel);
    tree->setHeaderHidden(false);
    tree->expandAll();

    // Stretch header nicely
    tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setWindowTitle("Transaction Viewer");

}

void TransactionMainWindow::refresh()
{
    setupUi();
}

void TransactionMainWindow::onShowXmlClicked()
{
    QString xml = generateXmlFromRecords();

    for (Transaction* t : list->getRecordList()) {
        if (!t) {
            qDebug() << "Null transaction skipped.";
            continue;
        }

        if (t->getItem().isEmpty()) {
            qDebug() << "Empty item name in transaction!";
            continue;
        }


    }


    UdpSenderThread *senderThread = new UdpSenderThread(xml, this);
    connect(senderThread, &QThread::finished, senderThread, &QObject::deleteLater); // <== important!
    senderThread->start();


    if (xmlWindow) {
        xmlWindow->close();
        xmlWindow = nullptr;
    }


     xmlWindow = new XmlDisplayWindow(xml);
    // xmlWindow->setAttribute(Qt::WA_DeleteOnClose);  // Auto delete when closed
    xmlWindow->show();
}

QString TransactionMainWindow::generateXmlFromRecords()
{
    QDomDocument doc;

    // Add XML version manually
    QDomProcessingInstruction xmlVersion = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(xmlVersion);

    QDomElement root = doc.createElement("ModelData");
    doc.appendChild(root);

    QStringList customerNames = customerLists->getCustomerNamesAsStrings();

    for (const QString &customerName : std::as_const(customerNames)) {
        QDomElement customerElem = doc.createElement("customer");
        customerElem.setAttribute("name", customerName.isEmpty() ? "NoCustomer" : customerName);
        root.appendChild(customerElem);

        for (Transaction* t : list->getRecordList()) {
            if (!t) continue;

            QDomElement transElem = doc.createElement("transaction");
            transElem.setAttribute("date", t->getDateTime().toString(Qt::ISODate));

            QDomElement lineitem = doc.createElement("lineitem");
            lineitem.setAttribute("name", t->getItem());
            lineitem.setAttribute("type", t->getType());
            lineitem.setAttribute("quantity", QString::number(t->getQuantity()));

            transElem.appendChild(lineitem);
            customerElem.appendChild(transElem);
        }
    }

    return doc.toString(4); //
}

void TransactionMainWindow::onAddCustomerClicked()
{
    if (!transWindow) {
        transWindow = new SecondWindow(store, customerLists, list, this);
        transWindow = nullptr;
    }

}

void TransactionMainWindow::onRestoreClicked()
{
    if (store) {
        store->restore();
        refresh(); // Refresh the tree view if applicable
    } else {
        qDebug() << "No store attached!";
    }
}






