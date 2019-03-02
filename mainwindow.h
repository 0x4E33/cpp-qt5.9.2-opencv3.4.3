#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include <opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <Python.h>
#include <QTextCodec>

using namespace cv;
using namespace cv::face;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Mat norm_0_255(InputArray);
    void read_csv(const string&, vector<Mat>&, vector<int>&, char);
    //int Predict(Mat&);
    QImage  Mat2QImage(cv::Mat);
    int file_index = 41;
    int file_order = 35;
    map<int,string> Map_name;
    void DelDir(const QString&);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

private:
    void Camera();
    void Run_python();
    void Train_model();
    void Judge();
    void Add_name();
    void Retake();
};

#endif // MAINWINDOW_H
