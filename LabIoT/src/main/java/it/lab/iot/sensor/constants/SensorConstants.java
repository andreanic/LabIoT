package it.lab.iot.sensor.constants;

import java.util.ArrayList;
import java.util.List;

public class SensorConstants {
	protected static final String FUOCO_SENSOR = "Fuoco";
	protected static final String LUCE_SENSOR = "Luce";
	protected static final String HEARTBEAT_SENSOR = "Heartbeat";
	protected static final String SUONO_SENSOR = "Suono";
	protected static final String TEMPERATURA_SENSOR = "Temperatura";
	protected static final String TILT_SENSOR = "Tilt";
	protected static final String UMIDITA_SENSOR = "Umidita";
	protected static final String VIBRAZIONE_SENSOR = "Vibrazione";
	protected static final String WIFIPOWER_SENSOR = "Wifipower";
	
	public List<String> getConstantsList(){
		List<String> constants = new ArrayList<String>();
		
		constants.add(FUOCO_SENSOR);
		constants.add(LUCE_SENSOR);
		constants.add(HEARTBEAT_SENSOR);
		constants.add(SUONO_SENSOR);
		constants.add(TEMPERATURA_SENSOR);
		constants.add(TILT_SENSOR);
		constants.add(UMIDITA_SENSOR);
		constants.add(VIBRAZIONE_SENSOR);
		constants.add(WIFIPOWER_SENSOR);
		
		return constants;
	}
}
