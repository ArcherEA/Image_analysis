#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cmath>
using namespace cv;
using namespace std;
void helptext()
{
	cout << "\t\t-------------------------------------------------------------------------\t\t" << endl;
	cout << "\t\t        this program is made by Yukuan Hao, Liang Gu, Liming Yang and Rouwen Mao " << endl;
	cout << "\t\t         please input an image location\t\t" << endl;
	cout << "\t\t-------------------------------------------------------------------------\t\t" << endl;
}
void helptext2() 
{
	cout << "load image success!" << endl;
	cout << "there are some methods to enhance the image.\t\t" << endl;
}
void helptext3()
{
	cout << "please choose one method\t\t" << endl;
	cout << "1.histogram stretch  2.powerlaw filter  3.linear filter(average mask)  4.median filter  5.sobel edge detector  6.Gaussian filter" << endl;
	cout << "If you are satisfied with the results, please enter \"stop\" to show the original image" << endl;
}

class Histogram1D {
private:
	int histsize[1];     
	float hranges[2];  
	const float*ranges[1];
	int channels[1];  
public:
	Histogram1D() 
	{
		histsize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}

};
Mat getHistImg(const MatND& hist) {
	double maxVal = 0;
	double minVal = 0;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	int histSize = hist.rows;
	Mat histImg(histSize, histSize, CV_8U, Scalar(255));
	int hpt = static_cast<int>(0.9*histSize);

	for (int h = 0; h < histSize; h++)
	{
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*hpt / maxVal);
		line(histImg, Point(h, histSize), Point(h, histSize - intensity), Scalar::all(0));
	}

	return histImg;
};
Mat histo(Mat &img) 
{
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };
	MatND hist;
	calcHist(&img, 1, channels, Mat(), hist, 1, histSize, ranges);
	Mat image1 = getHistImg(hist);
	return image1;
}
int checkmask()
{
	int mask;
	cout << "please input the mask level (3,5,7...)" << endl;
	cin >> mask;
	if (mask > 2 && (mask - 1) % 2 == 0) { cout << "the value is correct" << endl; return mask; }
	else
	{
		cout << "the value is not correct,the correct number is 3,5,7..." << endl;
		return checkmask();
	}
}
double checkvalue()
{
	double value;
	cin >> value;
	if (value > 0) { cout << "the value is correct" << endl; return value; }
	else
	{
		cout << "the value is not correct,the value range is positive number" << endl;
		return checkvalue();
	}
}
template <class  ItemType >
int  MinIndex(ItemType values[], int  start, int end)
{
	int  indexOfMin = start;
	for (int index = start + 1; index <= end; index++)
		if (values[index] < values[indexOfMin])
			indexOfMin = index;
	return   indexOfMin;
}
template <class  ItemType >
void  SelectionSort(ItemType values[],
	int  numValues)
{
	int  endIndex = numValues - 1;
	for (int current = 0; current < endIndex;
		current++)
		std::swap(values[current],
			values[MinIndex(values, current, endIndex)]);
}
Mat selectcontour(Mat &img)
{
	Mat dstImage;
	dstImage = Mat::zeros(img.size(), 0);
	int imax = img.rows;
	int jmax = img.cols;

	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			if (i - 1 >= 0 && i + 1 < imax&&j - 1 >= 0 && j + 1 < jmax)
			{
				dstImage.ptr<uchar>(i)[j] = sqrt((-img.ptr<uchar>(i - 1)[j - 1] + img.ptr<uchar>(i - 1)[j + 1] - 2 * img.ptr<uchar>(i)[j - 1] + 2 * img.ptr<uchar>(i)[j + 1] - img.ptr<uchar>(i + 1)[j - 1] +
					img.ptr<uchar>(i + 1)[j + 1])
					*(-img.ptr<uchar>(i - 1)[j - 1] + img.ptr<uchar>(i - 1)[j + 1] - 2 * img.ptr<uchar>(i)[j - 1] + 2 * img.ptr<uchar>(i)[j + 1] - img.ptr<uchar>(i + 1)[j - 1] + img.ptr<uchar>(i + 1)[j + 1])
					+ (img.ptr<uchar>(i - 1)[j - 1] + 2 * img.ptr<uchar>(i - 1)[j] + img.ptr<uchar>(i)[j + 1] - img.ptr<uchar>(i + 1)[j - 1] - 2 * img.ptr<uchar>(i + 1)[j] - img.ptr<uchar>(i + 1)[j + 1])
					*(img.ptr<uchar>(i - 1)[j - 1] + 2 * img.ptr<uchar>(i - 1)[j] + img.ptr<uchar>(i)[j + 1] - img.ptr<uchar>(i + 1)[j - 1] - 2 * img.ptr<uchar>(i + 1)[j] - img.ptr<uchar>(i + 1)[j + 1]));
			}
			else { dstImage.ptr<uchar>(i)[j] = img.ptr<uchar>(i)[j]; }
		}
	}
	return dstImage;
}
Mat histo_stretch(Mat& img)
{
	int a[256];
	for (int i = 0; i < 256; i++) 
	{
		a[i] = 0;
	}
	int imax = img.rows;
	int jmax = img.cols;
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++) 
		{
			a[img.ptr<uchar>(i)[j]]=a[img.ptr<uchar>(i)[j]]+1;
		}
	}
	int sum=0;
	int nmax;
	int nmin;
	for (int i = 0; i < 256; i++) 
	{
		sum = a[i] + sum;
	}
	for (int i = 0; i < 256; i++)
	{
		if (a[i] > 0 )
		{
			nmin = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--)
	{
		if (a[i] > 0)
		{
			nmax = i;
			break;
		}
	}
	Mat dstImage;
	dstImage = Mat::zeros(img.size(), 0);
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			if (img.ptr<uchar>(i)[j] < nmin) { dstImage.ptr<uchar>(i)[j] = 0; }
			else if (img.ptr<uchar>(i)[j] > nmax) { dstImage.ptr<uchar>(i)[j] = 255; }
			else 
			{
				int value= (img.ptr<uchar>(i)[j] - nmin) * 255 / (nmax - nmin);
				dstImage.ptr<uchar>(i)[j] = static_cast<uchar>(std::round((img.ptr<uchar>(i)[j] - nmin) * 255.0 / (nmax - nmin)));
			}
		}
	}
	return dstImage;
}
Mat powerlaw(Mat &img,double R,double c) 
{
	Mat dstImage;
	dstImage = Mat::zeros(img.size(), 0);
	int imax = img.rows;
	int jmax = img.cols;
	double pixel;
	
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			pixel = img.ptr<uchar>(i)[j];
			if (c*(pow(pixel,R)) <= 255)
			{
				dstImage.ptr<uchar>(i)[j] = c * (pow(pixel, R));
			}
			else { dstImage.ptr<uchar>(i)[j] = 255; }
		}
	}
	return dstImage;
}
Mat Gaussian(Mat &img, int mask)
{
	int level = (mask - 1) / 2;
	Mat dstImage;
	dstImage = Mat::zeros(img.size(), 0);
	int imax = img.rows;
	int jmax = img.cols;
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			if (i - level >= 0 && i + level < imax&&j - level >= 0 && j + level < jmax)
			{
				double pixel = 0;
				double sum = 0;
				for (int ii = -level; ii <= level; ii++)
				{
					for (int jj = -level; jj <= level; jj++)
					{
						pixel = exp(-(ii)^2+(jj)^2)*img.ptr<uchar>(i + ii)[j + jj] + pixel;
						sum = sum + exp(-(ii) ^ 2 + (jj) ^ 2);
					}
				}
				dstImage.ptr<uchar>(i)[j] = pixel / sum;
			}
			else { dstImage.ptr<uchar>(i)[j] = img.ptr<uchar>(i)[j]; }
		}
	}
	return dstImage;
}
Mat linear(Mat &img,int mask)
{
	int level = (mask - 1) / 2;
	Mat dstImage;
	dstImage = Mat::zeros(img.size(), 0);
	int imax = img.rows;
	int jmax = img.cols;
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			if (i-level>=0&&i+level<imax&&j-level>=0&&j+level<jmax)
			{
				double pixel = 0;
				for (int ii=-level;ii<=level;ii++)
				{
					for (int jj = -level; jj <= level; jj++) 
					{
						pixel = img.ptr<uchar>(i + ii)[j + jj] + pixel;
					}
				}
				dstImage.ptr<uchar>(i)[j]= pixel/(mask*mask);
			}
			else { dstImage.ptr<uchar>(i)[j] = img.ptr<uchar>(i)[j]; }
		}
	}
	return dstImage;
}
Mat median(Mat &img,int mask) 
{
	const int level = (mask - 1) / 2;
	uchar *a=new uchar[mask*mask];

	Mat dstImage;
	dstImage = Mat::zeros(img.size(), 0);
	int imax = img.rows;
	int jmax = img.cols;
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			if (i - level >= 0 && i + level < imax&&j - level >= 0 && j + level < jmax)
			{
				int k = 0;
				for (int c = i - level; c < i + level+1 ; c++) 
				{
					for (int b = j - 1; b < j + level+1; b++) 
					{
						a[k] = img.ptr<uchar>(c)[b];
						k++;
					}
				}
				SelectionSort(a, mask*mask);
				dstImage.ptr<uchar>(i)[j] = a[5];
			}
			else { dstImage.ptr<uchar>(i)[j] = img.ptr<uchar>(i)[j]; }
		}
	}
	delete a;
	return dstImage;
}
Mat control2(Mat &image,int i) 
{
	i++;
	string a;
	helptext3();
	cout << "please input a number" << endl;
	cin >> a;
	if (a == "1") 
	{
		string b = "histogram stretch";
		Mat result= histo_stretch(image);
		imshow("step" + to_string(i) + ":" + b, result);
		waitKey(1000);
		Mat histogram = histo(result);
		imshow("step" + to_string(i) + ": histogram" ,histogram);
		waitKey(1000);
		return control2(result,i);
	}
	else if(a=="2")
	{
		string b = "power law filter";
		double R;
		double c;
		cout << "please input the parameter c (the value range is positive values)"<<endl;
		c=checkvalue();
		cout << "please input the parameter gama (the value range is positive values)" << endl;
		R=checkvalue();
		Mat result = powerlaw(image,R,c);
		imshow("step" + to_string(i) + ":" + b, result);
		waitKey(1000);
		Mat histogram = histo(result);
		imshow("step" + to_string(i) + ": histogram", histogram);
		waitKey(1000);
		return control2(result, i);
	}
	else if (a == "3")
	{
		string b = "linear filter";
		int mask;
		mask=checkmask();
		Mat result = linear(image,mask);
		imshow("step" + to_string(i) + ":" + b, result);
		waitKey(1000);
		Mat histogram = histo(result);
		imshow("step" + to_string(i) + ": histogram", histogram);
		waitKey(1000);
		return control2(result, i);
	}
	else if (a == "4")
	{
		string b = "median filter";
		int mask=checkmask();
		Mat result = median(image, mask);
		imshow("step" + to_string(i) + ":" + b, result);
		waitKey(1000);
		Mat histogram = histo(result);
		imshow("step" + to_string(i) + ": histogram", histogram);
		waitKey(1000);
		return control2(result, i);
	}
	else if (a == "5")
	{
		string b = "edge detection";
		Mat result = selectcontour(image);
		imshow("step"+to_string(i)+":"+b, result);
		waitKey(1000);
		Mat histogram = histo(result);
		imshow("step" + to_string(i) + ": histogram", histogram);
		waitKey(1000);
		return control2(result, i);
	}
	else if (a == "6")
	{
		string b = "Gaussian filter";
		int mask;
		mask = checkmask();
		Mat result = Gaussian(image, mask);
		imshow("step" + to_string(i) + ":" + b, result);
		waitKey(1000);
		Mat histogram = histo(result);
		imshow("step" + to_string(i) + ": histogram", histogram);
		waitKey(1000);
		return control2(result, i);
	}
	else if (a == "stop") 
	{
		return image;
	}
	else{
		i--;
		cout << "please input correct number(1-6)" << endl;
		return control2(image, i);
	}
}
Mat control(Mat &image) 
{
	cout << "do you want use default setting(Y/N)" << endl;
	string a;
	cin >> a;
	if (a=="YES"||a=="yes"||a=="Y"||a=="y")
	{
		cout<<"the default setting:1.histogram stretch 2.median filter(3x3) 3.sobel edge detecter(3x3)"<<endl;
		Mat result= histo_stretch(image);
		imshow("first step:histogram stretch", result);
		Mat result2= median(result,3);
		imshow("Second step:median filter(3x3)", result2);
		Mat edge= selectcontour(result2);
		imshow("third step:sobel edge detecter(3x3)", edge);
		waitKey(1000);
		return edge;
	}
	else if(a == "NO" || a == "no" || a == "N" || a == "n") { return control2(image,0); }
	else 
	{
		cout << "please input correct answer" << endl;
		return control(image);
	}
}
Mat loadimage()
{
	string a;
	cin >> a;
	Mat image= imread(a, 0);
	if (image.data == NULL) 
	{
		cout << "cannot open the image, please check the location" << endl;
		return loadimage();
	}
	else 
	{
		return image;
	}
}
int main()
{
	helptext();
	Mat img = loadimage();
	Mat hisotgram_origin = histo(img);
	imshow("origin histogram", hisotgram_origin);
	waitKey(1000);
	helptext2();
	control(img);
	imshow("origin picture", img);
	waitKey(1000);
	waitKey(0);
}
