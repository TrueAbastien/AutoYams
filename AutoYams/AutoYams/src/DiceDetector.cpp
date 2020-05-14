#include <AutoYams\opencv\DiceDetector.h>
#include <vector>
using namespace cv;

#include <AutoYams\FileDebug.h> //DEBUG

DiceDetector::DiceDetector()
{
}

QList<int> DiceDetector::get(Mat img, Mat& output)
{
	dices.clear();

	// Gray Scale
	Mat grayScaled;
	cvtColor(img, grayScaled, CV_BGR2GRAY);
	grayScaled.convertTo(grayScaled, CV_8U);

	// Remove Noise & Background
	GaussianBlur(grayScaled, grayScaled, cvSize(3, 3), 0, 0);
	//Mat canny; grayScaled.copyTo(canny);
	threshold(grayScaled, grayScaled, 200, 255, cv::THRESH_BINARY_INV);
	//threshold(grayScaled, grayScaled, 200, 255, cv::THRESH_BINARY);
	erode(grayScaled, grayScaled, Mat(), cv::Point(-1, -1), 2);

	/*/
	// Remove Noise & Background
	GaussianBlur(grayScaled, grayScaled, cvSize(3, 3), 0, 0);
	//threshold(grayScaled, grayScaled, 200, 255, cv::THRESH_BINARY_INV);
	threshold(grayScaled, grayScaled, 200, 255, cv::THRESH_BINARY);
	//erode(grayScaled, grayScaled, Mat(), cv::Point(-1, -1), 2);


	GaussianBlur(borders, borders, cvSize(3, 3), 0, 0);
	GaussianBlur(borders, borders, cvSize(3, 3), 0, 0);
	Laplacian(borders, borders, CV_8U);
	//borders.convertTo(borders, -1, 5);

	//dilate(borders, borders, Mat(), cv::Point(-1, -1), 1);
	threshold(borders, borders, 0, 128, cv::THRESH_BINARY);
	grayScaled -= borders;

	//threshold(grayScaled, grayScaled, 0, 255, cv::THRESH_BINARY_INV);
	//*/

	/*/
	std::vector<std::vector<Point>> preContours, postContours;
	std::vector<Vec4i> preHierarchy;
	findContours(grayScaled, preContours, preHierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	Mat borders(grayScaled.rows, grayScaled.cols, CV_8U, cv::Scalar(0, 0, 0));
	for (int ii = 0; ii < preHierarchy.size(); ++ii)
		if (preHierarchy[ii][2] > 0)
			postContours.push_back(preContours[ii]);
	drawContours(borders, postContours, -1, Scalar(255, 255, 255), 2);

	GaussianBlur(laplacian, laplacian, cvSize(3, 3), 0, 0);
	Laplacian(laplacian, laplacian, CV_8U);
	laplacian.convertTo(laplacian, -1, 5);
	dilate(borders, borders, Mat(), cv::Point(-1, -1), 3);
	threshold(laplacian, laplacian, 128, 255, cv::THRESH_BINARY);
	laplacian -= borders;

	grayScaled -= laplacian;
	//*/

	/*/
	std::vector<std::vector<Point>> preContours, postContours;
	std::vector<Vec4i> preHierarchy;
	findContours(grayScaled, preContours, preHierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	Mat borders(grayScaled.rows, grayScaled.cols, CV_8U, cv::Scalar(0, 0, 0));
	for (int ii = 0; ii < preHierarchy.size(); ++ii)
		postContours.push_back(preContours[ii]);
	drawContours(borders, postContours, -1, Scalar(255, 255, 255), 1);

	Canny(canny, canny, 128, 255);
	//canny -= borders;
	//*/

	// Find Contours
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(grayScaled, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	//findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	// Go Through Hierarchy
	QList<int> existingIndex;
	int count = 0;
	for (Vec4i contour : hierarchy)
		if (contour[2] < 0 && contour[3] >= 0)
		{
			if (!existingIndex.contains(contour[3]))
			{
				dices.push_back(1);
				existingIndex.push_back(contour[3]);
			}
			else dices[existingIndex.indexOf(contour[3])]++;
		}

	// Fill output
	if (output.rows > 0)
	{
		output = img;
		//drawKeypoints(invBack2, keypoints, output, Scalar(0, 0, 255), 0);
		//drawContours(output, contours, -1, Scalar(0, 255, 0), 3);

		//*/
		std::vector<std::vector<Point>> parentContours, childrenContours;

		for (int contourIndex : existingIndex)
			parentContours.push_back(contours[contourIndex]);
		drawContours(output, parentContours, -1, Scalar(0, 255, 0), 2);

		for (int ii = 0; ii < hierarchy.size(); ++ii)
			if (hierarchy[ii][2] < 0)
				childrenContours.push_back(contours[ii]);
		drawContours(output, childrenContours, -1, Scalar(0, 0, 255), 2);
		//*/
	}

	// DEBUG // -------------------------------------------------------------------------------- //
	QString data = "";
	/*/
	for (int dice : dices)
		data += QString::number(dice) + " ";
	//*/
	if (!data.isEmpty())
		FileDebug::write(data);
	// DEBUG // -------------------------------------------------------------------------------- //

	return dices;
}
