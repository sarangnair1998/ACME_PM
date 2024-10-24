#include "detector.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <fstream>
#include <iostream>

namespace Detector {
    ObjectDetector::ObjectDetector(
        const std::string& model_path,
        const std::string& config_path,
        const std::string& labels_path,
        float confidence_threshold
    )
        : model_path_(model_path)
        , config_path_(config_path)
        , labels_path_(labels_path)
        , min_confidence_score_(confidence_threshold)
    {
    }

    ObjectDetector::~ObjectDetector() {
        cv::destroyAllWindows();
    }

    bool ObjectDetector::loadClassNames() {
        std::ifstream ifs(labels_path_.c_str());
        std::string line;
        
        while(std::getline(ifs, line)) {
            std::cout << line << std::endl;
            class_names_.push_back(line);
        }
        
        return !class_names_.empty();
    }

    bool ObjectDetector::loadNetwork() {
        try {
            net_ = cv::dnn::readNet(model_path_, config_path_);
            return !net_.empty();
        } catch (const cv::Exception& e) {
            std::cerr << "Error loading network: " << e.what() << std::endl;
            return false;
        }
    }

    bool ObjectDetector::initialize() {
        if (!loadClassNames()) {
            std::cerr << "Failed to load class names" << std::endl;
            return false;
        }
        
        if (!loadNetwork()) {
            std::cerr << "Failed to load network" << std::endl;
            return false;
        }
        
        return true;
    }

    cv::Mat ObjectDetector::preprocess(const cv::Mat& frame) {
        return cv::dnn::blobFromImage(
            frame,
            1/255.0,
            cv::Size(416,416),
            cv::Scalar(0,0,0), 
            true, 
            false
        );
    }

    void ObjectDetector::drawPredictions(cv::Mat& frame, const cv::Mat& results) {
        for (int i = 0; i < results.rows; i++) {
            int class_id = int(results.at<float>(i,1));
            float confidence = results.at<float>(i,2);

            if (confidence > min_confidence_score_) {
                int bboxX = int(results.at<float>(i,3) * frame.cols);
                int bboxY = int(results.at<float>(i,4) * frame.rows);
                int bboxWidth = int(results.at<float>(i,5) * frame.cols - bboxX);
                int bboxHeight = int(results.at<float>(i,6) * frame.rows - bboxY);

                cv::rectangle(
                    frame, 
                    cv::Point(bboxX,bboxY), 
                    cv::Point(bboxX + bboxWidth, bboxY + bboxHeight), 
                    cv::Scalar(0,0,255),
                    2
                );
                
                std::string class_name = class_names_[class_id-1];
                cv::putText(
                    frame, 
                    class_name + " " + std::to_string(int(confidence*100)) + "%", 
                    cv::Point(bboxX,bboxY-10), 
                    cv::FONT_HERSHEY_SIMPLEX, 
                    1.5, 
                    cv::Scalar(0,255,0),
                    2
                );
            }
        }
    }

    void ObjectDetector::processFrame(cv::Mat& frame) {
        auto start = cv::getTickCount();
        
        cv::Mat blob = preprocess(frame);
        net_.setInput(blob);
        cv::Mat output = net_.forward();
        
        cv::Mat results(output.size[2], output.size[3], CV_32F, output.ptr<float>());
        drawPredictions(frame, results);
        
        auto end = cv::getTickCount();
        auto totalTime = (end - start)/cv::getTickFrequency();
        
        cv::putText(
            frame, 
            "FPS: " + std::to_string(int(1/totalTime)), 
            cv::Point(50,50),
            cv::FONT_HERSHEY_DUPLEX, 
            1,
            cv::Scalar(0,255,0), 
            2, 
            false
        );
    }

    void ObjectDetector::start() {
        cv::VideoCapture cap(0);
        
        if (!cap.isOpened()) {
            std::cerr << "Failed to open camera!" << std::endl;
            return;
        }
        
        while(cap.isOpened()) {
            cv::Mat frame;
            bool isSuccess = cap.read(frame);
            
            if(!isSuccess) {
                std::cerr << "Could not load the image!" << std::endl;
                break;
            }

            processFrame(frame);
            cv::imshow("Object Detection", frame);

            int key = cv::waitKey(10);
            if (key == 'q') {
                break;
            }
        }
        
        cap.release();
    }
}  // namespace Detector