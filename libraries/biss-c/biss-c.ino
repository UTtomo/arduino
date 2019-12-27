#include "user_init.h"
/*
D3 :MAピン
D2 :SLOピン
のつもりで作ってます

TIM0使えないのでdelay関係の関数使えません
*/

#define DATA_SIZE 1024

void setup() {
	
	SBI(DDRD,3);	//D3ピン出力
	CBI(DDRD,2);	//D2ピン入力
	
	TCCR0A = 0b00000010;//標準タイマ動作
	TCCR0B = 0b00000001;//分周1/1
	
	TIMSK0 = 0b00000010;//CTC_ON
	OCR0A = 79;			//80clock->5usで割り込み
	
	SBI(PORTD,3);		//MAをHIGHに
}

//データ保存用
long data_table[DATA_SIZE]={0};
int data_reading;

//割り込み関数
 ISR(TIMER0_COMPA_vect)
{
	static int step;	//データ受信のステップ
	static int clk;		//MAクロック許可(0で停止,1で動作)
	static long data_buf;	//データの一時格納
	static int CRC;		//エラーチェック用(使用してない、必要なら自分でどぞ)

	//MAがHIGHのとき
	if(PIND&0x08){
		switch(step){
			//起動
			case 0:
				if(PIND&0x40){
					step++;
					clk=1;
					data_buf=CRC=0;
				}
				break;
				
			case 1://ack待ち
			case 38: //Warning 必要なら適宜分離して処理
				step++;
				break;
			
			case 2:	//ackに正常に入ったことを検出
			case 4:	//'0'検出
				if(PIND&0x40==0)step++;
				else step=0;
				break;
			
			case 3:	//スタート検出(ここだけは待ちなので、elseのときもstepがリセットされない)
				if(PIND&0x40)step++;
				break;
			
			//case 5~36まで データ それ以外は入らないものとする(多分ｗ)
			default:
				data_buf+=((PIND&0x40)>>2)<<(36-step);
				step++;
				break;
				
			//エラーチェック
			case 37:
				if(PIND&0x40)step++;
				else step=0;
				break;
			
			//CRC格納
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
				CRC+=((PIND&0x40)>>2)<<(44-step);
				step++;
				break;
			//終了処理
			case 45:
				data_table[data_reading]=data_buf;
				data_reading++;
				if(data_reading==DATA_SIZE)data_reading=0;
				step=0;
				clk=0;
				break;
		}
	}
	
	PORTD^=(clk<<3);//clk=1のときだけ反転動作
}


void loop() {
  //loop関数はArduinoのmaiｎ関数から呼び出されている
  //メイン関数ループ毎のloop関数呼び出しオーバーヘッドが嫌なので、mainに戻らないようにする
  //関数のオーバーヘッドはクロックが数サイクル必要なのでもったいない
  while(1){


	}
}
