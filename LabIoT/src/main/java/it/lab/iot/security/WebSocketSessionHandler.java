package it.lab.iot.security;

import java.lang.reflect.Type;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.messaging.simp.stomp.StompCommand;
import org.springframework.messaging.simp.stomp.StompHeaders;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandlerAdapter;

import it.lab.iot.dto.SensorValueDTO;

public class WebSocketSessionHandler extends StompSessionHandlerAdapter {
	
	private static final Logger logger = LoggerFactory.getLogger(WebSocketSessionHandler.class);
	
    @Override
    public void afterConnected(StompSession session, StompHeaders connectedHeaders) {
//        session.subscribe("/topic/greetings", this);
//        session.send("/hello", "{\"name\":\"Client\"}".getBytes());

        logger.info("New session: "+ session.getSessionId());
    }

    @Override
    public void handleException(StompSession session, StompCommand command, StompHeaders headers, byte[] payload, Throwable exception) {
        logger.error("Error on WebSocket");
    }
    
    @Override
    public Type getPayloadType(StompHeaders headers) {
        return SensorValueDTO.class;
    }

}