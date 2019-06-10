package it.lab.iot.sensor.mapper;

import java.util.ArrayList;
import java.util.List;

import it.lab.iot.device.exception.NoDeviceFoundException;
import it.lab.iot.device.mapper.DeviceToDTO;
import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.dto.SensorDevicesDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.sensor.entity.DeviceSensor;
import it.lab.iot.sensor.entity.Sensor;
import it.lab.iot.sensor.exception.NoSensorFoundException;

public class SensorToSensorDevicesDTO {
	public static SensorDevicesDTO map(Sensor sensor) throws BaseException {
		SensorDevicesDTO dto = new SensorDevicesDTO();
		
		dto.setSensor(SensorToDTO.map(sensor));
		
		if(sensor.getDeviceSensors() == null || sensor.getDeviceSensors().isEmpty()) throw new NoDeviceFoundException();
		
		List<DeviceDTO> devicesDTO = new ArrayList<DeviceDTO>();
		
		for(DeviceSensor deviceSensor : sensor.getDeviceSensors()) {
			devicesDTO.add(DeviceToDTO.map(deviceSensor.getSubscriber()));
		}
		
		dto.setDevices(devicesDTO);
		
		return dto;
	}
}
