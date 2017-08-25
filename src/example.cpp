#include "example.h"


ExampleClass::ExampleClass()
{
  std::cout << "class instantiated" << std::endl;

  // open video here
  std::string video_path_ = "../videos/sample.mp4";
  cv::VideoCapture source(video_path_);

  if (!source.isOpened())
    std::cout << "invalid video file path" << std::endl;

  source >> frame_;
  if(frame_.empty())
  {
    std::cout << "frame is bad" << std::endl;
    return;
  }
  cv::imshow("frame", frame_);

  // hard-coded location of object in first frame
  uint32_t col = 160;
  uint32_t row = 160;
  uint32_t w   = 40;
  uint32_t h   = 60;
  cv::Mat roi_ = frame_(cv::Rect(col, row, w, h));
  cv::imshow("roi", roi_);

  // convert roi to HSV
  cv::cvtColor(roi_, roi_hsv_, cv::COLOR_BGR2HSV);
  cv::imshow("roi_hsv", roi_hsv_);

  // generate the mask used when finding the histogram
  cv::inRange(roi_hsv_, cv::Scalar(0,0,0), cv::Scalar(255,255,255), mask_);
  cv::imshow("roi_mask", mask_);

  // histogram using hue channel only (as seen in examples)
  int n_images = 1; // one image only
  int channels = 0; // use the first channel (hue)
  int dims = 1; // histogram dimensionality
  int hist_size = 16; // histogram size (bins) 180 was used by another example
  float hue_ranges[] = {0, 180}; // hue varies from 0 to 179, see cvtColor
  const float* ranges = hue_ranges; // make const pointer
  cv::calcHist(&roi_hsv_, n_images, &channels, mask_, roi_hist_, dims, &hist_size, &ranges);

  // normalize
  cv::normalize(roi_hist_, roi_hist_, 0, 255, cv::NORM_MINMAX);

  // termination criteria for the mean-shift operation
  mean_shift_term_ = cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 10, 1);


  cv::waitKey();
}


void ExampleClass::operations()
{
  // perform operation on uMat class member
  std::cout << "starting operations" << std::endl;

  // while (true) {
  //   // get the next frame; loop if the end of the video is reached
  //   source >> frame_;
  //   if(frame_.empty())
  //   {
  //     std::cout << "looping video" << std::endl;
  //     source.release();
  //     source.open(video_path_);
  //     source >> frame_; // TODO: remove endless loop
  //   }
  // }


}