 /* USER CODE BEGIN 3 */
 //HAL_UART_Transmit(&huart6,"0",3, 10);

uint16_t Motor_Speed1; // ���ǵ�1�ܰ�
uint16_t Motor_Speed2; // ���ǵ�2�ܰ�

void UART6_IRQHandler(void)// ������ ���ͷ�Ʈ ��
{    
  if ( (UART6->SR & USART_SR_RXNE) )// flag ���� �ʿ����  �����͸� ������ flag���� ������
	{
		char ch;
		ch = (uint16_t)(UART6->DR & (uint16_t)0x01FF);	// ���ŵ� ���� ����
                
                // ���� ����  PWM: TIM9 Ch1 PE5 , ���� ���� DIR:  GPIO A  PA5 
                // ������ ���� PWM: TIM9 Ch2 PE6, ������ ���� DIR: GPIO A  PA6
                if(ch==0x31){ // ���� 
              TIM9->CCR1=(Motor_Speed1-1); //���� ���� �ӵ� 1�ܰ�
              HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);//������
              
              TIM9->CCR2=(Motor_Speed1-1); //������ ���� �ӵ� 1�ܰ�
              HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);//������
              }
        }
}



// ���� PWM: TIM9 Ch1 PE5 ,  ���� DIR:  GPIO A  PA5 , ���� Encoder :  TIM4 Ch1, Ch2 :  PB6, PB7 
    
    if(TIM_FLAG==1){
       
      TIM9->CCR1=(order[i]-1);
      if(i<4){ // 5���� ������
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);  // DIR  //������
      TIM_CCR_Value=order[i];
      }
      else{
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);  // DIR  //������
      if(order[i]==1){TIM_CCR_Value=0;} //  TIM_CCR_Value ����  0���� ǥ���Ǳ� ����  �̰��� ���ϸ� 1�� ǥ�� ARR���� -1, ������ϱ⿡ ����.
      else{TIM_CCR_Value=-order[i];}
      }
      TIM_FLAG=0;
      SWITCH_FLAG=0;
        i++;
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);//  LED��
    }
    if(i>8){
    i=0;
    }
    ch=__HAL_TIM_GET_COUNTER(&htim4);
    sprintf(string,"%6d %3d \r\n",ch,TIM_CCR_Value);
    HAL_UART_Transmit(&huart6,(uint8_t *)string,strlen(string),100);
    HAL_Delay(100);
  }