#include "func.h"

using namespace std;





int main()
{
#if 1
    Mat src = imread(IMG_PATH, IMREAD_ANYCOLOR);//��ȡ�����������Ծ��������,�ڶ�������������ʾһ�ŻҶ�ͼ��
    if (src.empty())
    {
        printf("could not load image");//���ͼƬ������ ���޷���ȡ����ӡ���նˡ�
    }
    //������Ļ��ͼ���޷���ʾʱ����ô˺�����
    /*
    namedWindow("���봰��", WINDOW_FREERATIO);//������һ���´��ڣ�����1��ʾ���ƣ��ڶ�����������һ�����ɵı���
    imshow("���봰��", src);//��ʾ��ʾ���´��������봰���ϣ���һ��������ʾ�������ƣ�src��ʾ���ݶ���Mat 
    */

    QuickDemo qd;
    //qd.colorSpace_Demo(src);
    //qd.random_drawing();
    //qd.alphaBlending();
    //qd.video_demo();
    qd.face();
    //qd.face2();

    
    waitKey(0);//ִ�е���䣬����������������ʾ��ʱʱ�䡣��λms
    destroyAllWindows();//����ǰ�洴������ʾ����
#endif
    return 0;
}