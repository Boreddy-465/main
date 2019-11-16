#pragma once

/* Vector table */
extern void (*__Vectors[256]) (void);

/* Function to attach an irq handler.  Directly 
 * replaces the vector table with the funciton
 * provided
 */
static inline void irq_attach(int irq, void (*irq_func) (void))
{
  NVIC_DisableIRQ(static_cast < IRQn > (irq));
  NVIC_ClearPendingIRQ(static_cast < IRQn > (irq));
  __Vectors[16 + irq] = irq_func;
  NVIC_EnableIRQ(static_cast < IRQn > (irq));
}

/* Function to replace the irq handler without disabling, clearing
 * or enabling the irq.
 */
static inline void irq_replace(int irq, void (*irq_func) (void))
{
  __Vectors[16+irq] = irq_func;
}

/* Function to detach an irq.  disables
 * the interrupt and assigns a bad irq handler
 */
static inline void irq_detach(int irq)
{
    extern void Detached_IRQ_Handler();
    NVIC_DisableIRQ(static_cast < IRQn > (irq));
    NVIC_ClearPendingIRQ(static_cast < IRQn > (irq));
    __Vectors[16 + irq] = Detached_IRQ_Handler;
}

/* Returns a non zero when in irq context.
 */
static inline int is_irq_context()
{
  return (__get_IPSR() != 0);
}

static inline void irq_disable(int irq)
{
  NVIC_DisableIRQ(static_cast < IRQn > (irq));
}

static inline void irq_enable(int irq)
{
  NVIC_EnableIRQ(static_cast < IRQn > (irq));
}

static inline void irq_clear(int irq)
{
  NVIC_ClearPendingIRQ(static_cast < IRQn > (irq));
}

static inline unsigned int is_irq_pending(int irq)
{
  return NVIC_GetPendingIRQ(static_cast < IRQn > (irq));
}
