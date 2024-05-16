import { Component, OnInit } from '@angular/core';
import { GenericService } from '../generic.service';
import { Car } from '../car'; 
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-car-filter',
  templateUrl: './car-filter.component.html',
  styleUrls: ['./car-filter.component.css']
})
export class CarFilterComponent implements OnInit {

  selectedOption: string = '';
  colors: string[] = [];
  filteredCars: Car[] = [];

  prevOption: string = 'None';
  optionHistory: string[] = ["None"];

  constructor(private genericService: GenericService) { }

  ngOnInit(): void {
    this.getColors();
  }

  getColors(): void {
    this.genericService.fetchColors()
      .subscribe(colors => this.colors = colors);
  }

  getFilteredCarsByColor(): void {
    this.prevOption = this.optionHistory[this.optionHistory.length - 1];
    this.optionHistory.push(this.selectedOption);
    this.genericService.fetchCarsByColor(this.selectedOption)
      .subscribe(cars => {
        this.filteredCars = cars;
      });
  }
}
