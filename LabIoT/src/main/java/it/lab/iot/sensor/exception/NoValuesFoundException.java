package it.lab.iot.sensor.exception;

import it.lab.iot.exception.BaseException;

public class NoValuesFoundException extends BaseException {
	public NoValuesFoundException(String sensorName) {
		this.hrMessage = "Nessun valore trovato per il sensore: " + sensorName;
	}
}
