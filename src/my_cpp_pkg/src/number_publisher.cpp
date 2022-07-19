#include "example_interfaces/msg/int64.hpp"
#include "rclcpp/rclcpp.hpp"

class NumberPublisherNode : public rclcpp::Node {
public:
    NumberPublisherNode() : Node("number_publisher_node") {
        counter_ = 0;
        number_publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&NumberPublisherNode::callbackNumberPublisher, this));
    };

private:
    int counter_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr number_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    void callbackNumberPublisher() {
        counter_ += 1;
        auto msg = example_interfaces::msg::Int64();
        msg.data = counter_;
        number_publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "published %d", counter_);
    };
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
};