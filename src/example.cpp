#include "example.h"


ExampleClass::ExampleClass()
{
  std::cout << "class instantiated" << std::endl;

  // initialize windows
  cv::namedWindow("frame", CV_WINDOW_AUTOSIZE);
  cv::moveWindow("frame", 50, 50);

  // open video here
  video_path_ = "../videos/sample.mp4";
  cv::VideoCapture source_(video_path_);

  if (!source_.isOpened())
    std::cout << "invalid video file path" << std::endl;

  source_ >> frame_;
  if(frame_.empty())
  {
    std::cout << "frame is bad" << std::endl;
    return;
  }

  // hard-coded location of object in first frame
  uint32_t col = 160;
  uint32_t row = 160;
  uint32_t w   = 40;
  uint32_t h   = 60;
  cv::Mat roi_ = frame_(cv::Rect(col, row, w, h)).clone();
  cv::imshow("roi", roi_);

  // draw rectangle
  cv::rectangle(frame_, cv::Point(col,row), cv::Point(col+w, row+h), cv::Scalar(255, 0, 0), 2);
  cv::imshow("frame", frame_);

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

  // close the video source for scoping reasons
  source_.release();
}


void ExampleClass::operations()
{
  // perform operations
  std::cout << "starting operations; press esc to end early" << std::endl;

  // reopen the video source and resume at frame 2
  source_.open(video_path_);
  source_.set(CV_CAP_PROP_POS_FRAMES, 1);
  if (!source_.isOpened())
    std::cout << "invalid video file path" << std::endl;

  while (true)
  {
    // plot the results of the last iteration and wait for keypress
    auto key = cv::waitKey();
    if ((int)key==27)
      return;

    // get the next frame
    source_ >> frame_;
    if (frame_.empty())
      return;

    // hsv the frame

    // back project the frame with the roi_hist_ that is remembered

    // apply mean-shift

    // use the resulting window to draw the new rectangle
    // NOTE: this operates on the entire window, use the current estimate
    // to select a subwindow, decreasing the amount of backprop required?

    // draw the resulting rectangle

    cv::imshow("frame", frame_); // TEMP
  }
}