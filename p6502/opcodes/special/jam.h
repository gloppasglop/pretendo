
#ifndef JAM_20140417_H_
#define JAM_20140417_H_

//------------------------------------------------------------------------------
// Name: opcode_jam
// Desc: stall the CPU
//------------------------------------------------------------------------------
class opcode_jam {
public:
	void operator()() {
		execute();
	}

private:
	void execute() {
		switch(cycle_) {
		case 1:
			// make sure we spin forever
			--PC.raw;
			if(jam_handler_) {
				(*jam_handler_)();
			}
			OPCODE_COMPLETE;
			break;
		default:
			abort();
		}
	}
};

#endif

