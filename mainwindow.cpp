#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setFrameShape(QFrame::Box);
    ui->label_1->setFrameShape(QFrame::Box);
    ui->label_2->setFrameShape(QFrame::Box);
    ui->label_3->setFrameShape(QFrame::Box);
    ui->label_4->setFrameShape(QFrame::Box);
    ui->label_5->setFrameShape(QFrame::Box);
    ui->label_6->setFrameShape(QFrame::Box);
    ui->label_7->setFrameShape(QFrame::Box);
    ui->label_8->setFrameShape(QFrame::Box);
    ui->label_9->setFrameShape(QFrame::Box);
    ui->label_10->setFrameShape(QFrame::Box);
    Map_name.clear();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage  MainWindow::Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if (cvImg.channels() == 3)                          //3 channels color image
    {
        cvtColor(cvImg, cvImg, CV_BGR2RGB);
        qImg = QImage((const unsigned char*)(cvImg.data),
            cvImg.cols, cvImg.rows,
            cvImg.cols*cvImg.channels(),
            QImage::Format_RGB888);
    }
    else if (cvImg.channels() == 1)                    //grayscale image
    {
        qImg = QImage((const unsigned char*)(cvImg.data),
            cvImg.cols, cvImg.rows,
            cvImg.cols*cvImg.channels(),
            QImage::Format_Indexed8);
    }
    else
    {
        qImg = QImage((const unsigned char*)(cvImg.data),
            cvImg.cols, cvImg.rows,
            cvImg.cols*cvImg.channels(),
            QImage::Format_RGB888);
    }

    return qImg;
}

void MainWindow::Camera()
{
        ui->pushButton->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        //cout << "!!!!!!!!!!!!!!!  " << file_index << endl;
        ui->pushButton_5->setEnabled(true);
        CascadeClassifier cascada;
        cascada.load("C:/Users/admin/Desktop/Demo/cascades/haarcascades/haarcascade_frontalface_alt2.xml");
        VideoCapture cap(0);
        Mat frame, myFace;
        int pic_num = 1;
        QImage Img,Img2;
        QLabel* pp;
        while (pic_num<=10)
        {
            cap >> frame;
            vector<Rect> faces;
            Mat frame_gray;
            cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
            cascada.detectMultiScale(frame_gray, faces, 1.1, 4, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70), Size(1000, 1000));
            //cout << "face number:" << faces.size() << endl;
            //printf("face number: %u\n", faces.size());
            for (int i = 0; i < faces.size(); ++i)
            {
                rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
            }
            if (faces.size() == 1)
            {
                Mat faceROI = frame_gray(faces[0]);
                cv::resize(faceROI, myFace, Size(92, 112));
                putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);
                QString folder_name = QString::fromStdString("C:\\Users\\admin\\Desktop\\Demo\\att_faces\\orl_faces\\s" + to_string(file_index));
                string filename = "C:\\Users\\admin\\Desktop\\Demo\\att_faces\\orl_faces\\s" + to_string(file_index) + "\\" + to_string(pic_num) + ".jpg";
                //cout << "######### " << filename << endl;
                //string filename = format("%d.jpg", pic_num);
                QDir dir;
                if(!dir.exists(folder_name))
                {
                    dir.mkpath(folder_name);
                }
                imwrite(filename, myFace);
                //imshow(filename, myFace);
                Img = Mat2QImage(myFace);
                pp = findChild<QLabel*>("label_"+QString::number(pic_num));
                pp->setScaledContents(true);
                pp->resize(pp->width(),pp->height());
                pp->setPixmap(QPixmap::fromImage(Img));
                waitKey(500);
                destroyWindow(filename);
                ++pic_num;
            }
            //int c = waitKey(10);
            //if ((char)c == 27)
            //    break;
            Img2 = Mat2QImage(frame);
            ui->label->setScaledContents(true);
            ui->label->resize(ui->label->width(),ui->label->height());
            ui->label->setPixmap(QPixmap::fromImage(Img2));
            //imshow("frame", frame);
            waitKey(200);
        }
        ++file_index;
        //QImage Img = Mat2QImage(myFace);
        //ui->label->setScaledContents(true);
        //ui->label->resize(ui->label->width(),ui->label->height());
        //ui->label->setText(tr("Deal lay low more"));
        //ui->label->setStyleSheet("border:2px solid black");
        //ui->label->setPixmap(QPixmap::fromImage(Img));
        waitKey(500);
        cap.release();
        ui->label->clear();
        //destroyWindow("frame");
        return;
}

void MainWindow::on_pushButton_clicked()
{
    Camera();
    ui->pushButton_5->setText("继续添加");
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
}

void MainWindow::Run_python()
{
    ui->pushButton_2->setEnabled(false);
    ui->label_1->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_7->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    Py_Initialize();
    if(!Py_IsInitialized())
        return;
    PyObject* pModule = PyImport_ImportModule("create_csv");
    if(!pModule)
    {
        cout << "can not open Python file" << endl;
        return;
    }
    PyObject* pFunction = PyObject_GetAttrString(pModule,"create");
    if(!pFunction)
    {
        cout << "can not find the function" << endl;
    }
    PyObject_CallFunction(pFunction,NULL);
    Py_Finalize();
    return;
}

void MainWindow::on_pushButton_2_clicked()
{
    Run_python();
    ui->pushButton->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
    ui->label_11->setText("生成完毕");
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit->setText("");
}

Mat MainWindow::norm_0_255(InputArray _src)
{
    Mat src = _src.getMat();
    Mat dst;
    switch (src.channels())
    {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

void MainWindow::read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';')
{
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty())
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void MainWindow::Train_model()
{
        ui->pushButton_3->setEnabled(false);
        string fn_csv = "at.txt";
        vector<Mat> images;
        vector<int> labels;
        try
        {
            read_csv(fn_csv, images, labels); //从csv文件中批量读取训练数据
        }
        catch (cv::Exception& e)
        {
            cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
            exit(1);
        }
        if (images.size() <= 1) {
            string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
            CV_Error(CV_StsError, error_message);
        }
        for (int i = 0; i < images.size(); i++)
        {
            if (images[i].size() != Size(92, 112))
            {
                cout << i << endl;
                cout << images[i].size() << endl;
            }
        }
        for (int i = 0; i < images.size(); i++)
        {
            if (images[i].size() != Size(92, 112))
            {
                cout << i << endl;
                cout << images[i].size() << endl;
            }
        }
        Mat testSample = images[images.size() - 1];
        int testLabel = labels[labels.size() - 1];
        images.pop_back();
        labels.pop_back();
        EigenFaceRecognizer::create(10);
        Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();
        model->train(images, labels);
        model->save("C:\\Users\\admin\\Desktop\\Demo\\model\\MyFacePCAModel.xml");//保存路径可自己设置，但注意用“\\”

        Ptr<BasicFaceRecognizer> model1 = FisherFaceRecognizer::create();
        model1->train(images, labels);
        model1->save("C:\\Users\\admin\\Desktop\\Demo\\model\\MyFaceFisherModel.xml");

        Ptr<LBPHFaceRecognizer> model2 = LBPHFaceRecognizer::create();
        model2->train(images, labels);
        model2->save("C:\\Users\\admin\\Desktop\\Demo\\model\\MyFaceLBPHModel.xml");
        int predictedLabel = model->predict(testSample);//加载分类器
        int predictedLabel1 = model1->predict(testSample);
        int predictedLabel2 = model2->predict(testSample);
        string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
        string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);
        string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);
        cout << result_message << endl;
        cout << result_message1 << endl;
        cout << result_message2 << endl;
        waitKey(1000);
        return;
}

void MainWindow::on_pushButton_3_clicked()
{
    Train_model();
    ui->pushButton_4->setEnabled(true);
    ui->label_12->setText("训练完毕");
}

/*int MainWindow::Predict(Mat &src_image)
{
        Ptr<FaceRecognizer> model;
        Mat face_test;
        int predict = 0;

        if (src_image.rows >= 120)
        {
            cv::resize(src_image, face_test, Size(92, 112));

        }
        if (!face_test.empty())
        {
            predict = model->predict(face_test);
        }
        //cout << predict << endl;
        return predict;
}*/

void MainWindow::Judge()
{
        ui->pushButton_4->setEnabled(false);
        Mat face_test;
        int predict = 0;
        RNG g_rng(12345);
        Ptr<FaceRecognizer> model;
        VideoCapture cap(0);
        if (!cap.isOpened())
        {
            cout << "can not open the camera" << endl;
            return ;
        }
        Mat frame;
        Mat gray;
        QImage Img;
        CascadeClassifier cascade;
        //bool stop = false;
        cascade.load("E:\\opencv\\install\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml");//感觉用lbpcascade_frontalface效果没有它好，注意哈！要是正脸
        model = FisherFaceRecognizer::create();
        //1.加载训练好的分类器
        model->read("C:\\Users\\admin\\Desktop\\Demo\\model\\MyFaceFisherModel.xml");// opencv2用load
                                             //3.利用摄像头采集人脸并识别
        while (1)
        {
                cap >> frame;

                vector<Rect> faces(0);//建立用于存放人脸的向量容器

                cvtColor(frame, gray, CV_RGB2GRAY);//测试图像必须为灰度图

                equalizeHist(gray, gray); //变换后的图像进行直方图均值化处理
                //检测人脸
                cascade.detectMultiScale(gray, faces,
                    1.1, 4, 0
                    //|CV_HAAR_FIND_BIGGEST_OBJECT
                    | CV_HAAR_DO_ROUGH_SEARCH,
                    //| CV_HAAR_SCALE_IMAGE,
                    Size(30, 30), Size(500, 500));
                Mat* pImage_roi = new Mat[faces.size()];    //定以数组
                Mat face;
                Point text_lb;//文本写在的位置
                //框出人脸
                string str;
                //cout << "Size: " << faces.size() << endl;
                for (int i = 0; i < faces.size(); i++)
                {
                    pImage_roi[i] = gray(faces[i]); //将所有的脸部保存起来
                    text_lb = Point(faces[i].x, faces[i].y);
                    if (pImage_roi[i].empty())
                        continue;
                    if (pImage_roi[i].rows >= 120)
                    {
                        cv::resize(pImage_roi[i], face_test, Size(92, 112));
                    }
                    if (!face_test.empty())
                    {
                        predict = model->predict(face_test);
                        //cout << "predict number:" << predict << endl;
                    if(predict<35)
                        str = "Error";
                    else
                        str = Map_name[predict];
                    /*switch (predict) //对每张脸都识别
                    {
                        case 35:str = "kachun"; break;
                        default: str = "Error"; break;
                    }*/
                    Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//所取的颜色任意值
                    rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), color, 1, 8);//放入缓存
                    putText(frame, str, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));//添加文字
                    }
                }
                Img = Mat2QImage(frame);
                delete[]pImage_roi;
                //imshow("face", frame);
                ui->label->setScaledContents(true);
                ui->label->resize(ui->label->width(),ui->label->height());
                ui->label->setPixmap(QPixmap::fromImage(Img));
                waitKey(1000);
                if (waitKey(100) == 27)
                    break;
        }
            cap.release();
            ui->label->clear();
            return ;
}

void MainWindow::on_pushButton_4_clicked()
{
    Judge();
}

void MainWindow::Add_name()
{
    ui->pushButton_5->setEnabled(false);
    string str = ui->lineEdit->text().toStdString();
    cout << "str is : " << str << endl;
    cout << "and now file_order is " << file_order << endl;
    Map_name[file_order++] = str;
}

void MainWindow::on_pushButton_5_clicked()
{
    Add_name();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->label_1->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_7->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
}

void MainWindow::DelDir(const QString &path)
{
    if (path.isEmpty()){
            return ;
        }
        QDir dir(path);
        if(!dir.exists()){
            return ;
        }
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
        QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
        foreach (QFileInfo file, fileList){ //遍历文件信息
            if (file.isFile()){ // 是文件，删除
                file.dir().remove(file.fileName());
            }else{ // 递归删除
                DelDir(file.absoluteFilePath());
            }
        }
        dir.rmpath(dir.absolutePath()); // 删除文件夹
}

void MainWindow::Retake()
{
    ui->pushButton_6->setEnabled(false);
    const QString qstr = QString::fromStdString("C:\\Users\\admin\\Desktop\\Demo\\att_faces\\orl_faces\\s"+to_string(file_index-1));
    DelDir(qstr);
    --file_index;

}

void MainWindow::on_pushButton_6_clicked()
{
    ui->label_1->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_7->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    Retake();
    ui->pushButton_6->setEnabled(true);
    Camera();
}
