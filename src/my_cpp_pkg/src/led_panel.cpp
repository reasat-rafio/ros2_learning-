#include "my_robot_interfaces/msg/led_status.hpp"
#include "my_robot_interfaces/srv/battery_status.hpp"
#include "rclcpp/rclcpp.hpp"

class LEDPanelNode : public rclcpp::Node {
public:
    LEDPanelNode() : Node("led_panel_node") {
        ledService_ = this->create_service<my_robot_interfaces::srv::BatteryStatus>(
            "set_led",
            std::bind(
                &LEDPanelNode::callBackLedledService, this,
                std::placeholders::_1, std::placeholders::_2));

        ledStatePublisher_ = this->create_publisher<my_robot_interfaces::msg::LedStatus>(
            "led_state", 10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&LEDPanelNode::callbackLedStatePublisher, this));
    };

private:
    std::vector<int32_t, std::allocator<int32_t>> ledPanelStatus = {0, 0, 0};
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<my_robot_interfaces::msg::LedStatus>::SharedPtr ledStatePublisher_;
    rclcpp::Service<my_robot_interfaces::srv::BatteryStatus>::SharedPtr ledService_;

    void callBackLedledService(
        const my_robot_interfaces::srv::BatteryStatus::Request::SharedPtr req,
        const my_robot_interfaces::srv::BatteryStatus::Response::SharedPtr res) {
        if (req->state) {
            ledPanelStatus[req->led_number - 1] = 1;
            RCLCPP_INFO(this->get_logger(), "Led Turn On");
        } else {
            ledPanelStatus[req->led_number - 1] = 0;
            RCLCPP_INFO(this->get_logger(), "Led Turn Off");
        }
        res->success = true;
    };

    void callbackLedStatePublisher() {
        auto msg = my_robot_interfaces::msg::LedStatus();
        msg.led_status = ledPanelStatus;
        ledStatePublisher_->publish(msg);
    };
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LEDPanelNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
};