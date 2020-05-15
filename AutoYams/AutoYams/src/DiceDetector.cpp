#include <AutoYams\opencv\DiceDetector.h>
#include <vector>
using namespace cv;

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
	threshold(grayScaled, grayScaled, 200, 255, cv::THRESH_BINARY_INV);
	erode(grayScaled, grayScaled, Mat(), cv::Point(-1, -1), 2);

	// Find Contours
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(grayScaled, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

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
		std::vector<std::vector<Point>> parentContours, childrenContours;

		for (int contourIndex : existingIndex)
			parentContours.push_back(contours[contourIndex]);
		drawContours(output, parentContours, -1, Scalar(0, 255, 0), 2);

		for (int ii = 0; ii < hierarchy.size(); ++ii)
			if (hierarchy[ii][2] < 0)
				childrenContours.push_back(contours[ii]);
		drawContours(output, childrenContours, -1, Scalar(0, 0, 255), 2);
	}

	return dices;
}
