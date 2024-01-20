from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    
    return LaunchDescription([
        Node(namespace='ros2_demo', package='ros2_demo', executable='my_node', output='screen')
    ])

