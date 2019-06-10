package it.lab.iot.device.exception;

import it.lab.iot.exception.BaseException;

public class NoDeviceFoundException extends BaseException{
	public NoDeviceFoundException() {
		this.hrMessage = "Nessun device trovato";
	}
	
	public NoDeviceFoundException(Integer deviceId) {
		this.hrMessage = "Nessun device trovato con id " + deviceId;
	}
}
