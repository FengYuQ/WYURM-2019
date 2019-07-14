#ifndef _MODE_H_
#define _MODE_H_

void ModeChoose(void);
void ModeTest(void);
void ModeFire(void);
void ModePatrol(void);
void Agl_limit(void);
void JudgeDriver(void);
void ParamInit(void);

typedef struct{
	int Mode;
	int GetPos;
	int Partrol;
	int Direction;
	int RedFlag;
	int GreenFlag;
	int FireFlag;
	int PatrolFlag;
	int ResidueFlag;
	
}Flag_t;

#endif
