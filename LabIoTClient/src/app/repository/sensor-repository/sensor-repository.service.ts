import { Injectable } from '@angular/core';
import { Http, Response, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Observable';
import { SensorValue } from '../../model/SensorValue';
import 'rxjs/add/operator/map';
import 'rxjs/add/operator/catch';
import 'rxjs/add/observable/throw';
import { SensorDTO } from '../../model/SensorDTO';
import { SensorDevicesDTO } from '../../model/SensorDevicesDTO';
import { environment } from '../../../environments/environment';

@Injectable()
export class SensorRepository {

  constructor(private http: Http) { }

  public getLastValues(): Observable<SensorValue[]>{
    return this.http.get(`${environment.server.url}/sensor/values`,{})
                    .map((res: Response) =>  <SensorValue[]>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body).payload));
  }

  public getLast20ValuesBySensorId(sensorId: string): Observable<SensorValue[]>{
    return this.http.get(`${environment.server.url}/sensor/`+sensorId+'/values',{})
                    .map((res: Response) =>  <SensorValue[]>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body).payload));
  }

  public getLast20ValuesBySensorIdAndDeviceId(sensorId: string, deviceId: number): Observable<SensorValue[]>{
    return this.http.get(`${environment.server.url}/sensor/`+sensorId+'/'+deviceId+'/values',{})
                    .map((res: Response) =>  <SensorValue[]>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body).payload));
  }

  public getAllSensorsAvailable(): Observable<SensorDTO[]>{
    return this.http.get(`${environment.server.url}/sensor/all`,{})
                    .map((res: Response) =>  <SensorDTO[]>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body).payload));
  }

  public getSensorDevices(sensorId: string): Observable<SensorDevicesDTO>{
    return this.http.get(`${environment.server.url}/sensor/`+sensorId+'/devices',{})
                    .map((res: Response) =>  <SensorDevicesDTO>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body).payload));
  }
}
