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
#include <IBUS_Protocol.h>

IBUS_Protocol::IBUS_Protocol(void (*txfunction)(uint8_t))
 : _frameComplete(false)
{
	_txfunction = txfunction;
	_sending = false;
	_rxpos = 0;
	rxFrame._packet = _rxbuffer;
}

IBUS_Protocol::~IBUS_Protocol() {
}

int IBUS_Protocol::sendFrame(IBUS_Frame *frame)
{
	// TODO wait for clear path / no rx since x ms
	uint8_t* packet = frame->packet();
	uint8_t chk;
	int packetLength = frame->len() + 2;
	for(int i=0;i<packetLength;i++) {
		// set response to a different than expected value
		_txresponse = 0x7f ^ packet[i];
		_txresponse_received = false;
		// hardware send
		_txfunction(packet[i]);
		// wait for the sent byte
		//while(!_txresponse_received){
			// TODO timeout
			// TODO yield
		//	;
		//}
		
		// check response
		//if (_txresponse != packet[i]) {
		//	// overwritten on bus, abort
		//	return 1;
		//}
	}
	return 0;
}

void IBUS_Protocol::feed(uint8_t byte)
{
	if(_sending == true) {
		_txresponse = byte;
		_txresponse_received = true;
		
		// TODO continue in send function before executing on frame received callback
	}
	
	_parseInput(byte);
}


IBUS_Frame* IBUS_Protocol::getFrame()
{
	if (_frameComplete) {
		_frameComplete = false;
		return &rxFrame;
	}
	return 0;
}

void IBUS_Protocol::_parseInput(uint8_t byte)
{
	_rxbuffer[_rxpos++] = byte;
	
	if (_rxpos >= 2) {
		// ll byte is present, message length is known
		
		int expectedLength = _rxbuffer[1] + 2;
		if (_rxpos >= expectedLength) {
			// message seems to be complete
			
			int ckPos = expectedLength-1;
			uint8_t myCk = 0;
			for(int i=0;i<ckPos;i++) {
				myCk ^= _rxbuffer[i];
			}
			
			if (myCk == _rxbuffer[ckPos]) {
				// ck byte matches calculated XOR checksum
				
				// TODO store received frame
				_frameComplete = true;
				
				_rxpos = 0;
			} else {
				_onInputMismatch();
			}
		}
	}
	
	// buffer overflow
	if (_rxpos == sizeof(_rxbuffer))
		_onInputMismatch();
}

void IBUS_Protocol::_onInputMismatch()
{
	int oldLen = _rxpos;
	_rxpos = 0;
	// feed buffer with first byte discarded
	for (int i=1;i<oldLen;i++)
		_parseInput(_rxbuffer[i]);
	// TODO are there recursive implications here?
}
