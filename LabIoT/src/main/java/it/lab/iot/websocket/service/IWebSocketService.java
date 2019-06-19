package it.lab.iot.websocket.service;

import it.lab.iot.exception.BaseException;

public interface IWebSocketService {
	public <T> void sendMessage(T payload) throws BaseException;
}
