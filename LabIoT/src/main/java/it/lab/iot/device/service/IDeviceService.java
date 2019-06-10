package it.lab.iot.device.service;

import java.util.List;

import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.dto.DeviceSensorsDTO;
import it.lab.iot.exception.BaseException;

public interface IDeviceService {
	public List<DeviceDTO> getAllDeviceAvailable() throws BaseException;
	public DeviceSensorsDTO getAllDeviceSensors(Integer deviceId) throws BaseException;
	public DeviceDTO subscribe(DeviceSensorsDTO device) throws BaseException;
	public void deleteSubscribedDevice(Integer deviceId) throws BaseException;
}
