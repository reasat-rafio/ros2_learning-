#include "example_interfaces/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"

class RobotNewsStationNode : public rclcpp::Node {
public:
    RobotNewsStationNode() : Node("robot_news_station"), robot_name_("zimaBlue") {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&RobotNewsStationNode::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "Robot news station started");
    }

private:
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::string robot_name_;

    void publishNews() {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi this is ") + robot_name_;
        publisher_->publish(msg);
    };
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
};