// license:???
// copyright-holders:???
/*********************************************************************

    midiinport.h

    MIDI In port - glues the image device to the pluggable midi port

*********************************************************************/

#ifndef _MIDIINPORT_H_
#define _MIDIINPORT_H_

#include "midi.h"
#include "imagedev/midiin.h"

class midiin_port_device : public device_t,
	public device_midi_port_interface
{
public:
	midiin_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE_LINE_MEMBER( read ) { output_rxd(state); }

protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start() { m_owner = dynamic_cast<midi_port_device *>(owner()); }
	virtual void device_reset() { }

private:
	required_device<midiin_device> m_midiin;
};

extern const device_type MIDIIN_PORT;

#endif
