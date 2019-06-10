package it.lab.iot.device.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import it.lab.iot.device.exception.InvalidDeviceIdException;
import it.lab.iot.device.exception.NoDeviceFoundException;
import it.lab.iot.device.exception.SubscribeInputEmptyException;
import it.lab.iot.device.mapper.DeviceDTOToDevice;
import it.lab.iot.device.mapper.DeviceToDTO;
import it.lab.iot.device.mapper.DeviceToDeviceSensorsDTO;
import it.lab.iot.device.repository.IDeviceRepository;
import it.lab.iot.device.repository.IDeviceSensorRepository;
import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.dto.DeviceSensorsDTO;
import it.lab.iot.dto.SensorDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.sensor.entity.Device;
import it.lab.iot.sensor.entity.DeviceSensor;
import it.lab.iot.sensor.entity.Sensor;
import it.lab.iot.sensor.exception.InvalidSensorIdException;
import it.lab.iot.sensor.mapper.SensorDTOToSensor;
import it.lab.iot.sensor.repository.ISensorRepository;
import it.lab.iot.sensor.service.ISensorService;

@Service
public class DeviceService implements IDeviceService {

	private static final Logger logger = LoggerFactory.getLogger(DeviceService.class);
	
	@Autowired
	private IDeviceRepository deviceRepository;
	@Autowired
	private ISensorRepository sensorRepository;
	@Autowired
	private IDeviceSensorRepository deviceSensorRepository;
	
	@Override
	public List<DeviceDTO> getAllDeviceAvailable() throws BaseException {		
		List<Device> devices = (List<Device>) deviceRepository.findAll();
		
		if(devices == null || devices.isEmpty()) throw new NoDeviceFoundException();
		
		List<DeviceDTO> devicesDTO = new ArrayList<DeviceDTO>();
		for(Device device : devices) {
			devicesDTO.add(DeviceToDTO.map(device));
		}
		
		return devicesDTO;
	}
	
	@Override
	public DeviceSensorsDTO getAllDeviceSensors(Integer deviceId) throws BaseException {
		if(deviceId == null) throw new InvalidDeviceIdException();
		
		Optional<Device> device = deviceRepository.findById(deviceId);
		
		if(!device.isPresent()) throw new NoDeviceFoundException(deviceId);
		
		return DeviceToDeviceSensorsDTO.map(device.get());
	}

	@Override
	public DeviceDTO subscribe(DeviceSensorsDTO deviceDTO) throws BaseException {
		if(deviceDTO.getDevice() == null || deviceDTO.getDevice().getDeviceName() == null || deviceDTO.getDevice().getDeviceName().isEmpty()) 
			throw new SubscribeInputEmptyException();
		
		Integer deviceId = null;
		
		//Aggiungo un nuovo device solamente se il device id è nullo o uguale a -1 (cioè non inizializzato)
		if(deviceDTO.getDevice().getDeviceId() == null || new Integer(-1).equals(deviceDTO.getDevice().getDeviceId())) {
			deviceId = this.addNewDevice(deviceDTO);
		}
		//Altrimenti refresho il device rendendolo visibile per altri N minuti
		else {
			Optional<Device> device = deviceRepository.findById(deviceDTO.getDevice().getDeviceId());
			
			if(device.isPresent()) {
				//Salvo direttamente poichè al salvataggio si aggiorna la data con il current time
				deviceRepository.save(device.get());
				deviceId = device.get().getId();
			}
			else {
				throw new InvalidDeviceIdException();
			}
		}
		
		DeviceDTO response = new DeviceDTO();
		
		response.setDeviceId(deviceId);
		
		return response;
	}
	
	private Integer addNewDevice(DeviceSensorsDTO deviceDTO) throws BaseException{
		Device device = DeviceDTOToDevice.map(deviceDTO.getDevice());
		
		device = deviceRepository.save(device);
		
		for(SensorDTO sensorDTO : deviceDTO.getSensors()) {
			if(sensorDTO.getSensorId() == null || sensorDTO.getSensorId().isEmpty()) throw new InvalidSensorIdException();
			
			Optional<Sensor> sensor = sensorRepository.findById(sensorDTO.getSensorId());
			
			DeviceSensor deviceSensor = new DeviceSensor();
			deviceSensor.setSubscriber(device);

			if(sensor.isPresent()) {
				deviceSensor.setSensor(sensor.get());
			}
			else {
				Sensor sensorToAdd = SensorDTOToSensor.map(sensorDTO);
				sensorToAdd = sensorRepository.save(sensorToAdd);
				
				deviceSensor.setSensor(sensorToAdd);
				
			}
			
			deviceSensor = deviceSensorRepository.save(deviceSensor);
		}
		
		
		return device.getId();
	}

	@Override
	public void deleteSubscribedDevice(Integer deviceId) throws BaseException {
		if(deviceId == null) throw new InvalidDeviceIdException();
		
		Optional<Device> device = deviceRepository.findById(deviceId);
		
		if(!device.isPresent()) throw new NoDeviceFoundException();
		
		deviceRepository.delete(device.get());
		
	}

}
