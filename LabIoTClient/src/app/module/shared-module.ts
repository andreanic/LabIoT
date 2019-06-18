import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import { SensorRepository } from '../repository/sensor-repository/sensor-repository.service';
import { BrowserModule } from '@angular/platform-browser';
import { DeviceRepositoryService } from '../repository/device-repository/device-repository.service';


@NgModule({
  imports: [
    FormsModule,
    HttpModule,
    CommonModule,
  ],
  declarations: [
  ],
  providers: [
    SensorRepository,
    DeviceRepositoryService
  ],
  exports: [
    FormsModule,
    HttpModule,
    CommonModule,
    
  ]
})
export class SharedModule { }
