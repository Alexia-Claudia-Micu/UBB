import { Component, OnInit } from '@angular/core';
import { Car } from '../car';
import { GenericService } from '../generic.service';

@Component({
  selector: 'app-car-crud', // Updated selector
  templateUrl: './car-crud.component.html', // Updated template URL
  styleUrls: ['./car-crud.component.css'] // Updated style URLs
})
export class CarCrudComponent implements OnInit {

  cars: Car[] = [];

  constructor(private genericService: GenericService) { }

  ngOnInit(): void {
    console.log("ngOnInit called for CarCrudComponent");
    this.getCars();
  }

  getCars(): void {
    this.genericService.fetchCars()
      .subscribe(cars => this.cars = cars);
  }

  onUpdate(car: Car): void {
    // Updated HTML element IDs for car properties
    (<HTMLInputElement>document.getElementById("model2")).value = (car.model);
    (<HTMLInputElement>document.getElementById("enginePower2")).value = String(car.enginePower);
    (<HTMLInputElement>document.getElementById("fuel2")).value = (car.fuel);
    (<HTMLInputElement>document.getElementById("price2")).value = String(car.price);
    (<HTMLInputElement>document.getElementById("color2")).value = (car.color);
    (<HTMLInputElement>document.getElementById("age2")).value = String(car.age);
    (<HTMLInputElement>document.getElementById("history2")).value = (car.history);
    
    let displayVal: string = document.getElementById('update_form')!.style.display;
    if (displayVal === "none")
      document.getElementById('update_form')!.style.display = "inline";
    else document.getElementById('update_form')!.style.display = "none";
  }

  onDelete(carID: number): void {
    const confirmDelete = confirm("Are you sure you want to delete this car?");
    if (confirmDelete) {
        this.genericService.deleteCar(carID).
        subscribe(r => {
            console.log(r.result);
            this.ngOnInit();
        });
    } else {
        console.log("Deletion aborted.");
    }
}


  addCar(newModel: HTMLInputElement, newEnginePower: HTMLInputElement, newFuel: HTMLInputElement, newPrice: HTMLInputElement, newColor: HTMLInputElement, newAge: HTMLInputElement, newHistory: HTMLInputElement) {
    let addedCar: Car = {
      id: +newPrice.value,
      model: newModel.value,
      enginePower: +newEnginePower.value,
      fuel: newFuel.value,
      price: +newPrice.value,
      color: newColor.value,
      age: +newAge.value,
      history: newHistory.value
    };

    this.genericService.addCar(addedCar)
      .subscribe(r => {
        console.log(r.result);
        this.ngOnInit();
      });

    // Clear input fields after adding car
    newModel.value = '';
    newEnginePower.value = '';
    newFuel.value = '';
    newPrice.value = '';
    newColor.value = '';
    newAge.value = '';
    newHistory.value = '';
  }

  updateCar(uModel: HTMLInputElement, uEnginePower: HTMLInputElement, uFuel: HTMLInputElement, uPrice: HTMLInputElement, uColor: HTMLInputElement, uAge: HTMLInputElement, uHistory: HTMLInputElement) {
    let updatedCar: Car = {
      id: +uPrice.value,
      model: uModel.value,
      enginePower: +uEnginePower.value,
      fuel: uFuel.value,
      price: +uPrice.value,
      color: uColor.value,
      age: +uAge.value,
      history: uHistory.value
    };

    this.genericService.updateCar(updatedCar)
      .subscribe(r => {
        console.log(r.result);
        document.getElementById('update_form')!.style.display = "none";
        this.ngOnInit();
      });
  }
}
