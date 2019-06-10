package it.lab.iot.sensor.repository;

import org.springframework.data.repository.CrudRepository;

import it.lab.iot.sensor.entity.Sensor;

public interface ISensorRepository extends CrudRepository<Sensor, String> {
}
