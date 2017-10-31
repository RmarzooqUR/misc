#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void drawGround(Mat image){
    Point p1,p2;
    p1.x = 0;
    p1.y = image.size().height;
    p2.x = image.size().width;
    p2.y = image.size().height;
    line(image,p1,p2,Scalar(0,0,0),2);
}

void drawSun(Mat image, int ht){
    Point p_center;
    p_center.x = image.size().width/2;
    p_center.y = ht;
    circle(image,p_center,25,Scalar(0,255,255),50);
}
int main()
{
    char ch = 'y';
    while (ch=='y'){
        Mat image(1368/2,720,CV_8UC3);
        cout<<"Enter Height of Sun(in pixels : 0-720):";
        int ht_sun,ht_sheet,sheet_width,sheet_hole_dia;
        sheet_width = 130;
        sheet_hole_dia = 50;
        cin>>ht_sun;
        cout<<"Enter height of the sheet (0-height of sun):";
        cin>>ht_sheet;
        ht_sheet =image.size().height - ht_sheet;
        ht_sun = image.size().height - ht_sun;

        Point sheet_left,sheet_right,sheet_hole_left,sheet_hole_right;
        sheet_left.x = image.size().width/2 - sheet_width/2;
        sheet_right.x = image.size().width/2 + sheet_width/2;
        sheet_left.y = ht_sheet;
        sheet_right.y = ht_sheet;

        sheet_hole_left.x = image.size().width/2 - sheet_hole_dia/2;
        sheet_hole_right.x = image.size().width/2 + sheet_hole_dia/2;
        sheet_hole_left.y = ht_sheet;
        sheet_hole_right.y = ht_sheet;

        int flag1 = 0;
        while(1){
            image = Scalar(252,233,200);
            if(ht_sun>ht_sheet){
                cout<<"Sheet cannot be above Sun!!!!";
                break;
            }
            drawGround(image);
            drawSun(image,ht_sun);

            Point circle_center;
            Point shadow1_left,shadow1_right,shadow2_left,shadow2_right;

            circle_center.x = image.size().width/2;
            circle_center.y = ht_sun;
            shadow1_left.y = image.size().height-1;
            shadow1_right.y = image.size().height-1;
            shadow2_left.y = image.size().height-1;
            shadow2_right.y = image.size().height-1;

            double height_sun = image.size().height-ht_sun;
            double height_sheet = image.size().height - ht_sheet;

            double x1 = (image.size().width/2)-sheet_left.x;
            double x2 = sheet_right.x - image.size().width/2;
            double s1 = sheet_hole_left.x - image.size().width/2;
            double s2 = sheet_hole_right.x - image.size().width/2;

            x1 = (height_sun/(height_sun - height_sheet))*x1;
            x2 = (height_sun/(height_sun-height_sheet))*x2;
            s1 = (height_sun/(height_sun-height_sheet))*s1;
            s2 = (height_sun/(height_sun-height_sheet))*s2;

            shadow1_left.x = image.size().width/2 - x1;
            shadow2_right.x = image.size().width/2 + x2;
            shadow1_right.x = image.size().width/2 + s1;
            shadow2_left.x = image.size().width/2 + s2;

            line(image,sheet_left,sheet_right,Scalar(225,0,0),2);
            line(image,sheet_hole_left,sheet_hole_right,Scalar(252,233,200),2);


            line(image,shadow1_left,shadow1_right,Scalar(220,220,220),5);
            line(image,shadow2_left,shadow2_right,Scalar(220,220,220),5);

            line(image,circle_center,shadow1_left,Scalar(0,255,255),1);
            line(image,circle_center,shadow1_right,Scalar(0,255,255),1);
            line(image,circle_center,shadow2_left,Scalar(0,255,255),1);
            line(image,circle_center,shadow2_right,Scalar(0,255,255),1);

            if(sheet_left.x<0){
                flag1 = 1;
            }
            else if(sheet_right.x>image.size().width){
                flag1 = 0 ;
            }


            if(!flag1){
                sheet_left.x--;
                sheet_right.x--;
                sheet_hole_left.x--;
                sheet_hole_right.x--;
            }
            else{
                sheet_left.x++;
                sheet_right.x++;
                sheet_hole_left.x++;
                sheet_hole_right.x++;
            }

            imshow("Display Window",image);
            if( waitKey(1) == 13 ){
                cvDestroyWindow("Display Window");
                break;
            }
        }
        cout<<"\nRun the program again(y/n):";
        cin>>ch;
    }
}
