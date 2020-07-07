 /* USER CODE BEGIN 3 */
 //HAL_UART_Transmit(&huart6,"0",3, 10);

uint16_t Motor_Speed1; // 스피드1단계
uint16_t Motor_Speed2; // 스피드2단계

void UART6_IRQHandler(void)// 받으면 인터럽트 됨
{    
  if ( (UART6->SR & USART_SR_RXNE) )// flag 지울 필요없이  데이터를 읽으면 flag값이 지워짐
	{
		char ch;
		ch = (uint16_t)(UART6->DR & (uint16_t)0x01FF);	// 수신된 문자 저장
                
                // 왼쪽 모터  PWM: TIM9 Ch1 PE5 , 왼쪽 모터 DIR:  GPIO A  PA5 
                // 오른쪽 모터 PWM: TIM9 Ch2 PE6, 오른쪽 모터 DIR: GPIO A  PA6
                if(ch==0x31){ // 전진 
              TIM9->CCR1=(Motor_Speed1-1); //왼쪽 모터 속도 1단계
              HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);//정방향
              
              TIM9->CCR2=(Motor_Speed1-1); //오른쪽 모터 속도 1단계
              HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);//정방향
              }
        }
}



// 모터 PWM: TIM9 Ch1 PE5 ,  모터 DIR:  GPIO A  PA5 , 모터 Encoder :  TIM4 Ch1, Ch2 :  PB6, PB7 
    
    if(TIM_FLAG==1){
       
      TIM9->CCR1=(order[i]-1);
      if(i<4){ // 5보다 작으면
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  // DIR  //정방향
      TIM_CCR_Value=order[i];
      }
      else{
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);  // DIR  //역방향
      if(order[i]==1){TIM_CCR_Value=0;} //  TIM_CCR_Value 값이  0으로 표현되기 위해  이것을 안하면 1로 표현 ARR에서 -1, 해줘야하기에 했음.
      else{TIM_CCR_Value=-order[i];}
      }
      TIM_FLAG=0;
      SWITCH_FLAG=0;
        i++;
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);//  LED끔
    }
    if(i>8){
    i=0;
    }
    ch=__HAL_TIM_GET_COUNTER(&htim4);
    sprintf(string,"%6d %3d \r\n",ch,TIM_CCR_Value);
    HAL_UART_Transmit(&huart6,(uint8_t *)string,strlen(string),100);
    HAL_Delay(100);
  }