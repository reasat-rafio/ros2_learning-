#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client_no_oop");

    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        RCLCPP_WARN(node->get_logger(), "waiting for the server");
    }

    auto req = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    req->a = 3;
    req->b = 8;

    auto future = client->async_send_request(req);
    if (rclcpp::spin_until_future_complete(node, future) == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(node->get_logger(), "sum = %ld", future.get()->sum);
    } else {
        RCLCPP_ERROR(node->get_logger(), "Error while calling the service");
    };
    rclcpp::shutdown();
    return 0;
}
