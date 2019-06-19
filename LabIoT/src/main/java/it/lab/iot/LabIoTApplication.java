package it.lab.iot;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import it.lab.iot.websocket.service.IWebSocketService;

@SpringBootApplication
public class LabIoTApplication {
	
	public static void main(String[] args) {
		SpringApplication.run(LabIoTApplication.class, args);
	}

}
