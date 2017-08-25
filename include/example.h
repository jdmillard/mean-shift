#include <iostream>
#include <math.h>
#include <chrono>
#include <opencv2/opencv.hpp>
// not sure if these two are needed:
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"


class ExampleClass
{
public:
  ExampleClass();
  void operations();

private:
  std::string video_path_;
  cv::VideoCapture source_;

  cv::Mat frame_;
  cv::Mat roi_;
  cv::Mat roi_hsv_;
  cv::Mat mask_;
  cv::Mat roi_hist_; // the only cv::Mat required to be a member

  cv::TermCriteria mean_shift_term_;

};