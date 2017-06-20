#include "avr_ros/Compass.h"
using namespace higgs_arduino;
ros::MsgSz Compass::serialize(uint8_t *in_data)
{
	ros::MsgSz offset = 0;
	offset += this->orientation.serialize(in_data + offset);
	for(ros::MsgSz i = 0; i < 9; i++) {
		union {
			float real;
			uint32_t base;
		} u_orientation_covariance;
		u_orientation_covariance.real = this->orientation_covariance[i];
		*(in_data + offset + 0) = (u_orientation_covariance.base >> (8 * 0)) & 0xFF;
		*(in_data + offset + 1) = (u_orientation_covariance.base >> (8 * 1)) & 0xFF;
		*(in_data + offset + 2) = (u_orientation_covariance.base >> (8 * 2)) & 0xFF;
		*(in_data + offset + 3) = (u_orientation_covariance.base >> (8 * 3)) & 0xFF;
		offset += sizeof(this->orientation_covariance[i]);
	}
	return offset;
}
ros::MsgSz Compass::deserialize(uint8_t *out_data)
{
	ros::MsgSz offset = 0;
	offset += this->orientation.deserialize(out_data + offset);
	for(ros::MsgSz i = 0; i < 9; i++) {
		union {
			float real;
			uint32_t base;
		} u_orientation_covariance;
		u_orientation_covariance.base = 0;
		u_orientation_covariance.base |= ((typeof(u_orientation_covariance.base)) (*(out_data + offset + 0))) << (8 * 0);
		u_orientation_covariance.base |= ((typeof(u_orientation_covariance.base)) (*(out_data + offset + 1))) << (8 * 1);
		u_orientation_covariance.base |= ((typeof(u_orientation_covariance.base)) (*(out_data + offset + 2))) << (8 * 2);
		u_orientation_covariance.base |= ((typeof(u_orientation_covariance.base)) (*(out_data + offset + 3))) << (8 * 3);
		this->orientation_covariance[i] = u_orientation_covariance.real;
		offset += sizeof(this->orientation_covariance[i]);
	}
	return offset;
}
ros::MsgSz Compass::bytes()
{
	ros::MsgSz msgSize = 0;
	msgSize += orientation.bytes();
	msgSize += sizeof(float);
	return msgSize;
}
