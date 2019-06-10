package it.lab.iot.device.exception;

import it.lab.iot.exception.BaseException;

public class SubscribeInputEmptyException extends BaseException {
	public SubscribeInputEmptyException() {
		this.hrMessage = "Uno o più campi obbligatori risultano vuoti";
	}
}
