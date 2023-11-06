#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "/home/mp4d/ros2_assignment2/src/processor/include/processor/xinverter.h"

class ImageProcessorNode : public rclcpp::Node {
public:
    ImageProcessorNode() : Node("processor_node") {
        subscriber_ = create_subscription<sensor_msgs::msg::Image>(
            "image_raw", 1, std::bind(&ImageProcessorNode::imageCallback, this, std::placeholders::_1));
        publisher_ = create_publisher<sensor_msgs::msg::Image>("processed_image", 1);


        // Setting my inverter up
        XInverter_Initialize(&xinverter, "inverter");

    }

    

    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        // Convert the ROS image message to an OpenCV image
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception& e) {
            RCLCPP_ERROR(get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        // Process the image (e.g., perform some OpenCV operations)
        cv::Mat processed_image;
        cv::cvtColor(cv_ptr->image, processed_image, cv::COLOR_BGR2GRAY);
        cv::resize(processed_image, processed_image, cv::Size(32,32));

        // Create an array to hold the pixel values
        char pixelArray[1024]; // 32x32 = 1024
        char out[1024];

        // Copy the pixel values from the image to the array
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < 32; j++) {
                pixelArray[i * 32 + j] = processed_image.at<char>(i, j);
            }
        }

        // Send the image to the FPGA for processing
        
        XInverter_Write_in_r_Bytes(&xinverter,0,pixelArray,1024);
        XInverter_Start(&xinverter);

        while(!XInverter_IsDone(&xinverter));

        XInverter_Read_in_r_Bytes(&xinverter,0,out,1024);


        // And then receive it back as an array


        // Reassemble the now inverted 32x32 grayscale image

        // Copy the pixel values from the array to the image
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < 32; j++) {
                processed_image.at<uint8_t>(i, j) = out[i * 32 + j];
            }
        }

        // Convert the processed image back to a ROS image message with cv_bridge
        msg_ = cv_bridge::CvImage(std_msgs::msg::Header(), "mono8", processed_image).toImageMsg();

        // Publish the processed image
        publisher_->publish(*msg_.get());
    }

private:
    sensor_msgs::msg::Image::SharedPtr msg_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    static XInverter xinverter;
};

XInverter ImageProcessorNode::xinverter;

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImageProcessorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
