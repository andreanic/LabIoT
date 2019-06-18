package it.lab.iot.mqtt.exception;

import it.lab.iot.exception.BaseException;

public class MqttConnectionFailException extends BaseException {
	public MqttConnectionFailException(String topic) {
		this.hrMessage = "Errore durante la connessione alla coda " + topic;
	}
}
