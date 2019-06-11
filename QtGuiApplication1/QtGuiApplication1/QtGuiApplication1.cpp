#include "QtGuiApplication1.h"

#include <opencv2/opencv.hpp>
#include<QDebug>
#include <iostream>
#include <thread>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <QImage>

using namespace std;
using namespace cv;


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	cap = new VideoCapture();
	cap->open("rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok()));
}
void QtGuiApplication1::ok() {
	while (1) {
		*cap >> frame;
		if (!frame.empty()) {
			image = Mat2QImg(frame);
			QGraphicsScene *scene = new QGraphicsScene();
			scene->addPixmap(QPixmap::fromImage(image));
			ui.graphicsView->setScene(scene);
			ui.graphicsView->resize(image.width() + 10, image.height() + 10);
			ui.graphicsView->show();
			waitKey(33);
		}
	}
}

QImage QtGuiApplication1::Mat2QImg(cv::Mat cvImg) {
	QImage qImg;
	if (cvImg.channels() == 3) {
		cvtColor(cvImg, cvImg, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1) {
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_Indexed8);
	}
	else {
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	return qImg;
}
