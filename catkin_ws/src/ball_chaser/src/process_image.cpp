#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    // Call the command_robot service and pass the requested move commands
    if(!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;

    // set range value (divide into 3 area)
    int lRange = img.width/3;
    int rRange = img.width*2/3;

    int i;
    int pPos = 0;   // pixel position in row
    int selPos = 0; // select position (left, forward, right)
    int lCnt = 0;   // num of white_pixel (left)
    int fCnt = 0;   // num of white_pixel (forward)
    int rCnt = 0;   // num of white_pixel (right)

    // Then, identify if this pixel falls in the left, mid, or right side of the image
    for(i=0;i<img.height*img.step;i += 3)
    {
        // If image pixel is white
        if(img.data[i]==white_pixel && img.data[i+1]==white_pixel && img.data[i+2]==white_pixel)
        {
            pPos = i % (img.width*3) / 3;
            if(pPos<lRange)
                ++lCnt;
            if(pPos>rRange)
                ++rCnt;
            if(pPos>lRange && pPos<=rRange)
                ++fCnt;
        }
    }
    
    // Drive robot ()depending on the white ball position)
    if(lCnt+rCnt+fCnt>0)
    {
        selPos = lCnt > rCnt ? (lCnt > fCnt ? lCnt : fCnt) : (rCnt > fCnt ? rCnt : fCnt);
        if(selPos==lCnt)
        {
            drive_robot(0.0, 1.0);  //  rotate left
        }
        if(selPos==rCnt)
        {
            drive_robot(0.0, -1.0); //  rotate right
        }
        if(selPos==fCnt)
        {
            drive_robot(1.0, 0.0);  //  move forward
        }
    }
    // Request a stop when there's no white ball seen by the camera
    else
    {
        drive_robot(0,0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

