import { Component, OnInit } from '@angular/core';
import { GenericService } from '../generic.service';
import { Car } from '../car'; 

@Component({
  selector: 'app-car-filter-model',
  templateUrl: './car-filter-model.component.html',
  styleUrls: ['./car-filter-model.component.css']
})
export class CarFilterModelComponent implements OnInit {

  selectedOption: string = '';
  models: string[] = [];
  filteredCars: Car[] = [];

  prevOption: string = 'None';
  optionHistory: string[] = ["None"];

  constructor(private genericService: GenericService) { }

  ngOnInit(): void {
    this.getModels();
  }

  getModels(): void {
    this.genericService.fetchModels()
      .subscribe(models => this.models = models);
  }

  getFilteredCarsByModel(): void {
    this.prevOption = this.optionHistory[this.optionHistory.length - 1];
    this.optionHistory.push(this.selectedOption);
    this.genericService.fetchCarsByModel(this.selectedOption)
      .subscribe(cars => {
        this.filteredCars = cars;
      });
  }

}
