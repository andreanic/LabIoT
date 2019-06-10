package it.lab.iot.sensor.exception;

import it.lab.iot.exception.BaseException;

public class NoSensorFoundException extends BaseException {
	public NoSensorFoundException(String sensorId) {
		this.hrMessage = "Nessun sensore trovato con id " + sensorId;
	}
	
	public NoSensorFoundException() {
		this.hrMessage = "Nessun sensore trovato";
	}
}
