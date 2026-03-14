#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QListWidget>

class Books;
class Magazines;
class Store;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Store *s, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void items();
    void closed();

public slots:
    void addItem();
    void closeWindow();
    void enable();

private:
    void setupUi();
    QLabel *title_label;
    QLabel *item_label;
    QLabel *name_label;
    QPushButton *add_button;
    QLineEdit *edit_name;
    QGridLayout *layouts;
    QComboBox *box;
    Books *book;
    Magazines *magazine;
    Store *store;
    QPushButton *submit;
    MainWindow *window;

};
#endif // MAINWINDOW_H

