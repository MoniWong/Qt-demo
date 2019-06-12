#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <QtCore>

using namespace std;
using namespace cv;

class ReadProcesser : public QObject
{
	Q_OBJECT
public:
	ReadProcesser(QObject* parent = Q_NULLPTR);
	~ReadProcesser();

public slots:
	void work();
	void doRead();
	void stopRead();

private:
	VideoCapture *cap;
	bool flag;
	int rate;

signals:
	void getResult(cv::Mat&);
};
