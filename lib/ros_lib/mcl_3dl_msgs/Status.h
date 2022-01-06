#ifndef _ROS_mcl_3dl_msgs_Status_h
#define _ROS_mcl_3dl_msgs_Status_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mcl_3dl_msgs
{

  class Status : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _status_type;
      _status_type status;
      typedef uint8_t _error_type;
      _error_type error;
      typedef uint8_t _convergence_status_type;
      _convergence_status_type convergence_status;
      typedef uint32_t _particle_size_type;
      _particle_size_type particle_size;
      typedef float _match_ratio_type;
      _match_ratio_type match_ratio;
      typedef float _entropy_type;
      _entropy_type entropy;
      enum { NORMAL =  0 };
      enum { GLOBAL_LOCALIZATION =  1 };
      enum { EXPANSION_RESETTING =  2 };
      enum { ERROR_NORMAL =  0 };
      enum { ERROR_POINTS_NOT_FOUND =  1 };
      enum { CONVERGENCE_STATUS_NORMAL =  0 };
      enum { CONVERGENCE_STATUS_CONVERGED =  1 };
      enum { CONVERGENCE_STATUS_LARGE_STD_VALUE =  2 };

    Status():
      header(),
      status(0),
      error(0),
      convergence_status(0),
      particle_size(0),
      match_ratio(0),
      entropy(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      *(outbuffer + offset + 0) = (this->error >> (8 * 0)) & 0xFF;
      offset += sizeof(this->error);
      *(outbuffer + offset + 0) = (this->convergence_status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->convergence_status);
      *(outbuffer + offset + 0) = (this->particle_size >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->particle_size >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->particle_size >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->particle_size >> (8 * 3)) & 0xFF;
      offset += sizeof(this->particle_size);
      union {
        float real;
        uint32_t base;
      } u_match_ratio;
      u_match_ratio.real = this->match_ratio;
      *(outbuffer + offset + 0) = (u_match_ratio.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_match_ratio.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_match_ratio.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_match_ratio.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->match_ratio);
      union {
        float real;
        uint32_t base;
      } u_entropy;
      u_entropy.real = this->entropy;
      *(outbuffer + offset + 0) = (u_entropy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_entropy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_entropy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_entropy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->entropy);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
      this->error =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->error);
      this->convergence_status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->convergence_status);
      this->particle_size =  ((uint32_t) (*(inbuffer + offset)));
      this->particle_size |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->particle_size |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->particle_size |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->particle_size);
      union {
        float real;
        uint32_t base;
      } u_match_ratio;
      u_match_ratio.base = 0;
      u_match_ratio.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_match_ratio.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_match_ratio.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_match_ratio.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->match_ratio = u_match_ratio.real;
      offset += sizeof(this->match_ratio);
      union {
        float real;
        uint32_t base;
      } u_entropy;
      u_entropy.base = 0;
      u_entropy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_entropy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_entropy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_entropy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->entropy = u_entropy.real;
      offset += sizeof(this->entropy);
     return offset;
    }

    const char * getType(){ return "mcl_3dl_msgs/Status"; };
    const char * getMD5(){ return "f47002d781357aed0b4c4738b39ef49a"; };

  };

}
#endif
