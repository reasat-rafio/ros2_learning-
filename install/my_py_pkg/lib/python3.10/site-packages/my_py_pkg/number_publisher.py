import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64


class NumberPublisher(Node):

    def __init__(self):
        super().__init__("number_publisher_client")
        self.counter_ = 0
        self.publisher_ = self.create_publisher(Int64, "number", 10)
        self.get_logger().info("published on topic number_publisher")
        self.timer_ = self.create_timer(1, self.callback_number_publisher)

    def callback_number_publisher(self):
        self.counter_ += 1
        msg = Int64()
        msg.data = self.counter_
        self.publisher_.publish(msg)
        self.get_logger().info("publishing = " + str(self.counter_))


def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisher()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
