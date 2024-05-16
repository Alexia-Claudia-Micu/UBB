import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { CarCrudComponent } from './car-crud/car-crud.component';
import { CarHomeComponent } from './car-home/car-home.component';
import { CarFilterComponent } from './car-filter/car-filter.component';
import { HttpClientModule} from "@angular/common/http";
import { FormsModule } from '@angular/forms';
import { CarFilterModelComponent } from './car-filter-model/car-filter-model.component';

@NgModule({
  declarations: [
    AppComponent,
    CarCrudComponent,
    CarFilterComponent,
    CarFilterModelComponent
  ],
  imports: [
    BrowserModule,
    CarHomeComponent,
    AppRoutingModule,
    HttpClientModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }