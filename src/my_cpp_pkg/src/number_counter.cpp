#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"
#include "rclcpp/rclcpp.hpp"

class NumberCounterNode : public rclcpp::Node {
public:
    NumberCounterNode() : Node("number_counter_node") {
        number_subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(
                &NumberCounterNode::callbackNumberSubscriber,
                this,
                std::placeholders::_1));

        number_publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_counter", 10);

        number_service_ = this->create_service<example_interfaces::srv::SetBool>(
            "reset_counter",
            std::bind(
                &NumberCounterNode::callbackNumberService,
                this,
                std::placeholders::_1,
                std::placeholders::_2));
    };

private:
    int counter_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr number_subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr number_publisher_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr number_service_;

    void callbackNumberSubscriber(const example_interfaces::msg::Int64::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "subscriber recived = %ld", msg->data);
        counter_ += msg->data;
        auto new_msg = example_interfaces::msg::Int64();
        new_msg.data = counter_;
        number_publisher_->publish(new_msg);
    };

    void callbackNumberService(
        const example_interfaces::srv::SetBool::Request::SharedPtr req,
        const example_interfaces::srv::SetBool::Response::SharedPtr res) {
        if (req->data) {
            counter_ = 0;
            res->success = true;
            res->message = "counter set to 0";
        } else {
            res->success = false;
            res->message = "failed";
        }
    };
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
};