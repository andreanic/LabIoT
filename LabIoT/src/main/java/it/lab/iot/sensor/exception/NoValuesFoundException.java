package it.lab.iot.sensor.exception;

import it.lab.iot.exception.BaseException;

public class NoValuesFoundException extends BaseException {
	public NoValuesFoundException(String sensorName) {
		this.hrMessage = "Nessun valore trovato per il sensore: " + sensorName;
	}
	
	public NoValuesFoundException(String sensorId, Integer deviceId) {
		this.hrMessage = "Nessun valore trovato per il sensore " + sensorId + " del device " + deviceId;
	}
}
