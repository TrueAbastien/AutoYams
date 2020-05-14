#pragma once
#include <AutoYams\gameplay\Score.h>

class Player
{
public:
	struct ScoreData
	{
		int firstScore = 0, firstTotal = 0,
			secondScore = 0, lastTotal = 0;
		bool bonusEligeable = false;
	};

private:
	QString name;
	Score firstScore, secondScore;

public:
	Player(QString name);
	QString getName() const;
	int getScore() const;

	bool addFirstScore(QString name, int amount);
	bool addSecondScore(QString name, int amount);
	bool hasPlayed(QString name);

	ScoreData score;
	void processScoreData();
};