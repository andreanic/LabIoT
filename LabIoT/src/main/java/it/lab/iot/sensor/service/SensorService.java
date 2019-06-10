package it.lab.iot.sensor.service;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Optional;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import it.lab.iot.device.exception.NoDeviceFoundException;
import it.lab.iot.device.repository.IDeviceRepository;
import it.lab.iot.dto.SensorDTO;
import it.lab.iot.dto.SensorDevicesDTO;
import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.sensor.entity.Device;
import it.lab.iot.sensor.entity.Sensor;
import it.lab.iot.sensor.entity.SensorValues;
import it.lab.iot.sensor.exception.InvalidSensorIdException;
import it.lab.iot.sensor.exception.InvalidSensorRecordException;
import it.lab.iot.sensor.exception.NoSensorFoundException;
import it.lab.iot.sensor.exception.NoValuesFoundException;
import it.lab.iot.sensor.mapper.SensorToDTO;
import it.lab.iot.sensor.mapper.SensorToSensorDevicesDTO;
import it.lab.iot.sensor.mapper.SensorValueToDTO;
import it.lab.iot.sensor.repository.ISensorRepository;
import it.lab.iot.sensor.repository.ISensorValuesRepository;

@Service
public class SensorService implements ISensorService  {

	private static final Logger logger = LoggerFactory.getLogger(SensorService.class);
	
	@Autowired
	private ISensorValuesRepository sensorValuesRepository;
	@Autowired
	private ISensorRepository sensorRepository;
	@Autowired
	private IDeviceRepository deviceRepository;
	
	@Override
	public List<SensorValueDTO> getValues() throws BaseException {
		List<SensorValueDTO> values = new ArrayList<SensorValueDTO>();
		
		List<Sensor> sensors = (List<Sensor>) sensorRepository.findAll();
		
		for(Sensor sensor : sensors) {
			try {
				SensorValueDTO value = getLastSensorValueById(sensor.getId());
				values.add(value);
			}catch(BaseException ex) {
				logger.warn(ex.getHrMessage());
			}
		}
		
		return values;
	}
	
	private SensorValueDTO getLastSensorValueById(String sensorId) throws BaseException{
		if(sensorId == null || sensorId.isEmpty()) throw new InvalidSensorIdException();
		
		SensorValues sensor = sensorValuesRepository.findFirstBySensorIdOrderByDataCampioneDesc(sensorId);
		
		if(sensor == null) throw new NoValuesFoundException(sensorId);
		
		return SensorValueToDTO.map(sensor);
		
	}

	@Override
	public List<SensorValueDTO> getLast20ValuesBySensorId(String sensorId) throws BaseException {
		if(sensorId == null || sensorId.isEmpty()) throw new InvalidSensorIdException();
		
		List<SensorValues> values = sensorValuesRepository.findFirst20BySensorIdOrderByDataCampioneDesc(sensorId);
		List<SensorValueDTO> sensorValues = new ArrayList<SensorValueDTO>();
		if(values != null && !values.isEmpty()) {
			for(SensorValues value : values) {
				sensorValues.add(SensorValueToDTO.map(value));
			}
		}
		else {
			throw new NoValuesFoundException(sensorId);
		}
		
		return sensorValues;
	}
	
	@Override
	public void createValue(SensorValueDTO sensorValue) throws BaseException {
		if(sensorValue == null || sensorValue.getSensorId() == null || sensorValue.getSensorId().isEmpty()) throw new InvalidSensorRecordException();
		
		Optional<Sensor> sensor = sensorRepository.findById(sensorValue.getSensorId());
		
		if(!sensor.isPresent()) throw new NoSensorFoundException(sensorValue.getSensorId());
		
		Optional<Device> device = deviceRepository.findById(sensorValue.getDeviceId());
		
		if(!device.isPresent()) throw new NoDeviceFoundException(sensorValue.getDeviceId());
		
		SensorValues sensorValueToAdd = new SensorValues();
		sensorValueToAdd.setSensor(sensor.get());
		sensorValueToAdd.setSubscriber(device.get());
		sensorValueToAdd.setValore(sensorValue.getValue());
		sensorValueToAdd.setIsAlert(sensorValue.getIsAlert() != null ? sensorValue.getIsAlert() : false);
		
		this.sensorValuesRepository.save(sensorValueToAdd);		
	}
	
	@Override
	public void deleteOldValue(String sensorId) throws BaseException {
		Calendar cal = Calendar.getInstance();
	    cal.add(Calendar.DATE, -1);
	    Date yesterday =  cal.getTime();
		
		List<SensorValues> oldRecords = sensorValuesRepository.findAllBySensorIdAndDataCampioneLessThan(sensorId, yesterday);
		
		if(oldRecords != null) {
			sensorValuesRepository.deleteAll(oldRecords);
		}
	}
	
	@Override
	public List<SensorDTO> getAllSensorsAvailable() throws BaseException {
		List<Sensor> sensors = (List<Sensor>) sensorRepository.findAll(); 
		
		if(sensors == null || sensors.isEmpty()) throw new NoSensorFoundException();
		
		List<SensorDTO> sensorsDTO = new ArrayList<SensorDTO>();
		for(Sensor sensor : sensors) {
			sensorsDTO.add(SensorToDTO.map(sensor));
		}
		
		return sensorsDTO;
	}


	@Override
	public SensorDevicesDTO getAllSensorDevices(String sensorId) throws BaseException {
		if(sensorId == null) throw new InvalidSensorIdException();
		
		Optional<Sensor> sensor = sensorRepository.findById(sensorId);
		
		if(!sensor.isPresent()) throw new NoSensorFoundException();
		
		return SensorToSensorDevicesDTO.map(sensor.get());
	}

	@Override
	public List<SensorValueDTO> getLast20ValuesBySensorIdAndDeviceId(String sensorId, Integer deviceId) throws BaseException {
		if(sensorId == null || sensorId.isEmpty()) throw new InvalidSensorIdException();
		
		List<SensorValues> values = sensorValuesRepository.findFirst20BySensorIdAndSubscriberIdOrderByDataCampioneDesc(sensorId, deviceId);
		
		List<SensorValueDTO> sensorValues = new ArrayList<SensorValueDTO>();
		if(values != null && !values.isEmpty()) {
			for(SensorValues value : values) {
				sensorValues.add(SensorValueToDTO.map(value));
			}
		}
		else {
			throw new NoValuesFoundException(sensorId, deviceId);
		}
		
		return sensorValues;
	}
}
