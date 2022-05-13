#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringList>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QLabel>
#include "logic.h"
#include <QFileDialog>

char* QStringToCharLine(QString FileName);
QStringList ConvertRowToQTFormat(char** row, size_t size);

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

    void on_pushButton_loaddata_clicked();//кнопка загрузить данные

    void on_pushButton_calculations_clicked();//кнопка вычислить

    void on_pushButton_openfile_clicked();//кнопка открыть файл

private:
    Ui::MainWindow *ui;

    void showData(FuncReturningValue* for_output);

    char*** getDataFromTable();
};

#endif // MAINWINDOW_H

