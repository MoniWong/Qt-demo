#include "QtGuiApplication1.h"

using namespace std;
using namespace cv;


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qRegisterMetaType<cv::Mat>("cv::Mat");
	qRegisterMetaType<cv::Mat>("cv::Mat&");
	qRegisterMetaType<cv::VideoCapture>("cv::VideoCapture&");

	readWorkThread = new QThread;
	readProcesser = new ReadProcesser();
	connect(ui.pushButton, SIGNAL(clicked()), readProcesser, SLOT(doRead()));
	connect(ui.pushButton_2, SIGNAL(clicked()), readProcesser, SLOT(stopRead()));
	connect(ui.pushButton_3, SIGNAL(clicked()), readProcesser, SLOT(work()));
	connect(readProcesser, SIGNAL(getResult(cv::Mat&)), this, SLOT(showImg(cv::Mat&)));
	readProcesser->moveToThread(readWorkThread);
	readWorkThread->start();
}
void QtGuiApplication1::showImg(cv::Mat& frame) {

	if (!frame.empty()) {
		image = Mat2QImg(frame);
		QGraphicsScene *scene = new QGraphicsScene();
		scene->addPixmap(QPixmap::fromImage(image));
		ui.graphicsView->setScene(scene);
		ui.graphicsView->resize(image.width() + 10, image.height() + 10);
		ui.graphicsView->show();
	}
}

QImage QtGuiApplication1::Mat2QImg(const cv::Mat& cvImg) {
	if (cvImg.channels() == 3) {
		cvtColor(cvImg, cvImg, CV_BGR2RGB);
		return QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1) {
		return QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_Indexed8);
	}
	return QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
}
