#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include <opencv2\opencv.hpp>
#include<QDebug>
#include <iostream>
#include <opencv2\imgproc\types_c.h>
#include <opencv2\highgui\highgui_c.h>
#include <QImage>
#include <QMutex>

using namespace std;
using namespace cv;

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);


private slots:
	void ok();


private:
	Ui::QtGuiApplication1Class ui;
	QImage Mat2QImg(cv::Mat cvImg);
	VideoCapture *cap;
	QImage image;
	Mat frame;
};

