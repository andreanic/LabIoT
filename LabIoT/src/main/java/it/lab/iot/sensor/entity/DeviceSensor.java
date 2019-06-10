package it.lab.iot.sensor.entity;

import java.io.Serializable;
import javax.persistence.*;


/**
 * The persistent class for the device_sensors database table.
 * 
 */
@Entity
@Table(name="device_sensors")
@NamedQuery(name="DeviceSensor.findAll", query="SELECT d FROM DeviceSensor d")
public class DeviceSensor implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	//bi-directional many-to-one association to Sensor
	@ManyToOne
	private Sensor sensor;

	//bi-directional many-to-one association to Subscriber
	@ManyToOne
	@JoinColumn(name="device_id")
	private Device subscriber;

	public DeviceSensor() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Sensor getSensor() {
		return this.sensor;
	}

	public void setSensor(Sensor sensor) {
		this.sensor = sensor;
	}

	public Device getSubscriber() {
		return this.subscriber;
	}

	public void setSubscriber(Device subscriber) {
		this.subscriber = subscriber;
	}

}