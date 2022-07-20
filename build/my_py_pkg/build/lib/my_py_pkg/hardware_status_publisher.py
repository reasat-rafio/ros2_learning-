import rclpy
from rclpy.node import Node

from my_robot_interfaces.msg import HardWareStatus


class HardWareStatusNode(Node):

    def __init__(self):
        super().__init__('hardware_status_node')
        self.hw_status_publisher = self.create_publisher(
            HardWareStatus,
            "hardware_publihser",
            10)
        self.timer_ = self.create_timer(1, self.publish_hw_status)
        self.get_logger().info("hardware status publisher has been started")

    def publish_hw_status(self):
        msg = HardWareStatus()
        msg.temperature = 45
        msg.are_motors_ready = True
        msg.debug_message = "Nothing special here"
        self.hw_status_publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(HardWareStatusNode())
    rclpy.shutdown()


if __name__ == '__main__':
    main()
