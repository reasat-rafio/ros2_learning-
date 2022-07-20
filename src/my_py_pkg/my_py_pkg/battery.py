import time
import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import BatteryStatus


class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery_node")
        self.battery_state__ = 0
        self.timer_ = self.create_timer(1, self.get_battery_state)

        self.battery_status_client = self.create_client(
            BatteryStatus, "set_led")

    def get_battery_state(self):
        if not self.battery_state__:
            time.sleep(3)
            self.battery_state__ = 100
            self.call_battery_status_client(battery_low=False)

        else:
            time.sleep(6)
            self.battery_state__ = 0
            self.call_battery_status_client(battery_low=True)

    def call_battery_status_client(self, battery_low: bool):
        while not self.battery_status_client.wait_for_service(1):
            self.get_logger().warn("Waiting for the clinet")

        req = BatteryStatus.Request()
        if battery_low:
            req.led_number = 3
            req.state = True
        else:
            req.led_number = 3
            req.state = False

        future = self.battery_status_client.call_async(req)
        future.add_done_callback(self.callback_battery_status_client)

    def callback_battery_status_client(self, future):
        try:
            response = future.result()
            self.get_logger().info("response = " + str(response.success))

        except Exception as e:
            self.get_logger().error("service call failed %r" % (e,))


def main(args=None):
    rclpy.init(args=args)
    node = BatteryNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
