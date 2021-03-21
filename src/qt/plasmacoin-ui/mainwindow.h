#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
};

#endif // MAINWINDOW_H
