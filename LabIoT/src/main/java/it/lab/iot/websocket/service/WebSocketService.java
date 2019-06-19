package it.lab.iot.websocket.service;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandler;
import org.springframework.stereotype.Service;
import org.springframework.util.concurrent.ListenableFuture;
import org.springframework.web.socket.client.standard.StandardWebSocketClient;
import org.springframework.web.socket.messaging.WebSocketStompClient;
import org.springframework.web.socket.sockjs.client.SockJsClient;
import org.springframework.web.socket.sockjs.client.Transport;
import org.springframework.web.socket.sockjs.client.WebSocketTransport;

import com.fasterxml.jackson.databind.ObjectMapper;

import it.lab.iot.device.exception.WebSocketException;
import it.lab.iot.exception.BaseException;
import it.lab.iot.security.WebSocketSessionHandler;
import it.lab.iot.sensor.service.SensorService;

@Service
public class WebSocketService implements IWebSocketService {

	private static final Logger logger = LoggerFactory.getLogger(WebSocketService.class);
	
	private static final String WEBSOCKET_URL = "ws://127.0.0.1:8080/register";
	
	@Override
	public <T> void sendMessage(T payloadObj) throws BaseException {
		
        try {
        	ObjectMapper mapper = new ObjectMapper();
        	String payload = mapper.writeValueAsString(payloadObj);
        	logger.info("Payload -> " + payload);
        	StompSession session = this.connect();
        	session.send("/data", payload.getBytes());
        	session.disconnect();
		} catch (Exception e) {
			throw new WebSocketException();
		} 
	}
	
	private StompSession connect() throws InterruptedException, ExecutionException {
		List<Transport> transports = new ArrayList<Transport>();
		transports.add(new WebSocketTransport(new StandardWebSocketClient()));  
		SockJsClient sockjsClient = new SockJsClient(transports);   
        WebSocketStompClient stompClient = new WebSocketStompClient(sockjsClient);

        StompSessionHandler sessionHandler = new WebSocketSessionHandler();
        ListenableFuture<StompSession> session = stompClient.connect(WEBSOCKET_URL, sessionHandler);
        return session.get();
	}

}
