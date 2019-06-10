package it.lab.iot.sensor.mapper;

import it.lab.iot.dto.SensorDTO;
import it.lab.iot.sensor.entity.Sensor;

public class SensorToDTO {
	private static final String ANALOGICO = "Analogico";
	private static final String DIGITALE = "Digitale";
	
	public static SensorDTO map(Sensor sensor) {
		SensorDTO dto = new SensorDTO();
		
		dto.setSensorId(sensor.getId());
		dto.setSensorName(sensor.getSensorName());
		dto.setDescription(sensor.getDescription());
		dto.setType(sensor.getIsDigital() ? DIGITALE : ANALOGICO);
		dto.setUom(sensor.getUom());
		dto.setUrl(sensor.getSensorUrl());
		
		return dto;
	}
}
