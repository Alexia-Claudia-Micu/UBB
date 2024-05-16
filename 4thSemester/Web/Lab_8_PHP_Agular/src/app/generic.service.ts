import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Observable, of } from 'rxjs';
import { catchError } from 'rxjs/operators';
import { Car } from './car'; // Import the Car interface

@Injectable({
  providedIn: 'root'
})
export class GenericService {
  private backendUrl = 'http://localhost/hw1/angular/controller/controller.php'; // URL to web api

  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };

  constructor(private http: HttpClient) { }

  fetchCars(): Observable<Car[]> {
    return this.http.get<Car[]>(this.backendUrl + '?action=selectAllCars')
      .pipe(catchError(this.handleError<Car[]>('fetchCars', [])));
  }

  fetchColors(): Observable<string[]> {
    let url = `${this.backendUrl}?action=getColors`;
    return this.http.get<string[]>(url)
      .pipe(catchError(this.handleError<string[]>('fetchColors', [])));
  }

  fetchModels(): Observable<string[]> {
    let url = `${this.backendUrl}?action=getModels`;
    return this.http.get<string[]>(url)
      .pipe(catchError(this.handleError<string[]>('fetchModels', [])));
  }

  fetchCarsByColor(color: string): Observable<Car[]> {
    let url = `${this.backendUrl}?action=getCarsByColor&color=${color}`;
    return this.http.get<Car[]>(url)
      .pipe(catchError(this.handleError<Car[]>('fetchCarsByColor', [])));
  }

  fetchCarsByModel(model: string): Observable<Car[]> {
    let url = `${this.backendUrl}?action=getCarsByModel&model=${model}`;
    return this.http.get<Car[]>(url)
      .pipe(catchError(this.handleError<Car[]>('fetchCarsByModel', [])));
  }

  /** POST: add a new car to the database */
  addCar(car: Car): Observable<any> {
    let url = `${this.backendUrl}?action=addCar&model=${car.model}&enginePower=${car.enginePower}&fuel=${car.fuel}&price=${car.price}&color=${car.color}&age=${car.age}&history=${car.history}`;
    return this.http.get<string>(url)
      .pipe(catchError(this.handleError<string>('addCar', "")));
  }

  updateCar(car: Car): Observable<any> {
    let url = `${this.backendUrl}?action=updateCar&id=${car.id}&model=${car.model}&enginePower=${car.enginePower}&fuel=${car.fuel}&price=${car.price}&color=${car.color}&age=${car.age}&history=${car.history}`;
    return this.http.get<string>(url)
      .pipe(catchError(this.handleError<string>('updateCar', "")));
  }

  deleteCar(id: number): Observable<any> {
    let url = `${this.backendUrl}?action=deleteCar&id=${id}`;
    return this.http.get<string>(url)
      .pipe(catchError(this.handleError<string>('deleteCar', "")));
  }

  /**
   * Handle Http operation that failed.
   * Let the app continue.
   * @param operation - name of the operation that failed
   * @param result - optional value to return as the observable result
   */
  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      // TO DO: send the error to remote logging infrastructure
      console.error(error); // log to console instead
      // Let the app keep running by returning an empty result.
      return of(result as T);
    };
  }
}
