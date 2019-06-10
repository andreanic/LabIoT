package it.lab.iot.device.mapper;

import java.util.ArrayList;
import java.util.List;

import it.lab.iot.dto.DeviceSensorsDTO;
import it.lab.iot.dto.SensorDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.sensor.entity.Device;
import it.lab.iot.sensor.entity.DeviceSensor;
import it.lab.iot.sensor.exception.NoSensorFoundException;
import it.lab.iot.sensor.mapper.SensorToDTO;

public class DeviceToDeviceSensorsDTO {
	public static DeviceSensorsDTO map(Device device) throws BaseException {
		DeviceSensorsDTO dto = new DeviceSensorsDTO();
		
		dto.setDevice(DeviceToDTO.map(device));
		
		List<SensorDTO> sensorsDTO = new ArrayList<SensorDTO>();
		
		if(device.getDeviceSensors() == null || device.getDeviceSensors().isEmpty()) throw new NoSensorFoundException();
		
		for(DeviceSensor deviceSensor : device.getDeviceSensors()) {
			sensorsDTO.add(SensorToDTO.map(deviceSensor.getSensor()));
		}
		
		dto.setSensors(sensorsDTO);
		
		return dto;
	}
}
