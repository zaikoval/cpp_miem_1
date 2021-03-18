#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector.h>
#include <iostream>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QtAlgorithms>
#include <List.h>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Vector <char> alph;
    for(int i=0;i<(int)tmpStr.size();i++)
        alph.push_back(tmpStr[i]);

    for (char w:alph)
        defText4.append(w);

    ui->textEdit->setText(defText4);
    ui->textEdit->setReadOnly(true);
    ui->lineEdit_3->setInputMask("BBBBBBBBBBBB");
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //FWD Button clicked
{
    if (ui->textEdit->toPlainText() != QString::fromStdString(tmpStr)) {
        std::reverse(defText4.begin(), defText4.end());
        ui->textEdit->setText(defText4);
    }
}

void MainWindow::on_pushButton_2_clicked() //RWD Button clicked
{
    if (ui->textEdit->toPlainText() == QString::fromStdString(tmpStr)) {
        std::reverse(defText4.begin(), defText4.end());
        ui->textEdit->setText(defText4);
    }
}

void MainWindow::on_pushButton_4_clicked() //chooseFile
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/Users/zaikoval/Desktop",
                                                    tr("Text files (*.txt)"));

    QFile file(fileName);
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            def5.push_back(line.toStdString());
        }
    }
    file.close();

    ui->listWidget->clear();
    for(std::string el:def5)
        ui->listWidget->addItem(QString::fromStdString(el));
     ui->listWidget->sortItems();
}



void MainWindow::on_pushButton_3_clicked() //Enter
{
    if (!ui->lineEdit->text().isEmpty()){ // можно добавить ещё мильён проверок или валидатор
        def5.push_back(ui->lineEdit->text().toStdString());
        ui->listWidget->clear();
        for(std::string el:def5)
            ui->listWidget->addItem(QString::fromStdString(el));
        ui->listWidget->sortItems();
    }
}

void MainWindow::on_pushButton_5_clicked() // clear list
{
    ui->listWidget->clear();
    this->def5.clear();
}

void MainWindow::on_pushButton_6_clicked() //a words
{
    ui->listWidget->clear();
    for (auto el:def5)
        if(el[0]=='a' || el[0]=='A')
            ui->listWidget->addItem(QString::fromStdString(el));
    ui->listWidget->sortItems();

}

void MainWindow::on_pushButton_7_clicked() //remove citrus
{
    ui->listWidget->clear();
    Vector <std::string> citrusLess;
    for (std::string el:def5)
        if (CitrusSet.find(QString::fromStdString(el).toLower()) == CitrusSet.end())
            citrusLess.push_back(el);

    for(std::string el:citrusLess)
        ui->listWidget->addItem(QString::fromStdString(el));
    ui->listWidget->sortItems();
}

void MainWindow::on_pushButton_8_clicked()
{

    QDate Date;
    if (!ui->lineEdit_2->text().isEmpty()){
        for (auto it = fmts.begin(); (it != fmts.end()) && !Date.isValid(); it++)
            Date = QDate::fromString(ui->lineEdit_2->text(), *it);
        if (Date.isValid())
            DatesList.push_back(Date);
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Warning");
            msgBox.setInformativeText("Invalid date format");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();

        }
        std::sort(DatesList.begin(), DatesList.end());
        std::reverse(DatesList.begin(), DatesList.end());
    }

    ui->listWidget_2->clear();
    for (auto el: DatesList)
        ui->listWidget_2->addItem(el.toString(fmts[2]));
}

void MainWindow::on_pushButton_9_clicked() // Enter N6
{
    if(!ui->lineEdit_3->text().isEmpty() && ui->lineEdit_3->hasAcceptableInput()){
        bs.append(std::bitset<12>(ui->lineEdit_3->text().toStdString()));
    }
}

void MainWindow::on_pushButton_11_clicked() // compute result
{
    std::string constVis;
    std::string lessEight;
    for (int i=0; i<bs.size(); i++){
        if (bs[i].count() == 12)
            constVis += " " + std::to_string(i+1);
        if (bs[i].count() < 8)
            lessEight += " " + std::to_string(i+1);
    }
    ui->lineEdit_4->setText(QString::fromStdString(constVis));
    ui->lineEdit_5->setText(QString::fromStdString(lessEight));

}

void MainWindow::on_pushButton_10_clicked() // clear N6
{
    bs.clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void MainWindow::on_pushButton_12_clicked() // N10 part1
{

    for (int i=1; i<=100; i++)
        def10.push_back(i*i);

    struct cust{
        void operator()(const int n){sqs += " " + std::to_string(n);}
        std::string sqs;
    };

    cust s = std::for_each(def10.begin(), def10.end(), cust());
    ui->textEdit_2->setText(QString::fromStdString(s.sqs));

}

void MainWindow::on_pushButton_13_clicked() // N10 part2
{
    struct new_vec{
        void operator()(int n){
            newOne.push_back((int)std::sqrt(n));
        };
        Vector <int> newOne;
    };


    new_vec Vec2 = std::for_each(def10.begin(), def10.end(), new_vec());

    struct cust{
        void operator()(int n){sqs += " " + std::to_string(n);}
        std::string sqs;
    };

    cust s = std::for_each(Vec2.newOne.begin(), Vec2.newOne.end(), cust());
    ui->textEdit_3->setText(QString::fromStdString(s.sqs));

}


void MainWindow::on_pushButton_14_clicked()
{
    QString type = ui->comboBox->currentText();
    QString fin;
    if (type == "char"){
        achar.clear();
        for( int i=0; i<5; i++){
            char s = 'a' + rand() % 26;
            achar.push_back(s);
            fin.append(s);
            fin.append(' ');
        }
        fin.remove(fin.size()-1, 1);
        ui->textEdit_4->setText(fin);
    }
    if (type == "int"){
        aint.clear();
        for( int i=0; i<5; i++){
            int s = rand() % 10;
            aint.push_back(s);
            fin.append(QString::number(s));
            fin.append(' ');
        }
        fin.remove(fin.size()-1, 1);
        ui->textEdit_4->setText(fin);
    }
    if (type == "bitset<67>"){
        abitset.clear();
        for( int i=0; i<5; i++){
            std::string f;
            for (int j=0; j<67;j++){
                if (rand() % 10 > 5)
                    f.append("0");
                else
                    f.append("1");
            }
            std::bitset<67> b(f);
            abitset.push_back(b);
            fin.append(QString::fromStdString(f));
            fin.append(' ');
        }
        fin.remove(fin.size()-1, 1);
        ui->textEdit_4->setText(fin);
    }

}


void MainWindow::on_pushButton_15_clicked() //bitwise left shift
{
    if (aint.size() != 0){
        QString newText;

        for (auto el:aint)
            newText.append(QString::number(intBitwiseLeftShift(el)));
        ui->textEdit_4->setText(newText);
    }
    if (achar.size() != 0){
        QString newText;

        for (auto el:achar)
            newText.append(charBitwiseLeftShift(el));
        ui->textEdit_4->setText(newText);
    }
    if (abitset.size() != 0){
        QString newText;

        for (auto el:abitset)
            newText.append(QString::fromStdString(bitsetBitwiseLeftShift(el).to_string()));
        ui->textEdit_4->setText(newText);
    }
}

void MainWindow::on_pushButton_16_clicked() //bitwise right
{
    if (aint.size() != 0){

        QString newText;

        for (auto el:aint)
            newText.append(QString::number(intBitwiseRightShift(el)));
        ui->textEdit_4->setText(newText);
    }
    if (achar.size() != 0){
        QString newText;

        for (auto el:achar)
            newText.append(charBitwiseRightShift(el));
        ui->textEdit_4->setText(newText);
    }
    if (abitset.size() != 0){
        QString newText;

        for (auto el:abitset)
            newText.append(QString::fromStdString(bitsetBitwiseRightShift(el).to_string()));
        ui->textEdit_4->setText(newText);
    }
}



void MainWindow::on_pushButton_17_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/Users/zaikoval/Desktop",
                                                    tr("Text files (*.txt)"));
    int i = 4;
    int j = -1;
    QFile file(fileName);
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            if(i==4){
                i = 0;
                j++;
                ui->tableWidget->insertRow(j);
            }
            line = stream.readLine();
            QTableWidgetItem *item=new QTableWidgetItem (line);
            ui->tableWidget->setItem(j, i, item);
            i++;

        }
    }
    file.close();
}

void MainWindow::on_pushButton_18_clicked()
{
    QString a = ui->lineEdit_6->text();
    if (a.toInt() > 0){
        Vector <int> uv;
        List <int> ul;
        for (int i=0; i<a.toInt(); i++){
            uv.push_back(i);
            ul.push_back(i);
        }
        unsigned int start_v =  clock();
        int elv = uv[(int)(a.toInt()/2)];
        unsigned int end_v =  clock();
        unsigned int v_time = end_v - start_v;
        unsigned int start_l =  clock();
        int ell = ul[(int)(a.toInt()/2)];
        unsigned int end_l =  clock();
        unsigned int l_time = end_l - start_l;
        ui->label_11->setText("Vector time: " + QString::number(v_time));
        ui->label_12->setText("List time: " + QString::number(l_time));
    }
}
