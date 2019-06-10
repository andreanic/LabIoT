package it.lab.iot.sensor.exception;

import it.lab.iot.exception.BaseException;

public class InvalidSensorIdException extends BaseException{
	public InvalidSensorIdException() {
		this.hrMessage = "Ricevuto un sensor id errato";
	}
}
