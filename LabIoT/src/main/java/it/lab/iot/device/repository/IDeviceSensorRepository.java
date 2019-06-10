package it.lab.iot.device.repository;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import it.lab.iot.sensor.entity.DeviceSensor;

public interface IDeviceSensorRepository extends CrudRepository<DeviceSensor, Integer> {
//	@Query("SELECT ds FROM DeviceSensor ds WHERE ds.sensor.id = :sensorId")
//	public DeviceSensor findBySensorId(@Param("sensorId") String sensorId);
}
