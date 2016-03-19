
#include "PulseAudio.h"
#include <iostream>

//------------------------------------------------------------------------------
// Name: PulseAudio
//------------------------------------------------------------------------------
PulseAudio::PulseAudio() {
	std::cout << "[PulseAudio::PulseAudio]" << std::endl;
	
    static const pa_sample_spec ss = { 
		PA_SAMPLE_U8,
		44100,
		1
	};
	

    int error;

    // Create a new playback stream
    if (!(stream_ = pa_simple_new(NULL, "pretendo", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %stream_\n", pa_strerror(error));
        abort();
    }

}

//------------------------------------------------------------------------------
// Name: ~PulseAudio
//-------------------------------------------------------------------
PulseAudio::~PulseAudio() {
    if (stream_) {
		pa_simple_free(stream_);
	}
}

//------------------------------------------------------------------------------
// Name: write
//------------------------------------------------------------------------------
void PulseAudio::write(const void *p, size_t n) {
	
	int error;
    if (pa_simple_write(stream_, p, n, &error) < 0) {
        fprintf(stderr, __FILE__": pa_simple_write() failed: %stream_\n", pa_strerror(error));
		abort();		
    }	
}

//------------------------------------------------------------------------------
// Name: start
//------------------------------------------------------------------------------
void PulseAudio::start() {
}

//------------------------------------------------------------------------------
// Name: stop
//------------------------------------------------------------------------------
void PulseAudio::stop() {
}