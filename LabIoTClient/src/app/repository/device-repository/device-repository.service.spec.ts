import { TestBed, inject } from '@angular/core/testing';

import { DeviceRepositoryService } from './device-repository.service';

describe('DeviceRepositoryService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [DeviceRepositoryService]
    });
  });

  it('should be created', inject([DeviceRepositoryService], (service: DeviceRepositoryService) => {
    expect(service).toBeTruthy();
  }));
});
