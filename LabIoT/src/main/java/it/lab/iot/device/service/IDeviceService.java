package it.lab.iot.device.service;

import java.util.List;

import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.dto.DeviceSensorsDTO;
import it.lab.iot.exception.BaseException;

public interface IDeviceService {
	public static final String START = "start";
	public static final String STOP = "stop";
	public List<DeviceDTO> getAllDeviceAvailable() throws BaseException;
	public DeviceSensorsDTO getAllDeviceSensors(Integer deviceId) throws BaseException;
	public DeviceDTO subscribe(DeviceSensorsDTO device) throws BaseException;
	public String deleteSubscribedDevice(Integer deviceId) throws BaseException;
	public String startStopMonitoring(DeviceDTO device, String type) throws BaseException;
}
