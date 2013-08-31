/*
  IBus protocol library V1.0
  2013 Copyright (c) Tim Otto <tim.otto@ubergrund.de>  All right reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "Arduino.h"
#include "IBUS_Frame.h"

IBUS_Frame::IBUS_Frame(uint8_t from, uint8_t to, uint8_t len, uint8_t* data) 
{
	if (len > 253)
		len = 253; // TODO throw
	
	int packetLength = len + 4;
	_packet = (uint8_t*)malloc(packetLength);
	_packet[0] = from;
	_packet[1] = len + 2;
	_packet[2] = to;
	memcpy(&_packet[3], data, len);
}

IBUS_Frame::IBUS_Frame(uint8_t* src, int offset, int len)
{
	memcpy(_packet+offset, src, len);
}

IBUS_Frame::~IBUS_Frame()
{
	free(_packet);
}


uint8_t IBUS_Frame::from()
{
	return _packet[0];
}

uint8_t IBUS_Frame::to()
{
	return _packet[2];
}

uint8_t IBUS_Frame::len()
{
	return _packet[1] - 2;
}

uint8_t* IBUS_Frame::data()
{
	return &_packet[3];
}

uint8_t* IBUS_Frame::packet()
{
	return _packet;
}
