
#include "Noise.h"

namespace nes {
namespace apu {

namespace {

// NTSC period table
const uint16_t frequency_table[16] = {
	4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068};

}

//------------------------------------------------------------------------------
// Name: set_enabled
//------------------------------------------------------------------------------
void Noise::set_enabled(bool value) {
	if (value) {
		enable();
	} else {
		disable();
	}
}

//------------------------------------------------------------------------------
// Name: enable
//------------------------------------------------------------------------------
void Noise::enable() {
	enabled_ = true;
}

//------------------------------------------------------------------------------
// Name: disable
//------------------------------------------------------------------------------
void Noise::disable() {
	enabled_ = false;
	length_counter.clear();
}

//------------------------------------------------------------------------------
// Name: write_reg0
//------------------------------------------------------------------------------
void Noise::write_reg0(uint8_t value) {

	if (value & 0x20) {
		length_counter.halt();
	} else {
		length_counter.resume();
	}

	envelope.set_control(value);
}

//------------------------------------------------------------------------------
// Name: write_reg2
//------------------------------------------------------------------------------
void Noise::write_reg2(uint8_t value) {

	lfsr_.set_mode(value & 0x80);
	timer_.frequency = frequency_table[value & 0x0f];
}

//------------------------------------------------------------------------------
// Name: write_reg3
//------------------------------------------------------------------------------
void Noise::write_reg3(uint8_t value) {

	if (enabled_) {
		length_counter.load((value >> 3) & 0x1f);
	}

	envelope.start();
}

//------------------------------------------------------------------------------
// Name: enabled
//------------------------------------------------------------------------------
bool Noise::enabled() const {
	return enabled_;
}

//------------------------------------------------------------------------------
// Name: tick
//------------------------------------------------------------------------------
void Noise::tick() {

	timer_.tick([this]() {
		lfsr_.clock();
	});
}

//------------------------------------------------------------------------------
// Name: output
//------------------------------------------------------------------------------
uint8_t Noise::output() const {
	if (length_counter.value() == 0 || ((lfsr_.value() & 1) == 0)) {
		return 0;
	} else {
		return envelope.volume();
	}
}

}
}
