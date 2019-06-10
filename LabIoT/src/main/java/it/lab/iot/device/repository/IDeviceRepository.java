package it.lab.iot.device.repository;

import org.springframework.data.repository.CrudRepository;

import it.lab.iot.sensor.entity.Device;

public interface IDeviceRepository extends CrudRepository<Device, Integer> {
}
