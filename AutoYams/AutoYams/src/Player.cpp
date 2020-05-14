#include <AutoYams\gameplay\Player.h>

Player::Player(QString _name)
	: name(_name)
{
	firstScore.add({ "Total1", "Total2" ,"Total3" ,"Total4" ,"Total5" ,"Total6" });
	secondScore.add({ "Brelan", "Carre", "Full", "PetiteSuite", "GrandeSuite", "Yams", "Chance" });
}

QString Player::getName() const
{
	return name;
}

int Player::getScore() const
{
	return firstScore.get(35, 63) + secondScore.get();
}

bool Player::addFirstScore(QString name, int amount)
{
	return firstScore.set(name, amount);
}

bool Player::addSecondScore(QString name, int amount)
{
	return secondScore.set(name, amount);
}

bool Player::hasPlayed(QString name)
{
	if (!firstScore.set(name, -1))
		if (!secondScore.set(name, -1))
			return true;
	return false;
}

void Player::processScoreData()
{
	score.firstScore = firstScore.get();
	score.firstTotal = firstScore.get(35, 63);
	score.bonusEligeable = score.firstTotal > score.firstScore;
	score.secondScore = secondScore.get();
	score.lastTotal = getScore();
}
