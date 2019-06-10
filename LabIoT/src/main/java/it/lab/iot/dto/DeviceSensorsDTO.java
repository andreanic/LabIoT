package it.lab.iot.dto;

import java.util.List;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

@Data
public class DeviceSensorsDTO {
	@JsonProperty(required = true)
	private DeviceDTO device;
	private List<SensorDTO> sensors;
}
