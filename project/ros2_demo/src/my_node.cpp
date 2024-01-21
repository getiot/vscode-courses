#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node
{
public:
    MyNode(const std::string &name)
        : Node(name)
    {
        publisher_ = create_publisher<std_msgs::msg::String>("/my_topic", 10);
        timer_ = this->create_wall_timer(1000ms, std::bind(&MyNode::timer_callback, this));

        subscription_ = create_subscription<std_msgs::msg::String>(
            "/my_topic", 10, std::bind(&MyNode::sub_callback, this, std::placeholders::_1));
    }

private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }

    void sub_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(get_logger(), "Received: %s", msg->data.c_str());
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
};

int main(int argc, char ** argv)
{
    rclcpp::init (argc, argv);

    auto my_node = std::make_shared<MyNode>("my_node");

    rclcpp::spin(my_node);
    rclcpp::shutdown();

    return 0;
}
