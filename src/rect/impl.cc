#include "impls.h"
/*#include "utils.h"*/

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    std::vector<std::vector<cv::Point>> aim;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat input_gray;
    cv::cvtColor(input,input_gray,cv::COLOR_BGR2GRAY);
    cv::Mat input_cp;
    cv::threshold(input_gray,input_cp,100,255,cv::THRESH_BINARY);
    cv::findContours(input_cp,aim,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE);
    /*cv::Mat aim1 = show_contours(aim, input.rows, input.cols);
    cv::imshow("<test_find_contours> 正确的答案", aim1);*/
    res.first=cv::boundingRect(aim[0]);
    res.second=cv::minAreaRect(aim[0]);
    return res;
}