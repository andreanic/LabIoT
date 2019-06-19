import { Injectable } from '@angular/core';
import * as Stomp from 'stompjs';
import * as SockJS from 'sockjs-client';
import { SensorValue } from '../../model/SensorValue';
import { Observable } from 'rxjs/Observable';
import { environment } from '../../../environments/environment';

@Injectable()
export class WebSocketService {

  public sensorValues: SensorValue[] = [];
  public sensorId: string;
  public deviceId: number;
  private SENSORVALUES_LIMIT: number = 20;
  private stompClient = null;  
  private url: string = `${environment.server.url}/register`;

  constructor() { }

  public disconnect(): void {
    if (this.stompClient != null) {
      this.stompClient.disconnect();
    }

    this.sensorId = null;
    this.deviceId = null;
  }

  public connect(sensorId?: string, deviceId?: number): void{
    const socket = new SockJS(this.url);
    this.stompClient = Stomp.over(socket);
    this.sensorId = sensorId;
    this.deviceId = deviceId;
 
    const _this = this;
    this.stompClient.connect({}, function (frame) { 
      _this.stompClient.subscribe('/webclient', function (msg){
        _this.updateSensorValues(JSON.parse(msg.body));
      });
    }); 
  }

  private updateSensorValues(sensorValue: SensorValue): void{
    if(!this.sensorId && !this.deviceId){
      let updateItem = this.sensorValues.find((item) => {
        return item.sensorId == sensorValue.sensorId;
      });

      let index = null;
      if(updateItem) {
        index = this.sensorValues.indexOf(updateItem);
      }
        
  
      if(index || index == 0){
        this.sensorValues[index] = sensorValue;
      } 
      else {
        this.sensorValues.push(sensorValue);
      }
        
    }
    else if(this.sensorId == sensorValue.sensorId && this.deviceId == sensorValue.deviceId){
      this.sensorValues.splice(0,0,sensorValue);
      if(this.sensorValues.length > this.SENSORVALUES_LIMIT){
        this.sensorValues.pop();
      }
    }
    
  }



}
