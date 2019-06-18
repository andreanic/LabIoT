import { Component, OnInit, OnDestroy } from '@angular/core';
import { SensorValue } from '../../model/SensorValue';
import { SensorRepository } from '../../repository/sensor-repository/sensor-repository.service';
import { DeviceDTO } from '../../model/DeviceDTO';
import { SensorDTO } from '../../model/SensorDTO';
import { DeviceRepositoryService } from '../../repository/device-repository/device-repository.service';
import { DeviceSensorsDTO } from '../../model/DeviceSensorsDTO';
import { SensorDevicesDTO } from '../../model/SensorDevicesDTO';
import { ToastrService } from 'ngx-toastr';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit, OnDestroy {

  //DTO response
  private sensorValues: SensorValue[] = [];
  private specificSensorValues: SensorValue[] = [];
  private devices: DeviceDTO[] = [];
  private sensors: SensorDTO[] = [];
  private deviceSensors: DeviceSensorsDTO;
  private sensorDevices: SensorDevicesDTO;
 
  private refreshValuesID: NodeJS.Timer;
  private isStopped: boolean = false;
  private tableTitle: string = null;
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
  private showTime: number = 20000;

  constructor(private sensorRepository: SensorRepository,
              private deviceRepository: DeviceRepositoryService,
              private toasterService: ToastrService) { }

  ngOnInit() {
    //this.startMonitoring();
  }

  ngOnDestroy(){
  }

  public getAllDevices(): void{
    this.deviceRepository.getAllDevicesAvailable().subscribe(devices => {
      this.devices = devices;
      this.changeCategory(this.DEVICES);
    },
    err => {
      console.error(err);
    }) 
    
  }

  public getAllSensors(): void{
    this.sensorRepository.getAllSensorsAvailable().subscribe(sensors => {      
      this.sensors = sensors;
      this.changeCategory(this.SENSORS);
    },
    err => {      
      console.error(err);
    });
    
  }

  public getLastValues(): void{
    this.sensorRepository.getLastValues().subscribe(values => {
      this.sensorValues = values;
      this.changeCategory(this.VALUES);
    },
    err => {
      console.error(err);
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
      console.error(err);
    })
  }

  public getLast20Values(sensorValue: SensorValue): void{
    this.tableTitle = sensorValue.sensorName
    this.sensorRepository.getLast20ValuesBySensorId(sensorValue.$sensorId).subscribe(records => {
      this.specificSensorValues = records;
    },
    err => {
      console.warn("Error -> " + err);
    });
  }

  public getLast20ValuesByDeviceAndSensorID(sensorId: string, deviceId: number): void{
    this.sensorRepository.getLast20ValuesBySensorIdAndDeviceId(sensorId, deviceId).subscribe(records => {
      this.specificSensorValues = records;
    });
  }

  private changeCategory(category: string): void{
    this.selectedCategory = category;
    this.specificSensorValues = null;
    this.changeSubcategory(null);
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

  private goToUrl(url: string): void{
    window.location.href = url;
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
