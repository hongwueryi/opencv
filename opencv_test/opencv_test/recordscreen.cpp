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
    lpbitmap中的数据是从左下角到右上角排列，
    而视频帧图像的数据是从左上角到右下角排列，
    所以要将数据按行上下翻转，即lpbitmap第一行对应视频图像的最后一行
    另外BMP图像数据每行的字节数必须是4字节的整数倍，
    而写入视频的Mat数据没有这个要求，
    即每行数据大小是图像实际宽度乘以每个颜色占用的字节数
    ，所以实际每行拷贝的数据是width * 3节字
    */
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (BitBlt(hdcMemDC, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY))
        {
            GetDIBits(hdcMemDC, hbmScreen, 0, height, lpbitmap, &bi, DIB_RGB_COLORS);

            ////位图文件头结构     
            //DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
            //BITMAPFILEHEADER     bmfHdr;
            //char bmppath[128] = { 0 };
            //sprintf_s(bmppath, "E:\\CaptureScreen-%d-%d-%d.bmp", h, m, i++);
            //HANDLE fh = CreateFileA(bmppath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            //    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

            //if (fh == INVALID_HANDLE_VALUE)         return     FALSE;

            ////     设置位图文件头             
            //bmfHdr.bfType = 0x4D42;     //     "BM"             
            //dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
            //bmfHdr.bfSize = dwDIBSize;
            //bmfHdr.bfReserved1 = 0;
            //bmfHdr.bfReserved2 = 0;
            //bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
            ////     写入位图文件头             
            //WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
            ////     写入位图文件其余内容             
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