#include "MainWindow.h"
#include "SidePanel.h"
#include "SplitView.h"
#include "ToolBar.h"
#include "ToolButton.h"
#include "PushButton.h"
#include "Alert.h"
#include "SimpleMessage.h"
#include "PixmapBuilder.h"
#include <QApplication>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QLabel>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	auto *widget = new QWidget(this);
	auto *toolBar = new ToolBar(this);
	auto *splitView = new SplitView(this);
	auto *sidePanel = new SidePanel();
	auto layoutMain = new QVBoxLayout(widget);
	auto *btnMenu = new ToolButton();
	auto *btnAlert = new PushButton();
	auto *btnDrumset = new PushButton();
	auto *labTitle = new QLabel(this);
	auto *labFooter = new QLabel(this);
	auto *labBody = new QLabel(this);

	QPalette p;

	p.setColor(QPalette::Window, QColor("#F0F1F2"));
	p.setColor(QPalette::WindowText, QColor("#303030"));
	p.setColor(QPalette::Base, QColor("#50585D"));
	p.setColor(QPalette::Button, QColor("#FFFFFF"));
	p.setColor(QPalette::Dark, QColor("#50585D"));
	p.setColor(QPalette::Text, QColor("#616b71"));
	p.setColor(QPalette::Highlight, QColor("#15999B"));
	p.setColor(QPalette::Link, QColor("#15999B"));

	QApplication::setPalette(p);
	QApplication::setFont(QFont("MS Shell Dlg 2", 11));

	btnMenu->setPixmap(PixmapBuilder::create(PixmapBuilder::Menu,
											 palette().color(QPalette::Button),
											 16));
	btnMenu->setSize(48);

	labBody->setContentsMargins(12, 12, 12, 12);
	labBody->setWordWrap(true);
	labBody->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	labBody->setText("<p>The FlatGUI library allows Qt5 users to build elegant "
				   "graphical user interfaces for desktop applications in C++ "
				   "without the need of using technologies other than widgets. "
				   "The GUI elements are tested fully under Windows 7/10 and "
				   "partially under Ubuntu 17 Desktop. The library is open "
				   "source and you are welcome to use it and contribute to it.</p>"
				   "<p>Enjoy!</p>"
				   "<p>P.S. I play drums too. Check them out. :)</p>");

	labTitle->setOpenExternalLinks(true);
	labTitle->setText(tr("Created with <a style='text-decoration: none' href='%1'>FlatGUI"
						 "</a> by <a style='text-decoration: none;' href='%2'>Michael "
						 "Scopchanov</a>.")
					  .arg(QStringLiteral("https://github.com/scopchanov/flat-gui"))
					  .arg(QStringLiteral("https://de.linkedin.com/in/michael-scopchanov")));

	toolBar->addSpacing(12);
	toolBar->addWidget(labTitle);
	toolBar->addStretch();
	toolBar->addWidget(btnMenu);
	toolBar->setMaximumHeight(48);
	toolBar->setBackgroundRole(QPalette::Dark);

	btnAlert->setText(tr("Show alert"));
	btnDrumset->setText(tr("My drumset"));

	QFont f(font());

	f.setPointSize(10);

	labFooter->setFont(f);
	labFooter->setAlignment(Qt::AlignRight);
	labFooter->setText(tr("Landau/Pfalz<br />"
						  "Germany, 2018"));
	labFooter->setForegroundRole(QPalette::Text);
	labFooter->setStyleSheet(".QLabel { padding: 9px; }");

	sidePanel->addWidget(btnAlert);
	sidePanel->addWidget(btnDrumset);
	sidePanel->addStretch();
	sidePanel->addWidget(labFooter);
	sidePanel->setFixedWidth(150);

	splitView->setBaseWidget(labBody);
	splitView->setSideWidget(sidePanel);

	layoutMain->addWidget(toolBar);
	layoutMain->addWidget(splitView);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	setCentralWidget(widget);
	resize(480, 640);

	connect(btnMenu, &ToolButton::clicked, splitView, &SplitView::splitScreen);
	connect(btnAlert, &PushButton::clicked, this, &MainWindow::onAlert);
	connect(btnDrumset, &PushButton::clicked, this, &MainWindow::onDrumset);
}

void MainWindow::onAlert()
{
	if (Alert::showAlert(this,
						 PixmapBuilder::create(PixmapBuilder::Warning,
											   palette().color(QPalette::Highlight), 48),
						 tr("This is an alert"),
						 tr("Write text to alert the user<br />"
							"about something and let him/her<br />"
							"decide what to do next."),
						 QStringList({tr("Deny"), tr("Accept")}), 1))
		SimpleMessage::showMessage(this,
								   PixmapBuilder::create(PixmapBuilder::Info,
														 palette().color(QPalette::Highlight), 48),
								   tr("Accepted"), 3000);
	else
		SimpleMessage::showMessage(this,
								   PixmapBuilder::create(PixmapBuilder::Error,
														 palette().color(QPalette::Highlight), 48),
								   tr("Denied"), 3000);
}

void MainWindow::onDrumset()
{
	QDesktopServices::openUrl(QUrl::fromUserInput("https://scontent-frx5-1.xx.fbcdn.net/v/t1.0-9/"
												  "13427_991617647537157_7716924885763298239_n.jpg"
												  "?oh=41dfd0b279f215501ac56ca13ca52197&oe=5B25516E"));
}
