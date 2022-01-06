#ifndef _ROS_cloud_msgs_cloud_info_h
#define _ROS_cloud_msgs_cloud_info_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace cloud_msgs
{

  class cloud_info : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t startRingIndex_length;
      typedef int32_t _startRingIndex_type;
      _startRingIndex_type st_startRingIndex;
      _startRingIndex_type * startRingIndex;
      uint32_t endRingIndex_length;
      typedef int32_t _endRingIndex_type;
      _endRingIndex_type st_endRingIndex;
      _endRingIndex_type * endRingIndex;
      typedef float _startOrientation_type;
      _startOrientation_type startOrientation;
      typedef float _endOrientation_type;
      _endOrientation_type endOrientation;
      typedef float _orientationDiff_type;
      _orientationDiff_type orientationDiff;
      uint32_t segmentedCloudGroundFlag_length;
      typedef bool _segmentedCloudGroundFlag_type;
      _segmentedCloudGroundFlag_type st_segmentedCloudGroundFlag;
      _segmentedCloudGroundFlag_type * segmentedCloudGroundFlag;
      uint32_t segmentedCloudColInd_length;
      typedef uint32_t _segmentedCloudColInd_type;
      _segmentedCloudColInd_type st_segmentedCloudColInd;
      _segmentedCloudColInd_type * segmentedCloudColInd;
      uint32_t segmentedCloudRange_length;
      typedef float _segmentedCloudRange_type;
      _segmentedCloudRange_type st_segmentedCloudRange;
      _segmentedCloudRange_type * segmentedCloudRange;

    cloud_info():
      header(),
      startRingIndex_length(0), startRingIndex(NULL),
      endRingIndex_length(0), endRingIndex(NULL),
      startOrientation(0),
      endOrientation(0),
      orientationDiff(0),
      segmentedCloudGroundFlag_length(0), segmentedCloudGroundFlag(NULL),
      segmentedCloudColInd_length(0), segmentedCloudColInd(NULL),
      segmentedCloudRange_length(0), segmentedCloudRange(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->startRingIndex_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->startRingIndex_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->startRingIndex_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->startRingIndex_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->startRingIndex_length);
      for( uint32_t i = 0; i < startRingIndex_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_startRingIndexi;
      u_startRingIndexi.real = this->startRingIndex[i];
      *(outbuffer + offset + 0) = (u_startRingIndexi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_startRingIndexi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_startRingIndexi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_startRingIndexi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->startRingIndex[i]);
      }
      *(outbuffer + offset + 0) = (this->endRingIndex_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->endRingIndex_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->endRingIndex_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->endRingIndex_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->endRingIndex_length);
      for( uint32_t i = 0; i < endRingIndex_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_endRingIndexi;
      u_endRingIndexi.real = this->endRingIndex[i];
      *(outbuffer + offset + 0) = (u_endRingIndexi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_endRingIndexi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_endRingIndexi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_endRingIndexi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->endRingIndex[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_startOrientation;
      u_startOrientation.real = this->startOrientation;
      *(outbuffer + offset + 0) = (u_startOrientation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_startOrientation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_startOrientation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_startOrientation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->startOrientation);
      union {
        float real;
        uint32_t base;
      } u_endOrientation;
      u_endOrientation.real = this->endOrientation;
      *(outbuffer + offset + 0) = (u_endOrientation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_endOrientation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_endOrientation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_endOrientation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->endOrientation);
      union {
        float real;
        uint32_t base;
      } u_orientationDiff;
      u_orientationDiff.real = this->orientationDiff;
      *(outbuffer + offset + 0) = (u_orientationDiff.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_orientationDiff.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_orientationDiff.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_orientationDiff.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->orientationDiff);
      *(outbuffer + offset + 0) = (this->segmentedCloudGroundFlag_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->segmentedCloudGroundFlag_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->segmentedCloudGroundFlag_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->segmentedCloudGroundFlag_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->segmentedCloudGroundFlag_length);
      for( uint32_t i = 0; i < segmentedCloudGroundFlag_length; i++){
      union {
        bool real;
        uint8_t base;
      } u_segmentedCloudGroundFlagi;
      u_segmentedCloudGroundFlagi.real = this->segmentedCloudGroundFlag[i];
      *(outbuffer + offset + 0) = (u_segmentedCloudGroundFlagi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->segmentedCloudGroundFlag[i]);
      }
      *(outbuffer + offset + 0) = (this->segmentedCloudColInd_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->segmentedCloudColInd_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->segmentedCloudColInd_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->segmentedCloudColInd_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->segmentedCloudColInd_length);
      for( uint32_t i = 0; i < segmentedCloudColInd_length; i++){
      *(outbuffer + offset + 0) = (this->segmentedCloudColInd[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->segmentedCloudColInd[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->segmentedCloudColInd[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->segmentedCloudColInd[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->segmentedCloudColInd[i]);
      }
      *(outbuffer + offset + 0) = (this->segmentedCloudRange_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->segmentedCloudRange_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->segmentedCloudRange_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->segmentedCloudRange_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->segmentedCloudRange_length);
      for( uint32_t i = 0; i < segmentedCloudRange_length; i++){
      union {
        float real;
        uint32_t base;
      } u_segmentedCloudRangei;
      u_segmentedCloudRangei.real = this->segmentedCloudRange[i];
      *(outbuffer + offset + 0) = (u_segmentedCloudRangei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_segmentedCloudRangei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_segmentedCloudRangei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_segmentedCloudRangei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->segmentedCloudRange[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t startRingIndex_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      startRingIndex_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      startRingIndex_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      startRingIndex_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->startRingIndex_length);
      if(startRingIndex_lengthT > startRingIndex_length)
        this->startRingIndex = (int32_t*)realloc(this->startRingIndex, startRingIndex_lengthT * sizeof(int32_t));
      startRingIndex_length = startRingIndex_lengthT;
      for( uint32_t i = 0; i < startRingIndex_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_startRingIndex;
      u_st_startRingIndex.base = 0;
      u_st_startRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_startRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_startRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_startRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_startRingIndex = u_st_startRingIndex.real;
      offset += sizeof(this->st_startRingIndex);
        memcpy( &(this->startRingIndex[i]), &(this->st_startRingIndex), sizeof(int32_t));
      }
      uint32_t endRingIndex_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      endRingIndex_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      endRingIndex_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      endRingIndex_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->endRingIndex_length);
      if(endRingIndex_lengthT > endRingIndex_length)
        this->endRingIndex = (int32_t*)realloc(this->endRingIndex, endRingIndex_lengthT * sizeof(int32_t));
      endRingIndex_length = endRingIndex_lengthT;
      for( uint32_t i = 0; i < endRingIndex_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_endRingIndex;
      u_st_endRingIndex.base = 0;
      u_st_endRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_endRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_endRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_endRingIndex.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_endRingIndex = u_st_endRingIndex.real;
      offset += sizeof(this->st_endRingIndex);
        memcpy( &(this->endRingIndex[i]), &(this->st_endRingIndex), sizeof(int32_t));
      }
      union {
        float real;
        uint32_t base;
      } u_startOrientation;
      u_startOrientation.base = 0;
      u_startOrientation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_startOrientation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_startOrientation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_startOrientation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->startOrientation = u_startOrientation.real;
      offset += sizeof(this->startOrientation);
      union {
        float real;
        uint32_t base;
      } u_endOrientation;
      u_endOrientation.base = 0;
      u_endOrientation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_endOrientation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_endOrientation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_endOrientation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->endOrientation = u_endOrientation.real;
      offset += sizeof(this->endOrientation);
      union {
        float real;
        uint32_t base;
      } u_orientationDiff;
      u_orientationDiff.base = 0;
      u_orientationDiff.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_orientationDiff.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_orientationDiff.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_orientationDiff.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->orientationDiff = u_orientationDiff.real;
      offset += sizeof(this->orientationDiff);
      uint32_t segmentedCloudGroundFlag_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      segmentedCloudGroundFlag_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      segmentedCloudGroundFlag_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      segmentedCloudGroundFlag_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->segmentedCloudGroundFlag_length);
      if(segmentedCloudGroundFlag_lengthT > segmentedCloudGroundFlag_length)
        this->segmentedCloudGroundFlag = (bool*)realloc(this->segmentedCloudGroundFlag, segmentedCloudGroundFlag_lengthT * sizeof(bool));
      segmentedCloudGroundFlag_length = segmentedCloudGroundFlag_lengthT;
      for( uint32_t i = 0; i < segmentedCloudGroundFlag_length; i++){
      union {
        bool real;
        uint8_t base;
      } u_st_segmentedCloudGroundFlag;
      u_st_segmentedCloudGroundFlag.base = 0;
      u_st_segmentedCloudGroundFlag.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_segmentedCloudGroundFlag = u_st_segmentedCloudGroundFlag.real;
      offset += sizeof(this->st_segmentedCloudGroundFlag);
        memcpy( &(this->segmentedCloudGroundFlag[i]), &(this->st_segmentedCloudGroundFlag), sizeof(bool));
      }
      uint32_t segmentedCloudColInd_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      segmentedCloudColInd_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      segmentedCloudColInd_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      segmentedCloudColInd_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->segmentedCloudColInd_length);
      if(segmentedCloudColInd_lengthT > segmentedCloudColInd_length)
        this->segmentedCloudColInd = (uint32_t*)realloc(this->segmentedCloudColInd, segmentedCloudColInd_lengthT * sizeof(uint32_t));
      segmentedCloudColInd_length = segmentedCloudColInd_lengthT;
      for( uint32_t i = 0; i < segmentedCloudColInd_length; i++){
      this->st_segmentedCloudColInd =  ((uint32_t) (*(inbuffer + offset)));
      this->st_segmentedCloudColInd |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_segmentedCloudColInd |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_segmentedCloudColInd |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_segmentedCloudColInd);
        memcpy( &(this->segmentedCloudColInd[i]), &(this->st_segmentedCloudColInd), sizeof(uint32_t));
      }
      uint32_t segmentedCloudRange_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      segmentedCloudRange_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      segmentedCloudRange_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      segmentedCloudRange_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->segmentedCloudRange_length);
      if(segmentedCloudRange_lengthT > segmentedCloudRange_length)
        this->segmentedCloudRange = (float*)realloc(this->segmentedCloudRange, segmentedCloudRange_lengthT * sizeof(float));
      segmentedCloudRange_length = segmentedCloudRange_lengthT;
      for( uint32_t i = 0; i < segmentedCloudRange_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_segmentedCloudRange;
      u_st_segmentedCloudRange.base = 0;
      u_st_segmentedCloudRange.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_segmentedCloudRange.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_segmentedCloudRange.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_segmentedCloudRange.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_segmentedCloudRange = u_st_segmentedCloudRange.real;
      offset += sizeof(this->st_segmentedCloudRange);
        memcpy( &(this->segmentedCloudRange[i]), &(this->st_segmentedCloudRange), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "cloud_msgs/cloud_info"; };
    const char * getMD5(){ return "af8fdf3af62b4ae75761d0e92aa4cf43"; };

  };

}
#endif
