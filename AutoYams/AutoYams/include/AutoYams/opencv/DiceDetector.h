#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QObject>

class DiceDetector : public QObject
{
	Q_OBJECT

private:
	QList<int> dices;
	//

public:
	DiceDetector();
	QList<int> get(cv::Mat img, cv::Mat& output = cv::Mat());
};