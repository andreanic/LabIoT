import { TestBed, inject } from '@angular/core/testing';

import { SensorRepositoryService } from './sensor-repository.service';

describe('SensorRepositoryService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [SensorRepositoryService]
    });
  });

  it('should be created', inject([SensorRepositoryService], (service: SensorRepositoryService) => {
    expect(service).toBeTruthy();
  }));
});
