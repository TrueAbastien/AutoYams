#include <AutoYams\opencv\graphic\ImageOpenCV.h>
using namespace cv;
using namespace std;

#include <QMessageBox>


ImageOpenCV::ImageOpenCV(QLabel* lab)
	: content(lab), scale(1)
{
}

void ImageOpenCV::setImage(cv::Mat img)
{
	img.copyTo(image);
	content->setText("");
	Update();
}

cv::Mat ImageOpenCV::getImage() const
{
	return image;
}

bool ImageOpenCV::exists() const
{
	return !image.empty();
}

void ImageOpenCV::setScale(double val)
{
	scale = val;
}

QList<int> ImageOpenCV::asDices()
{
	auto res = detector.get(image, image);
	Update();
	return res;
}

void ImageOpenCV::Update()
{
	if (image.cols*image.rows)
	{
		Mat rgb;
		QPixmap p;
		cvtColor(image, rgb, (-2 * image.channels() + 10));
		p.convertFromImage(QImage(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888));
		content->setPixmap(p.scaled(content->width() * scale, content->height() * scale, Qt::KeepAspectRatio));
	}
}
