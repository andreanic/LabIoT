package it.lab.iot.device.exception;

import it.lab.iot.exception.BaseException;

public class InvalidStartStopTypeException extends BaseException {
	public InvalidStartStopTypeException() {
		this.hrMessage = "Operazione di start/stop non valida";
	}
}
