import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import BatteryStatus
from my_robot_interfaces.msg import LedStatus


class LED_PanelNode(Node):
    def __init__(self):
        super().__init__("led_panel_node")

        self.led_status = [0, 0, 0]
        self.timer_ = self.create_timer(1, self.callback_led_status_publisher)

        self.led_service_ = self.create_service(
            BatteryStatus, "set_led", self.callback_set_led)
        self.led_status_publisher_ = self.create_publisher(
            LedStatus, "led_state", 10)

    def callback_set_led(self, req, res):
        if req.state:
            self.led_status[req.led_number - 1] = 1
            self.get_logger().info(str(req.led_number) + " led got turned on")

        else:
            self.led_status[req.led_number - 1] = 0
            self.get_logger().info(str(req.led_number) + " led got turned off")

        res.success = True
        return res

    def callback_led_status_publisher(self):
        msg = LedStatus()
        msg.led_status = self.led_status
        self.led_status_publisher_.publish(msg)
        self.get_logger().info("publishing led status = " + str(self.led_status))


def main(args=None):
    rclpy.init(args=args)
    node = LED_PanelNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
