/// @file RosArrayPublisher.h
/// @brief MultiArray publisher using rosserial
/// @date 2020.10.31
/// @author Shunya Hara
#pragma once
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>

template<typename ARRAY_TYPE> class RosArrayPublisher{
    public:
    /// @brief コンストラクタ
    /// @param nh rosのノードハンドル
    /// @param topic_name publishするtopic名
    /// @param array_size publishする配列の要素数
    RosArrayPublisher(ros::NodeHandle& nh,const char *topic_name,int array_size);

    /// @brief publishする関数
    void publish();

    /// @brief publishするデータを入れるオブジェクト array.data[1]のようにアクセスする
    ARRAY_TYPE array;

    private:
    ros::Publisher array_pub;
};




template<typename ARRAY_TYPE>
RosArrayPublisher<ARRAY_TYPE>::RosArrayPublisher(ros::NodeHandle& nh,const char *topic_name,int array_size):
array_pub(topic_name, &array){
    array.data=decltype(array.data)(malloc(sizeof (array.data)*array_size));
    //array.data=malloc(sizeof (array.data)*array_size);
    array.data_length=array_size;
    for(int i=0;i<array_size;i++){
        array.data[i]=0.0;
    }
    nh.advertise(array_pub);
}

template<typename ARRAY_TYPE>
void RosArrayPublisher<ARRAY_TYPE>::publish(){
    array_pub.publish(&array);
}
