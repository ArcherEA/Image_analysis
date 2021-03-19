#include <opencv2/opencv.hpp>
#include <cmath>
#include "ConsoleApplication1.h"
using namespace cv;
using namespace std;

string input;
Mat inputimage;


 void kmeanscolor(int k, Mat img)
 {
	 if (img.channels() == 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	 }
	 RNG rng;
	 int *distance = new int[k];
	 vector<Vec3b> *cluster = new vector<Vec3b>[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 Vec3b *centerold = new Vec3b[k];
	 Vec3b *center = new Vec3b[k];
	 int flag = 0;
	 for (int p = 0; p < k; p++)
	 {
		 center[p][0] = rng.operator uchar();
		 center[p][1] = rng.operator uchar();
		 center[p][2] = rng.operator uchar();
	 }
	 
	 do {
		 for (int i = 0; i < k; i++) 
		 {
			 centerold[i][0]=center[i][0];
			 centerold[i][1] = center[i][1];
			 centerold[i][2] = center[i][2];
		 }
		 
		 for (int i = 0; i < k; i++)
		 {
			 distance[i] = 0;
		 }
		 vector<int> *tempcol = new vector<int>[k];
		 vector<int> *temprow = new vector<int>[k];
		 vector<Vec3b> *tempcluster = new vector<Vec3b>[k];
		 delete[] cluster;
		 delete[]col;
		 delete[]row;
		 cluster = tempcluster;
		 col = tempcol;
		 row = temprow;
		 for (int i = 0; i < img.rows; i++)
		 {
			 for (int j = 0; j < img.cols; j++)
			 {
				 for (int p = 0; p < k; p++)
				 {
					 for (int b = 0; b < 3; b++)
					 {

						 distance[p] = pow((img.at<Vec3b>(i, j)[b] - center[p][b]),2) + distance[p];
						 
					 }
					 distance[p] = sqrt(distance[p]);
					
				 }
				 double min = distance[0];
				 int no = 0;
				 for (int x = 0; x < k; x++)
				 {
					 if (distance[x] < min)
					 {
						 min = distance[x];
						 no = x;
					 }
				 }
				 cluster[no].push_back(img.at<Vec3b>(i, j));
				 col[no].push_back(j);
				 row[no].push_back(i);
			 }
		 }
		 for (int i = 0; i < k; i++)
		 {
			 double sum[3] = { 0, 0, 0 };
			 int max = cluster[i].size();
			 for (int j = 0; j < max; j++)
			 {
				 sum[0] = cluster[i][j][0] + sum[0];
				 sum[1] = cluster[i][j][1] + sum[1];
				 sum[2] = cluster[i][j][2] + sum[2]; 
			 }
			 center[i][0] = sum[0] / max;
			 center[i][1] = sum[1] / max;
			 center[i][2] = sum[2] / max;
			 //cout << center[i][0] << " " << center[i][1] << " " << center[i][2] << endl;
			/* double *test = new double[3 * k];
			 for (int i = 0; i < k; i++) 
			 {
				 for (int j = 0; j < 3; j++)
				 {
					 test[3 * i + j] = center[i][j];
					 cout << test[3 * i + j] << endl;
				 }
			 }*/
		 }
		 flag = 0;
		 for (int i = 0; i < k; i++) 
		 {
			 if (center[i][0] == centerold[i][0] && center[i][1] == centerold[i][1] && center[i][2] == centerold[i][2]) 
			 {
				 flag++;
			 }
		 }

	 } while (flag!=k);
	/*double *test = new double[3 * k];
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < 3; j++)
		 {
			 test[3 * i + j] = center[i][j];
			 cout << test[3 * i + j] << endl;
		 }
	 }*/

	 Mat result(img.rows, img.cols, img.type());
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j <cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] =r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	 namedWindow("kmeansResult", WINDOW_NORMAL);
	 cv::imshow("kmeansResult", result);
	 
 }

 void kmeansgrayscale(int k, Mat img)
 {
	if (img.channels() != 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	 }
	 RNG rng;
	 double *distance = new double[k];
	 vector<uchar> *cluster = new vector<uchar>[k];
	 vector<int> *col= new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 uchar *centerold = new uchar[k];
	 uchar *center = new uchar[k];
	 int flag = 0;
	 for (int i = 0; i < k; i++)
	 {
		 center[i] = rng.operator uchar();
	 }
	
	 do 
	 {
		 for (int i = 0; i < k; i++)
		 {
			 centerold[i] = center[i];
		 }
		 for (int i = 0; i < k; i++)
		 {
			 distance[i] = 0;
		 }
		 vector<int> *tempcol = new vector<int>[k];
		 vector<int> *temprow = new vector<int>[k];
		 vector<uchar> *tempcluster = new vector<uchar>[k];
		 delete[]cluster;
		 delete[] col;
		 delete[]row;
		 cluster = tempcluster;
		 col = tempcol;
		 row = temprow;
		 for (int i = 0; i < img.rows; i++)
		 {
			 for (int j = 0; j < img.cols; j++)
			 {


				 for (int p = 0; p < k; p++)
				 {
					 distance[p] = sqrt(pow((img.at<uchar>(i, j) - center[p]),2));
				 }
				 double min = distance[0];
				 int no = 0;
				 for (int x = 0; x < k; x++)
				 {
					 if (distance[x] < min)
					 {
						 min = distance[x];
						 no = x;
					 }
				 }
				 cluster[no].push_back(img.at<uchar>(i, j));
				 col[no].push_back(j);
				 row[no].push_back(i);
			 }
		 }
		 for (int i = 0; i < k; i++)
		 {

			 double sum = 0;
			 int max = cluster[i].size();
			 for (int j = 0; j < max; j++)
			 {
				 sum = cluster[i][j] + sum;
			 }
			 center[i] = sum / max;
		 }
		 flag = 0;
		 for (int i = 0; i < k; i++)
		 {
			 if (center[i] == centerold[i])
			 {
				 flag++;
			 }
		 }
	 } while (flag!=k);
	 Mat result(img.rows, img.cols, img.type());//need change to color image
	 cv::cvtColor(img, result, cv::COLOR_GRAY2BGR);
	 uchar *r = new uchar[k];
	 uchar *g= new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		  r[i] = rng.operator uchar();
		  g[i] = rng.operator uchar();
		  b[i]= rng.operator uchar();
	 }

	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++) 
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	 cv::imshow("kmeansResult", result);
	 Vec3b *centercolor=new Vec3b[k];
	 for (int i = 0; i < k; i++)
	 {
		 centercolor[i][0] = center[i];
		 centercolor[i][1] = center[i];
		 centercolor[i][2] = center[i];
	 }
	 
 }

 void kmeanslocationcolor(int k, Mat img)
 {
	 
	 if (img.channels() == 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	 }
	 RNG rng;
	 int *distance = new int[k];
	 vector<Vec3b> *cluster = new vector<Vec3b>[k];
	 int *colcenter = new int[k];
	 int *rowcenter = new int[k];
	 int *colcenterold = new int[k];
	 int *rowcenterold = new int[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 Vec3b *centerold = new Vec3b[k];
	 Vec3b *center = new Vec3b[k];
	 int flag = 0;
	 
	 for (int p = 0; p < k; p++)
	 {
		 colcenter[p] = rand()%img.cols;
		 rowcenter[p]= rand() % img.rows;
	 }
	 for (int p = 0; p < k; p++)
	 {
		 center[p][0] = img.at<Vec3b>(rowcenter[p], colcenter[p])[0];
		 center[p][1] = img.at<Vec3b>(rowcenter[p], colcenter[p])[1];
		 center[p][2] = img.at<Vec3b>(rowcenter[p], colcenter[p])[2];
	 }

	 do {
		 for (int i = 0; i < k; i++)
		 {
			 centerold[i][0] = center[i][0];
			 centerold[i][1] = center[i][1];
			 centerold[i][2] = center[i][2];
			 colcenterold[i] = colcenter[i];
			 rowcenterold[i] = rowcenter[i];
		 }
		

		 for (int i = 0; i < k; i++)
		 {
			 distance[i] = 0;
		 }
		 vector<int> *tempcol = new vector<int>[k];
		 vector<int> *temprow = new vector<int>[k];
		 vector<Vec3b> *tempcluster = new vector<Vec3b>[k];
		 delete[] cluster;
		 delete[] col;
		 delete[] row;
		 cluster = tempcluster;
		 col = tempcol;
		 row = temprow;
		 
		 for (int i = 0; i < img.rows; i++)
		 {
			 for (int j = 0; j < img.cols; j++)
			 {
				 for (int p = 0; p < k; p++)
				 {
					 for (int b = 0; b < 3; b++)
					 {

						 distance[p] = pow((img.at<Vec3b>(i, j)[b] - center[p][b]), 2) + distance[p];

					 }
					 distance[p] = (pow(i - rowcenter[p], 2) + pow(j - colcenter[p], 2))/100 + distance[p];
					 distance[p] = sqrt(distance[p]);

				 }
				 double min = distance[0];
				 int no = 0;
				 for (int x = 0; x < k; x++)
				 {
					 if (distance[x] < min)
					 {
						 min = distance[x];
						 no = x;
					 }
				 }
				 cluster[no].push_back(img.at<Vec3b>(i, j));
				 col[no].push_back(j);
				 row[no].push_back(i);
			 }
		 }
		 for (int i = 0; i < k; i++)
		 {
			 double sum[3] = { 0, 0, 0 };
			 int max = cluster[i].size();
			 for (int j = 0; j < max; j++)
			 {
				 sum[0] = cluster[i][j][0] + sum[0];
				 sum[1] = cluster[i][j][1] + sum[1];
				 sum[2] = cluster[i][j][2] + sum[2];
			 }
			 center[i][0] = sum[0] / max;
			 center[i][1] = sum[1] / max;
			 center[i][2] = sum[2] / max;
			 int colavg=0;
			 int rowavg = 0;
			 for (int j = 0; j < max; j++) 
			 {
				 colavg = colavg +col[i][j] ;
				 rowavg = rowavg +row[i][j] ;
			 }
			 colcenter[i] = colavg / max;
			 rowcenter[i] = rowavg / max;

			 //cout << center[i][0] << " " << center[i][1] << " " << center[i][2] << endl;
			/* double *test = new double[3 * k];
			 for (int i = 0; i < k; i++)
			 {
				 for (int j = 0; j < 3; j++)
				 {
					 test[3 * i + j] = center[i][j];
					 cout << test[3 * i + j] << endl;
				 }
			 }*/
		 }
		 flag = 0;
		 for (int i = 0; i < k; i++)
		 {
			 if (center[i][0] == centerold[i][0] && center[i][1] == centerold[i][1] && center[i][2] == centerold[i][2]&& colcenter[i]== colcenterold[i]&& rowcenter[i]== rowcenterold[i])
			 {
				 flag++;
			 }
		 }

	 } while (flag != k);
	 /*double *test = new double[3 * k];
	  for (int i = 0; i < k; i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  test[3 * i + j] = center[i][j];
			  cout << test[3 * i + j] << endl;
		  }
	  }*/

	 Mat result(img.rows, img.cols, img.type());
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	
	 cv::imshow("kmeansResult", result);
	
 }

 void kmeanslocationgrayscale(int k, Mat img)
 {
	 if (img.channels() != 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	 }
	 RNG rng;
	 double *distance = new double[k];
	 int *colcenter = new int[k];
	 int *rowcenter = new int[k];
	 int *colcenterold = new int[k];
	 int *rowcenterold = new int[k];
	 vector<uchar> *cluster = new vector<uchar>[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 uchar *centerold = new uchar[k];
	 uchar *center = new uchar[k];
	 int flag = 0;
	 for (int i = 0; i < k; i++)
	 {
		 center[i] = rng.operator uchar();
	 }
	 for (int p = 0; p < k; p++)
	 {
		 colcenter[p] = rand() % img.cols;
		 rowcenter[p] = rand() % img.rows;
	 }

	 do
	 {
		 for (int i = 0; i < k; i++)
		 {
			 centerold[i] = center[i];
		 }
		 for (int i = 0; i < k; i++)
		 {
			 colcenterold[i] = colcenter[i];
			 rowcenterold[i] = rowcenter[i];
		 }

		 for (int i = 0; i < k; i++)
		 {
			 distance[i] = 0;
		 }


		 vector<int> *tempcol = new vector<int>[k];
		 vector<int> *temprow = new vector<int>[k];
		 vector<uchar> *tempcluster = new vector<uchar>[k];
		 delete[]cluster;
		 delete[]col;
		 delete[]row;
		 cluster = tempcluster;
		 col = tempcol;
		 row = temprow;


		 for (int i = 0; i < img.rows; i++)
		 {
			 for (int j = 0; j < img.cols; j++)
			 {


				 for (int p = 0; p < k; p++)
				 {
					 distance[p] = pow((img.at<uchar>(i, j) - center[p]), 2);
					 distance[p] = (pow(i - rowcenter[p], 2) + pow(j - colcenter[p], 2))/100 + distance[p];
					 distance[p] = sqrt(distance[p]);
				 }
				 
				 double min = distance[0];
				 int no = 0;
				 for (int x = 0; x < k; x++)
				 {
					 if (distance[x] < min)
					 {
						 min = distance[x];
						 no = x;
					 }
				 }
				 cluster[no].push_back(img.at<uchar>(i, j));
				 col[no].push_back(j);
				 row[no].push_back(i);
			 }
		 }
		 for (int i = 0; i < k; i++)
		 {

			 double sum = 0;
			 int max = cluster[i].size();
			 for (int j = 0; j < max; j++)
			 {
				 sum = cluster[i][j] + sum;
			 }
			 center[i] = sum / max;
		 }
		 flag = 0;
		 for (int i = 0; i < k; i++)
		 {
			 if (center[i] == centerold[i]&& colcenter[i] == colcenterold[i] && rowcenter[i] == rowcenterold[i])
			 {
				 flag++;
			 }
		 }
	 } while (flag != k);
	 Mat result(img.rows, img.cols, img.type());//need change to color image
	 cv::cvtColor(img, result, cv::COLOR_GRAY2BGR);
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }

	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	
	 cv::imshow("kmeansResult", result);
	 Vec3b *centercolor = new Vec3b[k];
	 for (int i = 0; i < k; i++)
	 {
		 centercolor[i][0] = center[i];
		 centercolor[i][1] = center[i];
		 centercolor[i][2] = center[i];
	 }
	 
 }

 void Meng_Hee_Hengcolor( int maxcluster,Mat img)
 {
	 if (img.channels() == 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	 }
	 int k = 2;
	 int oldk;
	 RNG rng;
	 int avgcenterdistance=0;
	 int maxi[3];
	 int *distance = new int[k];
	 vector<Vec3b> *cluster = new vector<Vec3b>[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 Vec3b *centerold = new Vec3b[k];
	 Vec3b *center = new Vec3b[k];
	 int flag = 0;
	 for (int p = 0; p < k; p++)
	 {
		 center[p][0] = rng.operator uchar();
		 center[p][1] = rng.operator uchar();
		 center[p][2] = rng.operator uchar();
	 }
	
	 
	 do {
		 for (int p = 0; p < 3; p++)
		 {
			 maxi[p] = 0;
		 }
		 oldk = k;
		 do {
			 for (int i = 0; i < k; i++)
			 {
				 centerold[i][0] = center[i][0];
				 centerold[i][1] = center[i][1];
				 centerold[i][2] = center[i][2];
			 }
			 vector<int> *tempcol = new vector<int>[k];
			 vector<int> *temprow = new vector<int>[k];
			 vector<Vec3b> *tempcluster = new vector<Vec3b>[k];
			 delete[]cluster;
			 delete[]col;
			 delete[] row;
			 cluster = tempcluster;
			 col = tempcol;
			 row = temprow;
			 for (int i = 0; i < k; i++)
			 {
				 distance[i] = 0;
			 }
			 
			 for (int i = 0; i < img.rows; i++)
			 {
				 for (int j = 0; j < img.cols; j++)
				 {
					 for (int p = 0; p < k; p++)
					 {
						 for (int b = 0; b < 3; b++)
						 {

							 distance[p] = pow((img.at<Vec3b>(i, j)[b] - center[p][b]), 2) + distance[p];

						 }
						 distance[p] = sqrt(distance[p]);
						
					 }
					 double min = distance[0];
					 int no = 0;
					 for (int x = 0; x < k; x++)
					 {
						 if (distance[x] < min)
						 {
							 min = distance[x];
							 no = x;
						 }
					 }
					 if (distance[no] > maxi[0])
					 {
						 maxi[0] = distance[no];
						 maxi[1] = i;
						 maxi[2] = j;
					 }
					 cluster[no].push_back(img.at<Vec3b>(i, j));
					 col[no].push_back(j);
					 row[no].push_back(i);
				 }
			 }
			 for (int i = 0; i < k; i++)
			 {
				 double sum[3] = { 0, 0, 0 };
				 int max = cluster[i].size();
				 for (int j = 0; j < max; j++)
				 {
					 sum[0] = cluster[i][j][0] + sum[0];
					 sum[1] = cluster[i][j][1] + sum[1];
					 sum[2] = cluster[i][j][2] + sum[2];
				 }
				 center[i][0] = sum[0] / max;
				 center[i][1] = sum[1] / max;
				 center[i][2] = sum[2] / max;
				 //cout << center[i][0] << " " << center[i][1] << " " << center[i][2] << endl;
				/* double *test = new double[3 * k];
				 for (int i = 0; i < k; i++)
				 {
					 for (int j = 0; j < 3; j++)
					 {
						 test[3 * i + j] = center[i][j];
						 cout << test[3 * i + j] << endl;
					 }
				 }*/
			 }
			 flag = 0;
			 for (int i = 0; i < k; i++)
			 {
				 if (center[i][0] == centerold[i][0] && center[i][1] == centerold[i][1] && center[i][2] == centerold[i][2])
				 {
					 flag++;
				 }
			 }

		 } while (flag != k);
		 int sum = 0;
		 for (int i = 0; i < k; i++) 
		 {
			 for (int j = i + 1; j < k; j++) 
			 {
				 sum++;
				 avgcenterdistance = sqrt(pow(center[i][0] - center[j][0], 2) + pow(center[i][1] - center[j][1], 2) + pow(center[i][2] - center[j][2], 2))+avgcenterdistance;
			 }
		 }
		 avgcenterdistance = avgcenterdistance / (2*sum);
		 if (maxi[0] > avgcenterdistance && k< maxcluster+1)
		 {
			 int *tempdistance=new int[k+1];
			 delete[]distance;
			 distance = tempdistance;
			 vector<Vec3b> *tempcluster = new vector<Vec3b>[k+1];
			 delete []cluster;
			 cluster = tempcluster;
			 vector<int> *tempcol = new vector<int>[k+1];
			 vector<int> *temprow = new vector<int>[k+1];
			 delete []col;
			 delete []row;
			 col = tempcol;
			 row = temprow;
			 Vec3b *tempcenterold = new Vec3b[k+1];
			 delete []centerold;
			 centerold = tempcenterold;
			 Vec3b *tempcenter = new Vec3b[k+1];
			 for (int i = 0; i < k; i++) 
			 {
				 tempcenter[i][0] = center[i][0];
				 tempcenter[i][1] = center[i][1];
				 tempcenter[i][2] = center[i][2];
			 }
			 delete[] center;
			 tempcenter[k][0]= img.at<Vec3b>(maxi[1], maxi[2])[0];
			 tempcenter[k][1]= img.at<Vec3b>(maxi[1], maxi[2])[1];
			 tempcenter[k][2]= img.at<Vec3b>(maxi[1], maxi[2])[2];
			 center = tempcenter;
			 k = k + 1; 
			
		 }
		

	 } while (k!=oldk&&k< maxcluster+2);
	 /*double *test = new double[3 * k];
	  for (int i = 0; i < k; i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  test[3 * i + j] = center[i][j];
			  cout << test[3 * i + j] << endl;
		  }
	  }*/

	 Mat result(img.rows, img.cols, img.type());
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	 cv::imshow("mhh", result);
	 
 }

 void Meng_Hee_Hengcolorlocation(int maxcluster,Mat img)
 {
	 if (img.channels() == 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	 }
	 int k = 2;
	 int oldk;
	 RNG rng;
	 int avgcenterdistance = 0;
	 int maxi[3];
	 int *colcenter = new int[k];
	 int *rowcenter = new int[k];
	 int *colcenterold = new int[k];
	 int *rowcenterold = new int[k];
	 int *distance = new int[k];
	 vector<Vec3b> *cluster = new vector<Vec3b>[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 Vec3b *centerold = new Vec3b[k];
	 Vec3b *center = new Vec3b[k];
	 int flag = 0;
	 for (int p = 0; p < k; p++)
	 {
		 colcenter[p] = rand() % img.cols;
		 rowcenter[p] = rand() % img.rows;
	 }
	 for (int p = 0; p < k; p++)
	 {
		 center[p][0] = img.at<Vec3b>(rowcenter[p], colcenter[p])[0];
		 center[p][1] = img.at<Vec3b>(rowcenter[p], colcenter[p])[1];
		 center[p][2] = img.at<Vec3b>(rowcenter[p], colcenter[p])[2];
	 }


	 do {
		 for (int p = 0; p < 3; p++)
		 {
			 maxi[p] = 0;
		 }
		 
		 oldk = k;
		 do {
			 for (int i = 0; i < k; i++)
			 {
				 centerold[i][0] = center[i][0];
				 centerold[i][1] = center[i][1];
				 centerold[i][2] = center[i][2];
				 colcenterold[i] = colcenter[i];
				 rowcenterold[i] = rowcenter[i];
			 }
			
			 vector<int> *tempcol = new vector<int>[k];
			 vector<int> *temprow = new vector<int>[k];
			 vector<Vec3b> *tempcluster = new vector<Vec3b>[k];
			 delete[]cluster;
			 delete[]col;
			 delete[] row;
			 cluster = tempcluster;
			 col = tempcol;
			 row = temprow;
			 for (int i = 0; i < k; i++)
			 {
				 distance[i] = 0;
			 }

			 for (int i = 0; i < img.rows; i++)
			 {
				 for (int j = 0; j < img.cols; j++)
				 {
					 for (int p = 0; p < k; p++)
					 {
						 for (int b = 0; b < 3; b++)
						 {

							 distance[p] = pow((img.at<Vec3b>(i, j)[b] - center[p][b]), 2) + distance[p];

						 }
						 distance[p] = (pow(i - rowcenter[p], 2) + pow(j - colcenter[p], 2))/100 + distance[p];
						 distance[p] = sqrt(distance[p]);
					 }
					 double min = distance[0];
					 int no = 0;
					 for (int x = 0; x < k; x++)
					 {
						 if (distance[x] < min)
						 {
							 min = distance[x];
							 no = x;
						 }
					 }
					 if (distance[no] > maxi[0])
					 {
						 maxi[0] = distance[no];
						 maxi[1] = i;
						 maxi[2] = j;
					 }
					 cluster[no].push_back(img.at<Vec3b>(i, j));
					 col[no].push_back(j);
					 row[no].push_back(i);
				 }
			 }
			 for (int i = 0; i < k; i++)
			 {
				 double sum[3] = { 0, 0, 0 };
				 int max = cluster[i].size();
				 for (int j = 0; j < max; j++)
				 {
					 sum[0] = cluster[i][j][0] + sum[0];
					 sum[1] = cluster[i][j][1] + sum[1];
					 sum[2] = cluster[i][j][2] + sum[2];
				 }
				 center[i][0] = sum[0] / max;
				 center[i][1] = sum[1] / max;
				 center[i][2] = sum[2] / max;
				 int colavg = 0;
				 int rowavg = 0;
				 for (int j = 0; j < max; j++)
				 {
					 colavg = colavg + col[i][j];
					 rowavg = rowavg + row[i][j];
				 }
				 colcenter[i] = colavg / max;
				 rowcenter[i] = rowavg / max;
				 //cout << center[i][0] << " " << center[i][1] << " " << center[i][2] << endl;
				/* double *test = new double[3 * k];
				 for (int i = 0; i < k; i++)
				 {
					 for (int j = 0; j < 3; j++)
					 {
						 test[3 * i + j] = center[i][j];
						 cout << test[3 * i + j] << endl;
					 }
				 }*/
			 }
			 flag = 0;
			 for (int i = 0; i < k; i++)
			 {
				 if (center[i][0] == centerold[i][0] && center[i][1] == centerold[i][1] && center[i][2] == centerold[i][2] && colcenter[i] == colcenterold[i] && rowcenter[i] == rowcenterold[i])
				 {
					 flag++;
				 }
			 }

		 } while (flag != k);
		 int sum = 0;
		 for (int i = 0; i < k; i++)
		 {
			 for (int j = i + 1; j < k; j++)
			 {
				 sum++;
				 avgcenterdistance = sqrt(pow(center[i][0] - center[j][0], 2) + pow(center[i][1] - center[j][1], 2) + pow(center[i][2] - center[j][2], 2)+pow(colcenter[i]- colcenter[j],2)+pow(rowcenter[i]- rowcenter[j],2)) + avgcenterdistance;
			 }
		 }
		 avgcenterdistance = avgcenterdistance / (2 * sum);
		 if (maxi[0] > avgcenterdistance && k < maxcluster+1)
		 {
			 int *tempdistance = new int[k + 1];
			 delete[]distance;
			 distance = tempdistance;
			 vector<Vec3b> *tempcluster = new vector<Vec3b>[k + 1];
			 delete[]cluster;
			 cluster = tempcluster;
			 vector<int> *tempcol = new vector<int>[k + 1];
			 vector<int> *temprow = new vector<int>[k + 1];
			 delete[]col;
			 delete[]row;
			 col = tempcol;
			 row = temprow;
			 Vec3b *tempcenterold = new Vec3b[k + 1];
			 delete[]centerold;
			 centerold = tempcenterold;
			 Vec3b *tempcenter = new Vec3b[k + 1]; 
			 int *tempcolcenter = new int[k+1];
			 int *temprowcenter = new int[k+1];
			 int *tempcolcenterold = new int[k+1];
			 int *temprowcenterold = new int[k+1];
			 for (int i = 0; i < k; i++)
			 {
				 tempcenter[i][0] = center[i][0];
				 tempcenter[i][1] = center[i][1];
				 tempcenter[i][2] = center[i][2];
				 tempcolcenter[i] = colcenter[i];
				 temprowcenter[i] = rowcenter[i];
				 
			 }
			 delete[] center;
			 delete[]colcenter;
			 delete[]rowcenter;
			 delete[]colcenterold;
			 delete[]rowcenterold;
			 tempcolcenter[k] = maxi[2];
			 temprowcenter[k] = maxi[1];
			 tempcenter[k][0] = img.at<Vec3b>(maxi[1], maxi[2])[0];
			 tempcenter[k][1] = img.at<Vec3b>(maxi[1], maxi[2])[1];
			 tempcenter[k][2] = img.at<Vec3b>(maxi[1], maxi[2])[2];
			 center = tempcenter;
			 colcenter = tempcolcenter;
			 rowcenter = temprowcenter;
			 rowcenterold = temprowcenterold;
			 colcenterold = tempcolcenterold;
			 k = k + 1;

		 }


	 } while (k != oldk && k < maxcluster+2);
	 /*double *test = new double[3 * k];
	  for (int i = 0; i < k; i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  test[3 * i + j] = center[i][j];
			  cout << test[3 * i + j] << endl;
		  }
	  }*/

	 Mat result(img.rows, img.cols, img.type());
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	 cv::imshow("mhh", result);

 }

 void Meng_Hee_Henggrayscalelocation(int maxcluster,Mat img)
 {
	 if (img.channels() != 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	 }
	 int k = 2;
	 int oldk;
	 RNG rng;
	 int avgcenterdistance = 0;
	 int maxi[3];
	 int *colcenter = new int[k];
	 int *rowcenter = new int[k];
	 int *colcenterold = new int[k];
	 int *rowcenterold = new int[k];
	 int *distance = new int[k];
	 vector<uchar> *cluster = new vector<uchar>[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 uchar *centerold = new uchar[k];
	 uchar *center = new uchar[k];
	 int flag = 0;
	 for (int p = 0; p < k; p++)
	 {
		 colcenter[p] = rand() % img.cols;
		 rowcenter[p] = rand() % img.rows;
	 }
	 for (int p = 0; p < k; p++)
	 {
		 center[p] = img.at<uchar>(rowcenter[p], colcenter[p]);
		 
	 }


	 do {
		 for (int p = 0; p < 3; p++)
		 {
			 maxi[p] = 0;
		 }

		 oldk = k;
		 do {
			 for (int i = 0; i < k; i++)
			 {
				 centerold[i] = center[i];
				
				 colcenterold[i] = colcenter[i];
				 rowcenterold[i] = rowcenter[i];
			 }

			 vector<int> *tempcol = new vector<int>[k];
			 vector<int> *temprow = new vector<int>[k];
			 vector<uchar> *tempcluster = new vector<uchar>[k];
			 delete[]cluster;
			 delete[]col;
			 delete[] row;
			 cluster = tempcluster;
			 col = tempcol;
			 row = temprow;
			 for (int i = 0; i < k; i++)
			 {
				 distance[i] = 0;
			 }

			 for (int i = 0; i < img.rows; i++)
			 {
				 for (int j = 0; j < img.cols; j++)
				 {
					 for (int p = 0; p < k; p++)
					 {
						 

							 distance[p] = pow((img.at<uchar>(i, j) - center[p]), 2) + distance[p];

						 
						 distance[p] = (pow(i - rowcenter[p], 2) + pow(j - colcenter[p], 2) )/100+ distance[p];
						 distance[p] = sqrt(distance[p]);
					 }
					 double min = distance[0];
					 int no = 0;
					 for (int x = 0; x < k; x++)
					 {
						 if (distance[x] < min)
						 {
							 min = distance[x];
							 no = x;
						 }
					 }
					 if (distance[no] > maxi[0])
					 {
						 maxi[0] = distance[no];
						 maxi[1] = i;
						 maxi[2] = j;
					 }
					 cluster[no].push_back(img.at<uchar>(i, j));
					 col[no].push_back(j);
					 row[no].push_back(i);
				 }
			 }
			 for (int i = 0; i < k; i++)
			 {
				 double sum=0;
				 int max = cluster[i].size();
				 for (int j = 0; j < max; j++)
				 {
					 sum = cluster[i][j] + sum;
					 
				 }
				 center[i] = sum / max;
				 
				 int colavg = 0;
				 int rowavg = 0;
				 for (int j = 0; j < max; j++)
				 {
					 colavg = colavg + col[i][j];
					 rowavg = rowavg + row[i][j];
				 }
				 colcenter[i] = colavg / max;
				 rowcenter[i] = rowavg / max;
				 //cout << center[i][0] << " " << center[i][1] << " " << center[i][2] << endl;
				/* double *test = new double[3 * k];
				 for (int i = 0; i < k; i++)
				 {
					 for (int j = 0; j < 3; j++)
					 {
						 test[3 * i + j] = center[i][j];
						 cout << test[3 * i + j] << endl;
					 }
				 }*/
			 }
			 flag = 0;
			 for (int i = 0; i < k; i++)
			 {
				 if (center[i] == centerold[i] && colcenter[i] == colcenterold[i] && rowcenter[i] == rowcenterold[i])
				 {
					 flag++;
				 }
			 }

		 } while (flag != k);
		 int sum = 0;
		 for (int i = 0; i < k; i++)
		 {
			 for (int j = i + 1; j < k; j++)
			 {
				 sum++;
				 avgcenterdistance = sqrt(pow(center[i] - center[j], 2)  + pow(colcenter[i] - colcenter[j], 2) + pow(rowcenter[i] - rowcenter[j], 2)) + avgcenterdistance;
			 }
		 }
		 avgcenterdistance = avgcenterdistance / (2 * sum);
		 if (maxi[0] > avgcenterdistance && k < maxcluster+1)
		 {
			 int *tempdistance = new int[k + 1];
			 delete[]distance;
			 distance = tempdistance;
			 vector<uchar> *tempcluster = new vector<uchar>[k + 1];
			 delete[]cluster;
			 cluster = tempcluster;
			 vector<int> *tempcol = new vector<int>[k + 1];
			 vector<int> *temprow = new vector<int>[k + 1];
			 delete[]col;
			 delete[]row;
			 col = tempcol;
			 row = temprow;
			 uchar *tempcenterold = new uchar[k + 1];
			 delete[]centerold;
			 centerold = tempcenterold;
			 uchar *tempcenter = new uchar[k + 1];
			 int *tempcolcenter = new int[k + 1];
			 int *temprowcenter = new int[k + 1];
			 int *tempcolcenterold = new int[k + 1];
			 int *temprowcenterold = new int[k + 1];
			 for (int i = 0; i < k; i++)
			 {
				 tempcenter[i] = center[i];
				
				 tempcolcenter[i] = colcenter[i];
				 temprowcenter[i] = rowcenter[i];

			 }
			 delete[] center;
			 delete[]colcenter;
			 delete[]rowcenter;
			 delete[]colcenterold;
			 delete[]rowcenterold;
			 tempcolcenter[k] = maxi[2];
			 temprowcenter[k] = maxi[1];
			 tempcenter[k] = img.at<uchar>(maxi[1], maxi[2]);
			
			 center = tempcenter;
			 colcenter = tempcolcenter;
			 rowcenter = temprowcenter;
			 rowcenterold = temprowcenterold;
			 colcenterold = tempcolcenterold;
			 k = k + 1;

		 }


	 } while (k != oldk && k < maxcluster+2);
	 /*double *test = new double[3 * k];
	  for (int i = 0; i < k; i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  test[3 * i + j] = center[i][j];
			  cout << test[3 * i + j] << endl;
		  }
	  }*/

	 Mat result(img.rows, img.cols, img.type());
	 cv::cvtColor(img, result, cv::COLOR_GRAY2BGR);
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	 cv::imshow("mhh", result);

 }

 void Meng_Hee_Henggrayscale(int maxcluster,Mat img)
 {
	 if (img.channels() != 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	 }
	 int k = 2;
	 int oldk;
	 RNG rng;
	 int avgcenterdistance = 0;
	 int maxi[3];
	 int *distance = new int[k];
	 vector<uchar> *cluster = new vector<uchar>[k];
	 vector<int> *col = new vector<int>[k];
	 vector<int> *row = new vector<int>[k];
	 uchar *centerold = new uchar[k];
	 uchar *center = new uchar[k];
	 int flag = 0;
	 for (int p = 0; p < k; p++)
	 {
		 center[p] = rng.operator uchar();
		 
	 }


	 do {
		 for (int p = 0; p < 3; p++)
		 {
			 maxi[p] = 0;
		 }
		 oldk = k;
		 do {
			 for (int i = 0; i < k; i++)
			 {
				 centerold[i] = center[i];
				
			 }
			 vector<int> *tempcol = new vector<int>[k];
			 vector<int> *temprow = new vector<int>[k];
			 vector<uchar> *tempcluster = new vector<uchar>[k];
			 delete[]cluster;
			 delete[]col;
			 delete[] row;
			 cluster = tempcluster;
			 col = tempcol;
			 row = temprow;
			 for (int i = 0; i < k; i++)
			 {
				 distance[i] = 0;
			 }

			 for (int i = 0; i < img.rows; i++)
			 {
				 for (int j = 0; j < img.cols; j++)
				 {
					 for (int p = 0; p < k; p++)
					 {
						 

							 distance[p] = pow((img.at<uchar>(i, j) - center[p]), 2);

						
						 distance[p] = sqrt(distance[p]);

					 }
					 double min = distance[0];
					 int no = 0;
					 for (int x = 0; x < k; x++)
					 {
						 if (distance[x] < min)
						 {
							 min = distance[x];
							 no = x;
						 }
					 }
					 if (distance[no] > maxi[0])
					 {
						 maxi[0] = distance[no];
						 maxi[1] = i;
						 maxi[2] = j;
					 }
					 cluster[no].push_back(img.at<uchar>(i, j));
					 col[no].push_back(j);
					 row[no].push_back(i);
				 }
			 }
			 for (int i = 0; i < k; i++)
			 {
				 double sum=0;
				 int max = cluster[i].size();
				 for (int j = 0; j < max; j++)
				 {
					 sum = cluster[i][j] + sum;
					
				 }
				 center[i] = sum / max;
				
				 //cout << center[i][0] << " " << center[i][1] << " " << center[i][2] << endl;
				/* double *test = new double[3 * k];
				 for (int i = 0; i < k; i++)
				 {
					 for (int j = 0; j < 3; j++)
					 {
						 test[3 * i + j] = center[i][j];
						 cout << test[3 * i + j] << endl;
					 }
				 }*/
			 }
			 flag = 0;
			 for (int i = 0; i < k; i++)
			 {
				 if (center[i] == centerold[i])
				 {
					 flag++;
				 }
			 }

		 } while (flag != k);
		 int sum = 0;
		 for (int i = 0; i < k; i++)
		 {
			 for (int j = i + 1; j < k; j++)
			 {
				 sum++;
				 avgcenterdistance = sqrt(pow(center[i] - center[j], 2) ) + avgcenterdistance;
			 }
		 }
		 avgcenterdistance = avgcenterdistance / (2 * sum);
		 if (maxi[0] > avgcenterdistance && k < maxcluster+1)
		 {
			 int *tempdistance = new int[k + 1];
			 delete[]distance;
			 distance = tempdistance;
			 vector<uchar> *tempcluster = new vector<uchar>[k + 1];
			 delete[]cluster;
			 cluster = tempcluster;
			 vector<int> *tempcol = new vector<int>[k + 1];
			 vector<int> *temprow = new vector<int>[k + 1];
			 delete[]col;
			 delete[]row;
			 col = tempcol;
			 row = temprow;
			 uchar *tempcenterold = new uchar[k + 1];
			 delete[]centerold;
			 centerold = tempcenterold;
			 uchar *tempcenter = new uchar[k + 1];
			 for (int i = 0; i < k; i++)
			 {
				 tempcenter[i] = center[i];
				
			 }
			 delete[] center;
			 tempcenter[k] = img.at<uchar>(maxi[1], maxi[2]);
			
			 center = tempcenter;
			 k = k + 1;

		 }


	 } while (k != oldk && k < maxcluster +2);
	 /*double *test = new double[3 * k];
	  for (int i = 0; i < k; i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  test[3 * i + j] = center[i][j];
			  cout << test[3 * i + j] << endl;
		  }
	  }*/

	 Mat result(img.rows, img.cols, img.type());
	 cv::cvtColor(img, result, cv::COLOR_GRAY2BGR);
	 uchar *r = new uchar[k];
	 uchar *g = new uchar[k];
	 uchar *b = new uchar[k];
	 for (int i = 0; i < k; i++) {
		 r[i] = rng.operator uchar();
		 g[i] = rng.operator uchar();
		 b[i] = rng.operator uchar();
	 }
	 for (int i = 0; i < k; i++)
	 {
		 for (int j = 0; j < cluster[i].size(); j++)
		 {
			 result.at<Vec3b>(row[i][j], col[i][j])[0] = r[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[1] = g[i];
			 result.at<Vec3b>(row[i][j], col[i][j])[2] = b[i];
		 }
	 }
	cv:: imshow("mhh", result);

 }

 Mat lbp(Mat img) 
 {
	 if (img.channels() != 1)
	 {
		 cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	 }
	 Mat result = img;
	 for (int i = 1; i < img.rows-1; i++)
	 {
		 for (int j = 1; j < img.cols-1; j++)
		 {
			 int a, b, c, d, e, f, g, h;
			 if (result.at<uchar>(i - 1, j - 1) > result.at<uchar>(i, j)) { a = 1; }
			 else { a = 0; }
			 if (result.at<uchar>(i , j - 1) > result.at<uchar>(i, j)) { b = 1; }
			 else { b = 0; }
			 if (result.at<uchar>(i + 1, j - 1) > result.at<uchar>(i, j)) { c = 1; }
			 else { c = 0; }
			 if (result.at<uchar>(i + 1, j ) > result.at<uchar>(i, j)) { d = 1; }
			 else { d = 0; }
			 if (result.at<uchar>(i +1, j + 1) > result.at<uchar>(i, j)) { e = 1; }
			 else { e = 0; }
			 if (result.at<uchar>(i , j + 1) > result.at<uchar>(i, j)) { f = 1; }
			 else { f = 0; }
			 if (result.at<uchar>(i - 1, j + 1) > result.at<uchar>(i, j)) { g = 1; }
			 else { g = 0; }
			 if (result.at<uchar>(i - 1, j ) > result.at<uchar>(i, j)) { h = 1; }
			 else { h = 0; }
			 result.at<uchar>(i, j) = pow(a * 2, 7) + pow(b * 2, 6) + pow(c * 2, 5) + pow(d * 2, 4) + pow(e * 2, 3) + pow(f * 2, 2) + pow(g * 2, 1) + pow(h * 2, 0);
		 }
	 }
	 namedWindow("LBP");
	 cv::imshow("LBP", result);
	 return result;
 }

 /*Mat lbpcolor(Mat img)
 {
	 Mat result = img;
	 cvtColor(result, result, cv::COLOR_BGR2GRAY);

	 for (int i = 1; i < img.rows - 1; i++)
	 {
		 for (int j = 1; j < img.cols - 1; j++)
		 {
			 int a, b, c, d, e, f, g, h;
			 if (result.at<uchar>(i - 1, j - 1) > result.at<uchar>(i, j)) { a = 1; }
			 else { a = 0; }
			 if (result.at<uchar>(i-1, j ) > result.at<uchar>(i, j)) { b = 1; }
			 else { b = 0; }
			 if (result.at<uchar>(i , j +1) > result.at<uchar>(i, j)) { c = 1; }
			 else { c = 0; }
			 if (result.at<uchar>(i , j+1) > result.at<uchar>(i, j)) { d = 1; }
			 else { d = 0; }
			 if (result.at<uchar>(i + 1, j + 1) > result.at<uchar>(i, j)) { e = 1; }
			 else { e = 0; }
			 if (result.at<uchar>(i+1, j ) > result.at<uchar>(i, j)) { f = 1; }
			 else { f = 0; }
			 if (result.at<uchar>(i +1, j -1) > result.at<uchar>(i, j)) { g = 1; }
			 else { g = 0; }
			 if (result.at<uchar>(i , j-1) > result.at<uchar>(i, j)) { h = 1; }
			 else { h = 0; }
			 result.at<uchar>(i, j) = pow(a * 2, 7) + pow(b * 2, 6) + pow(c * 2, 5) + pow(d * 2, 4) + pow(e * 2, 3) + pow(f * 2, 2) + pow(g * 2, 1) + pow(h * 2, 0);
		 }
	 }
	 namedWindow("LBP");
	 cv::imshow("LBP", result);
	 return result;
 }*/

 void texture(Mat image) {
	 Mat img;
	 Mat preprocess;
	 if (image.channels() != 1)
	 {
		 cv::cvtColor(image, img, cv::COLOR_BGR2GRAY);
	 }
	 else { img = image; }
	 preprocess = img;
	// medianBlur(preprocess, preprocess, 7);
	// imshow("blur", preprocess);
	 Mat result = Mat::zeros(img.size(), img.type());
	 for (int i = 8; i < img.rows - 8; i++)
	 {
		 for (int j = 8; j < img.cols - 8; j++)
		 {
			 double avgpix = 0;
			 for (int p = -8; p < 8; p++)
			 {
				 for (int q = -8; q < 8; q++)
				 {
					 avgpix = avgpix + preprocess.at<uchar>(i + p, j + q);
				 }
			 }
			 avgpix = avgpix / 225;
			 /*double avgpix = (preprocess.at<uchar>(i - 1, j - 1) + preprocess.at<uchar>(i, j - 1) + preprocess.at<uchar>(i + 1, j - 1) +
				 preprocess.at<uchar>(i - 1, j) + preprocess.at<uchar>(i, j) + preprocess.at<uchar>(i + 1, j) +
				 preprocess.at<uchar>(i - 1, j + 1) + preprocess.at<uchar>(i, j +1) +preprocess.at<uchar>(i + 1, j + 1) ) / 9;*/
			 result.at<uchar>(i, j) = avgpix - preprocess.at<uchar>(i, j);
		 }
	 }
	 cv::imshow("prop", result);
	 int L[5] = { 1,4,6,4,1 };
	 int E[5] = { -1,-2,0,2,1 };
	 int S[5] = { -1,0,2,0,-1 };
	 int R[5] = { 1,-4,6,-4,1 };
	 int LE[5][5];
	 int LS[5][5];
	 int LR[5][5];
	 int EE[5][5];
	 int ES[5][5];
	 int ER[5][5];
	 int SS[5][5];
	 int SR[5][5];
	 int RR[5][5];
	 /*int sumLE = 0;
	 int sumLS = 0;
	 int sumLR = 0;
	 int sumEE = 0;
	 int sumES = 0;
	 int sumER = 0;
	 int sumSS = 0;
	 int sumSR = 0;
	 int sumRR = 0;*/

	 for (int i = 0; i < 5; i++)
	 {
		 for (int j = 0; j < 5; j++)
		 {
			 LE[i][j] = L[i] * E[j];
			 LS[i][j] = L[i] * S[j];
			 LR[i][j] = L[i] * R[j];
			 EE[i][j] = E[i] * E[j];
			 ES[i][j] = E[i] * S[j];
			 ER[i][j] = E[i] * R[j];
			 SS[i][j] = S[i] * S[j];
			 SR[i][j] = S[i] * R[j];
			 RR[i][j] = R[i] * R[j];

		 }
	 }
	 /*for (int i = 0; i < 5; i++)
	 {
		 for (int j = 0; j < 5; j++)
		 {
			 sumLE = sumLE + LE[i][j];
			 sumLS = sumLS + LS[i][j];
			 sumLR = sumLR + LR[i][j];
			 sumEE = sumEE + EE[i][j];
			 sumES = sumES + ES[i][j];
			 sumER = sumER + ER[i][j];
			 sumSS = sumSS + SS[i][j];
			 sumSR = sumSR + SR[i][j];
			 sumRR = sumRR + RR[i][j];
		 }
	 }*/
	 Mat L5E5 = Mat::zeros(img.size(), img.type());
	 Mat L5S5 = Mat::zeros(img.size(), img.type());
	 Mat L5R5 = Mat::zeros(img.size(), img.type());
	 Mat E5E5 = Mat::zeros(img.size(), img.type());
	 Mat E5S5 = Mat::zeros(img.size(), img.type());
	 Mat E5R5 = Mat::zeros(img.size(), img.type());
	 Mat S5S5 = Mat::zeros(img.size(), img.type());
	 Mat S5R5 = Mat::zeros(img.size(), img.type());
	 Mat R5R5 = Mat::zeros(img.size(), img.type());

	 /*Mat L5E5(img.rows, img.cols, img.type());
	 Mat L5S5(img.rows, img.cols, img.type());
	 Mat L5R5(img.rows, img.cols, img.type());
	 Mat E5E5(img.rows, img.cols, img.type());
	 Mat E5S5(img.rows, img.cols, img.type());
	 Mat E5R5(img.rows, img.cols, img.type());
	 Mat S5S5(img.rows, img.cols, img.type());
	 Mat S5R5(img.rows, img.cols, img.type());
	 Mat R5R5(img.rows, img.cols, img.type());*/
	 for (int i = 2; i < img.rows - 2; i++)
	 {
		 for (int j = 2; j < img.cols - 2; j++)
		 {
			 double LEpixel = 0;
			 double LSpixel = 0;
			 double LRpixel = 0;
			 double EEpixel = 0;
			 double ESpixel = 0;
			 double ERpixel = 0;
			 double SSpixel = 0;
			 double SRpixel = 0;
			 double RRpixel = 0;
			 int pixelvalue[5][5];
			 for (int k = 0; k < 5; k++)
			 {
				 for (int l = 0; l < 5; l++)
				 {
					 pixelvalue[k][l] = result.at<uchar>(i + k - 2, j + l - 2);
				 }
			 }
			 for (int k = 0; k < 5; k++)
			 {
				 for (int l = 0; l < 5; l++)
				 {
					 LEpixel = LEpixel + (LE[k][l] * pixelvalue[k][l]);
					 LSpixel = LSpixel + (LS[k][l] * pixelvalue[k][l]);
					 LRpixel = LRpixel + (LR[k][l] * pixelvalue[k][l]);
					 EEpixel = EEpixel + (EE[k][l] * pixelvalue[k][l]);
					 ESpixel = ESpixel + (ES[k][l] * pixelvalue[k][l]);
					 ERpixel = ERpixel + (ER[k][l] * pixelvalue[k][l]);
					 SSpixel = SSpixel + (SS[k][l] * pixelvalue[k][l]);
					 SRpixel = SRpixel + (SR[k][l] * pixelvalue[k][l]);
					 RRpixel = RRpixel + (RR[k][l] * pixelvalue[k][l]);
				 }
			 }
			 L5E5.ptr<uchar>(i)[j] = LEpixel;
			 L5S5.ptr<uchar>(i)[j] = LSpixel;
			 L5R5.ptr<uchar>(i)[j] = LRpixel;
			 E5E5.ptr<uchar>(i)[j] = EEpixel;
			 E5S5.ptr<uchar>(i)[j] = ESpixel;
			 E5R5.ptr<uchar>(i)[j] = ERpixel;
			 S5S5.ptr<uchar>(i)[j] = SSpixel;
			 S5R5.ptr<uchar>(i)[j] = SRpixel;
			 R5R5.ptr<uchar>(i)[j] = RRpixel;
		 }
	 }
	 //Meng_Hee_Henggrayscale(img,5);
	/*Mat combine = Mat::zeros(img.size(), img.type());

	 for (int i = 0; i < img.rows; i++)
	 {
		 for (int j = 0; j < img.cols; j++)
		 {
			 double combinepixel = (L5E5.ptr<uchar>(i)[j] + L5S5.ptr<uchar>(i)[j] + L5R5.ptr<uchar>(i)[j] + E5E5.ptr<uchar>(i)[j] + E5S5.ptr<uchar>(i)[j]
				 + E5R5.ptr<uchar>(i)[j] + S5S5.ptr<uchar>(i)[j] + S5R5.ptr<uchar>(i)[j] + R5R5.ptr<uchar>(i)[j]) / 9;
			 combine.ptr<uchar>(i)[j] = combinepixel;
		 }
	 }
	 cv::imshow("combine", combine);*/
	 cv::imshow("L5E5", L5E5);
	 cv::imshow("L5S5", L5S5);
	 cv::imshow("L5R5", L5R5);
	 cv::imshow("E5E5", E5E5);
	 cv::imshow("E5S5", E5S5);
	 cv::imshow("E5R5", E5R5);
	 cv::imshow("S5S5", S5S5);
	 cv::imshow("S5R5", S5R5);
	 cv::imshow("R5R5", R5R5);
 }

 void ShowHelpText()
 {
	 //output some informations 
	 printf("\n----------------------------------------------------------------------------\n");
	 printf("Welcome to use this program\n");
	 printf("This is a program is used for image segmentation\n");
	 printf("first you need to input the location of the image location \n");
	 printf("second you need choose the method for image segmentation\n");
	 printf("We provide basic Kmeans image segmentation and Meng_Hee_Heng's variant \n");
	 printf("Also you can choose location, grayscale, color, and texture as feature to process the image \n");
	 printf("About texture, this program can use LBP method and Law's texture method, but the result is not good if you choose law's texture method\n");

	 printf("\t\t \n");
	 printf("Opencv version is:" CV_VERSION);
	 printf("\n\t\t\t\t made by: Yukuan Hao, Liming Yang,Liang Gu, and Rouwen Mao");
	 printf("\n----------------------------------------------------------------------------\n");
 }
 void ShowHelpText1(Mat &img)
 {
	 string inputnumber;
	 printf("Please choose a method\n");
	 printf(" 1.basic kmeans with grayscale\n 2.basic kmeans with color\n 3.basic kmeans with grayscale and location\n 4.basic kmeans with color and location\n 5.basic kmeans with texture and location \n 6.basic kmeans with texture and grayscale\n");
	 printf(" 7.basic kmeans with texture and color\n 8.Meng_Hee_Heng's variant with  texture and color\n");
	 printf(" 9.Meng_Hee_Heng's variant with grayscale\n 10.Meng_Hee_Heng's variant with color\n 11.Meng_Hee_Heng's variant with grayscale and location\n 12.Meng_Hee_Heng's variant with color and location\n 13.Meng_Hee_Heng's variant with texture and location \n 14.Meng_Hee_Heng's variant with texture and grayscale\n");
	 printf(" 15.extract texture with Law's method\n");
	 cin >> inputnumber;
	 if (inputnumber == "1") 
	 {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeansgrayscale(k,img); 
	 }
	 else if (inputnumber == "2") {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeanscolor(k, img);
	 }
	 else if (inputnumber == "3") {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeanslocationgrayscale(k, img);
	 }
	 else if (inputnumber == "4") {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeanslocationcolor(k, img);
	 }
	 else if (inputnumber == "5") {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeanslocationcolor(k, lbp(img));
	 }
	 else if (inputnumber == "6") {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeansgrayscale(k, lbp(img));
	 }
	 else if (inputnumber == "7") {
		 int k;
		 printf("how many cluster do you want to create?\n");
		 cin >> k;
		 kmeanscolor(k, lbp(img));
	 }
	 else if (inputnumber == "8") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Hengcolor(k, lbp(img));
	 }
	 else if (inputnumber == "9") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Henggrayscale(k, img);
	 }
	 else if (inputnumber == "10") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Hengcolor(k, img);
	 }
	 else if (inputnumber == "11") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Henggrayscalelocation(k, img);
	 }
	 else if (inputnumber == "12") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Hengcolorlocation(k, img);
	 }
	 else if (inputnumber == "13") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Henggrayscale(k, lbp(img));
	 }
	 else if (inputnumber == "14") {
		 int k;
		 printf("please set a maximum number for cluster\n");
		 cin >> k;
		 Meng_Hee_Henggrayscale(k, lbp(img));
	 }
	 else if (inputnumber == "15") { texture(img); }
	 else {
		 printf("Please input a correct number\n");
		 ShowHelpText1(img);
	 }
 }
 //use to check whether the image is loaded
 void checkimage (Mat &img)
 {
	 //if user do not input the correct location give user chances to input the location again
	 if (!img.data)
	 {
		 input.clear();
		 printf("Can not find the image,please input the correct location of the image\n");
		 cin >> input;
		 inputimage = imread(input, -1);
		 checkimage(img);
	 }
 }

int main()
{
	//show the information about this program
	ShowHelpText();//go showhelptext function
	printf("Please add the location of the image\n");
	printf("Spaces are not allowed in the path\n");
	cin >> input;//wait user to input the location of image
	inputimage = imread(input, -1);//load image
	checkimage(inputimage);
	cv::imshow("Input image", inputimage);
	waitKey(1);
	ShowHelpText1(inputimage);
	//Mat img = imread("F:\\text.png", -1);
	//Mat img = imread("F:\\Master\\cs563\\Final Project\\Kmeans\\Test images\\star.ppm",-1);
	//cv::imshow("MM Viewer", img);
	//Vec3b *a=new Vec3b[3];
	//a = kmeanslocationcolor(5, img);
	//Meng_Hee_Henggrayscalelocation(img);
	//Meng_Hee_Henggrayscale(img,5);
	//texture(img);
	//lbp(img);
	//Meng_Hee_Henggrayscale(img);
	//*a = *searchimggrayscale(3,lbpcolor(img));
	//*a = *locationgrayscale(3,img);
	
	/*double b[15];
	for (int i = 0; i < 5; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			b[i * 3 + j] = a[i][j];
			cout << b[i * 3 + j] << endl;
		}
	
	}*/
	waitKey(0);
}
