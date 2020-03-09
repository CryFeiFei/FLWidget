#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef Q_OS_WIN
#include "flwidget.h"
#else
#include "flwidget_linux.h"
#endif

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
#ifdef Q_OS_WIN
	ui->linuxBtn->setVisible(false);
#else
	ui->winBtn->setVisible(false);
#endif

	connect(ui->winBtn, &QPushButton::clicked, this, &MainWindow::showWinFLWidget);
	connect(ui->linuxBtn, &QPushButton::clicked, this, &MainWindow::showLinuxFLWidget);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showWinFLWidget()
{
#ifdef Q_OS_WIN
	FLWidget* flWidget = new FLWidget(this);
	flWidget->show();
#endif
}

void MainWindow::showLinuxFLWidget()
{
#ifdef Q_OS_LINUX
	FLWidget_Linux* flWidget = new FLWidget_Linux(this);
	flWidget->show();
#endif
}
