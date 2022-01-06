#ifndef _ROS_SERVICE_SetGlobalLocalizationEngine_h
#define _ROS_SERVICE_SetGlobalLocalizationEngine_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"

namespace hdl_global_localization
{

static const char SETGLOBALLOCALIZATIONENGINE[] = "hdl_global_localization/SetGlobalLocalizationEngine";

  class SetGlobalLocalizationEngineRequest : public ros::Msg
  {
    public:
      typedef std_msgs::String _engine_name_type;
      _engine_name_type engine_name;

    SetGlobalLocalizationEngineRequest():
      engine_name()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->engine_name.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->engine_name.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SETGLOBALLOCALIZATIONENGINE; };
    const char * getMD5(){ return "f71639c3aeb058fa00da5a20981c23c9"; };

  };

  class SetGlobalLocalizationEngineResponse : public ros::Msg
  {
    public:

    SetGlobalLocalizationEngineResponse()
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

    const char * getType(){ return SETGLOBALLOCALIZATIONENGINE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetGlobalLocalizationEngine {
    public:
    typedef SetGlobalLocalizationEngineRequest Request;
    typedef SetGlobalLocalizationEngineResponse Response;
  };

}
#endif
