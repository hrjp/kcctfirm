#ifndef _ROS_SERVICE_QueryGlobalLocalization_h
#define _ROS_SERVICE_QueryGlobalLocalization_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/PointCloud2.h"

namespace hdl_global_localization
{

static const char QUERYGLOBALLOCALIZATION[] = "hdl_global_localization/QueryGlobalLocalization";

  class QueryGlobalLocalizationRequest : public ros::Msg
  {
    public:
      typedef int64_t _max_num_candidates_type;
      _max_num_candidates_type max_num_candidates;
      typedef sensor_msgs::PointCloud2 _cloud_type;
      _cloud_type cloud;

    QueryGlobalLocalizationRequest():
      max_num_candidates(0),
      cloud()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_max_num_candidates;
      u_max_num_candidates.real = this->max_num_candidates;
      *(outbuffer + offset + 0) = (u_max_num_candidates.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_num_candidates.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max_num_candidates.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max_num_candidates.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_max_num_candidates.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_max_num_candidates.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_max_num_candidates.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_max_num_candidates.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->max_num_candidates);
      offset += this->cloud.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_max_num_candidates;
      u_max_num_candidates.base = 0;
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_max_num_candidates.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->max_num_candidates = u_max_num_candidates.real;
      offset += sizeof(this->max_num_candidates);
      offset += this->cloud.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return QUERYGLOBALLOCALIZATION; };
    const char * getMD5(){ return "0802ea456537ff7eae03a65bc7019e2c"; };

  };

  class QueryGlobalLocalizationResponse : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef std_msgs::Header _globalmap_header_type;
      _globalmap_header_type globalmap_header;
      uint32_t inlier_fractions_length;
      typedef float _inlier_fractions_type;
      _inlier_fractions_type st_inlier_fractions;
      _inlier_fractions_type * inlier_fractions;
      uint32_t errors_length;
      typedef float _errors_type;
      _errors_type st_errors;
      _errors_type * errors;
      uint32_t poses_length;
      typedef geometry_msgs::Pose _poses_type;
      _poses_type st_poses;
      _poses_type * poses;

    QueryGlobalLocalizationResponse():
      header(),
      globalmap_header(),
      inlier_fractions_length(0), inlier_fractions(NULL),
      errors_length(0), errors(NULL),
      poses_length(0), poses(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->globalmap_header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->inlier_fractions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->inlier_fractions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->inlier_fractions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->inlier_fractions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->inlier_fractions_length);
      for( uint32_t i = 0; i < inlier_fractions_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->inlier_fractions[i]);
      }
      *(outbuffer + offset + 0) = (this->errors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->errors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->errors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->errors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->errors_length);
      for( uint32_t i = 0; i < errors_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->errors[i]);
      }
      *(outbuffer + offset + 0) = (this->poses_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->poses_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->poses_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->poses_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poses_length);
      for( uint32_t i = 0; i < poses_length; i++){
      offset += this->poses[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->globalmap_header.deserialize(inbuffer + offset);
      uint32_t inlier_fractions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      inlier_fractions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      inlier_fractions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      inlier_fractions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->inlier_fractions_length);
      if(inlier_fractions_lengthT > inlier_fractions_length)
        this->inlier_fractions = (float*)realloc(this->inlier_fractions, inlier_fractions_lengthT * sizeof(float));
      inlier_fractions_length = inlier_fractions_lengthT;
      for( uint32_t i = 0; i < inlier_fractions_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_inlier_fractions));
        memcpy( &(this->inlier_fractions[i]), &(this->st_inlier_fractions), sizeof(float));
      }
      uint32_t errors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      errors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      errors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      errors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->errors_length);
      if(errors_lengthT > errors_length)
        this->errors = (float*)realloc(this->errors, errors_lengthT * sizeof(float));
      errors_length = errors_lengthT;
      for( uint32_t i = 0; i < errors_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_errors));
        memcpy( &(this->errors[i]), &(this->st_errors), sizeof(float));
      }
      uint32_t poses_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      poses_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      poses_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      poses_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->poses_length);
      if(poses_lengthT > poses_length)
        this->poses = (geometry_msgs::Pose*)realloc(this->poses, poses_lengthT * sizeof(geometry_msgs::Pose));
      poses_length = poses_lengthT;
      for( uint32_t i = 0; i < poses_length; i++){
      offset += this->st_poses.deserialize(inbuffer + offset);
        memcpy( &(this->poses[i]), &(this->st_poses), sizeof(geometry_msgs::Pose));
      }
     return offset;
    }

    const char * getType(){ return QUERYGLOBALLOCALIZATION; };
    const char * getMD5(){ return "a537b478ec66ac3888e62265f7d9d901"; };

  };

  class QueryGlobalLocalization {
    public:
    typedef QueryGlobalLocalizationRequest Request;
    typedef QueryGlobalLocalizationResponse Response;
  };

}
#endif
