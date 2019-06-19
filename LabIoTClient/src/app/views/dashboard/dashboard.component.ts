import { Component, OnInit, OnDestroy } from '@angular/core';
import { SensorValue } from '../../model/SensorValue';
import { SensorRepository } from '../../repository/sensor-repository/sensor-repository.service';
import { DeviceDTO } from '../../model/DeviceDTO';
import { SensorDTO } from '../../model/SensorDTO';
import { DeviceRepositoryService } from '../../repository/device-repository/device-repository.service';
import { DeviceSensorsDTO } from '../../model/DeviceSensorsDTO';
import { SensorDevicesDTO } from '../../model/SensorDevicesDTO';
import { ToastrService } from 'ngx-toastr';
import { WebSocketService } from '../../service/websocket-service/web-socket.service';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit, OnDestroy {

  //DTO response
  private specificSensorValues: SensorValue[] = [];
  private devices: DeviceDTO[] = [];
  private sensors: SensorDTO[] = [];
  private deviceSensors: DeviceSensorsDTO;
  private sensorDevices: SensorDevicesDTO;
 
  private refreshValuesID: NodeJS.Timer;
  private SENSOR_REFRESH_TIMER: number = 1000;
  
  private selectedCategory: string;
  private selectedSubCategory: string;

  //Dashboard lists
  private DEVICES: string = "DEVICES";
  private SENSORS: string = "SENSORS";
  private VALUES: string = "VALUES";
  private SENSORSXDEVICE: string = "SENSORSXDEVICE";
  private DEVICESXSENSOR: string = "DEVICEXSENSOR";

  //Start & Stop constants
  private START: string = "start";
  private STOP: string = "stop";

  //Toast message
  private errorMessage: string;
  private successMessage: string;
  private showTime: number = 2000;

  constructor(private sensorRepository: SensorRepository,
              private deviceRepository: DeviceRepositoryService,
              private websocketService: WebSocketService) { }

  ngOnInit() {
  }

  ngOnDestroy(){
    this.websocketService.disconnect();
  }

  public getAllDevices(): void{
    this.deviceRepository.getAllDevicesAvailable().subscribe(devices => {      
      this.changeCategory(this.DEVICES);
      this.devices = devices;
    },
    err => {
      this.showErrorMessage(err);
    }) 
    
  }

  public getAllSensors(): void{
    this.sensorRepository.getAllSensorsAvailable().subscribe(sensors => {      
      this.changeCategory(this.SENSORS);
      this.sensors = sensors;
    },
    err => {      
      this.showErrorMessage(err);
    });
    
  }

  public getLastValues(): void{
    this.sensorRepository.getLastValues().subscribe(values => {
      this.changeCategory(this.VALUES);
      this.websocketService.sensorValues = values;
      this.websocketService.connect();
    },
    err => {
      this.showErrorMessage(err);
    });
  }

  public getDeviceSensors(device: DeviceDTO): void{
    this.changeSubcategory(null);
    this.deviceRepository.getDeviceSensors(device.deviceId).subscribe(deviceSensors => {
      this.deviceSensors = deviceSensors;
      this.selectedSubCategory = this.SENSORSXDEVICE;
    },
    err => {
      this.showErrorMessage(err);
    });
  }

  public getSensorDevices(sensor: SensorDTO): void{
    this.changeSubcategory(null);
    this.sensorRepository.getSensorDevices(sensor.sensorId).subscribe(sensorDevices => {
      this.sensorDevices = sensorDevices;
      this.selectedSubCategory = this.DEVICESXSENSOR;
    },
    err => {
      this.showErrorMessage(err);
    })
  }

  public getLast20ValuesByDeviceAndSensorID(sensorId: string, deviceId: number): void{
    this.websocketService.disconnect();
    this.sensorRepository.getLast20ValuesBySensorIdAndDeviceId(sensorId, deviceId).subscribe(records => {
      this.websocketService.sensorValues = records;
      this.websocketService.connect(sensorId, deviceId);
    },
    err => {
      this.showErrorMessage(err);
    });
  }

  private changeCategory(category: string): void{
    this.sensors = null;
    this.devices = null;
    this.websocketService.sensorValues = null;
    this.selectedCategory = category;
    this.specificSensorValues = null;
    this.websocketService.disconnect();
    this.changeSubcategory(null);
    clearInterval(this.refreshValuesID);
  }

  private changeSubcategory(subcategory: string): void{
    this.selectedSubCategory = subcategory;
    this.deviceSensors = null;
    this.sensorDevices = null;    
  }

  private showErrorMessage(message: string): void{
    this.errorMessage = message;
    setTimeout(() => {
      this.errorMessage = null;
    }, this.showTime);
  }

  private showSuccessMessage(message: string): void{
    this.successMessage = message;
    setTimeout(() => {
      this.successMessage = null;
    }, this.showTime);
  }

  private startMonitoring(device: DeviceDTO): void{
    this.deviceRepository.startStopMonitoring(device,this.START).subscribe(response => {
      this.getDeviceSensors(device);
      this.showSuccessMessage(response);
    });
  }

  private stopMonitoring(device: DeviceDTO): void{
    this.deviceRepository.startStopMonitoring(device,this.STOP).subscribe(response => {
      this.getDeviceSensors(device);
      this.showSuccessMessage(response);
    });
  }
}
