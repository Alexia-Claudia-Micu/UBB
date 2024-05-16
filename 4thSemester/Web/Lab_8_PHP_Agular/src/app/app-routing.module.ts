import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { CarCrudComponent } from './car-crud/car-crud.component';
import { CarFilterComponent } from './car-filter/car-filter.component';
import { CarHomeComponent } from './car-home/car-home.component';
import { CarFilterModelComponent } from './car-filter-model/car-filter-model.component';

const routes: Routes = [
  {path: '', redirectTo: '/car-home', pathMatch: 'full'},
  {path: 'car-crud', component: CarCrudComponent},
  {path: 'car-filter', component:CarFilterComponent},
  {path: 'car-home', component:CarHomeComponent},
  {path: 'car-filter-model', component:CarFilterModelComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
