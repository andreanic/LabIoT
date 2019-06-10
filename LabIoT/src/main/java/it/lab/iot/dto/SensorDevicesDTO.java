package it.lab.iot.dto;

import java.util.List;

import lombok.Data;

@Data
public class SensorDevicesDTO {
	private SensorDTO sensor;
	private List<DeviceDTO> devices;
}
