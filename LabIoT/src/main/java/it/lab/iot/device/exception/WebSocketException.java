package it.lab.iot.device.exception;

import it.lab.iot.exception.BaseException;

public class WebSocketException extends BaseException{
	public WebSocketException() {
		this.hrMessage = "Errore durante l'invio del messaggio alla WebSocket";
	}
}
