#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
#define VIDEO_PATH "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\4k.mp4"
#define VIDEO_PATH_SAVE "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\4k_BAK.mp4"
#define IMG_PATH "E:\\Dten\\other demo\\opencv\\mydemo\\opencv_test\\res\\test.png"

class QuickDemo //����һ��QuickDemo����
{
public:
    void colorSpace_Demo(Mat& imge); //����һ���࣬�����������һ��ͼƬ����ͼƬ����
    void random_drawing(); //����һ��������ֺ������ɫ�������������ķ�ʽ��ʾ������ 
    void video_demo();
    void face();    //����ʶ��
    void face2();    //����ʶ��
    int alphaBlending();  //ͼƬ����
};

