#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define PI 3.14159

void getContours(Mat mask,Mat img,string color){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchu;
    findContours(mask,contours,hierarchu,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    //drawContours(img,contours,-1,Scalar(255,134,255),2);
    for(int i=0;i<contours.size();i++){
        vector<vector<Point>> connPoly(contours.size());
        float area = contourArea(contours[i]);
        float peri = arcLength(contours[i],true);
        vector<Rect> boundRect(contours.size());
        float rate = 4*PI*area/(peri*peri);
        //cout << area <<" "<< peri << " "<< rate <<endl;
        if(area>700 &&rate>0.3&&rate<1.3){
            approxPolyDP(contours[i],connPoly[i],0.02*peri,true);
            //drawContours(img,connPoly,i,Scalar(255,0,255),2);
            boundRect[i]=boundingRect(connPoly[i]);
            rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(255,0,255),5);
            putText(img,color,{boundRect[i].x,boundRect[i].y-20},FONT_HERSHEY_DUPLEX,1,Scalar(255,0,255),2);
        }
    }
}

int main(){
    string color1="Green",color2="Red";
    string path = "../TrafficLight.mp4";
    VideoCapture cap(path);
    Mat img,imgResize,imgHSV,mask_red,mask_green;
    while(true){
        cap.read(img);
        resize(img,imgResize,Size(),0.5,0.5);
        //转化成HSV图像用于颜色检测
        cvtColor(imgResize,imgHSV,COLOR_BGR2HSV);
        //红色mask制作红色边界矩形
        int hmin1=114,smin1=113,vmin1=0;
        int hmax1=179,smax1=255,vmax1=255;
        Scalar lower1(hmin1,smin1,vmin1);
        Scalar upper1(hmax1,smax1,vmax1);
        inRange(imgHSV,lower1,upper1,mask_red);
        //绿色mask制作绿色边界矩形
        int hmin2=74,smin2=136,vmin2=92;
        int hmax2=93,smax2=255,vmax2=201;
        Scalar lower2(hmin2,smin2,vmin2);
        Scalar upper2(hmax2,smax2,vmax2);
        inRange(imgHSV,lower2,upper2,mask_green);
        getContours(mask_green,imgResize,color1);
        getContours(mask_red,imgResize,color2);
        //imshow("Image",mask_red);
        imshow("Image",imgResize);//这里以后需要修改播放哪个视频
        waitKey(20);
    }

    return 0;
}