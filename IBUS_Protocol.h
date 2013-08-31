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
#ifndef IBUS_Protocol_H
#define IBUS_Protocol_H
#include <IBUS_Frame.h>

class IBUS_Protocol
{
	public:
		IBUS_Protocol(void (*txfunction)(uint8_t));
		~IBUS_Protocol();
		int sendFrame(IBUS_Frame *frame);
		void feed(uint8_t byte);
		IBUS_Frame* getFrame();

	private:
		void _parseInput(uint8_t byte);
		void _onInputMismatch();
		
		bool _sending;
		uint8_t _rxbuffer[257];
		int _rxpos;
		uint8_t _txresponse;
		bool _txresponse_received;
		void (*_txfunction)(uint8_t);
		IBUS_Frame rxFrame;
		bool _frameComplete;
};

#endif
