import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CarFilterModelComponent } from './car-filter-model.component';

describe('CarFilterModelComponent', () => {
  let component: CarFilterModelComponent;
  let fixture: ComponentFixture<CarFilterModelComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [CarFilterModelComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(CarFilterModelComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
