#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QObject>

/**
* \class DiceDetector
* \brief Dice detection algorithm with OpenCV
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Apply dice detection algorithm to the current video captured image in application.
*/
class DiceDetector : public QObject
{
	Q_OBJECT

private:
	/**
	* List of all detected dice data.
	*/
	QList<int> dices;

public:
	/**
	* \brief Default constructor
	*
	* Initialise dice list.
	*/
	DiceDetector();
	/**
	* \brief Run through a specific algorithm to detect dices in a specific image
	* \param img Specified image to run algorithm in
	* \param output Output image, can be specified to display found dices/contours
	* \return List of stored and modified dices data found in the specified image
	*
	* The algorithm does light adaptation of the current image background to limit noise with Gaussian Blur
	* and Thresholding then, after a few erosion, run the findContours function outputing a Hierarchy Containing Tree
	* allowing us to take children contours as dices dots and parents as the dices themselves.
	* In output image, the parent contours are green while the children are red.
	*/
	QList<int> get(cv::Mat img, cv::Mat& output = cv::Mat());
};