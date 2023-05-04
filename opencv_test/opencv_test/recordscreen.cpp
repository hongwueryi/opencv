#include <Windows.h>
#include "func.h"

#include<iostream>
#include<opencv2\opencv.hpp>
#define MAX_FRAMES 200
#define MAX_FPS 25.0
int QuickDemo::RecordScreen()
{
    cv::VideoWriter videoWriter;
    int codec = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    /*int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);*/
    DEVMODE mode;
    mode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, 0, &mode);
    int width = mode.dmPelsWidth;
    int height = mode.dmPelsHeight;
    time_t seconds = time(0);
    int s = seconds % 60;
    int m = (seconds % 3600) / 60;
    int h = (seconds % (3600 * 24)) / 3600 + 8;
    char timeBuf[128] = { 0 };
    char bmppath[128] = { 0 };
    sprintf_s(timeBuf, "CaptureScreen-%d-%d-%d.mp4", h, m, s);
    sprintf_s(bmppath, "E:\\CaptureScreen-%d-%d-%d.bmp", h, m, s);
    cv::String filePath = timeBuf;
    videoWriter.open(filePath, codec, MAX_FPS, cv::Size(width, height), true);
    if (!videoWriter.isOpened())
    {
        return -1;
    }

    HDC hdcScreen = GetDC(NULL);
    HDC hdcMemDC = CreateCompatibleDC(hdcScreen);
    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, width, height);

    BITMAPINFO bi;
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = width;
    bi.bmiHeader.biHeight = height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 24;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biSizeImage = 0;
    bi.bmiHeader.biXPelsPerMeter = 0;
    bi.bmiHeader.biYPelsPerMeter = 0;
    bi.bmiHeader.biClrUsed = 0;
    bi.bmiHeader.biClrImportant = 0;
    SelectObject(hdcMemDC, hbmScreen);

    int lineBytes = ((width * bi.bmiHeader.biBitCount + 31) / 32) * 4;
    int bmpSize = lineBytes * height;
    char* lpbitmap = new char[bmpSize];
    cv::Mat bmpMat(height, width, CV_8UC3);
    /*
    lpbitmap�е������Ǵ����½ǵ����Ͻ����У�
    ����Ƶ֡ͼ��������Ǵ����Ͻǵ����½����У�
    ����Ҫ�����ݰ������·�ת����lpbitmap��һ�ж�Ӧ��Ƶͼ������һ��
    ����BMPͼ������ÿ�е��ֽ���������4�ֽڵ���������
    ��д����Ƶ��Mat����û�����Ҫ��
    ��ÿ�����ݴ�С��ͼ��ʵ�ʿ�ȳ���ÿ����ɫռ�õ��ֽ���
    ������ʵ��ÿ�п�����������width * 3����
    */
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (BitBlt(hdcMemDC, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY))
        {
            GetDIBits(hdcMemDC, hbmScreen, 0, height, lpbitmap, &bi, DIB_RGB_COLORS);

            ////λͼ�ļ�ͷ�ṹ     
            //DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
            //BITMAPFILEHEADER     bmfHdr;
            //char bmppath[128] = { 0 };
            //sprintf_s(bmppath, "E:\\CaptureScreen-%d-%d-%d.bmp", h, m, i++);
            //HANDLE fh = CreateFileA(bmppath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            //    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

            //if (fh == INVALID_HANDLE_VALUE)         return     FALSE;

            ////     ����λͼ�ļ�ͷ             
            //bmfHdr.bfType = 0x4D42;     //     "BM"             
            //dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
            //bmfHdr.bfSize = dwDIBSize;
            //bmfHdr.bfReserved1 = 0;
            //bmfHdr.bfReserved2 = 0;
            //bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
            ////     д��λͼ�ļ�ͷ             
            //WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
            ////     д��λͼ�ļ���������             
            //WriteFile(fh, (LPSTR)&bi, dwDIBSize, &dwWritten, NULL);
            //CloseHandle(fh);
            
            for (int i = 0; i < height; i++)
            {
                int srcIndex = (height - i - 1) * lineBytes;
                int destIndex = i * width * 3;
                memcpy(&bmpMat.data[destIndex], &lpbitmap[srcIndex], width * 3);
            }
            videoWriter.write(bmpMat);//videoWriter << bmpMat;
            
            
        }
    }
    delete[] lpbitmap;
    if (videoWriter.isOpened())
    {
        videoWriter.release();
    }
    return 0;
}