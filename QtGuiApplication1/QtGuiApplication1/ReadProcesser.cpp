#include "ReadProcesser.h"
#include <fstream>

ReadProcesser::ReadProcesser(QObject* parent) :QObject(parent)
{
	cap = new VideoCapture();
	flag = true;
}

ReadProcesser::~ReadProcesser()
{
	cap->release();
	delete cap;
}

void ReadProcesser::work()
{
	cap->open("rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov");
	rate = 1000 / cap->get(cv::CAP_PROP_FPS);
	Mat frame;
	while (true)
	{
		cap->read(frame);
		if (flag) emit getResult(frame);
		cv::waitKey(rate);
	}
}

void ReadProcesser::doRead()
{
	flag = true;
}

void ReadProcesser::stopRead()
{
	flag = false;
}