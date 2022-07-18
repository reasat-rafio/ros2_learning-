#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

class AddTwoIntsClient : public rclcpp::Node {
public:
    AddTwoIntsClient() : Node("add_two_ints_client") {
        // thread1_ = std::thread(std::bind(&AddTwoIntsClient::callAddTwoIntsService, this, 1, 4));
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClient::callAddTwoIntsService, this, 1, 4)));
    }

    void callAddTwoIntsService(int a, int b) {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

        while (!client->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_INFO(this->get_logger(), "waiting for the server");
        }

        auto req = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        req->a = a;
        req->b = b;

        auto future = client->async_send_request(req);

        try {
            auto res = future.get();
            RCLCPP_INFO(this->get_logger(), "sum = %ld", res->sum);

        } catch (std::exception const &) {
            RCLCPP_ERROR(this->get_logger(), "Service call failed");
        };
    }

private:
    // std::thread thread1_;
    std::vector<std::thread> threads_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
