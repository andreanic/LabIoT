package it.lab.iot.sensor.entity;

import java.io.Serializable;
import javax.persistence.*;
import java.sql.Timestamp;
import java.util.List;


/**
 * The persistent class for the sensors database table.
 * 
 */
@Entity
@Table(name="sensors")
@NamedQuery(name="Sensor.findAll", query="SELECT s FROM Sensor s")
public class Sensor implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private String id;

	private Timestamp created;

	@Lob
	private String description;

	@Column(name="is_digital")
	private boolean isDigital;

	@Lob
	@Column(name="sensor_name")
	private String sensorName;

	@Lob
	@Column(name="sensor_url")
	private String sensorUrl;

	@Lob
	private String uom;

	private Timestamp updated;

	//bi-directional many-to-one association to DeviceSensor
	@OneToMany(mappedBy="sensor")
	private List<DeviceSensor> deviceSensors;

	//bi-directional many-to-one association to SensorValue
	@OneToMany(mappedBy="sensor")
	private List<SensorValues> sensorValues;

	public Sensor() {
	}

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Timestamp getCreated() {
		return this.created;
	}

	public void setCreated(Timestamp created) {
		this.created = created;
	}

	public String getDescription() {
		return this.description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public boolean getIsDigital() {
		return this.isDigital;
	}

	public void setIsDigital(boolean isDigital) {
		this.isDigital = isDigital;
	}

	public String getSensorName() {
		return this.sensorName;
	}

	public void setSensorName(String sensorName) {
		this.sensorName = sensorName;
	}

	public String getSensorUrl() {
		return this.sensorUrl;
	}

	public void setSensorUrl(String sensorUrl) {
		this.sensorUrl = sensorUrl;
	}

	public String getUom() {
		return this.uom;
	}

	public void setUom(String uom) {
		this.uom = uom;
	}

	public Timestamp getUpdated() {
		return this.updated;
	}

	public void setUpdated(Timestamp updated) {
		this.updated = updated;
	}

	public List<DeviceSensor> getDeviceSensors() {
		return this.deviceSensors;
	}

	public void setDeviceSensors(List<DeviceSensor> deviceSensors) {
		this.deviceSensors = deviceSensors;
	}

	public DeviceSensor addDeviceSensor(DeviceSensor deviceSensor) {
		getDeviceSensors().add(deviceSensor);
		deviceSensor.setSensor(this);

		return deviceSensor;
	}

	public DeviceSensor removeDeviceSensor(DeviceSensor deviceSensor) {
		getDeviceSensors().remove(deviceSensor);
		deviceSensor.setSensor(null);

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
		sensorValue.setSensor(this);

		return sensorValue;
	}

	public SensorValues removeSensorValue(SensorValues sensorValue) {
		getSensorValues().remove(sensorValue);
		sensorValue.setSensor(null);

		return sensorValue;
	}

}