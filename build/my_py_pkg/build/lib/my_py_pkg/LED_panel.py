import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import BatteryStatus


class LED_PanelNode(Node):
    def __init__(self):
        super().__init__("led_panel_node")
        self.led_status = [0, 0, 0]
        self.led_service_ = self.create_service(
            BatteryStatus, "set_led", 10, self.callback_set_led)
        # self.led_status_publisher_ = self.create_publisher()

    def callback_set_led(self, req, res):
        if req.state:
            self.led_service_[req.led_number - 1] = 1
            self.get_logger().info(str(req.led_number) + " led got turned on")

        else:
            self.led_service_[req.led_number - 1] = 0
            self.get_logger().info(str(req.led_number) + " led got turned off")

        res.success = True
        return res


def main(args=None):
    rclpy.init(args=args)
    node = LED_PanelNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
