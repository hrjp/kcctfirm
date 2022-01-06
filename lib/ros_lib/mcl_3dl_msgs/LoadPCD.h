#ifndef _ROS_SERVICE_LoadPCD_h
#define _ROS_SERVICE_LoadPCD_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mcl_3dl_msgs
{

static const char LOADPCD[] = "mcl_3dl_msgs/LoadPCD";

  class LoadPCDRequest : public ros::Msg
  {
    public:
      typedef const char* _pcd_path_type;
      _pcd_path_type pcd_path;

    LoadPCDRequest():
      pcd_path("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_pcd_path = strlen(this->pcd_path);
      varToArr(outbuffer + offset, length_pcd_path);
      offset += 4;
      memcpy(outbuffer + offset, this->pcd_path, length_pcd_path);
      offset += length_pcd_path;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_pcd_path;
      arrToVar(length_pcd_path, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_pcd_path; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_pcd_path-1]=0;
      this->pcd_path = (char *)(inbuffer + offset-1);
      offset += length_pcd_path;
     return offset;
    }

    const char * getType(){ return LOADPCD; };
    const char * getMD5(){ return "89d85a975322d7866dba283fe6c40322"; };

  };

  class LoadPCDResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    LoadPCDResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return LOADPCD; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class LoadPCD {
    public:
    typedef LoadPCDRequest Request;
    typedef LoadPCDResponse Response;
  };

}
#endif
