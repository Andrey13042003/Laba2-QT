#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_loaddata_clicked() {//обрабатываем кнопку "Загрузить данные"
    QString FileName = ui->namefile->text();
    QString RegName = ui->nameregion->text();
    if (FileName.isEmpty()) { // если не ввели название файла
        ui->error->setText("Файл не выбран!");
        return;
    } else if (RegName.isEmpty()) {//Если не указали название региона
        ui->error->setText("Не введено название региона!");
        return;
    } else {//выводим
        ui->error->setText("");
        FunctionArgument struct_for_output = {
            .filename = QStringToCharLine(FileName), // переводим QString в char
            .regionname = QStringToCharLine(RegName)
        };
        FuncReturningValue* for_output = entryPoint(getDataFromFile, &struct_for_output);
        showData(for_output);//выводим на экран
        entryPoint(cleanData, &struct_for_output);
        free(for_output);
    }
}

void MainWindow::on_pushButton_calculations_clicked() { //обрабатываем кнопку "Вычислить данные"
    QString NumColumn = ui->numbercolomn->text();//вводим номер колонки
    if (NumColumn.isEmpty()) {
        ui->error->setText("Не введен номер колонки!");
    } else {
        ui->error->setText("");
        FunctionArgument struct_for_output{
            .numcolumns = ui->numbercolomn->text().toInt(), //к типу int
            .data = getDataFromTable(), // получаем данные из таблицы
            .lines = (size_t)ui->TableWidget->rowCount(), //количество строк
            .coloumns = (size_t)ui->TableWidget->columnCount(), //количество колонок
        };
        if ((size_t)struct_for_output.numcolumns > struct_for_output.coloumns) // если введенный номер колонки больше количества колонок
            ui->error->setText("Вычисления недопустимы!");
        else {
            FuncReturningValue* tmp = entryPoint(calculationData, &struct_for_output);
            if ((tmp->calculation_res[NUM_MAX] != DEBAG) && (tmp->calculation_res[NUM_MIN] != DEBAG) && (tmp->calculation_res[NUM_MED] != DEBAG)) {
                ui->max->setText(QString::number(tmp->calculation_res[NUM_MAX])); //выводим
                ui->min->setText(QString::number(tmp->calculation_res[NUM_MIN]));
                ui->med->setText(QString::number(tmp->calculation_res[NUM_MED]));
            } else {
                ui->error->setText("Вычисления недопустимы!");
            }
            entryPoint(cleanData, &struct_for_output); // для чего нужна эта строчка?
            free(tmp);
        }
    }
}

void MainWindow::showData(FuncReturningValue* for_output) { //выводим данные в таблицу
    ui->TableWidget->setColumnCount(for_output->coloumns);
    QStringList QColumns = ConvertRowToQTFormat(for_output->table_headers, for_output->coloumns);
    ui->TableWidget->setHorizontalHeaderLabels(QColumns);
    if (for_output->data != NULL) {
        ui->TableWidget->setRowCount(for_output->lines);
        for(size_t i = 0; i < for_output->lines; i++) {
            QStringList currentSeries = ConvertRowToQTFormat(*((for_output)->data + i), for_output->coloumns);
            ui->TableWidget->setRowCount(i + 1);
            for(int j = 0; j < currentSeries.count(); j++) {
                QTableWidgetItem *Item = new QTableWidgetItem();
                Item->setData(Qt::EditRole, currentSeries.at(j));
                Item->setText(currentSeries.at(j));
                ui->TableWidget->setItem(i, j, Item);
            }
        }
    }
}

char*** MainWindow::getDataFromTable() {
    char*** data = (char***)malloc(sizeof(char**) * ui->TableWidget->rowCount());
    if (data != NULL){
        for(size_t i = 0; i < (size_t)ui->TableWidget->rowCount(); i++) {
            *(data + i) = (char**)malloc(sizeof(char*) * ui->TableWidget->columnCount());
            for(size_t j = 0; j < (size_t)ui->TableWidget->columnCount(); j++) {
                QTableWidgetItem *item = ui->TableWidget->item(i,j);
                char *str = QStringToCharLine(item->text());
                data[i][j] = str;
            }
        }
    }
    return data;
}

char* QStringToCharLine(QString FileName) {
    char* new_str = (char*)malloc(sizeof(char) * (FileName.size() + 1));
    if(new_str != NULL){
        for(qsizetype i = 0; i < FileName.size(); i++) {
            *(new_str + i) = FileName.at(i).unicode();
        }
        *(new_str + FileName.size()) = 0;
    }

    return new_str;
}

QStringList ConvertRowToQTFormat(char** row, size_t size) {
    QStringList nstr;
    for(size_t i = 0; i < size; i++) {
        nstr.append(*(row + i));
    }

    return nstr;
}

void MainWindow::on_pushButton_openfile_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", "CSV File (*.csv)");
    ui->namefile->setText(FileName);
    if(FileName.isEmpty()) {
        ui->error->setText("Файл не выбран!");
        return;
    }
}

