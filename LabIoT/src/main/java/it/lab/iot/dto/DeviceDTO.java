package it.lab.iot.dto;

import java.util.Date;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

@Data
public class DeviceDTO {
	@JsonProperty(required = true)
	private String deviceName;
	private Integer deviceId;
	private Date lastUpdate;
}
