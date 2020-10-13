#include <force_sensor/force_sensor.h>

void cb1(ConstWrenchStampedPtr &msg1)
{
        msgWrenchedStamped1.header.stamp = ros::Time::now();
        msgWrenchedStamped1.wrench.force.x = msg1->wrench().force().x();
        msgWrenchedStamped1.wrench.force.y = msg1->wrench().force().y();
        msgWrenchedStamped1.wrench.force.z = msg1->wrench().force().z();
        msgWrenchedStamped1.wrench.torque.x = msg1->wrench().torque().x();
        msgWrenchedStamped1.wrench.torque.y = msg1->wrench().torque().y();
        msgWrenchedStamped1.wrench.torque.z = msg1->wrench().torque().z();
}
void cb2(ConstWrenchStampedPtr &msg2)
{
        msgWrenchedStamped2.header.stamp = ros::Time::now();
        msgWrenchedStamped2.wrench.force.x = msg2->wrench().force().x();
        msgWrenchedStamped2.wrench.force.y = msg2->wrench().force().y();
        msgWrenchedStamped2.wrench.force.z = msg2->wrench().force().z();
        msgWrenchedStamped2.wrench.torque.x = msg2->wrench().torque().x();
        msgWrenchedStamped2.wrench.torque.y = msg2->wrench().torque().y();
        msgWrenchedStamped2.wrench.torque.z = msg2->wrench().torque().z();
}
/////////////////////////////////////////////////
int main(int argc, char **argv)
{
        // Load gazebo
        gazebo::client::setup(argc, argv);

        // Load ROS
        ros::init(argc, argv, "force_sensor");

        // Create our node for communication
        gazebo::transport::NodePtr node(new gazebo::transport::Node());
        node->Init();

        // Create ROS node and init
        ros::NodeHandle n;
        // ros::param::get("~ros_rate", ros_rate);

        // Listen to Gazebo world_stats topic
        gazebo::transport::SubscriberPtr sub1 = node->Subscribe("~/model_1/joint_01/force_torque/wrench", cb1);
        gazebo::transport::SubscriberPtr sub2 = node->Subscribe("~/model_2/joint_02/force_torque2/wrench", cb2);
        ros::Rate loop_rate(ros_rate); // 100 hz

        while(ros::ok())

        {

                if(fabs(msgWrenchedStamped1.wrench.torque.x) > 0.1 || fabs(msgWrenchedStamped1.wrench.torque.y) > 0.1 || fabs(msgWrenchedStamped1.wrench.torque.z) >0.1 ) {
                        collision_count_1 = 1;
                }
                else if(fabs(msgWrenchedStamped1.wrench.torque.x) < 0.0001 && fabs(msgWrenchedStamped1.wrench.torque.y) < 0.0001 && fabs(msgWrenchedStamped1.wrench.torque.z) <0.0001 ) {
                        collision_count_2 = 1;
                }
                else if(collision_count_1 == 1 && collision_count_2 == 1) {
                        count1 = count1 + 1;
                        collision_count_1 = 0;
                        collision_count_2 = 0;
                        printf("衝突回数：%d,%d\n",count1, count2);
                }
                else{
                        continue;
                }
                if(fabs(msgWrenchedStamped2.wrench.torque.x) > 0.1 || fabs(msgWrenchedStamped2.wrench.torque.y) > 0.1 || fabs(msgWrenchedStamped2.wrench.torque.z) >0.1 ) {
                        collision_count_3 = 1;
                }
                else if(fabs(msgWrenchedStamped2.wrench.torque.x) < 0.0001 && fabs(msgWrenchedStamped2.wrench.torque.y) < 0.0001 && fabs(msgWrenchedStamped2.wrench.torque.z) <0.0001 ) {
                        collision_count_4 = 1;
                }
                else if(collision_count_3 == 1 && collision_count_4 == 1) {
                        count2 = count2 + 1;
                        collision_count_3 = 0;
                        collision_count_4 = 0;
                        printf("衝突回数：%d,%d\n",count1, count2);
                }
                else{
                        continue;
                }
                ros::spinOnce();
                loop_rate.sleep();
        }
        gazebo::shutdown();
        return 0;
}
