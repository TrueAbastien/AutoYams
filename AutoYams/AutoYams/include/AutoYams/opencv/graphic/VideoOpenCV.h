#pragma once
#include <AutoYams\opencv\graphic\ImageOpenCV.h>

#include "opencv2/videoio.hpp"

#include <QTimer>
#include <QLabel>
#include <ctime>
#include <iostream>

/**
* \class VideoOpenCV
* \brief Object updating ImageOpenCV object
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Depending on framerate, update ImageOpenCV stored object from current Capture device output.
*/
class VideoOpenCV : public QObject
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param lab Reference of the Label used to create ImageOpenCV instance and set pixmap in
	* \param cap Video Capture device reference outputing the current webcam recorded image
	* \param fps Default framerate for timer instantiation
	*
	* Initialize object propreties, timed image processing & events connections.
	*/
	VideoOpenCV(QLabel* lab, cv::VideoCapture* cap = nullptr, int fps = 30);
	
public slots:
	/**
	* \brief Change max framerate of Image
	* \param fps New max framerate
	*
	* Change max framerate per second of the current Camera Device config.
	*/
	void setMaxFPS(int fps);
	/**
	* \brief Change capture device through device Index
	* \param capIndex Specific device Index
	*
	* Change current device if specified in Devices list.
	*/
	void setCapture(int capIndex);
	/**
	* \brief Change current image brightness
	* \param val New image brightness
	*
	* Change current brightness in both image and current configuration.
	*/
	void setBrightness(int val);
	/**
	* \brief Change current image contrast
	* \param val New image contrast
	*
	* Change current contrast in both image and current configuration.
	*/
	void setContrast(int val);
	/**
	* \brief Change current image zoom/scale
	* \param val New image zoom/scale
	*
	* Change current zoom/scale in both image and current configuration.
	*/
	void setZoom(double val);
	/**
	* \brief Disable image display
	*
	* Display a white Pixmap wherever the output image was previously displayed.
	*/
	void turnOff();

private:
	/**
	* Capture device reference (from main application).
	*/
	cv::VideoCapture* capture;
	/**
	* Current max framerate.
	*/
	int frameRate;

	/**
	* Current image contrast.
	*/
	double contrast;
	/**
	* Current image brightness.
	*/
	int brightness;

	/**
	* Current OpenCV image model (cv::Mat).
	*/
	cv::Mat currentImage;

	/**
	* Video Player object: update Timer called 'framerate' times per second at max.
	*/
	QTimer* player;
	/**
	* Image OpenCV object to display the capture output in.
	*/
	ImageOpenCV image;
	/**
	* Reference of the container for autoscaling purposes.
	*/
	QLabel* container;

	/**
	* List of all dices founds by algorithm by frame.
	*/
	QList<int> latestDiceList;
	/**
	* List of all dices saved if the 'latestDiceList' remains unchanged for at least 1 second.
	*/
	QList<int> savedDiceList;
	/**
	* Amount of ticks requiered for the 'savedDiceList' to be updated.
	* Should be the same as max framerate.
	*/
	int waitingTicks;
	/**
	* Current amount of ticks passed with 'latestDiceList' remaining unchanged.
	*/
	int currentTicks;

signals:
	/**
	* \brief Signal sent when new dices have been detected long enough
	* \param dices Value list of all detected dices
	*
	* Whenever the dices have been detected and unchanged for more than 1 second,
	* this signal will trigger through the EventThrowDice (Event Redirector).
	*/
	void DiceChanged(QList<int>& dices);
};