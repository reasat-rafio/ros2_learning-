import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64
from example_interfaces.srv import SetBool


class NumberCounterNode(Node):
    def __init__(self):
        super().__init__("number_counter_node")

        self.counter_ = 0
        self.publisher_ = self.create_publisher(Int64, "number_counter", 10)
        self.subscriber = self.create_subscription(
            Int64, "number", self.subscriptions_callback, 10)
        self.service_ = self.create_service(
            SetBool, "reset_counter", self.service_callback)

    def subscriptions_callback(self, msg):
        self.counter_ += msg.data
        new_msg = Int64()
        new_msg.data = self.counter_
        self.publisher_.publish(new_msg)
        self.get_logger().info("number_counter published")

    def service_callback(self, req, res):
        if req.data:
            self.coutner_ = 0
            res.success = True
            res.message = "Counter has been reset"
        else:
            res.success = False
            res.message = "Counter has been reset"

        return res


def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
