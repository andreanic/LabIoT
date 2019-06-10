import { NgModule } from '@angular/core';

import { DashboardComponent } from './dashboard.component';
import { DashboardRouting } from './dashboard.routing';
import { SharedModule } from '../../module/shared-module';

@NgModule({
  imports: [
    DashboardRouting,
    SharedModule
  ],
  declarations: [ 
    DashboardComponent,
  ]
})
export class DashboardModule { }
