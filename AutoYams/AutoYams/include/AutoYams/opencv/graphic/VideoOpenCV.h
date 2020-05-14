#pragma once
#include <AutoYams\opencv\graphic\ImageOpenCV.h>

#include "opencv2/videoio.hpp"

#include <QTimer>
#include <QLabel>
#include <ctime>
#include <iostream>


class VideoOpenCV : public QObject
{
	Q_OBJECT

public:
	VideoOpenCV(QLabel* lab, cv::VideoCapture* cap = nullptr, int fps = 30);
	
public slots:
	void setMaxFPS(int fps);
	void setCapture(int capIndex);
	void setBrightness(int val);
	void setContrast(int val);
	void setZoom(double val);
	void turnOff();

private:
	cv::VideoCapture* capture;
	int frameRate;

	double contrast;
	int brightness;

	cv::Mat currentImage;

	QTimer* player;
	ImageOpenCV image;
	QLabel* container;

	QList<int> latestDiceList, savedDiceList;
	int waitingTicks, currentTicks;

signals:
	void DiceChanged(QList<int>&);
};