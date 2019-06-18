package it.lab.iot.mqtt.service;

import java.util.UUID;

import org.eclipse.paho.client.mqttv3.IMqttClient;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.stereotype.Service;

import it.lab.iot.exception.BaseException;
import it.lab.iot.mqtt.exception.MqttConnectionFailException;

@Service
public class MqttService implements IMqttService {

	private static final String MQTT_IP = "tcp://localhost:1883";
	
	@Override
	public void sendMessage(MqttMessage msg, String topic) throws BaseException{
		
		try {
			String publisherId = UUID.randomUUID().toString();
			IMqttClient client = new MqttClient(MQTT_IP,publisherId);
			msg.setQos(2);
			client.connect();
	        client.publish(topic,msg);  
		} catch (MqttException e) {
			throw new MqttConnectionFailException(topic);
		}
		
	}

}
