import { Injectable } from '@angular/core';
import { Http, Response, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/map';
import 'rxjs/add/operator/catch';
import 'rxjs/add/observable/throw';
import { DeviceDTO } from '../../model/DeviceDTO';
import { DeviceSensorsDTO } from '../../model/DeviceSensorsDTO';
import { environment } from '../../../environments/environment';

@Injectable()
export class DeviceRepositoryService {

  constructor(private http: Http) { }

  public getAllDevicesAvailable(): Observable<DeviceDTO[]>{
    return this.http.get(`${environment.server.url}/device/all`,{})
                    .map((res: Response) =>  <DeviceDTO[]>res.json().payload)
                    .catch(err => Observable.throw(JSON.parse(err._body).payload));
  }

  public getDeviceSensors(deviceId: number): Observable<DeviceSensorsDTO>{
    return this.http.get(`${environment.server.url}/device/`+deviceId+'/sensors',{})
                    .map((res: Response) =>  <DeviceSensorsDTO>res.json().payload)
                    .catch(err => Observable.throw(JSON.parse(err._body).payload));
  }

  public startStopMonitoring(device: DeviceDTO, type: string): Observable<string>{
    return this.http.post(`${environment.server.url}/device/`+type, device,{})
                    .map((res: Response) =>  <string>res.json().payload)
                    .catch(err => Observable.throw(JSON.parse(err._body).payload));
  }
}
