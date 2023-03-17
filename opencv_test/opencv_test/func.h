#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
#define VIDEO_PATH "E:\\Dten\\other demo\\opencv\\opencv_test\\res\\4k.mp4"
#define VIDEO_PATH_SAVE "E:\\Dten\\other demo\\opencv\\opencv_test\\res\\4k_BAK.mp4"
#define IMG_PATH "E:\\Dten\\other demo\\opencv\\opencv_test\\res\\test.png"
#define IMG_PATH2 "E:\\Dten\\other demo\\opencv\\opencv_test\\res\\test2.png"
#define IMG_PATH3 "E:\\Dten\\other demo\\opencv\\opencv_test\\res\\test3.jpg"
#define IMG_OUTPUT_PATH3 "E:\\Dten\\other demo\\opencv\\opencv_test\\res\\output.png"

class QuickDemo //创建一个QuickDemo对象
{
public:
    void addText2img();
    void dealimg();  //图像处理
    void colorSpace_Demo(Mat& imge); //定义一个类，里面包含输入一个图片，对图片操作
    void random_drawing(); //产生一个随机数字和随机颜色，并且用线条的方式显示出来。 
    void video_demo();  //播放本地视频文件
    void face();    //人脸识别，读取本地文件视频数据
    void face2();    //人脸识别，读取摄像头数据，并显示帧率
    int alphaBlending();  //图片叠加，两张图合并
    void changebg(const char* filePath);  //更换证件照背景
};

