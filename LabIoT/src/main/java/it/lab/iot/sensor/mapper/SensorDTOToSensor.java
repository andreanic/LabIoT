package it.lab.iot.sensor.mapper;

import it.lab.iot.dto.SensorDTO;
import it.lab.iot.exception.BaseException;
import it.lab.iot.sensor.entity.Sensor;
import it.lab.iot.sensor.exception.InvalidSensorIdException;

public class SensorDTOToSensor {
	private static final String DIGITALE = "Digitale";
	
	public static Sensor map(SensorDTO dto) throws BaseException{
		if(dto.getSensorId() == null || dto.getSensorId().isEmpty()) throw new InvalidSensorIdException();
		
		Sensor sensor = new Sensor();
		
		sensor.setId(dto.getSensorId());
		sensor.setSensorName(dto.getSensorName());
		sensor.setDescription(dto.getDescription());
		sensor.setIsDigital(DIGITALE.equals(dto.getType()));
		sensor.setSensorUrl(dto.getUrl());
		sensor.setUom(dto.getUom());

		return sensor;
	}
}
