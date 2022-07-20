import time
import rclpy
from rclpy.node import Node


class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery_node")
        self.battery_state__ = 0
        self.timer_ = self.create_timer(1, self.get_battery_state)

    def get_battery_state(self):
        if not self.battery_state__:
            time.sleep(3)
            self.battery_state__ = 100
            self.get_logger().info("Battery full")

        else:
            time.sleep(6)
            self.battery_state__ = 0
            self.get_logger().info("Battery empty")


def main(args=None):
    rclpy.init(args=args)
    node = BatteryNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
