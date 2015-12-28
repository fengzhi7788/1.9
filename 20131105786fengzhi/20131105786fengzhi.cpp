#include "stdafx.h" 
#include <cstdio>  
#include <cstdlib>  
#include <Windows.h>  
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	
	const char *pstrImageName ="qqq.jpg";
	//IplImage *pSrcImage =cvLoadImage(pstrImageName,0);
	IplImage *img = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_COLOR);
	//Mat picture(pSrcImage);
	if(!img)
	{
		printf("can't load ");
		return -1;
	}
	const char *pstrCascadeFileName ="haarcascade_frontalface_alt.xml";
	const char *pstrCascadeproface="haarcascade_profileface.xml";
	if(!pstrCascadeFileName)
	{
		printf("error");
		return -1;
	}
	if(!pstrCascadeproface)
	{
		printf("error");
		return -1;
	}
	CvHaarClassifierCascade *pHaarCascade = NULL;
	CvHaarClassifierCascade *pHaarCascadepro=NULL;
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);
	pHaarCascadepro = (CvHaarClassifierCascade*)cvLoad(pstrCascadeproface);
	if (pHaarCascade != NULL)
	{		
		DWORD dwTimeBegin, dwTimeEnd;  
		dwTimeBegin = GetTickCount(); 
		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(img, pHaarCascade, pcvMStorage);
		dwTimeEnd = GetTickCount();
		printf("人脸个数: %d   识别用时: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);  
		for(int i = 0; i <pcvSeqFaces->total; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);	
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width * 0.5));
			center.y = cvRound((r->y + r->height * 0.5));
			radius = cvRound((r->width + r->height) * 0.25);
			printf("Found a face at (%d, %d)\n", center.x, center.y);
			cvCircle(img,center,radius, cvScalar(255,255,255));
			//ellipse(picture, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255),5, 2, 0);

			CvMemStorage* storage = 0;
			storage = cvCreateMemStorage(0) ;
			CvHaarClassifierCascade* cascade_e = 0;
			/*const char* cascade_name2 = "haarcascade_eye.xml";
			cascade_e = (CvHaarClassifierCascade*)cvLoad( cascade_name2, 0, 0, 0 );
			assert(cascade_e != NULL);
			//storage = cvCreateMemStorage(0) ;
			CvSeq *eyes = cvHaarDetectObjects(img,cascade_e,storage,1.01, 3, CV_HAAR_DO_CANNY_PRUNING,cvSize(20,20));
			//cout<<eyes->total<<endl;
			for(int i = 0; i < (eyes ? eyes->total : 0); i++ ) 
			{

				CvRect *eye = (CvRect*)cvGetSeqElem(eyes, i);
				//cvRectangle(img, cvPoint(eye->x, eye->y),cvPoint(eye->x + eye->width, eye->y + eye->height),CV_RGB(255, 0, 0),1, 8, 0);
				//cvRectangle(img, cvPoint(eye->x, eye->y),cvPoint(eye->x + eye->width, eye->y + eye->height),CV_RGB(255, 0, 0),1, 8, 0);
				cvCircle(img,cvPoint(eye->x, eye->y),20, cvScalar(0,255,0), 1);
			}*/
		}
	}
	cvNamedWindow("face detection", CV_WINDOW_AUTOSIZE);
	cvShowImage("face detection", img);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&img);	
}