import rclpy
from rclpy.node import Node


class MyNode(Node):
    def __init__(self):
        super().__init__("py_test")
        self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info("Helloo")


def main(args=None):
    rclpy.init(args=args)
    node = MyNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
