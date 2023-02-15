#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
#define VIDEO_PATH "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\4k.mp4"
#define VIDEO_PATH_SAVE "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\4k_BAK.mp4"
#define IMG_PATH "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\test.png"

class QuickDemo //创建一个QuickDemo对象
{
public:
    void colorSpace_Demo(Mat& imge); //定义一个类，里面包含输入一个图片，对图片操作
    void random_drawing(); //产生一个随机数字和随机颜色，并且用线条的方式显示出来。 
    void video_demo();
    void face();    //人脸识别
    void face2();    //人脸识别
    int alphaBlending();  //图片叠加
};

