package it.lab.iot.sensor.repository;

import java.util.Date;
import java.util.List;

import org.springframework.data.repository.CrudRepository;

import it.lab.iot.sensor.entity.Sensor;
import it.lab.iot.sensor.entity.SensorValues;

public interface ISensorValuesRepository extends CrudRepository<SensorValues, Integer> {
	public SensorValues findFirstBySensorIdOrderByDataCampioneDesc(String sensorId);
	public List<SensorValues> findFirst20BySensorIdOrderByDataCampioneDesc(String sensorId);
	public List<SensorValues> findFirst20BySensorIdAndSubscriberIdOrderByDataCampioneDesc(String sensorId, Integer deviceId);
	public List<SensorValues> findAllBySensorIdAndDataCampioneLessThan(String sensorId, Date yesterday);
}
