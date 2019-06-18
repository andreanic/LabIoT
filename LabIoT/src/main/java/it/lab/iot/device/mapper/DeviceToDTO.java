package it.lab.iot.device.mapper;

import java.util.ArrayList;
import java.util.List;

import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.sensor.entity.Device;

public class DeviceToDTO {
	public static DeviceDTO map(Device device) {
		DeviceDTO dto = new DeviceDTO();
		
		dto.setDeviceName(device.getDeviceName());
		dto.setDeviceId(device.getId());
		dto.setLastUpdate(device.getLastUpdate());
		dto.setRegistered(device.getRegistered());
		dto.setDescription(device.getDescription());
		dto.setEnabled(device.getEnabled());
		
		return dto;
	}
	
	public static List<DeviceDTO> map(List<Device> devices) {
		List<DeviceDTO> dtos = new ArrayList<DeviceDTO>();
		
		for(Device device : devices) {
			dtos.add(DeviceToDTO.map(device));
		}
		
		return dtos;
	}
}
