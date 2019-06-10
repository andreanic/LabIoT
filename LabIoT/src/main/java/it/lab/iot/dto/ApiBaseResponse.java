package it.lab.iot.dto;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;
import javax.ws.rs.core.Response;
import lombok.Getter;
import lombok.Setter;


@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
    "api",
    "status",
    "result",
    "payload"
})
@Getter
@Setter
public class ApiBaseResponse<T> {
    
    public final static String SUCCESS = "SUCCESS";
    public final static String FAIL = "FAIL";

    @JsonProperty("api")
    protected String api;
    @JsonProperty("status")
    protected Integer status;
    @JsonProperty("result")
    protected String result;
    @JsonProperty("payload")
    protected T payload;
    
    public ApiBaseResponse() { }
    
    public ApiBaseResponse(String api, T payload) { 
    	this.api = api;
        this.status = Response.Status.OK.getStatusCode();
        this.result = SUCCESS;
        this.payload = payload;
    }

    public ApiBaseResponse(
            String api, Integer status, String result, T payload) {
        this.api = api;
        this.status = status;
        this.result = result;
        this.payload = payload;
    }    
}
