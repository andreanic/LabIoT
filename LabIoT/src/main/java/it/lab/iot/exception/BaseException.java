package it.lab.iot.exception;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class BaseException extends Exception{
	private static final long serialVersionUID = 972900201803269016L;

	protected String hrMessage;
}
