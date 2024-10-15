#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    cv::Mat output;
    output.create(new_rows,new_cols,input.type());
    for (int y = 0; y < new_rows; ++y) {
        for (int x = 0; x < new_cols; ++x) {
            float xCoord = (x * input.cols) / new_cols;
            float yCoord = (y * input.rows) / new_rows;

            int x0 = static_cast<int>(std::floor(xCoord));
            int y0 = static_cast<int>(std::floor(yCoord));
            int x1 = std::min(x0 + 1, input.cols - 1);
            int y1 = std::min(y0 + 1, input.rows - 1);

            // 计算权重
            float dx = xCoord - x0;
            float dy = yCoord - y0;

            // 双线性插值
            for (int c = 0; c < input.channels(); ++c) {
                float val = 0;
                val += (1 - dx) * (1 - dy) * input.at<cv::Vec3b>(y0, x0)[c];
                val += dx * (1 - dy) * input.at<cv::Vec3b>(y0, x1)[c];
                val += (1 - dx) * dy * input.at<cv::Vec3b>(y1, x0)[c];
                val += dx * dy * input.at<cv::Vec3b>(y1, x1)[c];

                output.at<cv::Vec3b>(y, x)[c] = static_cast<uchar>(val);
            }
        }
    }
    return output;
}