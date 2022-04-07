#pragma once

#include <memory>

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>

#include "environment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitMenuBar();

    Ui::MainWindow *ui;
    Environment* _environment;
    QString _currentFile;

private slots:
    void FileOpen();
};
