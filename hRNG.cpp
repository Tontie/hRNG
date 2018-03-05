/* 
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

You should have received a copy of the GNU General Public License
along with this library.  If not, see <http://www.gnu.org/licenses/>

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#include "hRNG.h"
using namespace hRNG;

		void funk::init(){
			RNG::TASKS_START::en::write(1);
			RNG::CONFIG::bias::write(1);
			RNG::INTENCLR::dis::write(1);
		};

		uint8_t funk::Randy(void){
			RNG::INTENSET::en::write(1);
			RNG::EVENTS_VALRDY::rdy::read();
			while (!RNG::EVENTS_VALRDY::rdy::read()){ //wait for new value? this might get fuckity. Not positive if/when the event register refreshes to 0?
				;
			};
			uint8_t num = RNG::VALUE::val::read();
			RNG::INTENCLR::dis::write(1);
			return(num);
		};

		void funk::stop(){
			RNG::INTENCLR::dis::write(1);
			RNG::EVENTS_VALRDY::rdy::read();
			RNG::CONFIG::bias::write(0);
			RNG::TASKS_STOP::en::write(1);
		};
	