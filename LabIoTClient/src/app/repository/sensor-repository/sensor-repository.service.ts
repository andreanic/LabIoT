import { Injectable } from '@angular/core';
import { Http, Response, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Observable';
import { SensorValue } from '../../model/SensorValue';
import 'rxjs/add/operator/map';
import 'rxjs/add/operator/catch';

@Injectable()
export class SensorRepository {

  constructor(private http: Http) { }

  public getLastValues(): Observable<SensorValue[]>{
    return this.http.get(`http://localhost:8080/sensor/values`,{})
                    .map((res: Response) =>  <SensorValue[]>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body)));
  }

  public getLast20ValuesByName(sensorName: string): Observable<SensorValue[]>{
    return this.http.get(`http://localhost:8080/sensor/values/`+sensorName,{})
                    .map((res: Response) =>  <SensorValue[]>res.json().payload)
                    .catch((e: any) => Observable.throw(JSON.parse(e._body)));
  }
}
