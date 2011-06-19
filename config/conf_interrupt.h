/*
 * conf_interrupt.h
 *
 * Created: 4/21/2011 4:31:23 PM
 *  Author: mpoppe
 */ 


#ifndef CONF_INTERRUPT_H_
#define CONF_INTERRUPT_H_

typedef void (*irq_cb_t)(void);

#define EXTERN_ASSIGN_INTERRUPT(vect) \
    extern irq_cb_t irq_##vect##_cb; \
    extern INLINE void set_##vect##_cb(irq_cb_t irq) {irq_##vect##_cb = irq;} \
    extern INLINE void release_##vect##_cb(void) {irq_##vect##_cb = NULL;} \
    extern INLINE Bool isSet_##vect##_cb(void) {return((irq_##vect##_cb != NULL) ? YES : NO);} \
    extern INLINE irq_cb_t get_##vect##_cb(void) {return irq_##vect##_cb;}
        

EXTERN_ASSIGN_INTERRUPT(TCD0_CCA_vect);



 /*       
#define CONFIG_INTERRUPT_SPM_READY_vect
#define CONFIG_INTERRUPT_TWI_vect
#define CONFIG_INTERRUPT_TIMER3_OVF_vect
#define CONFIG_INTERRUPT_TIMER3_COMPC_vect
#define CONFIG_INTERRUPT_TIMER3_COMPB_vect
#define CONFIG_INTERRUPT_TIMER3_COMPA_vect
#define CONFIG_INTERRUPT_TIMER3_CAPT_vect
#define CONFIG_INTERRUPT_EE_READY_vect
#define CONFIG_INTERRUPT_ADC_vect
#define CONFIG_INTERRUPT_ANALOG_COMP_vect
#define CONFIG_INTERRUPT_USART1_TX_vect
#define CONFIG_INTERRUPT_USART1_UDRE_vect
#define CONFIG_INTERRUPT_USART1_RX_vect
#define CONFIG_INTERRUPT_SPI_STC_vect
#define CONFIG_INTERRUPT_TIMER0_OVF_vect
#define CONFIG_INTERRUPT_TIMER0_COMPB_vect
#define CONFIG_INTERRUPT_TIMER0_COMPA_vect
#define CONFIG_INTERRUPT_TIMER1_OVF_vect
#define CONFIG_INTERRUPT_TIMER1_COMPC_vect
#define CONFIG_INTERRUPT_TIMER1_COMPB_vect
#define CONFIG_INTERRUPT_TIMER1_COMPA_vect
#define CONFIG_INTERRUPT_TIMER1_CAPT_vect
#define CONFIG_INTERRUPT_TIMER2_OVF_vect
#define CONFIG_INTERRUPT_TIMER2_COMPB_vect
#define CONFIG_INTERRUPT_TIMER2_COMPA_vect
#define CONFIG_INTERRUPT_WDT_vect
#define CONFIG_INTERRUPT_USB_COM_vect
#define CONFIG_INTERRUPT_USB_GEN_vect
#define CONFIG_INTERRUPT_PCINT0_vect
#define CONFIG_INTERRUPT_INT7_vect 
#define CONFIG_INTERRUPT_INT6_vect
#define CONFIG_INTERRUPT_INT5_vect
#define CONFIG_INTERRUPT_INT4_vect
#define CONFIG_INTERRUPT_INT3_vect
#define CONFIG_INTERRUPT_INT2_vect
#define CONFIG_INTERRUPT_INT1_vect
#define CONFIG_INTERRUPT_INT0_vect
 */
#endif /* CONF_INTERRUPT_H_ */