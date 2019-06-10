package it.lab.iot.sensor.mapper;

import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.sensor.entity.SensorValues;

public class SensorValueToDTO {
	public static SensorValueDTO map(SensorValues sensorValue) {
		SensorValueDTO dto = new SensorValueDTO();
		
		dto.setDataInserimento(sensorValue.getDataCampione());
		dto.setSensorName(sensorValue.getSensor().getSensorName());
		dto.setSensorId(sensorValue.getSensor().getId());
		dto.setDeviceId(sensorValue.getSubscriber().getId());
		dto.setValue(sensorValue.getValore());
		dto.setIsAlert(sensorValue.getIsAlert());
		
		return dto;
	}
}
