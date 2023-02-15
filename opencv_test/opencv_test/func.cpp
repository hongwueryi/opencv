#include "func.h"

void QuickDemo::colorSpace_Demo(Mat& image)
{
    Mat gray, hsv;//����2���������ͼ��gray��hsv, HSV ɫ��ģ�ͣ�Hue ɫ��, Saturation ���Ͷ�, Value���ȣ�
    cvtColor(image, hsv, COLOR_BGR2HSV);//ͼ��ת�����������԰�imageת��hsv��������������ת�ɵ�����
    cvtColor(image, gray, COLOR_BGR2GRAY);//ͼ��ת�����������԰�imageת��hsv��������������ת�ɵ�����
    imshow("HSV", hsv);
    imshow("�Ҷ�", gray);
    //imwrite("D:/hsv.jpg", hsv);//����ͼƬ��ǰ���Ǳ���ͼ�ĵ�ַ�������Ǳ���ͼ������
    //imwrite("D:/gray.jpg", gray);
}

void QuickDemo::random_drawing()
{
    Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
    int w = canvas.cols;
    int h = canvas.rows;
    RNG rng(100);
    while (true)
    {
        int c = waitKey(10);
        if (c == 27)
        {
            break;
        }
        int x1 = rng.uniform(0, canvas.cols);
        int y1 = rng.uniform(0, h);
        int x2 = rng.uniform(0, canvas.cols);
        int y2 = rng.uniform(0, h);
        int b = rng.uniform(0, 255);
        int g = rng.uniform(0, 255);
        int r = rng.uniform(0, 255);
        canvas = Scalar(0, 0, 0);
        line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 8, LINE_AA, 0);//line_AA��ʾȥ����� 
        imshow("���������ʾ", canvas);
    }
}

void QuickDemo::video_demo()
{
    VideoCapture capture(VIDEO_PATH);  //��ȡ��Ƶ�ĵ�ַ
    Mat frame;//����һ����ֵ���� frame
    int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//��ȡ��Ƶ�Ŀ��
    int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//��ȡ��Ƶ�ĸ߶�
    int count = capture.get(CAP_PROP_FRAME_COUNT);//��Ƶ�ܵ�֡��
    //fps�Ǻ���������Ƶ������
    double fps = capture.get(CAP_PROP_FPS);
    std::cout << "frame width" << frame_width << std::endl;
    std::cout << "frame height" << frame_height << std::endl;
    std::cout << "frame FPS" << fps << std::endl;
    std::cout << "frame count" << count << std::endl;
    //VideoWriter writer(VIDEO_PATH_SAVE, capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
    //����1 �����ַ������2 ��ȡͼƬ�ĸ�ʽ ����3 ͼƬ��֡�� ����4 ��Ƶ��� ����5 ��
    while (true)
    {
        capture.read(frame); //��ȡ��Ƶ
        //flip(frame, frame, 1);//ͼ�������
        if (frame.empty())//�����ƵΪ�յĻ� ��������
        {
            break;
        }
        imshow("frame", frame);//��ʾ��Ƶ
        //colorSpace_Demo(frame);//����Ƶ����֮ǰ��demo
        int c = waitKey(1);//ͣ��100ms ����Ƶ������1
        if (c == 27) { //esc �˳�Ӧ�ó���
            break;
        }
    }
    capture.release();//�ͷ��������Դ
    //writer.release();//�ͷŴ�ŵ���Դ
}

void QuickDemo::face()
{
    dnn::Net net = dnn::readNetFromTensorflow(
        "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\tensorflow_uint8.pb",
        "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\tensorflow.pbtxt");
    VideoCapture capture("E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\test.mp4");
    Mat frame;
    while (true) {
        capture.read(frame);
        if (frame.empty()) {
            break;
        }
        Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
        net.setInput(blob);// NCHW
        Mat probs = net.forward(); // 
        Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
        // �������
        for (int i = 0; i < detectionMat.rows; i++) {
            float confidence = detectionMat.at<float>(i, 2);
            if (confidence > 0.5) {
                int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
                Rect box(x1, y1, x2 - x1, y2 - y1);
                rectangle(frame, box, Scalar(255, 0, 0), 2, 8, 0);  //(�����̣���)
            }
        }
        imshow("���������ʾ", frame);
        int c = waitKey(1);
        if (c == 27) { // �˳�
            break;
        }
    }
}

void QuickDemo::face2()
{
#if 1
    dnn::Net net = dnn::readNetFromTensorflow(
        "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\tensorflow_uint8.pb",
        "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\tensorflow.pbtxt");
#else
    //������
    dnn::Net net = dnn::readNetFromCaffe(
        "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\DenseNet_121.prototxt",
        "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\DenseNet_121.caffemodel"
        );
    net.setPreferableBackend(dnn::DNN_BACKEND_DEFAULT);
    net.setPreferableTarget(dnn::DNN_TARGET_CPU);
#endif
    VideoCapture capture;
    //capture.open(0);
    capture.open(0, CAP_DSHOW);
    if (!capture.isOpened())
    {
        printf("can't open the camera\n");
        return;
    }
    Mat frame;
    while (capture.read(frame))
    {
        int start = getTickCount();
        flip(frame, frame, 1);
        Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
        net.setInput(blob);// NCHW
        Mat probs = net.forward(); // 
        Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
        float confidence_thresh = 0.5;
        // �������
        for (int i = 0; i < detectionMat.rows; i++) {
            float confidence = detectionMat.at<float>(i, 2);
            if (confidence > confidence_thresh) {
                //��һ��������ͼ��ı�ţ�
                //�ڶ��еĸü��Ŀ��ķ���ID��
                //��������Ԥ���������Ŷȣ�
                //�����е������зֱ���Ŀ����ο�����Ͻ�x��y��������½�x��y���꣬ע�����������ֵ����ͼ���߳ɱ����ı�ֵ������ʹ�õ�ʱ����Ҫ����ͼ��Ŀ�ߡ�
                int classID = detectionMat.at<float>(i, 1);
                //int imageid = detectionMat.at<float>(i, 0);
                int top_left_x = detectionMat.at<float>(i, 3) * frame.cols;
                int top_left_y = detectionMat.at<float>(i, 4) * frame.rows;
                int button_right_x = detectionMat.at<float>(i, 5) * frame.cols;
                int button_right_y = detectionMat.at<float>(i, 6) * frame.rows;
                int width = button_right_x - top_left_x;
                int height = button_right_y - top_left_y;
                Rect box(top_left_x, top_left_y, width, height);
                rectangle(frame, box, Scalar(255, 0, 0), 1, 8, 0);
                //cout << classID << "," << notKnown << "," << confidence << endl;
            }
        }
        int end = getTickCount();
        double run_time = (double(end) - double(start)) / getTickFrequency();
        float FPS = 1 / run_time;
        putText(frame, format("FPS: %0.2f", FPS), Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, 8);
        imshow("face_recognizition", frame);
        int c = waitKey(1);
        if (c == 27) {
            break;
        }
    }
}

//
//  alphaBlend.cpp
//  
//  ��������
// 
//  Created by Sunita Nayak on 3/14/17.
//
//

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Alpha blending using multiply and add functions
Mat& blend(Mat& alpha, Mat& foreground, Mat& background, Mat& outImage)
{
    Mat fore, back;
    multiply(alpha, foreground, fore);
    multiply(Scalar::all(1.0) - alpha, background, back);
    add(fore, back, outImage);

    return outImage;
}

// Alpha Blending using direct pointer access
Mat& alphaBlendDirectAccess(Mat& alpha, Mat& foreground, Mat& background, Mat& outImage)
{

    int numberOfPixels = foreground.rows * foreground.cols * foreground.channels();

    float* fptr = reinterpret_cast<float*>(foreground.data);
    float* bptr = reinterpret_cast<float*>(background.data);
    float* aptr = reinterpret_cast<float*>(alpha.data);
    float* outImagePtr = reinterpret_cast<float*>(outImage.data);

    int i, j;
    for (j = 0; j < numberOfPixels; ++j, outImagePtr++, fptr++, aptr++, bptr++)
    {
        *outImagePtr = (*fptr) * (*aptr) + (*bptr) * (1 - *aptr);
    }

    return outImage;
}

int QuickDemo::alphaBlending()
{
    // Read in the png foreground asset file that contains both rgb and alpha information
    Mat foreGroundImage = imread("E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\foreGroundAsset.png", -1);
    Mat bgra[4];
    split(foreGroundImage, bgra);//split png foreground

    // Save the foregroung RGB content into a single Mat
    vector<Mat> foregroundChannels;
    foregroundChannels.push_back(bgra[0]);
    foregroundChannels.push_back(bgra[1]);
    foregroundChannels.push_back(bgra[2]);
    Mat foreground = Mat::zeros(foreGroundImage.size(), CV_8UC3);
    merge(foregroundChannels, foreground);

    // Save the alpha information into a single Mat
    vector<Mat> alphaChannels;
    alphaChannels.push_back(bgra[3]);
    alphaChannels.push_back(bgra[3]);
    alphaChannels.push_back(bgra[3]);
    Mat alpha = Mat::zeros(foreGroundImage.size(), CV_8UC3);
    merge(alphaChannels, alpha);

    // Read background image
    //Mat background = imread("E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\backGround.jpg");
    Mat background = imread("E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\bg.jpg");

    // Convert Mat to float data type
    foreground.convertTo(foreground, CV_32FC3);
    background.convertTo(background, CV_32FC3);
    alpha.convertTo(alpha, CV_32FC3, 1.0 / 255); // keeps the alpha values betwen 0 and 1

    // Number of iterations to average the performane over
    int numOfIterations = 1; //1000;

    // Alpha blending using functions multiply and add
    Mat outImage = Mat::zeros(foreground.size(), foreground.type());
    double t = (double)getTickCount();
    for (int i = 0; i < numOfIterations; i++) {
        outImage = blend(alpha, foreground, background, outImage);
    }
    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "Time for alpha blending using multiply & add function : " << t * 1000 / numOfIterations << " milliseconds" << endl;

    // Alpha blending using direct Mat access with for loop
    outImage = Mat::zeros(foreground.size(), foreground.type());
    t = (double)getTickCount();
    for (int i = 0; i < numOfIterations; i++) {
        outImage = alphaBlendDirectAccess(alpha, foreground, background, outImage);
    }
    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "Time for alpha blending using alphaBlendDirectAccess : " << t * 1000 / numOfIterations << " milliseconds" << endl;

    imshow("alpha blended image", outImage / 255);
    waitKey(0);

    return 0;
}