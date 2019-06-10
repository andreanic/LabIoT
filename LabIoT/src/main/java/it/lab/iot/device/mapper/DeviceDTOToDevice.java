package it.lab.iot.device.mapper;


import java.sql.Timestamp;
import java.util.Date;

import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.sensor.entity.Device;

public class DeviceDTOToDevice {
	public static Device map(DeviceDTO dto) {
		Device device = new Device();
		
		device.setId(dto.getDeviceId());
		device.setDeviceName(dto.getDeviceName());
		device.setLastUpdate(new Timestamp(new Date().getTime()));
		
		return device;
	}
}
