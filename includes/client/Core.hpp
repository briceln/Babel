/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#ifndef CPP_BABEL_2018_CORE_HPP
#define CPP_BABEL_2018_CORE_HPP

#include <QtWidgets/QStackedWidget>
#include <memory>
#include "includes/client/Network/TCPNetwork.hpp"
#include "includes/client/UI/Login.hpp"
#include "includes/client/UI/Home.hpp"
#include "includes/client/UI/Call.hpp"
#include "includes/client/Settings.hpp"

using namespace std;
using namespace Babel::UI;

class Core : public QMainWindow {
Q_OBJECT
public:
	explicit Core(Settings const &settings);
	~Core() override;

public slots:
	void checkForCall(int);

private:
	QStackedWidget              *_stackedWidget;
	Login                       *_loginScreen;
	Home                        *_homeScreen;
	Call                        *_callScreen;
	std::unique_ptr<TCPNetwork> _tcpNetwork;
};

#endif //CPP_BABEL_2018_CORE_HPP
