import { Component, OnInit, OnDestroy } from '@angular/core';
import { SensorValue } from '../../model/SensorValue';
import { SensorRepository } from '../../repository/sensor-repository/sensor-repository.service';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit, OnDestroy {

  private sensorValues: SensorValue[] = [];
  private specificSensorValues: SensorValue[] = null;
  private refreshValuesID: NodeJS.Timer;
  private isStopped: boolean = false;
  private tableTitle: string = null;
  private SENSOR_REFRESH_TIMER: number = 1000;

  constructor(private sensorRepository: SensorRepository) { }

  ngOnInit() {
    this.startMonitoring();
  }

  ngOnDestroy(){
    
  }

  public getLastValues(): void{
    this.sensorRepository.getLastValues().subscribe(values => {
      this.sensorValues = values;
    },
    err => {
      console.warn("Error -> " + err);
    });
  }

  public showMore(sensorValue: SensorValue): void{
    this.tableTitle = sensorValue.sensorName
    this.sensorRepository.getLast20ValuesByName(sensorValue.sensorName).subscribe(records => {
      this.specificSensorValues = records;
    },
    err => {
      console.warn("Error -> " + err);
    });
  }

  public startMonitoring(): void{
    this.isStopped = false;
    this.getLastValues();
    this.refreshValuesID = setInterval(() => {
      this.getLastValues();
    }, this.SENSOR_REFRESH_TIMER);
  }

  public stopMonitoring(): void{
    this.isStopped = true;
    clearInterval(this.refreshValuesID);
  }
}
