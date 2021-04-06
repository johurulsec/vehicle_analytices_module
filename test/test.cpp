#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("rtsp://admin:00125680Dahua@192.168.0.111/cam/realmonitor?channel=1&subtype=0");
	while(1)
	{
		Mat mat;
		cout<<"reading mat\n";
		cap>>mat;
		cout<<"mat read\n";
		if(!mat.data)
		{
			break;
		}

		imshow("test",mat);
		waitKey(10);
	}
}
