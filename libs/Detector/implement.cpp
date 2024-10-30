#include "detector.hpp"


namespace Detector {

    YOLODetector::YOLODetector(const string& configPath, 
                            const string& weightsPath, 
                            const string& classesPath)
                            : minConfidenceScore(0.5), nmsThreshold(0.4)
    {   
        // load model
        net = readNetFromDarknet(configPath, weightsPath);

        if (net.empty()) {
            cerr << "Failed to load network!" << endl;
            throw runtime_error("Failed to load network");
        }

        // Load class names from file
        ifstream ifs(classesPath.c_str());
        string line;
        while (getline(ifs, line)) {
            classNames.push_back(line);
        }

        // net.setPreferableBackend(DNN_BACKEND_OPENCV);
    }

    void YOLODetector::drawPred(int classId, 
                                float conf, 
                                int left, 
                                int top, 
                                int right, 
                                int bottom, 
                                Mat& frame)
    {   
        
        rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);

        string label = format("%.2f", conf);
        if (!classNames.empty() && classId < (int)classNames.size()) {
            label = classNames[classId] + ":" + label;
        }

        int baseLine;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        top = max(top, labelSize.height);
        rectangle(frame, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
        putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
    }

    void YOLODetector::postprocess(Mat& image, const vector<Mat>& output)
    {
        int personClassId = 0;
        vector<int> classIds;
        vector<float> confidences;
        vector<Rect> boxes;

        for (size_t i = 0; i < output.size(); ++i) {
            float* data = (float*)output[i].data;

            for (int j = 0; j < output[i].rows; ++j, data += output[i].cols) {
                Mat scores = output[i].row(j).colRange(5, output[i].cols);
                Point classIdPoint;
                double confidence;

                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                if (confidence > minConfidenceScore && classIdPoint.x == personClassId) {
                    int centerX = (int)(data[0] * image.cols);
                    int centerY = (int)(data[1] * image.rows);
                    int width = (int)(data[2] * image.cols);
                    int height = (int)(data[3] * image.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    classIds.push_back(classIdPoint.x);
                    confidences.push_back((float)confidence);
                    boxes.push_back(Rect(left, top, width, height));
                }
            }
        }

        vector<int> indices;
        NMSBoxes(boxes, confidences, minConfidenceScore, nmsThreshold, indices);
        for (size_t i = 0; i < indices.size(); ++i) {
            int idx = indices[i];
            Rect box = boxes[idx];
            drawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, image);
        }
    }

    void YOLODetector::videoStream()
    {
        vector<string> outputLayerNames = net.getUnconnectedOutLayersNames();

        VideoCapture cap(0);
        if (!cap.isOpened()) {
            cerr << "Error opening video stream or file" << endl;
            return;
        }

        while (cap.isOpened()) {
            Mat image;
            bool isSuccess = cap.read(image);
            if (!isSuccess) {
                cerr << "Failed to load frame!" << endl;
                break;
            }

            Mat blob = blobFromImage(image, 1 / 255.0, Size(416, 416), Scalar(0, 0, 0), true, false);
            net.setInput(blob);

            vector<Mat> output;
            net.forward(output, outputLayerNames);

            postprocess(image, output);
            imshow("YOLO Detection", image);

            int k = waitKey(10);
            if (k == 113) { // Press 'q' to exit
                break;
            }
        }

        cap.release();
        destroyAllWindows();
    }

}  // namespace Detector