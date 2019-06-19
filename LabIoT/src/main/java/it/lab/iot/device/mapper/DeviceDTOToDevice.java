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
		device.setDescription(dto.getDescription());
		device.setEnabled(Boolean.TRUE);
		device.setRegistered(new Date());
		device.setLastUpdate(new Date());
		
		return device;
	}
}
