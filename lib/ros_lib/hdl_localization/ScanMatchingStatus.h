#ifndef _ROS_hdl_localization_ScanMatchingStatus_h
#define _ROS_hdl_localization_ScanMatchingStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"
#include "std_msgs/String.h"

namespace hdl_localization
{

  class ScanMatchingStatus : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef bool _has_converged_type;
      _has_converged_type has_converged;
      typedef float _matching_error_type;
      _matching_error_type matching_error;
      typedef float _inlier_fraction_type;
      _inlier_fraction_type inlier_fraction;
      typedef geometry_msgs::Transform _relative_pose_type;
      _relative_pose_type relative_pose;
      uint32_t prediction_labels_length;
      typedef std_msgs::String _prediction_labels_type;
      _prediction_labels_type st_prediction_labels;
      _prediction_labels_type * prediction_labels;
      uint32_t prediction_errors_length;
      typedef geometry_msgs::Transform _prediction_errors_type;
      _prediction_errors_type st_prediction_errors;
      _prediction_errors_type * prediction_errors;

    ScanMatchingStatus():
      header(),
      has_converged(0),
      matching_error(0),
      inlier_fraction(0),
      relative_pose(),
      prediction_labels_length(0), prediction_labels(NULL),
      prediction_errors_length(0), prediction_errors(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_has_converged;
      u_has_converged.real = this->has_converged;
      *(outbuffer + offset + 0) = (u_has_converged.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->has_converged);
      union {
        float real;
        uint32_t base;
      } u_matching_error;
      u_matching_error.real = this->matching_error;
      *(outbuffer + offset + 0) = (u_matching_error.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_matching_error.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_matching_error.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_matching_error.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->matching_error);
      union {
        float real;
        uint32_t base;
      } u_inlier_fraction;
      u_inlier_fraction.real = this->inlier_fraction;
      *(outbuffer + offset + 0) = (u_inlier_fraction.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_inlier_fraction.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_inlier_fraction.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_inlier_fraction.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->inlier_fraction);
      offset += this->relative_pose.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->prediction_labels_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->prediction_labels_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->prediction_labels_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->prediction_labels_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->prediction_labels_length);
      for( uint32_t i = 0; i < prediction_labels_length; i++){
      offset += this->prediction_labels[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->prediction_errors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->prediction_errors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->prediction_errors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->prediction_errors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->prediction_errors_length);
      for( uint32_t i = 0; i < prediction_errors_length; i++){
      offset += this->prediction_errors[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_has_converged;
      u_has_converged.base = 0;
      u_has_converged.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->has_converged = u_has_converged.real;
      offset += sizeof(this->has_converged);
      union {
        float real;
        uint32_t base;
      } u_matching_error;
      u_matching_error.base = 0;
      u_matching_error.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_matching_error.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_matching_error.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_matching_error.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->matching_error = u_matching_error.real;
      offset += sizeof(this->matching_error);
      union {
        float real;
        uint32_t base;
      } u_inlier_fraction;
      u_inlier_fraction.base = 0;
      u_inlier_fraction.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_inlier_fraction.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_inlier_fraction.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_inlier_fraction.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->inlier_fraction = u_inlier_fraction.real;
      offset += sizeof(this->inlier_fraction);
      offset += this->relative_pose.deserialize(inbuffer + offset);
      uint32_t prediction_labels_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      prediction_labels_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      prediction_labels_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      prediction_labels_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->prediction_labels_length);
      if(prediction_labels_lengthT > prediction_labels_length)
        this->prediction_labels = (std_msgs::String*)realloc(this->prediction_labels, prediction_labels_lengthT * sizeof(std_msgs::String));
      prediction_labels_length = prediction_labels_lengthT;
      for( uint32_t i = 0; i < prediction_labels_length; i++){
      offset += this->st_prediction_labels.deserialize(inbuffer + offset);
        memcpy( &(this->prediction_labels[i]), &(this->st_prediction_labels), sizeof(std_msgs::String));
      }
      uint32_t prediction_errors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      prediction_errors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      prediction_errors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      prediction_errors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->prediction_errors_length);
      if(prediction_errors_lengthT > prediction_errors_length)
        this->prediction_errors = (geometry_msgs::Transform*)realloc(this->prediction_errors, prediction_errors_lengthT * sizeof(geometry_msgs::Transform));
      prediction_errors_length = prediction_errors_lengthT;
      for( uint32_t i = 0; i < prediction_errors_length; i++){
      offset += this->st_prediction_errors.deserialize(inbuffer + offset);
        memcpy( &(this->prediction_errors[i]), &(this->st_prediction_errors), sizeof(geometry_msgs::Transform));
      }
     return offset;
    }

    const char * getType(){ return "hdl_localization/ScanMatchingStatus"; };
    const char * getMD5(){ return "9482ff8da7c52f631faa8ed74fbad0c2"; };

  };

}
#endif
