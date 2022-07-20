// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_robot_interfaces:srv/BatteryStatus.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_INTERFACES__SRV__DETAIL__BATTERY_STATUS__BUILDER_HPP_
#define MY_ROBOT_INTERFACES__SRV__DETAIL__BATTERY_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_robot_interfaces/srv/detail/battery_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_robot_interfaces
{

namespace srv
{

namespace builder
{

class Init_BatteryStatus_Request_state
{
public:
  explicit Init_BatteryStatus_Request_state(::my_robot_interfaces::srv::BatteryStatus_Request & msg)
  : msg_(msg)
  {}
  ::my_robot_interfaces::srv::BatteryStatus_Request state(::my_robot_interfaces::srv::BatteryStatus_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_interfaces::srv::BatteryStatus_Request msg_;
};

class Init_BatteryStatus_Request_led_number
{
public:
  Init_BatteryStatus_Request_led_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BatteryStatus_Request_state led_number(::my_robot_interfaces::srv::BatteryStatus_Request::_led_number_type arg)
  {
    msg_.led_number = std::move(arg);
    return Init_BatteryStatus_Request_state(msg_);
  }

private:
  ::my_robot_interfaces::srv::BatteryStatus_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_interfaces::srv::BatteryStatus_Request>()
{
  return my_robot_interfaces::srv::builder::Init_BatteryStatus_Request_led_number();
}

}  // namespace my_robot_interfaces


namespace my_robot_interfaces
{

namespace srv
{

namespace builder
{

class Init_BatteryStatus_Response_success
{
public:
  Init_BatteryStatus_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_robot_interfaces::srv::BatteryStatus_Response success(::my_robot_interfaces::srv::BatteryStatus_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_interfaces::srv::BatteryStatus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_interfaces::srv::BatteryStatus_Response>()
{
  return my_robot_interfaces::srv::builder::Init_BatteryStatus_Response_success();
}

}  // namespace my_robot_interfaces

#endif  // MY_ROBOT_INTERFACES__SRV__DETAIL__BATTERY_STATUS__BUILDER_HPP_
