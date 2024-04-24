#ifndef INC_PROCESS_H_
#define INC_PROCESS_H_

#define ProcessDetectionStep 0x01
#define ProcessClose 0x02

class Process
{
public:
	uint8_t status = ProcessDetectionStep;
	uint16_t servos_task_id = 0;

	bool overflow = false;
	bool humanable = true;
};

#endif /* INC_PROCESS_H_ */
