#ifndef _ROS_SERVICE_SetGlobalMap_h
#define _ROS_SERVICE_SetGlobalMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/PointCloud2.h"

namespace hdl_global_localization
{

static const char SETGLOBALMAP[] = "hdl_global_localization/SetGlobalMap";

  class SetGlobalMapRequest : public ros::Msg
  {
    public:
      typedef sensor_msgs::PointCloud2 _global_map_type;
      _global_map_type global_map;

    SetGlobalMapRequest():
      global_map()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->global_map.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->global_map.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SETGLOBALMAP; };
    const char * getMD5(){ return "5ed403eb1abbaa077410b645f248da4e"; };

  };

  class SetGlobalMapResponse : public ros::Msg
  {
    public:

    SetGlobalMapResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETGLOBALMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetGlobalMap {
    public:
    typedef SetGlobalMapRequest Request;
    typedef SetGlobalMapResponse Response;
  };

}
#endif
