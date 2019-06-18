import { DeviceDTO } from "./DeviceDTO";
import { SensorDTO } from "./SensorDTO";

export class DeviceSensorsDTO {
    public device: DeviceDTO;
    public sensors: SensorDTO[];
}