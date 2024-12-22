#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    QMenu *fileMenu = menuBar()->addMenu("檔案");
    QAction *newAction = new QAction("新增", this);
    QAction *openAction = new QAction("開啟", this);
    QAction *saveAction = new QAction("儲存", this);
    QAction *saveAsAction = new QAction("另存", this);
    QAction *closeAction = new QAction("關閉", this);
    QAction *exitAction = new QAction("退出", this);

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    setWindowTitle("主視窗");
    resize(800, 600);
}

void MainWindow::newFile() {
    if (!textEdit->document()->isModified() || confirmSave()) {
        textEdit->clear();
        currentFile.clear();
    }
}

void MainWindow::openFile() {
    if (!textEdit->document()->isModified() || confirmSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, "開啟檔案", QString(), "文字檔案 (*.txt);;所有檔案 (*.*)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::Text)) {
                textEdit->setPlainText(file.readAll());
                currentFile = fileName;
            } else {
                QMessageBox::warning(this, "錯誤", "無法開啟檔案！");
            }
        }
    }
}

void MainWindow::closeFile() {
    if (!textEdit->document()->isModified() || confirmSave()) {
        textEdit->clear();
        currentFile.clear();
    }
}

void MainWindow::saveFile() {
    if (currentFile.isEmpty()) {
        saveFileAs();
    } else {
        saveToFile(currentFile);
    }
}

void MainWindow::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "另存檔案", QString(), "文字檔案 (*.txt);;所有檔案 (*.*)");
    if (!fileName.isEmpty()) {
        saveToFile(fileName);
    }
}

bool MainWindow::confirmSave() {
    auto reply = QMessageBox::question(this, "確認", "檔案尚未儲存，是否儲存？",
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
        saveFile();
        return true;
    }
    return reply == QMessageBox::No;
}

void MainWindow::saveToFile(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(textEdit->toPlainText().toUtf8());
        currentFile = fileName;
        textEdit->document()->setModified(false);
    } else {
        QMessageBox::warning(this, "錯誤", "無法儲存檔案！");
    }
}
