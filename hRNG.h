/*    	
  	This library is cobbled together based off a paper written by
	Ken Smith (kgsmith@gmail.com) in January 2010 called "C++
	Hardware Register Access Redux".
	
	
	
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


#ifndef hRNG_H
#define hRNG_H

//this library is compatible both with Arduino <=0023 and Arduino >=100
#if defined(ARDUINO) && (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <bluefruit.h>

namespace hRNG {

	//public class shit
	class funk{
		public:
			funk();
			uint8_t Randy(void);
			void init();
			void stop();
	};
	//struct template

	template
		<
		unsigned long address,
		unsigned mask,
		unsigned offset,
	class mutability_policy
		>
	struct reg_t
	{
		static void write(unsigned value)
		{
			mutability_policy::write(
				reinterpret_cast<volatile unsigned*>(address),
				mask,
				offset,
				value
				);
		}
		static unsigned read()
		{
			return mutability_policy::read(
				reinterpret_cast<volatile unsigned*>(address),
				mask,
				offset
				);
		}
	};

	//Write only register field

	struct wo_t
	{
		static void write(
		volatile unsigned* reg,
		unsigned mask,
		unsigned offset,
		unsigned value
		)
		{
			*reg = (value & mask) << offset;
		}
	};

	//Read only register field

	struct ro_t
	{
		static unsigned read(
		volatile unsigned* reg,
		unsigned mask,
		unsigned offset
		)
		{
			return (*reg >> offset) & mask;
		}
	};

	//Read/Write register field

	struct rw_t : public ro_t
	{
		static void write(
		volatile unsigned* reg,
		unsigned mask,
		unsigned offset,
		unsigned value
		)
		{
			*reg =
				(*reg & ~(mask << offset))
				|
				((value & mask) << offset);
		}
	};

	/******************************************************************************
     * The below schemata will accept literally any of the registers in the periph.
	 * typedef reg_t<BASE, size of data, LSB, read/write?> call variable;
	 * usage>> RNG::TASKS_START::en::write(1);
	 * or>> bool ready = RNG::EVENTS_VALRDY::rdy::read();
	 *******************************************************************************/

	namespace RNG
	{
		namespace TASKS_START
		{
			typedef reg_t<0x4000D000, 0x1, 0, wo_t> en;
		}
		namespace TASKS_STOP
		{
			typedef reg_t<0x4000D004, 0x1, 0, wo_t> en;
		}
		namespace EVENTS_VALRDY
		{
			typedef reg_t<0x4000D100, 0x1, 0, rw_t> rdy;
		}
		namespace SHORTS
		{
			typedef reg_t<0x4000D200, 0x1, 0, rw_t> en;
		}
		namespace INTENSET
		{
			typedef reg_t<0x4000D304, 0x1, 0, rw_t> en;
		}
		namespace INTENCLR
		{
			typedef reg_t<0x4000D308, 0x1, 0, rw_t> dis;
		}
		namespace CONFIG
		{
			typedef reg_t<0x4000D504, 0x1, 0, rw_t> bias;
		}
		namespace VALUE
		{
			typedef reg_t<0x4000D508, 0xff, 0, ro_t> val;
		}
	}

}
#endif
