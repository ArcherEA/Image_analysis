#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
//--------------------state the global variables------------------------
const int MaxbinarythresholdValue = 255;//set the maximum value for threashold(set the range of the binary image threashold) 
int binarythreshold;//the binary image threashold slider
int g_nThresh = 10;//canny function min threashold
int g_nThresh1 = 200;//canny function max threashold
int g_nThresh_max = 10000;//the max value for two threashold of canny function
int omin = 20;//set the minimum area of object
int omax = 1000;//set the maximum area of object
int OMIN = 3000;//set the max value of omin
int OMAX = 10000;//set the max value of omax
int num = -1;//set the default number of object number, use -1 to show all the object 
int originalsize;//store the number of object,use to detect the changing of the number of object
//int countexe = 0;//use to count the function execute how many times 
int maxnum;//the max number of object
string input;//store the input image location
RNG g_rng(12345);//get a random value
vector<vector<Point>> g_vContours;//use to store the object contours
vector<Vec4i> g_vHierarchy;
Mat g_cannyMat_output;//get the result of canny function
Mat inputimage;//store an image from computer,use to store the input image 
Mat result;// store the binary image from the function feature
Mat binaryimage;//store the binary image from the function binary_erson_dilation
Mat eroded;//store the eroded image
Mat dilated;//store the dilated image
Mat contours_output;//store contours used to output
Mat drawingrectcir_output;//store some features of object like bounding rectangle, center point....,used to output
Mat drawingContours_output;//store contours
Mat colorful_output;
Mat result_output;//store the binary image used to output
//------------state the function
void features(int, void*);// statement
//--------functions
/*void binary_erson_dilation(int, void*)//function to make binary image, erode image,and dilate image
{
	//set a variable of threshold to create a binary image
	threshold(inputimage,binaryimage, binarythreshold,255, cv::THRESH_BINARY);//get the binary
	cv::erode(binaryimage, eroded, cv::Mat());//erode the binary image
	namedWindow("Eroded Image(control by binary)", WINDOW_NORMAL);//create a windows
	cv::resizeWindow("Eroded Image(control by binary)", 500, 500);//resize this windows
	cv::imshow("Eroded Image(control by binary)", eroded);//show the image
	cv::dilate(eroded, dilated, cv::Mat());//dilate the binary image
	namedWindow("Dilated Image(control by binary)", WINDOW_NORMAL);//create a windows
	cv::resizeWindow("Dilated Image(control by binary)", 500, 500);//resize this windows
	cv::imshow("Dilated Image(control by binary)", dilated);//show the image
	cv::resizeWindow("binary image", 500, 500);//resize this windows
	imshow("binary image", binaryimage);//show the image
}*/
void ShowHelpText()
{
	//output some informations 
	printf("\n----------------------------------------------------------------------------\n");
	printf("Welcome to use this program\n");
	printf("This is a program is to detect the object on image and give the feature of each objects\n");
	printf("first you need to input the location of the image location \n");
	printf("second you need set a threshold to turn your image into binary image\n");
	printf("This program set the input image as gray scale image \n");
	printf("Then you should set the minimum and maximum objects' area to avoid the noise \n");
	printf("You can see the result in different windows,and you can change the threshold to get a different result\n");
	printf("\t\t \n");
	printf("Opencv version is:" CV_VERSION);
	printf("\n\t\t\t\t made by: Yukuan Hao, Liming Yang, and Liang Gu");
	printf("\n----------------------------------------------------------------------------\n");
}
void ShowHelpText1() 
{
	string answer;// use to store user's input 
	//output some informations 
	printf("\nDo you want to use the default setting?(Y/N)\n");
	cin >> answer;//get a value from user
	// use to detect user's choice, and give the result
	if (answer == "Y"||answer=="y" || answer == "YES" || answer == "yes")
	{
		binarythreshold = 170;//give a value to binarythreashold
		omin = 20;//give a value to omin
		omax = 10000;//give a value to omax
	}
	else if (answer == "N" || answer == "n" || answer == "NO" || answer == "no")
	{
		cout << "set  the threshold" << endl;
	    cin >> binarythreshold;
		printf("set the range of the area of objects\n");
		printf("minimum object area(range:0-3000):\n");
		cin >> omin;
		printf("maximum object area(range:0-10000):\n");
		cin >> omax;
	}
	else 
	{ 
		printf("please input Y/N");
		ShowHelpText1();
	}
}
//use to check whether the image is loaded
void checkimage() 
{
	//if user do not input the correct location give user chances to input the location again
	if (!inputimage.data) 
	{
		input.clear();
		printf("Can not find the image,please input the correct location of the image\n");
		cin >> input;
		inputimage = imread(input, 0);
		checkimage();
	}
}
//main( )function
int main()
{
	//show the information about this program
	ShowHelpText();//go showhelptext function
	printf("Please add the location of the image\n");
	cin >> input;//wait user to input the location of image
	ShowHelpText1();//go showhelptext1 function
	inputimage = imread(input, 0);//load image
	checkimage(); //go scheckimage function
	//create a windows used to output the binary image
	/*namedWindow("binary image", WINDOW_NORMAL);//create this windows
	//create a trackbar on the "binary image" windows
	createTrackbar("threshold", "binary image", &binarythreshold, MaxbinarythresholdValue, binary_erson_dilation);//create a slider to contorl the binary image threshold
	//the result will be show in this function
	binary_erson_dilation(binarythreshold, 0);//go to binary_erson_dilation function
	namedWindow("edge", WINDOW_NORMAL);//create this windows
	cv::resizeWindow("edge", 500, 500);
	//create trackbars 
	createTrackbar("threshold", "edge", &binarythreshold, MaxbinarythresholdValue, binary_erson_dilation);//create a slider to contorl the binary image threshold
	*/
	//createTrackbar("cannyMin", "edge", &g_nThresh, g_nThresh_max, features);(because I do not know how to set this threashold so I change this to a comment)
	namedWindow("edge", WINDOW_NORMAL);//create this windows
	//cv::resizeWindow("edge", 500, 500);
	createTrackbar("threshold", "edge", &binarythreshold, MaxbinarythresholdValue, features);//create a slider to contorl the binary image threshold
	createTrackbar("MIN OBJECT", "edge", &omin, OMIN, features);//create a slider to contorl the minimum area of object threshold
	createTrackbar("MAX OBJECT", "edge", &omax, OMAX, features);//create a slider to contorl the maximum area of object threshold
	features(0, 0);
	//createTrackbar("cannyMax", "edge", &g_nThresh1, g_nThresh_max, features);(because I do not know how to set this threashold so I change this to a comment)
	namedWindow("contours(remove noise)", WINDOW_NORMAL);//create this windows
	//cv::resizeWindow("contours(remove noise)", 500, 500);//resize this windows	
	features(0, 0);//go to features function
	maxnum = g_vContours.size()-1;//set the value of maxnum as g_vContours.size()-1
	createTrackbar("object No.", "contours(remove noise)", &num, maxnum, features);//create a slider to show the different object,default is to show all the object
	features(num, 0);//go to features function
	cout << "connected compoents are" << g_vContours.size() << std::endl;//get the result by counting the size of g_vContours
	waitKey(0);//wait user's input
	return 0;
}
void features(int, void*)
{
	threshold(inputimage, result, binarythreshold, 255, cv::THRESH_BINARY_INV);//get the binary image and reverse color
	// detect edge by using canny function

	cv::dilate(result, dilated, cv::Mat());//dilate the binary image
	cv::erode(dilated, eroded, cv::Mat());//erode the binary image
	namedWindow("Dilated Image", WINDOW_NORMAL);//create a windows
	namedWindow("Eroded Image", WINDOW_NORMAL);//create a windows
	//resizeWindow("Eroded Image", 500, 500);//resize this windows
	imshow("Eroded Image", eroded);//show the image
	//resizeWindow("Dilated Image", 500, 500);//resize this windows
	imshow("Dilated Image", dilated);//show the image
	//resizeWindow("binary image", 500, 500);//resize this windows
	namedWindow("binary image", WINDOW_NORMAL);//create this windows
	imshow("binary image", result);//show the image
	Canny(dilated, g_cannyMat_output, g_nThresh, g_nThresh1, 5);//use canny function to detect the contours
	bitwise_not(g_cannyMat_output, contours_output);//Reverse color
	bitwise_not(result, result_output);//Reverse color
	namedWindow("contours", WINDOW_NORMAL);//create this windows
	//resizeWindow("contours", 500, 500);//resize this windows
	imshow("contours", contours_output);//show the image
	imshow("edge", result_output);//show the image
	// findcontours
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, cv::RETR_EXTERNAL /*RETR_TREE*/, cv::CHAIN_APPROX_NONE/*CHAIN_APPROX_SIMPLE*/, Point(0, 0));//store those contours in g_vFontours
	//delect the noise of objects
	originalsize = g_vContours.size();//store the number of object before filter the object
	//here we use iterator to filter the image
	std::vector<std::vector<cv ::
		Point>> ::
		const_iterator itc = g_vContours.begin();//create an iterator 
	//delete the object which greater than the maximum area and less than minimum area
	while (itc != g_vContours.end()) {
		if (itc->size() < omin || itc->size() > omax)
			itc = g_vContours.erase(itc);
		else
			++itc;
	}
	Mat rmnoise(inputimage.size(), CV_8U, cv::Scalar(255));//create an image with white background to store a new image after filter the object
	//draw the object on rmnoise image
	drawContours(rmnoise, g_vContours,
		num,//draw all the objects
		cv::Scalar(0), // color is black
		FILLED); //the width of contours are 2 
	imshow("contours(remove noise)", rmnoise);//show the image
	Mat colorful = Mat::zeros(result.size(), CV_8UC3);//create an three channel image with white background and the size is the same as result image
	bitwise_not(colorful, colorful_output);// reserve the color
	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));// set variable color to ramdom color
		drawContours(colorful_output, g_vContours, i, color, FILLED, 8, vector<Vec4i>(), 0, Point());
	}
	namedWindow("objects", WINDOW_NORMAL);//create this windows
	//cv::resizeWindow("objects", 500, 500);//resize this windows
	imshow("objects", colorful_output);//show the image
	// calculate moments
	vector<Moments> mu(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)// search from all the objects
	{
		mu[i] = moments(g_vContours[i], false);//mu is central moment
	}
	//from https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html
	vector<Rect> boundRect(g_vContours.size());//create a vector to store the information of the object bounding rectangle 
	vector<Point2f>center(g_vContours.size());//create a vector to store the information of the object center point
	vector<float>radius(g_vContours.size());//create a vector to store the information of the object radius
	vector<vector<Point>> g_vContours_poly(g_vContours.size());// used to store the feature(boundrect,center point) on this vector
	for (unsigned int i = 0; i < g_vContours.size(); i++)// search from all the objects
	{
		//from https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html 
		approxPolyDP(Mat(g_vContours[i]), g_vContours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(g_vContours_poly[i]));
		minEnclosingCircle((Mat)g_vContours_poly[i], center[i], radius[i]);
	}
	//draw the boundary and the bounding box
	Mat drawingrectcir = Mat::zeros(result.size(), CV_8UC3);//create an three channel image with white background and the size is the same as result image
	bitwise_not(drawingrectcir, drawingrectcir_output);//Reverse color
	for (int i = 0; i < g_vContours.size(); i++)
	{
		//from https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html 
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));// set variable color to ramdom color
		drawContours(drawingrectcir_output, g_vContours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		//tl:top left.br:bottom right
		rectangle(drawingrectcir_output, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);//draw a rectangle
		circle(drawingrectcir_output, center[i], (int)radius[i], color, 2, 8, 0);//draw a circle 
	}
	namedWindow("Contours", WINDOW_NORMAL);//create this windows
	//cv::resizeWindow("Contours", 500, 500);//resize this windows
	imshow("Contours", drawingrectcir_output);//show the image
	//  calculate the center point
	vector<Point2f> mc(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		//get each object's center point 
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	// draw contours
	Mat drawingContours = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	bitwise_not(drawingContours, drawingContours_output);//Reverse color
	//output the information about the objects
	for (int x = 0; x < g_vContours.size(); x++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//random number
		drawContours(drawingContours_output, g_vContours, x, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawingContours_output, mc[x], 4, color, -1, 8, 0);
		// output the features of objects
		printf("\t output::the features of objects \n");
		printf(" Use m00 calculate the contours No.[%d]feathures Area: (M_00) = %.2f \n  and use OpenCV function:Area=%.2f , perimeter= %.2f ,circularity1=%.2f ,center point：(%.2f,%.2f), second moment:urr=%.2f, urc=%.2f,ucc=%.2f ,Axis of least inertia=%f \n\n",
			x + 1, mu[x].m00, contourArea(g_vContours[x]), arcLength(g_vContours[x], false),
			arcLength(g_vContours[x], false)*arcLength(g_vContours[x], false) / contourArea(g_vContours[x]),
			mc[x].x, mc[x].y, mu[x].mu20 / mu[x].m00, mu[x].mu11 / mu[x].m00, mu[x].mu02 / mu[x].m00, 2 * mu[x].mu11 / (mu[x].mu02*mu[x].mu20));//urr, urc, ucc, tana);

		

		/*countexe = 1 + countexe;
		if (countexe == 1)//set the condition :when the number of object is change or the first time execute do those operation(print the features of objects)
		{
		for (unsigned int i = 0; i < g_vContours.size() - 1; i++)
		{
			for (unsigned int j = i + 1; j < g_vContours.size(); j++)
			{
				double matching = matchShapes(g_vContours[i], g_vContours[j], CONTOURS_MATCH_I1, 0);//use matchshapes function to compare each object
				cout << "the similarity of No." << i + 1 << "and No," << j + 1 << "object is " << matching << "(using matchshapes function,the smaller the value obtained, the more similar the two objects are )" << endl;
			}

		}
		}*/

	}
	namedWindow("moment", WINDOW_NORMAL);//create this windows
		//cv::resizeWindow("moment", 500, 500);//resize this windows
	imshow("moment", drawingContours_output);//show the image
}
	
