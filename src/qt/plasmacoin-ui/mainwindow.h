#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	// Cycle the QStackedWidget object to display the correct information
	// on the correct tab
	void UpdateWindow();

private:
	QTabWidget* m_TabBar = Ui::MainWindow::tabWidget;

private slots:
	void DisplayPage(int index); // Actually set the index of the stack widget
};

#endif // MAINWINDOW_H
