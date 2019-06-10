package it.lab.iot.sensor.exception;

import it.lab.iot.exception.BaseException;

public class InvalidSensorRecordException extends BaseException {
	public InvalidSensorRecordException() {
		this.hrMessage = "Impossibile creare un nuovo record";
	}
}
