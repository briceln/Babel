/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <QtCore/QCoreApplication>
#include <sstream>
#include <iostream>
#include <includes/client/UI/Home.hpp>

#include "includes/client/UI/Home.hpp"
#include "includes/common/PrintVector.hpp"

Babel::UI::Home::Home(QStackedWidget *stack, TCPNetwork *tcpNetwork)
	: QWidget(), _tcpNetwork(tcpNetwork), _width(300), _height(300),
	_font("Pacifico", 20, 2), _stack(stack)
{
	QIcon tmp(QCoreApplication::applicationDirPath() + "/media/call.png");
	QIcon mic(QCoreApplication::applicationDirPath() + "/media/mic.png");
	QIcon log(QCoreApplication::applicationDirPath() + "/media/logout.png");
	_icon         = tmp;
	_timer        = new QTimer;
	_username     = new QLabel("Username");
	_listWidget   = new QListWidget;
	_logout       = new QPushButton;
	_call         = new QPushButton("Call");
	_test         = new QPushButton("Test Micro");
	_buttonLayout = new QHBoxLayout;
	_header       = new QHBoxLayout;
	_layout       = new QVBoxLayout;
	_call->setIcon(_icon);
	_call->setIconSize(QSize(30, 30));
	_test->setIcon(mic);
	_test->setIconSize(QSize(30, 30));
	_logout->setIcon(log);
	_logout->setIconSize(QSize(30, 30));
	_username->setAlignment(Qt::AlignCenter);
	_username->setFont(_font);
	_buttonLayout->addWidget(_test);
	_buttonLayout->addWidget(_call);
	_header->addWidget(_username);
	_header->addWidget(_logout);
	_layout->addLayout(_header);
	_layout->addWidget(_listWidget);
	_layout->addLayout(_buttonLayout);
	setLayout(_layout);
	connect(_call, SIGNAL(clicked()), this, SLOT(makeCall()));
	connect(_listWidget, SIGNAL(currentTextChanged(const QString & )), this, SLOT(changeButtonName(const QString & )));
	connect(_test, SIGNAL(clicked()), this, SLOT(makeTestCall()));
	connect(_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this, SLOT(itemDoubleClicked(QListWidgetItem * )));
	connect(_logout, SIGNAL(clicked()), this, SLOT(logout()));
	connect(_tcpNetwork, SIGNAL(dataToRead(QString)), this, SLOT(readData(QString)));
	connect(_tcpNetwork, SIGNAL(incomingCall(QString)), this, SLOT(takeIncomingCall(QString)));
	connect(_timer, SIGNAL(timeout()), this, SLOT(whoCall()));
	_listWidget->addItems(_contact);
	_timer->start(2000);
	_font.setPointSize(15);
	_listWidget->setFont(_font);
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string              token;
	std::istringstream       tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void Babel::UI::Home::makeCall()
{
	std::map<std::string, std::string>::iterator iterator;

	if (_contact.isEmpty()) {
		return;
	}
	_name    = _listWidget->currentItem()->text().toStdString();
	iterator = _contactIp.find(_name);
	if (iterator == _contactIp.end()) {
		return;
	}
	_tcpNetwork->writeData("2|" + (*iterator).first);
	_ip = (*iterator).second;
	_stack->setCurrentIndex(2);
}

void Babel::UI::Home::changeButtonName(QString const &currentText)
{
	_call->setText("Call (" + currentText + ").");
}

const std::string &Babel::UI::Home::getIp() const
{
	return _ip;
}

const std::string &Babel::UI::Home::getName() const
{
	return _name;
}

void Babel::UI::Home::makeTestCall()
{
	_ip   = "127.0.0.1";
	_name = _username->text().toStdString();
	_stack->setCurrentIndex(2);
}

void Babel::UI::Home::setUsername(QString &username)
{
	_username->setText(username);
}

void Babel::UI::Home::itemDoubleClicked(QListWidgetItem *listWidgetItem)
{
	(void)listWidgetItem;
	makeCall();
}

void Babel::UI::Home::logout()
{
	_tcpNetwork->writeData("1|" + _username->text().toStdString());
	_stack->setCurrentIndex(0);
}

void Babel::UI::Home::readData(QString data)
{
	std::string tmp = data.toStdString();

	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.end());
	std::cout << "Parse" << tmp << std::endl;
	_contact.clear();
	if (tmp.find('|') != std::string::npos) {
		std::vector<std::string> users = split(tmp, '|');
		for (auto &user : users) {
			std::vector<std::string> info = split(user, ':');
			_contact << QString::fromStdString(info[1]);
			_contactIp.insert({info[1], info[0]});
		}
	} else {
		std::vector<std::string> info = split(tmp, ':');
		_contact << QString::fromStdString(info[1]);
		_contactIp.insert({info[1], info[0]});
	}
	_listWidget->clear();
	_listWidget->addItems(_contact);
}

void Babel::UI::Home::whoCall()
{
	if (_stack->currentIndex() != _stack->indexOf(this)) {
		return;
	}
	_tcpNetwork->writeData("5|" + _username->text().toStdString());
}

void Babel::UI::Home::takeIncomingCall(QString ip)
{
	if (_stack->currentIndex() != _stack->indexOf(this)) {
		return;
	}
	_ip = ip.toStdString();
	_ip.erase(std::remove(_ip.begin(), _ip.end(), '\n'), _ip.end());
	_name = "Incomming...";
	_stack->setCurrentIndex(2);
}
