package it.lab.iot.device.exception;

import it.lab.iot.exception.BaseException;

public class InvalidDeviceIdException extends BaseException {
	public InvalidDeviceIdException() {
		this.hrMessage = "Ricevuto un device id errato";
	}
}
