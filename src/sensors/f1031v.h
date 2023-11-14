#ifndef __F1031V_H__
#define __F1031V_H__

/* Voltages. */
#define F1031V_M 36.463 
#define F1031V_INTERCEPT -18.036
#define F1031V_OFFSET 50

void sample_f1031v(struct flowsensor *f1031v);

#endif