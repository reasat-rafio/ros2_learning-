#include "my_robot_interfaces/srv/battery_status.hpp"
#include "rclcpp/rclcpp.hpp"

class BatteryNode : public rclcpp::Node {
public:
    BatteryNode() : Node("battery_node") {
        batteryState_ = 100;
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&BatteryNode::setBatteryState, this));
        batteryClinet_ = this->create_client<my_robot_interfaces::srv::BatteryStatus>("set_led");
    };

    void setBatteryState() {
        if (batteryState_) {
            std::this_thread::sleep_for((std::chrono::seconds(6)));
            batteryState_ = false;
            threads_.push_back(std::thread(std::bind(&BatteryNode::callBatteryClient, this, batteryState_)));
            RCLCPP_INFO(this->get_logger(), "Battery Low");
        } else {
            std::this_thread::sleep_for((std::chrono::seconds(3)));
            batteryState_ = true;
            threads_.push_back(std::thread(std::bind(&BatteryNode::callBatteryClient, this, batteryState_)));
        }
    };

    void callBatteryClient(bool batteryState) {
        while (!batteryClinet_->wait_for_service(std::chrono::seconds(1)))
            RCLCPP_WARN(this->get_logger(), "Waiting for the server");

        auto req = std::make_shared<my_robot_interfaces::srv::BatteryStatus::Request>();

        if (batteryState) {
            req->led_number = 3;
            req->state = true;
        } else {
            req->led_number = 3;
            req->state = true;
        }

        auto future = batteryClinet_->async_send_request(req);

        try {
            auto res = future.get();
            RCLCPP_INFO(this->get_logger(), "response = %d", res->success);

        } catch (std::exception const &) {
            RCLCPP_ERROR(this->get_logger(), "Service call failed");
        };
    };

private:
    bool batteryState_;
    std::vector<std::thread> threads_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<my_robot_interfaces::srv::BatteryStatus>::SharedPtr batteryClinet_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BatteryNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
};