#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <vector.h>
#include <bitset>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();


    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

private:
    Ui::MainWindow *ui;
    QString defText4;
    Vector <std::string> def5;
    const std::string tmpStr = "abcdefghijklmnopqrstuvwxyz";
    QSet <QString> CitrusSet = {"lemon", "orange", "lime"};
    QList <QString> fmts = {"MMMyy", "dd/M/yyyy", "dd-M-yyyy"};
    QList <QDate> DatesList;
    QList <std::bitset <12>> bs;
    Vector <int> def10;
    Vector <int> aint;
    Vector <int> achar;
    Vector <std::bitset <67>> abitset;

    int intBitwiseLeftShift(int a){return (a<<1);};
    int intBitwiseRightShift(int a){return (a>>1);};
    char charBitwiseLeftShift(char a){return (a<<1);};
    char charBitwiseRightShift(char a){return (a>>1);};
    std::bitset<67> bitsetBitwiseLeftShift(std::bitset<67> a){return (a<<1);};
    std::bitset<67> bitsetBitwiseRightShift(std::bitset<67> a){return (a>>1);};

};
#endif // MAINWINDOW_H
