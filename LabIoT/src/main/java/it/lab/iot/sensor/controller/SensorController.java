package it.lab.iot.sensor.controller;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import it.lab.iot.dto.ApiBaseResponse;
import it.lab.iot.dto.SensorDTO;
import it.lab.iot.dto.SensorDevicesDTO;
import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.exception.AppException;
import it.lab.iot.exception.BaseException;
import it.lab.iot.exception.ExceptionHandlerController;
import it.lab.iot.sensor.entity.SensorValues;
import it.lab.iot.sensor.service.ISensorService;


@RestController
@RequestMapping("/sensor")
public class SensorController extends ExceptionHandlerController{

	private static final Logger logger = LoggerFactory.getLogger(SensorController.class);
	
	@Autowired
	private ISensorService sensorService;
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/values")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getLastValues(HttpServletRequest request) throws AppException {
		try {
			logger.info(request.getRequestURI());
			List<SensorValueDTO> dto = sensorService.getValues();
			ApiBaseResponse<List<SensorValueDTO>> abp = new ApiBaseResponse<List<SensorValueDTO>>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/all")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getAllSensorsAvailable(HttpServletRequest request) throws AppException {
		try {
			logger.info(request.getRequestURI());
			List<SensorDTO> dto = sensorService.getAllSensorsAvailable();
			ApiBaseResponse<List<SensorDTO>> abp = new ApiBaseResponse<List<SensorDTO>>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/{sensorId}/values")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getLast20ValuesBySensorId(HttpServletRequest request, @PathVariable("sensorId") String sensorId) throws AppException {
		try {
			logger.info(request.getRequestURI());
			List<SensorValueDTO> dto = sensorService.getLast20ValuesBySensorId(sensorId);
			ApiBaseResponse<List<SensorValueDTO>> abp = new ApiBaseResponse<List<SensorValueDTO>>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/{sensorId}/{deviceId}/values")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getLast20ValuesBySensorIdAndDeviceId(HttpServletRequest request, @PathVariable("sensorId") String sensorId, 
			@PathVariable("deviceId") Integer deviceId) throws AppException {
		try {
			logger.info(request.getRequestURI());
			List<SensorValueDTO> dto = sensorService.getLast20ValuesBySensorIdAndDeviceId(sensorId, deviceId);
			ApiBaseResponse<List<SensorValueDTO>> abp = new ApiBaseResponse<List<SensorValueDTO>>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/{sensorId}/devices")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getSensorDevices(HttpServletRequest request, @PathVariable("sensorId") String sensorId) throws AppException {
		try {
			logger.info(request.getRequestURI());
			SensorDevicesDTO dto = sensorService.getAllSensorDevices(sensorId);
			ApiBaseResponse<SensorDevicesDTO> abp = new ApiBaseResponse<SensorDevicesDTO>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	@POST
	@RequestMapping("/values/create")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> createValue(HttpServletRequest request,@RequestBody SensorValueDTO sensorValue) throws AppException {
		try {
			logger.info(request.getRequestURI());
			SensorValueDTO response = sensorService.createValue(sensorValue);
			ApiBaseResponse<SensorValueDTO> abp = new ApiBaseResponse<SensorValueDTO>(request.getRequestURI(),response);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	@DELETE
	@RequestMapping("{sensorId}/values/delete")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> deleteOldValue(HttpServletRequest request, @PathVariable("sensorId") String sensorId) throws AppException {
		try {
			logger.info(request.getRequestURI());
			sensorService.deleteOldValue(sensorId);
			ApiBaseResponse abp = new ApiBaseResponse(request.getRequestURI(),null);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
    @MessageMapping("/data")
    @SendTo("/webclient")
    public SensorValueDTO greeting(SensorValueDTO message) {
        return message;
    }
}
