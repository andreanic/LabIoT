package it.lab.iot.sensor.service;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Optional;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandler;
import org.springframework.stereotype.Service;
import org.springframework.util.concurrent.ListenableFuture;
import org.springframework.web.socket.client.WebSocketClient;
import org.springframework.web.socket.client.standard.StandardWebSocketClient;
import org.springframework.web.socket.messaging.WebSocketStompClient;
import org.springframework.web.socket.sockjs.client.SockJsClient;
import org.springframework.web.socket.sockjs.client.Transport;
import org.springframework.web.socket.sockjs.client.WebSocketTransport;

import com.fasterxml.jackson.databind.ObjectMapper;

import it.lab.iot.device.exception.NoDeviceFoundException;
import it.lab.iot.device.exception.WebSocketException;
import it.lab.iot.device.repository.IDeviceRepository;
import it.lab.iot.dto.SensorDTO;
import it.lab.iot.dto.SensorDevicesDTO;
import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.security.WebSocketSessionHandler;
import it.lab.iot.sensor.entity.Device;
import it.lab.iot.sensor.entity.Sensor;
import it.lab.iot.sensor.entity.SensorValues;
import it.lab.iot.sensor.exception.InvalidSensorIdException;
import it.lab.iot.sensor.exception.InvalidSensorRecordException;
import it.lab.iot.sensor.exception.NoSensorFoundException;
import it.lab.iot.sensor.exception.NoValuesFoundException;
import it.lab.iot.sensor.mapper.SensorToDTO;
import it.lab.iot.sensor.mapper.SensorToSensorDevicesDTO;
import it.lab.iot.sensor.mapper.SensorValueDTOToSensorValue;
import it.lab.iot.sensor.mapper.SensorValueToDTO;
import it.lab.iot.sensor.repository.ISensorRepository;
import it.lab.iot.sensor.repository.ISensorValuesRepository;
import it.lab.iot.websocket.service.IWebSocketService;

@Service
public class SensorService implements ISensorService  {

	private static final Logger logger = LoggerFactory.getLogger(SensorService.class);
	
	@Autowired
	private ISensorValuesRepository sensorValuesRepository;
	@Autowired
	private ISensorRepository sensorRepository;
	@Autowired
	private IDeviceRepository deviceRepository;
	@Autowired
	private IWebSocketService webSocketService;
	
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
	public SensorValueDTO createValue(SensorValueDTO dto) throws BaseException {
		if(dto == null || dto.getSensorId() == null || dto.getSensorId().isEmpty() || dto.getDeviceId() == null) throw new InvalidSensorRecordException();
		
		Optional<Sensor> sensor = sensorRepository.findById(dto.getSensorId());
		
		if(!sensor.isPresent()) throw new NoSensorFoundException(dto.getSensorId());
		
		Optional<Device> device = deviceRepository.findById(dto.getDeviceId());
		
		if(!device.isPresent()) throw new NoDeviceFoundException(dto.getDeviceId());
		
		SensorValues sensorValue = SensorValueDTOToSensorValue.map(dto);
		sensorValue.setSensor(sensor.get());
		sensorValue.setSubscriber(device.get());
		
		sensorValue = this.sensorValuesRepository.save(sensorValue);	
		
		dto = SensorValueToDTO.map(sensorValue);
		
		try{
			webSocketService.sendMessage(dto);
		}catch(BaseException e) {
			logger.warn(e.getHrMessage());
		}
		
		return dto;
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
