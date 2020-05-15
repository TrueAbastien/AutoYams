#include <AutoYams\core\page\main\MenuPage.h>

#include <AutoYams\core\exception\AdvancedException.h>

MenuPage::MenuPage(AutoYams* ref)
	: Page(0, ref)
{
	connect(this, SIGNAL(changePage(int)), app->ui.pagination, SLOT(setCurrentIndex(int)));
	connect(app->ui.menu_startBtn, SIGNAL(pressed()), this, SLOT(startGame()));
	connect(app->ui.menu_playerAdd, SIGNAL(pressed()), this, SLOT(addPlayer()));
}

void MenuPage::startGame()
{
	if (app->ui.menu_playerList->count() > 1)
		emit changePage(ID + 1);
}

void MenuPage::handle()
{
	app->ui.menu_playerList->clear();
}

void MenuPage::addPlayer()
{
	QString player = app->ui.menu_playerName->text();
	if (player.length() >= 3)
	{
		if (app->ui.menu_playerList->findItems(player, Qt::MatchFixedString).isEmpty())
		{
			app->ui.menu_playerList->addItem(player);
			app->ui.menu_playerName->clear();
		}
	}
}
