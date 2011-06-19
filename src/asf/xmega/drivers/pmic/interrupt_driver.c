/*
 * interrupt_driver.c
 *
 * Created: 3/2/2011 6:24:58 PM
 *  Author: matt
 */ 

#include "avr/interrupt.h"
#include "avr/io.h"
#include "interrupt_driver.h"

typedef void (*irq_cb_t)(void);

#ifdef CONFIG_INTERRUPT_INT0_vect
#ifdef INT0_vect
ASSIGN_INTERRUPT(INT0_vect);
ISR(INT0_vect)
{
   (irq_INT0_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT1_vect
#ifdef INT1_vect
ASSIGN_INTERRUPT(INT1_vect);
ISR(INT1_vect)
{
    //if(isSet_INT1_vect_cb()) {(irq_INT1_vect_cb)();}
    (irq_INT1_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT2_vect
#ifdef INT2_vect
ASSIGN_INTERRUPT(INT2_vect);
ISR(INT2_vect)
{
    //if(isSet_INT2_vect_cb()) (irq_INT2_vect_cb)();
    (irq_INT2_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT3_vect
#ifdef INT3_vect
ASSIGN_INTERRUPT(INT3_vect);
ISR(INT3_vect)
{
    (irq_INT3_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT4_vect
#ifdef INT4_vect
ASSIGN_INTERRUPT(INT4_vect);
ISR(INT4_vect)
{
    (irq_INT4_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT5_vect
#ifdef INT5_vect
ASSIGN_INTERRUPT(INT5_vect);
ISR(INT5_vect)
{
    (irq_INT5_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT6_vect
#ifdef INT6_vect
ASSIGN_INTERRUPT(INT6_vect);
ISR(INT6_vect)
{
    (irq_INT6_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_INT7_vect
#ifdef INT7_vect
ASSIGN_INTERRUPT(INT7_vect);
ISR(INT7_vect)
{
    (irq_INT7_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_PCINT0_vect
#ifdef PCINT0_vect
ASSIGN_INTERRUPT(PCINT0_vect);
ISR(PCINT0_vect)
{
    (irq_PCINT0_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_USB_GEN_vect
#ifdef USB_GEN_vect
ASSIGN_INTERRUPT(USB_GEN_vect);
//ISR(USB_GEN_vect)

#endif
#endif

#ifdef CONFIG_INTERRUPT_USB_COM_vect
#ifdef USB_COM_vect
ASSIGN_INTERRUPT(USB_COM_vect);
//ISR(USB_COM_vect)

#endif
#endif

#ifdef CONFIG_INTERRUPT_WDT_vect
#ifdef WDT_vect
ASSIGN_INTERRUPT(WDT_vect);
ISR(WDT_vect)
{
    (irq_WDT_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER2_COMPA_vect
#ifdef TIMER2_COMPA_vect
ASSIGN_INTERRUPT(TIMER2_COMPA_vect);
ISR(TIMER2_COMPA_vect)
{
    (irq_TIMER2_COMPA_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER2_COMPB_vect
#ifdef TIMER2_COMPB_vect
ASSIGN_INTERRUPT(TIMER2_COMPB_vect);
ISR(TIMER2_COMPB_vect)
{
    (irq_TIMER2_COMPB_vect_cb)();    
}    
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER2_OVF_vect
#ifdef TIMER2_OVF_vect
ASSIGN_INTERRUPT(TIMER2_OVF_vect);
ISR(TIMER2_OVF_vect)
{
    (irq_TIMER2_OVF_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER1_CAPT_vect
#ifdef TIMER1_CAPT_vect
ASSIGN_INTERRUPT(TIMER1_CAPT_vect);
ISR(TIMER1_CAPT_vect)
{
    (irq_TIMER1_CAPT_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER1_COMPA_vect
#ifdef TIMER1_COMPA_vect
ASSIGN_INTERRUPT(TIMER1_COMPA_vect);
ISR(TIMER1_COMPA_vect)
{
    (irq_TIMER1_COMPA_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER1_COMPB_vect
#ifdef TIMER1_COMPB_vect
ASSIGN_INTERRUPT(TIMER1_COMPB_vect);
ISR(TIMER1_COMPB_vect)
{
    (irq_TIMER1_COMPB_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER1_COMPC_vect
#ifdef TIMER1_COMPC_vect
ASSIGN_INTERRUPT(TIMER1_COMPC_vect);
ISR(TIMER1_COMPC_vect)
{
    (irq_TIMER1_COMPC_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER1_OVF_vect
#ifdef TIMER1_OVF_vect
ASSIGN_INTERRUPT(TIMER1_OVF_vect);
ISR(TIMER1_OVF_vect)
{
    (irq_TIMER1_OVF_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER0_COMPA_vect
#ifdef TIMER0_COMPA_vect
ASSIGN_INTERRUPT(TIMER0_COMPA_vect);
ISR(TIMER0_COMPA_vect)
{
    (irq_TIMER0_COMPA_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER0_COMPB_vect
#ifdef TIMER0_COMPB_vect
ASSIGN_INTERRUPT(TIMER0_COMPB_vect);
ISR(TIMER0_COMPB_vect)
{
    (irq_TIMER0_COMPB_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER0_OVF_vect
#ifdef TIMER0_OVF_vect
ASSIGN_INTERRUPT(TIMER0_OVF_vect);
ISR(TIMER0_OVF_vect)
{
    (irq_TIMER0_OVF_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_SPI_STC_vect
#ifdef SPI_STC_vect
ASSIGN_INTERRUPT(SPI_STC_vect);
ISR(SPI_STC_vect)
{
    (irq_SPI_STC_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_USART1_RX_vect
#ifdef USART1_RX_vect
ASSIGN_INTERRUPT(USART1_RX_vect);
ISR(USART1_RX_vect)
{
    (irq_USART1_RX_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_USART1_UDRE_vect
#ifdef USART1_UDRE_vect
ASSIGN_INTERRUPT(USART1_UDRE_vect);
ISR( USART1_UDRE_vect)
{
    (irq_USART1_UDRE_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_USART1_TX_vect
#ifdef USART1_TX_vect
ASSIGN_INTERRUPT(USART1_TX_vect);
ISR(USART1_TX_vect)
{
    (irq_USART1_TX_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_ANALOG_COMP_vect
#ifdef ANALOG_COMP_vect
ASSIGN_INTERRUPT(ANALOG_COMP_vect);
ISR(ANALOG_COMP_vect)
{
    (irq_ANALOG_COMP_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_ADC_vect
#ifdef ADC_vect
ASSIGN_INTERRUPT(ADC_vect);
ISR(ADC_vect)
{
    (irq_ADC_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_EE_READY_vect
#ifdef EE_READY_vect
ASSIGN_INTERRUPT(EE_READY_vect);
ISR(EE_READY_vect)
{
    (irq_EE_READY_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER3_CAPT_vect
#ifdef TIMER3_CAPT_vect
ASSIGN_INTERRUPT(TIMER3_CAPT_vect);
ISR(TIMER3_CAPT_vect)
{
    (irq_TIMER3_CAPT_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER3_COMPA_vect
#ifdef TIMER3_COMPA_vect
ASSIGN_INTERRUPT(TIMER3_COMPA_vect);
ISR(TIMER3_COMPA_vect)
{
    (irq_TIMER3_COMPA_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER3_COMPB_vect
#ifdef TIMER3_COMPB_vect
ASSIGN_INTERRUPT(TIMER3_COMPB_vect);
ISR(TIMER3_COMPB_vect)
{
    (irq_TIMER3_COMPB_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER3_COMPC_vect
#ifdef TIMER3_COMPC_vect
ASSIGN_INTERRUPT(TIMER3_COMPC_vect);
ISR(TIMER3_COMPC_vect)
{
    (irq_TIMER3_COMPC_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TIMER3_OVF_vect
#ifdef TIMER3_OVF_vect
ASSIGN_INTERRUPT(TIMER3_OVF_vect);
ISR(TIMER3_OVF_vect)
{
    (irq_TIMER3_OVF_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_TWI_vect
#ifdef TWI_vect
ASSIGN_INTERRUPT(TWI_vect);
ISR(TWI_vect)
{
    (irq_TWI_vect_cb)();
}
#endif
#endif

#ifdef CONFIG_INTERRUPT_SPM_READY_vect
#ifdef SPM_READY_vect
ASSIGN_INTERRUPT(SPM_READY_vect);
ISR(SPM_READY_vect)
{
    (irq_SPM_READY_vect_cb)();
}
#endif
#endif


//XMEGA

#ifdef CONFIG_INTERRUPT_TCD0_CCA_vect
#ifdef TCF0_CCA_vect
ASSIGN_INTERRUPT(TCD0_CCA_vect);
ISR(TCD0_CCA_vect)
{
	(irq_TCD0_CCA_vect_cb)();
}
#endif
#endif

ISR(BADISR_vect)
{
    //TODO: Added error code/ alarm
}

