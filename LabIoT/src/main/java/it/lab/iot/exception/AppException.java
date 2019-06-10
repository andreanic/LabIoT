package it.lab.iot.exception;

import lombok.Data;

@Data
public class AppException extends Exception {

    private static final long serialVersionUID = -4801700670612878845L;

    String exception;
    String hrMessage;
    
    public AppException() { }

    public AppException(BaseException ex) {
        this.exception = ex.getClass().getCanonicalName();
        this.hrMessage = ex.getHrMessage();
    } 
}