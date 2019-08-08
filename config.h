/*
 * config.h
 *
 *  Created on: Jan 28, 2017
 *      Author: buildrooteclipse
 */

#ifndef CONFIG_H_
#define CONFIG_H_



#define BUFFER_SIZE 1024
#define DELAY_BUFFER_LENGTH 480000
#define PITCH_DETECTION_BUFFER_SIZE 1024
#define FILTER_ORDER 2
#define ANTI_ALIASING 1
#define UP_SAMPLE_FILTER 1
#define DOWN_SAMPLE_FILTER 0
#define FOOTSWITCH_COUNT 2
#define SPI_TX_BUFFER_SIZE 1500
#define SPI_RX_BUFFER_SIZE 1500
#define FILE_SIZE 32000
#define DISABLE_AUDIO_THREAD 0  // for allow for stepping through code in debugger
#define AUDIO_THREAD_EFFECTS_BYPASS 0   // for debugging audio processing
#define PROC_BUFFER_REF 1
#define PROC_BUFFER_VAL 0


#endif /* CONFIG_H_ */
