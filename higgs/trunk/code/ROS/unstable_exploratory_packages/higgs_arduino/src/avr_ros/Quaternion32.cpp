#include "avr_ros/Quaternion32.h"
using namespace higgs_arduino;
ros::MsgSz Quaternion32::serialize(uint8_t *in_data)
{
	ros::MsgSz offset = 0;
	union {
		float real;
		uint32_t base;
	} u_x;
	u_x.real = this->x;
	*(in_data + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
	*(in_data + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
	*(in_data + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
	*(in_data + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
	offset += sizeof(this->x);
	union {
		float real;
		uint32_t base;
	} u_y;
	u_y.real = this->y;
	*(in_data + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
	*(in_data + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
	*(in_data + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
	*(in_data + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
	offset += sizeof(this->y);
	union {
		float real;
		uint32_t base;
	} u_z;
	u_z.real = this->z;
	*(in_data + offset + 0) = (u_z.base >> (8 * 0)) & 0xFF;
	*(in_data + offset + 1) = (u_z.base >> (8 * 1)) & 0xFF;
	*(in_data + offset + 2) = (u_z.base >> (8 * 2)) & 0xFF;
	*(in_data + offset + 3) = (u_z.base >> (8 * 3)) & 0xFF;
	offset += sizeof(this->z);
	union {
		float real;
		uint32_t base;
	} u_w;
	u_w.real = this->w;
	*(in_data + offset + 0) = (u_w.base >> (8 * 0)) & 0xFF;
	*(in_data + offset + 1) = (u_w.base >> (8 * 1)) & 0xFF;
	*(in_data + offset + 2) = (u_w.base >> (8 * 2)) & 0xFF;
	*(in_data + offset + 3) = (u_w.base >> (8 * 3)) & 0xFF;
	offset += sizeof(this->w);
	return offset;
}
ros::MsgSz Quaternion32::deserialize(uint8_t *out_data)
{
	ros::MsgSz offset = 0;
	union {
		float real;
		uint32_t base;
	} u_x;
	u_x.base = 0;
	u_x.base |= ((typeof(u_x.base)) (*(out_data + offset + 0))) << (8 * 0);
	u_x.base |= ((typeof(u_x.base)) (*(out_data + offset + 1))) << (8 * 1);
	u_x.base |= ((typeof(u_x.base)) (*(out_data + offset + 2))) << (8 * 2);
	u_x.base |= ((typeof(u_x.base)) (*(out_data + offset + 3))) << (8 * 3);
	this->x = u_x.real;
	offset += sizeof(this->x);
	union {
		float real;
		uint32_t base;
	} u_y;
	u_y.base = 0;
	u_y.base |= ((typeof(u_y.base)) (*(out_data + offset + 0))) << (8 * 0);
	u_y.base |= ((typeof(u_y.base)) (*(out_data + offset + 1))) << (8 * 1);
	u_y.base |= ((typeof(u_y.base)) (*(out_data + offset + 2))) << (8 * 2);
	u_y.base |= ((typeof(u_y.base)) (*(out_data + offset + 3))) << (8 * 3);
	this->y = u_y.real;
	offset += sizeof(this->y);
	union {
		float real;
		uint32_t base;
	} u_z;
	u_z.base = 0;
	u_z.base |= ((typeof(u_z.base)) (*(out_data + offset + 0))) << (8 * 0);
	u_z.base |= ((typeof(u_z.base)) (*(out_data + offset + 1))) << (8 * 1);
	u_z.base |= ((typeof(u_z.base)) (*(out_data + offset + 2))) << (8 * 2);
	u_z.base |= ((typeof(u_z.base)) (*(out_data + offset + 3))) << (8 * 3);
	this->z = u_z.real;
	offset += sizeof(this->z);
	union {
		float real;
		uint32_t base;
	} u_w;
	u_w.base = 0;
	u_w.base |= ((typeof(u_w.base)) (*(out_data + offset + 0))) << (8 * 0);
	u_w.base |= ((typeof(u_w.base)) (*(out_data + offset + 1))) << (8 * 1);
	u_w.base |= ((typeof(u_w.base)) (*(out_data + offset + 2))) << (8 * 2);
	u_w.base |= ((typeof(u_w.base)) (*(out_data + offset + 3))) << (8 * 3);
	this->w = u_w.real;
	offset += sizeof(this->w);
	return offset;
}
ros::MsgSz Quaternion32::bytes()
{
	ros::MsgSz msgSize = 0;
	msgSize += sizeof(float);
	msgSize += sizeof(float);
	msgSize += sizeof(float);
	msgSize += sizeof(float);
	return msgSize;
}
