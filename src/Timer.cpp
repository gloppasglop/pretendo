
#include "Timer.h"

namespace nes {
namespace apu {

//------------------------------------------------------------------------------
// Name: reset
//------------------------------------------------------------------------------
void Timer::reset() {
	timer_ = frequency;
}

}
}
