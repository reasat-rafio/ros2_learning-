import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts


class AddTwoIntserServerNode(Node):

    def __init__(self):
        super().__init__('add_two_ints_server')
        self.server_ = self.create_service(
            AddTwoInts, "add_two_ints", self.callback_add_two_ints)

    def callback_add_two_ints(self, req, res):
        res.sum = req.a + req.b
        self.get_logger().info("sum = " + str(req.a + req.b))
        return res


def main(args=None):
    rclpy.init(args=args)
    node = AddTwoIntserServerNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
