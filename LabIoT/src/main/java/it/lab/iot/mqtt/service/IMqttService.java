package it.lab.iot.mqtt.service;

import org.eclipse.paho.client.mqttv3.MqttMessage;

import it.lab.iot.exception.BaseException;

public interface IMqttService {
	public void sendMessage(MqttMessage msg, String topic) throws BaseException;
}
