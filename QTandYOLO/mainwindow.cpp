#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <QList>
#include <QString>

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

void MainWindow::on_startButton_clicked()
{
    QMessageBox::information(this, "Important", "To finish the application, press 'Q'."); // Message to user

    QString pythonPath = "C:/Users/user/OneDrive/Área de Trabalho/QT/ProjectQTandYOLO/PythonPast/venv/Scripts/python.exe";  // Replace the python compiler inside past venv in your computer
    QString scriptPath = "C:/Users/user/OneDrive/Área de Trabalho/QT/ProjectQTandYOLO/PythonPast/Yolo-Webcam.py";  // Replace the file .py path in your computer

    QStringList arguments;
    // arguments << "arg1" << "arg2";  // Addition arguments

    //Configure the process
    QProcess *process = new QProcess(this);
    process->start(pythonPath, QStringList() << scriptPath << arguments);

    // Waiting to finish process
    if (process->waitForFinished()) {
        qDebug() << "Script Python executed successfully!";
    } else {
        qDebug() << "Error executing Python script: " << process->errorString();
    }

    QByteArray output = process->readAllStandardOutput();

    // Convert the output to string and print on screen

        QString outputString = QString::fromUtf8(output);
        qDebug() << "Output Python:" << outputString;

        QStringList lines = outputString.split("\r\n", Qt::SkipEmptyParts);

        // Create a QList<QString> based on lines
        QList<QString> nomeObjetos = lines;

        QString resultado = QString::number(nomeObjetos.size()) + " objects were found!\nThere may be errors!";

        QMessageBox::information(this, "Detected Objects", resultado);

}



