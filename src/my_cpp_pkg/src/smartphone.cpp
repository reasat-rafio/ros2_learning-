#include "example_interfaces/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"

class SmartphoneNode : public rclcpp::Node {
public:
    SmartphoneNode() : Node("smartphone") {
        subscriber__ = this->create_subscription<example_interfaces::msg::String>(
            "robot_news", 10, std::bind(&SmartphoneNode::subscribeCallback, this, std::placeholders::_1));
    }

private:
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber__;

    void subscribeCallback(const example_interfaces::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartphoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}