export class SensorValue{
    private sensorId: string;
    private deviceId: number;
    public sensorName: string;
	public value: number;
	public isAlert: boolean;
    public dataInserimento: Date;


    /**
     * Getter $sensorId
     * @return {string}
     */
	public get $sensorId(): string {
		return this.sensorId;
	}

    /**
     * Getter $deviceId
     * @return {number}
     */
	public get $deviceId(): number {
		return this.deviceId;
	}

    /**
     * Setter $sensorId
     * @param {string} value
     */
	public set $sensorId(value: string) {
		this.sensorId = value;
	}

    /**
     * Setter $deviceId
     * @param {number} value
     */
	public set $deviceId(value: number) {
		this.deviceId = value;
	}

}