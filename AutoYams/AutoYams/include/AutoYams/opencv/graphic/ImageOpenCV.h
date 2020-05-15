#pragma once
#include <QLabel>
#include <AutoYams\opencv\DiceDetector.h>


/**
* \class ImageOpenCV
* \brief Object setting a Label Pixmap with the current image
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Image OpenCV (cv::Mat) used on QLabel to modify QPixMap.
*/
class ImageOpenCV : public QObject
{
	Q_OBJECT

public:

	/**
	* \brief Default constructor
	* \param lab Label on which to apply current Image
	*
	* Instantiate image by saving Label.
	*/
	explicit ImageOpenCV(QLabel* lab);


	/**
	* \brief Accessor on current Image
	* \return Current Image
	*
	* Get currently saved image.
	*/
	cv::Mat getImage() const;

	/**
	* \brief Verify if an Image is saved
	* \return Result of verification
	*
	* Is True if a cv::Mat image is saved.
	*/
	bool exists() const;

	/**
	* \brief Setter of current Image Scale
	* \param val New image scale
	*
	* Change current Image scale to the new sepcified value.
	*/
	void setScale(double val);

	/**
	* \brief Run current algorithm to detect any Dice
	* \return List of all dice-value found
	*
	* Run through the currently specified algorithm to find any Dice & their value on the currently saved image.
	*/
	QList<int> asDices();

private:

	/**
	* Saved label on which to apply the image.
	*/
	QLabel* content;
	/**
	* Saved image to process and display.
	*/
	cv::Mat image;

	/**
	* Current scale/zoom of the displayed image.
	*/
	double scale;

	/**
	* Detector/algorithm to process image and find dices in.
	*/
	DiceDetector detector;

public slots:

	/**
	* \brief Modify actual image by the specified one
	* \param img Image specified
	*
	* Used in the update of current picture if necessary (ie. use of a video-device thingy...).
	*/
	void setImage(cv::Mat img);

	/**
	* \brief Update of current image display
	*
	* Apply on Label Pixmap the currently saved image, even if not modified.
	*/
	void Update();
};