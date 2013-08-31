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
#ifndef IBUS_Frame_H
#define IBUS_Frame_H

#include <stdint.h>

class IBUS_Frame
{
	public:
		IBUS_Frame() {}
		IBUS_Frame(uint8_t from, uint8_t to, uint8_t len, uint8_t* data);
		IBUS_Frame(uint8_t* src, int offset, int len);
		~IBUS_Frame();
		uint8_t from();
		uint8_t to();
		uint8_t len();
		uint8_t* data();
		uint8_t* packet();
		
		uint8_t* _packet;
	private:
};

#endif
