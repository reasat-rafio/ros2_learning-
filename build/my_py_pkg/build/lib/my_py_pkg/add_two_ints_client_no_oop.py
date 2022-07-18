
import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts


def main(args=None):
    rclpy.init(args=args)
    node = Node("add_two_ints_no_oop")
    client = node.create_client(AddTwoInts, "add_two_ints")
    while not client.wait_for_service(1.0):
        node.get_logger().warn("Waiting for server Add Two ints")

    req = AddTwoInts.Request()
    req.a = 3
    req.b = 8

    future = client.call_async(req)
    rclpy.spin_until_future_complete(node, future)

    try:
        res = future.result()
        node.get_logger().info("sum = " + str(res.sum))

    except Exception as e:
        node.get_logger().error("service call failed %r" % (e,))

    rclpy.shutdown()


if __name__ == '__main__':
    main()
