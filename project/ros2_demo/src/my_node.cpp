#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MyNode : public rclcpp::Node
{
public:
    MyNode(const std::string &name)
        : Node(name)
    {
        publisher_ = create_publisher<std_msgs::msg::String>("/my_topic", 10);
        subscription_ = create_subscription<std_msgs::msg::String>(
            "/my_topic", 10, std::bind(&MyNode::callback, this, std::placeholders::_1));
    }

private:
    void callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(get_logger(), "Received: %s", msg->data.c_str());

        // Modify the received message and publish it again
        auto new_msg = std::make_shared<std_msgs::msg::String>();
        new_msg->data = "Modified: " + msg->data;
        publisher_->publish(*new_msg);
        RCLCPP_INFO(get_logger(), "Published: %s", new_msg->data.c_str());
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{
    rclcpp::init (argc, argv);

    auto my_node = std::make_shared<MyNode>("my_node");
    rclcpp::spin(my_node);
    rclcpp::shutdown();

    return 0;
}
