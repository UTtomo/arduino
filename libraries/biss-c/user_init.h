#ifndef __USER_INIT_H__
#define __USER_INIT_H__

#define	SBI(PORT,BIT)	PORT |= (1<<BIT)//ビット操作のマクロ定義
#define	CBI(PORT,BIT)	PORT &=~(1<<BIT)

#endif