// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void countarea(Mat &image, int label) {
	double area = 0;
	double sumj = 0;
	double sumi = 0;
	double urr = 0;
	double ucc = 0;
	double urc = 0;
	double centroidr = 0;
	double centroidc = 0;
	for (int j = 0; j < image.rows - 1; j++)
	{
		for (int i = 0; i < image.cols - 1; i++)
		{
			if (image.ptr(j)[i] == label)
			{
				area = area + 1;
				sumj = sumj + j;
				sumi = sumi + i;
			}
		}
	}
		if (area >= 100)
		{
			 centroidr = sumj / area;
			 centroidc = sumi / area;
			printf("No.%d object's area is %.2f , the centroid is located at No. %f row, No. %f columns\n", label, area, centroidr, centroidc);
			for (int j = 0; j < image.rows - 1; j++)
			{
				for (int i = 0; i < image.cols - 1; i++)
				{
					if (image.ptr(j)[i] == label)
					{
						urr = urr + (j - centroidr)*(j - centroidr);
						ucc = ucc + (i - centroidc)*(i - centroidc);
						urc = urc + (j - centroidr)*(i - centroidc);
					}
				}
			}
			printf("No.%d object's second moment urr=%.2f , urc= %.2f ,ucc= %.2f ,Axis of least inertia = %.2f \n", label, urr / area, urc / area, ucc / area, 2 * urc / (urr - ucc));
		}
		else
		{
			for (int j = 0; j < image.rows - 1; j++)
			{
				for (int i = 0; i < image.cols - 1; i++)
				{
					if (image.ptr(j)[i] == label)
					{
						image.ptr(j)[i] = 0;
					}
				}
			}
		}
	}
//function match external corner
int external_match(int j,int i,Mat &image) {
	if (image.ptr<uchar>(j)[i] == 0 && image.ptr<uchar>(j + 1)[i] == 0 && image.ptr<uchar>(j)[i + 1] == 0 && image.ptr<uchar>(j + 1)[i + 1] != 0) { return 1; }
	else if (image.ptr<uchar>(j)[i] == 0 && image.ptr<uchar>(j + 1)[i] == 0 && image.ptr<uchar>(j)[i + 1] != 0 && image.ptr<uchar>(j + 1)[i + 1] == 0) { return 1; }
	else if (image.ptr<uchar>(j)[i] == 0 && image.ptr<uchar>(j + 1)[i] != 0 && image.ptr<uchar>(j)[i + 1] == 0 && image.ptr<uchar>(j + 1)[i + 1] == 0) { return 1; }
	else if (image.ptr<uchar>(j)[i] != 0 && image.ptr<uchar>(j + 1)[i] == 0 && image.ptr<uchar>(j)[i + 1] == 0 && image.ptr<uchar>(j + 1)[i + 1] == 0) { return 1; }
	else { return 0; }
}
//function match internal corner
int internal_match(int j, int i, Mat &image) {
	if (image.ptr<uchar>(j)[i] != 0 && image.ptr<uchar>(j + 1)[i] != 0 && image.ptr<uchar>(j)[i + 1] != 0 && image.ptr<uchar>(j + 1)[i + 1] == 0) { return 1; }
	else if (image.ptr<uchar>(j)[i] != 0 && image.ptr<uchar>(j + 1)[i] != 0 && image.ptr<uchar>(j)[i + 1] == 0 && image.ptr<uchar>(j + 1)[i + 1] != 0) { return 1; }
	else if (image.ptr<uchar>(j)[i] != 0 && image.ptr<uchar>(j + 1)[i] == 0 && image.ptr<uchar>(j)[i + 1] != 0 && image.ptr<uchar>(j + 1)[i + 1] != 0) { return 1; }
	else if (image.ptr<uchar>(j)[i] == 0 && image.ptr<uchar>(j + 1)[i] != 0 && image.ptr<uchar>(j)[i + 1] != 0 && image.ptr<uchar>(j + 1)[i + 1] != 0) { return 1; }
	else { return 0; }
}
//function count object
int count_objects (Mat &image) {
	int E = 0;
	int I = 0;

	for (int j = 0; j < image.rows - 2; j++) {
		for (int i = 0; i < image.cols - 2; i++){
			if (external_match(j,i,image)==1) {
				E = E + 1;
			}
			if (internal_match(j,i,image)==1) {
				I = I + 1;
			}
		}
	}
	return ((I - E) / 4);
}
//find the pixel in same object
void search(Mat &image, int label, int jl, int ip)
{
	image.ptr(jl)[ip] = label;
	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			if (jl + j > 0 && jl + j < image.rows - 1 && ip + i>0 && ip + i < image.cols - 1) {
				if (image.ptr(jl + j)[ip + i] == 0) {
					search(image, label, jl + j, ip + i);
				}
			}
		}
	}
}
//caculate how many labels
void find_components(Mat &image, int &label) {
	for (int jl = 0; jl < image.rows - 1; jl++) {
		for (int ip = 0; ip < image.cols - 1; ip++) {
			if (image.ptr(jl)[ip] == 0) {//0 represent black
				label = label + 1;
				search(image, label, jl, ip);
			}
		}
	}
}
//find the connected components
void recursive_connected_components(Mat &imageb, Mat &imagelb) {
	imagelb = imageb;
	int label = 0;
	int i;
	find_components(imagelb, label);
	for (i = 1; i <= label; i++)
	{
		countarea(imagelb, i);// output some feature of object and set the value to judge whether the object is noise

	}
	cv::imshow("imagecomponent",imagelb);
	std::cout <<"recursive connected component's result:labels are"<< label<<std::endl;
}
void ShowHelpText()
{
	//output some informations 
	printf("\n----------------------------------------------------------------------------\n");
	printf("Welcome to use this program\n");
	printf("This is a program is to detect the object on image and give the feature of each objects\n");
	printf("You need to input the location of the image location \n");
	printf("\t\t \n");
	printf("Opencv version is:" CV_VERSION);
	printf("\n\t\t\t\t made by: Yukuan Hao, Liming Yang, and Liang Gu");
	printf("\n----------------------------------------------------------------------------\n");
}
int main()
{
	ShowHelpText();
	//load an image
	cout<< "input an image"<<std::endl;
    string a;
	cin >> a;
	Mat img = imread(a,0);
	std::cout << img.cols <<img.rows<< std::endl;
	Mat result;
	cv::imshow("MM Viewer", img);
	threshold(img, result, 170, 255, cv::THRESH_BINARY);
	namedWindow("binary image");
	imshow("binary image", result);
	cv::Mat eroded;
	cv::erode(result, eroded, cv::Mat());
	cv::imshow(" Eroded Image ", eroded);
	cv::Mat dilated; 
	cv :: dilate(eroded, dilated, cv::Mat());
	cv::imshow(" Dilated Image ", dilated);
	cv::Mat contours;
	Canny(result,contours,30,170);
	cv::imshow("edge", contours);
	std::cout << "count object function result:objects are"<<count_objects(result)<< std::endl;	
	cv::Mat test;
	recursive_connected_components(result,test);
	waitKey(0);

}