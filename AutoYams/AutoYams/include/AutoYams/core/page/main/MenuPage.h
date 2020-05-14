#pragma once
#include <AutoYams\core\page\Page.h>

class MenuPage : public Page
{
	Q_OBJECT

public:
	explicit MenuPage(AutoYams* ref = 0);

	void handle() override;

private slots:
	void startGame();
	void addPlayer();

signals:
	void changePage(int);
};