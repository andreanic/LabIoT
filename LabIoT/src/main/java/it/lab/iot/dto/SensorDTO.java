package it.lab.iot.dto;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

@Data
public class SensorDTO {
	@JsonProperty(required = true)
	private String sensorId;
	@JsonProperty(required = true)
	private String sensorName;
	@JsonProperty(required = true)
	private String description;
	private String url;
	private String uom;
	private String type;
}
