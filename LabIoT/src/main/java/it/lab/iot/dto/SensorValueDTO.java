
package it.lab.iot.dto;

import java.util.Date;

import com.fasterxml.jackson.annotation.JsonFormat;

import lombok.Data;

@Data
public class SensorValueDTO {
	private String sensorId;
	private Integer deviceId;
	private String sensorName;
	private Float value;
	private Boolean isAlert;
	@JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy HH:mm:ss")
	private Date dataInserimento;
}
