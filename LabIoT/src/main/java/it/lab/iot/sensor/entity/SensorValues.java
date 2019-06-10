package it.lab.iot.sensor.entity;

import java.io.Serializable;
import javax.persistence.*;
import java.sql.Timestamp;


/**
 * The persistent class for the sensor_values database table.
 * 
 */
@Entity
@Table(name="sensor_values")
@NamedQuery(name="SensorValues.findAll", query="SELECT s FROM SensorValues s")
public class SensorValues implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	private int id;

	@Column(name="data_campione")
	private Timestamp dataCampione;

	@Column(name="is_alert")
	private boolean isAlert;

	private float valore;

	//bi-directional many-to-one association to Sensor
	@ManyToOne
	private Sensor sensor;

	//bi-directional many-to-one association to Subscriber
	@ManyToOne
	@JoinColumn(name="device_id")
	private Device subscriber;

	public SensorValues() {
	}

	public int getId() {
		return this.id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Timestamp getDataCampione() {
		return this.dataCampione;
	}

	public void setDataCampione(Timestamp dataCampione) {
		this.dataCampione = dataCampione;
	}

	public boolean getIsAlert() {
		return this.isAlert;
	}

	public void setIsAlert(boolean isAlert) {
		this.isAlert = isAlert;
	}

	public float getValore() {
		return this.valore;
	}

	public void setValore(float valore) {
		this.valore = valore;
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