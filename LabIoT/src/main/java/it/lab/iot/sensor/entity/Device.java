package it.lab.iot.sensor.entity;

import java.io.Serializable;
import javax.persistence.*;
import java.sql.Timestamp;
import java.util.List;


/**
 * The persistent class for the subscribers database table.
 * 
 */
@Entity
@Table(name="subscribers")
@NamedQuery(name="Device.findAll", query="SELECT s FROM Device s")
public class Device implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	@Lob
	@Column(name="device_name")
	private String deviceName;

	@Column(name="last_update")
	private Timestamp lastUpdate;

	//bi-directional many-to-one association to DeviceSensor
	@OneToMany(mappedBy="subscriber")
	private List<DeviceSensor> deviceSensors;

	//bi-directional many-to-one association to SensorValue
	@OneToMany(mappedBy="subscriber")
	private List<SensorValues> sensorValues;

	public Device() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getDeviceName() {
		return this.deviceName;
	}

	public void setDeviceName(String deviceName) {
		this.deviceName = deviceName;
	}

	public Timestamp getLastUpdate() {
		return this.lastUpdate;
	}

	public void setLastUpdate(Timestamp lastUpdate) {
		this.lastUpdate = lastUpdate;
	}

	public List<DeviceSensor> getDeviceSensors() {
		return this.deviceSensors;
	}

	public void setDeviceSensors(List<DeviceSensor> deviceSensors) {
		this.deviceSensors = deviceSensors;
	}

	public DeviceSensor addDeviceSensor(DeviceSensor deviceSensor) {
		getDeviceSensors().add(deviceSensor);
		deviceSensor.setSubscriber(this);

		return deviceSensor;
	}

	public DeviceSensor removeDeviceSensor(DeviceSensor deviceSensor) {
		getDeviceSensors().remove(deviceSensor);
		deviceSensor.setSubscriber(null);

		return deviceSensor;
	}

	public List<SensorValues> getSensorValues() {
		return this.sensorValues;
	}

	public void setSensorValues(List<SensorValues> sensorValues) {
		this.sensorValues = sensorValues;
	}

	public SensorValues addSensorValue(SensorValues sensorValue) {
		getSensorValues().add(sensorValue);
		sensorValue.setSubscriber(this);

		return sensorValue;
	}

	public SensorValues removeSensorValue(SensorValues sensorValue) {
		getSensorValues().remove(sensorValue);
		sensorValue.setSubscriber(null);

		return sensorValue;
	}

}