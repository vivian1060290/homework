#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();

private:
    QTextEdit *textEdit;
    QString currentFile;
    bool confirmSave();
    void saveToFile(const QString &fileName);
};

#endif // MAINWINDOW_H
