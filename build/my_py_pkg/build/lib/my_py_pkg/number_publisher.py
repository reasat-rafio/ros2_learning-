import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64


class NumberPublisher(Node):
    def __init__(self):
        super().__init__("number_publisher_client")
        self.counter_ = 0
        self.publisher_ = self.create_publisher(Int64, "number_publisher", 10)
        self.timer_ = self.create_timer(1, self.callback_number_publisher)

    def callback_number_publisher(self):
        counter += 1
        msg = Int64()
        msg.data = counter
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisher()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
