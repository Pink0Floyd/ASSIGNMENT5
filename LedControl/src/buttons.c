#include "buttons.h"
#include "gpio.h"

static int buttons_pin[4]={BUTTON1,BUTTON2,BUTTON3,BUTTON4};                  // Buttons data with pins numbers             
static int buttons_pos[4]={1,2,4,8};                                          // Buttons data with corresponding position 

static struct gpio_callback but1_cb_data;                                     // Callback structure related to BUTTON 1
static struct gpio_callback but2_cb_data;                                     // Callback structure related to BUTTON 2
static struct gpio_callback but3_cb_data;                                     // Callback structure related to BUTTON 3
static struct gpio_callback but4_cb_data;                                     // Callback structure related to BUTTON 4

static int but1_flag = 0;						      // Callback variable, flag to signal a BUTTON 1 press
static int but2_flag = 0;						      // Callback variable, flag to signal a BUTTON 2 press 
static int but3_flag = 0;						      // Callback variable, flag to signal a BUTTON 3 press 
static int but4_flag = 0;						      // Callback variable, flag to signal a BUTTON 4 press 

static const struct device *gpio0_dev;

///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:
void reset_flag(uint8_t n)
{
	switch(n)
	{
		case 1:
			but1_flag=0;	
			break;
		case 2:
			but2_flag=0; 
			break;
		case 3:
			but3_flag=0; 
			break;
		case 4:
			but4_flag=0;
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
// Calback Functions:
void but1_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
      reset_flag(1);
      but1_flag=1;										      // Update Flag   
      if(PRINT_BUTTONS_DEBUG)
      {
	    printk("Button 1 Pressed\n\r");       									      // Update Flag 
      }
} 

void but2_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
      reset_flag(2);
      but2_flag=1;	
      if(PRINT_BUTTONS_DEBUG)
      {
	    printk("Button 2 Pressed\n\r");       									      // Update Flag 
      }
} 

void but3_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
      reset_flag(3);
      but3_flag=1;	
      if(PRINT_BUTTONS_DEBUG)
      {
	    printk("Button 3 Pressed\n\r");       									      // Update Flag 
      } 
} 

void but4_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
      reset_flag(4);
      but4_flag=1;	
      if(PRINT_BUTTONS_DEBUG)
      {
	    printk("Button 4 Pressed\n\r");       									      // Update Flag 
      }
} 


void buttons_callback_init(char n_buttons)
{
      if((n_buttons & 1) == 1)
      {
	    if(PRINT_BUTTONS_DEBUG)
	    {
		  printk("Button 1 Callback Initialisition\n\r");
	    }
	    gpio_init_callback(&but1_cb_data, but1_cbfunction, BIT(BUTTON1));
	    gpio_add_callback(gpio0_dev, &but1_cb_data);
      }
      if((n_buttons & 2) == 2)
      {
	    if(PRINT_BUTTONS_DEBUG)
	    {
		  printk("Button 2 Callback Initialisition\n\r");
	    }
	    gpio_init_callback(&but2_cb_data, but2_cbfunction, BIT(BUTTON2));
	    gpio_add_callback(gpio0_dev, &but2_cb_data);
      }
      if((n_buttons & 4) == 4)
      {
	    if(PRINT_BUTTONS_DEBUG)
	    {
		  printk("Button 3 Callback Initialisition\n\r");
	    }
	    gpio_init_callback(&but3_cb_data, but3_cbfunction, BIT(BUTTON3));
	    gpio_add_callback(gpio0_dev, &but3_cb_data);
      }
      if((n_buttons & 8) == 8)
      {
	    if(PRINT_BUTTONS_DEBUG)
	    {
		  printk("Button 4 Callback Initialisition\n\r");
	    }
	    gpio_init_callback(&but4_cb_data, but4_cbfunction, BIT(BUTTON4));
	    gpio_add_callback(gpio0_dev, &but4_cb_data);
      }
}

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:
void buttons_init(char n_buttons)                                     // Initialize the board's buttons  
{
	gpio0_dev=gpio0_init();
      int i=0;
      int ret=0;

      for(i=0; i<4; i++)
      {
		if((n_buttons & buttons_pos[i]) == buttons_pos[i])
		{
			
			ret = gpio_pin_configure(gpio0_dev, buttons_pin[i], GPIO_INPUT | GPIO_PULL_UP);
			if (ret < 0) 
			{
				printk("Error %d: Failed to configure Button %d \n\r", ret, (i+1));
				i=5;
			}
		}
      }
}

void buttons_init_(char n_buttons, char c)
{
      buttons_init(n_buttons);
      int ret=0;
      int i=0;
    
      if((c=='H') || (c='h'))												// Rising edge interrupt configuration
      {
	    for(i=0; i<4; i++)
	    {
		  if((n_buttons & buttons_pos[i]) == buttons_pos[i])
		  {
			if(PRINT_BUTTONS_DEBUG)
			{	  
			      printk("%d\n\r",buttons_pos[i]);
			}
			ret=gpio_pin_interrupt_configure(gpio0_dev, buttons_pin[i], GPIO_INT_EDGE_TO_ACTIVE);		// Button rising edge interrupt configuration 
			if (ret < 0)											// In case of fail initialization and consequent error message
			{ 
			      printk("Error %d: failed to configure interrupt on BUTTON %d pin \n\r", ret, (i+1));
			      return;
			}
		  }
	    }
      }
      else if((c=='L') || (c='l'))											// Falling edge interrupt configuration
      {
	    for(i=0; i<4; i++)
	    {
		  if((n_buttons & buttons_pos[i]) == buttons_pos[i])
		  {
			if(PRINT_BUTTONS_DEBUG)
			{
			      printk("%d\n\r",buttons_pos[i]);
			}
			ret=gpio_pin_interrupt_configure(gpio0_dev, buttons_pin[i], GPIO_INT_EDGE_TO_INACTIVE);		// Button falling edge interrupt configuration 
			if (ret < 0)											// In case of fail initialization and consequent error message
			{ 
			      printk("Error %d: failed to configure interrupt on BUTTON %d pin \n\r", ret, (i+1));
			      return;
			}
		  }
	    }
      }
      else if((c=='B') || (c='b'))											// Rising and falling edge interrupt configuration
      {
	    for(i=0; i<4; i++)
	    {	  
		  if((n_buttons & buttons_pos[i]) == buttons_pos[i])
		  {
			if(PRINT_BUTTONS_DEBUG)
			{
			      printk("%d\n\r",buttons_pos[i]);
			}
			ret=gpio_pin_interrupt_configure(gpio0_dev, buttons_pin[i], GPIO_INT_EDGE_BOTH);              // Button rising and fallinf edge interrupt configuration 
			if (ret < 0)                                                                                  // In case of fail initialization and consequent error message
			{ 
			      printk("Error %d: failed to configure interrupt on BUTTON %d pin \n\r", ret, (i+1));
			      return;
			}
		  }
	    }
      }

      buttons_callback_init(n_buttons);
}

uint8_t read_buttons(uint8_t button)
{
      uint8_t aux_flag=0;
      switch (button)
      {
	    case 1:
		  aux_flag=but1_flag;
		  reset_flag(1);
		  break;
     
	    case 2:
		  aux_flag=but2_flag;
		  reset_flag(2);
		  break;
     
	    case 3:
		  aux_flag=but3_flag;
		  reset_flag(3);
		  break;
	    case 4:
		  aux_flag=but4_flag;
		  reset_flag(4);
		  break;
	    default:
		  printk("Wrong argument for read_buttons\n\r");
		  break;
      }
	return aux_flag;
}