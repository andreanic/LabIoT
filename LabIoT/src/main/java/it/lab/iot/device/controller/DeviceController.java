package it.lab.iot.device.controller;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.ws.rs.Consumes;
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

import it.lab.iot.device.service.IDeviceService;
import it.lab.iot.dto.ApiBaseResponse;
import it.lab.iot.dto.DeviceDTO;
import it.lab.iot.dto.DeviceSensorsDTO;
import it.lab.iot.dto.SensorValueDTO;
import it.lab.iot.exception.AppException;
import it.lab.iot.exception.BaseException;
import it.lab.iot.exception.ExceptionHandlerController;

@RestController
@RequestMapping("/device")
public class DeviceController extends ExceptionHandlerController{
	
	private static final Logger logger = LoggerFactory.getLogger(DeviceController.class);
	
	@Autowired
	private IDeviceService deviceService;
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/all")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getAllDevicesAvailable(HttpServletRequest request) throws AppException {
		try {
			logger.info(request.getRequestURI());
			List<DeviceDTO> dto = deviceService.getAllDeviceAvailable();
			ApiBaseResponse<List<DeviceDTO>> abr = new ApiBaseResponse<List<DeviceDTO>>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abr,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@GET
	@RequestMapping("/{deviceId}/sensors")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> getAllDeviceSensors(HttpServletRequest request, @PathVariable("deviceId") Integer deviceId) throws AppException {
		try {
			logger.info(request.getRequestURI());
			DeviceSensorsDTO dto = deviceService.getAllDeviceSensors(deviceId);
			ApiBaseResponse<DeviceSensorsDTO> abr = new ApiBaseResponse<DeviceSensorsDTO>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abr,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@POST
	@RequestMapping("/subscribe")
	@ResponseBody
	@Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> subscribe(HttpServletRequest request, @RequestBody DeviceSensorsDTO subscriber) throws AppException {
		try {
			logger.info(request.getRequestURI());
			DeviceDTO dto = deviceService.subscribe(subscriber);
			ApiBaseResponse<DeviceDTO> abr = new ApiBaseResponse<DeviceDTO>(request.getRequestURI(),dto);
	        return new ResponseEntity<ApiBaseResponse>(abr,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@POST
	@RequestMapping("/start")
	@ResponseBody
	@Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> startMonitoring(HttpServletRequest request, @RequestBody DeviceDTO device) throws AppException {
		try {
			logger.info(request.getRequestURI());
			String response = deviceService.startStopMonitoring(device, deviceService.START);
			ApiBaseResponse<String> abr = new ApiBaseResponse<String>(request.getRequestURI(),response);
	        return new ResponseEntity<ApiBaseResponse>(abr,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@POST
	@RequestMapping("/stop")
	@ResponseBody
	@Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> stopMonitoring(HttpServletRequest request, @RequestBody DeviceDTO device) throws AppException {
		try {
			logger.info(request.getRequestURI());
			String response = deviceService.startStopMonitoring(device, deviceService.STOP);
			ApiBaseResponse<String> abr = new ApiBaseResponse<String>(request.getRequestURI(),response);
	        return new ResponseEntity<ApiBaseResponse>(abr,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}
	
	@SuppressWarnings("rawtypes")
	@DELETE
	@RequestMapping("{deviceId}/delete")
	@ResponseBody
    @Produces(MediaType.APPLICATION_JSON)
	public ResponseEntity<ApiBaseResponse> deleteOldValue(HttpServletRequest request, @PathVariable("deviceId") Integer deviceId) throws AppException {
		try {
			logger.info(request.getRequestURI());
			String response = deviceService.deleteSubscribedDevice(deviceId);
			ApiBaseResponse<String> abp = new ApiBaseResponse<String>(request.getRequestURI(),response);
	        return new ResponseEntity<ApiBaseResponse>(abp,HttpStatus.OK);
		} catch (BaseException e) {
			throw new AppException(e);
		}
	}

}
