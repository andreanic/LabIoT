package it.lab.iot.sensor.mapper;

import java.util.Date;
import java.sql.Timestamp;

import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.sensor.entity.SensorValues;

public class SensorValueDTOToSensorValue {
	public static SensorValues map(SensorValueDTO dto) {
		SensorValues sensorValue = new SensorValues();
		sensorValue.setValore(dto.getValue());
		sensorValue.setDataCampione(new Timestamp(new Date().getTime()));
		sensorValue.setIsAlert(dto.getIsAlert() != null ? dto.getIsAlert() : false);
		
		return sensorValue;
	}
}
