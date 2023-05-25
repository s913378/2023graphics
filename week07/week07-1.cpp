#include <opencv/highgui.h>
int main()
{
    IplImage*img=cvLoadImage("a.jpg");
    cvShowImage("week07",img);
    cvWaitKey(0);
}
