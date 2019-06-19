package it.lab.iot.exception;

import javax.ws.rs.core.Response;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.context.request.ServletWebRequest;
import org.springframework.web.context.request.WebRequest;
import org.springframework.web.servlet.mvc.method.annotation.ResponseEntityExceptionHandler;

import it.lab.iot.dto.ApiBaseResponse;


@ControllerAdvice
public class ExceptionHandlerController extends ResponseEntityExceptionHandler {
	
	private static final Logger logger = LoggerFactory.getLogger(ExceptionHandlerController.class);
	
    @ExceptionHandler(value = { AppException.class, IllegalStateException.class })
    protected ResponseEntity<Object> handleConflict(AppException ex, WebRequest request) {
    	logger.error(ex.getHrMessage());
        ApiBaseResponse<String> apr = new ApiBaseResponse<String>(((ServletWebRequest)request).getRequest().getRequestURI().toString(), Response.Status.INTERNAL_SERVER_ERROR.getStatusCode(), ApiBaseResponse.FAIL, ex.getHrMessage());
        return handleExceptionInternal(ex, apr, new HttpHeaders(), HttpStatus.INTERNAL_SERVER_ERROR, request);
    }
}
