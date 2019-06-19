package it.lab.iot.device.repository;

import java.util.Date;
import java.util.List;

import org.springframework.data.repository.CrudRepository;

import it.lab.iot.sensor.entity.Device;

public interface IDeviceRepository extends CrudRepository<Device, Integer> {
	public List<Device> findAllByLastUpdateGreaterThanEqual(Date date);
}
