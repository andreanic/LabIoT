package it.lab.iot.sensor.service;

import java.util.List;

import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.dto.DeviceSensorsDTO;
import it.lab.iot.dto.SensorDTO;
import it.lab.iot.dto.SensorDevicesDTO;
import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.sensor.entity.SensorValues;

public interface ISensorService {
	public List<SensorValueDTO> getValues() throws BaseException;
	public List<SensorValueDTO> getLast20ValuesBySensorId(String sensorId) throws BaseException;
	public List<SensorValueDTO> getLast20ValuesBySensorIdAndDeviceId(String sensorId, Integer deviceId) throws BaseException;
	public List<SensorDTO> getAllSensorsAvailable() throws BaseException;
	public SensorDevicesDTO getAllSensorDevices(String sensorId) throws BaseException;
	public SensorValueDTO createValue(SensorValueDTO sensorValue) throws BaseException;
	public void deleteOldValue(String sensorName) throws BaseException;
}
