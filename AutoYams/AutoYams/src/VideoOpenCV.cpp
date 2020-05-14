#include <AutoYams\opencv\graphic\VideoOpenCV.h>
using namespace cv;

VideoOpenCV::VideoOpenCV(QLabel* lab, cv::VideoCapture* cap, int fps)
	: image(lab), capture(cap), brightness(0), contrast(1), container(lab)
{
	player = new QTimer();
	connect(player, &QTimer::timeout, [this]() {
		if (capture != nullptr)
		{
			if (capture->read(currentImage))
			{
				currentImage.convertTo(currentImage, -1, contrast, brightness);
				image.setImage(currentImage);

				auto dices = image.asDices();
				if (dices.size() == 5)
				{
					if (dices != savedDiceList)
					{
						if (dices == latestDiceList)
						{
							if (currentTicks > waitingTicks)
							{
								savedDiceList = dices;
								currentTicks = 0;
								emit DiceChanged(savedDiceList);
							}
							else currentTicks++;
						}
						else currentTicks = 0;
					}
				}
				latestDiceList = dices;
			}
		}
	});
	this->setMaxFPS(fps);
}

void VideoOpenCV::setMaxFPS(int fps)
{
	frameRate = (int)(1000.0 / fps);
	waitingTicks = fps;
	player->start(frameRate);
}

void VideoOpenCV::setCapture(int capIndex)
{
	if (capture != nullptr)
		capture->open(capIndex);
}

void VideoOpenCV::setBrightness(int val)
{
	brightness = val;
}

void VideoOpenCV::setContrast(int val)
{
	contrast = exp(((double)val / 10.0) - 1);
}

void VideoOpenCV::setZoom(double val)
{
	image.setScale(val);
}

void VideoOpenCV::turnOff()
{
	container->setPixmap(QPixmap());
	//container->setText(container->text());
}
